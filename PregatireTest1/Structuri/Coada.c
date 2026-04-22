#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
    int id;
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    unsigned char serie;
};
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file) {
    char buffer[100];
    char sep[3] = ",\n";
    fgets(buffer, 100, file);
    char* aux;
    Masina m1;
    aux = strtok(buffer, sep);
    m1.id = atoi(aux);
    m1.nrUsi = atoi(strtok(NULL, sep));
    m1.pret = atof(strtok(NULL, sep));
    aux = strtok(NULL, sep);
    m1.model = malloc(strlen(aux) + 1);
    strcpy_s(m1.model, strlen(aux) + 1, aux);

    aux = strtok(NULL, sep);
    m1.numeSofer = malloc(strlen(aux) + 1);
    strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

    m1.serie = *strtok(NULL, sep);
    return m1;
}

void afisareMasina(Masina masina) {
    printf("Id: %d\n", masina.id);
    printf("Nr. usi : %d\n", masina.nrUsi);
    printf("Pret: %.2f\n", masina.pret);
    printf("Model: %s\n", masina.model);
    printf("Nume sofer: %s\n", masina.numeSofer);
    printf("Serie: %c\n\n", masina.serie);
}
//COD COADA

typedef struct NodCoada NodCoada;
typedef struct Coada Coada;
struct NodCoada {
    Masina info;
    NodCoada* next;
    NodCoada* prev;
};
struct Coada {
    NodCoada* head;
    NodCoada* tail;
};

void enqueue(Coada* coada,Masina masinaNoua) {
    NodCoada* nodNou=(NodCoada*)malloc(sizeof(NodCoada));

    nodNou->info=masinaNoua;
    nodNou->prev=NULL;
    nodNou->next=coada->head;
    if (coada->head!=NULL) // daca mai am noduri
    {
            coada->head->prev=nodNou; // ruta inapoi de la urm nod
    }
    else
    {
        coada->tail=nodNou; //daca nu mai am e si primu si ultimu
    }
    coada->head=nodNou; //e noul prim nod
}

Masina dequeue(Coada* coada) {
    Masina masinaDequeue;
    masinaDequeue=coada->tail->info;

    if (coada->head==coada->tail) { //e un singur nod
        coada->head=NULL;
        coada->tail=NULL;
    }
    else //am mai multe noduri
    {
        coada->tail->prev->next=NULL;
        NodCoada* aux=coada->tail;
        coada->tail=coada->tail->prev;
        free(aux);
    }

    return masinaDequeue;
}



int main() {


    return 0;
}