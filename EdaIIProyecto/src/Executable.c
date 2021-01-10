#include "DataManager.h"

#define TAM_ARR 256

int getInteger( );

void menu       ( DataManager* dm );
void loadGraph  ( DataManager* dm );
void loadGraphDB( DataManager* dm );
void getBestPath( DataManager* dm );
void addNewCity ( DataManager* dm );
void addNewAxis ( DataManager* dm );
void printCities( DataManager* dm );
void printAxis  ( DataManager* dm );

int main(){
	DataManager* dm = DataManager_New();

	menu( dm );

	DataManager_Delete( dm );
	return 0;
}


void menu( DataManager* dm ){
	while( 1 ){
		printf(	"***************MENU*************\n\n"
				"0) Salir.\n"
				"1) Cargar grafo prediseñado.\n"
				"2) Cargar grafo de base de datos\n"
				"3) Obtener mejor ruta.\n"
				"4) Añadir ciudad.\n"
				"5) Añadir eje entre ciudades.\n"
				"6) Imprimir lista de ciudades.\n"
				"7) Imprimir lista de ejes.\n"
				"$ "

			);

		switch( getInteger() ){
			case 0: return;
			case 1: loadGraph  ( dm );  break;
			case 2: loadGraphDB( dm ); break;
			case 3: getBestPath( dm ); break;
			case 4: addNewCity ( dm ); break;
			case 5: addNewAxis ( dm ); break;
			case 6: printCities( dm ); break;
			case 7: printAxis  ( dm ); break;
			default: printf("FUERA DE RANGO\n"); break;
		}
	}
}

int getInteger( ){ int n; scanf( "%d",&n ); return n; }

void loadGraph( DataManager* dm ){
	if( DLL_Len( dm->cities ) > 0 ){
		printf("\n[ ERROR ] Grafo precargado.\n");
		return;
	}

	DM_Add_City( dm, "S" );
	DM_Add_City( dm, "B" );
	DM_Add_City( dm, "C" );
	DM_Add_City( dm, "D" );
	DM_Add_City( dm, "E" );
	DM_Add_City( dm, "T" );

	DM_Add_CityAxis( dm, "S", "B", 4 );
	DM_Add_CityAxis( dm, "S", "C", 2 );
	DM_Add_CityAxis( dm, "B", "C", 1 );
	DM_Add_CityAxis( dm, "B", "D", 5 );
	DM_Add_CityAxis( dm, "C", "E", 10 );
	DM_Add_CityAxis( dm, "C", "D", 8 );
	DM_Add_CityAxis( dm, "D", "E", 2 );
	DM_Add_CityAxis( dm, "D", "T", 6 );
	DM_Add_CityAxis( dm, "E", "T", 2 );
}

void loadGraphDB( DataManager* dm ){
	if( DLL_Len( dm->cities ) > 0 ){
		printf("\n[ ERROR ] Grafo precargado.\n");
		return;
	}

	DM_LoadInformation( dm );
}

void getBestPath( DataManager* dm ){
	char path[ 256 ] = "";
	DM_Obtain_Best_Path( dm, "S", "T", path, 256 );
	printf("%s\n",path);
}

void addNewCity( DataManager* dm ){
	printf("\nNombre de la ciudad: \n");
	char chain[ 100 ];
	scanf( "%s",&chain[ 0 ] );
	DM_Add_City( dm, chain );
}

void addNewAxis( DataManager* dm ){
	printf("\nCiudad [ origen ] a buscar: \n");
	char name1[ 100 ];
	scanf( "%s",&name1[ 0 ] );


	printf("\nCiudad [ destino ] a buscar: \n");
	char name2[ 100 ];
	scanf( "%s",&name2[ 0 ] );


	printf("Distancia: \n");
	int d;
	scanf( "%d", &d );

	DM_Add_CityAxis( dm, name1, name2, ( size_t )d );
}

void printCities( DataManager* dm ){
	DM_Print_CitiesList( dm );
}

void printAxis( DataManager* dm ){
	DM_Print_AxisList( dm );
}

