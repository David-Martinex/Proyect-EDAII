/* ==={ DLL.h }=== */

#include <stdlib.h> // Para malloc and friends
#include <assert.h> // para los asserts
#include <stdbool.h> // para bool, true y false
#include <stdio.h>// printf
#include <time.h>

typedef struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
}Node;

typedef Node* NodePtr;

typedef Node* NodePtr;

typedef struct DLL
{
    NodePtr first;
    NodePtr last;
    NodePtr cursor;
    size_t len;
}DLL;

DLL*   DLL_New( );
void   DLL_Delete(      DLL** this );
bool   DLL_InsertBack(  DLL* this, int data );
bool   DLL_InsertFront( DLL* this, int data );
bool   DLL_InsertAfter( DLL* this, int data );
bool   DLL_InsertBefore(DLL* this, int data );
bool   DLL_Remove(      DLL* this, int* data_back );
bool   DLL_RemoveFront( DLL* this, int* data_back );
bool   DLL_RemoveBack(  DLL* this, int* data_back );
bool   DLL_RemoveAfter( DLL* this, int* data_back );
bool   DLL_RemoveBefore(DLL* this, int* data_back );
size_t DLL_Len(         DLL* this );
bool   DLL_IsEmpty(     DLL* this );
void   DLL_MakeEmpty(   DLL* this );
bool   DLL_Peek(        DLL* this, int* data_back );
void   DLL_CursorFirst( DLL* this );
void   DLL_CursorLast(  DLL* this );
void   DLL_CursorNext(  DLL* this );
void   DLL_CursorPrev(  DLL* this );
bool   DLL_FindIf(      DLL* this, int key );
bool   DLL_Search(      DLL* this, int key );
void   DLL_Traverse(    DLL* this, void (*pfun)(int ) );

