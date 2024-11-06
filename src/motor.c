#include "motor.h"

#include <stdio.h>

#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include "pins.h"

uint enb1_slice;
uint enb2_slice;

void motor_init() {
  gpio_init(L1);
  gpio_init(L2);
  gpio_init(L3);
  gpio_init(L4);
  gpio_init(ENA);
  gpio_init(ENB);

  gpio_set_dir(L1, GPIO_OUT);
  gpio_set_dir(L2, GPIO_OUT);
  gpio_set_dir(L3, GPIO_OUT);
  gpio_set_dir(L4, GPIO_OUT);

  gpio_set_function(ENA, GPIO_FUNC_PWM);
  gpio_set_function(ENB, GPIO_FUNC_PWM);

  enb1_slice = pwm_gpio_to_slice_num(ENA);
  enb2_slice = pwm_gpio_to_slice_num(ENB);

  pwm_set_wrap(enb1_slice, 255);
  pwm_set_wrap(enb2_slice, 255);

  pwm_set_enabled(enb1_slice, true);
  pwm_set_enabled(enb2_slice, true);
}

void run_motor_one(int pwm) {
  if (pwm < 0) {
    pwm = -1 * pwm;
    gpio_put(L1, 0);
    gpio_put(L2, 1);
  } else {
    gpio_put(L1, 1);
    gpio_put(L2, 0);
  }

  pwm_set_chan_level(enb1_slice, ENA, pwm);
}

void set_speed(int pwmr, int pwml) {
  pwm_set_chan_level(enb1_slice, ENA, pwmr);
  pwm_set_chan_level(enb2_slice, ENB, pwml);
}
void run_motor_two(int pwm) {
  if (pwm < 0) {
    pwm = -1 * pwm;

    gpio_put(L3, 1);
    gpio_put(L4, 0);

  } else {
    gpio_put(L3, 0);
    gpio_put(L4, 1);
  }

  pwm_set_chan_level(enb2_slice, ENB, pwm);
}

void run_motor(int pwmr, int pwml, int p) {
  run_motor_one(pwmr);
  run_motor_two(pwml);
  // printf("enb1_slice %d\n", enb1_slice);
  // printf("enb2_slice %d\n", enb2_slice);
}