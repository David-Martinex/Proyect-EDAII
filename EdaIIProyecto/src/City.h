#ifndef  City_INC
#define  City_INC

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "DLL.h"

enum
{
	BLACK,
	GRAY,
	WHITE
};

typedef struct City
{
	char name[ 32 ];

	void* neighbors;

	int color;

	size_t distance;

	char  predecesor[ 32 ];

	size_t discoveryTime;

	size_t finishTime;
}City;

City* City_New( char name[] );

void City_Delete( City* this );

bool CT_Add_Neighbor( City* this, City* city );

void CT_Set_Distance( City* this, int distance );

void CT_Set_Color( City* this, int color );

void CT_Set_Predecesor( City* this, char predecesor[] );

void CT_Set_DiscoveryTime( City* this, size_t discoveryTime );

void CT_Set_FinishTime( City* this, size_t finishTime );

void CT_To_String_Neighbors( City* this, char str[], size_t len );

void CT_To_String( City* this, char chain[], size_t len );

void CT_Print( City* this );


#endif   /* ----- #ifndef City_INC  ----- */