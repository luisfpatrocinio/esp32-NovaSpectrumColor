#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <BleGamepad.h> 

// Inicializa o sensor de cor I2C
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// Inicializa o controle Bluetooth com o nome do projeto
BleGamepad bleGamepad("Nova Spectrum", "Nova Spectrum", 100);

void setup() {
  Serial.begin(115200); // Velocidade padrão do ESP32
  
  if (tcs.begin()) {
    Serial.println("Sensor I2C Encontrado!");
  } else {
    Serial.println("Erro: Sensor não encontrado. Verifique fios SDA e SCL.");
    while (1); // Trava aqui se der erro
  }

  // Inicia o Bluetooth
  bleGamepad.begin();
  Serial.println("ESP32 iniciado. Aguardando conexão Bluetooth...");
}

void loop() {
  // Só executa a leitura se o PC estiver conectado via Bluetooth
  if (bleGamepad.isConnected()) {
    
    uint16_t r, g, b, c;
    
    // Lê as cores brutas (R=Red, G=Green, B=Blue, C=Clear/Luz total)
    tcs.getRawData(&r, &g, &b, &c);

    /* Lógica:
       O sensor tem um LED forte. Quando encostamos um objeto, a luz reflete.
       Se a luz total (C) for muito baixa, não tem objeto lá.
       (Se a sala for muito clara, você pode aumentar esse número '100')
    */
    if (c > 100) { 
      
      if (b > r && b > g) {
        // AZUL -> BOTÃO 2
        bleGamepad.press(BUTTON_2);
        bleGamepad.release(BUTTON_1);
        bleGamepad.release(BUTTON_3);
      } 
      else if (r > b && g > b && (r * 2) > g) {
        // AMARELO -> BOTÃO 3 (Alta reflexão de Verde e Vermelho)
        bleGamepad.press(BUTTON_3);
        bleGamepad.release(BUTTON_1);
        bleGamepad.release(BUTTON_2);
      } 
      else if (g > r && g > b) {
        // VERDE -> BOTÃO 1
        bleGamepad.press(BUTTON_1);
        bleGamepad.release(BUTTON_2);
        bleGamepad.release(BUTTON_3);
      }
      
    } else {
      // Se tirar o objeto de perto do sensor, solta todos os botões do Joystick
      bleGamepad.release(BUTTON_1);
      bleGamepad.release(BUTTON_2);
      bleGamepad.release(BUTTON_3);
    }
  }
  
  // Pausa de 100ms para o jogo Ren'Py não travar com excesso de comandos
  delay(100);
}