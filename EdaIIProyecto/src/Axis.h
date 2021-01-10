#ifndef  Axis_INC
#define  Axis_INC

#include "City.h"

#include <assert.h>

typedef struct Axis{
	City* first;
	City* last;

	size_t weight;

}Axis;

Axis* Axis_New( City* first, City* last, size_t weight);

void Ax_To_String( Axis* this, char str[], size_t len );

void Ax_Print( Axis* this );

void Axis_Delete( Axis* this );


#endif   /* ----- #ifndef Axis_INC  ----- */