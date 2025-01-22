#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

// Definição dos pinos
#define PINO_LED_VERMELHO  15
#define PINO_LED_VERDE     14
#define PINO_LED_AZUL      13
#define PINO_BUZZER        16
#define PINO_UART_RX       0
#define PINO_UART_TX       1

// Funções para acender LEDs
void led_vermelho_on() {
    gpio_put(PINO_LED_VERMELHO, 1);
    gpio_put(PINO_LED_VERDE, 0);
    gpio_put(PINO_LED_AZUL, 0);
}

void led_verde_on() {
    gpio_put(PINO_LED_VERMELHO, 0);
    gpio_put(PINO_LED_VERDE, 1);
    gpio_put(PINO_LED_AZUL, 0);
}

void led_azul_on() {
    gpio_put(PINO_LED_VERMELHO, 0);
    gpio_put(PINO_LED_VERDE, 0);
    gpio_put(PINO_LED_AZUL, 1);
}

void led_branco_on() {
    gpio_put(PINO_LED_VERMELHO, 1);
    gpio_put(PINO_LED_VERDE, 1);
    gpio_put(PINO_LED_AZUL, 1);
}

void leds_off() {
    gpio_put(PINO_LED_VERMELHO, 0);
    gpio_put(PINO_LED_VERDE, 0);
    gpio_put(PINO_LED_AZUL, 0);
}

// Função para ligar o buzzer
void buzzer_on() {
    gpio_put(PINO_BUZZER, 1);
}

// Função para processar comandos recebidos pela UART
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
        default:
            break;
    }
}

int main() {
    // Inicializa os pinos GPIO
    gpio_init(PINO_LED_VERMELHO);
    gpio_set_dir(PINO_LED_VERMELHO, GPIO_OUT);
    gpio_init(PINO_LED_VERDE);
    gpio_set_dir(PINO_LED_VERDE, GPIO_OUT);
    gpio_init(PINO_LED_AZUL);
    gpio_set_dir(PINO_LED_AZUL, GPIO_OUT);
    gpio_init(PINO_BUZZER);
    gpio_set_dir(PINO_BUZZER, GPIO_OUT);

    // Inicializa a UART
    uart_init(uart0, 9600);
    gpio_set_function(PINO_UART_RX, GPIO_FUNC_UART);
    gpio_set_function(PINO_UART_TX, GPIO_FUNC_UART);

    // Inicializa a UART para monitoramento
    printf("Sistema iniciado. Aguardando comandos...\n");

    // Loop principal
    while (true) {
        // Espera por dados da UART
        if (uart_is_readable(uart0)) {
            char command = uart_getc(uart0);
            process_command(command);
        }

        // Adiciona um pequeno delay para evitar o uso excessivo da CPU
        sleep_ms(100);
    }

    return 0;
}
