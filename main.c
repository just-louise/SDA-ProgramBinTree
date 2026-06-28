#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "boolean.h"
#include "binTree.h"

void menu_autocomplete(Node *root){

}

void menu_sinonim(Node *root){

}

void menu_kalimat(Node *root, queue *Q){
    
}

int main(){
    Node *root = NULL;
    queue Q;
    int pilihan;

    Initial(&Q);
    LoadKamus(&root, "dataset/tesaurus-master/kamus.txt");

    do {
        printf("\n=== LEXIBUILD ===\n");
        printf("1. Kamus Pintar (Auto-Complete)\n");
        printf("2. Cari Sinonim\n");
        printf("3. Buat Kalimat\n");
        printf("0. Keluar \n");
        printf("Pilihan: \n");
        scanf("%d", &pilihan);

        switch(pilihan){
            case 1: menu_autocomplete(root); break;
            case 2: menu_sinonim(root); break;
            case 3: menu_kalimat(root,&Q); break;
            case 0: printf("Terima kasih dan sampai jumpa!\n"); break;
            default: printf ("Pilihan tidak valid. \n");
        }
    } while (pilihan != 0);

    FreeTree(&root);
    return 0;
}