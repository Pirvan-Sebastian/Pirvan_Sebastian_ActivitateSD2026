#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Telefon {
	int id;
	int RAM;
	char* producator;
}; //declarare structura Telefon

typedef struct Telefon Telefon; //alias

Telefon initializare(int id,int RAM, char* producator)
{
	Telefon telefon;
	telefon.id=id;
	telefon.RAM=RAM;
	//aloc spatiu pentru denumire producatorului
	telefon.producator=(char*)malloc(sizeof(char)*(strlen(producator)+1)); //+1 pentru \0
	strcpy(telefon.producator,producator);

	 return telefon;
}

void afisare(Telefon telefon)
{
	 printf("\n %d. Telefonul %s are %d GB Ram \n",telefon.id,telefon.producator,telefon.RAM);
}
//ca un setter de la POO, unde Telefon telefon e this
void modificaAtributRam(Telefon* telefon, int nouRam)
{
	if (nouRam > 0) {
		telefon->RAM=nouRam;
	}
}

void dezalocare(Telefon* telefon)
{
	if (telefon->producator!=NULL)
	{
		free(telefon->producator);
		telefon->producator=NULL;
	}

}
int main() {
	struct Telefon telefon;
	telefon = initializare(1,256,"Samsung");
	afisare(telefon);
	modificaAtributRam(&telefon,12);
	afisare(telefon);

	dezalocare(&telefon);
	return 0;
}