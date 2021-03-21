#ifndef LED_H
#define LED_H

void init_led(void);
void ledBlue(uint8_t value);
void ledRed(uint8_t value);
void ledBluePWMInit();
void ledBluePWM(uint16_t value);

#endif