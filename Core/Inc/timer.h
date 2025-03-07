// timer.h
#ifndef TIMER_H
#define TIMER_H

#include "stm32f4xx_hal.h"

// Bayraklar
extern volatile uint8_t flag100ms;
extern volatile uint8_t flag200ms;
extern volatile uint8_t flag500ms;

// Sayaçlar
extern volatile uint32_t counter100ms;
extern volatile uint32_t counter200ms;
extern volatile uint32_t counter500ms;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void setFlags(void);
void clearFlags(void);
void timerMissions(void);

#endif
