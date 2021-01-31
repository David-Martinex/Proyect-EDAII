#ifndef  DLL_INC
#define  DLL_INC

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "Station.h"

typedef void* Item;

typedef struct Node
{
	Item info;

	struct Node* next;
	struct Node* prev;
} Node;

typedef struct DLL
{
	Node*  first;
	Node*  last;
	Node*  cursor;
	size_t len;
} DLL;


DLL*   DLL_New();
void   DLL_Delete(      DLL* this );
bool   DLL_InsertBack(  DLL* this, Item value );
bool   DLL_RemoveFront( DLL* this, Item* value );
bool   DLL_RemoveNode(  DLL* this, Item value);
bool   DLL_Peek(        DLL* this, Item* value );
bool   DLL_IsEmpty (    DLL* this);
bool   DLL_IsOnList  (  DLL* this, Item value );
void   DLL_Purge(       DLL* this );
size_t DLL_Len(         DLL* this );
void   DLL_GetInformation( DLL* this, void* ptrArr[] );

#endif   /* ----- #ifndef DLL_INC  ----- */