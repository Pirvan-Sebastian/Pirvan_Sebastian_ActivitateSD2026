//#include<stdio.h>
//#include<stdlib.h>
//
//struct Joc {
//	int id;
//	int nrJucatoriMin;
//	char* denumire;
//	float pret;
//	char rating;
//};
//
//struct Joc initializare(int _id,int _nrJucatoriMin, char* _denumire, float _pret,char _rating) {
//	struct Joc s;
//    //initializare structura
//	s.id = _id;
//    s.nrJucatoriMin = _nrJucatoriMin;
//    //adaug spatiu pentru sir si caracteru /0 care e final de string
//    s.denumire= malloc(sizeof(char)*(strlen(_denumire)+1));
//    //mut valoarea din _denumire in s.denumire - strcpy adauga /0 automat
//    strcpy(s.denumire,_denumire);
//    s.rating=_rating;
//    s.pret=_pret;
//	return s;
//}
//
//void afisare(struct Joc s) {
//    printf("id: %d\n", s.id);
//	printf("Nume: %s\n", s.denumire);
//    printf("numar minim jucatori: %d\n", s.nrJucatoriMin);
//    printf("Rating: %c\n", s.rating);
//    printf("Pret: %5.2f\n", s.pret);
//
//}
//
//void modifica_Atribut(struct Joc *s, char* _denumire) {
//	free((*s).denumire);
//    (*s).denumire=malloc(sizeof(char)*(strlen(_denumire)+1));
//    strcpy((*s).denumire,_denumire);
//
//}
//float calcPretIndividual(struct Joc s) {
//    float pret;
//    pret= s.pret / s.nrJucatoriMin;
//    return pret;
//}
//void dezalocare(struct Joc *s) {
//	free(s->denumire);
//}
//
//int main3() {
//	struct Joc s;
//    s= initializare(1,2,"monopoly",120,'A');
//    afisare(s);
//    modifica_Atribut(&s,"basket");
//    afisare(s);
//    float pret;
//    pret= calcPretIndividual(s);
//    printf("Pretul este: %.2f", pret);
//
//    int nrJocuri = 3;
//    struct Joc *jocuri = malloc(sizeof(struct Joc) *nrJocuri);
//    jocuri[0] = s;
//    jocuri[1] = initializare(2,3,"catan",60,'A');
//    jocuri[2] = initializare(3,4,"Karak", 50, 'B');
//    afisare(*(jocuri+1));
//    dezalocare(&s);
//
//
//	return 0;
//}