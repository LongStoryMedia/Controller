#include "config.h"
// #include "printf.h"

#if defined RC
uint8_t address[][6] = {"bird", "nest"};
#endif

void Tx::prepare()
{
    packet.thrust = constrain(map(analogRead(thrustPin), 0, 3600, 1000, 0), 0, 1000);
    packet.roll = constrain(map(analogRead(rollPin), 100, 3700, -500, 500), -500, 500);
    packet.pitch = constrain(map(analogRead(pitchPin), 100, 3550, 500, -500), -500, 500);
    packet.yaw = constrain(map(analogRead(yawPin), 100, 3700, -500, 500), -500, 500);
    packet.thrust = packet.thrust < 25 ? 0 : packet.thrust;
    packet.roll = packet.roll > -25 && packet.roll < 25 ? 0 : packet.roll;
    packet.pitch = packet.pitch > -25 && packet.pitch < 25 ? 0 : packet.pitch;
    packet.yaw = packet.yaw > -25 && packet.yaw < 25 ? 0 : packet.yaw;
}

void Tx::scan(atCb cb)
{
    cb(atCommand("AT+SHOW?"));
    delay(2000);
    cb(atCommand("AT+DESC?"));
    delay(2000);
}

void Tx::start()
{
    initRc();
}

bool Tx::isConnected()
{
    return digitalRead(10) == HIGH;
}

menu Tx::atCommand(char *cmd)
{
    menu lines;
    lines.lineOne = cmd;
    char atLine[16] = {0};
    char _cmd[20];
    strcpy(_cmd, cmd);
    strcat(_cmd, "\r\n");
    uint32_t t = millis();
    while (t > millis() - 3500)
    {
        if (Serial1.available() > 0)
        {
            Serial1.readBytesUntil('\n', atLine, sizeof(atLine));
            lines.lineTwo = atLine;
        }
    }
    return lines;
}

void Tx::initRc()
{
    // initialize the transceiver on the SPI bus
    radio.begin();

    radio.setPALevel(RF24_PA_LOW); // RF24_PA_MAX is default.

    // save on transmission time by setting the radio to only transmit the
    // number of bytes we need to transmit
    radio.setPayloadSize(packetSize); // default value is the maximum 32 bytes

    // set the TX address of the RX node into the TX pipe
    radio.openWritingPipe(address[radioNumber]); // always uses pipe 0

    // set the RX address of the TX node into a RX pipe
    // radio.openReadingPipe(botRadioNumber, address[botRadioNumber]); // using pipe 1

    radio.stopListening(); // put radio in TX mode

    radio.enableDynamicAck();
    radio.setAutoAck(true);

    failures = 0;

    // For debugging info
    // printf_begin();             // needed only once for printing details
    // radio.printDetails();       // (smaller) function that prints raw register values
    // radio.printPrettyDetails(); // (larger) function that prints human readable data
}

void Tx::sendPacket()
{
    radio.flush_tx();

    if (!radio.write(&packet, packetSize))
    {
        failures++;
        radio.reUseTX();
    }
    else
    {
        failures = 0;
    }

    if (failures >= 10)
    {
        Serial.println(F("Too many failures detected. Restarting."));
        radio.powerDown();
        radio.flush_tx();
        radio.powerUp();
        radio.flush_tx();
        initRc();
    }
}
