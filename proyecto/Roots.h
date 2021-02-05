#ifndef  Roots_INC
#define  Roots_INC
/**
 * @file Roots.h
 * @brief Contiene la estructura de Roots y prototipos de los metodos relacionados con Roots.
 * @version 0.1
 * @date 2021-02-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Station.h"

#include <assert.h>

/**
 * @brief Declaramos un objeto de tipo Abstracto llamado Roots que no servira a manera de vertice para conectar a las estaciones, 
 * el cual entre sus parametros tendra:
 * 	- Objetos de tipo Station denominados first y last estos indicaran nuestra estacion origen y destino.
 *  - un size_t weight el cual indicara el coste por moverno de una estacion a otra.
 * 
 */
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