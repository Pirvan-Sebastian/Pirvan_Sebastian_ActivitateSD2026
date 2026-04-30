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
//COD STIVA - LSI
typedef struct NodStack NodStack;
struct NodStack {
	Masina info;
	NodStack* next;
};
void push(NodStack** headLista,Masina masinaNoua)
{
	NodStack* nodNou=(NodStack*)malloc(sizeof(NodStack));

	nodNou->next=*headLista;
	nodNou->info=masinaNoua;
	*headLista=nodNou;
}
Masina pop(NodStack** headLista)
{
	Masina masinaPop;
	masinaPop=(*headLista)->info;
	NodStack* nodAux=*headLista;
	//deepcopy
	// masinaPop.numeSofer=malloc(sizeof(char)*(strlen((*headLista)->info.numeSofer)+1));
	// strcpy(masinaPop.numeSofer,(*headLista)->info.numeSofer);
	// masinaPop.model=malloc(sizeof(char)*(strlen((*headLista)->info.model)+1));
	// strcpy(masinaPop.model,(*headLista)->info.model);
	*headLista=(*headLista)->next;
	free(nodAux);

	return masinaPop;
}
NodStack* citireFisierStack(const char* numeFisier) {
	FILE *file=fopen(numeFisier,"r");
	NodStack* headLista;
	while (!feof(file))
	{
		push(&headLista,citireMasinaDinFisier(file));
	}

	return headLista;
}

int main() {


	return 0;
}