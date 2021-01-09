#include <network_utils.h>
#include <WiFi.h>
#include <iostream>

using namespace std;

const char *hotspotSSID = "RovMower";
const char *hotspotPWD = "FutureCrew486";

const char *wifiSSID = "tplink";
const char *wifiPWD = "tplink";

const char *ftp_user = "esp32";
const char *ftp_password = "esp32";

void AP_setup()
{
    // Connect to Wi-Fi network with SSID and password
    Serial.print("Setting AP (Access Point)…");
    // Remove the password parameter, if you want the AP (Access Point) to be open
    WiFi.softAP(hotspotSSID, hotspotPWD);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
}

void STA_Setup()
{
    WiFi.begin(wifiSSID, wifiPWD);
    cout << "Connecting to " << wifiSSID << " network" << endl;

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    cout << endl
         << "Connected to " << wifiSSID << endl;
    cout << "IP address: " << WiFi.localIP() << endl;
}