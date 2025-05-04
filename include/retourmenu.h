#ifndef RETOURMENU_H             // Si RETOURMENU_H n'est pas défini,
                                 // on active le code jusqu'à #endif

#define RETOURMENU_H             // Définit RETOURMENU_H pour bloquer 
                                 // les inclusions futures de ce fichier

#include <stdio.h>               // Inclusion de la bibliothèque stdio.h
                                 // nécessaire pour FILE*, stdin, ou printf/scanf

int demanderRetourMenu();        // Déclaration de la fonction :
                                 // Rôle : Demande à l'utilisateur s'il veut retourner au menu

#endif           // Fin du bloc conditionnel 