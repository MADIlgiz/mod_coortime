#pragma once
#include <vector>
#include <gps.h>
#include "retk2/io/SerialPort.hpp"

class BaseGPS {
    /// Широта
    float Longitude;
    /// Долгота
    float Altitude;
    float Latitude;
    float Angle1;
    float Angle2;
    float Angle3;
    float Speed;

    public:
    int DebugMode = 0;
    enum GPSSTATES{
        DISABLED,
        ENABLED,
    };
    std::string uartname = "";
    GPSSTATES GpsState = DISABLED;
    virtual retk::IOHandler* getIOHandler() = 0;
    virtual int GetData(std::vector<float> & UsefulData) = 0;
    virtual int GetTime() = 0;
    virtual int InitDevice() = 0;
    virtual void GetIOhandler() = 0;
    virtual ~BaseGPS(){};
};