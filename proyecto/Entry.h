#ifndef  ENTRY_INC
#define  ENTRY_INC

#include <stdlib.h>
#include "Station.h"

typedef struct
{
	char key[15];       ///Cadena de texto asociada al registro (key).
	Station* station;   ///Referencia a un objeto City (value).
} Entry;

#endif   /* ----- #ifndef ENTRY_INC  ----- */