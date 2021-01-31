#ifndef  Roots_INC
#define  Roots_INC

#include "Station.h"

#include <assert.h>

typedef struct Roots{
	Station* first;
	Station* last;

	size_t weight;

}Roots;

Roots* Roots_New( Station* first, Station* last, size_t weight);

void Ro_To_String( Roots* this, char str[], size_t len );

void Ro_Print( Roots* this );

void Roots_Delete( Roots* this );


#endif   /* ----- #ifndef Roots_INC  ----- */