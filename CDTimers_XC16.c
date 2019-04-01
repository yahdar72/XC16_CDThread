////////////////////////////////////////////////////////////////////////////
////        (C) Copyright Dario Cortese                                 ////
//// This source code may only be used by Dario Cortese licensed users  ////
//// This source code may only be distributed to Dario Cortese licensed ////
//// users.  No other use, reproduction  or distribution is permitted   ////
//// without written permission.                                        ////
////                                                                    ////
//// Author: Dario Cortese                                              ////
//// Created on 26/08/2012                                              ////
//// Modify on 12/05/2018 to be adapted at XC8 compiler                 ////
//// File: cdtimers.c                                                   ////
//// Description:                                                       ////
//// THIS FILE HAS ALL IMPLEMENTATION OF FUNCTIONS USED FOR CDTIMERS    ////
////   MANAGING; TIMERS ARE USED WITH CDTHREAD, AND VICEVERSA           ////        
////////////////////////////////////////////////////////////////////////////

#ifndef _CDTIMERS_C_
#define _CDTIMERS_C_

#include "../OthSyInf.h"
#include "CDThread.h"




//enable this define if you want that will be stored 8 time-stamp in cdtimer_GetTicks
//#define _CDTIMERS_DEBUG_

cdTimerID Absolute_timer;


#ifdef _CDTIMERS_DEBUG_
    unsigned int Tim4idx=0;
    unsigned int8 Tim4Vals[8];
#endif

uint16_t _getTicks_prev_TMR = 0;
    


/*! \fn  void Update_Absolute_Timer()
    \author Dario Cortese
    \date 2019-01-22
    \brief update the value counting of absolute timer by the difference of actual tim0 value and last call calue
    \note call often this function to be sure to not lost timer ticks
    \version 1.00
*/
void Update_Absolute_Timer(){
    //one secondo is 118750 ticks of timer1; 
    //TIM1 Period = 0.551850993 s; Frequency = 30401250 Hz; PR1 65535; 
    uint16_t act_TMR;
    uint16_t delta;

    //act_TMR = TMR1_Counter16BitGet();
    act_TMR = TMR1 ;
    if( act_TMR < _getTicks_prev_TMR ){
        delta = PR1;
        delta -= _getTicks_prev_TMR;
        delta += act_TMR;
    }else{
    //if( act_TMR >= _getTicks_prev_TMR ){
        delta = act_TMR;
        delta -= _getTicks_prev_TMR; //now is delta ticks
    }
    //add delta to global u32_SysTicks
    Absolute_timer += delta;
    _getTicks_prev_TMR = act_TMR;

#ifdef _CDTIMERS_DEBUG_
    Tim4Vals[Tim4idx]=act_TMR;
    Tim4idx++;
    if (Tim4idx>7)
        Tim4idx=0;
#endif

}


/*! \void Set_Absolute_Timer( cdTimerID pval )
    \author Dario Cortese
    \date 2019-01-22
    \brief set the value counting of absolute timer avoid tick counting error when is called Update_Absolute_Timer
    \param pval is cdTimerID type value to set the Absolute_timer global variable 
    \version 1.00
*/
void Set_Absolute_Timer( cdTimerID pval ){
//    uint16_t u16appo;
    //update global timer
    //u16appo = TMR1_ReadTimer();
    //_getTicks_prev_TMR = TMR1_Counter16BitGet(); //as is TMR1
    _getTicks_prev_TMR = TMR1;
    Absolute_timer = pval;
}



/*! \fn  void ForceTim0Value( uint16_t tvalue )
    \author Dario Cortese
    \date 2019-01-22
    \brief update the value of tim1 and update internal register to avoid tick errors when will be call the Update_Absolute_Timer  
    \param tvalue is the value to set tim1 (remember that isr happen at ((0xFFFF - tvalue)+1)
    \version 1.00
*/
void ForceTim1Value( uint16_t tvalue ){
    uint16_t u16_appo;
    
    //TMR1_StopTimer();
    TMR1_Stop();
    Update_Absolute_Timer();
    //TMR1_WriteTimer( tvalue );
    
    if( TMR1 > _getTicks_prev_TMR ){
        u16_appo =  (uint16_t)TMR1;
        u16_appo -= (uint16_t)_getTicks_prev_TMR ;
    }else{
        u16_appo = PR1;
        u16_appo -= _getTicks_prev_TMR;
        u16_appo += TMR1;
    }
    TMR1 = tvalue;
    _getTicks_prev_TMR = tvalue;
    Absolute_timer += u16_appo  ;      

    TMR1_Start();
}



/*! \fn void cdtimer_INIT()
   \author Dario Cortese
   \date 15-03-2019
   \brief this function is called by main setup to initialize the time counter (one of the timers available in the microcontroller) in polling mode (NO ISR)
   \return none
   \warning this function must be redefined on different hardware or implementation
   \version 1.00
   \see cdtimer_GetTicks
*/
void cdtimer_INIT(){
    //intialize timer 4 as
    //#use timer(timer=4,tick=1000us,bits=32,NOISR)
    //prev_TMR = 0 ;
    _getTicks_prev_TMR = TMR1 ;
    Absolute_timer = 0;
}


#endif //_CDTIMERS_C_

