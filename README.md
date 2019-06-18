# Travail pratique 1

## Description

Ce projet, consiste à coder en langage C un programme qui permet de faire 
le décodage ou l'encodage d'un message. On s'est basé sur une ancienne méthode
qui se nomme César et qui date depuis le temps des Romains. 

Construction et maintenance de logiciel, INF3135, Université du Québec à Montréal

## Auteur

Mohamed Chaouki (CHAM27088802)

## Fonctionnement
   
Ce projet permet de lancer un programme coder en langage C à partir
de la ligne de commande afin de nous faire le décodage ou l'encodage
d'un message. Ces derniers se font en utilisant une clé simple.
La clé est soit un nombre positif ou un nombre négatif. Il faut utiliser
la clé afin de faire bouger les alphabets pour obtenir un message clair.
Le message est soit une phrase claire en français ou bien crypté.

les options facultatives sont : ```-i``` (donner le nom du fichier d'entrée) ```-a``` (le chemin du fichier alphabet)```-o``` (le fichier de sortie)
les options obligatoires sont : ```-k``` (la clé) ```-d``` | ```-e``` (decoder ou encoder) ```-c``` (code permanent)

exemple1 :``` ./tp1 -i message.txt -k 2 -e -a alphabet.txt -c ABCD12345678 -o sortie.txt``` 

exemple2: ```./tp1 < message.txt -k 2 -e -a alphabet.txt -c ABCD12345678 > sortie.txt ```
## Contenu du projet

Ce projet contient les fichiers suivants:

- Un fichier cp.txt contient mon code permanent en majuscule.
- Un fichier tp1.c contient le code source du projet, ainsi que la fonction main.
- Un fichier README.md contient tout le contenu du projet.
- Un fichier Makefile pour les fonctions suivantes: make, make clean, make data, make test et make resultat;
- Un fichier .gitignore qui contient les fichiers intentionnellement non suivis que Git doit ignorer.

## Références
Ce sit m'a beaucoup aide afin de comprendre plusieurs choses sur le langage C https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c   

## Statut

Tout mon programme marche bien sauf pour les``` <``` ``` >``` j'ai pas su comment bien utiliser le stdin et stdout. pour que mon programme marche faut faire le ```-i``` et ```-o``` et non pas ```<```
 et``` >```
