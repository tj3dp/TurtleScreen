#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "moonraker.h"
#include "pinout_t3.h"

//#define MOONRAKER_DEBUG

uint32_t lastMoonRakerUpdate;
uint32_t lastPostUpdate;
TaskHandle_t postTaskHandle = NULL;
TaskHandle_t moonrakerTaskHandle = NULL;

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
                // Serial.println(response.c_str());
                DynamicJsonDocument json_parse(response.length() * 2);
                deserializeJson(json_parse, response);
                String msg = json_parse["error"]["message"].as<String>();
#ifdef MOONRAKER_DEBUG
                Serial.println(msg.c_str());
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
        Serial.printf("moonraker http %s error.\r\n", type);
    }
    client.end(); // Free the resources

#ifdef MOONRAKER_DEBUG
    Serial.printf("\r\n\r\n %s code:%d************ %s *******************\r\n\r\n", type, code, url.c_str());
    Serial.println(response.c_str());
    Serial.println("\r\n*******************************\r\n\r\n");
#endif

    return response;
}

void MOONRAKER::http_post_loop(void)
{
    if (post_queue.count == 0)
        return;
    send_request("POST", post_queue.queue[post_queue.index_r]);
    post_queue.count--;
    post_queue.index_r = (post_queue.index_r + 1) % QUEUE_LEN;
}

bool MOONRAKER::post_to_queue(String path)
{
    if (post_queue.count >= QUEUE_LEN)
    {
        Serial.println("moonraker post queue overflow!");
        return false;
    }
    post_queue.queue[post_queue.index_w] = path;
    post_queue.index_w = (post_queue.index_w + 1) % QUEUE_LEN;
    post_queue.count++;
#ifdef MOONRAKER_DEBUG
    Serial.printf("\r\n\r\n ************ post queue *******************\r\n\r\n");
    Serial.print("count: ");
    Serial.println(post_queue.count);
    Serial.print("index_w: ");
    Serial.println(post_queue.index_w);
    Serial.print("queue: ");
    Serial.println(path);
    Serial.println("\r\n*******************************\r\n\r\n");
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
    http.begin(targetHost + "/printer/objects/query?webhooks");
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
                    Serial.print("Failed to parse JSON: ");
                    Serial.println(error.f_str());
                    return;
                }
            String state = json_parse["result"]["status"]["webhooks"]["state"].as<String>();
            unready = (state == "ready") ? false : true;
#ifdef MOONRAKER_DEBUG
            Serial.print("unready: ");
            Serial.println(unready);
#endif
        }
        else
        {
            unready = true;
            Serial.println("Empty: moonraker: get_printer_ready");
        }
    }
}
/*
void MOONRAKER::get_printer_info(void)
{
    http.begin(targetHost + "/api/printer");
    int httpresponsecode = http.GET();
    if (httpresponsecode == 200)
    {
        String printer_info = http.getString();
        if (!printer_info.isEmpty())
        {
            DynamicJsonDocument json_parse(printer_info.length() * 2);
            deserializeJson(json_parse, printer_info);
            data.pause = json_parse["state"]["flags"]["pausing"].as<bool>();        // pausing
            data.pause |= json_parse["state"]["flags"]["paused"].as<bool>();        // paused
            data.printing = json_parse["state"]["flags"]["printing"].as<bool>();    // printing
            data.printing |= json_parse["state"]["flags"]["cancelling"].as<bool>(); // cancelling
            data.printing |= data.pause;                                            // pause
            data.bed_actual = int16_t(json_parse["temperature"]["bed"]["actual"].as<double>() + 0.5f);
            data.bed_target = int16_t(json_parse["temperature"]["bed"]["target"].as<double>() + 0.5f);
            data.nozzle_actual = int16_t(json_parse["temperature"]["tool0"]["actual"].as<double>() + 0.5f);
            data.nozzle_target = int16_t(json_parse["temperature"]["tool0"]["target"].as<double>() + 0.5f);
#ifdef MOONRAKER_DEBUG
            // Serial.print("unoperational: ");
            // Serial.println(unoperational);
            Serial.print("printing: ");
            Serial.println(data.printing);
            Serial.print("bed_actual: ");
            Serial.println(data.bed_actual);
            Serial.print("bed_target: ");
            Serial.println(data.bed_target);
            Serial.print("nozzle_actual: ");
            Serial.println(data.nozzle_actual);
            Serial.print("nozzle_target: ");
            Serial.println(data.nozzle_target);
#endif
        }
        else
        {
            Serial.println("Empty: moonraker: get_printer_info");
        }
    }
    // String printer_info = send_request("GET", "/api/printer");
}
*/

void MOONRAKER::get_printer_info(void) {
    http.begin("http://" + targetHost + "/api/printer");
    int httpresponsecode = http.GET();

    if (httpresponsecode > 0) {
        String printer_info = http.getString();
        if (!printer_info.isEmpty()) {
            // Increase the size for parsing and add error handling
            DynamicJsonDocument json_parse(1024);  // Size adjusted for typical data, increase if needed

            DeserializationError error = deserializeJson(json_parse, printer_info);
            if (error) {
                Serial.print("Deserialization failed: ");
                Serial.println(error.c_str());
                return;
            }

            // Parse data assuming JSON structure is accurate
            data.pause = json_parse["state"]["flags"]["pausing"].as<bool>() ||
                         json_parse["state"]["flags"]["paused"].as<bool>();
            data.printing = json_parse["state"]["flags"]["printing"].as<bool>() ||
                            json_parse["state"]["flags"]["cancelling"].as<bool>() || data.pause;

            // Safely parse temperatures, converting to integer values
            data.bed_actual = int16_t(json_parse["temperature"]["bed"]["actual"].as<double>() + 0.5f);
            data.bed_target = int16_t(json_parse["temperature"]["bed"]["target"].as<double>() + 0.5f);
            data.nozzle_actual = int16_t(json_parse["temperature"]["tool0"]["actual"].as<double>() + 0.5f);
            data.nozzle_target = int16_t(json_parse["temperature"]["tool0"]["target"].as<double>() + 0.5f);

#ifdef MOONRAKER_DEBUG
            Serial.print("Printing: ");
            Serial.println(data.printing);
            Serial.print("Bed Actual: ");
            Serial.println(data.bed_actual);
            Serial.print("Bed Target: ");
            Serial.println(data.bed_target);
            Serial.print("Nozzle Actual: ");
            Serial.println(data.nozzle_actual);
            Serial.print("Nozzle Target: ");
            Serial.println(data.nozzle_target);
#endif
        } else {
            Serial.println("Empty: moonraker: get_printer_info");
        }
    } else {
        Serial.print("HTTP Error: ");
        Serial.println(httpresponsecode);
    }
    http.end();
}


// only return gcode file name except path
// for example:"SD:/test/123.gcode"
// only return "123.gcode"
const char *path_only_gcode(const char *path)
{
    char *name = strrchr(path, '/');

    if (name != NULL)
        return (name + 1);
    else
        return path;
}

void MOONRAKER::get_progress(void)
{
    http.begin("http://" + targetHost + "/printer/objects/query?virtual_sdcard");
    int httpresponsecode = http.GET();
    if (httpresponsecode > 0)
    {
        String display_status = http.getString();
        if (!display_status.isEmpty())
        {
            DynamicJsonDocument json_parse(display_status.length() * 2);
            deserializeJson(json_parse, display_status);
            data.progress = (uint8_t)(json_parse["result"]["status"]["virtual_sdcard"]["progress"].as<double>() * 100 + 0.5f);
            String path = json_parse["result"]["status"]["virtual_sdcard"]["file_path"].as<String>();
            strlcpy(data.file_path, path_only_gcode(path.c_str()), sizeof(data.file_path) - 1);
            data.file_path[sizeof(data.file_path) - 1] = 0;
#ifdef MOONRAKER_DEBUG
            Serial.print("progress: ");
            Serial.println(data.progress);
            Serial.print("path: ");
            Serial.println(data.file_path);
#endif
        }
        else
        {
            Serial.println("Empty: moonraker: get_progress");
        }
    }else {
        Serial.print("HTTP Error: ");
        Serial.println(httpresponsecode);
    }
    http.end();
}

void MOONRAKER::get_AFC_status(void)
{
    http.begin("http://" + targetHost + "/printer/objects/query?gcode_macro%20_AFC_STATUS");
    int httpresponsecode = http.GET();
    if (httpresponsecode > 0)
    {
        String AFC_status = http.getString();
        if (!AFC_status.isEmpty())
        {
            DynamicJsonDocument json_parse(AFC_status.length() * 2);
            deserializeJson(json_parse, AFC_status);
            data.homing = json_parse["result"]["status"]["gcode_macro _AFC_status"]["homing"].as<bool>();
            data.probing = json_parse["result"]["status"]["gcode_macro _AFC_status"]["probing"].as<bool>();
            data.qgling = json_parse["result"]["status"]["gcode_macro _AFC_status"]["qgling"].as<bool>();
            data.heating_nozzle = json_parse["result"]["status"]["gcode_macro _AFC_status"]["heating_nozzle"].as<bool>();
            data.heating_bed = json_parse["result"]["status"]["gcode_macro _AFC_status"]["heating_bed"].as<bool>();
            data.changing_lanes = json_parse["result"]["status"]["gcode_macro _AFC_status"]["changing_lane"].as<bool>();

#ifdef MOONRAKER_DEBUG
            Serial.print("homing: ");
            Serial.println(data.homing);
            Serial.print("probing: ");
            Serial.println(data.probing);
            Serial.print("qgling: ");
            Serial.println(data.qgling);
            Serial.print("heating_nozzle: ");
            Serial.println(data.heating_nozzle);
            Serial.print("heating_bed: ");
            Serial.println(data.heating_bed);
#endif
        }
        else
        {
            Serial.println("Empty: moonraker: get_AFC_status");
        }
    }else {
        Serial.print("HTTP Error: ");
        Serial.println(httpresponsecode);
    }
    http.end();
}

void MOONRAKER::http_get_loop(void)
{
    data_unlock = false;
    get_printer_ready();
    if (!unready)
    {
        // get_T3_status() must before get_printer_info()
        // avoid homing, qgling, etc action flag = 1
        // but printing flag has not refresh
        get_AFC_status();
        get_printer_info();
        if (data.printing)
        {
            get_progress();
        }
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

void moonraker_task(void *parameter)
{

    xTaskCreate(moonraker_post_task, "moonraker post",
                4096,           // Stack size (bytes)
                NULL,           // Parameter to pass
                6,              // Task priority
                &postTaskHandle // Task handle
    );
    for (;;)
    {
        if (WiFi.status() == WL_CONNECTED && !targetHost.isEmpty())
        {
            moonraker.http_get_loop();
        }
        lastMoonRakerUpdate = xTaskGetTickCount();
        vTaskDelay(pdMS_TO_TICKS(150));
    }
}

// Klipper Control: Restart Firmware Restart. /printer/restart, /printer/firmware_restart
// Service Control: stop start restart. POST /machine/services/stop|restart|start?service={name}
// Host Control: Reboot, Shutdown. POST /machine/shutdown, POST /machine/reboot
