#ifndef DataManager_INC
#define DataManager_INC
/**
 * @file DataManager.h
 * @brief Modulo del Tipo Abstracto denominado DataManager donde declaramos los componentes
 * y atributos del Tipo Abstracto y tambien tenemos sus metodos publicos que son de interes
 * para el usuario. Tambien la funcion de este Tipo Abstracto es manejar las bases de datos 
 * y los archivos de los cuales se rescatara la informacion.
 * @version 0.1
 * @date 2021-02-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "DLL.h"
#include "Station.h"
#include "DataBase.h"
#include "Roots.h"
#include "Graph.h"
#include "DataJson.h"

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

#endif   /* ----- #ifndef DataManager_INC  ----- */