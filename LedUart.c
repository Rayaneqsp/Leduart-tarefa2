#include <stdio.h>
#include <stdio.h>
#include "pico/stdlib.h"

// Definição dos pinos dos LEDs e buzzer
#define PINO_LED_VERMELHO  13
#define PINO_LED_VERDE     11
#define PINO_LED_AZUL      12
#define PINO_BUZZER        21

// Definindo pinos para UART (caso queira usar UART)
#define UART_TX_PIN        0
#define UART_RX_PIN        1

// Funções para acender LEDs RGB
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
    printf("Buzzer acionado\n");
    for (int i = 0; i < 1000; i++) {  
        gpio_put(PINO_BUZZER, 1);  
        gpio_put(PINO_BUZZER, 0);  
        sleep_us(500);  
    }
    printf("Buzzer desligado\n");
}

// Função para inicializar a UART
void uart_custom_init() {
    uart_init(uart0, 9600);  // Inicia UART0 com taxa de 9600 baud
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);  // Define o pino TX
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);  // Define o pino RX
}

int main() {
    // Inicializa os pinos GPIO para LEDs e buzzer
    gpio_init(PINO_LED_VERMELHO);
    gpio_set_dir(PINO_LED_VERMELHO, GPIO_OUT);
    gpio_init(PINO_LED_VERDE);
    gpio_set_dir(PINO_LED_VERDE, GPIO_OUT);
    gpio_init(PINO_LED_AZUL);
    gpio_set_dir(PINO_LED_AZUL, GPIO_OUT);
    gpio_init(PINO_BUZZER);
    gpio_set_dir(PINO_BUZZER, GPIO_OUT);

    // Inicializa o console serial e a UART personalizada
    stdio_init_all();
    uart_custom_init();  // Usa o nome renomeado para inicializar a UART

    printf("Sistema iniciado. LEDs alternando a cada 3 segundos...\n");

    while (true) {
        // Alterna entre as cores
        led_vermelho_on();
        sleep_ms(3000);  // Aguarda 3 segundos

        led_verde_on();
        sleep_ms(3000);  // Aguarda 3 segundos

        led_azul_on();
        sleep_ms(3000);  // Aguarda 3 segundos

        led_branco_on();
        sleep_ms(3000);  // Aguarda 3 segundos

        // Desliga todos os LEDs
        leds_off();

        // Aciona o buzzer por 2 segundos
        buzzer_on();
        sleep_ms(2000);  // Duração do som

        // Pausa de 2 segundos antes de reiniciar o ciclo
        sleep_ms(2000);
    }

    return 0;
}
