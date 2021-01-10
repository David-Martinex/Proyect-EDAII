#ifndef  DataBase_INC
#define  DataBase_INC

#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "City.h"
#include "Axis.h"
#include "sqlite3.h"
#include "DLL.h"


typedef struct DataBase
{
	sqlite3* dataBase;
}DataBase;

DataBase* DataBase_New();

void DataBase_Delete( DataBase* this ); 

bool DB_Save_Information( DataBase* this, DLL* dll, DLL* axis );

bool DB_Recover_Information( DataBase* this, DLL* dll, DLL* axis );






#endif   /* ----- #ifndef DataBaseManager_INC  ----- */