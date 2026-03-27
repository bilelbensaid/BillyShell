# 🐚 BillyShell - Interpréteur de commandes (C / POSIX)

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%2F%20WSL-lightgrey.svg)

**BillyShell** est un interpréteur de commandes (shell) développé en langage C. 
Ce projet a été réalisé afin de mettre en pratique la programmation système sous Linux, la gestion des processus, et la manipulation de la mémoire dynamique. Il démontre des compétences directement applicables au développement de **logiciels embarqués et de firmwares**.

## 🚀 Fonctionnalités

BillyShell gère l'exécution de commandes intégrées (built-ins) ainsi que l'appel aux binaires externes du système.

**Commandes internes (Built-ins) :**
* 📁 **Navigation & Dossiers :** `cd`, `pwd`, `mkdir`, `rmdir`
* 📄 **Gestion de Fichiers :** `mkfile`, `rmfile`, `lire` (cat), `ecrire`, `chmod`
* 💻 **Système :** `echo` (avec redirection `>`), `man` (manuel intégré)

**Commandes externes :**
* Support complet des exécutables systèmes (ex: `ls`, `tree`, `gcc`, `curl`, etc.) via la variable d'environnement `$PATH`.

## 🧠 Architecture & Choix Techniques

Ce projet met en œuvre plusieurs concepts clés de la programmation système et du C :

* **Appels Systèmes POSIX :** Utilisation de `fork()`, `execvp()`, et `waitpid()` pour la création de processus enfants et l'exécution sécurisée des commandes externes.
* **Gestion des descripteurs et métadonnées :** Manipulation directe des droits d'accès avec `chmod()`, `stat()`, et navigation via `dirent.h`.
* **Table de Dispatch (Pointeurs de fonctions) :** Architecture sans structures conditionnelles (if/else) infinies. Les commandes sont gérées dynamiquement via un tableau de structures `t_command` associant des chaînes de caractères à des pointeurs de fonctions.
* **Gestion de la Mémoire :** Parsing des entrées utilisateur (`ft_split`) avec allocations (`malloc`) et libérations (`free`) dynamiques sécurisées pour éviter les fuites de mémoire.

## 🛠️ Compilation et Exécution

### Prérequis
* Un environnement Linux ou WSL (Windows Subsystem for Linux)
* Compilateur `gcc` et l'outil `make` / `cmake`
* La librairie `readline` (`sudo apt install libreadline-dev`)

### Méthode 1 : Avec CMake (Recommandé)
```bash
cmake .
make
./BillyShell
```
### Méthode 2 : avec gcc
```bash
gcc src/*.c -I include -lreadline -o BillyShell
./BillyShell
```

## 📜Licence
Ce projet est distribué sous la licence MIT. Voir le fichier LICENSE pour plus d'informations.


Projet Réalisé par Bilel BEN SAID - Elève-ingénieur en Electronique et Systèmes Embarqués
