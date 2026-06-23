/* File    : bintree.h 	*/
/* Desk    : Deklarasi Binary Tree secara rekursif  	*/
/* Oleh    : ANI RAHMANI / 23501007  			*/
/* Tgl	   : 21 / 11 / 2001	     			*/

#ifndef BINTREE_H
#define BINTREE_H

#include <stdlib.h>
#include "boolean2.h"

#define Nil NULL
#define Info(P)  (P)->info
#define Left(P)  (P)->left
#define Right(P) (P)->right
#define Count(P) (P)->count

typedef char infotype;
typedef struct tElmtNode *address;
typedef struct tElmtNode {
			infotype info;
			address left;
			address right;
			int count;
		} ElmtNode;

typedef address BinTree;
typedef address ListOfNode; /* List  yg elemennya adalah ElmtNode */ 

BinTree Insert(BinTree P, char X);

address Alokasi(infotype X);
/* Menghasilkan  address hasil alokasi sebuah  Node 	*/
/* Jika alokasi berhasil, maka  address tidak NIl   	*/
/* Info(P)=X, Left(P)=Nil,Right(P)=Nil, dan Count(P)=0 	*/
/* Jika alokasi gagal mengembalikan Nil  		*/

boolean IsEmpty(BinTree P);
/* Mengembalikan true jika pohon kosong */

void CreateEmpty(BinTree *P);
/* Membuat  Tree   kosong  */

infotype GetAkar(BinTree P);
/* Mengirimkan nilai Akar pohon biner P */

BinTree GetLeft(BinTree P);
/* Mengirimkan anak kiri pohon biner P  */

BinTree GetRight(BinTree P);
/* Mengirimkan anak kanan pohon biner P  */

/* ******** KONSTRUKTOR ************ */
BinTree Tree(infotype X, BinTree L, BinTree R);
/* Menghasilkan sebuah pohon Biner dari A, L, dan R jika Alokasi berhasil */
/* Menghasilkan pohon kosong Nil, jika alokasi gagal 			  */

void MakeTree(infotype X, BinTree L, BinTree R, BinTree *P);
/* I.S   : Sembarang 	*/
/* F.S   : Menghasilkan sebuah pohon biner P dari A,L,dan R, jika alokasi */
/*         berhasil; Menghasilkan pohon P yang kosong jika alokasi gagal  */

void BuildTree(BinTree *P);
/* Membentuk sebuah pohon biner P dari pita karakter yang dibaca 	*/
/* I.S   : Pita berisi 'kostanta' pohon dalam bentuk prefiks, memory 	*/
/*         pasti cukup, alokasi pasti berhasil 				*/
/* F.S   : P dibentuk dari Ekspresi dalam Pita   			*/

/* ********* PREDIKAT PENTING  **************  */

boolean IsUnerLeft(BinTree P);
/* Mengirimkan True jika pohon biner tidak kosong; P adalah pohon  */
/* unerleft : hanya mempunyai subpohon kiri 			   */

boolean IsUnerRight(BinTree P);
/* Mengirimkan True jika pohon biner tidak kosong; P adalah pohon  */
/* unerright : hanya mempunyai subpohon kanan          		   */

boolean IsBiner(BinTree P);
/* Mengirimkan true jika pohon biner tidak kosong; P adalah pohon */
/* biner : mempunyai subpohon kiri dan subpohon kanan 		  */

/* ************* TRAVERSAL   ************* */

void Preorder(BinTree P);
/* I.S  : P terdefinisi   					    */
/* F.S  : semua simpul P sudah diproses secara Preorder; akar, kiri */
/*        kanan (dengan Proses (P)) 				    */

void Inorder(BinTree P);
/* I.S  : P terdefinisi   					    */
/* F.S  : semua simpul P sudah diproses secara Inorder; kiri, akar  */
/*        kanan (dengan Proses (P)) 				    */

void Postorder(BinTree P);
/* I.S  : P terdefinisi   					    */
/* F.S  : semua simpul P sudah diproses secara Postorder; kiri,     */    
/* 	  kanan, akar (dengan Proses (P)) 			    */

void PrintTree(BinTree P, char tab[]);
/* I.S  : P terdefinisi, h adalah jarak indentasi	*/
/* F.S  : semua simpul P sudah ditulis 			*/


/* ************ SEARCH **************** */
boolean Search(BinTree P, infotype X);
/* Mengirimkan true jika ada node dari P yang bernilai X */

/* ************* FUNGSI LAIN *************** */
int NbElmt(BinTree P);
/* Mengirimkan banyaknya elemen (Node) pohon biner P */

int NbDaun(BinTree P);
/* Mengirimkan banyaknya daun (Node) pohon biner P */

boolean IsSkewLeft (BinTree P);
/* Mengirimkan true jika P adalah pohon condong kiri */

boolean IsSkewRight(BinTree P);
/* Mengirimkan true jika P adalah pohon condong kanan */

int Level(BinTree P, infotype X);
/* Mengirinkan level dari Node X yang merupakan salah satu simpul */
/* dari pohon biner P. Akar(P) level-nya adalah 1. Pohon P  tidak */
/* kosong 	*/

/* ********* OPERASI LAIN ********* */
void AddDaunTerkiri(BinTree *P, infotype X);
/* I.S   : P boleh kosong 	*/
/* F.S   : P bertambah simpulnya, dengan X sbg simpul daun terkiri */  		

void AddDaun(BinTree *P, infotype X, infotype Y, boolean InputKiri);
/* I.S   : P boleh kosong 	*/
/* F.S   : P bertambah simpulnya, dengan Y sbg anak kiri X 		*/
/*	   jika kiri); atau sebagai anak kanan X (jika Not Kiri)	*/

void DelDaunTerkiri(BinTree *P, infotype *X);
/* I.S   : P tidak kosong 	*/
/* F.S   : P dihapus   daun terkirinya, dan didealokasi dengan X adalah  */
/*         info yang semula disimpan pada daun terkiri yang dihapus      */

void DelDaun(BinTree *P, infotype X);
/* I.S   : P tidak kosong; X adalah salah  satu daun 	*/
/* F.S   : X dihapus dari P    */



ListOfNode MakeListDaun(BinTree  P);
/* Jika P adalah pohon kosong, maka menghasilkan list kosong   */
/* Jika P bukan pohon kosong, menghasilkan list yang elemennya  */
/* adalah semua daun pohon P; Jika semua alokasi berhasil.      */
/* Menghasilkan list kosong jika ada alokasi yang gagal 	*/

ListOfNode MakeListPreoder(BinTree  P);
/* Jika P adalah pohon kosong, maka menghasilkan list kosong     */
/* Jika P bukan pohon kosong, menghasilkan list yang elemennya   */
/* adalah semua elemen pohon P dengan urutan Preorder,  jk semua */
/* alokasi berhasil 						 */
/* Menghasilkan list kosong jika ada alokasi yang gagal 	 */


ListOfNode MakeListLevel(BinTree  P, int N);
/* Jika P adalah pohon kosong, maka menghasilkan list kosong    */
/* Jika P bukan pohon kosong, menghasilkan list yang elemennya  */
/* adalah semua elemen pohon P yang levelnya N; Jika semua      */
/* alokasi berhasil. Menghasilkan list kosong jika ada alokasi  */
/* yang gagal 	*/

/* *********** MEMBENTUK BALANCE TREE ************* */
BinTree BuildBalanceTree(int n);
/* Menghasilkan sebuah balance tree dengan n node, nilai setiap */
/* node dibaca 							*/

/* ************** TERHADAP BINARY SEARCH TREE *************** */
boolean BSearch(BinTree P, infotype X);
/* Mengirimkan true jika ada node dari P yang bernilai X   */

BinTree InsSearch(BinTree *P, infotype X);
/* Menghasilkan sebuah pohon Binary Search Tree P dengan tambahan */
/* X. Belum ada simpul P yang bernilai X 			  */

void DelBTree(BinTree *P, infotype X);
/* I.S  : Pohon P tidak kosong 					   */
/* F.S  : Nilai yang dihapus pasti ada, sebuah node dengan nilai X */
/*        dihapus 						   */

/*Huffman*/
void CetakKodeHuffman(BinTree root, int jalur[], int kedalaman);


#endif

