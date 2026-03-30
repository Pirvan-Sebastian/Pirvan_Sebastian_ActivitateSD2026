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
	m1.model =(char*) malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer =(char*) malloc(strlen(aux) + 1);
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

//STACK
//Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
//putem reprezenta o stiva prin LSI, LDI sau vector

typedef struct NodSimplu NodSimplu;
struct NodSimplu {
	Masina info;
	NodSimplu* next;
};

void pushStack(NodSimplu** stack, Masina masina) {
	NodSimplu* nodNou = (NodSimplu*)malloc(sizeof(NodSimplu));

	nodNou->info = masina;
	nodNou->next = *stack;
	*stack = nodNou;
}

Masina popStack(NodSimplu** stack) {

	Masina masina;
	masina.id = -1;
	if (*stack != NULL) {
		NodSimplu* aux = *stack;
		*stack = (*stack)->next;

		masina = aux->info;
		free(aux);
	}

	return masina;

	

}

char emptyStack(NodSimplu* stack) {
	return !stack;
}

NodSimplu* citireStackMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	NodSimplu* stack = NULL;

	FILE* f = fopen(numeFisier, "r");
	while (!feof(f)) {
		pushStack(&stack,citireMasinaDinFisier(f));
	}
	fclose(f);
	return stack;
}

void dezalocareStivaDeMasini(/*stiva*/) {
	//sunt dezalocate toate masinile si stiva de elemente
}

//int size(/*stiva*/) {
//	//returneaza numarul de elemente din stiva
//}

//QUEUE
//Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
//putem reprezenta o coada prin LSI, LDI sau vector
typedef struct Nod Nod; //alias ca sa nu mai scriu mereu struct Nod
typedef struct Queue Queue;

struct Nod
{
	Masina masina;
	struct Nod* next;
	struct Nod* prev;

};
struct Queue {
	struct Nod* start;
	struct Nod* end;
};

void enqueue(Queue* queue, Masina masina) {
	//adauga o masina in coada

	Nod* nod = (Nod*) malloc(sizeof(Nod));
	nod->masina = masina;
	nod->next = queue->start;
	nod->prev = NULL;

	if (queue->start != NULL) {
		queue->start->prev = nod;
	} 
	else {
		queue->end = nod; //daca nu am deja ceva in coada pun ca asta e finalu 
	}	
	

	queue->start = nod;



}

Masina dequeue(Queue* queue) {
	//extrage o masina din coada
	if (queue->start == NULL) { //daca e gol
		Masina masinaEroare;
		masinaEroare.id = -1;
		return masinaEroare;
	}
	Masina masina = queue->end->masina;

	if (queue->start == queue->end) { //queue->end->prev == NULL -- daca exista 2 noduri sau daca start==end atunci am un nod

		free(queue->start);
		queue->start = NULL;
		queue->end = NULL;
	}
	else
	{
		queue->end = queue->end->prev; //primeste adresa celui de dinainte, acela fiind acum end ul
		free(queue->end->next); // duce la ce era ultima valoare inainte, dar treb next ca m am mutat una "inapoi" in coada
		queue->end->next = NULL;
	}

	return masina;

}

Queue citireCoadaDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul


	Queue queue;
	queue.start = NULL;
	queue.end = NULL;

	FILE* f = fopen(numeFisier, "r");

	while (!feof(f)) {
		Masina masina = citireMasinaDinFisier(f);
		enqueue(&queue, masina);
	}

	fclose(f);
	return queue;

}

void dezalocareCoadaDeMasini(/*coada*/) {
	//sunt dezalocate toate masinile si coada de elemente
}


////metode de procesare
Masina getMasinaByID(Queue* queue,int idCautat) {
	Queue aux;
	aux.end=NULL;
	aux.start=NULL;
	Masina rezultat;

	while (queue->start != NULL) {
		Masina masinaCurenta = dequeue(queue);

		if (masinaCurenta.id == idCautat) {
			//shallow copy
			rezultat = masinaCurenta;
			//fac deepcopy +1 pt /n
			rezultat.model = (char*)malloc(sizeof(char) * (strlen(masinaCurenta.model) + 1));
			strcpy(rezultat.model, masinaCurenta.model);
			rezultat.numeSofer = (char*)malloc(sizeof(char) * (strlen(masinaCurenta.numeSofer) + 1));
			strcpy(rezultat.numeSofer, masinaCurenta.numeSofer);
		}

		enqueue(&aux, masinaCurenta);
	}
	queue->start = aux.start;
	queue->end = aux.end;

	return rezultat;
}

float calculeazaPretTotal(NodSimplu** stack) {
	NodSimplu* nou = NULL;
	float sum = 0;
	while (*stack != NULL) {
		Masina masina = popStack(&stack);
		sum += masina.pret;
		pushStack(&nou, masina);
	}
	while (nou != NULL) {
		pushStack(stack, popStack(&nou)); //inversez la loc
	}

	return sum;
}

int main() {
	Queue queue=citireCoadaDeMasiniDinFisier("masini.txt");
	//afisareMasina(dequeue(&queue));

	Masina masina = getMasinaByID(&queue, 9);
	afisareMasina(masina);
	free(masina.model);
	free(masina.numeSofer);

	
	return 0;
}