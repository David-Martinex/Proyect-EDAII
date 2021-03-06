#ifndef  DataJson_INC
#define  DataJson_INC
/**
 * @file DataJson.h
 * @brief Contiene la estructura de DataJson y sus metodos.
 * @version 0.1
 * @date 2021-02-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

/**Para usar Station y sus METODOS*/
#include "Station.h"
/**Para usar Roots y sus METODOS*/
#include "Roots.h"
/**Para usar DLL y sus METODOS*/
#include "DLL.h"

/**
 * @brief Tipo Abstracto denominado DataJson que guardara nuestro buffer recuperado de
 * nuestro archivo .json;
 * 
 */
typedef struct DataJson
{
    char buffer[1024];
}DataJson;

/**
 * @brief COnstructor del tipo Abstracto denominado DataJson que se encarga de pedir
 * prestada memoria y rescata la informacion del .json.
 * 
 * @return DataJson* 
 */
DataJson* DataJson_New();

/**
 * @brief Destructor del tipo Abstracto denominado DataJson que se encarga de liberar
 * la memoria prestada.
 * 
 * @param file referencia a un Objeto DataJson a procesar.
 */
void DataJson_Delete( DataJson* file );

/**
 * @brief Funcion que se encargara de guardar la informacion procesada en nuestro programa
 * en un archivo.json.
 * 
 * @param stations 
 * @param n_stations Numero de estaciones aprocesar.
 * @param roots 
 * @param n_roots Numero de rutas a procesar
 */
void DataJson_Serialize( void** stations, size_t n_stations, void** roots, size_t n_roots );

#endif   /* ----- #ifndef DataJson_INC  ----- */