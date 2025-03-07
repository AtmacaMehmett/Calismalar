#include "timer.h"
#include "macro.h"
#include "stm32f4xx_hal.h"

// Bayraklar
volatile uint8_t flag100ms = 0;
volatile uint8_t flag200ms = 0;
volatile uint8_t flag500ms = 0;

// Sayaçlar
volatile uint32_t counter100ms = 0;
volatile uint32_t counter200ms = 0;
volatile uint32_t counter500ms = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2){  // Her 100 ms'de 1 kez girer
		// Sayaçlar
		counter100ms += 1;
		counter200ms += 1;
		counter500ms += 1;
	}
}

void setFlags(){
	// 100 ms'de bir flag'i aktif et
	if (counter100ms >= 1) {
		flag100ms = 1; // 100 ms bayrağını set et
		counter100ms = 0; // Sayaç sıfırla
	}

	// 200 ms'de bir flag'i aktif et
	if (counter200ms >= 2) {
		flag200ms = 1; // 200 ms bayrağını set et
		counter200ms = 0; // Sayaç sıfırla
	}

	// 500 ms'de bir flag'i aktif et
	if (counter500ms >= 5) {
		flag500ms = 1; // 500 ms bayrağını set et
		counter500ms = 0; // Sayaç sıfırla

	}
}

void clearFlags()
{
	// Bayraklar kalktıysa sıfırlama fonksiyonu
	if (flag100ms) {
		flag100ms = 0;  // 100 ms bayrağını sıfırla
	}

	if (flag200ms) {
		flag200ms = 0;  // 200 ms bayrağını sıfırla
	}

	if (flag500ms) {
		flag500ms = 0;  // 500 ms bayrağını sıfırla
	}
}


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
