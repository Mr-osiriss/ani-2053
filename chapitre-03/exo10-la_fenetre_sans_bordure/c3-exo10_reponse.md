# Exercice 10 : la fenêtre sans bordure

## État de l'exercice : incomplet, en cours de diagnostic

Ce document rapporte des tests réels et n'affirme rien qui n'ait été observé dans le terminal.

## Fenêtre sans bordure

```cpp
NkWindowConfig cfg;
cfg.frame = false;
```

Testé : la fenêtre s'ouvre bien sans barre de titre ni bordure de l'OS (voir capture).

## Ce qui fonctionne, confirmé par un test réel

D'après l'exécution du 28/09, avec compilation réussie (`Build Successful`, 4.57s) et un test de plusieurs secondes sans plantage (`termine normalement`, 72.13s) :

- **Le glisser démarre et se termine** : chaque clic gauche suivi d'un relâchement produit bien un log de début et de fin de