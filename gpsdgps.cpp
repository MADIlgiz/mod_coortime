#include "gpsdgps.hpp"
#include <iostream>
#include  <math.h>
#include <iomanip> 
using namespace std;

GpsdGPS::GpsdGPS(){
    if(0 != gps_open("localhost","2947",&gps_data))
    {
        cout << "Open error" << endl;
        
    }else{
        cout << "GPS open OK" << endl;
        RetVal = gps_stream(&gps_data,WATCH_ENABLE | WATCH_JSON, NULL);
        GpsState = ENABLED;
    }
    
    
}

GpsdGPS::~GpsdGPS(){
    cout << "GPS closed" << endl;
    gps_close(&gps_data);
}

int GpsdGPS::GetData(std::vector<float> & UsefulData){
    //cout << "in getdata" << endl;
    if(gps_waiting(&gps_data,10000)){
       // cout << "wait good" << endl;
        if(gps_read(&gps_data,NULL,0)){
          //  cout << "READ good" << endl;
            if(gps_data.fix.mode == MODE_NO_FIX){
                for(int i = 0; i < UsefulData.size(); i++){
                    UsefulData[i] = 0;
                }
                if(DebugMode == 1){
                cout << "MODE NO FIX" << endl;
                }
                return 0;
            }
            else if(gps_data.fix.mode == MODE_2D){
                UsefulData[0] = gps_data.fix.latitude;
                UsefulData[1] = gps_data.fix.longitude;
                UsefulData[2] = 0;
                UsefulData[6] = gps_data.fix.speed;
                for(int i = 3; i < UsefulData.size() - 1; i++){
                    UsefulData[i] = 0;
                }
                if(DebugMode == 1){
                cout << "MODE_2D" << endl;
                }
            }
            else if(gps_data.fix.mode == MODE_3D){
                UsefulData[0] = gps_data.fix.latitude;
                UsefulData[1] = gps_data.fix.longitude;
                UsefulData[2] = gps_data.fix.altitude;
                UsefulData[6] = gps_data.fix.speed;
                for(int i = 3; i < UsefulData.size() - 1; i++){
                    UsefulData[i] = 0;
                }
                if(DebugMode == 1){
                cout << "MODE_3D" << endl;
                }
            }
            else if(gps_data.fix.mode == MODE_NOT_SEEN){
                for(int i = 0; i < UsefulData.size(); i++){
                    UsefulData[i] = -1;
                }
                cout << "MODE NOT SEEN" << endl;
                return 1;
            }
            if(DebugMode == 1){
            //timespec_get(&gps_data.fix.time,TIME_UTC);
            char buff[100];
            strftime(buff, sizeof(buff), "%D %T", gmtime(&gps_data.fix.time.tv_sec));
            cout << "UTC time == " << buff << endl;
            
            //cout << "UTC time nsec == " << gps_data.fix.time.tv_nsec << endl;
            cout << std::setprecision(9) << "longitude === " << gps_data.fix.longitude << endl;
            cout << std::setprecision(9) << "latitude === " << gps_data.fix.latitude << endl;
            cout << std::setprecision(9) << "altitude === " << gps_data.fix.altitude << endl;
            cout << std::setprecision(9) << "speed === " << UsefulData[6] << endl;
            }
            gps_clear_fix(&gps_data.fix);
        }
        return 0;
    }
}
int GpsdGPS::GetTime(){
cout << "hello" << endl;

}

int GpsdGPS::InitDevice(){

}

float GpsdGPS::Getlatitude(){
    if(isfinite(gps_data.fix.latitude)){
    return gps_data.fix.latitude;
    }else{
        return 0;
    }
}

void GpsdGPS::GetIOhandler(){

}