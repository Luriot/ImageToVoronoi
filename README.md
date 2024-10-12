
# Voronoi Image Approximation Project

## Description

Ce projet est une implémentation en C++ d'un algorithme de création de diagrammes de Voronoi pour approximer une image. Le projet utilise différents algorithmes de distance pour calculer les régions de Voronoi à partir de germes aléatoires.

### Fonctionnalités

- Calcul et affichage d'un diagramme de Voronoi basé sur des germes aléatoires.
- Approximation d'une image en utilisant les couleurs moyennes de chaque région de Voronoi.
- Support de plusieurs algorithmes de distance : 
  - Euclidienne (par défaut)
  - Manhattan
  - Chebyshev

## Fichiers

- `voronoi.cpp` : Fichier source C++ contenant tout le code pour générer le diagramme de Voronoi et approximer une image.

## Prérequis

- OpenCV 4.8.0 (ou version compatible)
- Un compilateur C++ (comme GCC ou Clang)

## Compilation et exécution

### Via ligne de commande (Linux / macOS / Windows avec MinGW)

1. **Cloner le dépôt :**
   ```bash
   git clone https://github.com/Luriot/ImageToVoronoi.git
   cd VoronoiImageApproximation
   ```

2. **Compiler le projet :**
   Assurez-vous d'avoir installé OpenCV sur votre machine. Utilisez la commande suivante pour compiler :
   ```bash
   g++ voronoi.cpp -o voronoi -lopencv_core -lopencv_highgui -lopencv_imgproc
   ```

3. **Exécuter le programme :**
   Placez une image dans le dossier `images` avec le nom `in.png` ou modifiez le chemin dans le fichier source.
   ```bash
   ./voronoi
   ```

### Optionnel : Utilisation avec Visual Studio

Si vous utilisez Visual Studio pour votre projet, vous pouvez facilement créer un projet et y inclure le fichier `voronoi.cpp` :

1. Ouvrez Visual Studio et créez un **Nouveau Projet**.
2. Sélectionnez un projet **Console App** (Application Console).
3. Ajoutez `voronoi.cpp` à votre projet.
4. Configurez les chemins d'inclusion et les bibliothèques pour OpenCV dans les paramètres du projet.
5. Compilez et exécutez directement dans Visual Studio.

## Utilisation

- Modifiez les paramètres dans le fichier `voronoi.cpp` pour ajuster le nombre de germes ou changer le type de distance à utiliser.
- L'image d'entrée doit être placée dans le dossier `images` sous le nom `in.png`.
- Le résultat est sauvegardé dans `out.png` dans le même dossier.

## Algorithmes de distance disponibles

1. **Euclidienne** : Distance classique entre deux points dans un espace 2D. (par défaut)
2. **Manhattan** : Distance parcourue en suivant une grille (somme des distances horizontales et verticales).
3. **Chebyshev** : Plus grande différence entre les coordonnées x ou y des deux points.

## Licence

Ce projet est sous licence MIT. Voir le fichier [LICENSE](LICENSE) pour plus d'informations.

## Auteur

Développé par [Luriot](https://github.com/Luriot).
