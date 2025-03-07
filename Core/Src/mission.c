// mission.c
#include "timer.h"
#include "macro.h"

void timerMissions()
{
    // Eğer 100 ms bayrağı kalktıysa, LED1'i yak
    if (flag100ms) {
        TOGGLE_PIN(LED1);  // LED1-MAVİ
    }

    // Eğer 200 ms bayrağı kalktıysa, LED2'yi yak
    if (flag200ms) {
        TOGGLE_PIN(LED2);  // LED2-KIRMIZI
    }

    // Eğer 500 ms bayrağı kalktıysa, LED3'ü yak
    if (flag500ms) {
        TOGGLE_PIN(LED4);  // LED4-TURUNCU
    }
}
