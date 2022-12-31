#ifndef PAVAGE_H
#define PAVAGE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define LARGEUR_FENETRE 30
#define HAUTEUR_FENETRE 30
#define HAUTEUR_PAVET (int)((HAUTEUR_FENETRE*32)/20)
#define LARGEUR_PAVET (int)((LARGEUR_FENETRE*32)/20)
#define HAUTEUR_PAVET_IMAGE 32
#define LARGEUR_PAVET_IMAGE 32

/// @brief le pavage de notre niveau
typedef struct _sPavage
{
    SDL_Rect DestR_pavet[LARGEUR_FENETRE * HAUTEUR_FENETRE]; // rectangle désignant l'image du pavet
    SDL_Rect SrcR_pavet[LARGEUR_FENETRE * HAUTEUR_FENETRE];  // rectangle désignant la position de l'image
    SDL_Texture *pavages;                                    // texture du pavage
    int posEcranX;
    int posEcranY;
} _tPavage;

/// @brief initPavage initialise le fond de la fenêtre en fonction du tableau
/// @param pavages pavages qui va être initialisé
/// @param tab tableau qui va nous permettre d'initialiser le pavage
void initPavage(_tPavage *pavages, char **tab);

/// @brief onction qui modifie le terrain en fonction de tab
/// @param tab tableau qui nous permet de mettre le pavage à jour
/// @param pavages pavage à modifier
/// @param nbColonnes nombre de colonnes dans le terrain
void updatePavage(char **tab, _tPavage *pavages, int nbColonnes);

/// @brief la fonction affiche le pavage sur le renderer
/// @param pavages pavage à afficher
/// @param renderer renderer pour l'affichage
/// @param tab tableaau pour update le niveau
/// @param nbc nombre de colonnes dans le niveau
void afficherPavage(_tPavage *pavages, SDL_Renderer *renderer, char **tab, int nbC);

#endif