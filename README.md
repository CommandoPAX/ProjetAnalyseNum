# Simulation d'un double pendule par Théo Bruant L3-Magistère

## Features supportées
- Simulation d'un pendule simple
- Simulation d'un double pendule

## Compilation et execution du programme

Ce programme n'a été testé que sous Linux, la compilation de celui-ci sur Windows ou MacOS n'est pas assurée. 
Un makefile a été fourni avec le programme pour aider à la compilation. Il contient 3 instructions :
- make : compile le programme
- clean : efface tout les fichiers générés par le makefile
- fclean : efface tout les fichiers .o générés par le makefile

Pour executer le programme, il vous suffit d'executer scenario.bash. Ce dernier va générer deux dossiers : DATA et GRAPHES dans lesquels seront stockés les données brutes ainsi que les graphiques générés par le programme pour chaque set de donnée initiale défini dans multi_init.

scenario.bash accepte 5 arguments dont un optionnel : 
- Iter (int) : le nombre d'itérations que doit effectuer DoublePendulum pour chaque simulation (défaut : 100)
- DT (float) : le pas de temps utilisé dans la méthode de résolution RK4 (défaut : 0.1)
- TH1CST (int) : définit si la vitesse du premier pendule doit être considéré constante (True = 1, False = 0)
- TH2CST (int) : définit si la vitesse du second pendule doit être considéré constante (True = 1, False = 0)
- INIT_FILE (string, optionnel) : définit les paramètres de départ du pendule, il est conseillée d'utiliser le fichier multi init et de ne pas modifier cet argument.
