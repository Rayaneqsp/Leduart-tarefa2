#include <stdio.h>
#include "pico/stdlib.h"

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
    printf("Buzzer acionado\n");
    for (int i = 0; i < 1000; i++) {  
        gpio_put(PINO_BUZZER, 1);  
        gpio_put(PINO_BUZZER, 0);  
        sleep_us(500);  
    }
    printf("Buzzer desligado\n");
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
        led_vermelho_on();
        sleep_ms(3000);  

        led_verde_on();
        sleep_ms(3000); 

        led_azul_on();
        sleep_ms(3000);  

        led_branco_on();
        sleep_ms(3000);  

        
        leds_off();
        
        // Aciona o buzzer por 2 segundos
        buzzer_on(); 

        // Pausa de 1 segundo antes de reiniciar o ciclo
        sleep_ms(1000);  
    }

    return 0;
}

