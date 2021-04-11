#ifndef TX_H
#define TX_H

typedef struct
{
    char *lineOne;
    char *lineTwo;
} menu, menuPtr;

typedef struct
{
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
    uint8_t thrust;
} Packet;

typedef void (*atCb)(menu lines);

class Tx
{
private:
    // pins
    static const uint8_t thrustPin = A0;
    static const uint8_t yawPin = A1;
    static const uint8_t rollPin = A2;
    static const uint8_t pitchPin = A3;
    static const uint8_t searchPin = 9;
    static const uint8_t radioNumber = 1;
    static const uint8_t botRadioNumber = 0;
    static const uint8_t packetSize = sizeof(Packet);
    uint16_t thrust;
    int16_t roll;
    int16_t pitch;
    int16_t yaw;
    menu atCommand(char *cmd);
    void scan(atCb cb);
    void initRc();
    uint8_t failures;

public:
    void prepare();
    void sendPacket();
    void start(void (*func)());
    menu hummingbirdConnect();
    bool isConnected();
    RF24 radio = RF24(10, 8);
    Packet packet;
};

#endif