#include "device/CoverCalibratorHandler.h"

/*
Successful transaction 0x0 (0) N/A
Property or method not implemented 0x400 (1024) 0x80040400
Invalid value 0x401 (1025) 0x80040401
Value not set 0x402 (1026) 0x80040402
Not connected 0x407 (1031) 0x80040407
Invalid while parked 0x408 (1032) 0x80040408
Invalid while slaved 0x409 (1033) 0x80040409
Invalid operation 0x40B (1035) 0x8004040B
Action not implemented 0x40C (1036) 0x8004040C
*/

CoverCalibratorHandler::CoverCalibratorHandler(ESP8266WebServer *server)
{
    _server = server;
    coverCalibratorDevice = new CoverCalibratorDevice();
    serverTransactionID = 0;
}

void CoverCalibratorHandler::debugServerQuery()
{
    for (int i = 0; i < _server->args(); i++) {
        Log.traceln("%d" CR, i);
        Log.traceln("%s" CR, _server->argName(i));
        Log.traceln("%s" CR, _server->arg(i));
        Log.traceln("--------------------------");
    }
}

void CoverCalibratorHandler::incrementServerTransID()
{
    serverTransactionID++;
}

void CoverCalibratorHandler::returnEmpty(String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void CoverCalibratorHandler::returnBoolValue(bool val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void CoverCalibratorHandler::returnStringValue(String val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void CoverCalibratorHandler::returnIntValue(int val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void CoverCalibratorHandler::returnFloatValue(float val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void CoverCalibratorHandler::returnJsonArrayValue(JsonArray val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void CoverCalibratorHandler::returnDoubleValue(double val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}
/*
 * ALPACA DEVICE MANAGEMENT
 */

void CoverCalibratorHandler::handlerMgmtVersions()
{
    Log.traceln("handlerMgmtVersions called...");
    incrementServerTransID();

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        DynamicJsonDocument doc(1024);

        const size_t CAPACITY = JSON_ARRAY_SIZE(1);
        StaticJsonDocument<CAPACITY> devices;
        JsonArray array = devices.to<JsonArray>();
        array.add(1);
        // returnJsonArrayValue(array);
        
        doc["Value"] = array;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.traceln(F("Returning: %s" CR), output.c_str());
        // return output;
        _server->send(200, "text/json", output);
        // sendDeviceSetup( returnCode, message, err );
        
    }
}

void CoverCalibratorHandler::handlerMgmtDescription()
{
    Log.traceln("handlerMgmtDescription called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        incrementServerTransID();
        DynamicJsonDocument val(1024);

        val["ServerName"] = SERVER_NAME; //"TCN Mount Switch";
        val["Manufacturer"] = MANUFACTURER; // "Christian Kardach";
        val["ManufacturerVersion"] = MANUFACTURER_VERSION; //"1.0";
        val["Location"] = LOCATION; //"SE";

        const size_t CAPACITY = JSON_ARRAY_SIZE(5);
        StaticJsonDocument<CAPACITY> devices;
        JsonArray array = devices.to<JsonArray>();
        array.add(val);

        //returnJsonArrayValue(array);
        
        DynamicJsonDocument doc(1024);
        doc["Value"] = val;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.traceln(F("Returning: %s" CR), output.c_str());
        _server->send(200, "text/json", output);
        
    }
}

void CoverCalibratorHandler::handlerMgmtConfiguredDevices()
{
    Log.traceln("handlerMgmtConfiguredDevices called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        incrementServerTransID();
        DynamicJsonDocument val(1024);
        DynamicJsonDocument doc(1024);

        const size_t CAPACITY = JSON_ARRAY_SIZE(5);
        StaticJsonDocument<CAPACITY> devices;

        val["DeviceName"] = DEVICE_NAME; //"TCN Mount Switch";
        val["DeviceType"] = DEVICE_TYPE; //"Switch";
        val["DeviceNumber"] = DEVICE_NR; //0;
        val["UniqueID"] = UNIQUE_CLIENT_ID;
        JsonArray array = devices.to<JsonArray>();
        array.add(val);

        // returnJsonArrayValue(array);
        
        doc["Value"] = array;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.traceln(F("Returning: %s" CR), output.c_str());

        _server->send(200, "text/json", output);
        
    }
}

void CoverCalibratorHandler::handlerConnected()
{
    Log.traceln("handlerConnected called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        Log.traceln("handlerConnected GET called");

        String deviceType = _server->arg("device_type");
        //uint32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

        returnBoolValue(coverCalibratorDevice->connected, "", 0);
    }

    if (_server->method() == HTTP_PUT)
    {
        Log.traceln("handlerConnected POST called");

        // String _connected = _server->arg("Connected");
        coverCalibratorDevice->connected = (bool)_server->arg("Connected");
        // Log.traceln("%t", CR, coverCalibratorDevice->connected);

        returnEmpty("", 0);
    }
}

/***********************************
 * ASCOM STANDARD
 **********************************/
void CoverCalibratorHandler::handlerDescriptionGet()
{
    Log.traceln("handlerDescriptionGet called");
    returnStringValue(DESCRIPTION, "", 0);
}

void CoverCalibratorHandler::handlerDriverInfoGet()
{
    Log.traceln("handlerDriverInfoGet called");
    returnStringValue(DRIVER_INFO, "", 0);
}

void CoverCalibratorHandler::handlerDriverVersionGet()
{
    Log.traceln("handlerDriverVersionGet called");
    returnStringValue(DRIVER_VERSION, "", 0);
}

void CoverCalibratorHandler::handlerInterfaceVersionGet()
{
    Log.traceln("handlerInterfaceVersionGet called");
    returnIntValue(1, "", 0);
}

void CoverCalibratorHandler::handlerNameGet()
{
    Log.traceln("handlerNameGet called");
    returnStringValue(DEVICE_NAME, "", 0);
}

void CoverCalibratorHandler::handlerSupportedActionsGet()
{
    Log.traceln("handlerSupportedActionsGet called");

    DynamicJsonDocument val(1024);
    const size_t CAPACITY = JSON_ARRAY_SIZE(13);
    StaticJsonDocument<CAPACITY> devices;
    JsonArray array = devices.to<JsonArray>();
    
    array.add("action");
    array.add("commandblind");
    array.add("commandbool");
    array.add("commandstring");

    returnJsonArrayValue(array, "", 0);
    
}

void CoverCalibratorHandler::handleAction()
{
    Log.traceln("handleAction called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    //u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String action = _server->arg("Action");
    String parameters = _server->arg("Parameters");

    returnStringValue("ok", "", 0);
}

void CoverCalibratorHandler::handleCommandBlind()
{
    Log.traceln("handleCommandBlind called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.traceln("%s" CR, command);
    Log.traceln("%s" CR, raw);

    returnEmpty("", 0);
}

void CoverCalibratorHandler::handleCommandBool()
{
    Log.traceln("handleCommandBool called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.traceln("%s" CR, command);
    Log.traceln("%s" CR, raw);

    returnBoolValue(true, "", 0);
}

void CoverCalibratorHandler::handleCommandString()
{
    Log.traceln("handleCommandBool called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.traceln("%s" CR, command.c_str());
    Log.traceln("%s" CR, raw.c_str());

    returnStringValue("ok", "", 0);
}

/***********************************
 * ASCOM CoverCalibrator
 **********************************/
void CoverCalibratorHandler::handlerDriver0Brightness()
{
    Log.traceln("handlerDriver0Brightness called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnIntValue(coverCalibratorDevice->getBrightness(), "", 0);
}

void CoverCalibratorHandler::handlerDriver0CalibratorState()
{
    Log.traceln("handlerDriver0CalibratorState called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnIntValue(coverCalibratorDevice->calibrationState, "", 0);
}

void CoverCalibratorHandler::handlerDriver0CoverState()
{
    Log.traceln("handlerDriver0CalibratorState called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnIntValue(coverCalibratorDevice->coverState, "", 0);
}

void CoverCalibratorHandler::handlerDriver0MaxBrightness()
{
    Log.traceln("handlerDriver0MaxBrightness called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnIntValue(coverCalibratorDevice->maxBrightness, "", 0);
}

void CoverCalibratorHandler::handlerDriver0CalibratorOff()
{
    Log.traceln("handlerDriver0CalibratorOff called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_PUT)
    {
        coverCalibratorDevice->setCalibratonOff();
        returnEmpty("", 0);
    }
}

void CoverCalibratorHandler::handlerDriver0CalibratorOn()
{
    Log.traceln("handlerDriver0CalibratorOff called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_PUT)
    {
        //debugServerQuery();
        int brightness = _server->arg("Brightness").toInt();
        Log.traceln("brightness: %l" CR, brightness);

        if(brightness < 0)
        {
            returnEmpty("Wrong value", 1025);
        }
        else if(brightness > 255)
        {
            returnEmpty("Wrong value", 1025);
        }
        else {
            coverCalibratorDevice->setCalibratonOn(brightness);
            returnEmpty("", 0);
        }
        
    }
}

void CoverCalibratorHandler::handlerDriver0CloseCover()
{
    Log.traceln("handlerDriver0CloseCover called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_PUT)
    {
        coverCalibratorDevice->setCoverState(0);
        returnEmpty("", 1036);
    }
}

void CoverCalibratorHandler::handlerDriver0HaltCover()
{
    Log.traceln("handlerDriver0HaltCover called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_PUT)
    {
        coverCalibratorDevice->setCoverState(0);
        returnEmpty("", 1036);
    }
}

void CoverCalibratorHandler::handlerDriver0OpenCover()
{
    Log.traceln("handlerDriver0OpenCover called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_PUT)
    {
        coverCalibratorDevice->setCoverState(1);
        returnEmpty("", 1036);
    }
}
/*
void CoverCalibratorHandler::handlerDriver0CanWrite()
{
    Log.traceln("handlerDriver0CanWrite called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnBoolValue(true, "", 0);
}

void CoverCalibratorHandler::handlerDriver0SwitchDescription()
{
    Log.traceln("handlerDriver0SwitchDescription called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    switch (id)
    {
    case 0:
        returnStringValue(RELAY_0_DESC, "", 0);
        break;
    case 1:
        returnStringValue(RELAY_1_DESC, "", 0);
        break;
    case 2:
        returnStringValue(RELAY_2_DESC, "", 0);
        break;
    case 3:
        returnStringValue(RELAY_3_DESC, "", 0);
        break;
    case 4:
        returnStringValue(RELAY_4_DESC, "", 0);
        break;
    case 5:
        returnStringValue(RELAY_5_DESC, "", 0);
        break;
    case 6:
        returnStringValue(RELAY_6_DESC, "", 0);
        break;
    case 7:
        returnStringValue(RELAY_7_DESC, "", 0);
        break;
    default:
        returnStringValue("None", "", 0);
        break;
    }
    
}

void CoverCalibratorHandler::handlerDriver0SwitchState()
{
    Log.traceln("handlerDriver0SwitchState called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_GET)
    {
        Log.traceln("GET SwitchState called");

        returnBoolValue(coverCalibratorDevice->relayStateBool[id], "", 0);
    }
    else if (_server->method() == HTTP_PUT)
    {
        Log.traceln("PUT SwitchState called");
        bool val = (bool)_server->arg("State");

        coverCalibratorDevice->setRelayState(id, val);
        returnEmpty("", 0);
    }
}

void CoverCalibratorHandler::handlerDriver0SwitchName()
{
    Log.traceln("handlerDriver0SwitchName called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    switch (id)
    {
    case 0:
        returnStringValue(RELAY_0_NAME, "", 0);
        break;
    case 1:
        returnStringValue(RELAY_1_NAME, "", 0);
        break;
    case 2:
        returnStringValue(RELAY_2_NAME, "", 0);
        break;
    case 3:
        returnStringValue(RELAY_3_NAME, "", 0);
        break;
    case 4:
        returnStringValue(RELAY_4_NAME, "", 0);
        break;
    case 5:
        returnStringValue(RELAY_5_NAME, "", 0);
        break;
    case 6:
        returnStringValue(RELAY_6_NAME, "", 0);
        break;
    case 7:
        returnStringValue(RELAY_7_NAME, "", 0);
        break;
    
    default:
        break;
    }
    
}

void CoverCalibratorHandler::handlerDriver0SwitchValue()
{
    Log.traceln("handlerDriver0SwitchValue called");
    //debugServerQuery();

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_GET)
    {
        Log.traceln("GET SwitchValue called");
        returnDoubleValue(coverCalibratorDevice->relayStateValue[id], "", 0);
        
    }
    else if (_server->method() == HTTP_PUT)
    {
        Log.traceln("PUT SwitchValue called");
        double val = (double)_server->arg("Value").toDouble();
        
        coverCalibratorDevice->setRelayValue(id, val);
        returnEmpty("", 0);
    }


}

void CoverCalibratorHandler::handlerDriver0MinSwitchValue()
{
    Log.traceln("handlerDriver0MinSwitchValue called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnDoubleValue(0.0, "", 0);
}

void CoverCalibratorHandler::handlerDriver0MaxSwitchValue()
{
    Log.traceln("handlerDriver0MaxSwitchValue called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnDoubleValue(1.0, "", 0);
}

void CoverCalibratorHandler::handlerDriver0SwitchStep()
{
    Log.traceln("handlerDriver0SwitchStep called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    // u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnDoubleValue(1.0, "", 0);
}
*/