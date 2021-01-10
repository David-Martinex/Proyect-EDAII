
#ifndef  ENTRY_INC
#define  ENTRY_INC

#include <stdlib.h>
#include "City.h"

typedef struct
{
	char key[15];  ///Cadena de texto asociada al registro (key).
	City* city;    ///Referencia a un objeto City (value).
} Entry;

#endif   /* ----- #ifndef ENTRY_INC  ----- */
