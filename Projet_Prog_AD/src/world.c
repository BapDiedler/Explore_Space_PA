#include "../includes/world.h"

/// @brief consturcteur liste vide
/// @return une liste vide
liste l_vide()
{
    return NULL;
}

/// @brief constructeur de la liste
/// @param niveau nom du niveau
/// @param L reste de la nouvelle liste
/// @return la nouvelle liste
liste cons(char *level, liste L)
{
    liste M = l_vide();
    /* Réservation de la mémoire nécessaire et désignation d'une adresse */
    M = malloc(sizeof(struct Liste_s));
    M->level = level;
    M->next = L;
    return M;
}

/// @brief vérifie si la liste est vide
/// @param L liste dont on vérifie si elle est vide
/// @return vrai si la liste est vide, faux sinon
bool est_vide(liste L)
{
    return L == NULL;
}

/// @brief libère la mémoire allouée pour la liste
/// @param L la liste à libérer
void liberer_liste(liste L)
{
    while (!est_vide(L->next))
    {
        liste Suivant = L->next;
        free(L);
        L = Suivant;
    }
    free(L);
}

/// @brief donne le reste de la liste
/// @param L liste dont on veut le reste
/// @return le reste de la liste
liste next(liste L)
{
    liste Suivant = L->next;
    free(L);
    L = Suivant;
    return L;
}

/// @brief initialise la liste de niveau
/// @return la liste initialisée
liste initLevels()
{
    liste L = l_vide();
    L = cons("ressource/niveau3.txt", L);
    L = cons("ressource/niveau2.txt", L);
    L = cons("ressource/niveau1.txt", L);
    return L;
}

/**
 * @brief Affiche le nombre de pièce et de vie du joueur
 * @param pavage on a besoin de pavage pour récupérer l'image de pièce et de vie
 * @param chiffres on a besoin des chiffrs pour afficher la quantité de pièce et de vie
 * @param renderer le renderer
 * @param nbPieces le nombre de pièce du joueur
 * @param nbVies le nombre de vie du joueur
 */
void afficheChiffres(_tPavage* pavage, SDL_Texture* chiffres, SDL_Renderer* renderer, int nbPieces, int nbVies){
    // affichage de la pièce
    int tailleW = LARGEUR_PAVET_IMAGE;
    int tailleH = HAUTEUR_PAVET_IMAGE;
    SDL_Rect SrcR_Piece;
    SrcR_Piece.x = tailleW;
    SrcR_Piece.y = 0;
    SrcR_Piece.w = tailleW;
    SrcR_Piece.h = tailleH;
    SDL_Rect DestR_Piece;
    DestR_Piece.x = 10;
    DestR_Piece.y = 10;
    DestR_Piece.w = 30;
    DestR_Piece.h = 30;
    SDL_RenderCopy(renderer,pavage->pavages,&SrcR_Piece,&DestR_Piece);

    // affichage du nombre de pièce
    int tailleChiffresW = LARGEUR_CHIFFRE;
    int tailleChiffresH = HAUTEUR_CHIFFRE;
    SDL_Rect Src_nbPieces;
    Src_nbPieces.x = tailleChiffresW*nbPieces;
    Src_nbPieces.y = 0;
    Src_nbPieces.w = tailleChiffresW;
    Src_nbPieces.h = tailleChiffresH;
    SDL_Rect DestR_nbPieces;
    DestR_nbPieces.x = DestR_Piece.x + DestR_Piece.w;
    DestR_nbPieces.y = DestR_Piece.y;
    DestR_nbPieces.w = DestR_Piece.w;
    DestR_nbPieces.h = DestR_Piece.h;
    SDL_RenderCopy(renderer, chiffres, &Src_nbPieces, &DestR_nbPieces);

    // affichage de la vie
    SDL_Rect SrcR_Vie;
    SrcR_Vie.x = 9*tailleW;
    SrcR_Vie.y = 0;
    SrcR_Vie.w = tailleW;
    SrcR_Vie.h = tailleH;
    SDL_Rect DestR_Vie;
    DestR_Vie.x = DestR_nbPieces.x + 2*DestR_nbPieces.w;
    DestR_Vie.y = DestR_Piece.y;
    DestR_Vie.w = DestR_Piece.w;
    DestR_Vie.h = DestR_Piece.h;
    SDL_RenderCopy(renderer,pavage->pavages,&SrcR_Vie,&DestR_Vie);

    // affichage du nombre de vie
    SDL_Rect Src_nbVies;
    Src_nbVies.x = tailleChiffresW*nbVies;
    Src_nbVies.y = 0;
    Src_nbVies.w = tailleChiffresW;
    Src_nbVies.h = tailleChiffresH;
    SDL_Rect DestR_nbVies;
    DestR_nbVies.x = DestR_Vie.x + DestR_Vie.w;
    DestR_nbVies.y = DestR_Vie.y;
    DestR_nbVies.w = DestR_Vie.w;
    DestR_nbVies.h = DestR_Vie.h;
    SDL_RenderCopy(renderer, chiffres, &Src_nbVies, &DestR_nbVies);
}

/**
 * @brief Initialise le monde et toutes les données qui lui sont associées
 * @param nomFichierAstro nom de la feuille de sprites du personnage
 * @param nomFichierPav nom de la feuille de sprites des blocs
 * @param nomFichierChiffres nom de la feuille de sprite des chiffres
 * @param world le monde que l'on initialise
 * @param renderer le renderer
 * @param nbLignes nombre de lignes dans le niveau
 * @param nbColonnes nombre de colonnes dans le niveau
 * @return vrai si le monde a pu être correctement initialisé, faux sinon
 */
bool initWorld(char *nomFichierAstro, char *nomFichierPav, char *nomFichierChiffres,_tWorld *world, SDL_Renderer *renderer, int *nbLignes, int *nbColonnes)
{
    world->menu = true;      /// le jeu commendce sur le menu
    world->terminer = false; // le jeu commence
    world->list_level = initLevels();
    world->perso = malloc(sizeof(_tAstronaut));
    world->pavages = malloc(sizeof(_tPavage));
    lireImagePlayer(nomFichierAstro, world->perso, renderer);
    lireImagePavage(nomFichierPav, world->pavages, renderer);
    world->chiffres = lireImageChiffres(nomFichierChiffres,renderer);

    initAstraunot(world->perso); // initialisation du personnage
    // Si le fichier de donnée n'existe pas on intialise le jeu par défaut
    FILE *file = NULL;
    file = fopen(FICHIER_DONEE, "r");
    if (file != NULL)
    {
        lire_donnee(file, world);
        world->perso->next_level = false;
        fclose(file);
    }
    if (!taille_fichier(world->list_level->level, nbLignes, nbColonnes))
    {
        return false;
    } // dimension du terrain
    world->tab = lire_fichier(world->list_level->level);
    initPavage(world->pavages, world->tab); // initialisation du pavage
    return true;
}

/// @brief déplacement du personnage vers le bas
/// @param world monde dans lequel on déplace le personnage
/// @param nbLignes nombre de ligne dans le terrain
/// @param nbColonnes nombre de colonnes dans le terrain
/// @return vrai si le déplacement a pu s'effectuer, faux sinon
bool deplacementBas(_tWorld *world, int nbLignes, int nbColonnes)
{
    if (!collisionDown(world->perso, nbLignes) && !collisionBlocDown(world->perso, world->tab, nbLignes, nbColonnes))
    { // gravité du jeu
        world->perso->positionY++;
        world->perso->DestR_sprite.y += HAUTEUR_PAVET;
        if (world->perso->positionY + HAUTEUR_JOUEUR / HAUTEUR_PAVET >= HAUTEUR_FENETRE + world->pavages->posEcranY && !collisionDown(world->perso, nbLignes))
        {
            world->pavages->posEcranY += 1;
            world->perso->DestR_sprite.y -= HAUTEUR_PAVET;
        }
        return true;
    }
    return false;
}

/// @brief déplacement du personnage vers la gauche
/// @param world monde dans lequel on déplace le personnage
/// @param imagePersonnage image du personnage pour le déplacement
/// @param nbLignes nombre de ligne dans le terrain
/// @param nbColonnes nombre de colonnes dans le terrain
void deplacementGauche(_tWorld *world, SDL_Rect *imagePersonnage, int nbLignes, int nbColonnes)
{
    if (!(collisionLeft(world->perso) || collisionBlocRight(world->perso, world->tab, nbLignes, nbColonnes)))
    {
        world->perso->positionX -= SPEED;
        if ((world->perso->DestR_sprite.x + world->perso->DestR_sprite.w / 2) >= LARGEUR_FENETRE * LARGEUR_PAVET / 2)
        { // si le personnage se trouve au milieu de l'écran
            world->perso->DestR_sprite.x -= (SPEED * LARGEUR_PAVET);
        }
        else if (world->pavages->posEcranX != 0)
        {
            world->pavages->posEcranX -= SPEED;
        }
        else
        {
            world->perso->DestR_sprite.x -= (SPEED * LARGEUR_PAVET);
        }
        // changement des images pour le déplacement
        if (imagePersonnage->x == 0)
        {
            *imagePersonnage = world->perso->SrcR_sprite[4];
        }
        else if (imagePersonnage->x == world->perso->SrcR_sprite->w)
        {
            *imagePersonnage = world->perso->SrcR_sprite[5];
        }
        else
        {
            *imagePersonnage = world->perso->SrcR_sprite[3];
        }
    }
}

/// @brief déplacement du personnage vers la droite
/// @param world monde dans lequel on déplace le personnage
/// @param imagePersonnage image du personnage pour le déplacement
/// @param nbLignes nombre de ligne dans le terrain
/// @param nbColonnes nombre de colonnes dans le terrain
void deplacementDroit(_tWorld *world, SDL_Rect *imagePersonnage, int nbLignes, int nbColonnes)
{
    if ((!(collisionRight(world->perso, nbColonnes) || (collisionBlocLeft(world->perso, world->tab, nbLignes, nbColonnes)))) && world->perso->aToucheSol)
    { // en cas de collision
        world->perso->positionX += SPEED;
        if ((world->perso->DestR_sprite.x + world->perso->DestR_sprite.w / 2) < LARGEUR_FENETRE * LARGEUR_PAVET / 2 && world->pavages->posEcranX < nbColonnes - LARGEUR_FENETRE)
        { // si le personnage se trouve au milieu de l'écran
            world->perso->DestR_sprite.x += (SPEED * LARGEUR_PAVET);
        }
        else
        {
            if (world->pavages->posEcranX < nbColonnes - LARGEUR_FENETRE)
                world->pavages->posEcranX += SPEED;
            else
            {
                world->perso->DestR_sprite.x += (SPEED * LARGEUR_PAVET);
            }
        }
        // changement de image pour le déplacement
        if (imagePersonnage->x == 0)
        {
            *imagePersonnage = world->perso->SrcR_sprite[1];
        }
        else if (imagePersonnage->x == world->perso->SrcR_sprite->w)
        {
            *imagePersonnage = world->perso->SrcR_sprite[2];
        }
        else
        {
            *imagePersonnage = world->perso->SrcR_sprite[0];
        }
    }
}

/// @brief fonction qui gère le saut du personnage
/// @param world monde dans lequel le personnage saute
/// @param imagePersonnage image pour faire bouger le personnage
/// @param nbLignes nombre de lignes dans le niveau
/// @param nbColonnes nombre de colonnes dans le niveau
void jump(_tWorld *world, SDL_Rect *imagePersonnage, int nbLignes, int nbColonnes)
{
    if (world->perso->posSaut == 0 && world->perso->saut)
    {
        if (!collisionBlocUp(world->perso, world->tab, nbLignes, nbColonnes))
        {
            for (int i = 0; i < 2; i++)
            {
                if (!collisionBlocUp(world->perso, world->tab, nbLignes, nbColonnes) && !collisionUP(world->perso, 1))
                {
                    world->perso->positionY -= SPEED;
                    world->perso->DestR_sprite.y -= (SPEED * HAUTEUR_PAVET);
                    if (world->perso->positionY + HAUTEUR_JOUEUR / HAUTEUR_PAVET >= HAUTEUR_FENETRE + world->pavages->posEcranY)
                    {
                        world->pavages->posEcranY -= SPEED;
                        world->perso->DestR_sprite.y -= (SPEED * HAUTEUR_PAVET);
                    }
                    if (collisionUP(world->perso, (world->pavages->posEcranY)))
                    {
                        world->pavages->posEcranY -= SPEED;
                        world->perso->DestR_sprite.y += (SPEED * HAUTEUR_PAVET);
                    }
                }
            }
            world->perso->posSaut++;
        }
        else
        {
            world->perso->saut = false;
            world->perso->posSaut = 0;
        }
    }
    else if (world->perso->posSaut == LONGUEUR_SAUT / 2)
    {
        SDL_Delay(10);
        if (imagePersonnage->y == world->perso->SrcR_sprite[0].y)
        { // en cas de collision
            deplacementDroit(world, imagePersonnage, nbLignes, nbColonnes);
        }
        else if (imagePersonnage->y == world->perso->SrcR_sprite[3].y)
        { // en cas de collision
            deplacementGauche(world, imagePersonnage, nbLignes, nbColonnes);
        }
        world->perso->posSaut++;
    }
    else if (world->perso->posSaut == LONGUEUR_SAUT)
    {
        world->perso->saut = false;
        world->perso->posSaut = 0;
        if (imagePersonnage->y == world->perso->SrcR_sprite[0].y)
        { // en cas de collision
            deplacementDroit(world, imagePersonnage, nbLignes, nbColonnes);
        }
        else if (imagePersonnage->y == world->perso->SrcR_sprite[3].y)
        { // en cas de collision
            deplacementGauche(world, imagePersonnage, nbLignes, nbColonnes);
        }
        while (deplacementBas(world, nbLignes, nbColonnes))
            ;
    }
    else
    {
        world->perso->posSaut++;
    }
}

/**
 * @brief Met à jour le niveau
 * @param world le monde
 * @param tailleWp nombre de lignes
 * @param tailleHp nombre de colonnes
 * @return 1 si le monde s'est correcement mis à jour, 0 sinon
 */
int updateNiveau(_tWorld *world, int tailleWp, int tailleHp)
{
    initAstraunot(world->perso); // initialisation du personnage
    if (!taille_fichier(world->list_level->level, &tailleWp, &tailleHp))
    {
        return 0;
    } // dimension du terrain
    world->tab = lire_fichier(world->list_level->level);
    initPavage(world->pavages, world->tab);
    return 1;
}

/**
 * @brief Affiche le monde sur le renderer
 * @param world le monde
 * @param renderer le renderer
 * @param imagePersonnage image courante du personnage
 * @param messages les boutons du jeu
 * @param nbLignes nombre de ligne
 * @param nbColonnes nombre
 * @return 1 si l'affichage s'est fait correctement, 0 sinon
 */
int afficherWorld(_tWorld *world, SDL_Renderer *renderer, SDL_Rect imagePersonnage, _tMessage *messages, int *nbLignes, int *nbColonnes)
{
    SDL_RenderClear(renderer);

    // couleur de fond
    SDL_SetRenderDrawColor(renderer, 25, 0, 50, 0);

    if (!estVivant(world->perso))
    { // seulement si le personnage est mort
        // affichage du message "PERDU"
        SDL_RenderCopy(renderer, getTexture(messages[2]), NULL, getTexte_pos(messages[2]));
        SDL_RenderPresent(renderer);
        SDL_Delay(2000);
        if (!updateNiveau(world, *nbLignes, *nbColonnes))
            return 0;
        world->menu = true;
    }
    else if (world->perso->next_level)
    { // Passage au niveau suivant
        if (!est_vide(world->list_level->next))
        {
            world->perso->aToucheSol = false; // empêche le déplacement pendant la mise en place du personnage
            world->list_level = next(world->list_level);
            taille_fichier(world->list_level->level, nbLignes, nbColonnes);
            if (!updateNiveau(world, *nbLignes, *nbColonnes))
                return 0;
        }
        else
        {
            // affichage du message "GAGNE"
            SDL_RenderCopy(renderer, getTexture(messages[3]), NULL, getTexte_pos(messages[3]));
            SDL_RenderPresent(renderer);
            SDL_Delay(2000);
            world->list_level = initLevels(); // recommence le jeu
            if (!updateNiveau(world, *nbLignes, *nbColonnes))
                return 0;
            taille_fichier(world->list_level->level, nbLignes, nbColonnes);
            world->menu = true;
        }
    }
    else if (!world->menu)
    { // si le personnage est vivant et que l'on n'est pas sur le menu

        if (world->perso->saut)
        { // si le personnage fait un saut
            jump(world, &imagePersonnage, *nbLignes, *nbColonnes);
        }
        else
        { // mis en place de la gravité du jeu
            deplacementBas(world, *nbLignes, *nbColonnes);
            if (collisionBlocDown(world->perso, world->tab, *nbLignes, *nbColonnes))
            {
                world->perso->aToucheSol = true;
            }
            SDL_Delay(10);
        }
        if (collisionDown(world->perso, *nbLignes))
        {
            world->perso->vie = 0;
        }
        // affichage des données du pavage
        afficherPavage(world->pavages, renderer, world->tab, *nbColonnes);

        // affichage du message "MENU"
        SDL_RenderCopy(renderer, getTexture(messages[0]), NULL, getTexte_pos(messages[0]));

        // affichage de l'astraunot
        afficherPlayer(world->perso, renderer, imagePersonnage);

        // affichage des chiffres
        afficheChiffres(world->pavages, world->chiffres, renderer, world->perso->nbPieces, world->perso->vie);

        // on applique le renderer
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    else
    { // si on est sur le menu

        // affichage du texte
        //  Message Accueil
        SDL_RenderCopy(renderer, getTexture(messages[1]), NULL, getTexte_pos(messages[1]));
        // Message Recommencer
        SDL_RenderCopy(renderer, getTexture(messages[4]), NULL, getTexte_pos(messages[4]));
        // Message Continuer
        SDL_RenderCopy(renderer, getTexture(messages[5]), NULL, getTexte_pos(messages[5]));
        // Message Sauvegarger
        SDL_RenderCopy(renderer, getTexture(messages[6]), NULL, getTexte_pos(messages[6]));
        // Message Quitter
        SDL_RenderCopy(renderer, getTexture(messages[7]), NULL, getTexte_pos(messages[7]));

        // on applique le renderer
        SDL_RenderPresent(renderer);
    }
    return 1;
}


/// @brief fonction qui gère les évènements du jeu
/// @param evenements évènements du jeu
/// @param renderer le renderer
/// @param world le monde
/// @param souris souris pour les évènements
/// @param messages messages en lien avec des évènements
/// @param imagePersonnage image du personnage
/// @param nbLignes nombre de lignes dans  le niveau
/// @param nbColonnes nombre de colonnes dans le niveau
void gestionEvent(SDL_Event evenements, SDL_Renderer *renderer, _tWorld *world, SDL_MouseButtonEvent souris,
                  _tMessage *messages, SDL_Rect *imagePersonnage, int nbLignes, int nbColonnes)
{
    SDL_PollEvent(&evenements);
    switch (evenements.type)
    {
    case SDL_QUIT:
        world->terminer = true;
        break;
    case SDL_KEYDOWN:
        if (!world->menu && estVivant(world->perso))
        {
            switch (evenements.key.keysym.sym)
            {
            case SDLK_ESCAPE:
            case SDLK_q:
                world->terminer = true;
                break;

            case SDLK_RIGHT:
                deplacementDroit(world, imagePersonnage, nbLignes, nbColonnes);
                break;
            case SDLK_LEFT:
                deplacementGauche(world, imagePersonnage, nbLignes, nbColonnes);
                break;
            case SDLK_DOWN:
                while (deplacementBas(world, nbLignes, nbColonnes))
                    ;
                break;
            case SDLK_UP:
                if (!world->perso->saut)
                {
                    world->perso->saut ^= true;
                }
                break;
            case SDLK_s:
                // ecrire_fichier(world->list_level->level,world->tab,nbLignes,nbColonnes);
                ecrire_donnee(FICHIER_DONEE, world);
                break;
            case SDLK_SPACE: // passage du jeu vers le menu
                world->menu ^= true;
                break;
            default:
                break;
            }
        }
        else
        {
            switch (evenements.key.keysym.sym)
            {
            case SDLK_SPACE: // passage du menu vers le jeu
                world->menu ^= true;
                break;
            case SDLK_ESCAPE:
            case SDLK_q:
                world->terminer = true;
                break;
            }
        }
        break;
    case SDL_MOUSEBUTTONDOWN: // gestion de la souris pour faire pause et aller au menu
        eventSouris(evenements, world, souris, messages, renderer, nbLignes, nbColonnes);
        break;
    }
}

/// @brief vérifie si une case du menu à été cliquée
/// @param souris la souris
/// @param messages le message sur lequel on a cliqué
/// @return vrai si on a bien cliqué sur le message, faux sinon
bool estClique(SDL_MouseButtonEvent souris, _tMessage messages)
{
    // on regarde si la souris se trouve dans le rectangle du message
    return souris.y > messages->rectangle.y && souris.y <= messages->rectangle.y + messages->rectangle.h && souris.x > messages->rectangle.x && souris.x <= messages->rectangle.x + messages->rectangle.w;
}

/// @brief fonction qui s'occupe des évènements de la souris
/// @param evenements évènement du jeu
/// @param world le monde
/// @param souris souris pour les events
/// @param messages messages liés aux évènements
/// @param renderer le renderer
/// @param nbLignes nombre de lignes dans le niveau
/// @param nbColonnes nombre de colonnes dans le niveau
void eventSouris(SDL_Event evenements, _tWorld *world, SDL_MouseButtonEvent souris, _tMessage *messages, SDL_Renderer *renderer,
                 int nbLignes, int nbColonnes)
{

    SDL_GetMouseState(&souris.x, &souris.y);
    switch (evenements.button.button)
    {
    case SDL_BUTTON_LEFT:
        if (!world->menu)
        { // Sur le jeu
            if (estClique(souris, messages[0]))
            { // Aller sur le menu
                world->menu = true;
            }
        }
        else
        { // Sur le menu
            // Clique sur continuer dans le menu
            if (estClique(souris, messages[5]))
            {
                world->menu ^= true;
            }
            // Clique sur recommencer dans le menu
            if (estClique(souris, messages[4]))
            {
                remove(FICHIER_DONEE);
                world = realloc(world, sizeof(_tWorld)); // On écrase l'espace mémoire alloué à world pour recommencer
                initWorld("ressource/sprite.bmp", "ressource/pavet.bmp", "ressource/numbers.bmp",world, renderer, &nbLignes, &nbColonnes);
                world->menu ^= true;
            }
            // Clique sur sauvegarder dans le menu
            if (estClique(souris, messages[6]))
            {
                ecrire_donnee(FICHIER_DONEE, world);
                world->menu ^= true;
            }
            // Clique sur quitter dans le menu
            if (estClique(souris, messages[7]))
            {
                world->terminer = true;
            }
        }
        break;
    default:
        break;
    }
}

/// @brief écrit les données du personnage et du monde dans un fichier pour les sauvegarder
/// @param nomFichier nom du fichier dans lequel on écrit les données
/// @param world le monde dont on va récupèrer les données
void ecrire_donnee(const char *nomFichier, _tWorld *world)
{
    FILE *fichier = NULL;
    fichier = fopen(nomFichier, "w");
    if (fichier != NULL)
    {
        fprintf(fichier, "%d %d %s", world->perso->vie, world->perso->nbPieces, world->list_level->level);
    }
    fclose(fichier);
}

/// @brief lecture des données dans un fichier pour les récupérer
/// @param donnee fichier dans lequel on a sauvegardé les données du monde et du joueur
/// @param world le monde  dans lequel on récupère les données
void lire_donnee(FILE *donnee, _tWorld *world)
{
    char *l = malloc(sizeof(char) * TAILLE_NOM_FICHIER);
    fscanf(donnee, "%d %d %s", &world->perso->vie, &world->perso->nbPieces, l);
    while (strcmp(world->list_level->level, l) != 0)
    {
        world->list_level = next(world->list_level);
    }
    free(l);
}

/// @brief libère l'espace mémoire attribué au monde
/// @param world le monde dont veut libérer l'espace mémoire associé
/// @param nbL nombre de ligne dans le niveau
void libere_monde(_tWorld *world, int nbL)
{
    liberer_liste(world->list_level);
    desallouer_tab_2D(world->tab, nbL);
    free(world->pavages);
    free(world->perso);
    free(world);
}

/**
 * @brief libère toute l'espace mémoire attribué au jeu
 * @param world le monde
 * @param renderer le renderer
 * @param window la fenêtre
 * @param nbL le nombre de ligne du niveau
 */
void liberer(_tWorld *world, SDL_Renderer *renderer, SDL_Window *window, int nbL)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    libere_monde(world, nbL);
}