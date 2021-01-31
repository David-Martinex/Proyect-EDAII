#ifndef  Graph_INC
#define  Graph_INC

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "DLL.h"
#include "Station.h"
#include "Roots.h"
#include "Entry.h"
#include "Map.h"

void G_Best_Route(City* origen, City* destino, DLL* cities, DLL* axis, char path[], size_t len);

void Add_Cities( DLL* cities, MapPtr vertices);

#endif   /* ----- #ifndef graph_INC  ----- */