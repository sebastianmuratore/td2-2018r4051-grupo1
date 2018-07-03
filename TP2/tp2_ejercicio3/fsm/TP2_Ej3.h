
#ifndef TP2_EJ3_H_
#define TP2_EJ3_H_

#include "sc_types.h"
		
#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'TP2_Ej3'.
*/

/*! Enumeration of all states */ 
typedef enum
{
	TP2_Ej3_main_region_Secuencia,
	TP2_Ej3_main_region_Secuencia__region0__1,
	TP2_Ej3_main_region_Secuencia__region0__2,
	TP2_Ej3_main_region_Secuencia__region0__3,
	TP2_Ej3_main_region_Secuencia__region0__4,
	TP2_Ej3_main_region_Secuencia__region0__5,
	TP2_Ej3_main_region_Secuencia__region0__7,
	TP2_Ej3_main_region_Secuencia__region0__6,
	TP2_Ej3_main_region_Pausado,
	TP2_Ej3_last_state
} TP2_Ej3States;

/*! Type definition of the data structure for the TP2_Ej3Internal interface scope. */
typedef struct
{
	sc_boolean evPausar_raised;
	sc_boolean evReanudar_raised;
	sc_boolean vaInvertido;
	sc_boolean evTiempo_raised;
} TP2_Ej3Internal;

/*! Type definition of the data structure for the TP2_Ej3TimeEvents interface scope. */
typedef struct
{
	sc_boolean tP2_Ej3_tev0_raised;
} TP2_Ej3TimeEvents;


/*! Define dimension of the state configuration vector for orthogonal states. */
#define TP2_EJ3_MAX_ORTHOGONAL_STATES 1
	/*! Define dimension of the state configuration vector for history states. */
#define TP2_EJ3_MAX_HISTORY_STATES 1

/*! 
 * Type definition of the data structure for the TP2_Ej3 state machine.
 * This data structure has to be allocated by the client code. 
 */
typedef struct
{
	TP2_Ej3States stateConfVector[TP2_EJ3_MAX_ORTHOGONAL_STATES];
	TP2_Ej3States historyVector[TP2_EJ3_MAX_HISTORY_STATES];
	sc_ushort stateConfVectorPosition; 
	
	TP2_Ej3Internal internal;
	TP2_Ej3TimeEvents timeEvents;
} TP2_Ej3;

/*! Initializes the TP2_Ej3 state machine data structures. Must be called before first usage.*/
extern void tP2_Ej3_init(TP2_Ej3* handle);

/*! Activates the state machine */
extern void tP2_Ej3_enter(TP2_Ej3* handle);

/*! Deactivates the state machine */
extern void tP2_Ej3_exit(TP2_Ej3* handle);

/*! Performs a 'run to completion' step. */
extern void tP2_Ej3_runCycle(TP2_Ej3* handle);

/*! Raises a time event. */
extern void tP2_Ej3_raiseTimeEvent(const TP2_Ej3* handle, sc_eventid evid);

extern void tP2_Ej3_invertirSecuencia(TP2_Ej3* fsm);
extern void tP2_Ej3_raise_evReanudar(TP2_Ej3* fsm);
extern void tP2_Ej3_raise_evPausar(TP2_Ej3* fsm);

/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean tP2_Ej3_isActive(const TP2_Ej3* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean tP2_Ej3_isFinal(const TP2_Ej3* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean tP2_Ej3_isStateActive(const TP2_Ej3* handle, TP2_Ej3States state);

#ifdef __cplusplus
}
#endif 

#endif /* TP2_EJ3_H_ */
