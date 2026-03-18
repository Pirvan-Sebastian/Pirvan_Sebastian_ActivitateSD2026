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
typedef struct ListaDubla ListaDubla;
typedef struct Nod Nod;
struct Nod {
	Masina info;
	struct Nod* next;
	struct Nod* prev;
};

struct ListaDubla {
	Nod* prim;
	Nod* ultim;
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

void afisareListaMasini(ListaDubla lista) {
	Nod* p = lista.prim;
	while (p) {
		afisareMasina(p->info);
		p = p->next;
	}
}

void adaugaMasinaInLista(ListaDubla* listadubla, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	nou->prev = listadubla->ultim; 
	//il leg la lista initiala si adresa prev al lui este ultimul element al listei initiale
	if (listadubla->ultim) {
		listadubla->ultim->next = nou; 
		listadubla->ultim = nou;
	}
	else //daca nu aveam alte noduri in lista e si primul si ultimul nod
	{
		listadubla->prim = nou;
		listadubla->ultim = nou;
	}


}

void adaugaLaInceputInLista (ListaDubla* listadubla, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = listadubla->prim;
	nou->prev = NULL;
	//il leg la lista initiala si adresa prev al lui este ultimul element al listei initiale
	if (listadubla->prim) {
		listadubla->prim->prev = nou;
		
	}
	else //daca nu aveam alte noduri in lista e si primul si ultimul nod
	{
	
		listadubla->ultim = nou;
	}
	listadubla->prim = nou;
}

ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* file = fopen(numeFisier, "r");

	if (file) {
		ListaDubla lista;
		lista.prim = NULL;
		lista.ultim = NULL;
		while (!feof(file)) {
			Masina m1 = citireMasinaDinFisier(file);
			adaugaMasinaInLista(&lista, m1);
		}
		fclose(file);
		return lista;
	}
}

void dezalocareLDMasini(ListaDubla* listadubla) {
	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
	while (listadubla->prim && listadubla->prim->next) {
		free(listadubla->prim->info.numeSofer);
		free(listadubla->prim->info.model);
		listadubla->prim = listadubla->prim->next;
		free(listadubla->prim->prev);
	}

	if (listadubla->prim) {
		free(listadubla->prim->info.numeSofer);
		free(listadubla->prim->info.model);
		free(listadubla->prim);
	}

	listadubla->prim = listadubla->ultim = NULL;
}

float calculeazaPretMediu(ListaDubla listadubla) {
	//calculeaza pretul mediu al masinilor din lista.
	Nod* p = listadubla.prim;
	float suma = 0;
	int nr = 0;
	while (p) {
		suma += p->info.pret;
		nr++;
		p = p->next;	
	}

	return suma/nr;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(ListaDubla listadubla) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	Nod* p = listadubla.prim;
	int maxim = 0;
	char* numeSoferMasinaScumpa = NULL;
	while (p) {
		if (p->info.pret > maxim)
		{
			maxim = p->info.pret;
			numeSoferMasinaScumpa = p->info.numeSofer;
		}
		p = p->next;
	}

	return numeSoferMasinaScumpa;
}

int main() {


	ListaDubla lista= citireLDMasiniDinFisier("masini.txt");
	afisareListaMasini(lista);
	printf("Numele soferului cu cea mai scumpa masina %s\n", getNumeSoferMasinaScumpa(lista));
	printf("Medie: %f\n", calculeazaPretMediu(lista));
	
	return 0;
}