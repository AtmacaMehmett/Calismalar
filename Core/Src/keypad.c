#include "keypad.h"
#include "stm32f4xx_hal.h"
#include "macro.h"

// MAIN İÇERİSİNDE KULLANIMI
/*
 * char pressed_key = '\0';
 * pressed_key = Read_Keypad();
 * if (pressed_key != '\0') {}
 */

// Union yapısı tanımlanıyor. Union kullanılarak farklı şekillerde veri saklanabilir,
// ancak yalnızca en büyük üyeye ait bellek alanı kullanılır.
typedef union {

    // Struct kullanarak her bir tuşa 1 bit ayırıyoruz.
    // Her tuş bir bit ile temsil edilecek.
    struct {
        uint16_t key1 : 1;    // key1, 1 tuşu
        uint16_t key2 : 1;    // key2, 2 tuşu
        uint16_t key3 : 1;    // key3, 3 tuşu
        uint16_t key4 : 1;    // key4, 4 tuşu
        uint16_t key5 : 1;    // key5, 5 tuşu
        uint16_t key6 : 1;    // key6, 6 tuşu
        uint16_t key7 : 1;    // key7, 7 tuşu
        uint16_t key8 : 1;    // key8, 8 tuşu
        uint16_t key9 : 1;    // key9, 9 tuşu
        uint16_t keyA : 1;    // keyA, A tuşu
        uint16_t keyB : 1;    // keyB, B tuşu
        uint16_t keyC : 1;    // keyC, C tuşu
        uint16_t keyD : 1;    // keyD, D tuşu
        uint16_t keyStar : 1; // keyStar, * tuşu
        uint16_t key0 : 1;    // key0, 0 tuşu
        uint16_t keyHash : 1; // keyHash, # tuşu
    } keys;

    // all_keys değişkeni, tüm tuşların durumunu tek bir değişken olarak saklamak için kullanılır.
    // Bu değişkenin boyutu 16 bit (2 byte) olup, tüm tuşların 1-bitlik durumunu tutar.
    uint16_t all_keys;    // Tüm tuşların durumlarını tutan 16 bitlik değişken.
} KeypadState;

KeypadState keypad_state;
uint32_t lastDebounceTime = 0;
#define DEBOUNCE_DELAY_MS 100  // 100 ms debouncing süresi

// Her tuş için hangi karakteri döndüreceğimizin harf tablosu
char Read_Keypad(void) {
    static uint16_t lastState = 0;  // Önceki tuş durumu
    uint16_t currentState = 0;

    // Tüm satırlarda tuşlar kontrol ediliyor
    GPIO_WRITE(R1, ON);
    if (READ_INPUT(C1) == ON) keypad_state.keys.key1 = 1;  // key1
    if (READ_INPUT(C2) == ON) keypad_state.keys.key2 = 1;  // key2
    if (READ_INPUT(C3) == ON) keypad_state.keys.key3 = 1;  // key3
    if (READ_INPUT(C4) == ON) keypad_state.keys.keyA = 1;  // keyA
    GPIO_WRITE(R1, OFF);

    GPIO_WRITE(R2, ON);
    if (READ_INPUT(C1) == ON) keypad_state.keys.key4 = 1;  // key4
    if (READ_INPUT(C2) == ON) keypad_state.keys.key5 = 1;  // key5
    if (READ_INPUT(C3) == ON) keypad_state.keys.key6 = 1;  // key6
    if (READ_INPUT(C4) == ON) keypad_state.keys.keyB = 1;  // keyB
    GPIO_WRITE(R2, OFF);

    GPIO_WRITE(R3, ON);
    if (READ_INPUT(C1) == ON) keypad_state.keys.key7 = 1;  // key7
    if (READ_INPUT(C2) == ON) keypad_state.keys.key8 = 1;  // key8
    if (READ_INPUT(C3) == ON) keypad_state.keys.key9 = 1;  // key9
    if (READ_INPUT(C4) == ON) keypad_state.keys.keyC = 1;  // keyC
    GPIO_WRITE(R3, OFF);

    GPIO_WRITE(R4, ON);
    if (READ_INPUT(C1) == ON) keypad_state.keys.keyStar = 1; // keyStar
    if (READ_INPUT(C2) == ON) keypad_state.keys.key0 = 1;    // key0
    if (READ_INPUT(C3) == ON) keypad_state.keys.keyHash = 1; // keyHash
    if (READ_INPUT(C4) == ON) keypad_state.keys.keyD = 1;    // keyD
    GPIO_WRITE(R4, OFF);

    // Zaman kontrolü ile debouncing işlemi
    if (keypad_state.all_keys != lastState) {
        lastDebounceTime = HAL_GetTick();  // Zamanlayıcıyı sıfırla
    }

    // Debounce gecikmesi sonrası tuş kontrolü
    if ((HAL_GetTick() - lastDebounceTime) > DEBOUNCE_DELAY_MS) {
        lastState = keypad_state.all_keys; // Son tuş durumunu sakla

        // Eğer tuşa basıldıysa, uygun karakteri döndürüyoruz
        if (keypad_state.keys.key1 && keypad_state.keys.key3) {
            return 'H';  // 1 ve 3'e aynı anda basıldığında 'H' döner
        }

        if (keypad_state.keys.key1 && keypad_state.keys.key6) {
            return 'M';  // 1 ve 6'ya aynı anda basıldığında 'M' döner
        }

        if (keypad_state.keys.key1) {
            return '1';  // Yalnızca 1'e basıldığında '1' döner
        }

        if (keypad_state.keys.key2) {
            return '2';  // Yalnızca 2'ye basıldığında '2' döner
        }

        if (keypad_state.keys.key3) {
            return '3';  // Yalnızca 3'e basıldığında '3' döner
        }

        if (keypad_state.keys.key4) {
            return '4';  // Yalnızca 4'e basıldığında '4' döner
        }

        if (keypad_state.keys.key5) {
            return '5';  // Yalnızca 5'e basıldığında '5' döner
        }

        if (keypad_state.keys.key6) {
            return '6';  // Yalnızca 6'ya basıldığında '6' döner
        }

        if (keypad_state.keys.key7) {
            return '7';  // Yalnızca 7'ye basıldığında '7' döner
        }

        if (keypad_state.keys.key8) {
            return '8';  // Yalnızca 8'e basıldığında '8' döner
        }

        if (keypad_state.keys.key9) {
            return '9';  // Yalnızca 9'a basıldığında '9' döner
        }

        if (keypad_state.keys.keyA) {
            return 'A';  // Yalnızca A'ya basıldığında 'A' döner
        }

        if (keypad_state.keys.keyB) {
            return 'B';  // Yalnızca B'ye basıldığında 'B' döner
        }

        if (keypad_state.keys.keyC) {
            return 'C';  // Yalnızca C'ye basıldığında 'C' döner
        }

        if (keypad_state.keys.keyD) {
            return 'D';  // Yalnızca D'ye basıldığında 'D' döner
        }

        if (keypad_state.keys.keyStar) {
            return '*';  // Yalnızca * tuşuna basıldığında '*' döner
        }

        if (keypad_state.keys.key0) {
            return '0';  // Yalnızca 0'a basıldığında '0' döner
        }

        if (keypad_state.keys.keyHash) {
            return '#';  // Yalnızca # tuşuna basıldığında '#' döner
        }
    }

    return '\0';  // Eğer hiç bir tuşa basılmamışsa boş karakter döner
}
