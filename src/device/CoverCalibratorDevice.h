#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include "configuration.hpp"

class CoverCalibratorDevice
{


    public:
        CoverCalibratorDevice();

        bool connected = false;
        String uniqueID = "";

        int maxBrightness = 255;
        int calibrationState = 1;
        int coverState = 0;
        
        int getBrightness();
        void setCalibratonOn(int brightness);
        void setCalibratonOff();
        void setCoverState(int state);
        /*
        enum CalibratorState {
            NotPresent,
            Off,
            NotReady,
            Ready,
            Unknown,
            Error
        };

        enum CoverStatus {
            NotPresent,
            Closed,
            Moving,
            Open,
            Unknown,
            Error
        };
        */

    private:
        int _brightness;
        //void writeRelayData(int relay, int boolValue, double doubleValue);
        //byte relayData = B00000000;
};
