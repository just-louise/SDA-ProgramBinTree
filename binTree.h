/* File    : binTree.h */
/* Desk    : Deklarasi Binary Search Tree untuk kamus kata */

#ifndef BINTREE_H
#define BINTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"

#define Nil NULL

#define MAX_KATA 50
#define MAX_SINONIM 5

#define Kata(P)    ((P)->kata)
#define Sinonim(P) ((P)->sinonim)
#define Left(P)    ((P)->left)
#define Right(P)   ((P)->right)

#ifndef TRUE
#define TRUE true
#endif

#ifndef FALSE
#define FALSE false
#endif

typedef struct tNode *address;
typedef struct tNode {
	char kata[MAX_KATA];
	char sinonim[MAX_SINONIM][MAX_KATA];
	address left;
	address right;
} Node;

typedef address BinTree;
typedef address ListOfNode;

address Alokasi(const char *kata, char sinonim[][MAX_KATA], int jumlahSinonim);
void Dealokasi(address *P);

boolean IsEmpty(BinTree P);
void CreateEmpty(BinTree *P);

const char *GetAkar(BinTree P);
BinTree GetLeft(BinTree P);
BinTree GetRight(BinTree P);

BinTree Tree(const char *kata, BinTree L, BinTree R);
void MakeTree(const char *kata, BinTree L, BinTree R, BinTree *P);
void BuildTree(BinTree *P);

boolean IsUnerLeft(BinTree P);
boolean IsUnerRight(BinTree P);
boolean IsBiner(BinTree P);

void Preorder(BinTree P);
void Inorder(BinTree P);
void Postorder(BinTree P);
void PrintTree(BinTree P, char tab[]);

boolean Search(BinTree P, const char *kata);
address SearchNode(BinTree P, const char *kata);
Node *CariSinonim(Node *root, const char *kata);
void PrintSinonim(Node *node);
void SearchPrefix(Node *root, const char *prefix, int *count);

int NbElmt(BinTree P);
int NbDaun(BinTree P);
boolean IsSkewLeft(BinTree P);
boolean IsSkewRight(BinTree P);
int Level(BinTree P, const char *kata);

void AddDaunTerkiri(BinTree *P, const char *kata);
void AddDaun(BinTree *P, const char *parentKata, const char *anakKata, boolean InputKiri);
void DelDaunTerkiri(BinTree *P, char *kata);
void DelDaun(BinTree *P, const char *kata);

ListOfNode MakeListDaun(BinTree P);
ListOfNode MakeListPreoder(BinTree P);
ListOfNode MakeListLevel(BinTree P, int N);

BinTree BuildBalanceTree(int n);

void LoadKamus(Node **root, const char *filename);
void FreeTree(BinTree *P);

boolean BSearch(BinTree P, const char *kata);
BinTree InsSearch(BinTree *P, const char *kata);
void Delete(BinTree *P, const char *kata);
void DelBTree(BinTree *P, const char *kata);

void CetakKodeHuffman(BinTree root, int jalur[], int kedalaman);

#endif