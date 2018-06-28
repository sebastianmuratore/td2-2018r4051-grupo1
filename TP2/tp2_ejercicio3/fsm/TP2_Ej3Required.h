
#ifndef TP2_EJ3REQUIRED_H_
#define TP2_EJ3REQUIRED_H_

#include "sc_types.h"
#include "TP2_Ej3.h"

#ifdef __cplusplus
extern "C"
{
#endif 

/*! \file This header defines prototypes for all functions that are required by the state machine implementation.

This is a state machine uses time events which require access to a timing service. Thus the function prototypes:
	- tP2_Ej3_setTimer and
	- tP2_Ej3_unsetTimer
are defined.

This state machine makes use of operations declared in the state machines interface or internal scopes. Thus the function prototypes:
	- tP2_Ej3Iface_opLed
are defined.

These functions will be called during a 'run to completion step' (runCycle) of the statechart. 
There are some constraints that have to be considered for the implementation of these functions:
	- never call the statechart API functions from within these functions.
	- make sure that the execution time is as short as possible.
 
*/
extern void tP2_Ej3Iface_opLed(const TP2_Ej3* handle, const sc_integer Led, const sc_boolean State);



/*!
 * This is a timed state machine that requires timer services
 */ 

/*! This function has to set up timers for the time events that are required by the state machine. */
/*! 
	This function will be called for each time event that is relevant for a state when a state will be entered.
	\param evid An unique identifier of the event.
	\time_ms The time in milli seconds
	\periodic Indicates the the time event must be raised periodically until the timer is unset 
*/
extern void tP2_Ej3_setTimer(TP2_Ej3* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic);

/*! This function has to unset timers for the time events that are required by the state machine. */
/*! 
	This function will be called for each time event taht is relevant for a state when a state will be left.
	\param evid An unique identifier of the event.
*/
extern void tP2_Ej3_unsetTimer(TP2_Ej3* handle, const sc_eventid evid);



#ifdef __cplusplus
}
#endif 

#endif /* TP2_EJ3REQUIRED_H_ */
