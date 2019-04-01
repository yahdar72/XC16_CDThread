////////////////////////////////////////////////////////////////////////////
////        (C) Copyright Dario Cortese                                 ////
//// This source code may only be used by Dario Cortese licensed users  ////
//// This source code may only be distributed to Dario Cortese licensed ////
//// users.  No other use, reproduction  or distribution is permitted   ////
//// without written permission.                                        ////
////                                                                    ////
//// Author: Dario Cortese                                              ////

//// User: Dario Cortese                                                ////
//// Created on 27/01/2012                                              ////
//// Modify on 28/02/2019 to be adapted at CCS compiler                 ////
//// File: cdevents.h                                                   ////
//// Description:                                                       ////
////    This file has the functions prototypes and data definitions     ////
////    to manage software events types                                 ////  
////////////////////////////////////////////////////////////////////////////
#ifndef __CDEVENTS_H_
#define __CDEVENTS_H_

#ifdef DOXYGEN
    #define section( YY )
#endif

#include "CD_types.h"

//if following is defined then cdevent_t has the ptrParam and is possible to use also
// cdeventSetParamPointer and cdeventGetParamPointer to pass information with the event
//but this use resource so is possible to disable
//#define CDEVENT_USE_PTRPARAM

#ifdef CDEVENT_USE_PTRPARAM
typedef struct cdevent_t_tag{
   sint_t Enabled;   //!< indicates if true that the event is usable (if false and active=true however the isActive function return false) 
//   sint_t Active;      //!< indicates if the event is happened, this flag must be resetted (=false) by the event consumer/manager
//   sint_t Id;         //!< optional, indicates a number that identify the event of the same type (used in events array)
   unsigned int Counter;      //!< indicates the number of times that event is happened before kill him (when killed this counter resets)   
   void* ptrParam;   //!< optional, is a pointer to static memory that point to a primitive data or struct (user data) that must be used to pass a parameter to event consumer/manager
}cdevent_t;
#else //CDEVENT_USE_PTRPARAM
typedef struct cdevent_t_tag{
   sint_t Enabled;   //!< indicates if true that the event is usable (if false and active=true however the isActive function return false) 
   unsigned int Counter;      //!< indicates the number of times that event is happened before kill him (when killed this counter resets)   
}cdevent_t;

#endif //ELSE CDEVENT_USE_PTRPARAM


///*! \def cdeventInit( XyX,YxY)
//   inits the event, this means that is enabled but not activated and the id is set to pEvtId with param pointer to null (0); y is the id number (int) for this event
//   \n param XyX is the event structure
//   \n param YxY is the event id number; 
//   \todo test it   
//*/
//#define cdeventInit(XyX,YxY)  XyX.Enabled= TRUE ; XyX.Active= FALSE ; XyX.Id=( YxY ); XyX.ptrParam=0

#ifdef CDEVENT_USE_PTRPARAM

/*! \def cdeventInit( XyX)
   inits the event, this means that is enabled but not activated and the id is set to pEvtId with param pointer to null (0); y is the id number (int) for this event
   \n param XyX is the event structure
   \todo test it   
*/
#define cdeventInit(XyX)  XyX.Enabled= TRUE ; XyX.Counter=0 ; XyX.ptrParam=0
//#define cdeventInit(XyX)  XyX.Enabled= TRUE ; XyX.Active= FALSE ; XyX.Counter=0 ; XyX.ptrParam=0

#else //CDEVENT_USE_PTRPARAM

/*! \def cdeventInit( XyX)
   inits the event, this means that is enabled but not activated and the id is set to pEvtId with param pointer to null (0); y is the id number (int) for this event
   \n param XyX is the event structure
   \todo test it   
*/
#define cdeventInit(XyX)  XyX.Enabled= TRUE ; XyX.Counter=0

#endif //else CDEVENT_USE_PTRPARAM


/*! \def cdeventGenerate(XyX)
   activate the event, pratically increment counter, but doesn't change Enabled, so if enabled is false then the event remains inactive untile Enabled became true 
   \n param XyX is the event structure
   \todo test it   
*/
#define cdeventGenerate(XyX) if( XyX.Enabled ){ if( XyX.Counter < 255 ) XyX.Counter++; } 
//#define cdeventGenerate(XyX) if( XyX.Enabled ){ XyX.Active= TRUE ; if( XyX.Counter < 255 ) XyX.Counter++; } 
//#define cdeventGenerate(XyX) XyX.Active= TRUE


/*! \def cdeventKill(XyX)
   deactivate the event, pratically set reduce the counter 
   \n param XyX is the event structure
   \todo test it   
*/
#define cdeventKill(XyX) if( XyX.Counter > 0 ) { XyX.Counter-- ;} 
//#define cdeventKill(XyX) XyX.Active= FALSE; XyX.Counter=0
//#define cdeventKill(XyX) XyX.Active= FALSE

/*! \def cdeventDestroy(XyX)
   deactivate the event, pratically set counter to 0
   \n param XyX is the event structure
   \todo test it   
*/
#define cdeventDestry(XyX) XyX.Counter = 0 

/*! \def cdeventEnable(XyX)
   Enable the event, pratically set Enable at true, but doesn't change Active, if Active is true the event became immediately active, otherwise the event remains inactive untile Active became true 
   \n param XyX is the event structure
   \todo test it   
*/
#define cdeventEnable(XyX) XyX.Enabled= TRUE

/*! \def cdeventDisable(XyX)
   Disable the event, pratically set Enable at false, but doesn't change Active, if Active is true the event became immediately inactive, until it return enabled
   \n param XyX is the event structure
   \todo test it   
*/
#define cdeventDisable(XyX) XyX.Enabled= FALSE

/*! \def cdeventIsOccurred(XyX)
   checks if event is occurred (was generated); the event must be Enabled to happen. It will be active, if was generated, when will return TRUE
   \n param XyX is the event structure
   \return TRUE if event occurred, FALSE if not
*/
#define cdeventIsOccurred(XyX) ( XyX.Counter > 0 )   
#define cdeventIsActive(XyX) ( XyX.Counter > 0 )   
//#define cdeventIsOccurred(XyX) (XyX.Active)   
//#define cdeventIsActive(XyX) (XyX.Active)   
//#define cdeventIsActive(XyX) ((XyX.Enabled) && (XyX.Active))   

/*! \def cdeventIsNotOccurred(XyX)
   checks if event is not occurred (not generated, previously killed); It will be active, if was generated, when will return TRUE
   \n param XyX is the event structure
   \return TRUE if event occurred, FALSE if not
*/
#define cdeventIsNotOccurred(XyX) ( XyX.Counter == 0 )   
#define cdeventIsInactive(XyX) ( XyX.Counter == 0 )   

///*! \def cdeventGetId(XyX)
//   read the id of the event; XyX is the event_struct variable 
//   \n param XyX is the event structure
//   \todo test it   
//*/
//#define cdeventGetId(XyX) (XyX.Id)
/*! \def cdeventGetCounter(XyX)
   return the Number of times (max 127)that is happened the event when enabled and before to be killed; XyX is the event_struct variable 
   \n param XyX is the event structure
   \todo test it   
*/
#define cdeventGetCounter(XyX) (XyX.Counter)


#ifdef CDEVENT_USE_PTRPARAM
/*! \def cdeventSetParamPointer(XyX,YxY)
   set the ptrParam of event to YxY that must be a pointer; XyX is the event_struct variable 
   \n param XyX is the event structure
   \n param YxY is the memory pointer to param data; the structure of data depends by event and must be knowed by event user 
   \todo test it   
*/
#define cdeventSetParamPointer(XyX,YxY) XyX.ptrParam=(void*)(YxY)

/*! \def cdeventGetParamPointer(XyX)
	get the ptrParam of event, return a void pointer; xx is the event_struct variable 
   \n param XyX is the event structure
   \todo test it   
*/
#define cdeventGetParamPointer(XyX) (XyX.ptrParam)
#endif //CDEVENT_USE_PTRPARAM


#endif //__CDEVENTS_H_
