#ifndef MOTOR_H
#define MOTOR_H

void rollMotorPinsRegister();

void rollMotorA(uint8_t value);
void rollMotorB(uint8_t value);
void rollMotorC(uint8_t value);

void rollMotorAPWM(uint16_t value);
void rollMotorBPWM(uint16_t value);
void rollMotorCPWM(uint16_t value);

void rollMotorPinAP(uint16_t value);
void rollMotorPinBP(uint16_t value);
void rollMotorPinCP(uint16_t value);

#endif