#pragma once
#include <HardwareSerial.h>
class OutputHelper
{
private:
        static OutputHelper *instance;
        unsigned long _lastMS;
        unsigned long timer;
        String convert()
        {
                unsigned long hours = timer / 3600000;
                unsigned long minutes = (timer % 3600000) / 60000;
                unsigned long seconds = (timer % 60000) / 1000;
                unsigned long ms = timer % 1000;
                String formattedTime = String(hours) + ":" +
                                       (minutes < 10 ? "0" : "") + String(minutes) + ":" +
                                       (seconds < 10 ? "0" : "") + String(seconds) + "." +
                                       (ms < 10 ? "00" : (ms < 100 ? "0" : "")) + String(ms);

                return formattedTime;
        }
        OutputHelper()
        {
                Serial.begin(115200);
                Serial.println("OutputHelper intialized!");
                timer = 0;
                _lastMS = millis();
        }

public:
        OutputHelper(const OutputHelper &) = delete;
        OutputHelper &operator=(const OutputHelper &) = delete;
        static OutputHelper *getInstance()
        {
                if (instance == nullptr)
                        instance = new OutputHelper();
                return instance;
        }
        void updateCounter()
        {
                timer = millis() - _lastMS;
        }
        template <typename T>
        void sendMSG(T x)
        {
                Serial.println(convert() + " : " + String(x));
        }
};