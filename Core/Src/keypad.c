#include "keypad.h"
#include "stm32f4xx_hal.h"
#include "macro.h"

// Union yapısı tanımlanıyor.
typedef union {
	struct {
		uint16_t key1 : 1;
		uint16_t key2 : 1;
		uint16_t key3 : 1;
		uint16_t keyA : 1;

		uint16_t key4 : 1;
		uint16_t key5 : 1;
		uint16_t key6 : 1;
		uint16_t keyB : 1;

		uint16_t key7 : 1;
		uint16_t key8 : 1;
		uint16_t key9 : 1;
		uint16_t keyC : 1;

		uint16_t keyStar : 1;
		uint16_t key0 : 1;
		uint16_t keyHash : 1;
		uint16_t keyD : 1;

	} keys;

	uint16_t all_keys;
} KeypadState;

KeypadState keypad_state;
uint32_t lastDebounceTime = 0;
#define DEBOUNCE_DELAY_MS 100  // 100 ms debouncing süresi

char Read_Keypad(void) {
	static uint16_t lastState = 0;  // Önceki tuş durumu
	uint16_t currentState = 0;

	// Tüm satırlarda tuşlar kontrol ediliyor
	GPIO_WRITE(R1, ON);
	if (READ_INPUT(C1) == ON) currentState |= (1 << 0);  // key1
	if (READ_INPUT(C2) == ON) currentState |= (1 << 1);  // key2
	if (READ_INPUT(C3) == ON) currentState |= (1 << 2);  // key3
	if (READ_INPUT(C4) == ON) currentState |= (1 << 3);  // keyA
	GPIO_WRITE(R1, OFF);

	GPIO_WRITE(R2, ON);
	if (READ_INPUT(C1) == ON) currentState |= (1 << 4);  // key4
	if (READ_INPUT(C2) == ON) currentState |= (1 << 5);  // key5
	if (READ_INPUT(C3) == ON) currentState |= (1 << 6);  // key6
	if (READ_INPUT(C4) == ON) currentState |= (1 << 7);  // keyB
	GPIO_WRITE(R2, OFF);

	GPIO_WRITE(R3, ON);
	if (READ_INPUT(C1) == ON) currentState |= (1 << 8);  // key7
	if (READ_INPUT(C2) == ON) currentState |= (1 << 9);  // key8
	if (READ_INPUT(C3) == ON) currentState |= (1 << 10); // key9
	if (READ_INPUT(C4) == ON) currentState |= (1 << 11); // keyC
	GPIO_WRITE(R3, OFF);

	GPIO_WRITE(R4, ON);
	if (READ_INPUT(C1) == ON) currentState |= (1 << 12); // keyStar
	if (READ_INPUT(C2) == ON) currentState |= (1 << 13); // key0
	if (READ_INPUT(C3) == ON) currentState |= (1 << 14); // keyHash
	if (READ_INPUT(C4) == ON) currentState |= (1 << 15); // keyD
	GPIO_WRITE(R4, OFF);

	// Zaman kontrolü ile debouncing işlemi
	if (currentState != lastState) {
		lastDebounceTime = HAL_GetTick();  // Zamanlayıcıyı sıfırla
	}

	// Debounce gecikmesi sonrası tuş kontrolü
	if ((HAL_GetTick() - lastDebounceTime) > DEBOUNCE_DELAY_MS) {
		keypad_state.all_keys = currentState;

		// Basılı olan tuş sayısını hesapla
		uint8_t pressedKeys = __builtin_popcount(currentState);

		if (keypad_state.keys.key1 && keypad_state.keys.key3) {
			return 'H';  // 1 ve 3'e aynı anda basıldığında 'H' döndür
		} else if (keypad_state.keys.key1 && keypad_state.keys.key6) {
			return 'M';  // 1 ve 6'ya aynı anda basıldığında 'M' döndür
		} else if (pressedKeys > 1) {
			return '\0';  // Tanımlı kombinasyonlar harici çift basışlarda '\0' dön
		} else if (keypad_state.keys.key1) {
			return '1';  // Yalnızca 1'e basıldığında '1' döndür
		} else if (keypad_state.keys.key2) {
			return '2';  // Yalnızca 2'ye basıldığında '2' döndür
		} else if (keypad_state.keys.key3) {
			return '3';  // Yalnızca 3'e basıldığında '3' döndür
		} else if (keypad_state.keys.key4) {
			return '4';  // Yalnızca 4'e basıldığında '4' döndür
		} else if (keypad_state.keys.key5) {
			return '5';  // Yalnızca 5'e basıldığında '5' döndür
		} else if (keypad_state.keys.key6) {
			return '6';  // Yalnızca 6'ya basıldığında '6' döndür
		} else if (keypad_state.keys.key7) {
			return '7';  // Yalnızca 7'ye basıldığında '7' döndür
		} else if (keypad_state.keys.key8) {
			return '8';  // Yalnızca 8'e basıldığında '8' döndür
		} else if (keypad_state.keys.key9) {
			return '9';  // Yalnızca 9'a basıldığında '9' döndür
		} else if (keypad_state.keys.key0) {
			return '0';  // Yalnızca 0'a basıldığında '0' döndür
		} else if (keypad_state.keys.keyA) {
			return 'A';  // Yalnızca A'ya basıldığında 'A' döndür
		} else if (keypad_state.keys.keyB) {
			return 'B';  // Yalnızca B'ye basıldığında 'B' döndür
		} else if (keypad_state.keys.keyC) {
			return 'C';  // Yalnızca C'ye basıldığında 'C' döndür
		} else if (keypad_state.keys.keyD) {
			return 'D';  // Yalnızca D'ye basıldığında 'D' döndür
		} else if (keypad_state.keys.keyStar) {
			return '*';  // Yalnızca '*' tuşuna basıldığında '*' döndür
		} else if (keypad_state.keys.keyHash) {
			return '#';  // Yalnızca '#' tuşuna basıldığında '#' döndür
		}
	}

	lastState = currentState;  // Son tuş durumunu sakla
	return '\0';  // Hiçbir tuşa basılmadıysa boş karakter döndür
}

