#include <filesys.h>
#include <Arduino.h>
// #include "LittleFS.h"
#include <SPIFFS.h>
// #include <ESP8266FtpServer.h>

// FtpServer ftpSrv;
// #include <SPIFFS.h>

// void fstest()
// {
//     if (!LittleFS.begin())
//     {
//         Serial.println("An Error has occurred while mounting LittleFS");
//         return;
//     }

//     File file = LittleFS.open("/test.txt", "r");
//     if (!file)
//     {
//         Serial.println("Failed to open file for reading");
//         return;
//     }

//     Serial.println("File Content:");
//     while (file.available())
//     {
//         Serial.write(file.read());
//     }
//     file.close();
// }



// void SpiffsFtpSetup()
// {
//     Serial.println(F("Inizializing FS..."));
//     // FTP Setup, ensure SPIFFS is started before try to use ftp methods
//     if (SPIFFS.begin(true))
//     {
//         Serial.println("SPIFFS opened!");
//         ftpSrv.begin(ftp_user, ftp_password); //username, password for ftp
//     }
// }
// void SpiffsFtpLoop(void)
// {
//     ftpSrv.handleFTP();
// }