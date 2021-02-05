#ifndef DataManager_INC
#define DataManager_INC
/**
 * @file DataManager.h
 * @brief Se encarga de los Tipos Abstracto denominados DataManager donde inicializaremos y 
 * tambien tenemos sus metodos publicos que son de interes para el usuario. 
 * Tambien la funcion de este Tipo Abstracto es manejar todos nuestrs tipos Abstractos y
 * sus metodos.
 * @version 0.1
 * @date 2021-02-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
/**Para hacer uso de asserts*/
#include <assert.h>
/**Para hacer uso de strcpy y strcmp*/
#include <string.h>
/**Para hacer uso de printf y compañia*/
#include <stdio.h>
#include <stdlib.h>

/**Para hacer uso de Tipos Abstractos DLL(Listas Doblemente Enlazadas) y sus metodos*/
#include "DLL.h"
/**Para hacer uso de Tipos Abstractos Station(Nuestras Estaciones) y sus metodos*/
#include "Station.h"
/**Para hacer uso de Tipos Abstractos DataBase( Base de Datos SQL) y sus metodos*/
#include "DataBase.h"
/**Para hacer uso de Tipos Abstractos Roots( Nuestras Rutas ) y sus metodos*/
#include "Roots.h"
/**Para hacer uso de Tipos Abstractos Graph( Nuestro Grafo ) y sus metodos*/
#include "Graph.h"
/**Para hacer uso de Tipos Abstractos DataJson( Manejo de Arhivos.json) y sus metodos*/
#include "DataJson.h"

#include "QuickSort.h"
#include "BinarySearch.h"
/** 
 * @struct DataManager
 * @brief estructura encargada de llevar los datos de la aplicación.
 * @var stations contiene la dirección de una lista doblemente enlazada
 * de las estaciones.
 * @var roots contiene la  direacción de una lista doblemente enlazada
 * de las rutas.
 * @var dataBase contiene la dirección del manejador de la base de datos.
 * @var dataJson contiene el buffer para el manejo de datos .json.
 */
typedef struct DataManager
{
    DLL* stations;
    DLL* roots;
    DataBase* dataBase;
    DataJson* dataJson;
} DataManager;

DataManager* DataManager_New();

void DataManager_Delete( DataManager* this );

void DM_LoadInformation( DataManager* this );

bool DM_Add_Station( DataManager* this, char name[] );

bool DM_Add_StationRoots( DataManager* this, char name1[], char name2[], size_t weight );

Station* DM_Find_Station( DataManager* this, char name[] );

void DM_Get_StationList( DataManager* this, void* ptrArr[] );

void DM_Print_StationsList( DataManager* this );

void DM_Print_RootsList( DataManager* this );

void DM_Obtain_Best_Path( DataManager* this, char name1[], char name2[], char path[], size_t len );

void DM_Serialize( DataManager* this );

void DM_Search( DataManager* this );

#endif   /* ----- #ifndef DataManager_INC  ----- */