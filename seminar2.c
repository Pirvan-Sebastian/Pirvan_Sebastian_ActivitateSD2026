#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Film
{
	int id;
	int durata;
	char *denumire;
	float buget;
	int varstaMinima;
};
struct Film initializare(/*parametri necesari*/ int _id, int _durata, char *_denumire, float _buget, int _varstaMinima)
{
	struct Film s;
	s.id = _id;
	s.durata = _durata;
	s.denumire = malloc((strlen(_denumire) + 1) * sizeof(char));
	strcpy(s.denumire, _denumire);
	s.buget = _buget;
	s.varstaMinima = _varstaMinima;
	// initializare structura
	return s;
}
struct Film copyFilm(struct Film s)
{
	return initializare(s.id, s.durata, s.denumire, s.buget, s.varstaMinima);
}

void afisare(struct Film s)
{
	// afisarea tuturor atributelor.

	printf("Nume: %s \n", s.denumire);
	printf("Durata in minute: %d\n", s.durata);
	printf("Buget: %.2f\n", s.buget);
	printf("Varsta minima: %d \n", s.varstaMinima);
}

void afisareVector(struct Film *vector, int nrElemente)
{
	// afisarea elementelor din vector apeland functia afisare

	for (int i = 0; i < nrElemente; i++)
	{
		afisare(vector[i]);
		printf("\n");
	}
}

struct Film *copiazaPrimeleNElemente(struct Film *vector, int nrElemente, int nrElementeCopiate)
{
	// copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Film *vectorNou = malloc(nrElementeCopiate * sizeof(struct Film));
	for (int i = 0; i < nrElementeCopiate; i++)
	{
		vectorNou[i] = copyFilm(vector[i]);
	}

	return vectorNou;
}

void dezalocare(struct Film **vector, int *nrElemente)
{
	// dezalocam elementele din vector si vectorul

	for (int i = 0; i < *nrElemente; i++)
	{
		free((*vector)[i].denumire);
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaAnumiteElemente(struct Film *vector, char nrElemente, float bugetMaxim, struct Film **vectorNou, int *dimensiune)
{
	// parametrul prag poate fi modificat in functie de
	//  tipul atributului ales pentru a indeplini o conditie
	// este creat un nou vector cu elementele care indeplinesc acea

	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].buget < bugetMaxim)
		{
			dimensiune++;
		}

		vectorNou = malloc((*dimensiune) * sizeof(struct Film));
		int k = 0;
		for (int i; i < nrElemente; i++)
		{
			if (vector[i].buget < bugetMaxim)
			{
				(*vectorNou)[k] =copyFilm(vector[i]);
				k++;
			}
		}
	}
}

struct Film getPrimulElementConditionat(struct Film *vector, int nrElemente, const char *numeCautat)
{
	// trebuie cautat elementul care indeplineste o conditie
	// dupa atributul de tip char*. Acesta este returnat.
	struct Film s;
	s.id = -11;

	for (int i=0;i<nrElemente;i++) {
		if(!strcmp(vector[i].denumire,numeCautat));
			return vector[i];
	}

	
}

int main()
{

	struct Film film1 = initializare(1, 120, "Dune", 20.6, 14);

	afisare(film1);

	int nrFilme = 3;

	struct Film *filme = malloc(nrFilme * sizeof(struct Film));

	filme[0] = film1;
	filme[1] = initializare(2, 95, "Inception", 15.2f, 12);
	filme[2] = initializare(3, 110, "Interstellar", 25.0f, 14);
	printf("\n Elemente: \n");
	afisareVector(filme, nrFilme);

	int nrFilmeCopiate = 2;
	struct Film *vectorNou;
	vectorNou = copiazaPrimeleNElemente(filme, nrFilme, nrFilmeCopiate);
	printf("\n Elemente copiate 1 : \n");
	afisareVector(vectorNou, nrFilmeCopiate);
	dezalocare(&vectorNou, &nrFilmeCopiate);

	printf("\n Elemente copiate 2 : \n");
	// afisareVector(vectorNou, nrFilmeCopiate);

	struct Film *vectorIeftin;

	float prag = 40;
	int dimIeftin;

	copiazaAnumiteElemente(filme, 50, prag, &vectorIeftin, &dimIeftin);
	// afisareVector(vectorIeftin, dimIeftin);

	afisare(getPrimulElementConditionat(filme,nrFilme,"Dune"));

	return 0;
}