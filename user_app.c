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

static u8 UserApp_au8sinTable[] =
{
    0x80,0x83,0x86,0x89,0x8c,0x8f,0x92,0x95,0x98,0x9b,0x9e,0xa2,0xa5,0xa7,0xaa,0xad,
    0xb0,0xb3,0xb6,0xb9,0xbc,0xbe,0xc1,0xc4,0xc6,0xc9,0xcb,0xce,0xd0,0xd3,0xd5,0xd7,
    0xda,0xdc,0xde,0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xeb,0xed,0xee,0xf0,0xf1,0xf3,0xf4,
    0xf5,0xf6,0xf8,0xf9,0xfa,0xfa,0xfb,0xfc,0xfd,0xfd,0xfe,0xfe,0xfe,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xfe,0xfe,0xfe,0xfd,0xfd,0xfc,0xfb,0xfa,0xfa,0xf9,0xf8,0xf6,
    0xf5,0xf4,0xf3,0xf1,0xf0,0xee,0xed,0xeb,0xea,0xe8,0xe6,0xe4,0xe2,0xe0,0xde,0xdc,
    0xda,0xd7,0xd5,0xd3,0xd0,0xce,0xcb,0xc9,0xc6,0xc4,0xc1,0xbe,0xbc,0xb9,0xb6,0xb3,
    0xb0,0xad,0xaa,0xa7,0xa5,0xa2,0x9e,0x9b,0x98,0x95,0x92,0x8f,0x8c,0x89,0x86,0x83,
    0x80,0x7c,0x79,0x76,0x73,0x70,0x6d,0x6a,0x67,0x64,0x61,0x5d,0x5a,0x58,0x55,0x52,
    0x4f,0x4c,0x49,0x46,0x43,0x41,0x3e,0x3b,0x39,0x36,0x34,0x31,0x2f,0x2c,0x2a,0x28,
    0x25,0x23,0x21,0x1f,0x1d,0x1b,0x19,0x17,0x15,0x14,0x12,0x11,0x0f,0x0e,0x0c,0x0b,
    0x0a,0x09,0x07,0x06,0x05,0x05,0x04,0x03,0x02,0x02,0x01,0x01,0x01,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x02,0x02,0x03,0x04,0x05,0x05,0x06,0x07,0x09,
    0x0a,0x0b,0x0c,0x0e,0x0f,0x11,0x12,0x14,0x15,0x17,0x19,0x1b,0x1d,0x1f,0x21,0x23,
    0x25,0x28,0x2a,0x2c,0x2f,0x31,0x34,0x36,0x39,0x3b,0x3e,0x41,0x43,0x46,0x49,0x4c,
    0x4f,0x52,0x55,0x58,0x5a,0x5d,0x61,0x64,0x67,0x6a,0x6d,0x70,0x73,0x76,0x79,0x7c
};

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
    
    //Turn on RA7.
    LATA = 0x80;

    //Timer0 on, asynch mode, 16 bit Fosc/4, 1:16 Pre, 1:1 Pro.
    T0CON0 = 0xB0;
    T0CON1 = 0x54;
    
    // Configure DAC1 for Vss and Vdd references, on, and RA2 output
    DAC1CON = 0xa0;
    DAC1DATL = 0x00;
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
    /* // Code to create triangle wave
    static u8 u8Tracker = 0x00; // Tracks what part of the triangle wave to create
    static u8 u8MinValue = 0x00;
    static u8 u8MaxValue = 0xff;
    
    if (u8Tracker == 0x00)
    {
        DAC1DATL += 4; // Increment DAC1DATL until max value
        
        if (DAC1DATL == u8MaxValue)
        {
            u8Tracker = 0x01; // Switch to next part of wave
        }
    }
    else if (u8Tracker == 0x01)
    {
        DAC1DATL -= 4; // Decrement DAC1DATL until min value
        
        if (DAC1DATL == u8MinValue)
        {
            u8Tracker = 0x00; // Switch to next part of wave
        }
    }
    */
    
    // Code to create sine wave
    static u8 u8Index = 0x00; // Used to index sinTable
    
    DAC1DATL = UserApp_au8sinTable[u8Index]; // Sets DAC1DATL to the value at index u8Index of the sinTable
    u8Index += 4; // Rolls back over to 0 once max value is reached
    
} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------
 * void TimeXus(INPUT_PARAMETER_)
 * Sets Timer0 to count u16Microseconds_
 * 
 * Requires
 * -Timer0 configured such that each timer tick is 1 microsecond
 * -INPUT_PARAMETER_is the value in microseconds to time from 1 to 65535
 * Promises:
 * -Pre-loads TMR0H:L to clock out desired period
 * -TMR0IF cleared
 * -Timer0 enabled*/
void TimeXus(u16 u16TimeXus)
{
    /* Disable the timer during config */
    T0CON0 = T0CON0 & 0x7F;
    
    /* Preload TMR0H and TMR0L based on u16TimeXus */
    TMR0H = (u8)(0x00FF - (u16TimeXus & 0xFF00) / 0x100);
    TMR0L = (u8)(0x00FF - u16TimeXus & 0xFF);
    
    /* Clear TMR0IF and enable Timer 0 */
    PIR3 = PIR3 & 0x7F;
    T0CON0 = T0CON0 | 0x80;
} /* end TimeXus () */

/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
