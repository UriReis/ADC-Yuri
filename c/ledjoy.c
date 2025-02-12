#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "define.h"
#include "inicia.h"
#include "hardware/pwm.h"
uint32_t last_print_time = 0;

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

void ledjoy(){

    // Lê os valores do joystick
    adc_select_input(0);  
    uint16_t vrx_value = adc_read(); // Lê o eixo X (0 a 4095)
    
    adc_select_input(1);
    uint16_t vry_value = adc_read(); // Lê o eixo Y (0 a 4095)

    // Ajusta o duty cycle do LED Azul (Eixo Y)
    uint16_t pwm_level_azul = abs(vry_value - 2048) * 2; // Quanto mais longe do centro, mais brilho
    pwm_set_gpio_level(pinB, pwm_level_azul);

    // Ajusta o duty cycle do LED Vermelho (Eixo X)
    uint16_t pwm_level_vermelho = abs(vrx_value - 2048) * 2;
    pwm_set_gpio_level(pinR, pwm_level_vermelho);

    // Calcula o duty cycle em porcentagem para depuração
    float duty_cycle_azul = (pwm_level_azul / 4095.0) * 100;
    float duty_cycle_vermelho = (pwm_level_vermelho / 4095.0) * 100;

    // Exibir valores no terminal a cada 1 segundo
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    if (current_time - last_print_time >= 1000) {
        printf("VRX: %u | VRY: %u\n", vrx_value, vry_value);
        printf("Duty Cycle LED Azul: %.2f%% | Duty Cycle LED Vermelho: %.2f%%\n", duty_cycle_azul, duty_cycle_vermelho);
        last_print_time = current_time;
    }

}