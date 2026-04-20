#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128

struct Student {
    int id;
    char* nume;
    float medie;
};

//  CITIRE CSV
void citireCSV(char* numeFisier) {
    FILE* f = fopen(numeFisier, "r");
    if (!f) {
        printf("Eroare: Fisierul nu a putut fi deschis!\n");
        return;
    }
    
    char buffer[LINESIZE], seps[] = ",\n";
    char* token;
    int linie = 0;
    
    while (fgets(buffer, sizeof(buffer), f)) {  // Citire linie cu linie
        linie++;
        
        // Parsare CSV: "1,Ion Popescu,9.5"
        token = strtok(buffer, seps);     // Obți "1"
        int id = atoi(token);
        
        token = strtok(NULL, seps);       // Obți "Ion Popescu"
        char* nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
        strcpy(nume, token);
        
        token = strtok(NULL, seps);       // Obți "9.5"
        float medie = (float)atof(token);
        
        printf("Linie %d: ID=%d, Nume=%s, Medie=%.2f\n", linie, id, nume, medie);
        
        free(nume);
    }
    
    fclose(f);
}

// SCRIERE CSV
void scriereCSV(char* numeFisier, struct Student* studenti, int n) {
    FILE* f = fopen(numeFisier, "w");
    
    for (int i = 0; i < n; i++) {
        // Format: id,nume,medie
        fprintf(f, "%d,%s,%.2f\n", 
                studenti[i].id, 
                studenti[i].nume, 
                studenti[i].medie);
    }
    
    fclose(f);
}

int main() {
    printf("╔════════════════════════════════════════╗\n");
    printf("║       CITIRE FIȘIER                    ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    citireCSV("Studenti.txt");
    
    return 0;
}