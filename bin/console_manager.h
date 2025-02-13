/* Directive préprocesseur permettant de définir le fichier courant de manière 
à ce qu'il ne soit inclut qu'une seule fois dans une seule compilation. */
#pragma once

/**
 * @brief procédure affichant le menu d'accueil questionnant l'utilisateur sur le type de traitement qu'il souhaite réaliser.
 * 
 */
void print_welcome_menu();

/**
 * @brief procédure affichant le menu questionnant l'utilisateur sur le chemin vers son répertoire de travail.
 * 
 */
void print_ask_path_menu();

/**
 * @brief procédure affichant le menu questionnant l'utilisateur sur le nom du fichier image (.bmp) qu'il souhaite traiter.
 * 
 */
void print_ask_file_name_menu();

/**
 * @brief procédure affichant le menu questionnant l'utilisateur sur le nom du fichier image (.bmp) qu'il souhaite superposer.
 * 
 */
void print_ask_second_file_name_menu();
