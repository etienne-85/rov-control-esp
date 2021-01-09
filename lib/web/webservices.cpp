#include <webservices.h>

AsyncWebServer WebServer::server = AsyncWebServer(80);

/**
 * WebServer class implem
 */
WebServer::WebServer()
{
  initSPIFFS();
  initRoutes();
}

void WebServer::initSPIFFS()
{
  cout << "init SPIFFS to serve http files" << endl;
  // Initialize SPIFFS
  if (!SPIFFS.begin(true))
  {
    cout << "An Error has occurred while mounting SPIFFS" << endl;
    return;
  }
}

void WebServer::initRoutes()
{
  cout << "init http routes" << endl;
  // Route for root / web page
  // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
  //   request->send(SPIFFS, "/index.html", String(), false, processor);
  // });
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  // Route to load css file
  server.on("/main.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/main.css", "text/css");
  });

  // Route to load js file
  server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/main.js", "text/js");
  });

  // Start server
  server.begin();
}

/**
 * WebSockets class implem
 */
// WebSockets::websocket = WebSockets("/ws");
string WebSockets::socketData = R"({"left":0,"right":0})";
AsyncWebSocket WebSockets::websocket = AsyncWebSocket("/ws");

WebSockets::WebSockets()
{
  websocket.onEvent(onEvent);
}

void WebSockets::notifyClients(string data)
{
  // websocket.textAll(String(ledState));
  websocket.textAll(String(data.c_str()));
}

void WebSockets::handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
  {
    data[len] = 0;
    // if (strcmp((char *)data, "toggle") == 0)
    // {
    //   ledState = !ledState;
    cout << data << endl;
    string s(data, data + len);
    socketData = s;
    notifyClients(s);
    // }
  }
}

void WebSockets::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
                         void *arg, uint8_t *data, size_t len)
{
  switch (type)
  {
  case WS_EVT_CONNECT:
    cout << "WebSocket client " << client->id() << " connected from " << client->remoteIP().toString().c_str() << endl;
    break;
  case WS_EVT_DISCONNECT:
    cout << "WebSocket client " << client->id() << "disconnected" << endl;
    break;
  case WS_EVT_DATA:
    handleWebSocketMessage(arg, data, len);
    break;
  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    break;
  }
}

String WebSockets::processor(const String &var)
{
  cout << var << endl;
  if (var == "STATE")
  {
    if (ledState)
    {
      return "ON";
    }
    else
    {
      return "OFF";
    }
  }
}

void WebSockets::loop()
{
  websocket.cleanupClients();
}

Json::Value WebUtils::parseJSON(string rawJson)
{
  // const std::string rawJson = R"({"Age": 20, "Name": "colin"})";
  const auto rawJsonLength = static_cast<int>(rawJson.length());
  JSONCPP_STRING err;
  Json::Value root;

  Json::CharReaderBuilder builder;
  const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
  if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root,
                     &err))
  {
    cout << "error" << endl;
    return EXIT_FAILURE;
  }
  return root;
}