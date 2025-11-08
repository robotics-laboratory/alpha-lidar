#include <eXoCAN.h>

eXoCAN can;
#define bluePillLED PC13

int value = 5000;

int txMsgID = 0x1FF;
uint8_t txData[8]{(value >> 8) & 0xFF, value & 0xFF, 0, 0, 0, 0, 0, 0};
uint8_t txDataLen = 8;
uint32_t txDly = 5000;

int id, fltIdx;
uint8_t rxbytes[8];

void canISR() // get CAN bus frame passed by a filter into fifo0
{
    can.receive(id, fltIdx, rxbytes);  // empties fifo0 so that another another rx interrupt can take place
    // digitalToggle(bluePillLED);
}


void printFrame(uint8_t rxbytes[8]) {
    // Serial1.print("ID: 0x1FF Len: 8 Data: 0x");
    
    // for (int i = 0; i < 8; i++) {
    //     if (rxbytes[i] < 0x10) {
    //         Serial1.print("0");
    //     }
    //     Serial1.print(rxbytes[i], HEX);
    //     if (i < 7) {
    //         Serial1.print(" ");
    //     }
    // }

    Serial1.println();
    uint16_t angle = rxbytes[0] << 8 | rxbytes[1];
    // Serial.print(">a:");
    Serial1.print(angle, HEX);
    Serial1.print(" ");

    // Serial1.println();
    uint16_t speed = rxbytes[2] << 8 | rxbytes[3];
    // Serial.print(">s:");
    Serial1.print(speed, HEX);
    Serial1.print(" ");

    // Serial1.println();
    uint16_t torqe = rxbytes[4] << 8 | rxbytes[5];
    // Serial.print(">t:");
    Serial1.print(torqe, HEX);
    
}


void setup()
{   
    can.attachInterrupt(canISR);

    Serial1.begin(115200);
    can.begin(STD_ID_LEN, BR1M, PORTB_8_9_WIRE_PULLUP);
}

void loop(){
    delay(10);
    can.transmit(txMsgID, txData, txDataLen);

    // Serial1.println(id);
    // Serial1.println(fltIdx);
    printFrame(rxbytes);
}