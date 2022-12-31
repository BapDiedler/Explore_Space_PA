#include "../includes/fonctions_fichiers.h"

/**
 * @brief allouer un tableau de caractères de
taille n × m, où n et m sont les nombres de lignes et de colonnes, et initialiser
ce tableau avec le caractère espace (’ ’)
 *
 * @param n nb lignes
 * @param m nb colonnes
 * @return char** la matrice
 */
char ** allouer_tab_2D(int n, int m)
{
    char** tab = (char **)calloc(sizeof(char *) ,n);
    for (int i = 0; i < n; i++)
    {
        tab[i] = (char *)calloc(sizeof(char) ,m);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            tab[i][j] = ' ';
        }
    }
    return tab;
}

/**
 * @brief libére un tableau à deux
dimensions
 *
 * @param tab le tableau à libérer
 * @param n nb lignes
 */
void desallouer_tab_2D(char **tab, int n)
{
    for (int i = 0; i < n; i++)
        free(tab[i]);
    free(tab);
}

/**
 * @brief affiche le contenu d’un
tableau de caractères de taille n × m
 *
 * @param tab le tableau que l'on veut afficher
 * @param n nb lignes
 * @param m nb colonnes
 */
void afficher_tab_2D(char **tab, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%c ", tab[i][j]);
        // Saute de ligne pour le passage à la prochaine ligne
        printf("\n");
    }
}

/**
 * @brief compte le nombre max de lignes (nbLig) et de colonnes (nbCol) dans le fichier
dont le nom est nomFichier.
 *
 * @param nomFichier nom du fichier dont on veut la taille
 * @param nbLig nb lignes
 * @param nbCol nb colonnes
 * @return vrai si le taille du fichier est correcte, faux sinon
 */
bool taille_fichier(const char *nomFichier, int *nbLig, int *nbCol)
{
    FILE *fichier = NULL;
    fichier = fopen(nomFichier, "r");
    int c;
    *nbLig = 0;
    *nbCol = 0;
    int colMax = 0;
    int nCol = 0;
    if (fichier != NULL)
    {
        do
        {
            c = fgetc(fichier);
            if (c == '\n' || c == '\r' || c == EOF)
            {
                if (c != EOF)
                {
                    (*nbLig)++;
                }
                if (nCol > colMax)
                {
                    colMax = nCol;
                }
                nCol = 0;
            }
            else
            {
                nCol++;
            }

        } while (c != EOF);
        *nbCol = colMax;
        (*nbLig)++;
        fclose(fichier);
        if(*nbCol<LARGEUR_FENETRE || *nbLig<HAUTEUR_FENETRE){
            return false;
        }
        return true;
    }
    return false;
}

/**
 * @brief lire un fichier dont le nom
est nomFichier, et retourner le tableau qui contient les caractères du fichier
tel qu’une ligne du tableau correspond à une ligne du fichier.
 *
 * @param nomFichier le nom du fichier
 * @return char** la matrice correspondante
 */
char **lire_fichier(const char *nomFichier)
{
    int lignes;
    int colonnes;
    FILE *fichier = NULL;
    fichier = fopen(nomFichier, "r");
    taille_fichier(nomFichier, &lignes, &colonnes);
    char** tab = allouer_tab_2D(lignes, colonnes);
    int lig = 0, col = 0;
    char c;
    if (fichier != NULL)
    {
        do
        {
            c = fgetc(fichier);
            if (c == '\n' || c == '\r' || c == EOF)
            {
                lig++;
                col = 0;
            }
            else
            {
                tab[lig][col] = c;
                col++;
            }

        } while (c != EOF);
        fclose(fichier);
    }
    return tab;
}

/**
 * Retourner un nouveau tableau, dans lequel toutes les occurrences du
 * caractère ancien sont remplacées par le caractère nouveau
 * @param char** tab le tableau sur lequel on se base pour faire le nouveau tableau modifié
 * @param int n le nombre de lignes
 * @param int m le nombre de colonnes
 * @param char ancien le caractère que l'on veut modifier
 * @param char nouveau le caractère par lequel on veut modifier le tableau
 * @return char** le nouveau tableau modifié
 */
char **modifier_caractere(char **tab, int n, int m, char ancien, char nouveau)
{
    char **new_tab = tab;
    if (tab != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (new_tab[i][j] == ancien)
                    new_tab[i][j] = nouveau;
            }
        }
    }
    return new_tab;
}

/**
 * Écrire le tableau tab de taille n × m dans un fichier dont le nom est nomFichier
 * @param const char* nomFichier le nom du fichier dans lequel on écrit le tableau
 * @param char** tab le tabeau qui sera écrit dans le fichier
 * @param int n le nombre de lignes
 * @param int m le nombre de colonnes
 */
void ecrire_fichier(const char *nomFichier, char **tab, int n, int m)
{
    FILE *fichier = NULL;
    fichier = fopen(nomFichier, "w");
    if (fichier != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                fputc(tab[i][j], fichier);
            }
            fprintf(fichier, "\r");
        }
        fclose(fichier);
    }
}