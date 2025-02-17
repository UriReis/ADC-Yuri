#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "define.h"
#include "inicia.h"
#include "hardware/pwm.h"


uint pwm_init_gpio(uint gpio, uint wrap) {
    gpio_set_function(gpio, GPIO_FUNC_PWM); // Configura o pino como PWM
    uint slice_num = pwm_gpio_to_slice_num(gpio); // Obtém o slice PWM do pino
    pwm_set_wrap(slice_num, wrap); // Define o valor de wrap (limite do contador PWM)
    pwm_set_enabled(slice_num, true);  // Ativa o PWM
    return slice_num;  
}

void inipwm(){
    uint pwm_wrap = 4096; // Define o valor máximo do PWM (12 bits)
    
    // Inicializa PWM para os LEDs
    uint pwm_slice_azul = pwm_init_gpio(pinB, pwm_wrap);
    uint pwm_slice_vermelho = pwm_init_gpio(pinR, pwm_wrap);

    
}



bool estadoLeds = true; // Estado inicial: LEDs ligados

void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    static volatile uint32_t last_timeA = 0; // Armazena o tempo do último evento (em microssegundos)

    // Verifica se foi o botão A que foi pressionado
    if (gpio == Botao_A)
    {
        if (current_time - last_timeA > 200000) // Debouncing de 200ms
        {
            last_timeA = current_time;

            // Alterna o estado dos LEDs (toggle)
            estadoLeds = !estadoLeds;

            if (estadoLeds)
            {
                printf("Leds on\n");
            }
            else
            {
                printf("LEDs off\n");
                pwm_set_gpio_level(pinB, 0); // Desliga LED Azul
                pwm_set_gpio_level(pinR, 0); // Desliga LED Vermelho
            }
        }
    }
}

void ledjoy()
{
    // Lê os valores do joystick
    adc_select_input(0);
    uint16_t vrx_value = adc_read(); // Lê o eixo X (0 a 4095)

    adc_select_input(1);
    uint16_t vry_value = adc_read(); // Lê o eixo Y (0 a 4095)

    if (estadoLeds) // Somente atualiza os LEDs se estiverem ativados pelo botão A
    {
        uint16_t pwm_level_azul = abs(vry_value - 1892) * 2;
        if (pwm_level_azul >= 0 && pwm_level_azul <= 500)
        {
            pwm_set_gpio_level(pinB, 0);
        }
        else
        {
            pwm_set_gpio_level(pinB, pwm_level_azul);
        }

        uint16_t pwm_level_vermelho = abs(vrx_value - 1876) * 2;
        if (pwm_level_vermelho >= 0 && pwm_level_vermelho <= 500)
        {
            pwm_set_gpio_level(pinR, 0);
        }
        else
        {
            pwm_set_gpio_level(pinR, pwm_level_vermelho);
        }
    }
}




