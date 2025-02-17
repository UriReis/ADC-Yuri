# ADC-Yuri


README - Controle de LEDs e Display com Joystick no RP2040

Projeto: Controle de LEDs e Display OLED com Joystick no RP2040

Nome: Yuri Silva Reis

Matrícula: TIC370101506

Descrição:

Este projeto implementa o controle de LEDs RGB por PWM e a movimentação de um quadrado em um display OLED SSD1306 utilizando um joystick analógico no microcontrolador RP2040. O código permite:

- Controlar o brilho dos LEDs vermelho e azul de acordo com o movimento do joystick.
- Mover um quadrado na tela do display OLED conforme a posição do joystick.
- Alternar o estado dos LEDs azul e vermelho com o botão A.
- Alternar entre dois modos de exibição no display com o botão PB do joystick, além de alterar o estado do led verde.

Configuração do PWM para os LEDs

Os LEDs são controlados por PWM (Modulação por Largura de Pulso), ajustando seu brilho proporcionalmente ao deslocamento do joystick.


LED Azul (GPIO pinB) → Controlado pelo eixo Y do joystick (vale lembrar que os eixos na placa BitDoglab estão invertidos).

LED Vermelho (GPIO pinR) → Controlado pelo eixo X do joystick (vale lembrar que os eixos na placa BitDoglab estão invertidos).

Zona Morta: Se o joystick estiver próximo do centro (±500 unidades), o LED permanece apagado para evitar cintilação.

Controle do Display OLED

O display SSD1306 (I2C) exibe um quadrado de 8x8 pixels que se move conforme a posição do joystick.

Eixo X do Joystick → Move o quadrado horizontalmente.

Eixo Y do Joystick → Move o quadrado verticalmente.

O botão PB do joystick alterna entre modo normal e modo alternativo, onde a borda do display muda de estilo e o led verde muda de estado.

Funcionalidades Implementadas

1- Controle dos LEDs por PW
- Ajusta o brilho dos LEDs Azul e Vermelho proporcionalmente ao movimento do joystick.
- Implementa uma zona morta para evitar pequenas variações quando o joystick está no centro.
- O Botão A permite ligar/desligar os LEDs sem afetar o display.

2️- Controle do Quadrado no Display OLED
- O quadrado de 8x8 pixels é atualizado dinamicamente com os valores do joystick.
- O Botão PB do joystick alterna entre dois modos de exibição:

Modo normal: Quadrado se move livremente.
Modo alternativo: A borda do display muda e o led altera para o estado ON.

3️- Interrupções com o Botão A
- Implementação de interrupção (IRQ) no Botão A para alternar o estado dos LEDs azul e vermelho.
- Utilização de debouncing (200ms) para evitar múltiplas ativações acidentais.

Estrutura do Código

adc.c → Código principal.

inicia.c → Configuração dos GPIOs, ADC e inicialização do sistema.

display.c → Controle do display e movimentação do quadrado.

ledjoy.c → Configuração do PWM para controle dos LEDs, lógica de leitura do joystick e  interrupção para alternância dos LEDs via Botão A.



Como Executar:

Compilar e rodar no VS Code utilizando o SDK do RP2040.

Testar as funcionalidades:

Movimentação do quadrado no display.

Controle de brilho dos LEDs pelo joystick.

Alternância dos modos de exibição com o botão PB do joystick.

Ligar/desligar os LEDs com o botão A.
