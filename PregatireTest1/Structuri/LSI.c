#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;
typedef struct NodLSI NodLSI;

//creare structura pentru un nod dintr-o lista simplu inlantuita
struct NodLSI {
	//valoarea din nod
	 Masina info;
	//pointer la urmatorul Nod din lista
	NodLSI* next;
};

Masina citireMasinaFisier(FILE* file) {
	//1,3,5000,Astra,Ionescu,A
	Masina masinaCitita;
	//declar un buffer in care bag linia citita
	char buffer[100];

	char sep[3]=",\n"; //separatorii datelor + sfarsit de sircaract
	//citeste din file maxim 100 caractere si le pune in buffer
	//fgets(undePun,catPunMaxim,deUndePun);
	fgets(buffer,100,file);

	char* aux=strtok(buffer,sep);
	masinaCitita.id=atoi(aux);
	masinaCitita.nrUsi=atoi(strtok(NULL,sep));
	masinaCitita.pret=atof(strtok(NULL,sep));

	aux=strtok(NULL,sep);
	masinaCitita.model=(char*)malloc(strlen(aux)+1);
	strcpy(masinaCitita.model,aux);

	aux=strtok(NULL,sep);
	masinaCitita.numeSofer=(char*)malloc(strlen(aux)+1);
	strcpy(masinaCitita.numeSofer,aux);

	masinaCitita.serie= *strtok(NULL,sep);

	return masinaCitita;

}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//----FUNCTII LSI-----

void afisareListaMasini(NodLSI* headLista) {
	while (headLista!=NULL) {
		afisareMasina(headLista->info);
		headLista=headLista->next;
	}
}

void adaugaMasinaFinal(NodLSI** headLista, Masina masinaNoua) {

	NodLSI* nodNou=(NodLSI*)malloc(sizeof(NodLSI));
	nodNou->info=masinaNoua;
	nodNou->next=NULL;
	NodLSI* pNodAuxiliar= *headLista;
	if (*headLista==NULL)
	{
		*headLista=nodNou;
	}
	else
	{
		while (pNodAuxiliar->next!=NULL)
			{
			pNodAuxiliar=pNodAuxiliar->next;
			}
		pNodAuxiliar->next=nodNou;
	}
}

void adaugareMasinaInceput(NodLSI** headLista,Masina masinaNoua) {
	NodLSI* nodNou = (NodLSI*)malloc(sizeof(NodLSI));
	nodNou->info=masinaNoua;
	nodNou->next=*headLista;
	*headLista=nodNou;
}

NodLSI* citireListaMasiniDinFisier(const char* numeFisier) {
	FILE* file=fopen(numeFisier,"r");
	NodLSI* headLista=NULL;
	if (file) {
		while (!feof(file)) {
			adaugaMasinaFinal(&headLista,citireMasinaFisier(file));
		}
	}

	fclose(file);
	return headLista;
}

void dezalocareLSI(NodLSI** headLista) {

	while (*headLista!=NULL) {
		NodLSI* pAuxiliar= *headLista;
		(*headLista)=(*headLista)->next;

		free(pAuxiliar->info.numeSofer);
		free(pAuxiliar->info.model);
		free(pAuxiliar);
	}
}

int caulculeazaPretMediu(NodLSI* headLista) {
	int sumaPret=0;
	int nrMasini=0;
	while (headLista->next!=NULL) {
		sumaPret+=headLista->info.pret;
		nrMasini++;
		headLista=headLista->next;
	}

	return sumaPret/nrMasini;
}
void StergeMasiniSerie(NodLSI** headLista,char serieCautata) {

	//stergere  la inceput
	while (*headLista!=NULL && (*headLista)->info.serie==serieCautata)
	{	NodLSI* pAuxiliar= *headLista;
		*headLista=(*headLista)->next;
		free(pAuxiliar->info.numeSofer);
		free(pAuxiliar->info.model);
		free(pAuxiliar);
	}
	NodLSI* pAuxiliar2= *headLista;
	while (pAuxiliar2->next!=NULL)
	{	NodLSI* pAux= pAuxiliar2->next;
		if (pAux->info.serie==serieCautata)
		{
			free(pAux->info.numeSofer);
			free(pAux->info.model);
			pAuxiliar2->next=pAux->next;
			free(pAux);
		}
		else
		{
			pAuxiliar2=pAuxiliar2->next;
		}
	}
}

int main() {
	NodLSI* headLista = citireListaMasiniDinFisier("masini.txt");

	// Masina m1 = (Masina){1, 4, 12000.0f, "Logan", "Ion", 'A'};
	// Masina m2 = (Masina){2, 2, 22000.0f, "Clio", "Ana", 'B'};
	// Masina m3 = (Masina){3, 4, 34000.0f, "Octavia", "Mihai", 'C'};
	Masina m0 = (Masina){0, 4, 18000.0f, "Polo", "Maria", 'D'};
	// 1) Prima inserare la inceput (head devine primul nod real)
	// adaugareMasinaInceput(&headLista, m1);
	// 2) Inserari la final
	// adaugaMasinaFinal(&headLista, m2);
	// adaugaMasinaFinal(&headLista, m3);
	// 3) Inserare  la inceput
	adaugareMasinaInceput(&headLista, m0);

	printf("Lista rezultata (de la head la final):\n\n");
	afisareListaMasini(headLista);
	printf("\nPret Mediu: %d\n",caulculeazaPretMediu(headLista));

	printf("Lista rezultata stergere:\n\n");
	StergeMasiniSerie(&headLista,'A');
	afisareListaMasini(headLista);


	return 0;
}