#include "uartgps.hpp"
#include <string>
#include <cstring>
#include <iomanip>
using namespace std;
using namespace retk;

UartGPS::UartGPS(){

}

UartGPS::~UartGPS(){
    dev.close();
}

int UartGPS::GetData(std::vector<float> & UsefulData){
    
    //cout << n << endl;
    //string GPSstr(&GPSMSGBUFFER[0]);
   // cout << GPSstr << endl;
   // cout << GPSstr.size() << endl;
    //GetMsgType(GPSstr);
    //GPSmsgtypeparser(GPSstr);
    int n = 0;
    n = dev.readMatch(Header, 5, Preamble[0]);
    if((Header[2] == 1) && (Header[3] == 7)){
        n = dev.readMatch(buf,Header[4],0);
    }
    dev.flush();

    if(Header[3] == 7){
        if(DebugMode == 1){
        cout << "MSG header" << endl;
        for(int i = 0; i < 5; i++){
          if(i<4){
          printf("%X " , Header[i]);
          }
          else{
            printf("%d",Header[i]);
          }
        }
        cout << endl;
        for(int i = 0; i < Header[4]; i++){

          printf("%X ",buf[i]);
          
          }
        }
           uint16_t year;
        //memcpy(&GPSTime,&buf[],sizeof(uint32_t));
        uint16_t months;
        uint8_t day;
        
        //memcpy(&year,&buf[5],sizeof(uint16_t));
        //memcpy(&months,&buf[7],sizeof(uint16_t));
        
        memcpy(&LocalTime,&buf[5],7);
        int32_t longitude = 0;
        memcpy(&longitude,&buf[25],sizeof(int32_t));
        int32_t latitude = 0;
        memcpy(&latitude,&buf[29],sizeof(int32_t));
        int32_t height;
        memcpy(&height, &buf[33],sizeof(int32_t));
        int32_t speed;
        memcpy(&speed, &buf[61],sizeof(int32_t));
        if(DebugMode == 1){
        cout << endl;
        cout << "UTC time == " << LocalTime.year << "/" << int(LocalTime.months);
        
        //cout << "months == " << int(LocalTime.months) << endl;
        cout << "/" << int(LocalTime.day) << " ";
        cout << int(LocalTime.hour) << ":" << int(LocalTime.min) << ":" << int(LocalTime.sec) << endl;
        cout << "Latitude = " << std::setprecision(9) << float(latitude)/10000000 << endl;
        cout << "longitude = " << std::setprecision(9) << float(longitude)/10000000 << endl;
        cout << "Height = " << std::setprecision(9) << float(height)/1000 << endl;
        cout << "Speed = " << std::setprecision(9) << float(speed)/1000 << endl;
        }
        UsefulData[0] = float(latitude)/10000000;
        UsefulData[1] = float(longitude)/10000000;
        UsefulData[2] = float(height)/1000;
        UsefulData[6] = float(speed)/1000;
        for(int i = 3; i < UsefulData.size();i++){
            UsefulData[i] = 0;
        }
    }
    
    
    
    //dev.close();
}

int UartGPS::GetTime(){

}

int UartGPS::InitDevice(){
    dev.port_rate = 57600;
    dev.port_bits = 8;
    dev.port_fctrl = retk::SerialPort::FlowControl::fctrlNone;
    dev.port_parity = retk::SerialPort::Parity::parityNone;
    dev.port_stopbits = 1;
    dev.open(uartname.c_str());
}
void UartGPS::handle(uint32_t event_mask){
    if(event_mask & EPOLLIN){
        
        message_resived = true;

    }
}

