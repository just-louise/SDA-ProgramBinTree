#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <string.h>

/* Mengalokasikan node baru dengan nilai X */
addressQ AlokasiQ(infotype X) {
    addressQ P = (addressQ)malloc(sizeof(ElmtList));
    if (P != NULL) {
        strcpy(Info(P), X);
        Next(P) = Nil;
    }
    return P;
}

/* Membebaskan memori node P */
void DealokasiQ(addressQ *P) {
    free(*P);
    *P = Nil;
}

/* Mengecek apakah queue kosong */
boolean IsEmptyQ(queue Q) {
    return (Front(Q) == Nil && Rear(Q) == Nil);
}

/* Inisialisasi queue menjadi kosong */
void Initial(queue *Q) {
    Front(*Q) = Nil;
    Rear(*Q) = Nil;
}

/* Set front queue ke node berikutnya */
void setFront(queue *Q) {
    if (!IsEmptyQ(*Q)) {
        Front(*Q) = Next(Front(*Q));
        if (Front(*Q) == Nil) {
            Rear(*Q) = Nil;
        }
    }
}

/* Set rear queue ke node baru (dipakai internal) */
void setRear(queue *Q) {
    if (!IsEmptyQ(*Q)) {
        addressQ temp = Front(*Q);
        while (Next(temp) != Nil) {
            temp = Next(temp);
        }
        Rear(*Q) = temp;
    }
}

/* Menambahkan elemen data ke belakang queue (enqueue) */
void Insert(queue *Q, infotype data) {
    addressQ P = AlokasiQ(data);
    if (P == Nil) {
        printf("Alokasi gagal! Memori penuh.\n");
        return;
    }

    if (IsEmptyQ(*Q)) {
        Front(*Q) = P;
        Rear(*Q) = P;
    } else {
        Next(Rear(*Q)) = P;
        Rear(*Q) = P;
    }
}

/* Mengambil dan menghapus elemen dari depan queue (dequeue) */
void DeleteQ(queue *Q, infotype *data) {
    if (IsEmptyQ(*Q)) {
        printf("Queue kosong! Tidak ada yang bisa dihapus.\n");
        return;
    }

    addressQ P = Front(*Q);
    strcpy(*data, Info(P));
    setFront(Q);
    DealokasiQ(&P);
}

/* Menampilkan semua elemen queue dari front ke rear */
void PrintQueue(queue Q) {
    if (IsEmptyQ(Q)) {
        printf("Queue kosong.\n");
        return;
    }

    printf("Isi Queue (front -> rear): ");
    addressQ temp = Front(Q);
    while (temp != Nil) {
        printf("%s", Info(temp));
        if (Next(temp) != Nil) printf(" -> ");
        temp = Next(temp);
    }
    printf("\n");
}
