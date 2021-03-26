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
    LATA = 0x80; // Initialize pin values
    ANSELA = 0x00; // Digital/Analog Selector
    
    T0CON0 = 0x90;
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
    static u32 u32DelayCounter = 0;
    u32DelayCounter++;
    
    if (u32DelayCounter == 150) // Runs every 150 times UserAppRun is called (1ms delay every time, 150ms total)
        {
        static u16 u16PatternIndex = 0;
        u32DelayCounter = 0;
        u8 au8Pattern[6] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20}; // Various LED patterns to cycle through

        u8 u8LATATemporary = LATA; // Store value of LATA into temporary 8 bit variable

        u8LATATemporary &= 0xC0; // Mask out 6 LSB's from LATATemporary

        u8LATATemporary |= au8Pattern[u16PatternIndex]; // Update 6 LSB's with a certain value to LATATemporary

        LATA = u8LATATemporary; // Update the value of LATA with the new value in LATATemporary

        if (u16PatternIndex < 5)
        {
            u16PatternIndex++;
        }
        else
            u16PatternIndex = 0;
    }
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
    T0CON0 &= 0x7f; // Turns Timer off during config
    
    /* Preload TMR0H and TMR0L based on u16TimerValue_*/
    TMR0H = (u8)(0x00ff - ((0xff00 & u16TimerValue_) >> 8));
    TMR0L = (u8)(0x00ff - (u16TimerValue_ & 0x00ff));
    PIR3 &= 0x7f; //Clears TMR0IF   
            
    T0CON0 |= 0x80; // Turns timer on
}  /* end TimeXus () */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
