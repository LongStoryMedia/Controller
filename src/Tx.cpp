#include "config.h"
// #include "printf.h"

#if defined RC
uint8_t address[][6] = {"bird", "nest"};
#endif

void Tx::prepare()
{
    packet.thrust = constrain(map(analogRead(thrustPin), JOYSTICK_RANGE_LOW, JOYSTICK_RANGE_HIGH, 100, 0), 0, 100);
    packet.roll = constrain(map(analogRead(rollPin), JOYSTICK_RANGE_LOW, JOYSTICK_RANGE_HIGH, 50, -50), -50, 50);
    packet.pitch = constrain(map(analogRead(pitchPin), JOYSTICK_RANGE_LOW, JOYSTICK_RANGE_HIGH, -50, 50), -50, 50);
    packet.yaw = constrain(map(analogRead(yawPin), JOYSTICK_RANGE_LOW, JOYSTICK_RANGE_HIGH, -50, 50), -50, 50);
    packet.thrust = packet.thrust < 5 ? 0 : packet.thrust;
    packet.roll = packet.roll > -5 && packet.roll < 5 ? 0 : packet.roll;
    packet.pitch = packet.pitch > -5 && packet.pitch < 5 ? 0 : packet.pitch;
    packet.yaw = packet.yaw > -5 && packet.yaw < 5 ? 0 : packet.yaw;
#if DEBUG
    Serial.print("adjusted: \t");
    Serial.print(packet.yaw);
    Serial.print("\t");
    Serial.print(packet.pitch);
    Serial.print("\t");
    Serial.print(packet.roll);
    Serial.print("\t");
    Serial.print(packet.thrust);
    Serial.print("\t actual: \t");
    Serial.print(analogRead(yawPin));
    Serial.print("\t");
    Serial.print(analogRead(pitchPin));
    Serial.print("\t");
    Serial.print(analogRead(rollPin));
    Serial.print("\t");
    Serial.println(analogRead(thrustPin));
#endif
}

void Tx::scan(atCb cb)
{
    cb(atCommand("AT+SHOW?"));
    delay(2000);
    cb(atCommand("AT+DESC?"));
    delay(2000);
}

menu Tx::hummingbirdConnect()
{
    // scan(cb);
    // cb(atCommand("AT+START"));
    // cb(atCommand("AT"));
    // delay(1000);
    // A434F1A1CC5B
    // cb(atCommand("at+con882583F32582")); // cn41a/at-09
    // return atCommand("AT+CONA4DA32550629"); // hm-19
    // cb(atCommand("at+conE003CD881508")); // nanoble33
    // menu connectMenu;
    // char lineOne[] = "select comm protocol:";
    // char lineTwo[] = "ble     rc";
    // connectMenu.lineOne = lineOne;
    // connectMenu.lineTwo = lineTwo;
}

void Tx::start(void (*func)())
{
    // scan(cb);
    // cb(atCommand("AT+NOTI1"));
    // delay(2000);
    // cb(atCommand("AT+PIO11"));
    // delay(1500);
    // cb(atCommand("AT+IMME1"));
    // delay(1500);
    // cb(atCommand("AT+ROLE1"));
    // delay(1500);
    // cb(atCommand("AT+MODE2"));
    // delay(1500);

    // pinMode(searchPin, INPUT_PULLUP);
    // attachInterrupt(searchPin, func, FALLING);
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
    // Serial1.print(_cmd);
    uint32_t t = millis();
    while (t > millis() - 3500)
    {
        // if (Serial1.available() > 0)
        // {
        //     Serial1.readBytesUntil('\n', atLine, sizeof(atLine));
        //     lines.lineTwo = atLine;
        // }
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
        delay(1000);
        radio.flush_tx();
        radio.powerUp();
        radio.flush_tx();
        initRc();
    }
}
