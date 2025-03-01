/*
 * macro.h
 *
 *  Created on: 2025
 *      Author: Yasin Batuhan URAL
 */

#ifndef macro_h
#define macro_h

#include "stm32f4xx_hal.h"
#include "main.h"

/*__________________________________MACROLAR__________________________________*/

/*_____GPIO İŞLEMLERİ_____*/

									/*__OUTPUT__*/

 //_SET RESET_

#define GPIO_WRITE(GpioPin, action) \
    HAL_GPIO_WritePin(GpioPin##_GPIO_Port, GpioPin##_Pin, (action == ON) ? GPIO_PIN_SET : GPIO_PIN_RESET);


									/*__INPUT__*/

 //_READ_
#define READ_INPUT(InputPin) \
	(HAL_GPIO_ReadPin(InputPin##_GPIO_Port, InputPin##_Pin) == GPIO_PIN_SET ? HIGH : LOW)

 //_TOGGLE_
#define TOGGLE_PIN(TogglePin) \
	HAL_GPIO_TogglePin(TogglePin##_GPIO_Port, TogglePin##_Pin)




/*_____DİĞER İŞLEMLER_____*/

//ERROR CHECK
#define CHECK_ERROR(status)  if(status != HAL_OK) { Error_Handler(); }


//ADC OKUMA
#define ADC_READ(adc_channel) HAL_ADC_GetValue(adc_channel)
// KULLANIMI -> uint32_t adc_value = ADC_READ(&hadc1);



								/*_____İLGİLİ DEFİNELAR_____*/

#define ON 1
#define OFF 0
#define HIGH 1
#define LOW 0


#endif /* MACRO_H */
