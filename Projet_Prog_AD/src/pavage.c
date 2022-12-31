#include "../includes/pavage.h"


/// @brief initialise le fond de la fenêtre en fonction du tableau
/// @param pavages pavages qui va être initialisé
/// @param tab tableau qui va nous permettre d'initialiser le pavage
void initPavage(_tPavage *pavages, char **tab)
{
    pavages->posEcranX = 0;//la première image est en haut à gauche de la map
    pavages->posEcranY = 0;
    updatePavage(tab, pavages, LARGEUR_FENETRE);
}

/// @brief onction qui modifie le terrain en fonction de tab
/// @param tab tableau qui nous permet de mettre le pavage à jour
/// @param pavages pavage à modifier
/// @param nbColonnes nombre de colonnes dans le terrain
void updatePavage(char **tab, _tPavage *pavages, int nbColonnes)
{
    int k = 0;

    //initialisation de l'image pavage
    int x = pavages->posEcranX;
    int y = pavages->posEcranY;
    int tailleW = LARGEUR_PAVET_IMAGE;
    int tailleH = HAUTEUR_PAVET_IMAGE;

    int val;
    if (x < nbColonnes)
    {   //on parcourt là où l'on se trouve dans le tableau
        for (int i = x; i < LARGEUR_FENETRE + x; i++)
        {
            for (int j = y; j < HAUTEUR_FENETRE + y; j++)
            {
                if (tab[j][i] == ' ')
                { // en cas d'absence de bloc on créer un bloc null
                    pavages->SrcR_pavet[k].x = 0;
                    pavages->SrcR_pavet[k].y = 0;
                    pavages->SrcR_pavet[k].w = 0;
                    pavages->SrcR_pavet[k].h = 0;
                }
                val = tab[j][i] - '0';
                if (val <= 9 && val >= 0)
                { //lors de la présence d'un bloc
                    pavages->SrcR_pavet[k].x = val * tailleW;
                    pavages->SrcR_pavet[k].y = 0; // car tous les blocs sont sur la même ligne
                    pavages->SrcR_pavet[k].w = tailleW;
                    pavages->SrcR_pavet[k].h = tailleH;
                }
                k++;
            }
        }
    }
}

/// @brief la fonction affiche le pavage sur le renderer
/// @param pavages pavage à afficher
/// @param renderer renderer pour l'affichage
/// @param tab tableaau pour update le niveau
/// @param nbc nombre de colonnes dans le niveau
void afficherPavage(_tPavage *pavages, SDL_Renderer *renderer, char **tab, int nbC)
{
    updatePavage(tab, pavages, nbC);//on modifie le pavage en fonction du tableau 
    for (int k = 0; k < (LARGEUR_FENETRE * HAUTEUR_FENETRE); k++)
    {   //on affiche chaque blocs
        SDL_RenderCopy(renderer, pavages->pavages, &pavages->SrcR_pavet[k], &pavages->DestR_pavet[k]);
    }
}