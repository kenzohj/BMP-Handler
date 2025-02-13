/* Directive préprocesseur permettant d'importer les prototypes des fonctions implémentées. */
#include "image_manager.h"

/* Directives préprocesseurs permettant d'importer les bibliothèques standards. */
#include <stdio.h>
#include <stdlib.h>

/* Déclarations des fonctions locales. */
int init_files(char *file_path);
int init_third_file(char *file_path);
void close_files(void);
int apply_color_modification(int treatment);
int fusion_two_images(void);
int outlines_extraction(void);

/* Initialisation des variables de type pointeurs de caractères qui stockeront les adresses des fichiers utilisés. */
FILE *file = NULL;
FILE *second_file = NULL;
FILE *new_file = NULL;

/* Initialisation d'un tablau de 54 caractères qui stockera le header du fichier BMP à traiter. */
unsigned char header[54] = {0};
/* Initialisation de 3 variables de type entière qui stockeront respectivement
la largeur, la hauteur ainsi que du biais de l'image BMP à traiter. */
int width, height, offset_l = 0;

/**
 * @brief fonction permettant d'initialiser le fichier d'image BMP à traiter ainsi que du fichier BMP résultant le traitement appliqué.
 *
 * @param file_path représente le chemin vers le fichier d'image BMP à traiter.
 * @return int - renvoie :
 *              0 si l'initialisation s'est bien passée,
 *              -2 si le fichier d'image BMP à traiter ne peux pas être ouvert ou lu,
 *              -3 si le fichier de sortie BMP ne peux pas être écrit.
 */
int init_files(char *file_path)
{
    /* Initialisation du pointeur du fichier d'image BMP à traiter. */
    file = fopen(file_path, "r+b");
    /* Initialisation du pointeur du fichier d'image BMP de sortie. */
    new_file = fopen("temp.bmp", "w+b");

    /* Vérification de l'existence et de la possibilité d'ouverture du fichier d'image BMP à traiter. */
    if(file == NULL)
        /* Renvoie de l'erreur si ce n'est pas le cas. */
        return -2;

    /* Vérification de la possibilité d'écriture du fichier d'image BMP de sortie. */
    if(new_file == NULL)
        /* Renvoie de l'erreur si ce n'est pas le cas. */
        return -3;

    /* Copie de l'en-tête de l'image BMP à traiter dans l'image BMP de sortie. */
    fread(header, sizeof(unsigned char), 54, file);
    fwrite(header, sizeof(unsigned char), 54, new_file);

    /* Récupération des dimensions de l'image BMP à traiter... */
    width = header[0x13] * (16*16) + header[0x12]; /* largeur, */
    height = header[0x17] * (16*16) + header[0x16]; /* hauteur. */

    /* Calcul du biais de largeur si besoin. */
    if(offset_l%4 != 0)
        offset_l = width%4;

    /* Revoie 0 si tout s'est bien déroulé. */
    return 0;
}

/**
 * @brief fonction permettant d'initialiser le second fichier d'image BMP à traiter.
 *
 * @param file_path représente le chemin vers le second fichier d'image BMP à traiter.
 * @return int - renvoie :
 *              0 si l'initialisation s'est bien passée,
 *              -2 si le second fichier d'image BMP à traiter ne peux pas être ouvert ou lu.
 */
int init_third_file(char *file_path)
{
    /* Initialisation du pointeur du second fichier d'image BMP à traiter. */
    second_file = fopen(file_path, "r+b");

    /* Vérification de l'existence et de la possibilité d'ouverture du second fichier d'image BMP à traiter. */
    if(second_file == NULL)
        /* Renvoie de l'erreur si ce n'est pas le cas. */
        return -2;

    /* Décallage du pointeur jusqu'au début des données des pixels du second fichier d'image BMP à traiter. */
    fseek(second_file, 54 , SEEK_CUR);

    /* Revoie 0 si tout s'est bien déroulé. */
    return 0;
}

/**
 * @brief fonction permettant de fermer les différents fichiers d'image BMP utilisés.
 *
 */
void close_files(void)
{
    /* Fermeture des fichiers utilisés en mémoire. */
    fclose(file);
    fclose(new_file);

    /* Fermeture du second fichier en mémoire s'il a été utilisé */
    if(second_file != NULL)
        fclose(second_file);
}

/**
 * @brief fonction permettant d'appliquer le traitement 1, 2 ou 3.
 *
 * @param treatment représente le traitement à réaliser.
 * @return int - renvoie :
 *              0 si le traitement s'est bien passé,
 *              -3 s'il est impossible d'écrire dans le fichier d'image BMP de sortie.
 */
int apply_color_modification(int treatment)
{
    /* Déclaration de la variable qui contiendra les valeurs RVB du pixel courant. */
    unsigned char current_pixel[3];
    /* Déclaration de la variable gray_value qui stockera la valeur RVB de repère.  */
    int gray_value;

    /* Boucle imbriquée qui parcourt tous les pixels de l'image. */
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            /* Lecture des valeurs RVB du pixel courant. */
            fread(current_pixel, sizeof(unsigned char), 3, file);

            /* Switch faisait varier les différentes valeurs possibles du traitement à effectuer. */
            switch (treatment)
            {

            /* Traitement 1: Nuances de Gris. */
            case 1:

                /* Moyenne des valeurs RVB du pixel pour obtenir la couleur grise. */
                gray_value = (current_pixel[0] + current_pixel[1] + current_pixel[2]) / 3;

                current_pixel[0] = gray_value; // Valeur bleu du pixel.
                current_pixel[1] = gray_value; // Valeur vert du pixel.
                current_pixel[2] = gray_value; // Valeur rouge du pixel.
                break; /* Pixel suivant... */

            /* Traitement 2: Couleurs Inversées. */
            case 2:
                current_pixel[0] = 255 - current_pixel[0]; // Valeur bleu inversée.
                current_pixel[1] = 255 - current_pixel[1]; // Valeur verte inversée.
                current_pixel[2] = 255 - current_pixel[2]; // Valeur rouge inversée.
                break; /* Pixel suivant... */

            /* Traitement 3: Image Monochrome. */
            case 3:

                /* Moyenne des valeurs RVB du pixel courant. */
                gray_value = (current_pixel[0] + current_pixel[1] + current_pixel[2]) / 3;

                /* Si la moyenne est supérieur à 128... */
                if (gray_value > 128)
                {
                    /* On rend le pixel blanc. */
                    current_pixel[0] = 255; // Valeur bleu du pixel.
                    current_pixel[1] = 255; // Valeur verte du pixel.
                    current_pixel[2] = 255; // Valeur rouge du pixel.
                }
                /* Sinon... */
                else
                {
                    /* On rend le pixel noir. */
                    current_pixel[0] = 0; // Valeur bleu du pixel.
                    current_pixel[1] = 0; // Valeur verte du pixel.
                    current_pixel[2] = 0; // Valeur rouge du pixel.
                }
                break; /* Pixel suivant... */

            /* Si le traitement n'est pas reconu... */
            default:
                /* On renvoie l'erreur correspondante. */
                return -3;
            }
            /* Écriture des valeurs du pixel dans le nouveau fichier. */
            fwrite(current_pixel, sizeof(unsigned char), 3, new_file);
        }
        /* Application de l'offset de largeur. */
        fseek(file, offset_l, SEEK_CUR);
    }

    /* Tout s'est bien déroulé, on renvoie donc 0. */
    return 0;
}

/**
 * @brief fonction permettant de réaliser le traitement d'extraction des contours.
 *
 * @return int - renvoie 0 si tout s'est bien déroulé.
 */
int outlines_extraction(void)
{
    /* Déclaration de la variable qui contiendra les valeurs RVB du pixel courant. */
    unsigned char current_pixel[3];
    /* Déclaration de la variable qui contiendra les valeurs grises. */
    unsigned char second_image_pixel[height][width];

    /* Boucle imbriquée qui parcourt tous les pixels de l'image. */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /* Lecture des valeurs RVB du pixel courant. */
            fread(current_pixel, sizeof(unsigned char), 3, file);

            /* Moyenne des valeurs RVB du pixel pour obtenir la couleur grise. */
            int gris = (current_pixel[0] + current_pixel[1] + current_pixel[2]) / 3;
            /* Application de la couleur grise sur le pixel courant du tableau "second_image_pixel". */
            second_image_pixel[i][j] = gris;
        }

        /* Application de l'offset de largeur. */
        fseek(file, offset_l , SEEK_CUR);
    }

    /* Boucle imbriquée qui parcourt tous les pixels de l'image. */
    for (int i2 = 0; i2 < height; i2++)
    {
        for (int j2 = 0; j2 < width; j2++)
        {
            /* Les pixels sur les bords de l'image sont mis en blanc. */
            if (i2 == 0 || i2 == height-1 || j2 == 0 || j2 == width-1)
            {
                current_pixel[0] = 255; // Valeur bleu du pixel.
                current_pixel[1] = 255; // Valeur vert du pixel.
                current_pixel[2] = 255; // Valeur rouge du pixel.
                /* On remplace les valeurs du pixel courant. */
                fwrite(current_pixel, sizeof(unsigned char), 3, new_file);
            }
            else
            {
                /* Calcul faisant la moyenne des directions tout autour du pixel. */
                int average = sqrt(
                                   pow(second_image_pixel[i2-1][j2-1] - second_image_pixel[i2+1][j2+1],2) +
                                   pow(second_image_pixel[i2][j2-1] - second_image_pixel[i2][j2+1],2)     +
                                   pow(second_image_pixel[i2-1][j2+1] - second_image_pixel[i2+1][j2-1],2) +
                                   pow(second_image_pixel[i2-1][j2] - second_image_pixel[i2+1][j2],2)
                                   );
                /* On compare la valeur obtenue à la valeur repaire pour déterminer si c'est un contour ou non. */
                if (average > 80)
                {
                    /* Pixels Noirs. */
                    current_pixel[0] = 0; // Valeur bleu du pixel.
                    current_pixel[1] = 0; // Valeur vert du pixel.
                    current_pixel[2] = 0; // Valeur rouge du pixel.
                }
                else
                {
                    /* Pixels Blancs. */
                    current_pixel[0] = 255; // Valeur bleu du pixel.
                    current_pixel[1] = 255; // Valeur vert du pixel.
                    current_pixel[2] = 255; // Valeur rouge du pixel.
                }
                /* Écriture des valeurs du pixel dans le nouveau fichier. */
                fwrite(current_pixel, sizeof(unsigned char), 3, new_file);
            }
        }
    }
    /* Tout s'est bien déroulé, on renvoie donc 0. */
    return 0;
}

/**
 * @brief fonction permettant de réaliser le traitement de fusion d'images.
 *
 * @return int - renvoie 0 si tout s'est bien déroulé.
 */
int fusion_two_images(void)
{
    /* Déclaration de la variable qui contiendra les valeurs RVB du pixel courant. */
    unsigned char current_pixel[3];
    /* Déclaration de la variable qui contiendra les valeurs RVB du pixel courant de la seconde image. */
    unsigned char second_file_current_pixel[3];

    /* Boucle imbriquée qui parcourt tous les pixels de l'image. */
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            /* Lecture des pixels des deux images. */
            fread(current_pixel, sizeof(unsigned char), 3, file);
            fread(second_file_current_pixel, sizeof(unsigned char), 3, second_file);

            /* Moyenne des valeurs des pixels des deux images. */
            current_pixel[0] = (current_pixel[0] + second_file_current_pixel[0]) / 2; // Valeur bleu du pixel.
            current_pixel[1] = (current_pixel[1] + second_file_current_pixel[1]) / 2; // Valeur vert du pixel.
            current_pixel[2] = (current_pixel[2] + second_file_current_pixel[2]) / 2; // Valeur rouge du pixel.

            /* Écriture des valeurs du pixel dans le nouveau fichier. */
            fwrite(current_pixel, sizeof(unsigned char), 3, new_file);
        }
        /* Application de l'offset de largeur. */
        fseek(file, offset_l, SEEK_CUR);
    }
    /* Tout s'est bien déroulé, on renvoie donc 0. */
    return 0;
}

/**
 * @brief fonction permettant d'appliquer le traitement souhaité sur l'image fournie.
 *
 * @param file_path représente le chemin vers l'image à traiter.
 * @param treatment représente le traitement à réaliser à l'image.
 * @return int - renvoie :
 *              0 si le traitement s’est bien passé,
 *              -1 si le traitement demandé n’existe pas ou s’il ne s’est pas bien déroulé,
 *              -2 si l’un des fichiers fournis n’existe pas ou ne peut être ouvert,
 *              -3 si le fichier de sortie result.bmp ne peut pas être écrit.
 */
int process_image_changes(char *file_path, int treatment)
{
    /* Déclaration des variables contenant les valeurs de retour des différentes fonctions afin de les traiter. */
    int has_init, return_value;

    /* Initialisation de la variable "has_init" par la valeur de retour de l'initialisation des fichiers. */
    has_init = init_files(file_path);
    /* Si l'initialisation a commis une erreur... */
    if(has_init == -2 || has_init == -3)
        /* On renvoie l'erreur. */
        return has_init;

    /* Si le traitement souhaité est l'extraction des contours... */
    if(treatment == 4)
        /* Initialisation de la variable "return_value" par la valeur de retour de l'application du traitement d'extraction des contours. */
        return_value = outlines_extraction();
    /* Sinon... */
    else
        /* Initialisation de la variable "return_value" par la valeur de retour de l'application du traitement fourni (entre 1, 2 et 3). */
        return_value = apply_color_modification(treatment);

    /* Fermeture des fichiers images. */
    close_files();
    /* Libération de l'espace mémoire occupé par le chemin vers le fichier image. */
    free(file_path);

    /* Suppression du fichier image "result.bmp" temporaire. */
    remove("result.bmp");
    /* Rennomage du fichier image de sortie temporaire en tant que fichier image de sortie final "result.bmp". */
    rename("temp.bmp", "result.bmp");

    /* Renvoie d'une erreur éventuelle lors de l'application du traitement. */
    return return_value;
}

/**
 * @brief fonction permettant d'appliquer le traitement de fusion de 2 images sur les images fournies.
 *
 * @param file_path représente le chemin vers l'image à traiter.
 * @param second_file_path représente le chemin vers la seconde image à traiter.
 * @return int - renvoie :
 *              0 si le traitement s’est bien passé,
 *              -1 si le traitement demandé n’existe pas ou s’il ne s’est pas bien déroulé,
 *              -2 si l’un des fichiers fournis n’existe pas ou ne peut être ouvert,
 *              -3 si le fichier de sortie result.bmp ne peut pas être écrit.
 */
int process_images_fusion(char *file_path, char *second_file_path)
{
    /* Initialisation de la variable "has_init" par la valeur de retour de l'initialisation des fichiers. */
    int has_init = init_files(file_path);
    /* Si l'initialisation a commis une erreur... */
    if(has_init == -2 || has_init == -3)
        /* On renvoie l'erreur. */
        return has_init;

    /* Seconde initialisation de la variable "has_init" par la valeur de retour de l'initialisation du second fichier image. */
    has_init = init_third_file(second_file_path);
    /* Si l'initialisation a commis une erreur... */
    if(has_init == -2)
        /* On renvoie l'erreur. */
        return has_init;

    /* Application de la fusion d'image. */
    fusion_two_images();

    /* Fermeture des fichiers images. */
    close_files();
    /* Libération de l'espace mémoire occupé par le chemin vers le fichier image. */
    free(file_path);
    /* Libération de l'espace mémoire occupé par le chemin vers le second fichier image. */
    free(second_file_path);

    /* Suppression du fichier image "result.bmp" temporaire. */
    remove("result.bmp");
    /* Rennomage du fichier image de sortie temporaire en tant que fichier image de sortie final "result.bmp". */
    rename("temp.bmp", "result.bmp");

    /* Tout s'est bien déroulé, on renvoie donc 0. */
    return 0;
}

