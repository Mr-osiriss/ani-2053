# Compte rendu — Exo 3 : Le module seul (`NKMath`)

J'ai lancé la commande Jenga pour build uniquement `NKMath` et noté l'ordre de compilation des dépendances (du bas vers le haut / racines vers feuilles).

## Arbre de construction (premier construit en bas, `NKMath` en haut)
```text
   [Dépendance / Base requise (compilée en premier - BAS)]
                           │
                           ▼
   NKMath (Sommet - Cible finale compilée en dernier - HAUT)