# Démonstration 3 : ce que le reflog sauve

## Démarche

1. Construction d'un travail réel : deux commits successifs sur `travail.md`.
2. Destruction volontaire de ce travail avec `git reset --hard HEAD~2`.
3. Constat de la perte : les commits n'apparaissent plus dans `git log`, même avec `--all`.
4. Récupération du travail via `git reflog`.

## Le travail construit

​```
5f58963 Ajoute une partie importante du travail (2)
3a6ecd9 Ajoute une partie importante du travail (1)
​```

## La destruction

​```
git reset --hard HEAD~2
​```

Résultat : `git log` remonte directement au commit précédent, les deux commits ci-dessus ont disparu. Le fichier `travail.md` est revenu à sa version initiale, sans les deux ajouts.

## Le constat de la perte

​```
git log --oneline --all
​```

Même en demandant **toutes** les branches (`--all`), les commits `5f58963` et `3a6ecd9` n'apparaissent nulle part. Ils semblent réellement perdus.

## La récupération

​```
git reflog
​```

Extrait pertinent :
​```
b134b59 (HEAD -> main, origin/main) HEAD@{0}: reset: moving to HEAD~2
5f58963 HEAD@{1}: commit: Ajoute une partie importante du travail (2)
3a6ecd9 HEAD@{2}: commit: Ajoute une partie importante du travail (1)
​```

Les deux commits sont bien listés, avec leurs hash intacts.

​```
git reset --hard 5f58963
​```

Comme `5f58963` est le commit le plus récent des deux (il descend de `3a6ecd9`), ce seul `reset --hard` suffit à ramener **les deux commits d'un coup**, avec leurs hash d'origine inchangés.

## Ce que ça montre

`git reset --hard` ne supprime pas réellement les commits de la base de données Git : il déplace seulement le pointeur `HEAD` (et la branche courante) ailleurs. Les anciens commits restent des objets valides sur le disque, simplement plus atteignables depuis aucune branche — donc invisibles pour `git log`.

Le `reflog` est un journal local qui garde la trace de chaque déplacement de `HEAD` (commit, checkout, reset, rebase, merge...), indépendamment des branches. C'est ce journal qui permet de retrouver un commit "orphelin" et de le ramener avec un simple `reset --hard <hash>` ou un `cherry-pick`.

Limite importante : le reflog est **local** à la machine (il n'est jamais poussé sur le dépôt distant) et n'est conservé que temporairement (90 jours par défaut pour les commits atteignables, 30 jours pour les autres) avant que Git ne nettoie ces objets définitivement via son ramasse-miettes (`git gc`). Ce n'est donc pas un filet de sécurité infini, mais il couvre largement le cas d'une erreur de manipulation constatée peu après.