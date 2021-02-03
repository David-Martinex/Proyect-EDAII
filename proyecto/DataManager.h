#ifndef DataManager_INC
#define DataManager_INC

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "DLL.h"
#include "Station.h"
#include "DataBase.h"
#include "Roots.h"
#include "Graph.h"

/**
 * @brief Declaramos un tipo Abstracto constituido por atributos 2 
 * Listas Doblemente Enlazadas denomidas stations y roots que guardaran
 * la informacion necesaria para nuestro programa.
 * Tambien hacemos referencia a un Objeto DataBase
 * 
 */
typedef struct DataManager
{
    DLL* stations;
    DLL* roots;
    DataBase* dataBase;
} DataManager;

/**
*	@brief Constructor del objeto DataManager, también carga la DB.
*	@return dm Referencia a el objeto DataManager.
*/
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


#endif   /* ----- #ifndef DataManager_INC  ----- */