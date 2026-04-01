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
typedef struct Nod Nod; //alias struct Nod= Nod

//creare structura pentru un nod dintr-o lista simplu inlantuita

struct Nod { //Nod== lista
	Masina masina;
	Nod* next;
};



//creare structura pentru tabela de dispersie
// aceasta este un vector de liste
struct HashTable {
	int dim;
	Nod** vectorListe;
};
typedef struct HashTable HashTable;

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

void afisareListaMasini(Nod* nod) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()

	while (nod) {
		afisareMasina(nod->masina); //sau (*nod).masina e acelasi lucru -> dereferentiere si accesare
		nod = nod->next;
	}

}

void adaugaMasinaInLista(Nod** nod, Masina masinaNoua) { // ** ca modific si e decalrat ca **
	//adauga la final in lista primita o noua masina pe care o primim ca parametru

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->masina = masinaNoua;
	nou->next = NULL;

	if (!*nod)
	{
		*nod = nou;
	}
	else 
	{
		Nod* aux = *nod;
		while (aux->next)
		{
			aux = aux->next;
		}

		aux->next = nou;

	}
}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	//initializeaza vectorul de liste si seteaza fiecare lista ca fiind NULL;
	ht.dim = dimensiune;
	ht.vectorListe = malloc(sizeof(Nod*) * ht.dim);

	for (int i=0; i < ht.dim; i++)
	{
		ht.vectorListe[i] = NULL;
	}

	return ht;
}

int calculeazaHash(int id ,int dimensiune) {
	// este calculat hash-ul in functie de dimensiunea tabelei si un atribut al masinii

	return (id * 31) % dimensiune;

}

void inserareMasinaInTabela(HashTable ht, Masina masina) {
	//este folosit mecanismul CHAINING
	//este determinata pozitia si se realizeaza inserarea pe pozitia respectiva

	int hash = calculeazaHash(masina.id, ht.dim);

	if (ht.vectorListe[hash] != NULL);
	{
		adaugaMasinaInLista(&(ht.vectorListe[hash]), masina);

		return;
	}
	//fac nod nou si il pun in lista de la pozitie
	Nod* nod = malloc(sizeof(Nod));
	nod->masina = masina;
	nod->next = NULL;
	ht.vectorListe[hash] = nod;
	//tot ce e de la if in joc putea fi adaugaMasinaInLista
}

HashTable citireMasiniDinFisier(const char* numeFisier, int dimensiune) { //dimensiune = cate masini pun
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	// aceste masini sunt inserate intr-o tabela de dispersie initializata aici
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* f = fopen(numeFisier, "r");

	HashTable ht= initializareHashTable(dimensiune);

	while (!feof(f))
	{
		Masina masina = citireMasinaDinFisier(f);
		inserareMasinaInTabela(ht, masina);
	}
	fclose(f);

	return ht;

}

void afisareTabelaDeMasini(HashTable ht) {
	//sunt afisate toate masinile cu evidentierea clusterelor realizate

	for (int i = 0; i < ht.dim; i++)
	{
		if (ht.vectorListe[i] != NULL)
		{
			printf("Cluster %d\n", i + 1); 
			afisareListaMasini(ht.vectorListe[i]);

			printf("=================\n");
		}
	}
}

void dezalocareTabelaDeMasini(HashTable *ht) {
	//sunt dezalocate toate masinile din tabela de dispersie\
	//sterg masini+lista
	for (int i = 0; i < ht->dim; i++)
	{
		if (ht->vectorListe[i] != NULL)
		{
			Nod* aux = ht->vectorListe[i];
			Nod* next = NULL;

			while (aux != NULL)
			{
				free(aux->masina.model);
				free(aux->masina.numeSofer);

				next = aux->next;
				free(aux);
				aux = next;
			}
		}
	}
	//sterg vector adica ht ul
	free(ht->vectorListe);
	ht->dim = 0;
	ht->vectorListe = NULL;



}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	//calculeaza pretul mediu al masinilor din fiecare cluster.
	//trebuie sa returnam un vector cu valorile medii per cluster.
	//lungimea vectorului este data de numarul de clustere care contin masini
	int nr = 0; 

		for (int i = 0; i < ht.dim; i++) {
			if (ht.vectorListe[i] != NULL)
				nr++;
		}

		float* mediiCluster = malloc(nr * sizeof(float));
		int j = 0;

		for (int i = 0; i < ht.dim; i++) {
			if (ht.vectorListe[i] != NULL) {
				int nrNoduri = 0;
				float sum = 0;

				Nod* aux = ht.vectorListe[i];

				while (aux != NULL)
				{
					nrNoduri++;
					sum += aux->masina.pret;

					aux = aux->next; // NU uita de NEXT!
				}

				mediiCluster[j++] = sum / nrNoduri;
			}
		}

	*nrClustere = nr;
	return mediiCluster;
}

Masina getMasinaDupaCheie(HashTable ht, int id) {
	Masina m;
	//cauta masina dupa valoarea atributului cheie folosit in calcularea hash-ului
	//trebuie sa modificam numele functiei 
	int hash = calculeazaHash(id, ht.dim);
	//ar treb sa verific daca hash se afla intre 0 si ht.dim
	Nod* aux = ht.vectorListe[hash];
	while (aux != NULL)
	{
		if (aux->masina.id == id)
		{
			m= aux->masina;
			m.model = malloc((strlen(aux->masina.model) + 1) * sizeof(char));
			strcpy(m.model, aux->masina.model);

			m.numeSofer = malloc((strlen(aux->masina.numeSofer) + 1) * sizeof(char));
			strcpy(m.numeSofer, aux->masina.numeSofer);

		}

		aux = aux->next;
	}

	return m;
}

int main() {

	HashTable ht = citireMasiniDinFisier("masini.txt",5); //dim=5 pt test
	//afisareTabelaDeMasini(ht);

	//afisareMasina(getMasinaDupaCheie(ht, 9));
	int nrClustere;
	float* medii = calculeazaPreturiMediiPerClustere(ht, &nrClustere);

	for (int i = 0; i < nrClustere; i++)
	{
		printf("CLUSTER %d: %.2f\n", i+1,medii[i]);
	}


	dezalocareTabelaDeMasini(&ht);

	return 0;
}