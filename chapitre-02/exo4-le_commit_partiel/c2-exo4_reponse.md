# Exercice 4 : le commit partiel

## Ce qui a été fait

J'ai modifié deux sections sans rapport dans le même fichier `c2-exo4_reponse.md` :
- **Section A** (recette) : ajout d'une précision sur le sel
- **Section B** (liste de courses) : ajout du beurre

Ces deux modifications ont été séparées en deux commits distincts grâce à `git add -p`.

## Commande utilisée

​```
git add -p c2-exo4_reponse.md
​```

Comme les deux changements étaient proches dans le fichier, Git les a d'abord regroupés en un seul hunk. J'ai tapé `s` (split) pour les découper en deux hunks séparés, puis :
- `y` pour accepter le hunk de la Section A (le sel)
- `n` pour refuser (temporairement) le hunk de la Section B (le beurre)

## Historique obtenu

​```
c37c8cc (HEAD -> main) Ajoute le beurre a la liste de courses (Section B)
f14515c Ajoute une precision sur le sel dans la recette (Section A)
fc9e137 Ajoute le fichier reponse exo4 (base)
​```

## Vérification

Chaque commit ne contient qu'un seul sujet :
- `f14515c` ne modifie que la Section A (ajout de la ligne sur le sel)
- `c37c8cc` ne modifie que la Section B (ajout de la ligne "Beurre")

## Ce que ça montre

`git add -p` permet de choisir précisément **quelles lignes** ajouter à la zone de staging, même à l'intérieur d'un seul fichier modifié en plusieurs endroits. Ça permet de garder un historique propre, avec des commits atomiques (un seul sujet chacun), même quand on a travaillé sur plusieurs choses en parallèle avant de les committer.