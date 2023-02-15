#include "device/CoverCalibratorDevice.h"

CoverCalibratorDevice::CoverCalibratorDevice()
{
    pinMode(LIGHT_PIN_1, OUTPUT);
    pinMode(LIGHT_PIN_2, OUTPUT);
}

int CoverCalibratorDevice::getBrightness()
{
    return _brightness;
}
void CoverCalibratorDevice::setCalibratonOn(int brightness)
{
    analogWrite(LIGHT_PIN_1, brightness);
    analogWrite(LIGHT_PIN_2, brightness);
    _brightness = brightness;
    calibrationState = 3;
}

void CoverCalibratorDevice::setCalibratonOff()
{
    analogWrite(LIGHT_PIN_1, 0);
    analogWrite(LIGHT_PIN_2, 0);
    _brightness = 0;
    calibrationState = 1;
}

void CoverCalibratorDevice::setCoverState(int state)
{
    coverState = state;
}