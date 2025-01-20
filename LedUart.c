#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
///
#define LED_VERDE_PIN 11
#define LED_AZUL_PIN 12
#define LED_VERMELHO_PIN 13
#define BUZZER_PIN 21

// Função para configurar a UART
void init_uart() {
    uart_init(uart0, 115200);  // Inicializa a UART0 com baud rate de 115200
    gpio_set_function(0, GPIO_FUNC_UART);  // Pino 0 (TX)
    gpio_set_function(1, GPIO_FUNC_UART);  // Pino 1 (RX)
}

// Função para acionar o LED verde
void led_verde_on() {
    gpio_put(LED_VERDE_PIN, 1);
    gpio_put(LED_AZUL_PIN, 0);
    gpio_put(LED_VERMELHO_PIN, 0);
}

// Função para acionar o LED azul
void led_azul_on() {
    gpio_put(LED_VERDE_PIN, 0);
    gpio_put(LED_AZUL_PIN, 1);
    gpio_put(LED_VERMELHO_PIN, 0);
}

// Função para acionar o LED vermelho
void led_vermelho_on() {
    gpio_put(LED_VERDE_PIN, 0);
    gpio_put(LED_AZUL_PIN, 0);
    gpio_put(LED_VERMELHO_PIN, 1);
}

// Função para acionar os três LEDs (branco)
void led_branco_on() {
    gpio_put(LED_VERDE_PIN, 1);
    gpio_put(LED_AZUL_PIN, 1);
    gpio_put(LED_VERMELHO_PIN, 1);
}

// Função para desligar todos os LEDs
void leds_off() {
    gpio_put(LED_VERDE_PIN, 0);
    gpio_put(LED_AZUL_PIN, 0);
    gpio_put(LED_VERMELHO_PIN, 0);
}

// Função para acionar o buzzer
void buzzer_on() {
    gpio_put(BUZZER_PIN, 1);
    sleep_ms(2000);  // Buzzer ligado por 2 segundos
    gpio_put(BUZZER_PIN, 0);
}

// Função para processar comandos recebidos via UART
void process_command(char command) {
    switch (command) {
        case 'V':  // Verde
            led_verde_on();
            break;
        case 'A':  // Azul
            led_azul_on();
            break;
        case 'R':  // Vermelho
            led_vermelho_on();
            break;
        case 'B':  // Branco
            led_branco_on();
            break;
        case 'D':  // Desligar LEDs
            leds_off();
            break;
        case 'Z':  // Buzzer
            buzzer_on();
            break;
        case 'S':  // Reset
            // Para reiniciar o microcontrolador, podemos usar o seguinte:
            reboot();  // Reinicia o sistema
            break;
        default:
            break;
    }
}

int main() {
    // Inicializar os pinos GPIO para os LEDs e o buzzer
    gpio_init(LED_VERDE_PIN);
    gpio_set_dir(LED_VERDE_PIN, GPIO_OUT);
    gpio_init(LED_AZUL_PIN);
    gpio_set_dir(LED_AZUL_PIN, GPIO_OUT);
    gpio_init(LED_VERMELHO_PIN);
    gpio_set_dir(LED_VERMELHO_PIN, GPIO_OUT);
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    // Inicializar a UART
    init_uart();

    // Loop principal
    while (true) {
        if (uart_is_readable(uart0)) {
            // Lê o comando enviado via UART
            char command = uart_getc(uart0);

            // Processa o comando
            process_command(command);
        }
    }

    return 0;
}
