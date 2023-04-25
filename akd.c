#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structure d'un étudiant */
typedef struct Etudiant
{
    int identifiant;
    char nom[50];
    char prenom[50];
    char adresse[100];
    char telephone[10][15];
    char email[10][50];
    int niveau;
    struct Etudiant *suivant;
} Etudiant;

/* Structure d'une formation */
typedef struct Formation
{
    char nom[50];
    int identifiantEtudiant;
    int niveaux[10];
    struct Etudiant *etudiants;
    struct Formation *suivant;
} Formation;

// Prototypes des fonctions
void afficherMenu();
void ajouterEtudiant();
void modifierEtudiant();
void supprimerEtudiant();
int afficherListeEtudiants();
void ajouterFormation();
void modifierFormation();
void supprimerFormation();
void afficherFormations();
void afficherEtudiantsFormation();
void afficherEtudiantsNiveau();

Etudiant *listeEtudiants = NULL;   /* Liste des étudiants */
Formation *listeFormations = NULL; /* Liste des formations */

int main()
{
    int choix;
    Etudiant *tete = NULL;

    do
    {
        afficherMenu();
        scanf("%d", &choix);
        switch (choix)
        {

        case 1:
        {
            int identifiant, niveau;
            char nom[50], prenom[50], adresse[100], telephone[10][15], email[10][50];
            printf("Entrez les informations de l'etudiant:\n");
            printf("Identifiant: ");
            scanf("%d", &identifiant);
            printf("Nom: ");
            scanf("%s", nom);
            printf("Prenom: ");
            scanf("%s", prenom);
            printf("Adresse: ");
            scanf("%s", adresse);
            printf("Numero de telephone (max 10, separer par des espaces): ");
            for (int i = 0; i < 10; i++)
            {
                scanf("%s", telephone[i]);
            }

            // Modifier le code pour stocker les numéros de téléphone dans un tableau à une dimension
              char num_telephone[10][15];
              int num_telephone_index = 0;
              for (int i = 0; i < 10; i++)
            {
                //scanf("%s", num_telephone[num_telephone_index]);
                gets(num_telephone[num_telephone_index]);
                num_telephone_index++;
            }

            printf("Niveau: ");
            scanf("%d", &niveau);
            ajouterEtudiant(identifiant, nom, prenom, adresse, telephone, email, niveau);
            printf("Vous avez ajoute un etudiant.\n");
            break;
        }

        case 2:
            modifierEtudiant();
            break;
        case 3:
            supprimerEtudiant();
            break;
        case 4:
            printf("Nombre d'étudiants : %d\n", afficherListeEtudiants(tete));

            break;
        case 5:
            ajouterFormation();
            break;
        case 6:
            modifierFormation();
            break;
        case 7:
            supprimerFormation();
            break;
        case 8:
            afficherFormations();
            break;
        case 9:
            afficherEtudiantsFormation();
            break;
        case 10:
            afficherEtudiantsNiveau();
            break;
        case 11:
            printf("Au revoir !");
            break;
        default:
            printf("Choix invalide.\n");
        }
    } while (choix != 11);

    return 0;
}

/* Fonction pour le menu principal */
void afficherMenu()
{
    printf("***************MENU PRINCIPAL***************\n");
    printf("(1). Gestion des étudiants : \n 1-ajouterEtudiant \n 2-Modifier \n 3-Supprimer \n 4-Afficher la liste des etudiants par ordre alphabétique.\n");
    printf("(2). Gestion des formations :\n 5-Ajouter \n 6-Modifier \n 7-Supprimer \n 8-Afficher la liste des formations.\n");
    printf("(3). Gestion des étudiants par classe : \n 9-afficher la liste des étudiants par formation \n 10-afficher la liste des étudiants d'un niveau donné.\n");
    printf("(4). 11-Quitter le programme.\n");
    printf("Entrez votre choix : ");
}

//Gestion des Etudiants ()
/* Fonction pour ajouter un étudiant à la liste */
void ajouterEtudiant(int identifiant, char nom[], char prenom[], char adresse[], char telephone[][15], char email[][50], int niveau)
{
    Etudiant *nouvelEtudiant = (Etudiant *)malloc(sizeof(Etudiant));
    nouvelEtudiant->identifiant = identifiant;
    strcpy(nouvelEtudiant->nom, nom);
    strcpy(nouvelEtudiant->prenom, prenom);
    strcpy(nouvelEtudiant->adresse, adresse);
    for (int i = 0; i < 10; i++)
    {
        strcpy(nouvelEtudiant->telephone[i], telephone[i]);
        strcpy(nouvelEtudiant->email[i], email[i]);
    }
    nouvelEtudiant->niveau = niveau;
    nouvelEtudiant->suivant = listeEtudiants;
    listeEtudiants = nouvelEtudiant;
}

/* Fonction pour modifier les informations d'un étudiant */
void modifierEtudiant(int identifiant, char nom[], char prenom[], char adresse[], char telephone[][15], char email[][50], int niveau)
{
    Etudiant *courant = listeEtudiants;
    while (courant != NULL)
    {
        if (courant->identifiant == identifiant)
        {
            strcpy(courant->nom, nom);
            strcpy(courant->prenom, prenom);
            strcpy(courant->adresse, adresse);
            for (int i = 0; i < 10; i++)
            {
                strcpy(courant->telephone[i], telephone[i]);
                strcpy(courant->email[i], email[i]);
            }
            courant->niveau = niveau;
            break;
        }
        courant = courant->suivant;
    }
}

/* Fonction pour supprimer un étudiant de la liste */
void supprimerEtudiant(int identifiant)
{
    Etudiant *courant = listeEtudiants;
    Etudiant *precedent = NULL;
    while (courant != NULL)
    {
        if (courant->identifiant == identifiant)
        {
            if (precedent == NULL)
            {
                listeEtudiants = courant->suivant;
            }
            else
            {
                precedent->suivant = courant->suivant;
            }
            free(courant);
            break;
        }
        precedent = courant;
        courant = courant->suivant;
    }
}
/* Fonction pour trier la liste d'étudiants par ordre alphabétique */
void trierListeEtudiants(Etudiant **tete)
{
    int swapped;
    Etudiant *ptr1;
    Etudiant *lptr = NULL;

    /* Vérifier si la liste est vide */
    if (*tete == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = *tete;

        while (ptr1->suivant != lptr)
        {
            if (strcmp(ptr1->nom, ptr1->suivant->nom) > 0)
            {
                /* Swap des deux étudiants */
                Etudiant *temp = ptr1;
                ptr1 = ptr1->suivant;
                ptr1->suivant = temp;
                swapped = 1;
            }
            else
                ptr1 = ptr1->suivant;
        }
        lptr = ptr1;
    } while (swapped);
}

/* Fonction pour afficher la liste des étudiants par ordre alphabétique */
// void afficherListeEtudiants(Etudiant *tete)
// {
//     trierListeEtudiants(&tete);
//     printf("\n--- Liste des etudiants par ordre alphabetique ---\n");
//     while (tete != NULL)
//     {
//         printf("Identifiant: %d, Nom: %s, Prenom: %s, Adresse: %s, Telephone: %s, Email: %s, Niveau: %d\n", tete->identifiant, tete->nom, tete->prenom, tete->adresse, tete->telephone, tete->email, tete->niveau);
//         tete = tete->suivant;
//     }
//     printf("\n");
// }/* Fonction pour afficher la liste des étudiants par ordre alphabétique */
int afficherListeEtudiants(Etudiant *listeEtudiant)
{

    Etudiant *etudiant = listeEtudiant;
    int nbEtudiants = 0;

    while (listeEtudiant != NULL)
    {
        printf("Nom : %s\n", listeEtudiant->nom);
        printf("Prenom : %s\n", listeEtudiant->prenom);
        printf("Adresse : %s\n", listeEtudiant->adresse);
        printf("Telephone : %s\n", listeEtudiant->telephone[0]);
        printf("Email : %s\n", listeEtudiant->email[0]);
        printf("Niveau : %d\n", listeEtudiant->niveau);
        printf("-----------------------------\n");

        listeEtudiant = listeEtudiant->suivant;
        nbEtudiants++;
    }

    return nbEtudiants;
}

//Gestion des formations()
/* Fonction pour ajouter une formation */
void ajouterFormation(struct Formation **listeFormations, int identifiantEtudiant, char nom[], int niveaux[])
{
    /* Créer la nouvelle formation */
    struct Formation *nouvelleFormation = (struct Formation *)malloc(sizeof(struct Formation));
    nouvelleFormation->identifiantEtudiant = identifiantEtudiant;
    strcpy(nouvelleFormation->nom, nom);
    memcpy(nouvelleFormation->niveaux, niveaux, sizeof(int) * 10);
    nouvelleFormation->etudiants = NULL;
    nouvelleFormation->suivant = NULL;

    /* Insérer la nouvelle formation au début de la liste */
    nouvelleFormation->suivant = *listeFormations;
    *listeFormations = nouvelleFormation;
}
/* Fonction pour modifier une formation */
void modifierFormation(struct Formation *listeFormations, int identifiantEtudiant)
{
    struct Formation *formation = listeFormations;
    while (formation != NULL)
    {
        if (formation->identifiantEtudiant == identifiantEtudiant)
        {
            /* Modifier la formation */
            printf("Entrez le nouveau nom de la formation: ");
            fgets(formation->nom, 50, stdin);
            formation->nom[strcspn(formation->nom, "\n")] = '\0';

            printf("Entrez les nouveaux niveaux de la formation:\n");
            for (int i = 0; i < 10; i++)
            {
                printf("Niveau %d: ", i + 1);
                scanf("%d", &formation->niveaux[i]);
            }

            printf("La formation a ete modifiee avec succes.\n");
            return;
        }
        formation = formation->suivant;
    }

    printf("La formation avec l'ID %d n'existe pas.\n", identifiantEtudiant);
}
/* Fonction pour supprimer une formation */
void supprimerFormation(struct Formation **listeFormations, int identifiantEtudiant)
{
    struct Formation *formationCourante = *listeFormations;
    struct Formation *formationPrecedente = NULL;

    /* Parcourir la liste pour trouver la formation à supprimer */
    while (formationCourante != NULL && formationCourante->identifiantEtudiant != identifiantEtudiant)
    {
        formationPrecedente = formationCourante;
        formationCourante = formationCourante->suivant;
    }

    /* Si la formation est trouvée, la supprimer */
    if (formationCourante != NULL)
    {
        /* Délier la formation de la liste */
        if (formationPrecedente == NULL)
        {
            /* La formation est en tête de liste */
            *listeFormations = formationCourante->suivant;
        }
        else
        {
            /* La formation est au milieu ou à la fin de la liste */
            formationPrecedente->suivant = formationCourante->suivant;
        }

        /* Libérer la mémoire allouée pour la formation */
        free(formationCourante);

        printf("La formation a été supprimée avec succès.\n");
    }
    else
    {
        printf("La formation avec l'ID %d n'existe pas.\n", identifiantEtudiant);
    }
}
/* Fonction pour afficher la liste des formations */
void afficherFormations(struct Formation *listeFormations)
{
    struct Formation *formation = listeFormations;

    printf("Liste des formations :\n");
    while (formation != NULL)
    {
        printf("ID : %d\n", formation->identifiantEtudiant);
        printf("Nom : %s\n", formation->nom);
        printf("Niveaux : ");
        for (int i = 0; i < 10; i++)
        {
            printf("%d ", formation->niveaux[i]);
        }
        printf("\n\n");

        formation = formation->suivant;
    }
}
/* Fonction pour afficher la liste des étudiants par formation */
void afficherEtudiantsFormation(struct Formation *listeFormations)
{
    struct Formation *formation = listeFormations;

    printf("Liste des étudiants par formation :\n");
    while (formation != NULL)
    {
        printf("Formation : %s\n", formation->nom);

        struct Etudiant *etudiant = formation->etudiants;
        while (etudiant != NULL)
        {
            printf("- %s %s\n", etudiant->prenom, etudiant->nom);
            etudiant = etudiant->suivant;
        }

        printf("\n");
        formation = formation->suivant;
    }
}
//Gestion des étudiants par classe ()
/* Fonction pour afficher la liste des étudiants d'un niveau donné */
void afficherEtudiantsNiveau(struct Formation *listeFormations, int niveaux)
{
    struct Formation *formation = listeFormations;

    printf("Liste des étudiants du niveau %d :\n", niveaux);
    while (formation != NULL)
    {
        for (int i = 0; i < 10; i++)
        {
            if (formation->niveaux[i] == niveaux)
            {
                struct Etudiant *etudiant = formation->etudiants;
                printf("Formation : %s\n", formation->nom);
                while (etudiant != NULL)
                {
                    printf("- %s %s\n", etudiant->prenom, etudiant->nom);
                    etudiant = etudiant->suivant;
                }
                printf("\n");
                break;
            }
        }
        formation = formation->suivant;
    }
}
