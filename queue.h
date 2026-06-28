
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
typedef struct tElmtlist *address; 
typedef struct  tElmtlist   
{
	infotype info;
	address next;
}ElmtList;
 
typedef struct {
	address front;
	address rear;
}queue;

boolean IsEmpty(queue Q);
void Initial(queue *Q);
void setFront(queue *Q);
void setRear(queue *Q);
void Delete(queue *Q, infotype *data);
void Insert(queue *Q, infotype data);
void PrintQueue(queue Q);
address Alokasi(infotype  X);
void Dealokasi(address *P);

#endif

