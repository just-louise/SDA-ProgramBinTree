#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "binTree.h"

static void copy_string(char destination[], const char *source, size_t capacity) {
    if (capacity == 0) {
        return;
    }

    if (source == NULL) {
        destination[0] = '\0';
        return;
    }

    strncpy(destination, source, capacity - 1);
    destination[capacity - 1] = '\0';
}

static void copy_synonyms(char destination[][MAX_KATA], char source[][MAX_KATA], int jumlahSinonim) {
    int i;

    for (i = 0; i < MAX_SINONIM; i++) {
        destination[i][0] = '\0';
    }

    if (source == NULL) {
        return;
    }

    if (jumlahSinonim > MAX_SINONIM) {
        jumlahSinonim = MAX_SINONIM;
    }

    for (i = 0; i < jumlahSinonim; i++) {
        copy_string(destination[i], source[i], MAX_KATA);
    }
}

static boolean synonym_exists(const Node *node, const char *synonym) {
    int i;

    if (node == NULL || synonym == NULL || synonym[0] == '\0') {
        return FALSE;
    }

    for (i = 0; i < MAX_SINONIM; i++) {
        if (Sinonim(node)[i][0] != '\0' && strcmp(Sinonim(node)[i], synonym) == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

static void merge_synonyms(Node *node, char source[][MAX_KATA], int jumlahSinonim) {
    int i;
    int slot;

    if (node == NULL || source == NULL) {
        return;
    }

    if (jumlahSinonim > MAX_SINONIM) {
        jumlahSinonim = MAX_SINONIM;
    }

    for (i = 0; i < jumlahSinonim; i++) {
        if (source[i][0] == '\0' || synonym_exists(node, source[i])) {
            continue;
        }

        slot = 0;
        while (slot < MAX_SINONIM && Sinonim(node)[slot][0] != '\0') {
            slot++;
        }

        if (slot < MAX_SINONIM) {
            copy_string(Sinonim(node)[slot], source[i], MAX_KATA);
        }
    }
}

static BinTree insert_node(BinTree P, const char *kata, char sinonim[][MAX_KATA], int jumlahSinonim) {
    int comparison;

    if (IsEmpty(P)) {
        return Alokasi(kata, sinonim, jumlahSinonim);
    }

    comparison = strcmp(kata, Kata(P));
    if (comparison < 0) {
        Left(P) = insert_node(Left(P), kata, sinonim, jumlahSinonim);
    } else if (comparison > 0) {
        Right(P) = insert_node(Right(P), kata, sinonim, jumlahSinonim);
    } else {
        merge_synonyms(P, sinonim, jumlahSinonim);
    }

    return P;
}

static address delete_minimum(BinTree *P) {
    address result;

    if (*P == Nil) {
        return Nil;
    }

    if (Left(*P) == Nil) {
        result = *P;
        *P = Right(*P);
        result->left = Nil;
        result->right = Nil;
        return result;
    }

    return delete_minimum(&Left(*P));
}

static void to_lower_string(char *text) {
    if (text == NULL) {
        return;
    }

    while (*text != '\0') {
        *text = (char)tolower((unsigned char)*text);
        text++;
    }
}

static boolean prefix_match_case_insensitive(const char *word, const char *prefix) {
    char wordCopy[MAX_KATA];
    char prefixCopy[MAX_KATA];

    if (word == NULL || prefix == NULL) {
        return FALSE;
    }

    copy_string(wordCopy, word, MAX_KATA);
    copy_string(prefixCopy, prefix, MAX_KATA);
    to_lower_string(wordCopy);
    to_lower_string(prefixCopy);

    if (strlen(prefixCopy) > strlen(wordCopy)) {
        return FALSE;
    }

    return (strncmp(wordCopy, prefixCopy, strlen(prefixCopy)) == 0);
}

static void search_prefix_inorder(Node *root, const char *prefix, int *count) {
    if (root == NULL || prefix == NULL || count == NULL || *count >= 10) {
        return;
    }

    search_prefix_inorder(Left(root), prefix, count);

    if (*count >= 10) {
        return;
    }

    if (prefix_match_case_insensitive(Kata(root), prefix)) {
        printf("%s\n", Kata(root));
        (*count)++;
        if (*count >= 10) {
            return;
        }
    }

    search_prefix_inorder(Right(root), prefix, count);
}

static void trim_token(char *text) {
    char *start;
    char *end;

    if (text == NULL) {
        return;
    }

    start = text;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        start++;
    }

    if (start != text) {
        memmove(text, start, strlen(start) + 1);
    }

    if (text[0] == '\0') {
        return;
    }

    end = text + strlen(text) - 1;
    while (end >= text && isspace((unsigned char)*end)) {
        *end = '\0';
        if (end == text) {
            break;
        }
        end--;
    }
}

address Alokasi(const char *kata, char sinonim[][MAX_KATA], int jumlahSinonim) {
    address P = (address)malloc(sizeof(Node));

    if (P != Nil) {
        copy_string(Kata(P), kata, MAX_KATA);
        copy_synonyms(Sinonim(P), sinonim, jumlahSinonim);
        Left(P) = Nil;
        Right(P) = Nil;
    }

    return P;
}

void Dealokasi(address *P) {
    if (P != NULL && *P != Nil) {
        free(*P);
        *P = Nil;
    }
}

boolean IsEmpty(BinTree P) {
    return (P == Nil);
}

void CreateEmpty(BinTree *P) {
    if (P != NULL) {
        *P = Nil;
    }
}

const char *GetAkar(BinTree P) {
    return IsEmpty(P) ? NULL : Kata(P);
}

BinTree GetLeft(BinTree P) {
    return IsEmpty(P) ? Nil : Left(P);
}

BinTree GetRight(BinTree P) {
    return IsEmpty(P) ? Nil : Right(P);
}

BinTree Tree(const char *kata, BinTree L, BinTree R) {
    address P = Alokasi(kata, NULL, 0);

    if (P != Nil) {
        Left(P) = L;
        Right(P) = R;
    }

    return P;
}

void MakeTree(const char *kata, BinTree L, BinTree R, BinTree *P) {
    if (P != NULL) {
        *P = Tree(kata, L, R);
    }
}

void BuildTree(BinTree *P) {
    char kata[MAX_KATA];

    if (P == NULL) {
        return;
    }

    printf("Masukkan kata node (ketik \".\" untuk Nil/Kosong): ");
    if (scanf("%49s", kata) != 1) {
        *P = Nil;
        return;
    }

    if (strcmp(kata, ".") == 0) {
        *P = Nil;
        return;
    }

    *P = Alokasi(kata, NULL, 0);
    if (*P != Nil) {
        printf("--- Masuk ke Subpohon KIRI dari '%s' ---\n", kata);
        BuildTree(&Left(*P));

        printf("--- Masuk ke Subpohon KANAN dari '%s' ---\n", kata);
        BuildTree(&Right(*P));
    }
}

boolean IsUnerLeft(BinTree P) {
    return (P != Nil && Left(P) != Nil && Right(P) == Nil);
}

boolean IsUnerRight(BinTree P) {
    return (P != Nil && Left(P) == Nil && Right(P) != Nil);
}

boolean IsBiner(BinTree P) {
    return (P != Nil && Left(P) != Nil && Right(P) != Nil);
}

void Preorder(BinTree P) {
    if (!IsEmpty(P)) {
        printf("%s ", Kata(P));
        Preorder(Left(P));
        Preorder(Right(P));
    }
}

void Inorder(BinTree P) {
    if (!IsEmpty(P)) {
        Inorder(Left(P));
        printf("%s ", Kata(P));
        Inorder(Right(P));
    }
}

void Postorder(BinTree P) {
    if (!IsEmpty(P)) {
        Postorder(Left(P));
        Postorder(Right(P));
        printf("%s ", Kata(P));
    }
}

void PrintTree(BinTree P, char tab[]) {
    char tempTab[255];

    if (!IsEmpty(P)) {
        printf("%s%s\n", tab, Kata(P));
        snprintf(tempTab, sizeof(tempTab), "%s---", tab);
        PrintTree(Left(P), tempTab);
        PrintTree(Right(P), tempTab);
    }
}

boolean Search(BinTree P, const char *kata) {
    return (SearchNode(P, kata) != Nil);
}

address SearchNode(BinTree P, const char *kata) {
    return CariSinonim(P, kata);
}

Node *CariSinonim(Node *root, const char *kata) {
    int comparison;

    if (root == NULL || kata == NULL) {
        return Nil;
    }

    comparison = strcmp(kata, Kata(root));
    if (comparison == 0) {
        return root;
    }

    if (comparison < 0) {
        return CariSinonim(Left(root), kata);
    }

    return CariSinonim(Right(root), kata);
}

void PrintSinonim(Node *node) {
    int i;
    int nomor;

    if (node == NULL) {
        printf("Kata tidak ditemukan.\n");
        return;
    }

    printf("Sinonim dari \"%s\"\n\n", Kata(node));

    nomor = 1;
    for (i = 0; i < MAX_SINONIM; i++) {
        if (Sinonim(node)[i][0] != '\0') {
            printf("%d. %s\n", nomor, Sinonim(node)[i]);
            nomor++;
        }
    }
}

void SearchPrefix(Node *root, const char *prefix, int *count) {
    int hasil;

    if (count == NULL) {
        return;
    }

    *count = 0;
    if (prefix == NULL || prefix[0] == '\0') {
        printf("Tidak ada kata yang cocok.\n");
        return;
    }

    hasil = 0;
    search_prefix_inorder(root, prefix, &hasil);

    if (hasil == 0) {
        printf("Tidak ada kata yang cocok.\n");
    }

    *count = hasil;
}

void FreeTree(BinTree *P) {
    if (P == NULL || *P == Nil) {
        return;
    }

    FreeTree(&Left(*P));
    FreeTree(&Right(*P));
    Dealokasi(P);
}

int NbElmt(BinTree P) {
    if (IsEmpty(P)) {
        return 0;
    }

    return 1 + NbElmt(Left(P)) + NbElmt(Right(P));
}

int NbDaun(BinTree P) {
    if (IsEmpty(P)) {
        return 0;
    }

    if (Left(P) == Nil && Right(P) == Nil) {
        return 1;
    }

    return NbDaun(Left(P)) + NbDaun(Right(P));
}

boolean IsSkewLeft(BinTree P) {
    if (IsEmpty(P)) {
        return TRUE;
    }

    if (Right(P) != Nil) {
        return FALSE;
    }

    return IsSkewLeft(Left(P));
}

boolean IsSkewRight(BinTree P) {
    if (IsEmpty(P)) {
        return TRUE;
    }

    if (Left(P) != Nil) {
        return FALSE;
    }

    return IsSkewRight(Right(P));
}

int Level(BinTree P, const char *kata) {
    int leftLevel;
    int rightLevel;

    if (IsEmpty(P) || kata == NULL) {
        return 0;
    }

    if (strcmp(Kata(P), kata) == 0) {
        return 1;
    }

    leftLevel = Level(Left(P), kata);
    if (leftLevel != 0) {
        return 1 + leftLevel;
    }

    rightLevel = Level(Right(P), kata);
    if (rightLevel != 0) {
        return 1 + rightLevel;
    }

    return 0;
}

void AddDaunTerkiri(BinTree *P, const char *kata) {
    if (P == NULL) {
        return;
    }

    if (IsEmpty(*P)) {
        *P = Alokasi(kata, NULL, 0);
    } else {
        AddDaunTerkiri(&Left(*P), kata);
    }
}

void AddDaun(BinTree *P, const char *parentKata, const char *anakKata, boolean InputKiri) {
    if (P == NULL || IsEmpty(*P)) {
        return;
    }

    if (strcmp(Kata(*P), parentKata) == 0) {
        if (InputKiri) {
            if (Left(*P) == Nil) {
                Left(*P) = Alokasi(anakKata, NULL, 0);
            }
        } else {
            if (Right(*P) == Nil) {
                Right(*P) = Alokasi(anakKata, NULL, 0);
            }
        }
        return;
    }

    AddDaun(&Left(*P), parentKata, anakKata, InputKiri);
    AddDaun(&Right(*P), parentKata, anakKata, InputKiri);
}

void DelDaunTerkiri(BinTree *P, char *kata) {
    if (P == NULL || IsEmpty(*P)) {
        return;
    }

    if (Left(*P) == Nil && Right(*P) == Nil) {
        if (kata != NULL) {
            copy_string(kata, Kata(*P), MAX_KATA);
        }
        Dealokasi(P);
        return;
    }

    if (Left(*P) != Nil) {
        DelDaunTerkiri(&Left(*P), kata);
    } else {
        DelDaunTerkiri(&Right(*P), kata);
    }
}

void DelDaun(BinTree *P, const char *kata) {
    if (P == NULL || IsEmpty(*P) || kata == NULL) {
        return;
    }

    if (strcmp(Kata(*P), kata) == 0) {
        if (Left(*P) == Nil && Right(*P) == Nil) {
            Dealokasi(P);
        }
        return;
    }

    DelDaun(&Left(*P), kata);
    DelDaun(&Right(*P), kata);
}

ListOfNode MakeListDaun(BinTree P) {
    address leftList;
    address rightList;
    address temp;

    if (IsEmpty(P)) {
        return Nil;
    }

    if (Left(P) == Nil && Right(P) == Nil) {
        return Alokasi(Kata(P), NULL, 0);
    }

    leftList = MakeListDaun(Left(P));
    rightList = MakeListDaun(Right(P));

    if (leftList == Nil) {
        return rightList;
    }

    temp = leftList;
    while (Right(temp) != Nil) {
        temp = Right(temp);
    }
    Right(temp) = rightList;

    return leftList;
}

ListOfNode MakeListPreoder(BinTree P) {
    address akarList;
    address temp;

    if (IsEmpty(P)) {
        return Nil;
    }

    akarList = Alokasi(Kata(P), NULL, 0);
    Right(akarList) = MakeListPreoder(Left(P));

    temp = akarList;
    while (Right(temp) != Nil) {
        temp = Right(temp);
    }
    Right(temp) = MakeListPreoder(Right(P));

    return akarList;
}

ListOfNode MakeListLevel(BinTree P, int N) {
    address leftList;
    address rightList;
    address temp;

    if (IsEmpty(P) || N < 1) {
        return Nil;
    }

    if (N == 1) {
        return Alokasi(Kata(P), NULL, 0);
    }

    leftList = MakeListLevel(Left(P), N - 1);
    rightList = MakeListLevel(Right(P), N - 1);

    if (leftList == Nil) {
        return rightList;
    }

    temp = leftList;
    while (Right(temp) != Nil) {
        temp = Right(temp);
    }
    Right(temp) = rightList;

    return leftList;
}

BinTree BuildBalanceTree(int n) {
    char kata[MAX_KATA];
    int nL;
    int nR;
    address P;

    if (n <= 0) {
        return Nil;
    }

    nL = n / 2;
    nR = n - nL - 1;

    printf("Masukkan kata node untuk Balance Tree: ");
    if (scanf("%49s", kata) != 1) {
        return Nil;
    }

    P = Alokasi(kata, NULL, 0);
    if (P != Nil) {
        Left(P) = BuildBalanceTree(nL);
        Right(P) = BuildBalanceTree(nR);
    }

    return P;
}

void LoadKamus(Node **root, const char *filename) {
    FILE *file;
    char line[512];
    char *token;
    char kata[MAX_KATA];
    char sinonim[MAX_SINONIM][MAX_KATA];
    int jumlahSinonim;
    int loadedWords;

    if (root == NULL || filename == NULL) {
        printf("Failed to load dictionary.\n");
        return;
    }

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to load dictionary.\n");
        return;
    }

    loadedWords = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        int i;

        trim_token(line);
        if (line[0] == '\0' || line[0] == ',') {
            continue;
        }

        token = strtok(line, ",\r\n");
        if (token == NULL) {
            continue;
        }

        trim_token(token);
        if (token[0] == '\0') {
            continue;
        }

        copy_string(kata, token, MAX_KATA);

        for (i = 0; i < MAX_SINONIM; i++) {
            sinonim[i][0] = '\0';
        }

        jumlahSinonim = 0;
        while (jumlahSinonim < MAX_SINONIM) {
            token = strtok(NULL, ",\r\n");
            if (token == NULL) {
                break;
            }

            trim_token(token);
            if (token[0] == '\0') {
                continue;
            }

            copy_string(sinonim[jumlahSinonim], token, MAX_KATA);
            jumlahSinonim++;
        }

        *root = insert_node(*root, kata, sinonim, jumlahSinonim);
        loadedWords++;
    }

    fclose(file);
    printf("Loaded %d words successfully.\n", loadedWords);
}

boolean BSearch(BinTree P, const char *kata) {
    if (IsEmpty(P) || kata == NULL) {
        return FALSE;
    }

    if (strcmp(kata, Kata(P)) == 0) {
        return TRUE;
    }

    if (strcmp(kata, Kata(P)) < 0) {
        return BSearch(Left(P), kata);
    }

    return BSearch(Right(P), kata);
}

BinTree InsSearch(BinTree *P, const char *kata) {
    if (P == NULL) {
        return Nil;
    }

    if (IsEmpty(*P)) {
        *P = Alokasi(kata, NULL, 0);
        return *P;
    }

    if (strcmp(kata, Kata(*P)) < 0) {
        return InsSearch(&Left(*P), kata);
    }

    if (strcmp(kata, Kata(*P)) > 0) {
        return InsSearch(&Right(*P), kata);
    }

    return *P;
}

void Delete(BinTree *P, const char *kata) {
    DelBTree(P, kata);
}

void DelBTree(BinTree *P, const char *kata) {
    address successor;
    address temp;

    if (P == NULL || IsEmpty(*P) || kata == NULL) {
        return;
    }

    if (strcmp(kata, Kata(*P)) < 0) {
        DelBTree(&Left(*P), kata);
        return;
    }

    if (strcmp(kata, Kata(*P)) > 0) {
        DelBTree(&Right(*P), kata);
        return;
    }

    if (Left(*P) == Nil) {
        temp = *P;
        *P = Right(*P);
        free(temp);
        return;
    }

    if (Right(*P) == Nil) {
        temp = *P;
        *P = Left(*P);
        free(temp);
        return;
    }

    successor = delete_minimum(&Right(*P));
    if (successor != Nil) {
        copy_string(Kata(*P), Kata(successor), MAX_KATA);
        copy_synonyms(Sinonim(*P), Sinonim(successor), MAX_SINONIM);
        free(successor);
    }
}

void CetakKodeHuffman(BinTree root, int jalur[], int kedalaman) {
    int i;

    if (IsEmpty(root)) {
        return;
    }

    if (Left(root) != Nil) {
        jalur[kedalaman] = 0;
        CetakKodeHuffman(Left(root), jalur, kedalaman + 1);
    }

    if (Right(root) != Nil) {
        jalur[kedalaman] = 1;
        CetakKodeHuffman(Right(root), jalur, kedalaman + 1);
    }

    if (Left(root) == Nil && Right(root) == Nil) {
        printf("  Kata '%s'\n", Kata(root));
        for (i = 0; i < kedalaman; i++) {
            printf("%d", jalur[i]);
        }
        printf("\n");
    }
}