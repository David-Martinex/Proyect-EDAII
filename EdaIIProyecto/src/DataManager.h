#ifndef  DataManager_INC
#define  DataManager_INC

#include <assert.h>
#include <string.h>

#include "DLL.h"
#include "City.h"
#include "DataBase.h"
#include "Axis.h"
#include "graph.h"

typedef struct DataManager
{
	DLL* cities;
	DLL* axis;
	DataBase* dataBase;
} DataManager;

DataManager* DataManager_New();

void DataManager_Delete( DataManager* this );

void DM_LoadInformation( DataManager* this );

bool DM_Add_City( DataManager* this, char name[] );

bool DM_Add_CityAxis( DataManager* this, char name1[], char name2[], size_t weight );

City* DM_Find_City( DataManager* this, char name[] );

void DM_Get_CitiesList( DataManager* this, void* ptrArr[] );

void DM_Print_CitiesList( DataManager* this );

void DM_Print_AxisList( DataManager* this );

void DM_Obtain_Best_Path( DataManager* this, char name1[], char name2[], char path[], size_t len );


#endif   /* ----- #ifndef DataManager_INC  ----- */