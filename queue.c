#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

Node *Q1 = NULL;

void enqueue (int val){
	Node* newNode = malloc(sizeof(Node));
	newNode->data = val;
	newNode->next = NULL;
	
	if (Q1 == NULL){
		Q1 = newNode;
		return;
	}
	
	Node* temp = Q1;
	while (temp->next !=NULL) temp = temp->next;
	temp->next = newNode;
}

void printQueueLIFO (Node* head){
	if (head == NULL)
	return;
	printQueueLIFO(head->next);
	printf("%d -> ", head-> data);
}