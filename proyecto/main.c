#include "DataManager.h"
#include <stdio.h>

#define TAM 256

int getInteger();

void menu         ( DataManager* dm );
void loadGraph    ( DataManager* dm );
void loadGraphDB  ( DataManager* dm );
void getBestPath  ( DataManager* dm );
void addNewStation( DataManager* dm );
void addNewRoot   ( DataManager* dm );
void printStations( DataManager* dm );
void printRoots   ( DataManager* dm );

int main()
{
    DataManager* dm = DataManager_New();

    menu( dm );

    DataManager_Delete( dm );
    return 0;
}

int getInteger()
{
    int n;
    scanf("%d", &n);
    return n;
}

void menu( DataManager* dm )
{
    while( 1 ){
		printf(	"==============={ MENU }=============\n\n"
				"0) Salir.\n"
				"1) Cargar grafo prediseñado.\n"
				"2) Cargar grafo de base de datos\n"
				"3) Obtener mejor ruta.\n"
				"4) Añadir Estacion.\n"
				"5) Añadir eje entre estaciones.\n"
				"6) Imprimir lista de estaciones.\n"
				"7) Imprimir lista de ejes.\n"
				"$ "

			);

		switch( getInteger() ){
			case 0: return;
			case 1: loadGraph    ( dm ); break;
			case 2: loadGraphDB  ( dm ); break;
			case 3: getBestPath  ( dm ); break;
			case 4: addNewStation( dm ); break;
			case 5: addNewRoot   ( dm ); break;
			case 6: printStations( dm ); break;
			case 7: printRoots   ( dm ); break;
			default: printf("FUERA DE RANGO\n"); break;
		}
	}
}

void loadGraph( DataManager* dm )
{
    if ( DLL_Len( dm->stations ) > 0 ){
        printf("\t\n\n===>!!Error¡¡\n=>Grafo precargado\n\n");
        return;
    }

    DM_Add_Station( dm, "S" );
    DM_Add_Station( dm, "B" );
    DM_Add_Station( dm, "C" );
    DM_Add_Station( dm, "D" );
    DM_Add_Station( dm, "E" );
    DM_Add_Station( dm, "T" );
    
    DM_ADD_StationRoot( dm, "S", "B", 4 );
    DM_ADD_StationRoot( dm, "s", "c", 2 );
    DM_ADD_StationRoot( dm, "B", "C", 3 );
    DM_ADD_StationRoot( dm, "B", "D", 5 );
    DM_ADD_StationRoot( dm, "C", "E", 10);
    DM_ADD_StationRoot( dm, "C", "D", 8 );
    DM_ADD_StationRoot( dm, "D", "E", 3 );
    DM_ADD_StationRoot( dm, "D", "T", 6 );
    DM_ADD_StationRoot( dm, "E", "T", 3 );

}

void loadGraphDB  ( DataManager* dm )
{
    if ( DLL_Len( dm->stations ) > 0 ){
        printf("\t\n\n===>!!Error¡¡\n=>Grafo precargado\n\n");
        return;
    }

    DM_LoadInformation( dm );
}

void getBestPath  ( DataManager* dm )
{
    char path[ TAM ] = "";
    DM_Obtain_Best_Path( dm, "S", "T", path, TAM );
    printf("%s\n", path);
}

#define MAX_TAM 50

void addNewStation( DataManager* dm )
{
    printf("\n==>Nombre de la Estacion:\n$");
    char chain[ MAX_TAM ];
    scanf("s", &chain[ 0 ] );
    DM_Add_Station( dm, chain );
}

void addNewRoot( DataManager* dm )
{
    printf("\n=>Estacion [ origen ] a insertar:\n$");
    char name1[ MAX_TAM ];
    scanf("%s", &name1[ 0 ] );

    printf("\n=>Estacion [ destino ] a insertar:\n$");
    char name2[ MAX_TAM ];
    scanf("%s", &name2[ 0 ] );

    printf("\n=>Distancia: \n$");
    size_t d;
    scanf("%ld", &d );

    DM_Add_StationRoot( dm, name1, name2, d );
}

void printStations( DataManager* dm )
{
    DM_Print_StationsList( dm );
}

void printRoots( DataManager* dm )
{
    DM_Print_RootsList( dm );
}