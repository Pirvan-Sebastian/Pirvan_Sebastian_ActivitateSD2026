#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt


struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;
typedef struct NodLDI NodLDI;
typedef struct InformatiiLista InformatiiLista;
//creare structura pentru un nod dintr-o lista dublu inlantuita
struct NodLDI {
	Masina info;
	NodLDI* next;
	NodLDI* prev;
};
//creare structura pentru Lista Dubla
struct InformatiiLista {
	NodLDI* head;
	NodLDI* tail;
	int nrNoduri;
};
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
void afisareListaMasiniInceput(InformatiiLista listaDubla) {
	NodLDI* pAux= listaDubla.head;

	while (pAux!=NULL)
	{
		afisareMasina(pAux->info);
		pAux=pAux->next;
	}
}

void afisareListaMasiniFinal(InformatiiLista listaDubla) {
	NodLDI* pAux = listaDubla.tail;
	while (pAux!=NULL)
	{
		afisareMasina(pAux->info);
		pAux=pAux->prev;
	}
}

void adaugaMasinaFinal(InformatiiLista* listaDubla, Masina masinaNoua) {
	NodLDI* nodNou=(NodLDI*)malloc(sizeof(NodLDI));

	nodNou->info=masinaNoua;
	nodNou->next=NULL;
	nodNou->prev=listaDubla->tail;

	if (listaDubla->tail!=NULL)
	{
		listaDubla->tail->next=nodNou;
	}
	//daca NU mai am noduri in lista nodul adaugat acum devine si
	//head si tail.
	else
	{
		listaDubla->head=nodNou;
	}
	listaDubla->tail=nodNou;
	listaDubla->nrNoduri++;
}

void adaugaMasinaInceput(InformatiiLista* listaDubla,Masina masinaNoua) {
	NodLDI* nodNou=(NodLDI*)malloc(sizeof(NodLDI));

	nodNou->info=masinaNoua;
	nodNou->prev=NULL;
	nodNou->next=listaDubla->head;

	if (listaDubla->head!=NULL) //daca mai am noduri
	{
		listaDubla->head->prev=nodNou;
	}
	//e primul nod bagat deci si tail=nodNou
	else
	{
		listaDubla->tail=nodNou;
	}
	//orice ar fi head devine nodNou
	listaDubla->head=nodNou;
	listaDubla->nrNoduri++;
}
InformatiiLista citireLDMasiniFisier(const char* numeFisier) {
	FILE* file=fopen(numeFisier,"r");
	InformatiiLista listaDubla;
	//initializez structura cu valori default
	listaDubla.head=NULL;
	listaDubla.tail=NULL;
	listaDubla.nrNoduri=0;

	while (!feof(file)) {
		adaugaMasinaFinal(&listaDubla,citireMasinaDinFisier(file));
	}
	fclose(file);

	return listaDubla;
}

void stergereDupaID(InformatiiLista* listaDubla,int idCautat) {
	NodLDI* pNod=listaDubla->head;

	while (pNod!=NULL && pNod->info.id!=idCautat)
	{
		pNod=pNod->next;
	}

	// NodLDI* auxiliar=pNod; //pt dezalocare
	//singurul NOD
	if (pNod->prev==NULL && pNod->next==NULL)
	{
		listaDubla->head = NULL;
		listaDubla->tail = NULL;
	}
	//Ultimu
	else if (pNod->next==NULL)
	{
		pNod->prev->next=NULL;
		listaDubla->tail=pNod->prev;
	}
	//primu
	else if ( pNod->prev==NULL)
	{
		pNod->next->prev=NULL;
		listaDubla->head=pNod->next;
	}
	//la mijloc
	else
	{
		pNod->prev->next=pNod->next;
		pNod->next->prev=pNod->prev;
	}
}
//dezalocare ca la LSI -> merg de la head la tail (while(listaDubla->head!=NULL)
//pot declara un auxiliar = listaDubla->first ca sa nu ma incurc, dar
//listaDubla->first este practic headLista. Modific deci *ListaDubla in apel functie
int main() {
	InformatiiLista listaDubla=citireLDMasiniFisier("masini.txt");
	afisareListaMasiniInceput(listaDubla);

	return 0;
}