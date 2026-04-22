#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct NodLSI {
    int info;
    struct NodLSI* next;
};
struct HashTable{
    int dimensiune;
    struct NodLSI** vectorListe;
};

typedef struct HashTable HashTable;
typedef struct NodLSI NodLSI;

HashTable initializareHashTable(int dimensiune) {
    HashTable hashTable;

    hashTable.dimensiune=dimensiune;
    hashTable.vectorListe=(NodLSI**)malloc(sizeof(NodLSI)*dimensiune);
    for(int i=0;i<dimensiune;i++) {
        hashTable.vectorListe[i]=NULL;
    }
    return hashTable;
}

int calculeazaHash(int idMasina,int dimensiune) {
    return (idMasina*25)%dimensiune;
}

void inserareHash(HashTable hashTable, int info) {
    int hashMasina=calculeazaHash(info,hashTable.dimensiune);
    inserareLista(hashTable.vectorListe[hashMasina],info);
}
int main() {


    return 0;
}