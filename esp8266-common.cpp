#include "esp8266-common.h"

void esp8266Common::prepWifiManager(){
    prepWifiManager(WIFI_HOST_NAME, CONFIG_AP_NAME, CONFIG_AP_PASS, NULL, 0);
}

void esp8266Common::prepWifiManager(char* hostname){
    prepWifiManager(hostname, CONFIG_AP_NAME, CONFIG_AP_PASS, NULL, 0);
}

void esp8266Common::prepWifiManager(char* hostname, char* apName){
    prepWifiManager(hostname, apName, CONFIG_AP_PASS, NULL, 0);
}

void esp8266Common::prepWifiManager(char* hostname, char* apName, char* apPass){
    prepWifiManager(hostname, apName, apPass, NULL, 0);
}

void esp8266Common::prepWifiManager(char* hostname, char* apName, char* apPassword, WiFiManagerParameter* params[], uint8_t paramCount){
    WiFiManager wifiManager;

    if(paramCount > 0){
        for(int i = 0; i < paramCount; i++){
            wifiManager.addParameter(params[i]);
        }
    }

    wifiManager.setConfigPortalTimeout(CONFIG_AP_TIMEOUT);
    WiFi.hostname(hostname);
    if(!wifiManager.autoConnect(apName, apPassword)){
        Serial.println("Failed to connect and hit timeout");
        delay(3000);
        ESP.reset();
        delay(5000);
    }
}


void esp8266Common::setupOTA(){
    setupOTA(NULL, NULL, 8266);
}
void esp8266Common::setupOTA(char* otaHostName){
    setupOTA(otaHostName, NULL, 8266);
}
void esp8266Common::setupOTA(char* otaHostName, char* otaPassword){
    setupOTA(otaHostName, otaPassword, 8266);
}
void esp8266Common::setupOTA(char* otaHostName, uint16_t otaPort){
    setupOTA(otaHostName, NULL, otaPort);
}
void esp8266Common::setupOTA(char* otaHostName, char* otaPassword, uint16_t otaPort){
    this->OTAupdateInProgress = false;
    if(otaHostName != NULL)
        ArduinoOTA.setHostname(otaHostName);
    if(otaPassword != NULL)
        ArduinoOTA.setPassword(otaPassword);
    ArduinoOTA.setPort(otaPort);

    ArduinoOTA.onStart([this]() {
        this->OTAupdateInProgress = true;
        Serial.println("OTA Update Initiated");
    });
    ArduinoOTA.onEnd([this]() {
        Serial.println("\nOTA Update Ended");
        this->OTAupdateInProgress = false;
        ESP.restart();
        delay(5000);
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([this](ota_error_t error) {
        this->OTAupdateInProgress = false;
        Serial.printf("OTA Error [%u]: ", error);
        switch(error){
            case OTA_AUTH_ERROR: Serial.println("Auth Failed"); break;
            case OTA_BEGIN_ERROR: Serial.println("Begin Failed"); break;
            case OTA_CONNECT_ERROR: Serial.println("Connect Failed"); break;
            case OTA_RECEIVE_ERROR: Serial.println("Receive Failed"); break;
            case OTA_END_ERROR: Serial.println("End Failed"); break;
            default: Serial.println("Unknown Error"); break;
        }
    });
    ArduinoOTA.begin();
}

void esp8266Common::checkWiFi(){
    if (WiFi.status() != WL_CONNECTED){
        Serial.println("WiFi connection LOST");
        ESP.restart();
        delay(5000);
    }
}

void esp8266Common::blinkLED(int pin, int duration, int n) {
    for(int i=0; i<n; i++)  {
        digitalWrite(pin, HIGH);
        delay(duration);
        digitalWrite(pin, LOW);
        delay(duration);
    }
}

void esp8266Common::resetSettings(){
    WiFiManager wifiManager;

    SPIFFS.format();
    wifiManager.resetSettings();
    ESP.restart();
    delay(5000);
}