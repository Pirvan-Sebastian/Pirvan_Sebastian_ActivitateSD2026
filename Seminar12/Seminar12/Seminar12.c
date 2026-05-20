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

//1. 
// structuri necesare
//dorim stocarea unui graf intr-o lista de liste
//astfel avem nod ListaPrincipala si NodListaSecundara
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct NodPrincipal {
	Masina info;
	NodPrincipal* nodNext; //next
	NodSecundar* nodVecini; //vecinii -> in jos
};
struct NodSecundar {
	NodPrincipal* nodInfo; //pointer la nodul cu valoarea vecinului
	NodSecundar* nodNextVecin; //merg in jos pe lsita cu vecinii
};

//2.
//functii de inserare in liste
//si in principala si in secundara
void inserareInListaPrincipala(NodPrincipal** graf, Masina masinaNoua) {
	//cand fac o structura initializez tot
	NodPrincipal* nodNou = malloc(sizeof(NodPrincipal));
	nodNou->nodNext = NULL;
	nodNou->nodVecini = NULL;
	nodNou->info = masinaNoua;
	//daca nu exista
	if ((*graf) == NULL)
	{
		(*graf) = nodNou;
	}
	else
	{
		//parcurg cu un auxiliar pana la finalul listei ca sa inserez acolea
		NodPrincipal* aux = (*graf);
		while (aux->nodNext != NULL) {
			aux = aux->nodNext;
		}
		aux->nodNext = nodNou;
	}

}

void inserareInListaSecundara(NodSecundar** head,NodPrincipal* vecin)// vecin->capul listei principale)
{
	NodSecundar* nodNou = malloc(sizeof(NodSecundar));
	nodNou->nodNextVecin = NULL;
	nodNou->nodInfo = vecin; //info primeste valoarea adresei la care se afla vecinul lui
	if ((*head) == NULL)
	{
		(*head) = nodNou;
	}
	else
	{
		NodSecundar* aux = (*head);
		while (aux->nodNextVecin != NULL) 
		{
			aux = aux->nodNextVecin;
		}
		aux->nodNextVecin = nodNou;
	}
}

//3.
//functie de cautarea in lista principala dupa ID
NodPrincipal* cautaNodDupaID(NodPrincipal* listaPrincipala, int id) 
{
	
		while (listaPrincipala!=NULL && listaPrincipala->info.id != id) 
		{
			listaPrincipala = listaPrincipala->nodNext;
		}
		return listaPrincipala; //adresa nodului cu id ul cautat
}

//4.
//inserare muchie
void inserareMuchie(NodPrincipal* listaPrincipala, int idStart, int idStop)  //idStart si isStop sunt nodurile intre care fac legatura
{
	NodPrincipal* nodStart=cautaNodDupaID(listaPrincipala, idStart);
	NodPrincipal* nodStop=cautaNodDupaID(listaPrincipala,idStop);

	if (nodStart != NULL && nodStop != NULL) {
		inserareInListaSecundara(&nodStart->nodVecini, nodStop);
		inserareInListaSecundara(&nodStop->nodVecini, nodStart); //2 inserari ca am neorientat pot merge in ambele directii
	}


}

//listaPrincipala == head de mai sus cred? -> de verificat
void* citireNoduriMasiniDinFisier(const char* numeFisier)
{
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* file = fopen(numeFisier, "r");

	NodPrincipal* listaPrincipala = NULL;

	while (!feof(file)) 
	{
		inserareInListaPrincipala(&listaPrincipala, citireMasinaDinFisier(file));
	}

	fclose(file);
	return listaPrincipala;
}

void citireMuchiiDinFisier(NodPrincipal* listaPrincipala,const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste 
	//toate id-urile de start si stop pentru fiecare muchie
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* file = fopen(numeFisier,"r");
	int start, stop;

	while (!feof(file)) 
	{
		fscanf(file,"%d %d", &start, &stop);
		inserareMuchie(listaPrincipala, start, stop);
	}
}

void afisareListaSecundara(NodPrincipal* listaPrincipala, int id) {
	NodSecundar* auxiliar = listaPrincipala->nodVecini;

	while (auxiliar != NULL) 
	{
		afisareMasina(auxiliar->nodInfo->info);
	}
}

void dezalocareNoduriGraf(void* listaPrincipala) {
	//sunt dezalocate toate masinile din graf 
	//si toate nodurile celor doua liste
}

int main() {
	NodPrincipal* listaPrincipala = citireNoduriMasiniDinFisier("masini.txt");
	citireMuchiiDinFisier(listaPrincipala, "muchii.txt");
	afisareListaSecundara(listaPrincipala, 8);

	return 0;
}