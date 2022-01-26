#ifndef MAX485_h
#define MAX485_h

#include <Arduino.h>

class MAX485
{
    public:
        MAX485(
            HardwareSerial& hwSerial,
            uint8_t         transmissionEnablePin,
            uint32_t        baudrate,
            SerialConfig    config,
            uint16_t        predelay,
            uint16_t        postdelay
        );
        void begin();
        void end();
        int available();
        int peek();
        int read();
        void flush();
        size_t write(uint8_t b);

        void beginTransmission();
        void endTransmission();
        void setReceiverMode();
        void setTransmitterMode();

    private:
        HardwareSerial& serial;

        const uint8_t  transmissionEnablePin;

        const uint16_t predelay;
        const uint16_t postdelay;

        const uint32_t     serialBaudrate;
        const SerialConfig serialConfig;

        bool     transmissionActive = false;

};

#endif