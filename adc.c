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
#include "display.h"




int main()
{
    stdio_init_all();
    inicia();

    inipwm();

    inii2();

    

    while (true) {
      
        ledjoy();
        quadradodisplay();
        
        sleep_ms(50);
    }
}
