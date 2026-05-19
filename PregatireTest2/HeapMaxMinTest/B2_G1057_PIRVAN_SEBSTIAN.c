#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Pilot Pilot;
typedef struct Heap Heap;

struct Pilot {
	int id;
	float greutate;
	char* echipa;
};

struct Heap {
	int lungime;
	int nrPiloti;
	Pilot* vector;
};

void afisarePilot(Pilot pilot) {
	printf("\nID:%d\n", pilot.id);
	printf("\nGreutare %.2f:\n", pilot.greutate);
	printf("\nEchipa: %s\n\n", pilot.echipa);
}
Pilot citirePilotDinFisier(FILE* file){

}

Heap initializareHeap(int lungimeInitializare) {

	Heap heapNou;
	heapNou.lungime = lungimeInitializare;
	heapNou.nrPiloti = 0;
	heapNou.vector = (Pilot*)malloc(sizeof(Pilot) * lungimeInitializare);

	return heapNou;

}

void filtrareHeap(Heap heap, int pozNod)
{
	int pozStg = 2 * pozNod + 1;
	int pozDr = 2 * pozNod + 2;

	int pozMax = pozNod;

	if (pozStg < heap.nrPiloti && heap.vector[pozMax].id < heap.vector[pozStg].id)
		pozMax = pozStg;
	if (pozDr < heap.nrPiloti && heap.vector[pozMax].id < heap.vector[pozDr].id)
		pozMax = pozDr;

	if (pozMax != pozNod)
	{
		Pilot auxiliar = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozNod];
		heap.vector[pozNod] = auxiliar;

		if (2 * pozMax + 1 < heap.nrPiloti)
		{
			filtrareHeap(heap, pozMax);
		}
	}
}

Heap citireHeapDinFisier(const char* numeFisier,int numarNoduri)
{
	FILE* file = fopen(numeFisier, "r");
	Heap heapNou=initializareHeap(numarNoduri);

	while (!feof(file))
	{
		heapNou.vector[heapNou.nrPiloti++] = citirePilotDinFisier(file);
	}
	fclose(file); //!!! NU UITA -am uitat

	for (int i = (heapNou.nrPiloti-2)/2; i >= 0; i--)
	{
		filtrareHeap(heapNou, i);
	}

	return heapNou;
}

Pilot extrageDinHeap(Heap* heap) {

	Pilot auxiliar = heap->vector[0];
	heap->vector[0] = heap->vector[heap->nrPiloti - 1];
	heap->vector[heap->nrPiloti - 1] = auxiliar;

	heap->nrPiloti--;

	for (int i = (heap->nrPiloti - 2) / 2; i >= 0; i--) {
		filtrareHeap(*heap, i);
	}

	return auxiliar;//shallow copy
}
void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.nrPiloti; i++) 
		afisarePilot(heap.vector[i]);
}

void dezalocareHeap(Heap heap) {
	for (int i = 0; i < heap.lungime; i++)
	{
		free(heap.vector[i].echipa);
		//la fel la toate stringurile
	}

	free(heap.vector);
	heap.vector = NULL;
	heap.lungime = 0;
	heap.nrPiloti = 0;

}


int main() {

	return 0;
}
