// web_page.h
#ifndef WEB_PAGE_H
#define WEB_PAGE_H

// Store the HTML in a raw string literal
const char webpage_html[] = R"rawliteral(
<html><body>
    <form action="/setConfig" method="POST">
        <label for="ssid">Wi-Fi SSID:</label><br>
        <input type="text" id="ssid" name="ssid"><br>
        <label for="password">Wi-Fi Password:</label><br>
        <input type="password" id="password" name="password"><br><br>
        <label for="host">Target Device IP/Hostname:</label><br>
        <input type="text" id="host" name="host"><br><br>
        <input type="submit" value="Submit">
    </form>
</body></html>
)rawliteral";

#endif // WEB_PAGE_H
