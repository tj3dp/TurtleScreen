#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "moonraker.h"

//#define MOONRAKER_DEBUG

uint32_t lastMoonRakerUpdate;
uint32_t lastPostUpdate;
TaskHandle_t postTaskHandle = NULL;

String MOONRAKER::send_request(const char *type, String path)
{
    String ip = targetHost;
    String port = "80";
    String url = "http://" + ip + ":" + port + path;
    String response = "";
    HTTPClient client;
    // replace all " " space to "%20" for http
    url.replace(" ", "%20");
    client.begin(url);
    // set timeout to 60 seconds since some gcode like G28 need long time to feedback
    client.setTimeout(60000);
    int code = client.sendRequest(type, "");
    // http request success
    if (code > 0)
    {
        unconnected = false;
        response = client.getString();
        if (code == 400)
        {
            if (!response.isEmpty())
            {
                // DEBUG_PRINTLN(response.c_str());
                DynamicJsonDocument json_parse(response.length() * 2);
                deserializeJson(json_parse, response);
                String msg = json_parse["error"]["message"].as<String>();
#ifdef MOONRAKER_DEBUG
                DEBUG_PRINTLN(msg.c_str());
#endif
                msg.remove(0, 41);               //  remove header {'error': 'WebRequestError', 'message':
                msg.remove(msg.length() - 2, 2); // remove tail }
                msg.replace("\\n", "\n");
                // lv_popup_warning(msg.c_str(), true);
            }
        }
    }
    else
    {
        /*
         * since some gcode need long time cause code=-11 error
         * so don't set status when POST gcode
         * only set when GET
         */
        if (strcmp(type, "GET") == 0)
            unconnected = true;
        DEBUG_PRINTF("moonraker http %s error.\r\n", type);
    }
    client.end(); // Free the resources

#ifdef MOONRAKER_DEBUG
    DEBUG_PRINTF("\r\n\r\n %s code:%d************ %s *******************\r\n\r\n", type, code, url.c_str());
    DEBUG_PRINTLN(response.c_str());
    DEBUG_PRINTLN("\r\n*******************************\r\n\r\n");
#endif

    return response;
}

void MOONRAKER::http_post_loop(void)
{
    if (post_queue.count == 0)
        return;
    DEBUG_PRINTLN("read queue index: " + String(post_queue.index_r));
    DEBUG_PRINTLN("request: " + post_queue.queue[post_queue.index_r]);
    send_request("POST", post_queue.queue[post_queue.index_r]);
    post_queue.count--;
    post_queue.index_r = (post_queue.index_r + 1) % QUEUE_LEN;
}

bool MOONRAKER::post_to_queue(String path)
{
    if (post_queue.count >= QUEUE_LEN)
    {
        DEBUG_PRINTLN("moonraker post queue overflow!");
        return false;
    }
    post_queue.queue[post_queue.index_w] = path;
    post_queue.index_w = (post_queue.index_w + 1) % QUEUE_LEN;
    post_queue.count++;
#if 1  // def MOONRAKER_DEBUG
    DEBUG_PRINTF("\r\n\r\n ************ post queue *******************\r\n\r\n");
    DEBUG_PRINT("count: ");
    DEBUG_PRINTLN(post_queue.count);
    DEBUG_PRINT("index_w: ");
    DEBUG_PRINTLN(post_queue.index_w);
    DEBUG_PRINT("queue: ");
    DEBUG_PRINTLN(path);
    DEBUG_PRINTLN("\r\n*******************************\r\n\r\n");
#endif
    return true;
}

bool MOONRAKER::post_gcode_to_queue(String gcode)
{
    String path = "/printer/gcode/script?script=" + gcode;
    return post_to_queue(path);
}

void MOONRAKER::get_printer_ready(void)
{
    HTTPClient http;
    http.begin("http://" + targetHost + "/printer/objects/query?webhooks");
    int httpresponsecode = http.GET();
    if (httpresponsecode == 200)
    {
        String webhooks = http.getString();
        if (!webhooks.isEmpty())
        {
            DynamicJsonDocument json_parse(webhooks.length() * 2);
            DeserializationError error = deserializeJson(json_parse, webhooks);
            if (error)
                {
                    DEBUG_PRINT("Failed to parse JSON: ");
                    DEBUG_PRINTLN(error.f_str());
                    return;
                }
            String state = json_parse["result"]["status"]["webhooks"]["state"].as<String>();
            unready = (state == "ready") ? false : true;
#ifdef MOONRAKER_DEBUG
            DEBUG_PRINT("unready: ");
            DEBUG_PRINTLN(unready);
#endif
        }
        else
        {
            unready = true;
            DEBUG_PRINTLN("Empty: moonraker: get_printer_ready");
        }
    }
}

void MOONRAKER::get_printer_info(void) 
{
    http.begin("http://" + targetHost + "/api/printer");
    int httpresponsecode = http.GET();
    if (httpresponsecode > 0) 
    {
        String printer_info = http.getString();
        if (!printer_info.isEmpty()) 
        {
            DynamicJsonDocument json_parse(1024); 
            DeserializationError error = deserializeJson(json_parse, printer_info);
            if (error) {
                DEBUG_PRINT("Deserialization failed: ");
                DEBUG_PRINTLN(error.c_str());
                return;
            }
            data.pause = json_parse["state"]["flags"]["pausing"].as<bool>() ||
                         json_parse["state"]["flags"]["paused"].as<bool>();
            data.printing = json_parse["state"]["flags"]["printing"].as<bool>() ||
                            json_parse["state"]["flags"]["cancelling"].as<bool>() || 
                            data.pause;
            data.bed_actual = int16_t(json_parse["temperature"]["bed"]["actual"].as<double>() + 0.5f);
            data.bed_target = int16_t(json_parse["temperature"]["bed"]["target"].as<double>() + 0.5f);
            data.nozzle_actual = int16_t(json_parse["temperature"]["tool0"]["actual"].as<double>() + 0.5f);
            data.nozzle_target = int16_t(json_parse["temperature"]["tool0"]["target"].as<double>() + 0.5f);

#ifdef MOONRAKER_DEBUG
            DEBUG_PRINT("Printing: ");
            DEBUG_PRINTLN(data.printing);
            DEBUG_PRINT("Bed Actual: ");
            DEBUG_PRINTLN(data.bed_actual);
            DEBUG_PRINT("Bed Target: ");
            DEBUG_PRINTLN(data.bed_target);
            DEBUG_PRINT("Nozzle Actual: ");
            DEBUG_PRINTLN(data.nozzle_actual);
            DEBUG_PRINT("Nozzle Target: ");
            DEBUG_PRINTLN(data.nozzle_target);
#endif
        } else {
            DEBUG_PRINTLN("Empty: moonraker: get_printer_info");
        }
    } else {
        DEBUG_PRINT("HTTP Error: ");
        DEBUG_PRINTLN(httpresponsecode);
    }
    http.end();
}

void MOONRAKER::http_get_loop(void)
{
    data_unlock = false;
    get_printer_ready();
    if (!unready)
    {
        get_printer_info();
    }
    data_unlock = true;
}

MOONRAKER moonraker;

void moonraker_post_task(void *parameter)
{
    for (;;)
    {
        moonraker.http_post_loop();
        lastPostUpdate = xTaskGetTickCount();
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// Klipper Control: Restart Firmware Restart. /printer/restart, /printer/firmware_restart
// Service Control: stop start restart. POST /machine/services/stop|restart|start?service={name}
// Host Control: Reboot, Shutdown. POST /machine/shutdown, POST /machine/reboot
