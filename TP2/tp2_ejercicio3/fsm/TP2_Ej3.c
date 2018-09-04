
#include <stdlib.h>
#include <string.h>
#include "sc_types.h"
#include "TP2_Ej3.h"
#include "TP2_Ej3Required.h"
/*! \file Implementation of the state machine 'TP2_Ej3'
*/

/* prototypes of all internal functions */
static sc_boolean tP2_Ej3_check__lr0(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Secuencia_tr0_tr0(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__1_tr0_tr0(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__1_tr1_tr1(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__2_tr0_tr0(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__2_tr1_tr1(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__3_tr0_tr0(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__3_tr1_tr1(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__3_tr2_tr2(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__4_tr0_tr0(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__4_tr1_tr1(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__5_tr0_tr0(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__5_tr1_tr1(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__7_tr0_tr0(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__7_tr1_tr1(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__6_tr0_tr0(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__6_tr1_tr1(const TP2_Ej3* handle);
static sc_boolean tP2_Ej3_check_main_region_Pausado_tr0_tr0(const TP2_Ej3* handle);
static void tP2_Ej3_effect__lr0(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Secuencia_tr0(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Secuencia__region0__1_tr0(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Secuencia__region0__1_tr1(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Secuencia__region0__2_tr0(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Secuencia__region0__2_tr1(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Secuencia__region0__3_tr0(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Secuencia__region0__3_tr1(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Secuencia__region0__3_tr2(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Secuencia__region0__4_tr0(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Secuencia__region0__4_tr1(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Secuencia__region0__5_tr0(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Secuencia__region0__5_tr1(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Secuencia__region0__7_tr0(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Secuencia__region0__7_tr1(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Secuencia__region0__6_tr0(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Secuencia__region0__6_tr1(TP2_Ej3* handle);
static void tP2_Ej3_effect_main_region_Pausado_tr0(TP2_Ej3* handle);
static void tP2_Ej3_enact(TP2_Ej3* handle);
static void tP2_Ej3_enact_main_region_Secuencia__region0__1(TP2_Ej3* handle);
static void tP2_Ej3_enact_main_region_Secuencia__region0__2(TP2_Ej3* handle);
static void tP2_Ej3_enact_main_region_Secuencia__region0__3(TP2_Ej3* handle);
static void tP2_Ej3_enact_main_region_Secuencia__region0__4(TP2_Ej3* handle);
static void tP2_Ej3_enact_main_region_Secuencia__region0__5(TP2_Ej3* handle);
static void tP2_Ej3_enact_main_region_Secuencia__region0__7(TP2_Ej3* handle);
static void tP2_Ej3_enact_main_region_Secuencia__region0__6(TP2_Ej3* handle);
static void tP2_Ej3_exact(TP2_Ej3* handle);
static void tP2_Ej3_enseq_main_region_Secuencia_default(TP2_Ej3* handle);
static void tP2_Ej3_enseq_main_region_Secuencia__region0__1_default(TP2_Ej3* handle);
static void tP2_Ej3_enseq_main_region_Secuencia__region0__2_default(TP2_Ej3* handle);
static void tP2_Ej3_enseq_main_region_Secuencia__region0__3_default(TP2_Ej3* handle);
static void tP2_Ej3_enseq_main_region_Secuencia__region0__4_default(TP2_Ej3* handle);
static void tP2_Ej3_enseq_main_region_Secuencia__region0__5_default(TP2_Ej3* handle);
static void tP2_Ej3_enseq_main_region_Secuencia__region0__7_default(TP2_Ej3* handle);
static void tP2_Ej3_enseq_main_region_Secuencia__region0__6_default(TP2_Ej3* handle);
static void tP2_Ej3_enseq_main_region_Pausado_default(TP2_Ej3* handle);
static void tP2_Ej3_enseq_main_region_default(TP2_Ej3* handle);
static void tP2_Ej3_enseq_main_region_Secuencia__region0_default(TP2_Ej3* handle);
static void tP2_Ej3_shenseq_main_region_Secuencia__region0(TP2_Ej3* handle);
static void tP2_Ej3_exseq_main_region_Secuencia(TP2_Ej3* handle);
static void tP2_Ej3_exseq_main_region_Secuencia__region0__1(TP2_Ej3* handle);
static void tP2_Ej3_exseq_main_region_Secuencia__region0__2(TP2_Ej3* handle);
static void tP2_Ej3_exseq_main_region_Secuencia__region0__3(TP2_Ej3* handle);
static void tP2_Ej3_exseq_main_region_Secuencia__region0__4(TP2_Ej3* handle);
static void tP2_Ej3_exseq_main_region_Secuencia__region0__5(TP2_Ej3* handle);
static void tP2_Ej3_exseq_main_region_Secuencia__region0__7(TP2_Ej3* handle);
static void tP2_Ej3_exseq_main_region_Secuencia__region0__6(TP2_Ej3* handle);
static void tP2_Ej3_exseq_main_region_Pausado(TP2_Ej3* handle);
static void tP2_Ej3_exseq_main_region(TP2_Ej3* handle);
static void tP2_Ej3_exseq_main_region_Secuencia__region0(TP2_Ej3* handle);
static void tP2_Ej3_react_main_region_Secuencia__region0__1(TP2_Ej3* handle);
static void tP2_Ej3_react_main_region_Secuencia__region0__2(TP2_Ej3* handle);
static void tP2_Ej3_react_main_region_Secuencia__region0__3(TP2_Ej3* handle);
static void tP2_Ej3_react_main_region_Secuencia__region0__4(TP2_Ej3* handle);
static void tP2_Ej3_react_main_region_Secuencia__region0__5(TP2_Ej3* handle);
static void tP2_Ej3_react_main_region_Secuencia__region0__7(TP2_Ej3* handle);
static void tP2_Ej3_react_main_region_Secuencia__region0__6(TP2_Ej3* handle);
static void tP2_Ej3_react_main_region_Pausado(TP2_Ej3* handle);
static void tP2_Ej3_react_main_region_Secuencia__region0__entry_Default(TP2_Ej3* handle);
static void tP2_Ej3_react_main_region__entry_Default(TP2_Ej3* handle);
static void tP2_Ej3_clearInEvents(TP2_Ej3* handle);
static void tP2_Ej3_clearOutEvents(TP2_Ej3* handle);

const sc_integer TP2_EJ3_TP2_EJ3INTERNAL_CLEDR = 1;
const sc_integer TP2_EJ3_TP2_EJ3INTERNAL_CLEDG = 2;
const sc_integer TP2_EJ3_TP2_EJ3INTERNAL_CLEDB = 3;
const sc_boolean TP2_EJ3_TP2_EJ3INTERNAL_ON = bool_true;
const sc_boolean TP2_EJ3_TP2_EJ3INTERNAL_OFF = bool_false;

void tP2_Ej3_init(TP2_Ej3* handle)
{
	sc_integer i;

	for (i = 0; i < TP2_EJ3_MAX_ORTHOGONAL_STATES; ++i)
	{
		handle->stateConfVector[i] = TP2_Ej3_last_state;
	}
	
	for (i = 0; i < TP2_EJ3_MAX_HISTORY_STATES; ++i)
	{
		handle->historyVector[i] = TP2_Ej3_last_state;
	}
	
	handle->stateConfVectorPosition = 0;

	tP2_Ej3_clearInEvents(handle);
	tP2_Ej3_clearOutEvents(handle);

	/* Default init sequence for statechart TP2_Ej3 */
	handle->internal.vaInvertido = bool_false;

}

void tP2_Ej3_enter(TP2_Ej3* handle)
{
	/* Default enter sequence for statechart TP2_Ej3 */
	tP2_Ej3_enact(handle);
	tP2_Ej3_enseq_main_region_default(handle);
}

void tP2_Ej3_exit(TP2_Ej3* handle)
{
	/* Default exit sequence for statechart TP2_Ej3 */
	tP2_Ej3_exseq_main_region(handle);
	tP2_Ej3_exact(handle);
}

sc_boolean tP2_Ej3_isActive(const TP2_Ej3* handle)
{
	sc_boolean result;
	if (handle->stateConfVector[0] != TP2_Ej3_last_state)
	{
		result =  bool_true;
	}
	else
	{
		result = bool_false;
	}
	return result;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean tP2_Ej3_isFinal(const TP2_Ej3* handle)
{
   return bool_false;
}

static void tP2_Ej3_clearInEvents(TP2_Ej3* handle)
{
	handle->internal.evPausar_raised = bool_false;
	handle->internal.evReanudar_raised = bool_false;
	handle->internal.evTiempo_raised = bool_false;
	handle->timeEvents.tP2_Ej3_tev0_raised = bool_false;
}

static void tP2_Ej3_clearOutEvents(TP2_Ej3* handle)
{
}

void tP2_Ej3_runCycle(TP2_Ej3* handle)
{
	
	tP2_Ej3_clearOutEvents(handle);
	
	for (handle->stateConfVectorPosition = 0;
		handle->stateConfVectorPosition < TP2_EJ3_MAX_ORTHOGONAL_STATES;
		handle->stateConfVectorPosition++)
		{
			
		switch (handle->stateConfVector[handle->stateConfVectorPosition])
		{
		case TP2_Ej3_main_region_Secuencia__region0__1 :
		{
			tP2_Ej3_react_main_region_Secuencia__region0__1(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__2 :
		{
			tP2_Ej3_react_main_region_Secuencia__region0__2(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__3 :
		{
			tP2_Ej3_react_main_region_Secuencia__region0__3(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__4 :
		{
			tP2_Ej3_react_main_region_Secuencia__region0__4(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__5 :
		{
			tP2_Ej3_react_main_region_Secuencia__region0__5(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__7 :
		{
			tP2_Ej3_react_main_region_Secuencia__region0__7(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__6 :
		{
			tP2_Ej3_react_main_region_Secuencia__region0__6(handle);
			break;
		}
		case TP2_Ej3_main_region_Pausado :
		{
			tP2_Ej3_react_main_region_Pausado(handle);
			break;
		}
		default:
			break;
		}
	}
	
	tP2_Ej3_clearInEvents(handle);
}

void tP2_Ej3_raiseTimeEvent(const TP2_Ej3* handle, sc_eventid evid)
{
	if ( ((sc_intptr_t)evid) >= ((sc_intptr_t)&(handle->timeEvents))
		&&  ((sc_intptr_t)evid) < ((sc_intptr_t)&(handle->timeEvents)) + sizeof(TP2_Ej3TimeEvents))
		{
		*(sc_boolean*)evid = bool_true;
	}		
}

sc_boolean tP2_Ej3_isStateActive(const TP2_Ej3* handle, TP2_Ej3States state)
{
	sc_boolean result = bool_false;
	switch (state)
	{
		case TP2_Ej3_main_region_Secuencia :
			result = (sc_boolean) (handle->stateConfVector[0] >= TP2_Ej3_main_region_Secuencia
				&& handle->stateConfVector[0] <= TP2_Ej3_main_region_Secuencia__region0__6);
			break;
		case TP2_Ej3_main_region_Secuencia__region0__1 :
			result = (sc_boolean) (handle->stateConfVector[0] == TP2_Ej3_main_region_Secuencia__region0__1
			);
			break;
		case TP2_Ej3_main_region_Secuencia__region0__2 :
			result = (sc_boolean) (handle->stateConfVector[0] == TP2_Ej3_main_region_Secuencia__region0__2
			);
			break;
		case TP2_Ej3_main_region_Secuencia__region0__3 :
			result = (sc_boolean) (handle->stateConfVector[0] == TP2_Ej3_main_region_Secuencia__region0__3
			);
			break;
		case TP2_Ej3_main_region_Secuencia__region0__4 :
			result = (sc_boolean) (handle->stateConfVector[0] == TP2_Ej3_main_region_Secuencia__region0__4
			);
			break;
		case TP2_Ej3_main_region_Secuencia__region0__5 :
			result = (sc_boolean) (handle->stateConfVector[0] == TP2_Ej3_main_region_Secuencia__region0__5
			);
			break;
		case TP2_Ej3_main_region_Secuencia__region0__7 :
			result = (sc_boolean) (handle->stateConfVector[0] == TP2_Ej3_main_region_Secuencia__region0__7
			);
			break;
		case TP2_Ej3_main_region_Secuencia__region0__6 :
			result = (sc_boolean) (handle->stateConfVector[0] == TP2_Ej3_main_region_Secuencia__region0__6
			);
			break;
		case TP2_Ej3_main_region_Pausado :
			result = (sc_boolean) (handle->stateConfVector[0] == TP2_Ej3_main_region_Pausado
			);
			break;
		default:
			result = bool_false;
			break;
	}
	return result;
}




/* implementations of all internal functions */

static sc_boolean tP2_Ej3_check__lr0(const TP2_Ej3* handle)
{
	return handle->timeEvents.tP2_Ej3_tev0_raised;
}

static sc_boolean tP2_Ej3_check_main_region_Secuencia_tr0_tr0(const TP2_Ej3* handle)
{
	return handle->internal.evPausar_raised;
}

static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__1_tr0_tr0(const TP2_Ej3* handle)
{
	return ((handle->internal.evTiempo_raised) && (handle->internal.vaInvertido == bool_false)) ? bool_true : bool_false;
}

static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__1_tr1_tr1(const TP2_Ej3* handle)
{
	return ((handle->internal.evTiempo_raised) && (handle->internal.vaInvertido == bool_true)) ? bool_true : bool_false;
}

static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__2_tr0_tr0(const TP2_Ej3* handle)
{
	return ((handle->internal.evTiempo_raised) && (handle->internal.vaInvertido == bool_false)) ? bool_true : bool_false;
}

static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__2_tr1_tr1(const TP2_Ej3* handle)
{
	return ((handle->internal.evTiempo_raised) && (handle->internal.vaInvertido == bool_true)) ? bool_true : bool_false;
}

static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__3_tr0_tr0(const TP2_Ej3* handle)
{
	return ((handle->internal.evTiempo_raised) && (handle->internal.vaInvertido == bool_false)) ? bool_true : bool_false;
}

static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__3_tr1_tr1(const TP2_Ej3* handle)
{
	return ((handle->internal.evTiempo_raised) && (handle->internal.vaInvertido == bool_true)) ? bool_true : bool_false;
}

static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__3_tr2_tr2(const TP2_Ej3* handle)
{
	return ((handle->internal.evTiempo_raised) && (handle->internal.vaInvertido == bool_false)) ? bool_true : bool_false;
}

static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__4_tr0_tr0(const TP2_Ej3* handle)
{
	return ((handle->internal.evTiempo_raised) && (handle->internal.vaInvertido == bool_false)) ? bool_true : bool_false;
}

static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__4_tr1_tr1(const TP2_Ej3* handle)
{
	return ((handle->internal.evTiempo_raised) && (handle->internal.vaInvertido == bool_true)) ? bool_true : bool_false;
}

static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__5_tr0_tr0(const TP2_Ej3* handle)
{
	return ((handle->internal.evTiempo_raised) && (handle->internal.vaInvertido == bool_false)) ? bool_true : bool_false;
}

static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__5_tr1_tr1(const TP2_Ej3* handle)
{
	return ((handle->internal.evTiempo_raised) && (handle->internal.vaInvertido == bool_true)) ? bool_true : bool_false;
}

static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__7_tr0_tr0(const TP2_Ej3* handle)
{
	return ((handle->internal.evTiempo_raised) && (handle->internal.vaInvertido == bool_true)) ? bool_true : bool_false;
}

static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__7_tr1_tr1(const TP2_Ej3* handle)
{
	return ((handle->internal.evTiempo_raised) && (handle->internal.vaInvertido == bool_false)) ? bool_true : bool_false;
}

static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__6_tr0_tr0(const TP2_Ej3* handle)
{
	return ((handle->internal.evTiempo_raised) && (handle->internal.vaInvertido == bool_false)) ? bool_true : bool_false;
}

static sc_boolean tP2_Ej3_check_main_region_Secuencia__region0__6_tr1_tr1(const TP2_Ej3* handle)
{
	return ((handle->internal.evTiempo_raised) && (handle->internal.vaInvertido == bool_true)) ? bool_true : bool_false;
}

static sc_boolean tP2_Ej3_check_main_region_Pausado_tr0_tr0(const TP2_Ej3* handle)
{
	return handle->internal.evReanudar_raised;
}

static void tP2_Ej3_effect__lr0(TP2_Ej3* handle)
{
	handle->internal.evTiempo_raised = bool_true;
}

static void tP2_Ej3_effect_main_region_Secuencia_tr0(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Secuencia(handle);
	tP2_Ej3_enseq_main_region_Pausado_default(handle);
}

static void tP2_Ej3_effect_main_region_Secuencia__region0__1_tr0(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Secuencia__region0__1(handle);
	tP2_Ej3_enseq_main_region_Secuencia__region0__2_default(handle);
}

static void tP2_Ej3_effect_main_region_Secuencia__region0__1_tr1(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Secuencia__region0__1(handle);
	tP2_Ej3_enseq_main_region_Secuencia__region0__7_default(handle);
}

static void tP2_Ej3_effect_main_region_Secuencia__region0__2_tr0(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Secuencia__region0__2(handle);
	tP2_Ej3_enseq_main_region_Secuencia__region0__3_default(handle);
}

static void tP2_Ej3_effect_main_region_Secuencia__region0__2_tr1(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Secuencia__region0__2(handle);
	tP2_Ej3_enseq_main_region_Secuencia__region0__1_default(handle);
}

static void tP2_Ej3_effect_main_region_Secuencia__region0__3_tr0(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Secuencia__region0__3(handle);
	tP2_Ej3_enseq_main_region_Secuencia__region0__4_default(handle);
}

static void tP2_Ej3_effect_main_region_Secuencia__region0__3_tr1(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Secuencia__region0__3(handle);
	tP2_Ej3_enseq_main_region_Secuencia__region0__2_default(handle);
}

static void tP2_Ej3_effect_main_region_Secuencia__region0__3_tr2(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Secuencia__region0__3(handle);
	tP2_Ej3_enseq_main_region_Secuencia__region0__4_default(handle);
}

static void tP2_Ej3_effect_main_region_Secuencia__region0__4_tr0(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Secuencia__region0__4(handle);
	tP2_Ej3_enseq_main_region_Secuencia__region0__5_default(handle);
}

static void tP2_Ej3_effect_main_region_Secuencia__region0__4_tr1(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Secuencia__region0__4(handle);
	tP2_Ej3_enseq_main_region_Secuencia__region0__3_default(handle);
}

static void tP2_Ej3_effect_main_region_Secuencia__region0__5_tr0(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Secuencia__region0__5(handle);
	tP2_Ej3_enseq_main_region_Secuencia__region0__6_default(handle);
}

static void tP2_Ej3_effect_main_region_Secuencia__region0__5_tr1(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Secuencia__region0__5(handle);
	tP2_Ej3_enseq_main_region_Secuencia__region0__4_default(handle);
}

static void tP2_Ej3_effect_main_region_Secuencia__region0__7_tr0(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Secuencia__region0__7(handle);
	tP2_Ej3_enseq_main_region_Secuencia__region0__6_default(handle);
}

static void tP2_Ej3_effect_main_region_Secuencia__region0__7_tr1(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Secuencia__region0__7(handle);
	tP2_Ej3_enseq_main_region_Secuencia__region0__1_default(handle);
}

static void tP2_Ej3_effect_main_region_Secuencia__region0__6_tr0(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Secuencia__region0__6(handle);
	tP2_Ej3_enseq_main_region_Secuencia__region0__7_default(handle);
}

static void tP2_Ej3_effect_main_region_Secuencia__region0__6_tr1(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Secuencia__region0__6(handle);
	tP2_Ej3_enseq_main_region_Secuencia__region0__5_default(handle);
}

static void tP2_Ej3_effect_main_region_Pausado_tr0(TP2_Ej3* handle)
{
	tP2_Ej3_exseq_main_region_Pausado(handle);
	tP2_Ej3_enseq_main_region_Secuencia_default(handle);
}

/* Entry action for statechart 'TP2_Ej3'. */
static void tP2_Ej3_enact(TP2_Ej3* handle)
{
	/* Entry action for statechart 'TP2_Ej3'. */
	tP2_Ej3_setTimer(handle, (sc_eventid) &(handle->timeEvents.tP2_Ej3_tev0_raised) , 700, bool_true);
}

/* Entry action for state '1'. */
static void tP2_Ej3_enact_main_region_Secuencia__region0__1(TP2_Ej3* handle)
{
	/* Entry action for state '1'. */
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDR, TP2_EJ3_TP2_EJ3INTERNAL_OFF);
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDG, TP2_EJ3_TP2_EJ3INTERNAL_OFF);
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDB, TP2_EJ3_TP2_EJ3INTERNAL_ON);
}

/* Entry action for state '2'. */
static void tP2_Ej3_enact_main_region_Secuencia__region0__2(TP2_Ej3* handle)
{
	/* Entry action for state '2'. */
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDR, TP2_EJ3_TP2_EJ3INTERNAL_OFF);
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDG, TP2_EJ3_TP2_EJ3INTERNAL_ON);
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDB, TP2_EJ3_TP2_EJ3INTERNAL_OFF);
}

/* Entry action for state '3'. */
static void tP2_Ej3_enact_main_region_Secuencia__region0__3(TP2_Ej3* handle)
{
	/* Entry action for state '3'. */
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDR, TP2_EJ3_TP2_EJ3INTERNAL_OFF);
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDG, TP2_EJ3_TP2_EJ3INTERNAL_ON);
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDB, TP2_EJ3_TP2_EJ3INTERNAL_ON);
}

/* Entry action for state '4'. */
static void tP2_Ej3_enact_main_region_Secuencia__region0__4(TP2_Ej3* handle)
{
	/* Entry action for state '4'. */
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDR, TP2_EJ3_TP2_EJ3INTERNAL_ON);
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDG, TP2_EJ3_TP2_EJ3INTERNAL_OFF);
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDB, TP2_EJ3_TP2_EJ3INTERNAL_OFF);
}

/* Entry action for state '5'. */
static void tP2_Ej3_enact_main_region_Secuencia__region0__5(TP2_Ej3* handle)
{
	/* Entry action for state '5'. */
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDR, TP2_EJ3_TP2_EJ3INTERNAL_ON);
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDG, TP2_EJ3_TP2_EJ3INTERNAL_OFF);
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDB, TP2_EJ3_TP2_EJ3INTERNAL_OFF);
}

/* Entry action for state '7'. */
static void tP2_Ej3_enact_main_region_Secuencia__region0__7(TP2_Ej3* handle)
{
	/* Entry action for state '7'. */
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDR, TP2_EJ3_TP2_EJ3INTERNAL_ON);
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDG, TP2_EJ3_TP2_EJ3INTERNAL_OFF);
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDB, TP2_EJ3_TP2_EJ3INTERNAL_OFF);
}

/* Entry action for state '6'. */
static void tP2_Ej3_enact_main_region_Secuencia__region0__6(TP2_Ej3* handle)
{
	/* Entry action for state '6'. */
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDR, TP2_EJ3_TP2_EJ3INTERNAL_ON);
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDG, TP2_EJ3_TP2_EJ3INTERNAL_OFF);
	tP2_Ej3Iface_opLed(handle, TP2_EJ3_TP2_EJ3INTERNAL_CLEDB, TP2_EJ3_TP2_EJ3INTERNAL_OFF);
}

/* Exit action for state 'TP2_Ej3'. */
static void tP2_Ej3_exact(TP2_Ej3* handle)
{
	/* Exit action for state 'TP2_Ej3'. */
	tP2_Ej3_unsetTimer(handle, (sc_eventid) &(handle->timeEvents.tP2_Ej3_tev0_raised) );		
}

/* 'default' enter sequence for state Secuencia */
static void tP2_Ej3_enseq_main_region_Secuencia_default(TP2_Ej3* handle)
{
	/* 'default' enter sequence for state Secuencia */
	tP2_Ej3_enseq_main_region_Secuencia__region0_default(handle);
}

/* 'default' enter sequence for state 1 */
static void tP2_Ej3_enseq_main_region_Secuencia__region0__1_default(TP2_Ej3* handle)
{
	/* 'default' enter sequence for state 1 */
	tP2_Ej3_enact_main_region_Secuencia__region0__1(handle);
	handle->stateConfVector[0] = TP2_Ej3_main_region_Secuencia__region0__1;
	handle->stateConfVectorPosition = 0;
	handle->historyVector[0] = handle->stateConfVector[0];
}

/* 'default' enter sequence for state 2 */
static void tP2_Ej3_enseq_main_region_Secuencia__region0__2_default(TP2_Ej3* handle)
{
	/* 'default' enter sequence for state 2 */
	tP2_Ej3_enact_main_region_Secuencia__region0__2(handle);
	handle->stateConfVector[0] = TP2_Ej3_main_region_Secuencia__region0__2;
	handle->stateConfVectorPosition = 0;
	handle->historyVector[0] = handle->stateConfVector[0];
}

/* 'default' enter sequence for state 3 */
static void tP2_Ej3_enseq_main_region_Secuencia__region0__3_default(TP2_Ej3* handle)
{
	/* 'default' enter sequence for state 3 */
	tP2_Ej3_enact_main_region_Secuencia__region0__3(handle);
	handle->stateConfVector[0] = TP2_Ej3_main_region_Secuencia__region0__3;
	handle->stateConfVectorPosition = 0;
	handle->historyVector[0] = handle->stateConfVector[0];
}

/* 'default' enter sequence for state 4 */
static void tP2_Ej3_enseq_main_region_Secuencia__region0__4_default(TP2_Ej3* handle)
{
	/* 'default' enter sequence for state 4 */
	tP2_Ej3_enact_main_region_Secuencia__region0__4(handle);
	handle->stateConfVector[0] = TP2_Ej3_main_region_Secuencia__region0__4;
	handle->stateConfVectorPosition = 0;
	handle->historyVector[0] = handle->stateConfVector[0];
}

/* 'default' enter sequence for state 5 */
static void tP2_Ej3_enseq_main_region_Secuencia__region0__5_default(TP2_Ej3* handle)
{
	/* 'default' enter sequence for state 5 */
	tP2_Ej3_enact_main_region_Secuencia__region0__5(handle);
	handle->stateConfVector[0] = TP2_Ej3_main_region_Secuencia__region0__5;
	handle->stateConfVectorPosition = 0;
	handle->historyVector[0] = handle->stateConfVector[0];
}

/* 'default' enter sequence for state 7 */
static void tP2_Ej3_enseq_main_region_Secuencia__region0__7_default(TP2_Ej3* handle)
{
	/* 'default' enter sequence for state 7 */
	tP2_Ej3_enact_main_region_Secuencia__region0__7(handle);
	handle->stateConfVector[0] = TP2_Ej3_main_region_Secuencia__region0__7;
	handle->stateConfVectorPosition = 0;
	handle->historyVector[0] = handle->stateConfVector[0];
}

/* 'default' enter sequence for state 6 */
static void tP2_Ej3_enseq_main_region_Secuencia__region0__6_default(TP2_Ej3* handle)
{
	/* 'default' enter sequence for state 6 */
	tP2_Ej3_enact_main_region_Secuencia__region0__6(handle);
	handle->stateConfVector[0] = TP2_Ej3_main_region_Secuencia__region0__6;
	handle->stateConfVectorPosition = 0;
	handle->historyVector[0] = handle->stateConfVector[0];
}

/* 'default' enter sequence for state Pausado */
static void tP2_Ej3_enseq_main_region_Pausado_default(TP2_Ej3* handle)
{
	/* 'default' enter sequence for state Pausado */
	handle->stateConfVector[0] = TP2_Ej3_main_region_Pausado;
	handle->stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
static void tP2_Ej3_enseq_main_region_default(TP2_Ej3* handle)
{
	/* 'default' enter sequence for region main region */
	tP2_Ej3_react_main_region__entry_Default(handle);
}

/* 'default' enter sequence for region  */
static void tP2_Ej3_enseq_main_region_Secuencia__region0_default(TP2_Ej3* handle)
{
	/* 'default' enter sequence for region  */
	tP2_Ej3_react_main_region_Secuencia__region0__entry_Default(handle);
}

/* shallow enterSequence with history in child  */
static void tP2_Ej3_shenseq_main_region_Secuencia__region0(TP2_Ej3* handle)
{
	/* shallow enterSequence with history in child  */
	/* Handle shallow history entry of  */
	switch(handle->historyVector[ 0 ])
	{
		case TP2_Ej3_main_region_Secuencia__region0__1 :
		{
			tP2_Ej3_enseq_main_region_Secuencia__region0__1_default(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__2 :
		{
			tP2_Ej3_enseq_main_region_Secuencia__region0__2_default(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__3 :
		{
			tP2_Ej3_enseq_main_region_Secuencia__region0__3_default(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__4 :
		{
			tP2_Ej3_enseq_main_region_Secuencia__region0__4_default(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__5 :
		{
			tP2_Ej3_enseq_main_region_Secuencia__region0__5_default(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__7 :
		{
			tP2_Ej3_enseq_main_region_Secuencia__region0__7_default(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__6 :
		{
			tP2_Ej3_enseq_main_region_Secuencia__region0__6_default(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for state Secuencia */
static void tP2_Ej3_exseq_main_region_Secuencia(TP2_Ej3* handle)
{
	/* Default exit sequence for state Secuencia */
	tP2_Ej3_exseq_main_region_Secuencia__region0(handle);
}

/* Default exit sequence for state 1 */
static void tP2_Ej3_exseq_main_region_Secuencia__region0__1(TP2_Ej3* handle)
{
	/* Default exit sequence for state 1 */
	handle->stateConfVector[0] = TP2_Ej3_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state 2 */
static void tP2_Ej3_exseq_main_region_Secuencia__region0__2(TP2_Ej3* handle)
{
	/* Default exit sequence for state 2 */
	handle->stateConfVector[0] = TP2_Ej3_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state 3 */
static void tP2_Ej3_exseq_main_region_Secuencia__region0__3(TP2_Ej3* handle)
{
	/* Default exit sequence for state 3 */
	handle->stateConfVector[0] = TP2_Ej3_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state 4 */
static void tP2_Ej3_exseq_main_region_Secuencia__region0__4(TP2_Ej3* handle)
{
	/* Default exit sequence for state 4 */
	handle->stateConfVector[0] = TP2_Ej3_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state 5 */
static void tP2_Ej3_exseq_main_region_Secuencia__region0__5(TP2_Ej3* handle)
{
	/* Default exit sequence for state 5 */
	handle->stateConfVector[0] = TP2_Ej3_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state 7 */
static void tP2_Ej3_exseq_main_region_Secuencia__region0__7(TP2_Ej3* handle)
{
	/* Default exit sequence for state 7 */
	handle->stateConfVector[0] = TP2_Ej3_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state 6 */
static void tP2_Ej3_exseq_main_region_Secuencia__region0__6(TP2_Ej3* handle)
{
	/* Default exit sequence for state 6 */
	handle->stateConfVector[0] = TP2_Ej3_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for state Pausado */
static void tP2_Ej3_exseq_main_region_Pausado(TP2_Ej3* handle)
{
	/* Default exit sequence for state Pausado */
	handle->stateConfVector[0] = TP2_Ej3_last_state;
	handle->stateConfVectorPosition = 0;
}

/* Default exit sequence for region main region */
static void tP2_Ej3_exseq_main_region(TP2_Ej3* handle)
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of TP2_Ej3.main_region) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case TP2_Ej3_main_region_Secuencia__region0__1 :
		{
			tP2_Ej3_exseq_main_region_Secuencia__region0__1(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__2 :
		{
			tP2_Ej3_exseq_main_region_Secuencia__region0__2(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__3 :
		{
			tP2_Ej3_exseq_main_region_Secuencia__region0__3(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__4 :
		{
			tP2_Ej3_exseq_main_region_Secuencia__region0__4(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__5 :
		{
			tP2_Ej3_exseq_main_region_Secuencia__region0__5(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__7 :
		{
			tP2_Ej3_exseq_main_region_Secuencia__region0__7(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__6 :
		{
			tP2_Ej3_exseq_main_region_Secuencia__region0__6(handle);
			break;
		}
		case TP2_Ej3_main_region_Pausado :
		{
			tP2_Ej3_exseq_main_region_Pausado(handle);
			break;
		}
		default: break;
	}
}

/* Default exit sequence for region  */
static void tP2_Ej3_exseq_main_region_Secuencia__region0(TP2_Ej3* handle)
{
	/* Default exit sequence for region  */
	/* Handle exit of all possible states (of TP2_Ej3.main_region.Secuencia._region0) at position 0... */
	switch(handle->stateConfVector[ 0 ])
	{
		case TP2_Ej3_main_region_Secuencia__region0__1 :
		{
			tP2_Ej3_exseq_main_region_Secuencia__region0__1(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__2 :
		{
			tP2_Ej3_exseq_main_region_Secuencia__region0__2(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__3 :
		{
			tP2_Ej3_exseq_main_region_Secuencia__region0__3(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__4 :
		{
			tP2_Ej3_exseq_main_region_Secuencia__region0__4(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__5 :
		{
			tP2_Ej3_exseq_main_region_Secuencia__region0__5(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__7 :
		{
			tP2_Ej3_exseq_main_region_Secuencia__region0__7(handle);
			break;
		}
		case TP2_Ej3_main_region_Secuencia__region0__6 :
		{
			tP2_Ej3_exseq_main_region_Secuencia__region0__6(handle);
			break;
		}
		default: break;
	}
}

/* The reactions of state 1. */
static void tP2_Ej3_react_main_region_Secuencia__region0__1(TP2_Ej3* handle)
{
	/* The reactions of state 1. */
	if (tP2_Ej3_check__lr0(handle) == bool_true)
	{ 
		tP2_Ej3_effect__lr0(handle);
	} 
	if (tP2_Ej3_check_main_region_Secuencia_tr0_tr0(handle) == bool_true)
	{ 
		tP2_Ej3_effect_main_region_Secuencia_tr0(handle);
	}  else
	{
		if (tP2_Ej3_check_main_region_Secuencia__region0__1_tr0_tr0(handle) == bool_true)
		{ 
			tP2_Ej3_effect_main_region_Secuencia__region0__1_tr0(handle);
		}  else
		{
			if (tP2_Ej3_check_main_region_Secuencia__region0__1_tr1_tr1(handle) == bool_true)
			{ 
				tP2_Ej3_effect_main_region_Secuencia__region0__1_tr1(handle);
			} 
		}
	}
}

/* The reactions of state 2. */
static void tP2_Ej3_react_main_region_Secuencia__region0__2(TP2_Ej3* handle)
{
	/* The reactions of state 2. */
	if (tP2_Ej3_check__lr0(handle) == bool_true)
	{ 
		tP2_Ej3_effect__lr0(handle);
	} 
	if (tP2_Ej3_check_main_region_Secuencia_tr0_tr0(handle) == bool_true)
	{ 
		tP2_Ej3_effect_main_region_Secuencia_tr0(handle);
	}  else
	{
		if (tP2_Ej3_check_main_region_Secuencia__region0__2_tr0_tr0(handle) == bool_true)
		{ 
			tP2_Ej3_effect_main_region_Secuencia__region0__2_tr0(handle);
		}  else
		{
			if (tP2_Ej3_check_main_region_Secuencia__region0__2_tr1_tr1(handle) == bool_true)
			{ 
				tP2_Ej3_effect_main_region_Secuencia__region0__2_tr1(handle);
			} 
		}
	}
}

/* The reactions of state 3. */
static void tP2_Ej3_react_main_region_Secuencia__region0__3(TP2_Ej3* handle)
{
	/* The reactions of state 3. */
	if (tP2_Ej3_check__lr0(handle) == bool_true)
	{ 
		tP2_Ej3_effect__lr0(handle);
	} 
	if (tP2_Ej3_check_main_region_Secuencia_tr0_tr0(handle) == bool_true)
	{ 
		tP2_Ej3_effect_main_region_Secuencia_tr0(handle);
	}  else
	{
		if (tP2_Ej3_check_main_region_Secuencia__region0__3_tr0_tr0(handle) == bool_true)
		{ 
			tP2_Ej3_effect_main_region_Secuencia__region0__3_tr0(handle);
		}  else
		{
			if (tP2_Ej3_check_main_region_Secuencia__region0__3_tr1_tr1(handle) == bool_true)
			{ 
				tP2_Ej3_effect_main_region_Secuencia__region0__3_tr1(handle);
			}  else
			{
				if (tP2_Ej3_check_main_region_Secuencia__region0__3_tr2_tr2(handle) == bool_true)
				{ 
					tP2_Ej3_effect_main_region_Secuencia__region0__3_tr2(handle);
				} 
			}
		}
	}
}

/* The reactions of state 4. */
static void tP2_Ej3_react_main_region_Secuencia__region0__4(TP2_Ej3* handle)
{
	/* The reactions of state 4. */
	if (tP2_Ej3_check__lr0(handle) == bool_true)
	{ 
		tP2_Ej3_effect__lr0(handle);
	} 
	if (tP2_Ej3_check_main_region_Secuencia_tr0_tr0(handle) == bool_true)
	{ 
		tP2_Ej3_effect_main_region_Secuencia_tr0(handle);
	}  else
	{
		if (tP2_Ej3_check_main_region_Secuencia__region0__4_tr0_tr0(handle) == bool_true)
		{ 
			tP2_Ej3_effect_main_region_Secuencia__region0__4_tr0(handle);
		}  else
		{
			if (tP2_Ej3_check_main_region_Secuencia__region0__4_tr1_tr1(handle) == bool_true)
			{ 
				tP2_Ej3_effect_main_region_Secuencia__region0__4_tr1(handle);
			} 
		}
	}
}

/* The reactions of state 5. */
static void tP2_Ej3_react_main_region_Secuencia__region0__5(TP2_Ej3* handle)
{
	/* The reactions of state 5. */
	if (tP2_Ej3_check__lr0(handle) == bool_true)
	{ 
		tP2_Ej3_effect__lr0(handle);
	} 
	if (tP2_Ej3_check_main_region_Secuencia_tr0_tr0(handle) == bool_true)
	{ 
		tP2_Ej3_effect_main_region_Secuencia_tr0(handle);
	}  else
	{
		if (tP2_Ej3_check_main_region_Secuencia__region0__5_tr0_tr0(handle) == bool_true)
		{ 
			tP2_Ej3_effect_main_region_Secuencia__region0__5_tr0(handle);
		}  else
		{
			if (tP2_Ej3_check_main_region_Secuencia__region0__5_tr1_tr1(handle) == bool_true)
			{ 
				tP2_Ej3_effect_main_region_Secuencia__region0__5_tr1(handle);
			} 
		}
	}
}

/* The reactions of state 7. */
static void tP2_Ej3_react_main_region_Secuencia__region0__7(TP2_Ej3* handle)
{
	/* The reactions of state 7. */
	if (tP2_Ej3_check__lr0(handle) == bool_true)
	{ 
		tP2_Ej3_effect__lr0(handle);
	} 
	if (tP2_Ej3_check_main_region_Secuencia_tr0_tr0(handle) == bool_true)
	{ 
		tP2_Ej3_effect_main_region_Secuencia_tr0(handle);
	}  else
	{
		if (tP2_Ej3_check_main_region_Secuencia__region0__7_tr0_tr0(handle) == bool_true)
		{ 
			tP2_Ej3_effect_main_region_Secuencia__region0__7_tr0(handle);
		}  else
		{
			if (tP2_Ej3_check_main_region_Secuencia__region0__7_tr1_tr1(handle) == bool_true)
			{ 
				tP2_Ej3_effect_main_region_Secuencia__region0__7_tr1(handle);
			} 
		}
	}
}

/* The reactions of state 6. */
static void tP2_Ej3_react_main_region_Secuencia__region0__6(TP2_Ej3* handle)
{
	/* The reactions of state 6. */
	if (tP2_Ej3_check__lr0(handle) == bool_true)
	{ 
		tP2_Ej3_effect__lr0(handle);
	} 
	if (tP2_Ej3_check_main_region_Secuencia_tr0_tr0(handle) == bool_true)
	{ 
		tP2_Ej3_effect_main_region_Secuencia_tr0(handle);
	}  else
	{
		if (tP2_Ej3_check_main_region_Secuencia__region0__6_tr0_tr0(handle) == bool_true)
		{ 
			tP2_Ej3_effect_main_region_Secuencia__region0__6_tr0(handle);
		}  else
		{
			if (tP2_Ej3_check_main_region_Secuencia__region0__6_tr1_tr1(handle) == bool_true)
			{ 
				tP2_Ej3_effect_main_region_Secuencia__region0__6_tr1(handle);
			} 
		}
	}
}

/* The reactions of state Pausado. */
static void tP2_Ej3_react_main_region_Pausado(TP2_Ej3* handle)
{
	/* The reactions of state Pausado. */
	if (tP2_Ej3_check__lr0(handle) == bool_true)
	{ 
		tP2_Ej3_effect__lr0(handle);
	} 
	if (tP2_Ej3_check_main_region_Pausado_tr0_tr0(handle) == bool_true)
	{ 
		tP2_Ej3_effect_main_region_Pausado_tr0(handle);
	} 
}

/* Default react sequence for shallow history entry  */
static void tP2_Ej3_react_main_region_Secuencia__region0__entry_Default(TP2_Ej3* handle)
{
	/* Default react sequence for shallow history entry  */
	/* Enter the region with shallow history */
	if (handle->historyVector[0] != TP2_Ej3_last_state)
	{
		tP2_Ej3_shenseq_main_region_Secuencia__region0(handle);
	} else
	{
		tP2_Ej3_enseq_main_region_Secuencia__region0__1_default(handle);
	} 
}

/* Default react sequence for initial entry  */
static void tP2_Ej3_react_main_region__entry_Default(TP2_Ej3* handle)
{
	/* Default react sequence for initial entry  */
	tP2_Ej3_enseq_main_region_Pausado_default(handle);
}


