#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEL 5
#define MAX_EMAIL 5
#define MAX_ETUDIANTS 100
#define MAX_FORMATIONS 10

typedef struct {
    int identifiant;
    char nom[50];
    char prenom[50];
    char adresse[100];
    char telephones[MAX_TEL][15];
    char emails[MAX_EMAIL][50];
    int niveau;
} Etudiant;

typedef struct {
    char nomFormation[50];
    int idEtudiant;
    int niveaux[3];
} Formation;

Etudiant etudiants[MAX_ETUDIANTS];
Formation formations[MAX_FORMATIONS];
int nbEtudiants = 0;
int nbFormations = 0;

void ajouterEtudiant() {
    if (nbEtudiants < MAX_ETUDIANTS) {
        Etudiant etudiant;
        printf("Entrez l'identifiant de l'etudiant : ");
        scanf("%d", &etudiant.identifiant);
        printf("Entrez le nom de l'etudiant : ");
        scanf("%s", etudiant.nom);
        printf("Entrez le prenom de l'etudiant : ");
        scanf("%s", etudiant.prenom);
        printf("Entrez l'adresse de l'etudiant : ");
        scanf("%s", etudiant.adresse);
        printf("Entrez le niveau de l'etudiant (1, 2 ou 3) : ");
        scanf("%d", &etudiant.niveau);
        printf("Entrez le nombre de numeros de telephone de l'etudiant (maximum %d) : ", MAX_TEL);
        int nbTelephones;
        scanf("%d", &nbTelephones);
        printf("Entrez les numeros de telephone de l'etudiant : ");
        for (int i = 0; i < nbTelephones; i++) {
            scanf("%s", etudiant.telephones[i]);
        }
        printf("Entrez le nombre d'adresses email de l'etudiant (maximum %d) : ", MAX_EMAIL);
        int nbEmails;
        scanf("%d", &nbEmails);
        printf("Entrez les adresses email de l'etudiant : ");
        for (int i = 0; i < nbEmails; i++) {
            scanf("%s", etudiant.emails[i]);
        }
        etudiants[nbEtudiants++] = etudiant;
        printf("Etudiant ajoute avec succes.\n");
    } else {
        printf("Le nombre maximum d'etudiants a ete atteint.\n");
    }
}

void modifierEtudiant() {
    int id;
    printf("Entrez l'identifiant de l'etudiant a modifier : ");
    scanf("%d", &id);
    int index = -1;
    for (int i = 0; i < nbEtudiants; i++) {
        if (etudiants[i].identifiant == id) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        Etudiant etudiant = etudiants[index];
        printf("Entrez le nouveau nom de l'etudiant (ou '-' pour ne pas modifier) : ");
        char nom[50];
        scanf("%s", nom);
        if (strcmp(nom, "-") != 0) {
            strcpy(etudiant.nom, nom);
        }
        printf("Entrez le nouveau prenom de
