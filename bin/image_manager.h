/* Directive préprocesseur permettant de définir le fichier courant de manière
à ce qu'il ne soit inclut qu'une seule fois dans une seule compilation. */
#pragma once

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
int process_image_changes(char *file_path, int treatment);

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
int process_images_fusion(char *file_path, char *second_file_path);
