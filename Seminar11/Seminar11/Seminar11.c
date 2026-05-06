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

//creare structura pentru un nod dintr-un arbore binar de cautare

typedef struct NodArbore NodArbore;

struct NodArbore {
	Masina info;
	NodArbore* left;
	NodArbore* right;
	//cateodata gasim si gradul de echilibru deja salvat pt fiecare Nod
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

int calculeazaInaltimeArbore(NodArbore* radacina) {
	//calculeaza inaltimea arborelui care este data de 
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza

	if (radacina != NULL) {
		return max(calculeazaInaltimeArbore(radacina->left), calculeazaInaltimeArbore(radacina->right))+1;
	}
	else {
		return 0;
	}
	
}

//ALTE FUNCTII NECESARE:
// - aici veti adauga noile functii de care aveti nevoie.

char calculGE(NodArbore* radacina) {
	if (radacina != NULL) {
		return calculeazaInaltimeArbore(radacina->left) - calculeazaInaltimeArbore(radacina->right);
	}
	else {
		return 0;
	}
}

void rotireStanga(NodArbore** radacina) {
	NodArbore* aux = (*radacina)->right; //am dezechilibru in dreapta deci stiu clar ca exista si il salvez in aux
	(*radacina)->right = aux->left;
	aux->left = (*radacina);
	(*radacina) = aux;
}

void rotireDreapta(NodArbore** radacina) {
	NodArbore* aux = (*radacina)->left;
	(*radacina)->left = aux->right;
	aux->right = (*radacina);
	(*radacina) = aux;

	//efectiv la ca stanga, dar unde scrie right pun left si unde e left pun right👍 
}



void adaugaMasinaInArboreEchilibrat(NodArbore** radacina,Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte principiile de arbore binar de cautare ECHILIBRAT
	//dupa o anumita cheie pe care o decideti - poate fi ID


	if ((*radacina)!=NULL) {
		if ((*radacina)->info.id == masinaNoua.id) {
			adaugaMasinaInArboreEchilibrat(&(*radacina)->left, masinaNoua);
		}
		else {
			adaugaMasinaInArboreEchilibrat(&(*radacina)->right, masinaNoua);
		}

		int grad = calculGE((*radacina));
		if (grad == 2) { //dezechilibru stanga
			if (calculGE((*radacina)->left) == -1) { //-rotire dubla
				rotireStanga(&(*radacina)->left);
				rotireDreapta(&(*radacina));
			}
			else {
				rotireDreapta(&(*radacina));
			}
		}
		else if (grad == -2) { //dezechilibru dreapta
			if (calculGE((*radacina)->right) == 1) { //- rotire dubla 
				rotireDreapta(&(*radacina)->right);
			}
			rotireStanga(&(*radacina)); // am pus in afar IF ca se executa oricum
			//e aceeasi functie dar in loc de Dreapta e stanga, left e right si invers!👍
		}
	}
	else {
		NodArbore* nou = (NodArbore*)malloc(sizeof(NodArbore)); //a dat crash am pierdut cod
		//initializare NodNou cu null pe stg dreapta si info daca e primu nod ever din arbore 
		nou->info = masinaNoua;
		nou->left = NULL;
		nou->right = NULL;
		(*radacina) = nou;
	}

}

void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* file = fopen(numeFisier, "r");
	NodArbore* radacina = NULL;

	while (!feof(file)) {
		Masina masina = citireMasinaDinFisier(file);
		adaugaMasinaInArboreEchilibrat(&radacina, masina);
	}
	fclose(file);
	return radacina;
}

void afisareMasiniDinArbore(NodArbore*radacina) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere


	if (radacina != NULL) {
		afisareMasina(radacina->info);
		afisareMasiniDinArbore(radacina->left);
		afisareMasiniDinArbore(radacina->right);
	}
}

void dezalocareArboreDeMasini(/*arbore de masini*/) {
	//sunt dezalocate toate masinile si arborele de elemente

	//de completat ca la ABC


}

//Preluati urmatoarele functii din laboratorul precedent.
//Acestea ar trebuie sa functioneze pe noul arbore echilibrat.
//
//Masina getMasinaByID(/*arborele de masini*/int id);
//
//int determinaNumarNoduri(/*arborele de masini*/);
//
//float calculeazaPretTotal(/*arbore de masini*/);
//
float calculeazaPretulMasinilorUnuiSofer(NodArbore* radacina, const char* numeSofer) {
	float sum = 0;
	if (radacina != NULL) {
		sum+=calculeazaPretulMasinilorUnuiSofer(radacina->left, numeSofer);
		sum += calculeazaPretulMasinilorUnuiSofer(radacina->right, numeSofer);

		if (strcmp(radacina->info.numeSofer, numeSofer)==0);
		sum += radacina->info.pret;
	}

	return sum;
}

int main() {
	NodArbore* radacina = citireArboreDeMasiniDinFisier("masini_AVL.txt");
	afisareMasiniDinArbore(radacina);

	return 0;
}