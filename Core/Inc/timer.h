#ifndef TIMER_H_
#define TIMER_H_
#include "stm32f4xx_hal.h"



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void setFlags(void);
void clearFlags(void);
void timerMissions(void);


#endif /* TIMER_H_ */
