/******************************************************************************************************/
/* Name   : ultrasonic.c                                                                                     */
/* Author : Madonna Magdy                                                                             */
/* Version: V2                                                                                        */
/* Usage  : This module contains the implementation for the ultasonic driver functions                 */
/******************************************************************************************************/

/********************************************  Includes  ***************************************************************************/
#include "mdio.h"
#include"timer.h"
#include "ultrasonic.h"
/********************************************  GLOBAL STATIC VARIABLES  ***************************************************************************/
u8_t static g_edgeCount = 0;
u16_t static g_timeHigh = 0;
/********************************************  STATIC FUNCTION  ***************************************************************************/
/* static function because the application layer is not allowed to call it
 * the register callback function is initialized with the Ultrasonic_edgeProcessing */
void static Ultrasonic_edgeProcessing(void){
	g_edgeCount++;
		if(1 == g_edgeCount)
		{

	        (Icu_clearTimerValue)();

	        (Icu_setEdgeDetectionType)(FALLING);/* the timer will give interrupt at the next falling edge*/
		}

		else if(2 == g_edgeCount){

			g_timeHigh =(Icu_getInputCaptureValue)();/* time of a half cycle of an ultra-sonic wave */

			(Icu_setEdgeDetectionType)(RISING);/* the timer will give interrupt at the rising falling edge*/

		}


}
/********************************************INITIALIZATION  ***************************************************************************/
void  Ultrasonic_init(void)
{
	DelayTimer_8bits_Init ( &delayTimer2_micro , TIMER2_INDEX_ARRAY);
	/* initialize the timer delay function. It is not preferable to initialize it at the application layer
	 * because it is not preferable that the application layer calls the MCAL directly*/

	/*choose the delay time with micro-seconds configurations because the trigger pin will need
	 * a pulse of 10 micro-seconds only*/

	 mdio_setPinStatus(Trigger_Port, Trigger_Pin, DIO_OUTPUT_PIN);
	 mdio_setPinStatus(Echo_Port, Echo_Pin, DIO_INPUT_FLOAT_PIN);

	 Icu_init(&ICU_signalMeasurement);
	/* initialize the ICU driver. It is not preferable to initialize it at the application layer
	 *because it is not preferable that the application layer calls the MCAL directly*/

	 RegisterCallback (TIMER1_CAPT, Ultrasonic_edgeProcessing );
     /*register the edge processing function to func_register[TIMER1_CAPT] */

	 }
 /********************************************  STATIC INLINE FUNCTION ***************************************************************************/
/* The ultra-sonic trigger is an inline function because it is
 * small in size so we can make text replacement and no need
 * to make context switching
 * add to this, it is called once by Ultrasonic_readDistance so it will not increase the code size
 * it is static because it is called by the ultra-sonic trigger
 * there is no need for the user to call it */
  void static inline  Ultrasonic_Trigger(void)
 {

	 mdio_setPinValue(Trigger_Port, Trigger_Pin, DIO_HIGH_OUTPUT);

	 DelayTimer_8bits_synchrounous( _10_micro_sec, TIMER2_INDEX_ARRAY); /* delay 10 micro-second with timer2*/

	 mdio_setPinValue(Trigger_Port, Trigger_Pin, DIO_LOW_OUTPUT);

 }
/******************************************** READING DISTANCE ***************************************************************************/
u16_t  Ultrasonic_readDistance(void){

	//u32_t static  period;
	//u16_t static distance; /* if the variable (distance and period) is not static
	                         //and initialized with zero the lcd
	                         //will blink with zero and another value  */

	Ultrasonic_Trigger(); /* inline function */

	if( 2 == g_edgeCount){

		g_edgeCount = 0;  /* the edge count must be zero again to calculate a new time period
		                      if it is not returned zero again then the time period will not
		                      be changed      */
	  }

	//distance = period/58.8;

    return g_timeHigh/58.8;
}
/********************************************* END OF FILE **************************************************************************/

