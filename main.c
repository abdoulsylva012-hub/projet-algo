#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Etudiant {
    int idKairos;
    char nom[50];
    char prenom[50];
    float moyenne;
    struct Etudiant* suivant;
} Etudiant;

Etudiant* creerEtudiant(int id, char* nom, char* prenom, float moyenne) {
    Etudiant* nouveau = (Etudiant*)malloc(sizeof(Etudiant));
    if (nouveau == NULL) {
        printf("Erreur d'allocation memoire!\n");
        return NULL;
    }

    nouveau->idKairos = id;
    strcpy(nouveau->nom, nom);
    strcpy(nouveau->prenom, prenom);
    nouveau->moyenne = moyenne;
    nouveau->suivant = NULL;

    return nouveau;
}

void ajouterEnTete(Etudiant** tete, int id, char* nom, char* prenom, float moyenne) {
    Etudiant* nouveau = creerEtudiant(id, nom, prenom, moyenne);
    if (nouveau != NULL) {
        nouveau->suivant = *tete;
        *tete = nouveau;
        printf("Etudiant ajoute en tete avec succes!\n");
    }
}

void ajouterApres(Etudiant* tete, int idRecherche, int id, char* nom, char* prenom, float moyenne) {
    Etudiant* courant = tete;

    while (courant != NULL && courant->idKairos != idRecherche) {
        courant = courant->suivant;
    }

    if (courant == NULL) {
        printf("Etudiant avec ID %d non trouve!\n", idRecherche);
        return;
    }

    Etudiant* nouveau = creerEtudiant(id, nom, prenom, moyenne);
    if (nouveau != NULL) {
        nouveau->suivant = courant->suivant;
        courant->suivant = nouveau;
        printf("Etudiant ajoute apres l'ID %d avec succes!\n", idRecherche);
    }
}

void supprimerEtudiant(Etudiant** tete, int id) {
    if (*tete == NULL) {
        printf("La liste est vide!\n");
        return;
    }

    Etudiant* courant = *tete;
    Etudiant* precedent = NULL;

    if (courant->idKairos == id) {
        *tete = courant->suivant;
        free(courant);
        printf("Etudiant avec ID %d supprime!\n", id);
        return;
    }

    while (courant != NULL && courant->idKairos != id) {
        precedent = courant;
        courant = courant->suivant;
    }

    if (courant == NULL) {
        printf("Etudiant avec ID %d non trouve!\n", id);
        return;
    }

    precedent->suivant = courant->suivant;
    free(courant);

    printf("Etudiant avec ID %d supprime!\n", id);
}

void afficherListe(Etudiant* tete) {
    if (tete == NULL) {
        printf("La liste est vide!\n");
        return;
    }

    printf("\n=== Liste des etudiants ===\n");
    Etudiant* courant = tete;
    int compteur = 1;

    while (courant != NULL) {
        printf("%d. ID: %d | Nom: %s %s | Moyenne: %.2f\n",
               compteur, courant->idKairos, courant->nom,
               courant->prenom, courant->moyenne);

        courant = courant->suivant;
        compteur++;
    }
    printf("===========================\n\n");
}

void afficherMoyenne(Etudiant* tete) {
    if (tete == NULL) {
        printf("La liste est vide!\n");
        return;
    }

    float somme = 0;
    int count = 0;
    Etudiant* courant = tete;

    while (courant != NULL) {
        somme += courant->moyenne;
        count++;
        courant = courant->suivant;
    }

    printf("Moyenne generale des etudiants: %.2f\n", somme / count);
}

void supprimerDernier(Etudiant** tete) {
    if (*tete == NULL) {
        printf("La liste est vide!\n");
        return;
    }

    if ((*tete)->suivant == NULL) {
        free(*tete);
        *tete = NULL;
        printf("Dernier etudiant supprime!\n");
        return;
    }

    Etudiant* courant = *tete;

    while (courant->suivant->suivant != NULL) {
        courant = courant->suivant;
    }

    free(courant->suivant);
    courant->suivant = NULL;
    printf("Dernier etudiant supprime!\n");
}

void viderListe(Etudiant** tete) {
    Etudiant* courant = *tete;
    Etudiant* suivant;

    while (courant != NULL) {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }

    *tete = NULL;
    printf("Liste videe!\n");
}

void afficherMenu() {
    printf("\n========== MENU ==========\n");
    printf("1. Ajouter un etudiant en tete\n");
    printf("2. Ajouter un etudiant apres un element donne\n");
    printf("3. Supprimer un etudiant\n");
    printf("4. Afficher la liste\n");
    printf("5. Afficher la moyenne\n");
    printf("6. Supprimer le dernier\n");
    printf("7. Vider la liste\n");
    printf("8. Quitter\n");
    printf("==========================\n");
    printf("Votre choix: ");
}

int main() {
    Etudiant* tete = NULL;
    int choix, id, idRecherche;
    char nom[50], prenom[50];
    float moyenne;

    printf("=== Gestionnaire d'etudiants ===\n");

    do {
        afficherMenu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("ID Kairos: ");
                scanf("%d", &id);
                printf("Nom: ");
                scanf("%s", nom);
                printf("Prenom: ");
                scanf("%s", prenom);
                printf("Moyenne: ");
                scanf("%f", &moyenne);
                ajouterEnTete(&tete, id, nom, prenom, moyenne);
                break;

            case 2:
                printf("ID de l'etudiant apres lequel ajouter: ");
                scanf("%d", &idRecherche);
                printf("ID Kairos du nouvel etudiant: ");
                scanf("%d", &id);
                printf("Nom: ");
                scanf("%s", nom);
                printf("Prenom: ");
                scanf("%s", prenom);
                printf("Moyenne: ");
                scanf("%f", &moyenne);
                ajouterApres(tete, idRecherche, id, nom, prenom, moyenne);
                break;

            case 3:
                printf("ID de l'etudiant a supprimer: ");
                scanf("%d", &id);
                supprimerEtudiant(&tete, id);
                break;

            case 4:
                afficherListe(tete);
                break;

            case 5:
                afficherMoyenne(tete);
                break;

            case 6:
                supprimerDernier(&tete);
                break;

            case 7:
                viderListe(&tete);
                break;

            case 8:
                printf("Au revoir!\n");
                viderListe(&tete);
                break;

            default:
                printf("Choix invalide!\n");
        }

    } while (choix != 8);

    return 0;
}
