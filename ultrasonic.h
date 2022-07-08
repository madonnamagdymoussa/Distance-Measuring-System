/******************************************************************************************************/
/* Name   : ultrasonic.h                                                                                     */
/* Author : Madonna Magdy                                                                             */
/* Version: V2                                                                                        */
/* Usage  : This module contains the interface definitions of the ultra-sonic driver                 */
/******************************************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include"mdio.h"

/***************************************    ENUM  *************************************************************************************************/
typedef enum{
	Trigger_Pin = PIN5_ID,
	Trigger_Port= PORTB_ID,

	Echo_Pin = PIN6_ID,
	Echo_Port = PORTD_ID,

}UltraSonic_Trigger_Echo_t;
/***********************************************FUNCTION PROTOTYPE*****************************************************************************************/
void  Ultrasonic_init(void); /* initialize the ultra-sonic driver */
/****************************************************************************************************************************************/
/* FunctionID    : Ultrasonic_readDistance
 *
 * Description : This function is responsible for calculating the distance
 *
 *
 *PRE_CONDITION: the ultra-sonic trigger function must be implemented
 *PRE_CONDITION: the edge processing function must be implemented
 *PRE_CONDITION: the ultra-sonic driver must be initialized
 *
 *POST_CONDITION:the distance will be calculated
 *
 * Return: void
 *
 * */
u16_t  Ultrasonic_readDistance(void);

#endif /* ULTRASONIC_H_ */
