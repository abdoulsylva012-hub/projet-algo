#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Livre{
    int id;
    char titre[50];
    int annee;
    Livre *suivant;
}Livre;

typedef struct Liste{
    Livre *premier;
    int nb_livres
}Liste;

//Liste vide de livre
Liste *initialisation(){
    Liste *l=malloc(sizeof(Liste));
    l->premier = NULL;
    l->nb_livres = 0;
    return l;
}

//Ajout un livre en tete de liste
void ajoutTete(Liste *l, int id, char *titre, int annee){
    Livre *nouveau = malloc(sizeof(Livre));
    nouveau->id = id;
    strncpy(nouveau->titre, titre, 50);
    nouveau->titre[50]= '\0';
    nouveau->annee = annee;
    nouveau->suivant= l->premier;
    l->premier= nouveau;

}

//Ajout un livre en Fin de liste
void ajoutFin(Liste *l, int id, char *titre,int annee){
    Livre *nouveau= malloc(sizeof(Livre));
    nouveau->id= id;
    strncpy(nouveau->titre,titre,50);
    nouveau->titre[50]='\0';
    nouveau->annee= annee;
    nouveau->suivant= NULL;

    if(l->premier == NULL){
        l->premier= nouveau;
    }else{
        Livre *tmp = l->premier;
        while(tmp->suivant !=NULL){
            tmp = tmp->suivant;
        }
        tmp->suivant= nouveau;
    }
}

//Supprimer un livre par id en mettant a jour le nombre de livre
void supprimerElement(Liste *l,int id){
    Livre *tmp = l->premier;
    Livre  *ancien = NULL;

    while (tmp != NULL && tmp->id != id)
    {
        ancien = tmp;
        tmp = tmp->suivant;
    }

    if (ancien == NULL)
    {
        l->premier = tmp->suivant;
    }else{
        ancien->suivant= tmp->suivant;
    }
    free(tmp);
    
    
}

//Affichage de tous les livres
void afficherListe(Liste *l){
    Livre *tmp = l->premier;
    printf("Liste des %d Livres:\n", l->nb_livres);
    while (tmp !=NULL)
    {
        printf("Id: %d, Titre: %s, Annee: %d\n",tmp->id,tmp->titre,tmp->annee);
        tmp = tmp->suivant;
    }
    
}

//programme main 
int main(){
    Liste *l =initialisation();
    ajoutTete(l, 10,"Livre 1",2006);
    ajoutTete(l, 20,"Livre 2",2007);
    ajoutTete(l, 30,"Livre 3",2008);

    afficherListe(l);

    return 0;
}

