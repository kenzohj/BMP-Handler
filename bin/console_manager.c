/* Directive préprocesseur permettant d'importer les prototypes des fonctions implémentées. */
#include "console_manager.h"

/**
 * @brief fonction affichant le menu d'accueil questionnant l'utilisateur sur le type de traitement qu'il souhaite réaliser.
 * 
 */
void print_welcome_menu()
{
    printf("\n\n\n");
    printf("|========================================|\n");
    printf("|             MENU PRINCIPAL             |\n");
    printf("|========================================|\n");
    printf("| Bienvenue sur le gestionnaire d'images |\n");
    /* La variable '%c' est remplacée par un 'é' (numéro 130 dans la table ASCII étendue). */
    printf("|             developp%c par:             |\n", 130);
    printf("|        Kenzo, Baptiste, Nicolas        |\n");
    printf("|========================================|\n");
    printf("|  Tappez un nombre compris entre 1 & 5  |\n");
    printf("|    en fonction de l'action que vous    |\n");
    printf("|             desirez faire :            |\n");
    printf("|========================================|\n");
    printf("| 1: Passage en niveau de gris.          |\n");
    printf("| 2: Inversion des couleurs.             |\n");
    printf("| 3: Image monochrome.                   |\n");
    printf("| 4: Extraction de contours.             |\n");
    printf("| 5: Superposition de 2 images.          |\n");
    printf("|========================================|\n");
    printf("Votre choix: ");
}

/**
 * @brief fonction affichant le menu questionnant l'utilisateur sur le chemin vers son répertoire de travail.
 * 
 */
void print_ask_path_menu()
{
    printf("\n\n\n");
    printf("|========================================|\n");
    /* La variable '%c' est remplacée par un 'è' (numéro 138 dans la table ASCII étendue). */
    printf("|  Quel est le chemin d'acc%cs de votre   |\n", 138);
    printf("|          dossier de travail ?          |\n");
    printf("|========================================|\n");
    /* La variable '%c' est remplacée par un 'è' (numéro 138 dans la table ASCII étendue). */
    printf("Chemin d'acc%cs: ", 138);
}

/**
 * @brief fonction affichant le menu questionnant l'utilisateur sur le nom du fichier image (.bmp) qu'il souhaite traiter.
 * 
 */
void print_ask_file_name_menu()
{
    printf("\n\n\n");
    printf("|========================================|\n");
    printf("|      Quel est le nom de de votre       |\n");
    /* La variable '%c' est remplacée par un 'à' (numéro 133 dans la table ASCII étendue). */
    printf("|        fichier .BMP %c traiter ?        |\n", 133);
    printf("|========================================|\n");
    printf("Nom du fichier: ");
}

/**
 * @brief fonction affichant le menu questionnant l'utilisateur sur le nom du fichier image (.bmp) qu'il souhaite superposer.
 * 
 */
void print_ask_second_file_name_menu()
{
    printf("\n\n\n");
    printf("|========================================|\n");
    printf("|      Quel est le nom de de votre       |\n");
    /* La variable '%c' est remplacée par un 'à' (numéro 133 dans la table ASCII étendue). */
    printf("|      fichier .BMP %c superposer ?       |\n", 133);
    printf("|========================================|\n");
    printf("Nom du fichier: ");
}