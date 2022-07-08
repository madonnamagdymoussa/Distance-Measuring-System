/*************************************************************************************************************************************/
/* Name: timer.c                                                                                                                    */
/* Author: Madonna Magdy                                                                                                            */
/* Version: V4                                                                                                                      */
/* Usage: This module contains the implementation for the timer functions                                                */
/*************************************************************************************************************************************/


/********************************************  Includes  ***************************************************************************/
#include "lbit.h"
#include "lstd.h"

/***********************************/
#include "timer_hardware_register.h"
#include "timer.h"

/***********************************/
#include <avr/interrupt.h>
/***********************************/
#include "mdio.h"
/******************************************** Timer global variables *******************************************************************/

/*Global variable used to hold the selected timer1 pre-scaler*/
//static u8_t gu8_timer_16bits_SelectedPrescaler1=0;

static u8_t gu8_timer_8bits_SelectedPrescaler[2]={0};

/*It is not preferable to start the timer at the initialization function
 * once there is a selected pre-scaler inserted in the timer control register the timer will start counting
 * It is more preferable to have a function for starting the timer and for stopping the timer
 * so the value of the selected  pre-scaler will be copied into a global variable that hold the value of the pre-scaler
 * the global variable that hold the selected pre-scaler will be inserted into the timer counter control register in the
 * function of start timing and stop timing
 *
 */

/******************************************** Call Back Function ********************************************************************/

/* An array of functions handlers each with an id.*/
/* Without the curly braces in {NULL_PTR} , the FIRST callback function ONLY  will be initialized with null pointer*/
static volatile  CallbackFunc_t func_register[8] = {NULL_PTR};

/* Global variables to hold the address of the call back function in the application */
//static volatile void (*g_callBackPtr)(void) = NULL_PTR;

u8_t  TIMER_OUTPUT_COMPARE_FLAG_BIT[2]={TIMER0_OUTPUT_COMPARE_FLAG,TIMER2_OUTPUT_COMPARE_FLAG};
/* array that holds the number of bits of flag register of timer0 and timer2 in the interrupt flag mask register */

 /********************************************  ISR  ***************************************************************************/

/* If you don't initialize func_register[] with a null pointer
 * and you forgot to register the call back function there will
 * be segmentation fault because you are trying to access a wild pointer */

/* The advantage of the if condition ---> (if(func_register[] != NULL_PTR) )
 * you can't check on a garbage value but you can check on the null value
 * to see if the pointer to function (func_register[]) doesn't hold the
 * address of a function or doesn't hold a value*/

 ISR(TIMER0_OVF_vect){
	  	if(func_register[0] != NULL_PTR){
 		func_register[0]();
 	}
 }
/****************************************************/

 ISR(TIMER0_COMP_vect){
 	if(func_register[1] != NULL_PTR){
 		func_register[1]();
 	}
 }
 /****************************************************/
  ISR(TIMER1_OVF_vect){
 	if(func_register[2] != NULL_PTR){
 		func_register[2]();
 	}
 }
 /****************************************************/
 ISR(TIMER1_COMPA_vect){
 	if(func_register[3] != NULL_PTR){
 		func_register[3]();
 	}
 }
/****************************************************/
 ISR(TIMER1_COMPB_vect){
 	if(func_register[4] != NULL_PTR){
 		func_register[4]();
 	}
	  }
/****************************************************/
ISR(TIMER1_CAPT_vect){
 	if(func_register[5] != NULL_PTR){
 		(func_register[5])();
 	}

}

/****************************************************/
 ISR(TIMER2_OVF_vect){
 	if(func_register[6] != NULL_PTR){
 		func_register[6]();
 	}
 }
/****************************************************/
 ISR(TIMER2_COMP_vect){
 	if(func_register[7] != NULL_PTR){
 		func_register[7]();
 	}
 }
/******************************************** Array Of pointers to Registers *******************************************************************/


/**************************************************************************************************************/
/* creating an array of pointers to registers
 * the user (or the application layer) will not be allowed to have access to the hardware registers
 * because it's not his/her concern
 * he/she will only be allowed to call the interfacing functions in the timer.h file
 * for that reason a keyword static will be added*/

static volatile u8_t *const Timer_8bits_Control_Register[2]={
		(u8_t*)(&MTIMER_TCCR0),
		(u8_t*)(&MTIMER_TCCR2),


};

/**************************************************************************************************************/
/* creating an array of pointers to registers
 * the user (or the application layer) will not be allowed to have access to the hardware registers
 * because it's not his/her concern
 * he/she will only be allowed to call the interfacing functions in the timer.h file
 * for that reason a keyword static will be added*/

static volatile u8_t *const Timer_8bits_Compare_Match_Register[2]={
		(u8_t*)(&MTIMER_OCR0),
		(u8_t*)(&MTIMER_OCR2)


};


/**************************************************************************************************************/
/* creating an array of pointers to registers
 * the user (or the application layer) will not be allowed to have access to the hardware registers
 * because it's not his/her concern
 * he/she will only be allowed to call the interfacing functions in the timer.h file
 * for that reason a keyword static will be added*/

static volatile u8_t *const Timer_8bits_Counter_Register[2]={
		(u8_t*)(&MTIMER_TCNT0),
		(u8_t*)(&MTIMER_TCNT2)

};


/***************************************** Static Functions ******************************************************************************************/

/********************************************  8BIT TIMER  ********************************************************************/
void static mtimer_8bits_start(u8_t timerIndex)
{

	/*Resetting the selected timer counter*/
    *Timer_8bits_Counter_Register[timerIndex]= 0;

	/*Clear the bits responsible for the clock selection of the selected timer*/
	*Timer_8bits_Control_Register[timerIndex] &= ~(1<<TCCR_CLOCK_SELECT_0) & ~(1<<TCCR_CLOCK_SELECT_1) & ~(1<<TCCR_CLOCK_SELECT_2);

	/*Adding the previous selected timer pre-scaler*/
	 *Timer_8bits_Control_Register[timerIndex] |= gu8_timer_8bits_SelectedPrescaler[timerIndex];

	 return;

}

void static mtimer_8bits_stop(u8_t timerIndex)
{
	/*Clear the bits responsible for the clock selection*/
	*Timer_8bits_Control_Register[timerIndex] &= ~(1<<TCCR_CLOCK_SELECT_0) & ~(1<<TCCR_CLOCK_SELECT_1) & ~(1<<TCCR_CLOCK_SELECT_2);

	/*Return from this function*/
	return;
}


/****************************************************************************************************************************************/
/********************************************  DELAY MODE *******************************************************************************/
/****************************************************************************************************************************************/


/********************************************  8BIT TIMER  ********************************************************************/
/* the user have the option to select between timer0 and timer2 for initializing the delay function
 * by using the timerIndex  which is an index of the array of pointers to registers */

void  DelayTimer_8bits_Init ( DelayMode_8bit_Config_t * ptr_delayTimer , u8_t timerIndex){

	 *Timer_8bits_Control_Register[timerIndex] |= (1<<TCCR_WAVE_GENERATION_CTC);
	 *Timer_8bits_Control_Register[timerIndex] &= ~(1<< TCCR_WAVE_GENERATION_PWM);

	  gu8_timer_8bits_SelectedPrescaler[timerIndex]  = (ptr_delayTimer->prescaler);

	 *Timer_8bits_Compare_Match_Register[timerIndex] =(ptr_delayTimer->CompareValue);

}
/********************************************  8BIT TIMER  ********************************************************************/
void  DelayTimer_8bits_synchrounous(u8_t au8_delayTime,u8_t timerIndex){

	 mtimer_8bits_start(timerIndex); /* pre-scaling value inserted */

	/*Looping over the time */
	 while(au8_delayTime--){

		 while( 0 == GET_BIT(MTIMER_TIFR,TIMER_OUTPUT_COMPARE_FLAG_BIT[timerIndex]) );

		 /*Clearing the OCF0 flag*/
		 SET_BIT(MTIMER_TIFR, TIMER_OUTPUT_COMPARE_FLAG_BIT[timerIndex]);

	 }

	 mtimer_8bits_stop(timerIndex); /* pre-scaling value cleared*/
}
/*************************************************************************************************************************/








/****************************************************************************************************************/
/********************************************  ICU MODE *********************************************************/
/****************************************************************************************************************/

/****************************************************************************************************************/
void  Icu_init( ICU_Config_t * ptr_icu_config){

      /* NORMAL MODE the timer counts till 65,536  */
	  MTIMER_TCCR1A |= (TCCR1A_FORCE_OUTPUT_COMPARE_CHANNELB)|(TCCR1A_FORCE_OUTPUT_COMPARE_CHANNELA) ;

	  MTIMER_TCCR1B = ( (MTIMER_TCCR1B & 0xF8)|  (ptr_icu_config ->prescaler));

	  MTIMER_TCCR1B = ( (MTIMER_TCCR1B & 0xBF)|  ((ptr_icu_config->edge)<<TCCR1B_Input_Capture_Edge_Select) );
	  /* Insert the required edge and pre-scaling  */

	  MTIMER_TCNT1 = 0;

	  MTIMER_ICR1=0;

	  /* Enable the Input Capture interrupt to generate an interrupt when edge is detected on ICP1/PD6 pin */
	  MTIMER_TIMSK |=(1<<5);

	  MTIMER_SREG=(1<<7);

}
/****************************************************************************************************************/
void  Icu_setEdgeDetectionType( icu_Edge_t edge){

	MTIMER_TCCR1B =( (MTIMER_TCCR1B & 0xBF) | ( edge << TCCR1B_Input_Capture_Edge_Select ) );
	/*
	 * insert the required edge type in ICES1 bit in TCCR1B Register
	 */
}
/****************************************************************************************************************/
 u16_t  Icu_getInputCaptureValue(void){

	 return MTIMER_ICR1;

}
/******************************************** STOPPING ICU DRIVER  ********************************************************************/
void Icu_DeInit(void){

	MTIMER_TCCR1A=0;
	MTIMER_TCCR1B=0;

	MTIMER_TCNT1=0;
	MTIMER_OCR1A=0;
	MTIMER_OCR1B=0;
	MTIMER_ICR1=0;

	MTIMER_TIMSK=(0<<5);
/* clear  the bit responsible for the interrupt enable */
	/* Disable the icu driver  */
}

/****************************************************************************************************************/
 void  Icu_clearTimerValue(void){
	 MTIMER_TCNT1=0;
}

/***********************************************************************************************************************/

 void RegisterCallback (u8_t function_id, CallbackFunc_t  p_callback_func ) {

 	 func_register[function_id] = p_callback_func;
  }
/* insert the required callback function in the pointer to function --> func_register[function_id]    */
