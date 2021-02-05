#ifndef  ENTRY_INC
#define  ENTRY_INC

/**
 * @file Entry.h
 * @brief COntiene una estructura Entry.
 * @version 0.1
 * @date 2021-02-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdlib.h>
/**Para usar Station y sus metodos*/
#include "Station.h"

/**
 * @brief estructura que nos servira para nuestra Tabla Hash mejor conocida como
 * Map.
 * 
 */
typedef struct
{
	char key[15];       ///Cadena de texto asociada al registro (key).
	Station* station;   ///Referencia a un objeto Station (value).
} Entry;

#endif   /* ----- #ifndef ENTRY_INC  ----- */