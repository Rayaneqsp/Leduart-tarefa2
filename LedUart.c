#include <stdio.h>
#include "pico/stdlib.h"

// Definição dos pinos
#define PINO_LED_VERMELHO  13
#define PINO_LED_VERDE     11
#define PINO_LED_AZUL      12
#define PINO_BUZZER        21

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
    sleep_ms(2000);  // Mantém o buzzer ligado por 2 segundos
    gpio_put(PINO_BUZZER, 0); // Desliga o buzzer
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
            printf("Comando desconhecido: %c\n", command);
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

    // Inicializa o console serial
    stdio_init_all();
    printf("Sistema iniciado. Aguardando comandos...\n");

    // Loop principal
    while (true) {
        // Espera por comandos do console serial
        if (stdio_uart_connected()) {
            char command = getchar();  // Recebe um caractere do console
            process_command(command);
        }

        // Adiciona um pequeno delay para evitar o uso excessivo da CPU
        sleep_ms(100);
    }

    return 0;
}
