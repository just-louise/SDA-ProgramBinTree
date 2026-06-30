
#ifndef queue_H
#define queue_H

#include <stdio.h>
#include "boolean.h"
#define Front(Q) (Q).front
#define Rear(Q) (Q).rear
#define Nil  NULL
#define Info(P) (P)->info
#define Next(P) (P)->next
#define First(L) ((L).First)

typedef char infotype[50];
typedef struct tElmtlist *addressQ; 
typedef struct  tElmtlist   
{
	infotype info;
	addressQ next;
}ElmtList;
 
typedef struct {
	addressQ front;
	addressQ rear;
}queue;

boolean IsEmptyQ(queue Q);
void Initial(queue *Q);
void setFront(queue *Q);
void setRear(queue *Q);
void DeleteQ(queue *Q, infotype *data);
void Insert(queue *Q, infotype data);
void PrintQueue(queue Q);
addressQ AlokasiQ(infotype  X);
void DealokasiQ(addressQ *P);

#endif

