#ifndef  Station_INC
#define  Station_INC
/**
 * @file Station.h
 * @brief Contiene la estructura de Station y los prototipos de los metodos relazionados con esta.
 * @version 0.1
 * @date 2021-02-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/** Para usar Listas Doblemente Enlazadas*/
#include "DLL.h"

enum
{
	BLACK,
	GRAY,
	WHITE
};

typedef struct Station
{
	char name[ 32 ];

	void* neighbors;

	int color;

	size_t distance;

	char  predecesor[ 32 ];

	size_t discoveryTime;

	size_t finishTime;
}Station;

Station* Station_New( char name[] );

void Station_Delete( Station* this );

bool ST_Add_Neighbor( Station* this, Station* station );

void ST_Set_Distance( Station* this, int distance );

void ST_Set_Color( Station* this, int color );

void ST_Set_Predecesor( Station* this, char predecesor[] );

void ST_Set_DiscoveryTime( Station* this, size_t discoveryTime );

void ST_Set_FinishTime( Station* this, size_t finishTime );

void ST_To_String_Neighbors( Station* this, char str[], size_t len );

void ST_To_String( Station* this, char chain[], size_t len );

void ST_Print( Station* this );


#endif   /* ----- #ifndef Station_INC  ----- */