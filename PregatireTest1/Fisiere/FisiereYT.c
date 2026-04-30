#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

struct Masina{
    int id;
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    char serie;
};

typedef struct Masina Masina;

void adaugaMasinaInVector(Masina** vectorMasini,int* nrMasini,Masina masinaNoua) {
   *vectorMasini=(Masina*)realloc(*vectorMasini,sizeof(Masina)*((*nrMasini)+1));
    int j=*nrMasini;
    (*vectorMasini)[j]=masinaNoua;
    j++;
    *nrMasini=j;
}

Masina citireMasinaFisier(FILE* file) {
    //1,3,5000,Astra,Ionescu,A
    Masina masinaCitita;
    //declar un buffer in care bag linia citita
    char buffer[100];

    char sep[3]=",\n"; //separatorii datelor + sfarsit de sircaract
    //citeste din file maxim 100 caractere si le pune in buffer
    //fgets(undePun,catPunMaxim,deUndePun);
    fgets(buffer,100,file);
    //strtok(undeSepar->de unde incep sa ma uit,separatorii) -> separa string ul dat(undeSepar) dupa delimitari
    //si returneaza adresa de inceput a segmentului, si pune NULL dupa el(la separator).
    masinaCitita.id=atoi(strtok(buffer,sep)); //->atoi == ascii to int
    //el isi marcheaza pana unde a ajuns cu NULL, cand vreau sa continui ii dau
    //NULL,separatori si se uita unde a ajuns la ultima folosire, continuand de acolo
    masinaCitita.nrUsi=atoi(strtok(NULL,sep));
    masinaCitita.pret=atof(strtok(NULL,sep));
    //model
    char* aux=strtok(NULL,sep);
    masinaCitita.model=(char*)malloc(strlen(aux)+1);
    strcpy(masinaCitita.model,aux);

    aux=strtok(NULL,sep);
    masinaCitita.numeSofer=(char*)malloc(strlen(aux)+1);
    strcpy(masinaCitita.numeSofer,aux);

    masinaCitita.serie= *strtok(NULL,sep);

    return masinaCitita;

}


Masina* citireVectorMasiniFisier(const char* numeFisier,int* nrMasiniCitite) {

    FILE* file=fopen(numeFisier,"r");
    Masina* vectorMasiniCititie;
    *nrMasiniCitite=0;
    while (!feof(file))
    {
        adaugaMasinaInVector(&vectorMasiniCititie,nrMasiniCitite,citireMasinaFisier(file));
    }
    fclose(file);
}

int main() {
    
    return 0;
}