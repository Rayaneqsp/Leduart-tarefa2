#include <stdio.h>
#include "pico/stdlib.h"

// Definição dos pinos dos LEDs e buzzer
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

// Função para inicializar a UART
void uart_custom_init() {
    uart_init(uart0, 9600);  // Inicia UART0 com taxa de 9600 baud
    gpio_set_function(0, GPIO_FUNC_UART);  
    gpio_set_function(1, GPIO_FUNC_UART);  
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
    uart_custom_init();  

    printf("Sistema iniciado. Pressione 'Espaço' para alternar as cores dos LEDs e ativar o buzzer.\n");

    
    char comando;

    while (true) {
        // Aguarda o usuário enviar um comando via UART
        if (uart_is_readable(uart0)) {
            comando = uart_getc(uart0);  // Lê o comando recebido pela UART

            
            if (comando == ' ') {
                printf("Iniciando troca de cores...\n");

                // Alterna entre as cores com duração de 2 segundos cada
                led_vermelho_on();
                sleep_ms(2000);  

                led_verde_on();
                sleep_ms(2000);  

                led_azul_on();
                sleep_ms(2000);  

                led_branco_on();
                sleep_ms(2000);  

                // Desliga todos os LEDs
                leds_off();

                // Aciona o buzzer por 2 segundos
                buzzer_on();
                sleep_ms(2000);  

                printf("Ciclo completo. Pressione 'Espaço' novamente para reiniciar.\n");
            }
        }
    }

    return 0;
}
