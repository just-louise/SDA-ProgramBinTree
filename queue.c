#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* Mengalokasikan node baru dengan nilai X */
address Alokasi(infotype X) {
    address P = (address)malloc(sizeof(ElmtList));
    if (P != NULL) {
        Info(P) = X;
        Next(P) = Nil;
    }
    return P;
}

/* Membebaskan memori node P */
void Dealokasi(address *P) {
    free(*P);
    *P = Nil;
}

/* Mengecek apakah queue kosong */
boolean IsEmpty(queue Q) {
    return (Front(Q) == Nil && Rear(Q) == Nil);
}

/* Inisialisasi queue menjadi kosong */
void Initial(queue *Q) {
    Front(*Q) = Nil;
    Rear(*Q) = Nil;
}

/* Set front queue ke node berikutnya */
void setFront(queue *Q) {
    if (!IsEmpty(*Q)) {
        Front(*Q) = Next(Front(*Q));
        if (Front(*Q) == Nil) {
            Rear(*Q) = Nil;
        }
    }
}

/* Set rear queue ke node baru (dipakai internal) */
void setRear(queue *Q) {
    /* Fungsi ini biasanya dipakai untuk update rear ke node terakhir.
       Implementasi lengkap ada di Insert. */
    if (!IsEmpty(*Q)) {
        address temp = Front(*Q);
        while (Next(temp) != Nil) {
            temp = Next(temp);
        }
        Rear(*Q) = temp;
    }
}

/* Menambahkan elemen data ke belakang queue (enqueue) */
void Insert(queue *Q, infotype data) {
    address P = Alokasi(data);
    if (P == Nil) {
        printf("Alokasi gagal! Memori penuh.\n");
        return;
    }

    if (IsEmpty(*Q)) {
        Front(*Q) = P;
        Rear(*Q) = P;
    } else {
        Next(Rear(*Q)) = P;
        Rear(*Q) = P;
    }
}

/* Mengambil dan menghapus elemen dari depan queue (dequeue) */
void Delete(queue *Q, infotype *data) {
    if (IsEmpty(*Q)) {
        printf("Queue kosong! Tidak ada yang bisa dihapus.\n");
        return;
    }

    address P = Front(*Q);
    *data = Info(P);
    setFront(Q);
    Dealokasi(&P);
}

/* Menampilkan semua elemen queue dari front ke rear */
void PrintQueue(queue Q) {
    if (IsEmpty(Q)) {
        printf("Queue kosong.\n");
        return;
    }

    printf("Isi Queue (front -> rear): ");
    address temp = Front(Q);
    while (temp != Nil) {
        printf("%c", Info(temp));
        if (Next(temp) != Nil) printf(" -> ");
        temp = Next(temp);
    }
    printf("\n");
}
