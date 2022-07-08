
/*********************************************************************************************/
/* Name: timer_config.c                                                                      */
/* Author: Madonna Magdy                                                                     */
/* Version: V4                                                                               */
/* Usage: This module contains the implementation for the timer peripheral configurations    */
/*********************************************************************************************/


/************************************************************************/
/*                           Includes                                   */
/************************************************************************/

#include "timer_config.h"


/* The frequency of the delay mode will be FCPU/MTIMER_PRESCALER_8 ---> 1MHZ
 * for the delay mode the tick time wil be 1micro-second
 * 1micro-second*100 = 1ms
 */
DelayMode_8bit_Config_t  delayTimer0_milli=
{
		MTIMER_PRESCALER_8,
		0,    /* ---> initial value*/
		100,  /* ---> compare value*/

};



/* The frequency of the delay mode will be 8MHZ no pre-scaling
 * for the delay mode the tick time wil be 0.03125 micro-second
 *  0.03125*32= 1 micro-second
 */
DelayMode_8bit_Config_t delayTimer0_micro=
{
		MTIMER_PRESCALER_1,
		0,    /* ---> initial value*/
		32,  /* ---> compare value*/



};



/* The frequency of the delay mode will be FCPU/MTIMER_PRESCALER_8 ---> 1MHZ
 * for the delay mode the tick time wil be 1micro-second
 * 1micro-second*100 = 1ms
 */
DelayMode_8bit_Config_t  delayTimer2_milli=
{
		MTIMER_PRESCALER_8,
		0,    /* ---> initial value*/
		100,  /* ---> compare value*/

};


/* The frequency of the delay mode will be 8MHZ no pre-scaling
 * for the delay mode the tick time wil be 0.03125 micro-second
 *  0.03125*32= 1 micro-second
 */
DelayMode_8bit_Config_t delayTimer2_micro=
{
		MTIMER_PRESCALER_1,
		0,    /* ---> initial value*/
		32,  /* ---> compare value*/

};



ICU_Config_t   ICU_signalMeasurement=
{
		RISING, MTIMER_PRESCALER_8

};




