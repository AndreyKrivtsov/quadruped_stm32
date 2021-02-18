#ifndef LED_H
#define LED_H

void ledRegister(void);
void ledBlue(uint8_t value);
void ledRed(uint8_t value);
void ledBluePWMInit();
void ledBluePWM(uint16_t value);

#endif