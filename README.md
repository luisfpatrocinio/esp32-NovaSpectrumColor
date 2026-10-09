# Nova Spectrum Color

## Sobre o Projeto
O **Nova Spectrum Color** é um projeto baseado no microcontrolador ESP32 que funciona como um Gamepad Bluetooth customizado, utilizando um sensor de cor I2C (Adafruit TCS34725). 

O dispositivo lê as cores de objetos posicionados próximos ao sensor e as traduz em comandos de botões do controle Bluetooth. É ideal para interagir com jogos (como visual novels em engines como Ren'Py) ou outras aplicações que podem receber comandos de joystick baseados em cores.

## Como Funciona a Lógica de Cores
O sensor avalia a luz ambiente/refletida. Quando um objeto é posicionado próximo, o nível de luz total detectada aumenta (`C > 100`), disparando a leitura e avaliação dos canais RGB (Red, Green, Blue).

Atualmente, o projeto está configurado para mapear três cores específicas para os seguintes botões do Gamepad Bluetooth:

*   **Verde**: Aciona o **BOTÃO 1** (Detectado quando o canal Verde é superior ao Vermelho e Azul).
*   **Azul**: Aciona o **BOTÃO 2** (Detectado quando o canal Azul é dominante).
*   **Amarelo**: Aciona o **BOTÃO 3** (Detectado por uma mistura de altos níveis de luz Verde e Vermelha, superando o Azul).

Ao afastar o objeto de perto do sensor, todos os botões são liberados automaticamente.

## Hardware Necessário
*   Placa de desenvolvimento **ESP32**
*   Sensor de cor **Adafruit TCS34725** (Comunicação via I2C)
*   Cabos de conexão (Jumpers)

### Pinagem Padrão I2C (ESP32)
*   **SDA**: GPIO 21
*   **SCL**: GPIO 22
*   **VCC**: 3.3V
*   **GND**: GND

## Dependências / Bibliotecas
Para compilar e enviar o código usando o **PlatformIO**, certifique-se de que as seguintes bibliotecas estejam instaladas no seu ambiente:
1.  **Adafruit TCS34725**: Para comunicação e leitura dos dados do sensor de cor (inclusa no `platformio.ini`).
2.  **BleGamepad**: Para emular as funções do controle via Bluetooth. É necessário adicionar e instalar a dependência `lemmingdev/ESP32-BLE-Gamepad`.

## Executando o Projeto
1. Clone ou abra o projeto no VSCode com a extensão PlatformIO.
2. Compile o código e faça o upload para a sua placa ESP32.
3. Ligue o ESP32, ative o Bluetooth do seu computador ou smartphone e conecte-se ao dispositivo chamado **"Nova Spectrum"**.
4. Aproxime objetos de cores Verde, Azul ou Amarelo no sensor para ativar os comandos do gamepad!
