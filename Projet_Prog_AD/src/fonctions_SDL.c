#include "../includes/fonctions_SDL.h"

/**
 * @brief fonction qui initialise l'image du personnage
 * @param char * nomFichier le nom du fichier de l'image du personnage
 * @param _tAstronaut* perso le personnage
 * @param SDL_Renderer* renderer le renderer
 */
void lireImagePlayer(char *nomFichier, _tAstronaut *perso, SDL_Renderer *renderer)
{
    Uint8 r = 0, g = 255, b = 255;
    perso->texture = charger_image_transparente(nomFichier, renderer, r, g, b);
    int tailleWc = 0;
    int tailleHc = 0;
    SDL_QueryTexture(perso->texture, NULL, NULL, &tailleWc, &tailleHc);
    tailleWc /= 3;
    tailleHc /= 2;
    for (int k = 0; k < NB_IMAGES_SPRITES; k++)
    {
        perso->SrcR_sprite[k].x = k > 2 ? (k - 3) * (tailleWc) : k * (tailleWc);
        perso->SrcR_sprite[k].y = k > 2 ? tailleHc : 0;
        perso->SrcR_sprite[k].w = tailleWc;
        perso->SrcR_sprite[k].h = tailleHc;
    }
}

/**
 * @brief charge une image sur un renderer
 * @param const char* nomfichier le nom du fichier dans lequel se trouve l'image que l'on veut charger
 * @param SDL_Renderer* renderer le renderer
 * @return la texture correspondante
 */
SDL_Texture *charger_image(const char *nomfichier, SDL_Renderer *renderer)
{
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    surface = SDL_LoadBMP(nomfichier);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

/**
 * @brief charge l'image avec de la transparence. La couleur qui sera transparente sera définie par le code rgb
 * @param const char* nomfichier le nom du fichier dans lequel se trouve l'image que l'on veut charger
 * @param SDL_Renderer* renderer le renderer
 * @param Uint8 r le rouge
 * @param Uint8 g le vert
 * @param Uint8 b le bleu
 * @return la texture correspondant au fichier choisit sans la couleur associé au code RGB
 */
SDL_Texture *charger_image_transparente(const char *nomfichier, SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    surface = SDL_LoadBMP(nomfichier);
    Uint32 key = SDL_MapRGB(surface->format, r, g, b);
    SDL_SetColorKey(surface, SDL_TRUE, key);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

/**
 * @brief charge un texte sur le renderer
 * @param const char* message le texte que l'on veut charger
 * @param SDL_Renderer* renderer le renderer
 * @param TTF_Font *font la police
 * @param SDL_Color color la couleur
 * @return la texture du texte chargée
 */
SDL_Texture *charger_texte(const char *message, SDL_Renderer *renderer, TTF_Font *font, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, message, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

/// @brief charge la texture et place les pavets
/// @param nomFichier le nom du fichier avec les pavets
/// @param pavage le pavage
/// @param renderer le renderer
void lireImagePavage(char *nomFichier, _tPavage *pavages, SDL_Renderer *renderer)
{
    Uint8 r = 0, g = 255, b = 255;
    pavages->pavages = charger_image_transparente(nomFichier, renderer, r, g, b);
    int cpt = 0;
    for (int i = 0; i < LARGEUR_FENETRE; i++)
    {
        for (int j = 0; j < HAUTEUR_FENETRE; j++)
        {
            pavages->DestR_pavet[cpt].x = i * LARGEUR_PAVET;
            pavages->DestR_pavet[cpt].y = j * HAUTEUR_PAVET;
            pavages->DestR_pavet[cpt].w = LARGEUR_PAVET; // Largeur du sprite
            pavages->DestR_pavet[cpt].h = HAUTEUR_PAVET; // Hauteur du sprite
            cpt++;
        }
    }
}

/**
 * @brief fonction qui permet de passer le fichier des chiffres pour obtenir une texture
 * @param nomFichier nom du fichier d'entrée
 * @param renderer renderer du jeu
 * @return la texture des chiffres
*/
SDL_Texture * lireImageChiffres(char* nomFichier, SDL_Renderer *renderer){
    SDL_Texture *texture = NULL;
    Uint8 r = 255, g = 255, b = 255;
    texture = charger_image_transparente(nomFichier, renderer, r, g, b);
    return texture;
}