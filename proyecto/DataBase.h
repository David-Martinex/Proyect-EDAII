#ifndef  DataBase_INC
#define  DataBase_INC

#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "Station.h"
#include "Roots.h"
#include "sqlite3.h"
#include "DLL.h"

/**
 * @brief Declaracion de un tipo Abstracto denomidano DataBase que guardara
 * entre sus atributos un onjeto de tipo sqlite3 que nos serivra para el 
 * manejo de la Base de Datos SQL.
 */
typedef struct DataBase
{
	sqlite3* dataBase;
}DataBase;

/**
 * @brief Constructor del tipo Abstracto DataBase que se encargara de
 * pedir prestada memoria para el objeto.
 * 
 * @return DataBase* regresa un Objeto DataBase listo para usarse.
 */
DataBase* DataBase_New();

/**
 * @brief Destructor del tipo Abstracto DataBase que se encargara de 
 * destruir a nuestro objeto con la finalidad de regresar la memoria 
 * prestada a nuestra computadora para evitar fugas de memorias.
 * @param this referencia a un objeto de tipo DataBase que sera eliminado.
 */
void DataBase_Delete( DataBase* this ); 

/**
 * @brief Salva la informacion de los vertices en su repectiva BD.
 * 
 * @param this Referencia a la base de datos.
 * @param dll Referencia a una DLL con las estaciones a guardar.
 * @param roots Referencia a una DLL con las rutas a guardar.
 * @return true Si se ha salvado informacion con éxito. 
 * @return false Si no se ha salvado informacion con éxito.
 */
bool DB_Save_Information( DataBase* this, DLL* dll, DLL* roots );

/**
 * @brief Recobra información y la guarda en una DLL. En caso de estar vaciá
*	la BD el la DLL apuntara a NULL.
 * 
 * @param this Referencia a un objeto DataBase.
 * @param dll Referencia a una DLL donde se guardaran vértices recuperados.
 * @param roots Referencia a una DLL donde se guardaran vértices recuperados de nuestras rutas.
 * @return true Si se ha realizado la operacion con éxito.
 * @return false Si no se ha realizado la operacion con éxito.
 */
bool DB_Recover_Information( DataBase* this, DLL* dll, DLL* roots );

#endif   /* ----- #ifndef DataBaseManager_INC  ----- */