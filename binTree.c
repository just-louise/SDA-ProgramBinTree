#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "binTree.h"
#include "boolean2.h"

BinTree Insert(BinTree P, char X) {

    if (IsEmpty(P)) {
        return Alokasi(X);
    } else {
        
        if (Left(P) == Nil) {
            Left(P) = Alokasi(X);
        } else if (Right(P) == Nil) {
            Right(P) = Alokasi(X);
        } else {
            // Jika kedua cabang penuh, rekursif masukkan ke kiri
            Left(P) = Insert(Left(P), X);
        }
        return P;
    }
}

address Alokasi(infotype X){
    address P = (address)malloc(sizeof(ElmtNode));
    if (P != Nil) {
        Info(P) = X;
        Left(P) = Nil;
        Right(P) = Nil;
        Count(P) = 0;
    }
    return P;
}

boolean IsEmpty(BinTree P){
    return (P == Nil);
}

void CreateEmpty(BinTree *P){
    *P = Nil;
}

infotype GetAkar(BinTree P){
    return Info(P);
}

BinTree GetLeft(BinTree P){
    return Left(P);
}

BinTree GetRight(BinTree P){
    return Right(P);
}

/* ******** KONSTRUKTOR ************ */

BinTree Tree(infotype X, BinTree L, BinTree R){
    address P = Alokasi(X);
    if (P != Nil) {
        Left(P) = L;
        Right(P) = R;
    }
    return P;
}

void MakeTree(infotype X, BinTree L, BinTree R, BinTree *P) {
    *P = Tree(X, L, R);
}

void BuildTree(BinTree *P) {
    infotype X;
    
    printf("Masukkan nilai node (ketik '.' untuk Nil/Kosong): ");
    scanf(" %c", &X);
    if (X == '.') {
        *P = Nil;
    } else {
        *P = Alokasi(X);
        if (*P != Nil) {
            printf("--- Masuk ke Subpohon KIRI dari '%c' ---\n", X);
            BuildTree(&Left(*P));
            
            printf("--- Masuk ke Subpohon KANAN dari '%c' ---\n", X);
            BuildTree(&Right(*P));
        }
    }
}

/* ********* PREDIKAT PENTING  **************  */

boolean IsUnerLeft(BinTree P) {
    /* Punerleft: hanya mempunyai subpohon kiri */
    return (P != Nil && Left(P) != Nil && Right(P) == Nil);
}

boolean IsUnerRight(BinTree P) {
    /* Punerright: hanya mempunyai subpohon kanan */
    return (P != Nil && Left(P) == Nil && Right(P) != Nil);
}

boolean IsBiner(BinTree P) {
    /* Biner: mempunyai subpohon kiri dan subpohon kanan */
    return (P != Nil && Left(P) != Nil && Right(P) != Nil);
}

/* ************* TRAVERSAL   ************* */

void Preorder(BinTree P) {
    
    if (!IsEmpty(P)) {
        printf("%c ", Info(P));   // Proses Akar
        Preorder(Left(P));        // Jelajahi Subpohon Kiri
        Preorder(Right(P));       // Jelajahi Subpohon Kanan
    }
}

void Inorder(BinTree P) {
    if (!IsEmpty(P)) {
        Inorder(Left(P));         // Jelajahi Subpohon Kiri
        printf("%c ", Info(P));   // Proses Akar
        Inorder(Right(P));        // Jelajahi Subpohon Kanan
    }
}

void Postorder(BinTree P) {

    if (!IsEmpty(P)) {
        Postorder(Left(P));        // Jelajahi Subpohon Kiri
        Postorder(Right(P));       // Jelajahi Subpohon Kanan
        printf("%c ", Info(P));    // Proses Akar
    }
}

void PrintTree(BinTree P, char tab[]) {

    char tempTab[255];

    if (!IsEmpty(P)) {
        // Cetak identasi saat ini diikuti data dari akar/node
        printf("%s%c\n", tab, Info(P));

        strcpy(tempTab, tab);
        strcat(tempTab, "---");

        // Rekursif cetak anak kiri dan anak kanan menggunakan tabulasi baru
        PrintTree(Left(P), tempTab);
        PrintTree(Right(P), tempTab);
    }
}

/* ************ SEARCH **************** */

boolean Search(BinTree P, infotype X) {
    /* Mengirimkan true jika ada node dari P yang bernilai X */
    if (IsEmpty(P)) {
        return FALSE;
    }
    if (Info(P) == X) {
        return TRUE;
    }
    // Cari di subpohon kiri ATAU subpohon kanan
    return (Search(Left(P), X) || Search(Right(P), X));
}

/* ************* FUNGSI LAIN *************** */

int NbElmt(BinTree P) {

    if (IsEmpty(P)) {
        return 0;
    } else {
        // Total elemen = 1 (akar) + elemen di kiri + elemen di kanan
        return 1 + NbElmt(Left(P)) + NbElmt(Right(P));
    }
}

int NbDaun(BinTree P) {
    /* Mengirimkan banyaknya daun */
    if (IsEmpty(P)) {
        return 0;
    }
    // Jika sebuah node tidak punya anak kiri DAN tidak punya anak kanan, berarti dia daun
    if (Left(P) == Nil && Right(P) == Nil) {
        return 1;
    }
    // Jika bukan daun, terus cari ke bawah (kiri dan kanan)
    return NbDaun(Left(P)) + NbDaun(Right(P));
}

boolean IsSkewLeft(BinTree P) {
    /* Mengirimkan true jika P adalah pohon condong kiri (semua node hanya punya anak kiri) */
    if (IsEmpty(P)) {
        return TRUE; // Pohon kosong dianggap condong kiri secara default
    }
    if (Right(P) != Nil) {
        return FALSE;
    }
    // Cek rekursif ke bawah sepanjang jalur kiri
    return IsSkewLeft(Left(P));
}

boolean IsSkewRight(BinTree P) {
    /* Mengirimkan true jika P adalah pohon condong kanan (semua node hanya punya anak kanan) */
    if (IsEmpty(P)) {
        return TRUE; // Pohon kosong dianggap condong kanan secara default
    }
    if (Left(P) != Nil) {
        return FALSE;
    }
    // Cek rekursif ke bawah sepanjang jalur kanan
    return IsSkewRight(Right(P));
}

int Level(BinTree P, infotype X) {

    if (IsEmpty(P)) {
        return 0;
    }

    if (Info(P) == X) {
        return 1;
    }
    
    // Cari di subpohon kiri
    int leftLevel = Level(Left(P), X);
    if (leftLevel != 0) {
        return 1 + leftLevel; // Tambah 1 level setiap kali naik ke parent
    }
    
    // Cari di subpohon kanan
    int rightLevel = Level(Right(P), X);
    if (rightLevel != 0) {
        return 1 + rightLevel; // Tambah 1 level setiap kali naik ke parent
    }
    
    return 0; // Jika tidak ditemukan di manapun
}

/* ********* OPERASI LAIN ********* */

void AddDaunTerkiri(BinTree *P, infotype X) {

    if (IsEmpty(*P)) {
        *P = Alokasi(X);
    } else {
        AddDaunTerkiri(&Left(*P), X);
    }
}

void AddDaun(BinTree *P, infotype X, infotype Y, boolean InputKiri) {

    if (IsEmpty(*P)) {
        return; // Jika pohon kosong, tidak ada parent X yang bisa dicari
    }

    // Jika ketemu node parent-nya (X)
    if (Info(*P) == X) {
        if (InputKiri) {
            if (Left(*P) == Nil) {
                Left(*P) = Alokasi(Y);
            } else {
                printf("Gagal: Anak kiri dari %c sudah terisi!\n", X);
            }
        } else {
            if (Right(*P) == Nil) {
                Right(*P) = Alokasi(Y);
            } else {
                printf("Gagal: Anak kanan dari %c sudah terisi!\n", X);
            }
        }
        return;
    }

    // Jika belum ketemu, cari ke cabang kiri dan kanan
    AddDaun(&Left(*P), X, Y, InputKiri);
    AddDaun(&Right(*P), X, Y, InputKiri);
}

void DelDaunTerkiri(BinTree *P, infotype *X) {

    if (IsEmpty(*P)) {
        return;
    }

    // Kondisi dasar: Jika ini adalah daun (tidak punya anak sama sekali)
    if (Left(*P) == Nil && Right(*P) == Nil) {
        *X = Info(*P); // Ambil infonya sebelum dihapus
        free(*P);      // Dealokasi memori
        *P = Nil;      // Set pointer parent-nya menjadi Nil
        return;
    }

    // Jika cabang kiri masih ada, prioritaskan jalan ke kiri terus
    if (Left(*P) != Nil) {
        DelDaunTerkiri(&Left(*P), X);
    } else {
        // Jika kiri kosong tapi kanan ada, maka daun terkiri berada di jalur kanan
        DelDaunTerkiri(&Right(*P), X);
    }
}

void DelDaun(BinTree *P, infotype X) {
    /* I.S   : P tidak kosong; X adalah salah satu daun */
    /* F.S   : Node X dihapus dari P jika terbukti dia adalah daun */
    if (IsEmpty(*P)) {
        return;
    }

    // Cek apakah node saat ini mengandung info X DAN dia beneran daun
    if (Info(*P) == X) {
        if (Left(*P) == Nil && Right(*P) == Nil) {
            free(*P);
            *P = Nil;
        } else {
            printf("Gagal: %c bukan sebuah simpul daun!\n", X);
        }
        return;
    }

    // Cari ke cabang kiri dan kanan secara rekursif
    DelDaun(&Left(*P), X);
    DelDaun(&Right(*P), X);
}

ListOfNode MakeListDaun(BinTree P) {
    /* Jika P adalah pohon kosong, maka menghasilkan list kosong (Nil) */
    /* Jika P bukan pohon kosong, menghasilkan list yang elemennya adalah semua daun pohon P */
    if (IsEmpty(P)) {
        return Nil;
    }

    // Jika ketemu daun, buat node list baru dengan cabang kiri dan kanan diset Nil
    if (Left(P) == Nil && Right(P) == Nil) {
        address nodeBaru = Alokasi(Info(P));
        return nodeBaru; 
    }

    // Rekursif cari daun di kiri dan kanan
    ListOfNode leftList = MakeListDaun(Left(P));
    ListOfNode rightList = MakeListDaun(Right(P));

    // Gabungkan list kiri dan list kanan (sambungkan ekor list kiri ke kepala list kanan)
    if (leftList == Nil) {
        return rightList;
    } else {
        address temp = leftList;
        while (Right(temp) != Nil) { // Geser sampai ke ujung "list" kiri
            temp = Right(temp);
        }
        Right(temp) = rightList; // Sambungkan ke list kanan
        return leftList;
    }
}

ListOfNode MakeListPreoder(BinTree P) {
    /* Jika P adalah pohon kosong, maka menghasilkan list kosong (Nil) */
    /* Jika P bukan pohon kosong, menghasilkan list yang elemennya adalah semua elemen pohon P */
    /* dengan urutan Preorder (Akar -> Kiri -> Kanan) */
    if (IsEmpty(P)) {
        return Nil;
    }

    // 1. Alokasi untuk Akar saat ini
    address akarList = Alokasi(Info(P));
    
    // 2. Rekursif buat list dari subpohon kiri dan kanan
    ListOfNode leftList = MakeListPreoder(Left(P));
    ListOfNode rightList = MakeListPreoder(Right(P));

    // 3. Sambungkan: Akar -> Kiri -> Kanan
    Right(akarList) = leftList;
    
    // Cari ujung dari list kiri untuk menyambungkan list kanan
    address temp = akarList;
    while (Right(temp) != Nil) {
        temp = Right(temp);
    }
    Right(temp) = rightList;

    return akarList;
}

ListOfNode MakeListLevel(BinTree P, int N) {
    /* Jika P adalah pohon kosong, maka menghasilkan list kosong */
    /* Jika P bukan pohon kosong, menghasilkan list yang elemennya adalah semua elemen pohon P yang levelnya N */
    if (IsEmpty(P) || N < 1) {
        return Nil;
    }

    // Kondisi dasar: Jika sudah mencapai level target (N == 1 karena akar dimulai dari level 1)
    if (N == 1) {
        return Alokasi(Info(P));
    }

    // Rekursif cari ke level bawahnya (N dikurangi 1)
    ListOfNode leftList = MakeListLevel(Left(P), N - 1);
    ListOfNode rightList = MakeListLevel(Right(P), N - 1);

    // Gabungkan list kiri dan kanan hasil buruan di level N
    if (leftList == Nil) {
        return rightList;
    } else {
        address temp = leftList;
        while (Right(temp) != Nil) {
            temp = Right(temp);
        }
        Right(temp) = rightList;
        return leftList;
    }
}

/* *********** MEMBENTUK BALANCE TREE ************* */

BinTree BuildBalanceTree(int n) {
    /* Menghasilkan sebuah balance tree dengan n node, nilai setiap node dibaca */
    if (n <= 0) {
        return Nil;
    } else {
        infotype X;
        int nL, nR;
        address P;

        // 1. Hitung pembagian node agar seimbang
        nL = n / 2;       // Jumlah node untuk subpohon kiri
        nR = n - nL - 1;  // Sisa node untuk subpohon kanan (dikurangi 1 untuk akar)

        // 2. Baca input data dari user untuk node/akar saat ini
        printf("Masukkan nilai node untuk Balance Tree: ");
        scanf(" %c", &X);

        // 3. Alokasikan akar saat ini
        P = Alokasi(X);
        if (P != Nil) {
            // 4. Bangun subpohon kiri dan kanan secara rekursif sesuai jatah nL dan nR
            Left(P) = BuildBalanceTree(nL);
            Right(P) = BuildBalanceTree(nR);
        }
        
        return P;
    }
}

/* ************** TERHADAP BINARY SEARCH TREE *************** */

boolean BSearch(BinTree P, infotype X) {
    /* Mengirimkan true jika ada node dari P yang bernilai X pada BST */
    if (IsEmpty(P)) {
        return FALSE;
    }
    if (Info(P) == X) {
        return TRUE;
    }
    
    // Memanfaatkan sifat BST untuk mempercepat pencarian (efisien O(log n))
    if (X < Info(P)) {
        return BSearch(Left(P), X);  // Sesuai aturan, nilai kecil pasti di kiri
    } else {
        return BSearch(Right(P), X); // Nilai besar pasti di kanan
    }
}

BinTree InsSearch(BinTree *P, infotype X) {
    /* Menghasilkan sebuah pohon Binary Search Tree P dengan tambahan X. */
    /* Belum ada simpul P yang bernilai X. */
    if (IsEmpty(*P)) {
        *P = Alokasi(X);
        return *P;
    }
    
    if (X < Info(*P)) {
        return InsSearch(&Left(*P), X);  // Lempar ke kiri jika lebih kecil
    } else if (X > Info(*P)) {
        return InsSearch(&Right(*P), X); // Lempar ke kanan jika lebih besar
    }
    
    return *P; // Jika ternyata X sudah ada (tidak boleh duplikat di BST)
}

void DelBTree(BinTree *P, infotype X) {

    if (IsEmpty(*P)) {
        return;
    }

    // 1. Cari dulu posisi node X yang mau dihapus
    if (X < Info(*P)) {
        DelBTree(&Left(*P), X);
    } else if (X > Info(*P)) {
        DelBTree(&Right(*P), X);
    } 
    // 2. Jika node X sudah ditemukan (Info(*P) == X)
    else {
        address temp;
        
        // Kasus 1: Node adalah daun atau hanya punya 1 anak (anak kanan)
        if (Left(*P) == Nil) {
            temp = *P;
            *P = Right(*P); // Sambungkan langsung ke anak kanannya
            free(temp);
        }
        // Kasus 2: Node hanya punya 1 anak (anak kiri)
        else if (Right(*P) == Nil) {
            temp = *P;
            *P = Left(*P);  // Sambungkan langsung ke anak kirinya
            free(temp);
        }
        // Kasus 3: Node punya 2 anak (Biner murni)
        else {
            // Cari kandidat pengganti dari subpohon kanan yang paling kiri (nilai terkecil di kanan)
            address successor = Right(*P);
            while (Left(successor) != Nil) {
                successor = Left(successor);
            }
            
            // Salin nilai successor ke node yang ingin dihapus
            Info(*P) = Info(successor);
            
            // Hapus node successor asli yang nilainya baru saja kita salin tadi
            DelBTree(&Right(*P), Info(successor));
        }
    }
}

/*Huffman*/

void CetakKodeHuffman(BinTree root, int jalur[], int kedalaman) {
	int i;
    if (IsEmpty(root)) return;

    // Jika belok KIRI, catat '0' di array jalur
    if (Left(root) != Nil) {
        jalur[kedalaman] = 0;
        CetakKodeHuffman(Left(root), jalur, kedalaman + 1);
    }

    // Jika belok KANAN, catat '1' di array jalur
    if (Right(root) != Nil) {
        jalur[kedalaman] = 1;
        CetakKodeHuffman(Right(root), jalur, kedalaman + 1);
    }

    // Jika sampai di DAUN (Leaf), cetak karakter dan kode binernya
    if (Left(root) == Nil && Right(root) == Nil) {
        printf("  Huruf '%c' | Frekuensi: %2d | Kode: ", Info(root), Count(root));
        for (i = 0; i < kedalaman; i++) {
            printf("%d", jalur[i]);
        }
        printf("\n");
    }
}
