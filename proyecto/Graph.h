#ifndef  Graph_INC
#define  Graph_INC

/**
 * @file Graph.h
 * @brief Contiene La estructura Graph y los prototipos de los metodos relacionados con esta.
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
#include <omp.h>

#include "DLL.h"
#include "Station.h"
#include "Roots.h"
#include "Entry.h"
#include "Map.h"

typedef struct Graph
{
	int costo;

	int tiempo;

	MapPtr vertices;

}Graph;

void G_Best_Route(Station* origen, Station* destino, DLL* stations, DLL* roots, char path[], size_t len);

void G_Best_Route_Quick(  Station* origen, Station* destino, DLL* stations, DLL* roots, char path[], size_t len);

void G_Add_Station( DLL* stations, MapPtr vertices);

#endif   /* ----- #ifndef Graph_INC  ----- */