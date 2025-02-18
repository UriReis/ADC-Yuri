#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "define.h"
#include "inicia.h"
#include "hardware/pwm.h"


// Configura o pino como saída PWM e ativa o módulo PWM
uint pwm_init_gpio(uint gpio, uint wrap) {
    gpio_set_function(gpio, GPIO_FUNC_PWM); // Configura o pino como PWM
    uint slice_num = pwm_gpio_to_slice_num(gpio); // Obtém o slice PWM do pino
    pwm_set_wrap(slice_num, wrap); // Define o valor máximo do contador PWM
    pwm_set_enabled(slice_num, true);  // Ativa o PWM
    return slice_num;  
}

// Inicializa o PWM para os LEDs Azul e Vermelho
void inipwm(){
    uint pwm_wrap = 4096; // Define o valor máximo do PWM (12 bits)
    pwm_init_gpio(pinB, pwm_wrap); // Configura PWM para o LED Azul
    pwm_init_gpio(pinR, pwm_wrap); // Configura PWM para o LED Vermelho
}


bool estadoLeds = true; // Estado inicial dos LEDs (ligados)

// Interrupção do botão A para alternar o estado dos LEDs
void gpio_irq_handler(uint gpio, uint32_t events)
{
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    static volatile uint32_t last_timeA = 0; // Armazena o tempo do último evento

    if (gpio == Botao_A) // Verifica se o botão A foi pressionado
    {
        if (current_time - last_timeA > 200000) // Debouncing de 200ms
        {
            last_timeA = current_time;

            estadoLeds = !estadoLeds; // Alterna entre ligado e desligado

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

// Controla os LEDs de acordo com a posição do joystick
void ledjoy()
{
    adc_select_input(0);
    uint16_t vrx_value = adc_read(); // Leitura do eixo X do joystick

    adc_select_input(1);
    uint16_t vry_value = adc_read(); // Leitura do eixo Y do joystick

    if (estadoLeds) // Apenas ajusta o brilho dos LEDs se estiverem ligados
    {
        uint16_t pwm_level_azul = abs(vry_value - 1892) * 2;
        if (pwm_level_azul <= 500)
        {
            pwm_set_gpio_level(pinR, 0); // Evita brilho fraco e mantém apagado
        }
        else
        {
            pwm_set_gpio_level(pinR, pwm_level_azul);
        }

        uint16_t pwm_level_vermelho = abs(vrx_value - 1876) * 2;
        if (pwm_level_vermelho <= 500)
        {
            pwm_set_gpio_level(pinB, 0);
        }
        else
        {
            pwm_set_gpio_level(pinB, pwm_level_vermelho);
        }
    }
}
