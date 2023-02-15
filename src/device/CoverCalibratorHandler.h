#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ArduinoJson.h>
#include "device/CoverCalibratorDevice.h"
#include "configuration.hpp"

class CoverCalibratorHandler
{
    ESP8266WebServer* _server;

    public:
        CoverCalibratorHandler(ESP8266WebServer* server);
        
        void handlerMgmtVersions();
        void handlerMgmtDescription();
        void handlerMgmtConfiguredDevices();

        void handlerConnected();
        void handlerDescriptionGet();
        void handlerDriverInfoGet();
        void handlerDriverVersionGet();
        void handlerInterfaceVersionGet();
        void handlerNameGet();
        void handlerSupportedActionsGet();

        void handleAction();
        void handleCommandBlind();
        void handleCommandBool();
        void handleCommandString();

        void handlerDriver0Brightness();
        void handlerDriver0CalibratorState();
        void handlerDriver0CoverState();
        void handlerDriver0MaxBrightness();

        void handlerDriver0CalibratorOff();
        void handlerDriver0CalibratorOn();
        void handlerDriver0CloseCover();
        void handlerDriver0HaltCover();
        void handlerDriver0OpenCover();
   
    private:
        uint32_t transID;
        uint32_t clientID;
        uint32_t serverTransactionID = 0;
        String uniqueID = "4431281c-8560-4ad7-982f-5a6e507dda19";

        CoverCalibratorDevice* coverCalibratorDevice;

        void incrementServerTransID();

        void returnEmpty(String errMsg, int errNr);

        void returnStringValue(String val, String errMsg, int errNr);
        void returnBoolValue(bool val, String errMsg, int errNr);
        void returnIntValue(int val, String errMsg, int errNr);
        void returnFloatValue(float val, String errMsg, int errNr);
        void returnJsonArrayValue(JsonArray val, String errMsg, int errNr);
        void returnDoubleValue(double val, String errMsg, int errNr);

        void debugServerQuery();
        
};
