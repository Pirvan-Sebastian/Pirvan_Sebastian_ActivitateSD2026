// HeapMaxMinTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>


struct StructuraMasina { //de repetat
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
}; 
typedef struct StructuraMasina Masina;
typedef struct Heap Heap;

struct Heap {
	int lungime;//cate spatii goale sunt in vector (sau elemente ascunse)
	int nrMasini;//cate masini am eu in vector
	Masina* vectorMasini;//pe asta il vom face dupa regula Heap si vectorMasini[0] este max/minim
};

Masina citireMasinaDinFisier(FILE* file) { // de repetat si asta sa nu uit
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);

	//int
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));

	//float
	m1.pret = atof(strtok(NULL, sep));

	//string
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy(m1.model, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy(m1.numeSofer, aux);

	//1 caracter
	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) { //de repetat
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

Heap initializareHeap(int lungimeInitializare) {
	//la initializare declar un nou Heap
	// atribui ceva ficarui camp din struct heap
	//aloc spatiu pentru vectorMasini ca sa am unde pune datele mai tarziu
	//si sa pointeze undeva heap;
	Heap heapNou;
	heapNou.lungime = lungimeInitializare;
	heapNou.nrMasini = 0;
	heapNou.vectorMasini = (Masina*)malloc(sizeof(Masina) * lungimeInitializare); //aloc memorie pt nr=lungimeInitialziare elemente
	//vectorMasini e pointer de tip Masina* deci trebuie sa fac cast explicit la malloc ca sa ii returneze un pointer de tip Masina*

	return heapNou;
}
void filtreazaHeap(Heap heap, int pozitieNod) {//aplicat pe fiecare Nod ca sa verific daca Radacina >= stanga dreapta!
	int pozStanga = 2 * pozitieNod + 1; //formula fiu stanga Heap
	int pozDreapta = 2 * pozitieNod + 2; // formula fiu dreapta Heap
 
	int pozMax = pozitieNod; // imi asum ca pe radacina se afla nodul cu val maxima
	//pozStanga< heap.nrMasini verifica daca valoarea verificata face parte din vectorul meu ( am nrMasini masini deci pana la nodul cu index nrMasini sunt valorile)
	//
	if (pozStanga < heap.nrMasini && heap.vectorMasini[pozMax].id < heap.vectorMasini[pozStanga].id)
	{
		pozMax = pozStanga;
	}
	if (pozDreapta < heap.nrMasini && heap.vectorMasini[pozMax].id < heap.vectorMasini[pozDreapta].id)
	{
		pozMax = pozDreapta;
	}
	//interschimb  valoarea din pozMax(oricare ar fi el) cu pozitieNod-> aduc maximul in radacina daca nu e deja
	if (pozMax != pozitieNod) //daca radacina nu avea deja MAX
	{
		Masina auxiliar = heap.vectorMasini[pozMax];
		heap.vectorMasini[pozMax] = heap.vectorMasini[pozitieNod];
		heap.vectorMasini[pozitieNod] = auxiliar; 

		if (2 * pozMax + 1 < heap.nrMasini)
		{
			filtreazaHeap(heap, pozMax);
		}
	}
}

Heap citireHeapMasiniDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	int numarMasini = 10; //hard codat ca am 10 masini in fisier, il pot pasa ca argument cu (numeFisier, int numarMasini)
	Heap heap = initializareHeap(10);
	while (!feof(file)) 
	{
		heap.vectorMasini[heap.nrMasini++] = citireMasinaDinFisier(file);
		//sau pun [heap.nrMasini] si sub heap.nrMasini++ da e acelasi lucru
	}
	fclose(file);

	for (int i = (heap.nrMasini - 2) / 2; i >= 0; i--)       
	{
		filtreazaHeap(heap, i);
	}

	return heap;

}

void afisareHeap(Heap heap)
{
	for (int i = 0; i < heap.nrMasini; i++)
		afisareMasina(heap.vectorMasini[i]);
}

Masina extragereHeap(Heap* pHeap) //(&heap)
{
	if (pHeap->nrMasini > 0)
	{
		//interschimbare
		Masina aux = pHeap->vectorMasini[0];
		pHeap->vectorMasini[0] = pHeap->vectorMasini[pHeap->nrMasini - 1];
		pHeap->vectorMasini[pHeap->nrMasini - 1] = aux;

		pHeap->nrMasini--;
		for (int i = (pHeap->nrMasini - 2) / 2; i >= 0; i--) //parcurg iar de jos in sus
		{
			filtreazaHeap(*pHeap, i); //dereferentiere -> pHeap== adresa unde e heap si *pHeap este heap ul (obiect cum cere fct)
		}
		return aux;//shallow copy

		/**
		Masina masina = aux;

		masina.model = (char*)malloc((strlen(aux.model)+1));
		strcpy(masina.model, aux.model);

		masina.numeSofer = (char*)malloc((strlen(aux.numeSofer) + 1));
		strpcy(masina.numeSofer, aux.numeSofer);
		--deep copy
		**/
	}
}

void dezalocareHeap(Heap* heap)
{
	//sterg stringuri pt fiecare obierct masina din vector
	for (int i = 0; i < heap->lungime; i++)
	{
		free(heap->vectorMasini[i].model);
		free(heap->vectorMasini[i].numeSofer);
		
	}

	free(heap->vectorMasini);
	//valori default
	heap->vectorMasini = NULL;
	heap->lungime = 0;
	heap->nrMasini = 0;
}

int main() {
	Heap heap = citireHeapMasiniDinFisier("masini_arbore.txt");
	afisareHeap(heap); 
	printf("\nMasina extrasa\n");
	afisareMasina(extragereHeap(&heap));
	printf("\nDupa extragere\n\n");
	afisareHeap(heap);

	return 0;
}

