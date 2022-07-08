
/****************************************************************************************************/
/* Name: timer_config.h                                                                             */
/* Author: Madonna Magdy                                                                             */
/* Version: V4                                                                                       */
/* Usage: This module contains the interfacing definition of  the timer peripheral configurations    */
/****************************************************************************************************/

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

#include "lstd.h"
/**************************************  Enummeration  ***********************************************************************************/
/*Timer pre-scalers*/
typedef enum{
 MTIMER_NO_PRESCALING,
 MTIMER_PRESCALER_1,
 MTIMER_PRESCALER_8,
 MTIMER_PRESCALER_64,
 MTIMER_PRESCALER_256,
 MTIMER_PRESCALER_1024
}mtimerPrescaler_t;

typedef enum{
	Disable, Enable

}mimer_InterruptMask_State;

typedef enum{
	 FALLING, RISING

}icu_Edge_t;

/**************************************   Delay Mode ***********************************************************************************/
typedef struct{
	mtimerPrescaler_t prescaler;
    u8_t InitialValue;
    u8_t CompareValue;


}DelayMode_8bit_Config_t;

typedef struct{
	mtimerPrescaler_t prescaler;
    u16_t InitialValue;
    u16_t CompareValue;

}DelayMode_16bit_Config_t;

/************************************** ICU *****************************************************************************************/
typedef struct{

	icu_Edge_t edge;
	mtimerPrescaler_t prescaler;

} ICU_Config_t;

/************************************** Creating instances of typedef Structure *****************************************************************************************/
DelayMode_8bit_Config_t  delayTimer0_milli;

DelayMode_8bit_Config_t delayTimer0_micro;

DelayMode_8bit_Config_t  delayTimer2_milli;

DelayMode_8bit_Config_t delayTimer2_micro;

ICU_Config_t   ICU_signalMeasurement;




#endif /* TIMER_CONFIG_H_ */
