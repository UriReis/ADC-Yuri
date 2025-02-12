#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "include/ssd1306.h"
#include "include/font.h"
#include "define.h"
#include "inicia.h"




int main()
{
    stdio_init_all();
    inicia();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
