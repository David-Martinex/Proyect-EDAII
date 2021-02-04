#ifndef  ENTRY_INC
#define  ENTRY_INC

#include <stdlib.h>
#include "Station.h"

/**
 * @brief Tipo Abstracto que nos servira para nuestra Tabla Hash mejor conocida como
 * Map.
 * 
 */
typedef struct
{
	char key[15];       ///Cadena de texto asociada al registro (key).
	Station* station;   ///Referencia a un objeto Station (value).
} Entry;

#endif   /* ----- #ifndef ENTRY_INC  ----- */