#ifndef FONCTIONS_SDL_H
#define FONCTIONS_SDL_H

#include "../includes/player.h"

/**
 * @brief charge une image sur un renderer
 * @param const char* nomfichier le nom du fichier dans lequel se trouve l'image que l'on veut charger
 * @param SDL_Renderer* renderer le renderer
 * @return la texture correspondante
 */
SDL_Texture *charger_image(const char *nomfichier, SDL_Renderer *renderer);

/**
 * @brief charge l'image avec de la transparence. La couleur qui sera transparente sera définie par le code rgb
 * @param const char* nomfichier le nom du fichier dans lequel se trouve l'image que l'on veut charger
 * @param SDL_Renderer* renderer le renderer
 * @param Uint8 r le rouge
 * @param Uint8 g le vert
 * @param Uint8 b le bleu
 * @return la texture correspondant au fichier choisit sans la couleur associé au code RGB
 */
SDL_Texture *charger_image_transparente(const char *nomfichier, SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b);

/**
 * @brief charge un texte sur le renderer
 * @param const char* message le texte que l'on veut charger
 * @param SDL_Renderer* renderer le renderer
 * @param TTF_Font *font la police
 * @param SDL_Color color la couleur
 * @return la texture du texte chargée
 */
SDL_Texture *charger_texte(const char *message, SDL_Renderer *renderer, TTF_Font *font, SDL_Color color);

/**
 * @brief fonction qui initialise l'image du personnage
 * @param char * nomFichier le nom du fichier de l'image du personnage
 * @param _tAstronaut* perso le personnage
 * @param SDL_Renderer* renderer le renderer
 */
void lireImagePlayer(char *nomFichier, _tAstronaut *perso, SDL_Renderer *renderer);

/// @brief charge la texture et place les pavets
/// @param nomFichier le nom du fichier avec les pavets
/// @param pavage le pavage
/// @param renderer le renderer
void lireImagePavage(char *nomFichier, _tPavage *pavages, SDL_Renderer *renderer);

/**
 * @brief fonction qui permet de passer le fichier des chiffres pour obtenir une texture
 * @param nomFichier nom du fichier d'entrée
 * @param renderer renderer du jeu
 * @return la texture des chiffres
*/
SDL_Texture * lireImageChiffres(char* nomFichier, SDL_Renderer *renderer);

#endif
