# Exercice 10 : fusionner ou rejouer

## Démarche

1. Création d'une branche `feature-a` avec 2 commits.
2. Pendant ce temps, un commit a été ajouté sur `main`, créant une vraie divergence.
3. Intégration n°1 : fusion classique (`git merge --no-ff`), sur une branche `integration-par-fusion`.
4. Intégration n°2 : rejeu (`git rebase main` sur `feature-a`, puis fast-forward), sur une branche `integration-par-rebase`.
5. Comparaison des deux graphes obtenus avec `git log --oneline --graph --all`.

## Graphe n°1 : par fusion (`merge --no-ff`)

​```
*   bb753f4 (integration-par-fusion) Merge feature-a par fusion
|\  
| * c0809ec (feature-a) feature: etape 2
| * 0f313d8 feature: etape 1
* | acf2e54 (main) main: ajoute un fichier pendant que feature-a avance
|/  
* 0f150a8 (origin/main) Ajoute la réponse de l'exercice 8
​```

## Graphe n°2 : en rejouant (`rebase`)

​```
* 1ec60cc (integration-par-rebase, feature-a) feature: etape 2
* f92426e feature: etape 1
* acf2e54 (main) main: ajoute un fichier pendant que feature-a avance
* 0f150a8 (origin/main) Ajoute la réponse de l'exercice 8
​```

## Comparaison

- **Fusion :** garde une trace fidèle de ce qui s'est réellement passé — deux lignes de travail parallèles, qui se recollent à un instant précis (le commit de merge). Les hash des commits de `feature-a` restent inchangés.
- **Rebase :** réécrit l'historique pour donner l'illusion que `feature-a` a été développée **après** le commit de `main`, en ligne droite. Les commits de `feature-a` ont un **nouveau hash** (`f92426e` et `1ec60cc`, différents de `0f313d8` et `c0809ec`) : ce sont des commits recréés, pas les originaux.

## Ce que je préfère lire, et pourquoi

Je préfère lire le graphe **par rebase**. Il est plus simple : une seule ligne, sans embranchement à interpréter. Pour comprendre l'ordre des changements ou faire un `git bisect`, une ligne droite est plus rapide à parcourir qu'un graphe avec des fourches.

En contrepartie, le rebase cache le fait que le travail a réellement été fait en parallèle : si `feature-a` a mis deux semaines à être développée, l'historique final ne le montre plus, alors que la fusion en garde la trace exacte. Le rebase est donc une meilleure lecture **a posteriori** (plus simple à suivre), mais une moins bonne trace **historique** (moins fidèle à la réalité du travail).

Autre point important : le rebase change les hash des commits. Si `feature-a` avait déjà été poussée et récupérée par quelqu'un d'autre, rebaser casserait son historique local (les hash ne correspondraient plus) — le rebase est donc à réserver aux branches qui n'ont pas encore été partagées.