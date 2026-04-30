#define _CRT_SECURE_NO_WARNINGS_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Telefon {
    int id;
    int RAM;
    char* producator;
}; //declarare structura Telefon

typedef struct Telefon Telefon; //alias

Telefon initializare(int id,int RAM, char* producator)
{
    Telefon telefon;
    telefon.id=id;
    telefon.RAM=RAM;
    //aloc spatiu pentru denumire producatorului
    telefon.producator=(char*)malloc(sizeof(char)*(strlen(producator)+1)); //+1 pentru \0
    strcpy(telefon.producator,producator);

    return telefon;
}

void afisare(Telefon telefon)
{
    printf("\n %d. Telefonul %s are %d GB Ram \n",telefon.id,telefon.producator,telefon.RAM);
}

void afisareVector(Telefon* vector, int nrElemente)
{
    for (int i=0;i<nrElemente;i++)
    {
        afisare(vector[i]);
    }
}
Telefon* copiazaPrimeleNElemente(Telefon* vectorInitial, int nrElemente, int nrCopiate)
{
    Telefon* vectorNou=(Telefon*)malloc(sizeof(Telefon)*nrCopiate);
    if (nrElemente>=nrCopiate) {
        for (int i=0;i<nrCopiate;i++)
        {
            vectorNou[i]=vectorInitial[i];
            /**
            Daca aveam producator (char*) copia adresa exact cum era in vectorInitial
            (facea shallow) copy deci trebuia sa fac deep copy cu:
            vectorNou[i].producator=(char*)malloc(strlen(vectorInitial[i].producator+1)
            strcpy(vectorNou[i].producator,vectorInitial[i].producator)

            --la ce este un pointer in struct trebuie sa fac deep copy--
            **/
        }
    }
    return vectorNou;
}
//Dublu Pointer->modific adresa la care pointeaza vector si vreau sa se pastreze modificarea
//
void dezalocare(Telefon** vector,int* nrElemente)
{

    /**
    Daca aveam producator (char*) trebuia sa dau free pentru fiecare producator
    pe rand, deci pargurg vectorul si le dau free:
    for(int i=0;i<*nrElemente;i++)
    {
    //(*vector)[i] pentru ca e pasat ca **vector si trebuie sa dereferentiez si
    prioritizez
     if((*vector)[i].producator!=NULL)
       free((*vector[i].producator);
    }
    **/
    free(*vector);
    *vector = NULL;
    //valoarea de la adresa nrElemente este setata 0 acum;
    *nrElemente = 0;
}

Telefon* copiazaAnumiteElememente(Telefon* vectorInitial,int nrElemente,int minimRAM,int* nrElemeteNou) {
   Telefon* vectorNou;
    int j=0;
    for (int i=0;i<nrElemente;i++)
    {
        if (vectorInitial[i].RAM>= minimRAM)
            j++;
    }
    vectorNou=(Telefon*)malloc(sizeof(Telefon)*j);
    j=0;
    for (int i=0;i<nrElemente;i++)
    {
        if (vectorInitial[i].RAM>= minimRAM)
        {
            vectorNou[j]=vectorInitial[i];
            vectorNou[j].producator=(char*)malloc(strlen(vectorInitial[i].producator)+1);
            strcpy(vectorNou[j].producator,vectorInitial[i].producator);
            j++;
        }
    }
    *nrElemeteNou=j;
    return vectorNou;
}

Telefon getPrimulConditionat(Telefon* vector,int nrElemente,char* conditie) {
   Telefon telefonGasit;
    for (int i=0;i<nrElemente;i++)
    {
        if (strcmp(vector[i].producator,conditie)==0) {
            telefonGasit=vector[i];
            telefonGasit.producator=(char*)malloc(strlen(vector[i].producator));
            strcpy(telefonGasit.producator,vector[i].producator);
            return telefonGasit;
        }

    }
    return (Telefon){-1,0,NULL};
}
int main() {
    Telefon* vectorTelefoane= NULL;
    int nrTelefoane=3;
    //aloc spatiu pt vector de telefoane
    vectorTelefoane = (Telefon*)malloc(sizeof(Telefon)*nrTelefoane);

    //initializare
    vectorTelefoane[0]=initializare(1,12,"Samsung");
    vectorTelefoane[1]=initializare(2,24,"Apple");
    vectorTelefoane[2]=initializare(3,64,"Nothing");

    afisareVector(vectorTelefoane,nrTelefoane);
    printf("\n Primele 2 elemente:\n");
    afisareVector(copiazaPrimeleNElemente(vectorTelefoane,nrTelefoane,2),2);


    printf("\n Filtrare:\n");
    int nrFiltrate=0;
    Telefon*vectorFiltrare=copiazaAnumiteElememente(vectorTelefoane,nrTelefoane,16,&nrFiltrate);
    afisareVector(vectorFiltrare,nrFiltrate);


    printf("\n PrimulConditionat Exista:\n");
    afisare(getPrimulConditionat(vectorTelefoane,nrTelefoane,"Apple"));
    printf("\n PrimulConditionat NU exista:\n");
    afisare(getPrimulConditionat(vectorTelefoane,nrTelefoane,"Aple"));

    //DEZALOCARE
    dezalocare(&vectorTelefoane,&nrTelefoane);
    afisareVector(vectorTelefoane,nrTelefoane);

    return 0;
}