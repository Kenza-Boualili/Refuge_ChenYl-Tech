Refuge pour Animaux
Description:
Le projet Refuge pour Animaux consiste à développer un programme permettant de gérer un refuge pour animaux. Il permet aux utilisateurs de consulter les animaux disponibles à l'adoption, d'ajouter de nouveaux animaux, de rechercher un animal spécifique, ainsi que de les adopter ou de les remettre en refuge. Le programme propose aussi une gestion de l'inventaire et des repas des animaux.

Le système permet de gérer différents types d'animaux, de les classifier par espèces, et de suivre leur statut d'adoption ou d'entretien. Le programme s'appuie sur une interface texte et utilise un fichier CSV pour stocker les informations sur les animaux.

Contenu du projet
Ce répertoire contient les fichiers suivants :

README.md : Ce fichier que vous êtes en train de lire.

src/ : Répertoire contenant le code source en C pour la gestion des animaux.

include/ : Répertoire contenant les fichiers d'en-tête pour les fonctions utilisées dans le projet.

bin/ : Répertoire contenant les fichiers compilés.

obj/ : Répertoire contenant les fichiers objets générés lors de la compilation.
Makefile : Fichier de configuration pour la compilation du projet.
data/ : Répertoire contenant les informations sur les animaux. Ce dossier inclut des fichiers CSV avec les données des animaux dans le sous-dossier animaux/.

Installation
Pour installer et exécuter ce projet, suivez ces étapes :
-Télécharger le projet sous format ZIP (Cliquez sur le bouton Code et sélectionnez Download ZIP.)
-extrayez-le dans le répertoire de votre choix sur votre ordinateur
-Une fois le fichier extrait, ouvrez un terminal et accédez au répertoire extrait.
Assurez-vous que le programme est compilé avec les commandes suivantes :
"make clean && make"
Cela va générer les fichiers exécutables nécessaires à l'exécution du programme.

Assurez-vous que les données des animaux sont dans le bon répertoire. Le projet utilise les informations présentes dans le dossier data/animaux/ pour fonctionner correctement. Si vous avez un fichier de données spécifique à ajouter, placez-le dans ce dossier.
Un outil est également disponible pour nettoyer le fichier animaux.txt automatiquement, afin de garantir qu'il reste propre et bien formaté.

Utilisation:
Une fois l'installation terminée et la compilation effectuée, vous pouvez lancer le programme avec la commande suivante :
"./bin/chenil"

Fonctionnalités principales
Le programme vous propose plusieurs options dans un menu interactif. Voici les principales fonctionnalités que vous pouvez utiliser :

Ajouter un animal : Ajouter un nouvel animal à la liste du refuge.

Rechercher un animal : Chercher un animal par son nom, son espèce, ou son statut d'adoption.

Adopter un animal : Adopter un animal du refuge.

Consulter l'inventaire : Visualiser tous les animaux du refuge.

Gérer les repas : Organiser les repas des animaux (s'assurer qu'ils ont suffisamment à manger).
Documentation

La documentation du projet est disponible sous forme de fichiers PDF :
rapport.pdf : Rapport détaillant les résultats du projet, les analyses et les conclusions.

Auteurs:
Boualili Kenza
Eish Shahd
Houch Hadil


