#ifndef  DataBase_INC
#define  DataBase_INC
/**
 * @file DataBase.h
 * @brief Se encargara de guardar nuestra estructura que compone a nuestro Tipo
 * abtsracto DataBase, tambien los prototipos de los metodos relacionados con
 * este Tipo Abstracto.  
 * @version 0.1
 * @date 2021-02-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/** para usar bool´s*/
#include <stdbool.h>
/** Para usar assert´s*/
#include <assert.h>
/** Para usar strcpy y strcmp */
#include <string.h>

/**Para usar a Station y algunos de metodos relaionados*/
#include "Station.h"
/**Para usar a Roots y algunos de metodos relaionados*/
#include "Roots.h"
/**Para hacer uso de nuestras bases de datos SQL y algunos metodos*/
#include "sqlite3.h"
/**Para usar a DLL y algunos de sus metodos relaionados*/
#include "DLL.h"

/**
 * @brief Declaramos un tipo abstracto denominado DataBase que contendra 
 * entre sus atributos un sqlite3 para hacer uso de base de datos SQL.
 * 
 */
typedef struct DataBase
{
	sqlite3* dataBase;
}DataBase;

DataBase* DataBase_New();

void DataBase_Delete( DataBase* this ); 

bool DB_Save_Information( DataBase* this, DLL* dll, DLL* roots );

bool DB_Recover_Information( DataBase* this, DLL* dll, DLL* roots );

#endif   /* ----- #ifndef DataBaseManager_INC  ----- */