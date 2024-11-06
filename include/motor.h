#ifndef _MOTOR_H_
#define _MOTOR_H_

void motor_init();
void run_motor_one(int pwm);
void run_motor_two(int pwm);
void run_motor(int pwmr,int pwml,int p);
void set_speed(int,int);
#endif