#include <stdio.h>
#include "pico/stdlib.h"   // Inclui a biblioteca padrão para funcionalidades básicas como GPIO, temporização e comunicação serial.
#include "hardware/timer.h" // Inclui a biblioteca para gerenciamento de temporizadores de hardware.

#define LED_PIN_RED 11
#define LED_PIN_YELLOW 12
#define LED_PIN_GREEN 13

uint8_t qualLedAcender = 11;

// Função de callback que será chamada repetidamente pelo temporizador
bool repeating_timer_callback(struct repeating_timer *t) {

    if(qualLedAcender == 11) //Apaga o led anterior
        gpio_put(13, false);
    else
        gpio_put(qualLedAcender-1, false);

    gpio_put(qualLedAcender, true); //Acende o led atual

    if(qualLedAcender == 13) //Verifica se o led atual é o último (13)
        qualLedAcender = 11;
    else
        qualLedAcender++;
    
    return true; // Retorna true para manter o temporizador repetindo. Se retornar false, o temporizador para.
}

int main() {
    // Inicializa a comunicação serial, permitindo o uso de funções como printf.
    stdio_init_all();

    // Inicializar o pino GPIO11
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED,true);

    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW,true);

    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN,true);

    // Declaração de uma estrutura de temporizador de repetição.
    struct repeating_timer timer;

    // Configura o temporizador para chamar a função de callback a cada 1 segundo.
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop infinito que mantém o programa em execução.
    while (true) {
        sleep_ms(1000);
        printf("Voce esta um segundo mais velho!\n");
    }
    return 0;
}
