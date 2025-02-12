#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "include/ssd1306.h"
#include "include/font.h"
#include "define.h"
#include "inicia.h"
#include "hardware/pwm.h"
#include "ledjoy.h"




int main()
{
    stdio_init_all();
    inicia();

    inipwm();

    while (true) {
      
        ledjoy();
        sleep_ms(1000);
    }
}
