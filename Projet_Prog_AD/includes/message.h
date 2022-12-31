#ifndef MESSAGE_H
#define MESSAGE_H

#include "../includes/pavage.h"
#include "../includes/fonctions_SDL.h"

#define NB_MESSAGES 8 //nombre de messages dans le jeu
#define TAILLE_NOM_FICHIER 25 //taille max d'un message

//structure d'un message
struct Message_s
{
    SDL_Rect rectangle;
    SDL_Texture *texture;
};
typedef struct Message_s *_tMessage;

/**
 * @brief Construit un message vide
 * @return le message vide
 */
_tMessage message_vide();

/**
 * @brief Construit un message
 * @param texte texte du message
 * @param texture texture du message
 * @return le message construit
 */
_tMessage consMessage(SDL_Rect texte, SDL_Texture *texture);

/// @brief libére l'espace mémoire allouée au message
/// @param mes message à libérer
void liberer_message(_tMessage *mes);

/**
 * @brief renvoie le rectangle associé au message
 * @param message le message dont on récupère le rectangle
 * @return le rectangle
 */
SDL_Rect *getTexte_pos(_tMessage message);

/**
 * @brief Renvoie la texture associé au message
 * @param message le message dont on récupère la texture
 * @return la texture
 */
SDL_Texture *getTexture(_tMessage message);

/// @brief initialisation des messages
/// @param renderer renderer pour l'affichage
/// @return un tableau contenant les messages
_tMessage* initMessages(SDL_Renderer *renderer);

#endif