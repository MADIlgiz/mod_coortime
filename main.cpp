#include <iostream>
#include "gpsdgps.hpp"
#include <unistd.h>
#include "Programm.hpp"

using namespace std;
using namespace slp;
using namespace retk;
int LOOFlag = 0;

void LoopFunction(struct gps_data_t *gpsdata);

void signalHandler( int signum ) {
   cout << "Interrupt signal (" << signum << ") received.\n";

   // cleanup and close up stuff here  
   // terminate program  

   exit(0);  
}

int main(int argc, char* argv[]) {
        Program app;

  setlinebuf(stdout);
  try {
    if (app.setup(argc,argv)) return 0;
    return app.run();
  }
  catch (exception& ex) {
    cerr << "Error: " << ex.what() << endl;
    return -1;
  }




   /* GpsdGPS GPS;
    GPS.GetTime();
    //gps_mainloop(&GPS.gps_data,100000,&LoopFunction);
    int flag = 0;
    signal(SIGTERM,signalHandler);
    bool is_running = 1;
   // gps_mainloop(&GPS.gps_data,5000000,&LoopFunction);
    while(1){
        usleep(100000);
        
        //gps_mainloop(&GPS.gps_data,10000,&LoopFunction);

        //gps_mainloop(&GPS.gps_data,1000,&LoopFunction);
        //cout << "in while" << endl;
       if(gps_waiting(&GPS.gps_data,100000)){
        if(gps_read(&GPS.gps_data,NULL,0)){
       // LOOFlag = 1;
        cout << "GPS mode = " << GPS.gps_data.fix.mode << endl;  
        cout << "GPS mode = " << GPS.gps_data.fix.mode << endl;  
        cout << "Longitude = " << GPS.gps_data.fix.longitude <<
        " Latitude = " << GPS.gps_data.fix.latitude <<
        " Altitude = " << GPS.gps_data.fix.altitude << 
        " Speed = " << GPS.gps_data.fix.speed << endl;
       
            gps_clear_fix(&GPS.gps_data.fix);
          
        
            }
        }
    }
   /* while(is_running){
        cout << "in While" << endl;
        //gps_mainloop(&GPS.gps_data,10000,&LoopFunction);
    
        /*if(LOOFlag == 1){
            cout << "GPS mode = " << GPS.gps_data.fix.mode << endl;
            //flag = 1;
            LOOFlag = 0;
        }*/
        
    //}
    //cout << GPS.Getlatitude();
    //cout << "Hello, world!\n";
}


void LoopFunction(struct gps_data_t *gpsdata){
   // if(gps_waiting(gpsdata,10)){
    //cout << "in main loop" << endl;
    //usleep(10);
    if(gps_read(gpsdata,NULL,0)){
       // gps_clear_fix(&gpsdata->fix);
       // LOOFlag = 1;
        cout << "GPS mode = " << gpsdata->fix.mode << endl;  
        cout << "Longitude = " << gpsdata->fix.longitude <<
        " Latitude = " << gpsdata->fix.latitude <<
        " Altitude = " << gpsdata->fix.altitude << 
        " Speed = " << gpsdata->fix.speed << endl;
        gps_clear_fix(&gpsdata->fix);
       
        }
        usleep(1000);
    //}
}
