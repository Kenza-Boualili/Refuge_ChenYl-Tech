#ifndef ID_H           // Si la constante ID_H n'est pas définie,
                       // cela signifie que ce fichier n'a pas été inclus précédemment.

#define ID_H           // On définit ID_H pour éviter les inclusions multiples.
                       // Le compilateur ignorera ce code si ID_H est déjà défini.

int genererID();       // Déclaration de la fonction genererID.
                       // - 'int' : retourne un identifiant entier.
                       // - '()' : ne prend aucun paramètre.
                    

#endif                // Fin de la condition #ifndef. Tout le code entre #ifndef et #endif
                       // est protégé contre les inclusions multiples.