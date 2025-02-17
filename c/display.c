#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "include/ssd1306.h"
#include "include/font.h"
#include "define.h"

ssd1306_t ssd; // Estrutura para controlar o display OLED

void inii2()
{
    i2c_init(I2C_PORT, 400 * 1000); // Inicializa o I2C com frequência de 400 kHz

    // Configura os pinos SDA e SCL para função I2C com pull-up
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicializa o display SSD1306
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);

    ssd1306_fill(&ssd, false); // Limpa o display
    ssd1306_send_data(&ssd);
}

bool estado_pb = false; // Estado do botão do joystick (toggle entre modos)

void quadradodisplay()
{
    // Leitura do joystick nos eixos X e Y
    adc_select_input(0);
    uint16_t vrx_value = adc_read();
    adc_select_input(1);
    uint16_t vry_value = adc_read();

    // Converte os valores do joystick para coordenadas no display
    int pos_x = 60 + ((vry_value - 2048) * 60) / 2048;
    int pos_y = 28 - ((vrx_value - 2048) * 28) / 2048;

    // Limita os valores para manter o quadrado dentro da tela
    if (pos_x < 8) pos_x = 8;
    if (pos_x > 112) pos_x = 112;
    if (pos_y < 8) pos_y = 8;
    if (pos_y > 48) pos_y = 48;

    // Detecta mudança de estado do botão (pressionado e liberado)
    static bool botao_ultimo_estado = false;
    bool botao_atual = !gpio_get(JOYSTICK_PB); // Botão é PULL-UP (0 quando pressionado)

    if (botao_atual && !botao_ultimo_estado) // Detecta apenas a transição de solto -> pressionado
    {
        estado_pb = !estado_pb; // Alterna o estado do push-button
        printf("Botão pressionado! Novo estado: %d\n", estado_pb);
    }
    botao_ultimo_estado = botao_atual; // Atualiza o estado anterior do botão

    // Atualiza o display
    ssd1306_fill(&ssd, false); 
    ssd1306_rect(&ssd, 3, 3, 122, 58, true, false); // Desenha a borda

    if (estado_pb)  // Se o botão foi pressionado, ativa modo alternativo
    {
        gpio_put(pinG, true); // Acende LED Verde

        // Calcula nova posição para o quadrado alternativo
        int pos_xPB = 59 + ((vry_value - 2048) * 60) / 2048;
        int pos_yPB = 27 - ((vrx_value - 2048) * 28) / 2048;

        // Limita os valores para manter o quadrado dentro da tela
        if (pos_xPB < 8) pos_xPB = 8;
        if (pos_xPB > 112) pos_xPB = 112;
        if (pos_yPB < 8) pos_yPB = 8;
        if (pos_yPB > 48) pos_yPB = 48;

        ssd1306_draw_string(&ssd, "Z", pos_xPB, pos_yPB);
        ssd1306_rect(&ssd, 5, 5, 118, 54, true, false); // Borda dupla
    }
    else
    {
        gpio_put(pinG, false); // Apaga LED Verde
        ssd1306_draw_string(&ssd, "Z", pos_x, pos_y); // Desenha o quadrado normal
    }

    ssd1306_send_data(&ssd); // Atualiza o display
}
