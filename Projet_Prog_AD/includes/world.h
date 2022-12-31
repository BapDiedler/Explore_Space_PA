#ifndef WORLD_H
#define WORLD_H

#include "../includes/fonctions_fichiers.h"
#include "../includes/message.h"

#define FICHIER_DONEE "ressource/donnee.txt"
#define LARGEUR_CHIFFRE 24
#define HAUTEUR_CHIFFRE 30

/**
 * @Brief Structure liste, utilisée pour la liste de niveau
 */
typedef struct Liste_s *liste;
struct Liste_s
{
    char *level;
    liste next;
};

/// @brief structure du monde
typedef struct _sWorld
{
    bool menu;
    bool terminer;
    _tAstronaut *perso;
    _tPavage *pavages;
    SDL_Texture* chiffres;
    char **tab;
    liste list_level;
} _tWorld;

/// @brief consturcteur liste vide
/// @return une liste vide
liste l_vide();

/// @brief constructeur de la liste
/// @param niveau nom du niveau
/// @param L reste de la nouvelle liste
/// @return la nouvelle liste
liste cons(char niveau[TAILLE_NOM_FICHIER], liste L);

/// @brief vérifie si la liste est vide
/// @param L liste dont on vérifie si elle est vide
/// @return vrai si la liste est vide, faux sinon
bool est_vide(liste L);

/// @brief donne le reste de la liste
/// @param L liste dont on veut le reste
/// @return le reste de la liste
liste next(liste L);

/// @brief libère la mémoire allouée pour la liste
/// @param L la liste à libérer
void liberer_liste(liste L);

/// @brief initialise la liste de niveau
/// @return la liste initialisée
liste initNiveaux();

/**
 * Affiche le nombre de pièce et de vie du joueur
 * @param pavage on a besoin de pavage pour récupérer l'image de pièce et de vie
 * @param chiffres on a besoin des chiffrs pour afficher la quantité de pièce et de vie
 * @param renderer le renderer
 * @param nbPieces le nombre de pièce du joueur
 * @param nbVies le nombre de vie du joueur
 */
void afficheChiffres(_tPavage* pavage, SDL_Texture* chiffres, SDL_Renderer* renderer, int nbPieces, int nbVies);

/**
 * Initialise le monde et toutes les données qui lui sont associées
 * @param nomFichierAstro nom de la feuille de sprites du personnage
 * @param nomFichierPav nom de la feuille de sprites des blocs
 * @param nomFichierChiffres nom de la feuille de sprite des chiffres
 * @param world le monde que l'on initialise
 * @param renderer le renderer
 * @param nbLignes nombre de lignes dans le niveau
 * @param nbColonnes nombre de colonnes dans le niveau
 * @return vrai si le monde a pu être correctement initialisé, faux sinon
 */
bool initWorld(char *nomFichierAstro, char *nomFichierPav, char *nomFichierChiffres,_tWorld *world, SDL_Renderer *renderer, int *nbLignes, int *nbColonnes);

/// @brief déplacement du personnage vers le bas
/// @param world monde dans lequel on déplace le personnage
/// @param nbLignes nombre de ligne dans le terrain
/// @param nbColonnes nombre de colonnes dans le terrain
/// @return vrai si le déplacement a pu s'effectuer, faux sinon
bool deplacementBas(_tWorld *world, int nbLignes, int nbColonnes);

/// @brief déplacement du personnage vers la gauche
/// @param world monde dans lequel on déplace le personnage
/// @param imagePersonnage image du personnage pour le déplacement
/// @param nbLignes nombre de lignes dans le terrain
/// @param nbColonnes nombre de colonnes dans le terrain
void deplacementGauche(_tWorld *world, SDL_Rect *imagePersonnage, int nbLignes, int nbColonnes);

/// @brief déplacement du personnage vers la droite
/// @param world monde dans lequel on déplace le personnage
/// @param imagePersonnage image du personnage pour le déplacement
/// @param nbLignes nombre de lignes dans le terrain
/// @param nbColonnes nombre de colonnes dans le terrain
void deplacementDroit(_tWorld *world, SDL_Rect *imagePersonnage, int nbLignes, int nbColonnes);

/// @brief fonction qui gère le saut du personnage
/// @param world monde dans lequel le personnage saute
/// @param imagePersonnage image pour faire bouger le personnage
/// @param nbLignes nombre de lignes dans le niveau
/// @param nbColonnes nombre de colonnes dans le niveau
void jump(_tWorld *world, SDL_Rect *imagePersonnage, int nbLignes, int nbColonnes);

/**
 * Affiche le monde
 * @param world le monde
 * @param renderer le renderer
 * @param imagePersonnage image courante du personnage
 * @param messages les boutons du jeu
 * @param nbLignes nombre de ligne
 * @param nbColonnes nombre
 * @return 1 si l'affichage s'est fait correctement, 0 sinon
 */
int afficherWorld(_tWorld *world, SDL_Renderer *renderer, SDL_Rect imagePersonnage, _tMessage *messages,
                  int *nbLignes, int *nbColonnes);

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
                  _tMessage *messages, SDL_Rect *imagePersonnage, int nbLignes, int nbColonnes);

/// @brief vérifie si une case du menu à été cliquée
/// @param souris la souris
/// @param messages le message sur lequel on a cliqué
/// @return vrai si on a bien cliqué sur le message, faux sinon
bool estClique(SDL_MouseButtonEvent souris, _tMessage messages);

/// @brief fonction qui s'occupe des évènements de la souris
/// @param evenements évènement du jeu
/// @param world le monde
/// @param souris souris pour les events
/// @param messages messages liés aux évènements
/// @param renderer le renderer
/// @param nbLignes nombre de lignes dans le niveau
/// @param nbColonnes nombre de colonnes dans le niveau
void eventSouris(SDL_Event evenements, _tWorld *world, SDL_MouseButtonEvent souris, _tMessage *messages, SDL_Renderer *renderer,
                 int nbLignes, int nbColonnes);

/**
 * Met à jour le niveau
 * @param world le monde
 * @param tailleWp nombre de lignes
 * @param tailleHp nombre de colonnes
 * @return 1 si le monde s'est correcement mis à jour, 0 sinon
 */
int updateNiveau(_tWorld *world, int tailleWp, int tailleHp);

/// @brief écrit les données du personnage et du monde dans un fichier pour les sauvegarder
/// @param nomFichier nom du fichier dans lequel on écrit les données
/// @param world le monde dont on va récupèrer les données
void ecrire_donnee(const char *nomFichier, _tWorld *world);

/// @brief lecture des données dans un fichier pour les récupérer
/// @param donnee fichier dans lequel on a sauvegardé les données du monde et du joueur
/// @param world le monde  dans lequel on récupère les données
void lire_donnee(FILE *donnee, _tWorld *world);

/// @brief libère l'espace mémoire attribué au monde
/// @param world le monde dont veut libérer l'espace mémoire associé
/// @param nbL nombre de ligne dans le niveau
void libere_monde(_tWorld *world, int nbL);

/**
 * @brief libère toute l'espace mémoire attribué au jeu
 * @param world le monde
 * @param renderer le renderer
 * @param window la fenêtre
 * @param nbL le nombre de ligne du niveau
 */
void liberer(_tWorld *world, SDL_Renderer *renderer, SDL_Window *window, int nbL);

#endif