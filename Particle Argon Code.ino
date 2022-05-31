// This #include statement was automatically added by the Particle IDE.
#include <BH1750Lib.h>

// This #include statement was automatically added by the Particle IDE.
#include <Grove_Temperature_And_Humidity_Sensor.h>

BH1750Lib lightmeter;
DHT dht(D2);

//Output Pin that is connected to the solarnoid to power pump
int output = D5;


//autostart varibles
bool running = false;
bool autoStartEnabled = false;
int autoTemp = 59;
int autoMoist = 999;
int autoLux = 99999;
int autoDuration = 719;
bool autoStartStarted = false;

//enviromental varibles
float temprature;
float moisture;
float lux;
String tempratureString;
String moistureString;
String luxString;

int currentMinute;
int currentHour;
int currentWeekDay;



//timetable varibles
String monStart = "01:00";
String monFinish = "02:00";
String tueStart = "03:00";
String tueFinish = "04:00";
String wedStart = "05:00";
String wedFinish = "06:00";
String thuStart = "07:00";
String thuFinish = "08:00";
String friStart = "09:00";
String friFinish = "10:00";
String satStart = "11:00";
String satFinish = "12:00";
String sunStart = "13:00";
String sunFinish = "14:00";


void setup() {
    Time.zone(+10);
    
    pinMode(output, OUTPUT);
    lightmeter.begin(BH1750LIB_MODE_CONTINUOUSHIGHRES);
    dht.begin();
    
    //enviromental varibles explosed to cloud    
    Particle.variable("temprature",tempratureString);
    Particle.variable("moisture",moistureString);
    Particle.variable("lux",luxString);
    
    //autostart varibles explosed to cloud   
    Particle.variable("running",running);
    Particle.variable("autoStartEnabled",autoStartEnabled);
    Particle.variable("autoTemp",autoTemp);    
    Particle.variable("autoMoist",autoMoist);
    Particle.variable("autoLux",autoLux);
    Particle.variable("autoDuration",autoDuration);
    
    //timetable explosed to cloud   
    
    Particle.variable("monStart",monStart);
    Particle.variable("monFinish",monFinish);
    Particle.variable("tueStart",tueStart);
    Particle.variable("tueFinish",tueFinish);
    Particle.variable("wedStart",wedStart);
    Particle.variable("wedFinish",wedFinish);
    Particle.variable("thuStart",thuStart);
    Particle.variable("thuFinish",thuFinish);
    Particle.variable("friStart",friStart);
    Particle.variable("friFinish",friFinish);
    Particle.variable("satStart",satStart);
    Particle.variable("satFinish",satFinish);
    Particle.variable("sunStart",sunStart);
    Particle.variable("sunFinish",sunFinish);
    Particle.variable("Day",currentWeekDay);
    Particle.variable("Hour",currentHour);
    Particle.variable("Minute",currentMinute);
    
    //Particle functions exposed to cloud
    
    Particle.function("UpdateTimes",UpdateTimes);
    
    Particle.function("UpdateAutoStartEnabled",UpdateAutoStartEnabled);
    Particle.function("UpdateAutoTemp",UpdateAutoTemp);
    Particle.function("UpdateAutoMoist",UpdateAutoMoist);
    Particle.function("UpdateAutoLux",UpdateAutoLux);
    Particle.function("UpdateAutoDuration",UpdateAutoDuration);
    
}

int UpdateAutoStartEnabled(String Command){
    if(Command == "true"){
        autoStartEnabled = true;
        return 1;
    }
    if(Command == "false"){
        autoStartEnabled = true;
        return 1;
    }
    else{return -1;}
}

int UpdateAutoTemp(String Command){
    autoTemp = Command.toInt();
    return 1;
}

int UpdateAutoMoist(String Command){
    autoMoist = Command.toInt();
    return 1;
}

int UpdateAutoLux(String Command){
    autoLux = Command.toInt();
    return 1;
}

int UpdateAutoDuration(String Command){
    autoDuration = Command.toInt();
    return 1;
}

int UpdateTimes(String Command){
    String day ="mon";
    String onOrOff = "0";
    String Time = "00:00";
    bool Start = true;
    //accepts format day:Start/finish:Time
    //Eg Mon111:30 or Tue022:24
    //Extract day

    day = Command.substring(0,3);
    onOrOff = Command.substring(3,4);
    Time = Command.substring(4,9);

    if(onOrOff == "1"){
         Start = true;
    }
    else{
        Start = false;
    }

    if(day == "mon"){
        if(Start){
            monStart = Time;
            return 1;
        }
        if(!Start){
            monFinish = Time;
            return 1;
        }
        return -1;
    }
        if(day == "tue"){
        if(Start){
            tueStart = Time;
            return 1;
        }
        if(!Start){
            tueFinish = Time;
            return 1;
        }
        return -1;
    }
        if(day == "wed"){
        if(Start){
            wedStart = Time;
            return 1;
        }
        if(!Start){
            wedFinish = Time;
            return 1;
        }
        return -1;
    }
        if(day == "thu"){
        if(Start){
            thuStart = Time;
            return 1;
        }
        if(!Start){
            thuFinish = Time;
            return 1;
        }
        return -1;
    }
        if(day == "fri"){
        if(Start){
            friStart = Time;
            return 1;
        }
        if(!Start){
            friFinish = Time;
            return 1;
        }
        return -1;
    }
        if(day == "sat"){
        if(Start){
            satStart = Time;
            return 1;
        }
        if(!Start){
            satFinish = Time;
            return 1;
        }
        return -1;
    }
            if(day == "sun"){
        if(Start){
            sunStart = Time;
            return 1;
        }
        if(!Start){
            sunFinish = Time;
            return 1;
        }
        return -1;
    }
    //Return Failure
    return -1;
}

void loop() {
    currentMinute = Time.minute();
    currentHour = Time.hour();
    currentWeekDay = Time.weekday();
    
    

        if(currentWeekDay == 2){
            int startHour = monStart.substring(0,2).toInt();
            int StartMinute = monStart.substring(3,5).toInt();
            if(startHour == currentHour and StartMinute == currentMinute){
                running = true;
            }
        }
        if(currentWeekDay == 3){
            int startHour = tueStart.substring(0,2).toInt();
            int StartMinute = tueStart.substring(3,5).toInt();
            if(startHour == currentHour and StartMinute == currentMinute){
                running = true;
            }
        }
        if(currentWeekDay == 4){
            int startHour = wedStart.substring(0,2).toInt();
            int StartMinute = wedStart.substring(3,5).toInt();
            if(startHour == currentHour and StartMinute == currentMinute){
                running = true;
            }
        }
        if(currentWeekDay == 5){
            int startHour = thuStart.substring(0,2).toInt();
            int StartMinute = thuStart.substring(3,5).toInt();
            if(startHour == currentHour and StartMinute == currentMinute){
                running = true;
            }
        }
        if(currentWeekDay == 6){
            int startHour = friStart.substring(0,2).toInt();
            int StartMinute =friStart.substring(3,5).toInt();
            if(startHour == currentHour and StartMinute == currentMinute){
                running = true;
            }
        }
        if(currentWeekDay == 7){
            int startHour = satStart.substring(0,2).toInt();
            int StartMinute = satStart.substring(3,5).toInt();
            if(startHour == currentHour and StartMinute == currentMinute){
                running = true;
            }
        }
        if(currentWeekDay == 0){
            int startHour = sunStart.substring(0,2).toInt();
            int StartMinute = sunStart.substring(3,5).toInt();
            if(startHour == currentHour and StartMinute == currentMinute){
                running = true;
            }
        }
    

        if(currentWeekDay == 2){
            int startHour = monFinish.substring(0,2).toInt();
            int StartMinute = monFinish.substring(3,5).toInt();
            if(startHour == currentHour and StartMinute == currentMinute){
                running = false;
            }
        }
        if(currentWeekDay == 3){
            int startHour = tueFinish.substring(0,2).toInt();
            int StartMinute = tueFinish.substring(3,5).toInt();
            if(startHour == currentHour and StartMinute == currentMinute){
                running = false;
            }
        }
        if(currentWeekDay == 4){
            int startHour = wedFinish.substring(0,2).toInt();
            int StartMinute = wedFinish.substring(3,5).toInt();
            if(startHour == currentHour and StartMinute == currentMinute){
                running = false;
            }
        }
        if(currentWeekDay == 5){
            int startHour = thuFinish.substring(0,2).toInt();
            int StartMinute = thuFinish.substring(3,5).toInt();
            if(startHour == currentHour and StartMinute == currentMinute){
                running = false;
            }
        }
        if(currentWeekDay == 6){
            int startHour = friFinish.substring(0,2).toInt();
            int StartMinute = friFinish.substring(3,5).toInt();
            if(startHour == currentHour and StartMinute == currentMinute){
                running = false;
            }
        }
        if(currentWeekDay == 7){
            int startHour = satFinish.substring(0,2).toInt();
            int StartMinute = satFinish.substring(3,5).toInt();
            if(startHour == currentHour and StartMinute == currentMinute){
                running = false;
            }
        }
        if(currentWeekDay == 0){
            int startHour = sunFinish.substring(0,2).toInt();
            int StartMinute = sunFinish.substring(3,5).toInt();
            if(startHour == currentHour and StartMinute == currentMinute){
                running = false;
            }
        }
    
    temprature = dht.getTempCelcius();
    moisture = analogRead(A0);
    lux = lightmeter.lightLevel();
    
    if(autoStartEnabled){
        //reduce contdown
        if (autoDuration < 1) {
            running = false;
            autoStartEnabled = false;
        }
    }
    
    if(running == false){
        if(lux > autoLux){
            running = true;
            autoStartEnabled = true;
        }
        if(temprature > autoTemp){
            running = true;
            autoStartEnabled = true;
        }
        if(moisture > autoMoist){
            running = true;
            autoStartEnabled = true;
        }
        if(lux > autoLux){
            running = true;
            autoStartEnabled = true;
        }
    }
    
    
    tempratureString = "";
    tempratureString.concat((int)temprature);
    moistureString = "";
    moistureString.concat((int)moisture);
    luxString = "";
    luxString.concat((int)lux);
    
    if(running){
            
        digitalWrite(output, HIGH);
    }
    else{
        digitalWrite(output, LOW);
    }
    delay(5000);
}
