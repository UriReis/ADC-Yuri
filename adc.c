#include <stdio.h>         
#include <stdlib.h>        
#include "pico/stdlib.h"   // Biblioteca do Raspberry Pi Pico para funções básicas
#include "hardware/adc.h"  // Biblioteca para controle do ADC (Conversor Analógico-Digital)
#include "hardware/i2c.h"  // Biblioteca para comunicação via I2C
#include "include/ssd1306.h" 
#include "include/font.h"  // Biblioteca de fontes para o display
#include "define.h"        // Arquivo de definições 
#include "inicia.h"        // Arquivo de inicialização dos periféricos
#include "hardware/pwm.h"  // Biblioteca para controle de PWM 
#include "ledjoy.h"        // Arquivo com funções para controle dos LEDs com o joystick
#include "display.h"       // Arquivo com funções para controle do display a partir do joystick


int main()
{
    stdio_init_all(); 

    inicia();  // Chama a função de inicialização geral do sistema (configuração de GPIOs, ADC, etc.)
    inipwm();  // Configura e inicializa o PWM para controle dos LEDs
    inii2();   // Inicializa a comunicação I2C para o display OLED

    // Configura a interrupção para o botão A (Botao_A)
    gpio_set_irq_enabled_with_callback(Botao_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    
    while (true) {
        ledjoy();         // Atualiza o estado dos LEDs com base na posição do joystick
        quadradodisplay(); // Atualiza o display com a posição do quadrado controlado pelo joystick
        
        sleep_ms(10); // Pequeno atraso para evitar uso excessivo da CPU
    }
}
