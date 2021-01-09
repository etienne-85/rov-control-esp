
#include <iostream>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include <json.h>


using namespace std;

class WebUtils
{
public:
    static Json::Value parseJSON(string str);
    static Json::Value parseJSON_alt(string str);
};

class WebServer
{
public:
    // Create AsyncWebServer object on port 80
    static AsyncWebServer server;
    WebServer();
    void initSPIFFS();
    void initRoutes();
};

class WebSockets
{
public:
    static AsyncWebSocket websocket;
    static string socketData;
    bool ledState = 0;
    const int ledPin = 4;

    WebSockets();
    void loop();

private:
    static void notifyClients(std::string data);
    static void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
    static void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                        void *arg, uint8_t *data, size_t len);

    String processor(const String &var);
    void initWebSocket();
};