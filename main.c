#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "boolean.h"
#include "binTree.h"

void menu_autocomplete(Node *root){
    char prefix [50];
    int count;

    printf("\n=== KAMUS PINTAR ===\n");
    printf("Masukkan awalan kata (min. 3 huruf): ");
    scanf("%s", prefix);

    if (strlen(prefix) < 3){
        printf("Awalan kata minimal 3 huruf!\n");
        return;
    }

    SearchPrefix(root, prefix, &count);
}

void menu_sinonim(Node *root){
    char kata [50];
    Node *hasil;

    printf("\n=== CARI SINONIM ===\n");
    printf("Masukkan kata: ");
    scanf("%s", kata);

    hasil = CariSinonim(root, kata);
    if (hasil != NULL){
        PrintSinonim(hasil);
    } else {
        printf("Kata \"%s\" tidak ditemukan dalam kamus.\n", kata);
    }
}

void menu_kalimat(Node *root, queue *Q){
    int pilihan;
    char kata[50];

    do {
        printf("\n=== RUANG KERJA ===\n");
        printf("1. Cari Awalan Kata\n");
        printf("2. Cari Sinonim\n");
        printf("0. Selesai\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch(pilihan){
            case 1:
                printf("Masukkan awalan kata (min 3 huruf): ");
                scanf("%s", kata);

                if (strlen(kata) < 3){
                    printf("awalan kata minimal 3 huruf! \n");
                    break;
                }

                int count;
                SearchPrefix(root, kata, &count);

                if (count > 0){
                    printf("Pilih kata: ");
                    scanf("%s", kata);
                    Insert(Q,kata);
                    printf("Kata \"%s\" ditambahkan ke kalimat.\n", kata);
                }
                break;
            case 2: 
                break;
            case 0:
                break;
            default: printf ("Pilihan tidak valid. \n");
        }


    } while (pilihan !=0);
}

int main(){
    Node *root = NULL;
    queue Q;
    int pilihan;

    Initial(&Q);
    LoadKamus(&root, "dataset/kamus.txt");

    do {
        printf("\n=== LEXIBUILD ===\n");
        printf("1. Kamus Pintar (Auto-Complete)\n");
        printf("2. Cari Sinonim\n");
        printf("3. Buat Kalimat\n");
        printf("0. Keluar \n");
        printf("Pilihan: ");
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