#ifndef  MAP_INC
#define  MAP_INC

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <iso646.h>
#include <stdint.h>
#include <string.h>
#include "Entry.h"
#include "City.h"

typedef size_t (*pHash)(char key[], size_t max);

typedef size_t (*pCollRes)( size_t index, size_t max);

typedef struct
{
	Entry* table; ///< Es la tabla hash

	size_t size; ///< Es el número máximo de elementos en la tabla
	
	size_t len; ///< Es el número actual de elementos en la tabla

	size_t empty; ///< es el valor que 'key' interpretará como vacío

	pHash hash; ///< es la función hash

	pCollRes coll_res;

} Map;

typedef Map* MapPtr;


MapPtr Map_New( size_t capacity, size_t empty, pHash hash, pCollRes coll_res );


void Map_Delete( MapPtr this );


bool Map_Insert( MapPtr this, char nombre[], City* city );


City* Map_Retrieve( MapPtr this, char nombre[]);


size_t Map_Len( MapPtr this );


size_t Map_Size( MapPtr this );

#endif   /* ----- #ifndef MAP_INC  ----- */
