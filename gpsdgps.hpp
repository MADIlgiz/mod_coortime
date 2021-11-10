#pragma once
#include "basegps.hpp"

class GpsdGPS: public BaseGPS{
    
    /// Структура 
    ///struct gps_data_t gps_data;
    int RetVal = 0;
    public:
    struct gps_data_t gps_data;
    GpsdGPS();
    int GetData(std::vector<float> & UsefulData);
    int GetTime();
    int InitDevice();
    float Getlatitude();
    void GetIOhandler();
    retk::IOHandler* getIOHandler(){};
    ~GpsdGPS();
};