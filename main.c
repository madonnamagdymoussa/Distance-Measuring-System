/************************************************************************************/
/* Name: main.c                                                                     */
/* Author: Madonna Magdy                                                            */
/* Version: V1                                                                      */

/************************************************************************************/

/********************************  Includes  *******************************************************************************************/
#include "ultrasonic.h"
#include "lcd.h"
/****************************************************************************************************************************************/
int main(){

 #define F_CPU 8000000UL

	u16_t distance;


	     LCD_init();        /*initialize the lcd driver   */
	 	 LCD_clearScreen(); /* clear LCD at the beginning */

	 	 LCD_displayStringRowColumn(0,0, "Distance= "); /* this value will be displayed during the whole program  */
	 	 LCD_displayStringRowColumn(0,14, "cm");  /* this value will be displayed during the whole program  */

	 	 Ultrasonic_init(); /*initialize the ultra-sonic driver   */

        //# define sei()  __asm__ __volatile__ ("sei" ::: "memory") /* Enabling the global interrupt */

/********************************************************************************/

	 for( ;  ;){


		 distance= Ultrasonic_readDistance(); /*continuously  reading the distance measured by the ultra-sonic  */


		 LCD_moveCursor(0,10);
		 LCD_intgerToString(distance); /* Display the current temperature  */


		 if ((distance<10)){

        	LCD_displayStringRowColumn(0,11, "   ");
        }

        else if ((distance>10)&&(distance<100)){

        	LCD_displayStringRowColumn(0,12, "  ");
        }



	}/****************************************************************************************************************************************/

}
/**************************************** END OF MAIN ************************************************************************************************/

