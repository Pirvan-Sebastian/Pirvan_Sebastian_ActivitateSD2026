
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Avion Avion;
typedef struct Nod Nod;
struct Avion {
	int nrLocuri;
	char* model;
	int nrLocuriOcupate;
	//float* preturi;
};

struct Nod {
	Avion info;
	Nod* Nodstanga;
	Nod* NodDreapta;

};
Avion citireAvionDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	fgets(buffer, 100, file);
	Avion avion;

	aux = strtok(buffer, sep);
	avion.nrLocuri = atoi(aux);

	aux = strtok(NULL, sep);
	avion.model = (char*)malloc(strlen(aux) + 1);
	strcpy(avion.model, aux);

	aux = strtok(NULL, sep);
	avion.nrLocuriOcupate = atoi(aux);

	return avion;
}
void afisareAvion(Avion avion) {
	printf("\nNrlocuri: %d\n", avion.nrLocuri);
	printf("\nNrlocuriOcupate: %d\n", avion.nrLocuriOcupate);
	("\nModel: %s\n\n", avion.model);
}

Nod* inserareaAvionInArbore(Nod* arbore, Avion avionNou) {
	if (arbore != NULL) 
	{
		if (arbore->info.nrLocuri > avionNou.nrLocuri) //daca ce am primit din avionNou< ce era in radacina  -> pun in stanga (mai mici)
		{
			arbore->Nodstanga=inserareaAvionInArbore(arbore->Nodstanga, avionNou);
		}
		else //ce am primit > ce era in radacina -> dreapta
		{
			arbore->NodDreapta = inserareaAvionInArbore(arbore->NodDreapta, avionNou);
		}
		return arbore;//intorc radacina subtree ului verificat acum(posibil modificat)
	}
	else
	{
		//initializare Nod Avion
		Nod* nodNou = (Nod*)malloc(sizeof(Nod));
		nodNou->NodDreapta = NULL;
		nodNou->Nodstanga = NULL;

		nodNou->info = avionNou;//shallow copy

		//puteam face si shallow copy era okay ca se foloseste memoria de la malloc cu Nod in ocntinuare in nodul arborelui
		//nodNou->info.model = (char*)malloc(strlen(avionNou.model)+1);
		//strcpy(nodNou->info.model, avionNou.model);//deep copy
		

		return nodNou;

	}
}

Nod* citireArboreDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* arbore=NULL;
	while (!feof(file)) 
	{
		arbore = inserareaAvionInArbore(arbore, citireAvionDinFisier(file));
	}
	fclose(file);

	return arbore;
}

void afisareArbore(Nod* arbore) 
{
	if (arbore != NULL) 
	{
		afisareArbore(arbore->Nodstanga);
		afisareArbore(arbore->NodDreapta);
		afisareAvion(arbore->info);
		//Postordine!!
	}
}

Avion cautareAvionInArbore(int nrLocuri, Nod* arbore) {
	if (arbore != NULL)
	{
		//cand am functie ce are return fac return la autoapel cand nu fac doar autoapel(logic!)
		if (nrLocuri < arbore->info.nrLocuri)
			return cautareAvionInArbore(nrLocuri, arbore->Nodstanga);
		else if (nrLocuri > arbore->info.nrLocuri)
			return cautareAvionInArbore(nrLocuri, arbore->NodDreapta);
		else
			return arbore->info;
	}
	else
	{
		Avion avionEroare = { -1, NULL, -1 };
		return avionEroare;
	}

}

void dezalocareArbore(Nod* arbore) //dezalocare cu post order!-- exact ca afisarea dar free in loc de afisare si free si pt string si obiect!
{
	if (arbore != NULL) 
	{
		dezalocareArbore(arbore->Nodstanga);
		dezalocareArbore(arbore->NodDreapta);
		free(arbore->info.model);
		free(arbore);
	}
}

int main()
{

}
