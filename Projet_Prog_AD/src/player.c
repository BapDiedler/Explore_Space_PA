#include "../includes/player.h"

/**
 * @brief fonction d'initialisation du personnage
 * @param _tAstronaut* perso le personnage
 */
void initAstraunot(_tAstronaut *perso)
{
    // gestion du personnage
    perso->vie = 1;
    perso->positionX = 1;
    perso->positionY = 0;
    perso->saut = false;
    perso->next_level = false;
    perso->aToucheSol = false;
    perso->posSaut = 0;
    perso->nbPieces = 0;
    perso->DestR_sprite.x = perso->positionX * LARGEUR_PAVET;
    perso->DestR_sprite.y = perso->positionY * HAUTEUR_PAVET;
    perso->DestR_sprite.w = LARGEUR_JOUEUR; // Largeur du sprite
    perso->DestR_sprite.h = HAUTEUR_JOUEUR; // Hauteur du sprite
}

/**
 * @brief vérifie si le personnage est en vie
 * @param _tAstronaut * perso le personnage
 * @return vrai si le personnage est en vie, faux sinon
 */
bool estVivant(_tAstronaut *perso)
{
    if (perso->vie == 0)
    {
        return false;
    }
    return true;
}

/**
 * @brief gestion des collisions entre le personnage et le terrain par la droite
 * @param perso le personnage
 * @param nbColonnes nombre de colonnes dans le niveau
 * @return vrai si le personnage est en collision par la droite
 */
bool collisionRight(_tAstronaut *perso, int nbColonnes)
{
    return perso->positionX == nbColonnes - LARGEUR_JOUEUR / LARGEUR_PAVET;
}

/**
 * @brief gestion des collisions entre le personnage et le terrain par la gauche
 * @param perso le personnage
 * @return vrai si le personnage est en collision par la gauche
 */
bool collisionLeft(_tAstronaut *perso)
{
    return perso->positionX == 0;
}

/**
 * @brief gestion des collisions entre le personnage et le terrain par le bas
 * @param perso le personnage
 * @return vrai si le personnage est en collision par le bas
 */
bool collisionDown(_tAstronaut *perso, int nbLignes)
{
    return estEnCollisionBas(perso, nbLignes, perso->positionX);
}

/**
 * @brief gestion des collisions entre le personnage et le terrain par le haut
 * @param perso le personnage
 * @param posEcranY position en ordonné du bloc
 * @return vrai si le personnage est en collision par le haut
 */
bool collisionUP(_tAstronaut *perso, int posEcranY)
{
    return estEnCollisionHaut(perso, posEcranY, perso->positionX);
}

/// @brief vérifie si le personnage est en collision par la gauche
/// @param perso personnage
/// @param i position du bloc en ordonnée
/// @param j position du bloc en abscisse
/// @return vrai si le personnage est en collision
bool estEnCollisionGauche(_tAstronaut *perso, int i, int j)
{
    int nbCases = HAUTEUR_JOUEUR / HAUTEUR_PAVET;
    for (int k = 0; k < nbCases; k++)
    {
        if (j == perso->positionX + (LARGEUR_JOUEUR / LARGEUR_PAVET) && i == perso->positionY + (HAUTEUR_JOUEUR / HAUTEUR_PAVET) - 1 - k)
        {
            return true;
        }
    }
    return false;
}

/// @brief vérifie si le personnage est en collision par la droite
/// @param perso personnage
/// @param i position du bloc en ordonnée
/// @param j position du bloc en abscisse
/// @return vrai si le personnage est en collision
bool estEnCollisionDroit(_tAstronaut *perso, int i, int j)
{
    int nbCases = HAUTEUR_JOUEUR / HAUTEUR_PAVET;
    for (int k = 0; k < nbCases; k++)
    {
        if (j == perso->positionX - 1 && i == perso->positionY + (HAUTEUR_JOUEUR / HAUTEUR_PAVET) - 1 - k)
        {
            return true;
        }
    }
    return false;
}

/// @brief vérifie si le personnage est en collision par le haut
/// @param perso personnage
/// @param i position du bloc en ordonnée
/// @param j position du bloc en abscisse
/// @return vrai si le personnage est en collision
bool estEnCollisionHaut(_tAstronaut *perso, int i, int j)
{
    int nbCases = LARGEUR_JOUEUR / LARGEUR_PAVET;
    for (int k = 0; k < nbCases; k++)
    {
        if (j == perso->positionX + k && i == perso->positionY)
        {
            return true;
        }
    }
    return false;
}

/// @brief vérifie si le personnage est en collision par le bas
/// @param perso personnage
/// @param i position du bloc en ordonnée
/// @param j position du bloc en abscisse
/// @return vrai si le personnage est en collision
bool estEnCollisionBas(_tAstronaut *perso, int i, int j)
{
    int nbCases = LARGEUR_JOUEUR / LARGEUR_PAVET;
    for (int k = 0; k < nbCases; k++)
    {
        if (j == perso->positionX + k && i == perso->positionY + (HAUTEUR_JOUEUR / HAUTEUR_PAVET))
        {
            return true;
        }
    }
    return false;
}

/// @brief fontion qui applique les différentes caractéristiques des blocs
/// @param perso personnage
/// @param tab tableau avec la position des blocs
/// @param i position du bloc en ordonnée
/// @param j position du bloc en abscisse
/// @return vrai si le personnage est en collision
bool actionCollision(_tAstronaut *perso, char **tab, int i, int j)
{
    char c = tab[i][j] - 48; // convertion en chiffre
    if (c == 5 && perso->nbPieces >= 5)
    { // passage au niveau suivant
        perso->next_level = true;
        return true;
    }
    else if (c == 2 || c == 4 || c == 8)
    { // si le bloc est un piège
        tab[i][j] = ' ';
        printf("%d", perso->vie);
        perso->vie--;
        return false;
    }
    else if (c == 1)
    { // bloc pièce
        tab[i][j] = ' ';
        perso->nbPieces++;
        return false;
    }
    else if (c == 9)
    { // bloc vie
        tab[i][j] = ' ';
        perso->vie++;
        return false;
    }
    else if (c >= 0 && c < 10)
    { // autre bloc
        return true;
    }
    // si le bloc n'est pas valide il n'y a pas de collision
    return false;
}

/// @brief vérifie la collision entre l'astraunot et les blocs par la gauche
/// @param tab tableau de blocs
/// @param hauteur hauteur du tableu
/// @param largeur largeur du tableau
/// @param perso personnage
/// @return vrai si le personnage est en collision
bool collisionBlocLeft(_tAstronaut *perso, char **tab, int hauteur, int largeur)
{
    bool tmp = false;
    for (int i = 0; i < hauteur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {
            if (estEnCollisionGauche(perso, i, j))
            {
                tmp |= actionCollision(perso, tab, i, j);
            }
        }
    }
    return tmp;
}

/// @brief vérifie la collision entre l'astraunot et les blocs par la droite
/// @param tab tableau de blocs
/// @param hauteur hauteur du tableu
/// @param largeur largeur du tableau
/// @param perso personnage
/// @return vrai si le personnage est en collision
bool collisionBlocRight(_tAstronaut *perso, char **tab, int hauteur, int largeur)
{
    bool tmp = false;
    for (int i = 0; i < hauteur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {
            if (estEnCollisionDroit(perso, i, j))
            {
                tmp |= actionCollision(perso, tab, i, j);
            }
        }
    }
    return tmp;
}

/// @brief vérifie la collision entre l'astraunot et les blocs par le haut
/// @param tab tableau de blocs
/// @param hauteur hauteur du tableu
/// @param largeur largeur du tableau
/// @param perso personnage
/// @return vrai si le personnage est en collision
bool collisionBlocUp(_tAstronaut *perso, char **tab, int hauteur, int largeur)
{
    bool tmp = false;
    for (int i = 0; i < hauteur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {
            if (estEnCollisionHaut(perso, i + SPEED, j))
            {
                tmp |= actionCollision(perso, tab, i, j);
            }
        }
    }
    return tmp;
}

/// @brief vérifie la collision entre l'astraunot et les blocs par le bas
/// @param tab tableau de blocs
/// @param hauteur hauteur du tableu
/// @param largeur largeur du tableau
/// @param perso personnage
/// @return vrai si le personnage est en collision
bool collisionBlocDown(_tAstronaut *perso, char **tab, int hauteur, int largeur)
{
    bool tmp = false;
    for (int i = 0; i < hauteur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {
            if (estEnCollisionBas(perso, i, j))
            {
                tmp |= actionCollision(perso, tab, i, j);
            }
        }
    }
    return tmp;
}

/// @brief affiche le personnage
/// @param perso le personnage
/// @param renderer le renderer
/// @param imagePersonnage rectangle que l'on va récupèrer dans la feuille de sprite
void afficherPlayer(_tAstronaut *perso, SDL_Renderer *renderer, SDL_Rect imagePersonnage)
{
    SDL_RenderCopy(renderer, perso->texture, &imagePersonnage, &perso->DestR_sprite);
}