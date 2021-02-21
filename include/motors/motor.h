#ifndef MOTOR_H
#define MOTOR_H

void init_motors();
void init_timer_motors();
void motorHandler();

void setMotor1Value(float, int);

void motor1Step();
void motor2Step();
void motor3Step();

#endif