/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{
    TRISA = 0x00; // I/O selection
    LATA = 0x80; // IO Input/Output
    ANSELA = 0x00; // Digital/Analog Selector
    
    T0CON0 = 0xB0;
    T0CON1 = 0x54;

} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
    if (PORTA <= 0xBF) /* Check if counter is less than maximum value */
    {
        PORTA += 1; /* Binary increment counter */
    }
    else /* Executes if counter is greater than maximum value */
    {
        PORTA = 0x80; /* Reset all ports to 0 except pin 7 */
    }
    
    u32 u32Counter = 0;
    
    while(u32Counter < 200000)
    {
        u32Counter ++;
    } /* End of while loop delay */

} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
void TimeXus(INPUT_PARAMETER_)
Sets Timer0 to count u16Microseconds_

Requires:
-Timer0 configured such that each timer tick is 1 microsecond
-INPUT_PARAMETER_ is the value in microseconds to time from 1 to 65535

Promises:
-Pre-loads TMR0H:L to clock out desired period
- TMR0IF cleared
- Timer0 enabled
 */

void TimeXus(u16 u16TimerValue_)
{
    T0CON0 &= 0x7f; //Turns Timer off
    
    TMR0H = (u8)(0x00ff - ((0xff00 & u16TimerValue_) >> 8));
    TMR0L = (u8)(0x00ff - (u16TimerValue_ & 0x00ff));
    
    PIR3 &= 0x7f; //Clears TMR0IF   
            
    T0CON0 |= 0x80; //Turns timer back on
}  /* end TimeXus () */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
