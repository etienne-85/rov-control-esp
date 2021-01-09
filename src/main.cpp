#include <string>
#include <iostream>
#include <network_utils.h>
#include <webservices.h>
#include <filesys.h>
#include <drv_bts7960.h>
#include <json.h>

using namespace std;

// WEB
WebServer *websrv;
WebSockets *websck;

// MOTORS
bts7960drv *motorL;
bts7960drv *motorR;

int MAX_TEST_SPEED = 192;

void jsonSplit(string s)
{
  // std::string s = "scott>=tiger>=mushroom";
  std::string delimiter = ">=";

  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delimiter)) != std::string::npos)
  {
    token = s.substr(0, pos);
    std::cout << token << std::endl;
    s.erase(0, pos + delimiter.length());
  }
  std::cout << s << std::endl;
}

/**
 * Speed json sample:
 * ({"left": 0, "right": 0}) 
 */
int processMotorsRequest()
{
  // Json::Value jsonRoot = WebUtils::parseJSON(WebSockets::socketData);
  // // const std::string name = root["Name"].asString();
  // const int speedR = jsonRoot["Right"].asInt();
  // const int speedL = jsonRoot["Left"].asInt();

  // std::cout << speedR << std::endl;
  // std::cout << speedL << std::endl;

  // return speedR;
  string jsonData = WebSockets::socketData;

  size_t pos = 0;
  string token;

  pos = jsonData.find(",");
  token = jsonData.substr(0, pos);
  String speedL(token.c_str());
  String speedR = jsonData.erase(0, pos + 1).c_str();

  pos = string(speedL.c_str()).find(":");
  speedL = speedL.substring(pos + 1, speedL.length());
  // cout << speedL.toInt() << endl;
  motorL->instantSpeed(speedL.toInt());

  pos = string(speedR.c_str()).find(":");
  speedR = speedR.substring(pos + 1, speedR.length() - 1);
  // cout << speedR.toInt() << endl;
  motorR->instantSpeed(-speedR.toInt());
  return 0;
}

void setup()
{
  Serial.begin(115200);

  // AP & STA
  AP_setup();
  // STA_setup();

  // OTA updates
  OTA_setup();

  // websrv_setup();
  websrv = new WebServer();
  websck = new WebSockets();
  WebServer::server.addHandler(&websck->websocket);

  motorL = new bts7960drv(16, 17, 0, 1);
  motorR = new bts7960drv(26, 27, 2, 3);

  // motorL->test(MAX_TEST_SPEED);
  // motorR->test(MAX_TEST_SPEED);
}

void loop()
{
  processMotorsRequest();
  websck->loop();
  OTA_loop();
  // sleep(1);
}