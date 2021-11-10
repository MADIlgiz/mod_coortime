#pragma once
#include "basegps.hpp"
#include "retk2/io/Terminal.hpp"
#include "retk2/io/SerialPort.hpp"
#include "retk2/io/Poller.hpp"
#include "retk2/core/Application.hpp"
#include "retk2/core/StringUtils.hpp"
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <cstring>
#include <cstdio>
#include <string>
#include <algorithm>

#define BUFFER_SIZE 4096

class UartGPS: public BaseGPS {
    public:
    uint8_t Preamble[4] = {0xB5,0x62,0x01,0x07};
    uint8_t Header[5] = {0};
    uint8_t buf[BUFFER_SIZE] = {0};
    uint8_t GPSMSGBUFFER[BUFFER_SIZE];
    int num_bytes =0;
    retk::SerialPort dev;  
    UartGPS();
    ~UartGPS();
    /// структура хранящая время
    struct UTCtime{
        uint16_t year;
        uint8_t months;
        uint8_t day;
        uint8_t hour;
        uint8_t min;
        uint8_t sec;
    }LocalTime;

    float UTCtime = 0;
    float Longitude = 0;
    float Latitude = 0;
    float Altitude = 0;
    retk::IOHandler* getIOHandler(){return &dev;};
    void handle(uint32_t event_mask);
    bool message_resived = false;
    int GetData(std::vector<float> & UsefulData);
    int GetTime();
    int InitDevice();
    void GetIOhandler(){};
};