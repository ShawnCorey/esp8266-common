#ifndef esp8266-common_h
#define esp8266-common_h

#include <WiFiManager.h>
#include <Arduino.h>
#include <ArduinoOTA.h>
#include <FS.h>

#define MQTT_ON_CMD         "ON"                             // command that sets relay on
#define MQTT_OFF_CMD        "OFF"                            // command that sets relay off
#define MQTT_RESET_CMD      "reset"                          // command that resets the device
#define MQTT_STAT_CMD       "stat"                           // command that forces a refresh of the MQTT status
#define MQTT_REGISTER_CMD   "register"                       // command that forces reregistration
#define MQTT_UNREGISTER_CMD "unregister"                     // command that forces unregistration
#define MQTT_FACTORY_RESET  "factory-reset"                  // command that clears the WiFiManager saved settings and reboots

// Change this to modify the SSID of the configuration portal AP
#ifndef CONFIG_AP_NAME
#define CONFIG_AP_NAME       "NewSonoff"
#endif
// Change this to modify the password for the configuration portal AP
#ifndef CONFIG_AP_PASS
#define CONFIG_AP_PASS       "password123"
#endif
// Change this to something like "LampSonoff" to display this name on your router
// Otherwise it will show up with the same name as the config portal AP SSID
#ifndef WIFI_HOST_NAME
#define WIFI_HOST_NAME       CONFIG_AP_NAME
#endif

class esp8266Common {
  public:
        bool OTAupdateInProgress = false;

        void prepWifiManager();
        void prepWifiManager(char* hostname);
        void prepWifiManager(char* hostname, char* apName);
        void prepWifiManager(char* hostname, char* apName, char* apPassword);
        void prepWifiManager(char* hostname, char* apName, char* apPassword, WiFiManagerParameter* params[], uint8_t paramCount);

        void setupOTA();
        void setupOTA(char* otaHostName);
        void setupOTA(char* otaHostName, char* otaPassword);
        void setupOTA(char* otaHostName, uint16_t otaPort);
        void setupOTA(char* otaHostName, char* otaPassword, uint16_t otaPort);

        void checkWiFi();
        void blinkLED(int pin, int duration, int n);
        void resetSettings();
};
#endif