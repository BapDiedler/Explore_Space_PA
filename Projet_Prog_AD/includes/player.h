#ifndef PLAYER_H
#define PLAYER_H

#include "../includes/pavage.h"

#define HAUTEUR_JOUEUR 2*HAUTEUR_PAVET
#define LARGEUR_JOUEUR 2*LARGEUR_PAVET
#define SPEED 1
#define LONGUEUR_SAUT 15
#define NB_IMAGES_SPRITES 6

/**
 * Stucture représentant l'astronaut
 */
typedef struct _sAstronaut
{
    SDL_Rect DestR_sprite;
    SDL_Rect SrcR_sprite[NB_IMAGES_SPRITES];
    SDL_Texture *texture;
    int positionX;
    int positionY;
    bool saut;
    int posSaut;
    int vie;
    int nbPieces;
    bool next_level;
    bool aToucheSol;
} _tAstronaut;

/**
 * @brief fonction d'initialisation du personnage
 * @param _tAstronaut* perso le personnage
 */
void initAstraunot(_tAstronaut *perso);

/**
 * @brief vérifie si le personnage est en vie
 * @param _tAstronaut * perso le personnage
 * @return vrai si le personnage est en vie, faux sinon
 */
bool estVivant(_tAstronaut *perso);

/// @brief vérifie si le personnage est en collision par la gauche
/// @param perso personnage
/// @param i position du bloc en ordonnée
/// @param j position du bloc en abscisse
/// @return vrai si le personnage est en collision
bool estEnCollisionGauche(_tAstronaut *perso, int i, int j);

/// @brief vérifie si le personnage est en collision par la droite
/// @param perso personnage
/// @param i position du bloc en ordonnée
/// @param j position du bloc en abscisse
/// @return vrai si le personnage est en collision
bool estEnCollisionDroit(_tAstronaut *perso, int i, int j);

/// @brief regardde si le perso est en collision par le haut
/// @param perso personnage
/// @param i position du bloc en ordonnée
/// @param j position du bloc en abscisse
/// @return vrai si le personnage est en collision
bool estEnCollisionHaut(_tAstronaut *perso, int i, int j);

/// @brief regardde si le perso est en collision par le bas
/// @param perso personnage
/// @param i position du bloc en ordonnée
/// @param j position du bloc en abscisse
/// @return vrai si le personnage est en collision
bool estEnCollisionBas(_tAstronaut *perso, int i, int j);

/**
 * @brief gestion des collisions entre le personnage et le terrain par le haut
 * @param perso le personnage
 * @param posEcranY position en ordonné du bloc
 * @return vrai si le personnage est en collision par le haut
 */
bool collisionUP(_tAstronaut *perso, int posEcranY);

/**
 * @brief gestion des collisions entre le personnage et le terrain par la droite
 * @param perso le personnage
 * @param nbColonnes nombre de colonnes dans le niveau
 * @return vrai si le personnage est en collision par la droite
 */
bool collisionRight(_tAstronaut *perso, int nbColonnes);

/**
 * @brief gestion des collisions entre le personnage et le terrain par la gauche
 * @param perso le personnage
 * @return vrai si le personnage est en collision par la gauche
 */
bool collisionLeft(_tAstronaut *perso);

/**
 * @brief gestion des collisions entre le personnage et le terrain par le bas
 * @param perso le personnage
 * @return vrai si le personnage est en collision par le bas
 */
bool collisionDown(_tAstronaut *perso, int nbLignes);

/// @brief fontion qui applique les différentes caractéristiques des blocs
/// @param perso personnage
/// @param tab tableau avec la position des blocs
/// @param i position du bloc en ordonnée
/// @param j position du bloc en abscisse
/// @return vrai si le personnage est en collision
bool actionCollision(_tAstronaut *perso, char **tab, int i, int j);

/// @brief vérifie la collision entre l'astraunot et les blocs par la gauche
/// @param tab tableau de blocs
/// @param hauteur hauteur du tableu
/// @param largeur largeur du tableau
/// @param perso personnage
/// @return vrai si le personnage est en collision
bool collisionBlocLeft(_tAstronaut *perso, char **tab, int hauteur, int largeur);

/// @brief vérifie la collision entre l'astraunot et les blocs par la droite
/// @param tab tableau de blocs
/// @param hauteur hauteur du tableu
/// @param largeur largeur du tableau
/// @param perso personnage
/// @return vrai si le personnage est en collision
bool collisionBlocRight(_tAstronaut *perso, char **tab, int hauteur, int largeur);

/// @brief vérifie la collision entre l'astraunot et les blocs par le haut
/// @param tab tableau de blocs
/// @param hauteur hauteur du tableu
/// @param largeur largeur du tableau
/// @param perso personnage
/// @return vrai si le personnage est en collision
bool collisionBlocUp(_tAstronaut *perso, char **tab, int hauteur, int largeur);

/// @brief vérifie la collision entre l'astraunot et les blocs par le bas
/// @param tab tableau de blocs
/// @param hauteur hauteur du tableu
/// @param largeur largeur du tableau
/// @param perso personnage
/// @return vrai si le personnage est en collision
bool collisionBlocDown(_tAstronaut *perso, char **tab, int hauteur, int largeur);

/// @brief affiche le personnage
/// @param perso le personnage
/// @param renderer le renderer
/// @param imagePersonnage rectangle que l'on va récupèrer dans la feuille de sprite
void afficherPlayer(_tAstronaut *perso, SDL_Renderer *renderer, SDL_Rect imagePersonnage);

#endif