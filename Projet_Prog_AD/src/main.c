#include "../includes/world.h"

//___MAIN_PART___
int main(void)
{

    SDL_Event evenements;        // Événements liés à la fenêtre
    SDL_MouseButtonEvent souris; // gestion de la souris

    //création de la fenêtre
    SDL_Window *window = SDL_CreateWindow("Terrain", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_FENETRE * LARGEUR_PAVET, HAUTEUR_FENETRE * HAUTEUR_PAVET, SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    { // En cas d’erreur
        printf("\033[00;31mErreur de la creation d’une fenetre: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    //création du renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    { // En cas d’erreur
        printf("\033[00;31mErreur de la creation du renderer: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // initialisation du monde
    int nbLignes;         // nombre de ligne dans le terrain
    int nbColonnes;       // nombre de colonnes dans le terrain
    _tWorld *world = malloc(sizeof(_tWorld));
    if(!initWorld("ressource/sprite.bmp", "ressource/pavet.bmp", "ressource/numbers.bmp",world, renderer, &nbLignes, &nbColonnes)){
        printf("\033[00;31mfichier d'entrer est invalide car les dimensions sont de minimum %dx%d\n",LARGEUR_FENETRE,HAUTEUR_FENETRE);
        return EXIT_FAILURE;
    }

    SDL_Rect imagePersonnage = world->perso->SrcR_sprite[0]; // image de départ du personnage;*

    // initialise les messages
    TTF_Init();
    _tMessage *messages = initMessages(renderer);

    // Boucle principale
    while (!world->terminer)
    {
        // affichage des image su la fenêtre
        if(!afficherWorld(world, renderer, imagePersonnage, messages, &nbLignes, &nbColonnes)){
            printf("\033[00;31mfichier d'entrer est invalide car les dimensions sont de minimum %dx%d\n",LARGEUR_FENETRE,HAUTEUR_FENETRE);
            return EXIT_FAILURE;
        }

        // gestion des evenements
        gestionEvent(evenements, renderer, world, souris, messages, &imagePersonnage, nbLignes, nbColonnes);
    }
    // Quitter SDL
    liberer(world, renderer, window, nbLignes);
    liberer_message(messages);
    // Fermer la police et quitter SDL_ttf
    SDL_Quit();

    return EXIT_SUCCESS;
}