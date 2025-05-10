
# 🐾 Refuge pour Animaux

## 📘 Description

Le projet **Refuge pour Animaux** est une application en C qui permet de gérer un refuge. Il offre une interface en ligne de commande permettant :

- d'ajouter de nouveaux animaux,
- de consulter la liste des animaux présents,
- de rechercher des animaux par divers critères,
- d'organiser leur adoption,
- de gérer leur nourriture et l'inventaire du refuge.

Les données sont stockées dans des fichiers CSV (séparateur `;`) et organisées dans le dossier `data/`.

---

## 📁 Structure du projet

```
.
├── README.md              <- Ce fichier
├── Makefile               <- Script de compilation
├── src/                   <- Fichiers sources (.c)
├── include/               <- Fichiers d'en-tête (.h)
├── obj/                   <- Fichiers objets générés
├── bin/                   <- Fichier exécutable `chenil`
└── data/
    └── animaux/           <- Fichier `animaux.txt`
```

---

## 🛠️ Installation

1. **Télécharger le projet** :
   - Cliquez sur le bouton vert `Code` puis `Download ZIP`.
   - Extraire le dossier dans l’emplacement de votre choix.

2. **Ouvrir un terminal** :
   - Placez-vous dans le dossier du projet.

3. **Compiler le programme** :
   ```bash
   make clean
   make
   ```

4. **(Optionnel) Réinitialiser le fichier de données** :
   ```bash
   make cleanfile
   ```

---

## ▶️ Lancement du programme

Après compilation, vous pouvez lancer le programme avec :

```bash
./bin/chenil
```

---

## 🎯 Fonctionnalités

- 🔹 **Ajouter un animal** : Ajout avec vérifications des entrées et des limites du refuge (50 maximum).
- 🔍 **Rechercher un animal** : Par ID, nom ou année de naissance.
- 🐕 **Adopter un animal** : Supprime l’animal de la liste.
- 📦 **Inventaire** : Affiche tous les animaux actuellement au refuge.
- 🍽️ **Gérer les repas** : Donne les quantités de croquettes par espèce.
- 🧹 **Nettoyeur** : Nettoie les fichiers de données invalides ou corrompus.

---

## 📚 Documentation

- `rapport.pdf` : Rapport détaillé du projet (structure, implémentation, résultats).

---

## 👥 Auteurs

- Boualili Kenza  
- Eish Shahd  
- Houch Hadil

---

## 📄 Licence

Projet réalisé dans le cadre du cours d'informatique. Usage académique uniquement.


