#ifndef  Roots_INC
#define  Roots_INC

#include "Station.h"

#include <assert.h>

typedef struct Axis{
	Station* first;
	Station* last;

	size_t weight;

}Axis;

Axis* Axis_New( City* first, City* last, size_t weight);

void Ax_To_String( Axis* this, char str[], size_t len );

void Ax_Print( Axis* this );

void Axis_Delete( Axis* this );


#endif   /* ----- #ifndef Roots_INC  ----- */