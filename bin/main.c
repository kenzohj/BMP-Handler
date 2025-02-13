/* Directives préprocesseurs permettant d'importer les bibliothèques standards. */
#include <stdio.h>
#include <stdlib.h>

/* Directives préprocesseurs permettant d'importer nos fichiers headers afin d'accéder à nos fonctions. */
#include "console_manager.h"
#include "image_manager.h"

/**
 * @brief la fonction main regroupe les différents moyens d'appels du fichier exécutable, ainsi que les processus à réaliser lors de ces appels.
 *
 * @param argc représente le nombre de paramètres fournis lors de l'appel du fichier exécutable.
 * @param argv représente un tableau de chaines de caractères qui sont les différents arguments fournis par l'utilisateur lors de l'appel du fichier exécutable.
 * @return int - renvoie :
 *              0 si le traitement s’est bien passé,
 *              -1 si le traitement demandé n’existe pas ou s’il ne s’est pas bien déroulé,
 *              -2 si l’un des fichiers fournis n’existe pas ou ne peut être ouvert,
 *              -3 si le fichier de sortie result.bmp ne peut pas être écrit.
 */
int main(int argc, char* argv[])
{
    /* Variable de type caractère qui stock de manière temporaire le traitement à réaliser à(aux) l'(les)image(s). */
    char temp_treatment = 0;

    /* Variable de type entière qui stock le traitement à réaliser. */
    int treatment = 0;

    /* Initalisation des variables de type tableaux de caractères
    qui stockeront de manière temporaire le chemin vers le répertoire de travail,
    le nom du fichier image, ainsi que le nom du second fichier image (si celui-ci existe).
    Cela permettra que les allocations dynamiques vers ces différentes
    chaines de caractères soient de bonne taille. */
    char temp_path[] = {};
    char temp_file_name[] = {};
    char temp_second_file_name[] = {};

    /* Initalisation des variables de type pointeurs de caractère qui stockeront
    les adresses dynamiques des valeurs finales du chemin vers le répertoire de travail,
    du nom du fichier, ainsi que du nom du second fichier (si celui-ci existe). */
    char *path, *file_name, *second_file_name = NULL;

    /* Initialisation des variables de type pointeurs de charactère qui stockeront
    les adresses dynamiques du chemin vers le fichier à traiter ainsi que vers le
    second fichier à traiter (si celui-ci existe). */
    char *file_path, *second_file_path = NULL;

    /* Si le nombre d'arguments donnés est égal à 1, cela signifie qu'aucun argument n'a été renseigné lors de l'appel du fichier executable.
    Il faut alors demander à l'utilisateurs plusieurs informations afin de réaliser le traitement désiré sur l'(les) image(s) souhaitée(s). */
    if(argc == 1)
    {
        /* Affichage du menu d'accueil questionnant l'utilisateur sur le type de traitement qu'il souhaite réaliser. */
        print_welcome_menu();
        /* Récupération de la réponse de l'utilisateur sous forme de caractère. */
        scanf("%c", &temp_treatment);
        /* Conversion du caractère en entier. */
        treatment = atoi(&temp_treatment);

        /* Vérification que la réponse de l'utilisateur soit comprise entre 1 et 5. */
        if(treatment < 1 || treatment > 5)
            /* Renvoie de l'erreur si ce n'est pas le cas. */
            return -1;

        /* Suppression du retour à la ligne engendré par le scanf précédent afin de pouvoir scanner une chaine de caractères par la suite. */
        getchar();

        /* Affichage du menu questionnant l'utilisateur sur le chemin vers son répertoire de travail. */
        print_ask_path_menu();
        /* Récupération de la chaine de caractères entrée par l'utilisateur, stockée alors dans la variable temporaire. */
        gets(temp_path);
        /* Création de l'emplacement mémoire dynamique nécessaire à partir de la variable temporaire afin de stocker cette chaine de caractères. */
        path = strdup(temp_path);

        /* Affichage du menu questionnant l'utilisateur sur le nom du fichier image (.bmp) qu'il souhaite traiter. */
        print_ask_file_name_menu();
        /* Récupération de la chaine de caractères entrée par l'utilisateur, stockée alors dans la variable temporaire. */
        gets(temp_file_name);
        /* Création de l'emplacement mémoire dynamique nécessaire à partir de la variable temporaire afin de stocker cette chaine de caractères. */
        file_name = strdup(temp_file_name);

        /* Création de l'emplacement mémoire dynamique nécessaire à partir de la
        taille du chemin vers le répertoire de travail, de la taille du nom du 
        fichier à traiter ainsi que du caractère de fin de chaîne de caractères (\0). */ 
        file_path = malloc( sizeof(char)*strlen(path) + sizeof(char)*strlen(file_name) + sizeof(char)*1 );
        /* Initialisation de file_path comme étant une chaîne de caractères en ajoutant le caractère de fin '\0'. */
        *file_path = '\0';

        /* Si le chemin vers le répertoire de travail ne se termine pas par un '/', 
        on l'ajoute afin de pouvoir accéder par la suite à(aux) fichier(s) BMP utilisé(s). */
        if(*(path+strlen(path)-1) != '/')
            strcat(path, "/");

        /* Ajout du chemin vers le répertoire de travail à notre variable contenant le chemin vers le fichier BMP à traiter. */
        strcat(file_path, path);

        /* Ajout du nom du fichier à traiter à notre variable contenant le chemin vers le fichier BMP à traiter. */
        strcat(file_path, file_name);

        /* Libération de l'espace mémoire utilisé par le nom du fichier BMP à traiter. */
        free(file_name);

        /* Si le traitement demandé est égal à 5 ... */
        if(treatment == 5)
        {
            /* Affichage du menu questionnant l'utilisateur sur le nom du fichier image (.bmp) qu'il souhaite superposer. */
            print_ask_second_file_name_menu();
             /* Récupération de la chaine de caractères entrée par l'utilisateur, stockée alors dans la variable temporaire. */
            gets(temp_second_file_name);
            /* Création de l'emplacement mémoire dynamique nécessaire à partir de la variable temporaire afin de stocker cette chaine de caractères. */
            second_file_name = strdup(temp_second_file_name);

            /* Création de l'emplacement mémoire dynamique nécessaire à partir de la
            taille du chemin vers le répertoire de travail, de la taille du nom du second 
            fichier à traiter ainsi que du caractère de fin de chaîne de caractères (\0). */ 
            second_file_path = malloc( sizeof(char)*strlen(path) + sizeof(char)*strlen(second_file_name) + sizeof(char)*1 );
            /* Initialisation de file_path comme étant une chaîne de caractères en ajoutant le caractère de fin '\0'. */
            *second_file_path = '\0';

            /* Ajout du chemin vers le répertoire de travail à notre variable contenant le chemin vers le fichier BMP à traiter. */
            strcat(second_file_path, path);

            /* Ajout du nom du second fichier à traiter à notre variable contenant le chemin vers le second fichier BMP à traiter. */
            strcat(second_file_path, second_file_name);

            /* Libération de l'espace mémoire utilisé par le nom du second fichier BMP à traiter. */
            free(second_file_name);
            /* Libération de l'espace mémoire utilisé par le chemin vers le répertoire de travail. */
            free(path);

            /* Renvoie d'une erreur éventuelle de l'application de la superposition d'images souhaitée sur les images fournies situées dans le répertoire de travail founi. */
            return process_images_fusion(file_path, second_file_path);
        }

        /* Libération de l'espace mémoire utilisé par le chemin vers le répertoire de travail. */
        free(path);
        /* Sinon, renvoie d'une erreur éventuelle de l'application du traitement souhaité sur l'image fournie située dans le répertoire de travail founi. */
        return process_image_changes(file_path, treatment);
    }

    /* Si le nombre d'arguments donnés est supérieur à 1, cela signifie
    que les informations nécessaires au traitement du(des) fichier(s) image(s) ont été
    directement fournies par l'utilisateur lors de l'appel du fichier exécutable.

    Les arguments fournis sont alors donnés dans l'ordre suivant:
    chemin vers le répertoire de travail, numéro du traitement à effectuer,
    nom du fichier image à traiter et si il y a lieu, nom du fichier image à superposer.

    strdup permet de copier une chaine de caractères et de l'allouer en mémoire de manière dynamique.
    Cette fonction renvoie également l'adresse en mémoire de la copie de la chaine.

    Récupérations des différents arguments fournis par l'utilisateur à partir du second élément du tableau
    de chaine de caractères 'argv' car le premier élément est le nom du fichier exécutable exécuté. */

    /* Récupération du chemin vers le répertoire de travail fourni en premier argument grâce à la fonction strdup. */
    path = strdup(argv[1]);
    /* Récupération du numéro de traitement à réaliser en le convertissant en entier car les arguments fournis sont des chaines de caractères. */
    treatment = atoi(argv[2]);
    /* Récupération du nom du fichier image (.bmp) à traiter fourni en troisième argument grâce à la fonction strdup. */
    file_name = strdup(argv[3]);

    /* Création de l'emplacement mémoire dynamique nécessaire à partir de la
    taille du chemin vers le répertoire de travail, de la taille du nom du 
    fichier à traiter ainsi que du caractère de fin de chaîne de caractères (\0). */ 
    file_path = malloc( sizeof(char)*strlen(path) + sizeof(char)*strlen(file_name) + sizeof(char)*1 );
    /* Initialisation de file_path comme étant une chaîne de caractères en ajoutant le caractère de fin '\0'. */
    *file_path = '\0';

    /* Si le chemin vers le répertoire de travail ne se termine pas par un '/', 
    on l'ajoute afin de pouvoir accéder par la suite à(aux) fichier(s) BMP utilisé(s). */
    if(*(path+strlen(path)-1) != '/')
        strcat(path, "/");

    /* Ajout du chemin vers le répertoire de travail à notre variable contenant le chemin vers le fichier BMP à traiter. */
    strcat(file_path, path);

    /* Ajout du nom du fichier à traiter à notre variable contenant le chemin vers le fichier BMP à traiter. */
    strcat(file_path, file_name);

    /* Libération de l'espace mémoire utilisé par le nom du fichier BMP à traiter. */
    free(file_name);

    /* Vérification que le traitement soit compris entre 1 et 5. */
    if(treatment < 1 || treatment > 5)
        /* Renvoie de l'erreur si ce n'est pas le cas. */
        return -1;

    /* Si le traitement demandé est égal à 5 ... */
    if(treatment == 5)
    {
        /* Récupération du nom du fichier image (.bmp) à superposer fourni en dernier argument, par la fonction strdup. */
        second_file_name = strdup(argv[4]);

        /* Création de l'emplacement mémoire dynamique nécessaire à partir de la
        taille du chemin vers le répertoire de travail, de la taille du nom du second 
        fichier à traiter ainsi que du caractère de fin de chaîne de caractères (\0). */ 
        second_file_path = malloc( sizeof(char)*strlen(path) + sizeof(char)*strlen(second_file_name) + sizeof(char)*1 );
        /* Initialisation de file_path comme étant une chaîne de caractères en ajoutant le caractère de fin '\0'. */
        *second_file_path = '\0';

        /* Ajout du chemin vers le répertoire de travail à notre variable contenant le chemin vers le fichier BMP à traiter. */
        strcat(second_file_path, path);

        /* Ajout du nom du second fichier à traiter à notre variable contenant le chemin vers le second fichier BMP à traiter. */
        strcat(second_file_path, second_file_name);

        /* Libération de l'espace mémoire utilisé par le nom du second fichier BMP à traiter. */
        free(second_file_name);
        /* Libération de l'espace mémoire utilisé par le chemin vers le répertoire de travail. */
        free(path);

        /* Renvoie d'une erreur éventuelle de l'application de la superposition d'images souhaitée sur les images fournies. */
        return process_images_fusion(file_path, second_file_path);
    }

    /* Libération de l'espace mémoire utilisé par le chemin vers le répertoire de travail. */
    free(path);
    /* Sinon, renvoie d'une erreur éventuelle de l'application du traitement souhaité sur l'image fournie. */
    return process_image_changes(file_path, treatment);
}
