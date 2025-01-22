#include <stdio.h>
#include "pico/stdlib.h"

// Definição dos pinos
#define PINO_LED_VERMELHO  13
#define PINO_LED_VERDE     11
#define PINO_LED_AZUL      12
#define PINO_BUZZER        21

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
    gpio_put(PINO_BUZZER, 1);  // Liga o buzzer
    sleep_ms(2000);  // Mantém o buzzer ligado por 2 segundos
    gpio_put(PINO_BUZZER, 0);  // Desliga o buzzer
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
    printf("Sistema iniciado. LEDs alternando a cada 3 segundos...\n");

    // Loop principal
    while (true) {
        // Aciona o LED vermelho
        led_vermelho_on();
        sleep_ms(3000);  // Aguarda 3 segundos

        // Aciona o LED verde
        led_verde_on();
        sleep_ms(3000);  // Aguarda 3 segundos

        // Aciona o LED azul
        led_azul_on();
        sleep_ms(3000);  // Aguarda 3 segundos

        // Aciona os LEDs todos acesos (branco)
        led_branco_on();
        sleep_ms(3000);  // Aguarda 3 segundos com luz branca acesa

        // Desliga todos os LEDs
        leds_off();
        
        // Aciona o buzzer por 2 segundos
        buzzer_on();  // Toca o buzzer por 2 segundos

        // Pausa de 1 segundo antes de reiniciar o ciclo
        sleep_ms(1000);  // Aguarda 1 segundo antes de reiniciar o ciclo
    }

    return 0;
}
