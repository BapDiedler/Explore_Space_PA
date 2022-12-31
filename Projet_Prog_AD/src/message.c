#include "../includes/message.h"

/**
 * @brief Construit un message vide
 * @return le message vide
 */
_tMessage message_vide()
{
    return NULL;
}

/**
 * @brief Construit un message
 * @param texte texte du message
 * @param texture texture du message
 * @return le message construit
 */
_tMessage consMessage(SDL_Rect rect, SDL_Texture *text)
{
    _tMessage message;
    /* Réservation de la mémoire nécessaire et désignation d'une adresse */
    message = malloc(sizeof(struct Message_s));
    message->rectangle = rect;
    message->texture = text;
    return message;
}

/// @brief libére l'espace mémoire allouée au message
/// @param mes message à libérer
void liberer_message(_tMessage *mes)
{
    for (int i = 0; i < NB_MESSAGES; i++)
    {
        free(mes[i]);
    }
    free(mes);
}

/**
 * @brief renvoie le rectangle associé au message
 * @param message le message dont on récupère le rectangle
 * @return le rectangle
 */
SDL_Rect *getTexte_pos(_tMessage message)
{
    return &message->rectangle;
}

/**
 * @brief Renvoie la texture associé au message
 * @param message le message dont on récupère la texture
 * @return la texture
 */
SDL_Texture *getTexture(_tMessage message)
{
    return message->texture;
}

/// @brief initialisation des messages
/// @param renderer renderer pour l'affichage
/// @return un tableau contenant les messages
_tMessage * initMessages(SDL_Renderer *renderer)
{

    TTF_Font *font = TTF_OpenFont("ressource/arial.ttf", TAILLE_NOM_FICHIER);
    SDL_Rect text_pos; // Position du texte

    _tMessage * mess = (_tMessage *)calloc(sizeof(_tMessage),NB_MESSAGES);

    // 1er message (message menu)
    char *msg = "MENU";
    SDL_Color color = {255, 255, 255, 0};
    SDL_Texture *texte = charger_texte(msg, renderer, font, color);
    text_pos.y = 0;
    text_pos.w = strlen(msg) * LARGEUR_PAVET / 2;
    text_pos.h = HAUTEUR_PAVET * 2;
    text_pos.x = LARGEUR_FENETRE * LARGEUR_PAVET - text_pos.w - 10;
    mess[0] = consMessage(text_pos, texte);

    // 2ème message (message accueil)
    msg = "ACCUEIL";
    texte = charger_texte(msg, renderer, font, color);
    text_pos.y = HAUTEUR_FENETRE * HAUTEUR_PAVET / 2 - 250;
    text_pos.w = strlen(msg) * LARGEUR_FENETRE;
    text_pos.h = HAUTEUR_PAVET * 2;
    text_pos.x = LARGEUR_FENETRE * LARGEUR_PAVET / 2 - text_pos.w / 2;
    mess[1] = consMessage(text_pos, texte);

    // 3ème message (message vous avez perdu)
    msg = "PERDU";
    texte = charger_texte(msg, renderer, font, color);
    text_pos.y = HAUTEUR_FENETRE * HAUTEUR_PAVET / 2 - 64;
    text_pos.w = strlen(msg) * LARGEUR_FENETRE;
    text_pos.h = HAUTEUR_PAVET * 2;
    text_pos.x = LARGEUR_FENETRE * LARGEUR_PAVET / 2 - text_pos.w / 2;
    mess[2] = consMessage(text_pos, texte);

    // 4ème message (message vous avez gagné)
    msg = "GAGNE";
    texte = charger_texte(msg, renderer, font, color);
    text_pos.y = HAUTEUR_FENETRE * HAUTEUR_PAVET / 2 - 64;
    text_pos.w = strlen(msg) * LARGEUR_FENETRE;
    text_pos.h = HAUTEUR_PAVET * 2;
    text_pos.x = LARGEUR_FENETRE * LARGEUR_PAVET / 2 - text_pos.w / 2;
    mess[3] = consMessage(text_pos, texte);

    // 5ème message (message recommencer)
    msg = "RECOMMENCER";
    texte = charger_texte(msg, renderer, font, color);
    text_pos.y = HAUTEUR_FENETRE * HAUTEUR_PAVET / 2;
    text_pos.w = strlen(msg) * LARGEUR_FENETRE;
    text_pos.h = HAUTEUR_PAVET * 2;
    text_pos.x = LARGEUR_FENETRE * LARGEUR_PAVET / 2 - text_pos.w / 2;
    mess[4] = consMessage(text_pos, texte);

    // 6ème message (message continuer)
    msg = "CONTINUER";
    texte = charger_texte(msg, renderer, font, color);
    text_pos.y = HAUTEUR_FENETRE * HAUTEUR_PAVET / 2 - 100;
    text_pos.w = strlen(msg) * LARGEUR_FENETRE;
    text_pos.h = HAUTEUR_PAVET * 2;
    text_pos.x = LARGEUR_FENETRE * LARGEUR_PAVET / 2 - text_pos.w / 2;
    mess[5] = consMessage(text_pos, texte);

    // 7ème message (message sauvegarder)
    msg = "SAUVEGARDER";
    texte = charger_texte(msg, renderer, font, color);
    text_pos.y = HAUTEUR_FENETRE * HAUTEUR_PAVET / 2 + 100;
    text_pos.w = strlen(msg) * LARGEUR_FENETRE;
    text_pos.h = HAUTEUR_PAVET * 2;
    text_pos.x = LARGEUR_FENETRE * LARGEUR_PAVET / 2 - text_pos.w / 2;
    mess[6] = consMessage(text_pos, texte);

    // 8ème message (message quitter)
    msg = "QUITTER";
    texte = charger_texte(msg, renderer, font, color);
    text_pos.y = HAUTEUR_FENETRE * HAUTEUR_PAVET / 2 + 200;
    text_pos.w = strlen(msg) * LARGEUR_FENETRE;
    text_pos.h = HAUTEUR_PAVET * 2;
    text_pos.x = LARGEUR_FENETRE * LARGEUR_PAVET / 2 - text_pos.w / 2;
    mess[7] = consMessage(text_pos, texte);

    return mess;
}
