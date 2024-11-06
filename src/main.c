#include <stdio.h>
#include <stdlib.h>

#include "hardware/pwm.h"
#include "motor.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pins.h"

// #include "qtr_sensor.h"
#define LED_DELAY_MS 1000

int main() {
  uint16_t sensorValue;
  stdio_init_all();
  motor_init();

  gpio_init_mask(0x7C);
  // setup_default_uart();
  printf("Hello, world!\n");

  gpio_init(PICO_DEFAULT_LED_PIN);
  gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

  gpio_set_dir_in_masked(0x7C);

  puts("Hello, world!");
  // performCalibration(false);
  while (true) {
    gpio_put(PICO_DEFAULT_LED_PIN, true);
    // run_motor(150, 150, 0);
    // sleep_ms(LED_DELAY_MS);

    int d1 = gpio_get(D1);
    int d2 = gpio_get(D2);
    int d3 = gpio_get(D3);
    int d4 = gpio_get(D4);
    int d5 = gpio_get(D5);

    int dt = gpio_get_all();

    int bin = (dt & 0x7C) >> 2;

    // switch (bin) {
    //   case 0x11011:
    //     printf("F ");
    //     gpio_put(L1, 1);
    //     gpio_put(L2, 0);
    //     gpio_put(L3, 0);
    //     gpio_put(L4, 1);
    //     set_speed(150, 150);
    //     break;

    //   case 0x11111:
    //     printf("S");
    //     gpio_put(L1, 0);
    //     gpio_put(L2, 0);
    //     gpio_put(L3, 0);
    //     gpio_put(L4, 0);
    //     set_speed(0, 0);
    //     break;

    //   default:
    //     break;
    // }
    printf("%d %d %d %d %d\n", d1, d2, d3, d4, d5);

    // if only middle sensor detects black line
    if ((d1 == 1) && (d2 == 1) && (d3 == 0) && (d4 == 1) && (d5 == 1)) {
      // going forward with full speed
      printf("F ");
      gpio_put(L1, 1);
      gpio_put(L2, 0);
      gpio_put(L3, 0);
      gpio_put(L4, 1);
      set_speed(150, 150);
    }
    if ((d1 == 0) && (d2 == 0) && (d3 == 1) && (d4 == 0) && (d5 == 0)) {
      // going forward with full speed
      printf("F ");
      gpio_put(L1, 1);
      gpio_put(L2, 0);
      gpio_put(L3, 0);
      gpio_put(L4, 1);
      set_speed(150, 150);
    }

    // if only left sensor detects black line
    if ((d1 == 1) && (d2 == 1) && (d3 == 1) && (d4 == 0) && (d5 == 1)) {
      // going right with full speed
      printf("SR ");
      gpio_put(L1, 0);
      gpio_put(L2, 0);
      gpio_put(L3, 0);
      gpio_put(L4, 1);
      set_speed(150, 150);
    }
    if ((d1 == 1) && (d2 == 1) && (d3 == 1) && (d4 == 1) && (d5 == 0)) {
      // going right with full speed
      printf("SSR ");
      gpio_put(L1, 0);
      gpio_put(L2, 0);
      gpio_put(L3, 0);
      gpio_put(L4, 1);
      set_speed(0, 250);
    }

    if ((d1 == 1) && (d2 == 0) && (d3 == 1) && (d4 == 1) && (d5 == 1)) {
      // going right with full speed
      printf("SL ");
      gpio_put(L1, 0);
      gpio_put(L2, 0);
      gpio_put(L3, 1);
      gpio_put(L4, 0);
      set_speed(60, 150);
    }

    if ((d1 == 0) && (d2 == 1) && (d3 == 1) && (d4 == 1) && (d5 == 1)) {
      // going right with full speed
      printf("SSL ");
      gpio_put(L1, 0);
      gpio_put(L2, 0);
      gpio_put(L3, 1);
      gpio_put(L4, 0);
      set_speed(100, 150);
    }

    // // if all sensors are on a black line
    if ((d1 == 1) && (d2 == 1) && (d3 == 1) && (d4 == 1) && (d5 == 1)) {
      // // stop
      // printf("S");

      // gpio_put(L1, 0);
      // gpio_put(L2, 0);
      // gpio_put(L3, 0);
      // gpio_put(L4, 0);
      // set_speed(0, 0);
            printf("F ");
      gpio_put(L1, 1);
      gpio_put(L2, 0);
      gpio_put(L3, 0);
      gpio_put(L4, 1);
      set_speed(150, 150);
    // }
    }

    if ((d1 == 0) && (d2 == 0) && (d3 == 0) && (d4 == 0) && (d5 == 0)) {
      // stop
      printf("S");

      gpio_put(L1, 0);
      gpio_put(L2, 0);
      gpio_put(L3, 0);
      gpio_put(L4, 0);
      set_speed(0, 0);
    }
    // run_motor(-150, -150, 0);
    gpio_put(PICO_DEFAULT_LED_PIN, false);
    // sleep_ms(LED_DELAY_MS);
  }
  return 0;
}
