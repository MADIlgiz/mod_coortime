#include "Programm.hpp"
#include <unistd.h>
using namespace slp;
using namespace retk;
using namespace std;


Program::Program()
{
    version="0.0.1";
    do_disconnect = true;
    do_wait = true;
    p_vars.setName("mod_photo");
    //p_vars.add("local_addr",'l',"Local address").link(local_addr);
    //p_vars.add("remote_addr",'r',"Remote address").link(remote_addr);
    /// Маска 
    p_vars.add("rules",'u',"Rules in form key1:mask1 key2:mask2 ...").link(rules);
    /// Отладка
    p_vars.add("debug",'g',"Debug (0 - off, 1 - on)").link(debug);
    /// Режим работы
    p_vars.add("mode",'m',"Work mode (0 - gpsd, 1 - ttyAML1").link(WorkMode);
    /// Имя устройства в каталоге /dev
    p_vars.add("devname",'n',"Device name tty...").link(devname);
    /// Скорость обмена данными с портом
    p_vars.add("ttyspeed",'s',"Speed of tty...").link(speed);
    /// Режим сохранения или не сохранения
    p_vars.add("savemode",'p',"Module save date or not").link(SaveMode);
    /// Директория в которую будут сохраняться данные
    p_vars.add("savedir",'x',"Save dir for data").link(SaveDir);
    time_now = 0;


    ///Reporter
    debug = false;
    setReporterName("MOD_COORTIME");
    setReporterTTYColor(Terminal::Colors::Cyan);
    ///p_vars.add("sender",'s',"Sender subsystem id (SLP_SUBSYSTEMS), dec").link(sender);
    conf.push_back(&p_vars);
    confPacketLayer(conf);
};

void Program::init(){
    /// вывод аргументов приложения
    if (debug)
    {
        report('i',"Init Parameters:");
        //report('i',"Local address: %s",local_addr.c_str());
        //report('i',"Remote address: %s",remote_addr.c_str());
        report('i',"DBC rules: %s",rules.c_str());
        report('i',"Debug: %d", debug);
        report('i',"Sender subsystem: %u", sender);
        report('i',"GPS module work mode: %d",WorkMode);
        
    }
    msg_outcome.sender = (SLP_SUBSYSTEMS)sender;

}

void Program::cycle(){
    uint8_t layer = PacketMultiLayer::layerUnix;
    //uint8_t layer2 = PacketMultiLayer::layerSerial;
    Poller poll;
    
    //uint8_t layer2 = PacketMultiLayer::layerIP;
    initPacketLayer(layer,poll);
    client.setPacketLayer(pl);
    client.setRules(rules);
    client.connect();
    if(WorkMode == 0){
    /// GPSD

    GpsDevice = new GpsdGPS;
    GpsDevice->DebugMode = debug;
    }
    else if(WorkMode == 1){
        /// ttyAML ubx parse

        GpsDevice = new UartGPS;
        GpsDevice->uartname = devname;
        GpsDevice->InitDevice();
        poll.add(*GpsDevice->getIOHandler());
        GpsDevice->DebugMode = debug;
        //initPacketLayer(layer2,poll);
    }
    

    
        //GpsDevice = new GpsdGPS;
    
    
    vector<float> COORDINATES(7);
    /// Отправка статуса: Запущен, еще  нет связи с датчиком
    Status = slp::SLP_SUBSYSTEM_STATUS::SDSS_INIT;
    sendStatus();
    ///Создаем объект для управления ШИМ
   
    /// Отправить сообщение о текущем статусе, есть подключение к ШИМ
    
    while(is_running && do_wait)
    {

       // usleep(100000);
       // time_now = rtime_now();
        if(poll.wait(10)){
            if(client.hasMessage()){ 
                cout << "Client has nessage" << endl;
                client.recvMessage(&msg_income);
                proceedMsg(msg_income,msg_outcome,&has_answer);
            }
        }
        GpsDevice->GetData(COORDINATES);
        ///Отправка координат 
        if(COORDINATES[0] > 0){
            uint64_t rtime = rtime_now();
            msg_outcome.setParams(SLPS_NONE,SLPS_GPST,MSGR_DATAS,SLPD_COORDINATES_GPS);
            bool res;
            res = SLP_DataFormatter::pack(msg_outcome, COORDINATES, rtime);
            if(debug == 1){
            msg_outcome.print();
            }
            if(res){
                client.sendMessage(&msg_outcome);
            }
            for(int i = 0; i < COORDINATES.size(); i++){
                COORDINATES[i] = 0;
            }
       }
        //PWM_Controle();
    }
    if(do_disconnect) { 
        client.disconnect();
        cout << "Disconnect" << endl;
    }
    delete GpsDevice;
    shutdownPacketLayer();

}


int Program::run(){
    init();
    cycle();
    return 0;
}

void Program::proceedMsg(slp::SLP_Message &min, slp::SLP_Message &mout, bool *has_answer_l){
   
    *has_answer_l = false;

    try{/// обработка сообщений controle
        if(min.code == MSGR_CTRL){
            proceedMsgCTRL(min,mout,has_answer_l);
        }
    }catch(...){

    }

}

void Program::proceedMsgCTRL(slp::SLP_Message & min, slp::SLP_Message & mout, bool * has_answer_l)
{
    switch(min.obj_id) {
        case slp::SLPC_SUBS_SHUTTERS:
            report("SHUTTERRECIEVED\n");
            /// Установка флага о получении сообщения на начало измерения
            ShutterFlag = 1;
            /// Завожу таймер и включаю ШИМ на 50 мс
            /// При первом получении меняем статус на Запущен, есть связь с датчиком, инициализирован SDSS_CONNECT
            
            break;
        case slp::SLPC_SUBS_STATE:


            sendStatus();
            /// Отправка текущего статуса
            break;
        case slp::SLPC_SUBS_OFF:

            /// Отключить ШИМ
            break;
        case slp::SLPC_SUBS_ON:
            /// Не знаю пока что делать с ШИМ при команде на включение
            break;
        
        default:

            break;

    }
}
int Program::sendStatus(){
    
    bool res = false;
    //msg_outcome.sender = sender;
    msg_outcome.receiver = SLP_SUBSYSTEMS::SLPS_NONE;
    msg_outcome.code = MSGA_CTRL;
    msg_outcome.obj_id = SLP_CTRL::SLPC_SUBS_STATE;
    uint32_t Datasize = 1;
    //msg_outcome.setData(&Status,Datasize);   
    uint64_t statusRtime = rtime_now();
    res = slp::SLP_DataFormatter::pack(msg_outcome,&Status,Datasize,statusRtime);
    if(res == true){
        client.sendMessage(&msg_outcome);
    }
    return res;
}

