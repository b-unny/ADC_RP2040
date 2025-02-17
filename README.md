# Conversores Analógicos-Digitais

### Objetivos 
• Compreender o funcionamento do conversor analógico-digital (ADC) no RP2040. 
• Utilizar o PWM para controlar a intensidade de dois LEDs RGB com base nos valores do joystick. 
• Representar a posição do joystick no display SSD1306 por meio de um quadrado móvel. 
• Aplicar o protocolo de comunicação I2C na integração com o display.


1. Configurar o Conversor Analógico-Digital (ADC) no RP2040
        Capturar os valores analógicos do joystick nos eixos X (GPIO 26) e Y (GPIO 27).

2. Controlar LEDs RGB via PWM
        - Configurar PWM para os LEDs nas GPIOs 11 (Vermelho), 12 (Verde) e 13 (Azul).
        - Ajustar a intensidade do LED Azul conforme o eixo Y:
            Joystick centralizado (2048) → LED apagado.
            Movendo para cima (valores < 2048) ou para baixo (valores > 2048) → brilho aumenta até máximo (0 ou 4095).
        - Ajustar a intensidade do LED Vermelho conforme o eixo X:
            Joystick centralizado (2048) → LED apagado.
            Movendo para esquerda (valores < 2048) ou direita (valores > 2048) → brilho aumenta até máximo (0 ou 4095).

3. Exibir Posição do Joystick no Display SSD1306
        - Utilizar protocolo I2C nas GPIOs 14 e 15.
        - Exibir um quadrado de 8x8 pixels centralizado.
        - Mover o quadrado proporcionalmente conforme os valores do joystick.

4. Adicionar Funcionalidades do Botão do Joystick (GPIO 22)
        - Alternar o LED Verde a cada pressionamento.
        - Modificar a borda do display a cada pressionamento, alternando entre diferentes estilos.

5. Adicionar Funcionalidade do Botão A (GPIO 5)
        - Ativar ou desativar os LEDs RGB a cada acionamento.

6. Garantir a Interconexão Correta dos Componentes
        - LED RGB: GPIOs 11, 12 e 13.
        - Joystick: Eixos X e Y nos GPIOs 26 e 27.
        - Botão do Joystick: GPIO 22.
        - Botão A: GPIO 5.
        - Display SSD1306 (I2C): GPIOs 14 e 15.

[Créditos diretório "inc": Prof. Wilton Lacerda](https://github.com/wiltonlacerda)

[link para demostração]()
