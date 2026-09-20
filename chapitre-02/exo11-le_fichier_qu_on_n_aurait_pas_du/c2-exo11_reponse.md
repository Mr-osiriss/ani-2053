# Exercice 11 : le fichier qu'on n'aurait pas dû

## Démarche

1. Mesure de la taille du dossier `.git` avant toute manipulation.
2. Création d'un fichier binaire de 10 Mo (contenu aléatoire, non compressible).
3. Commit de ce fichier.
4. Mesure de la taille de `.git` avec le fichier ajouté.
5. Suppression du fichier avec `git rm`, puis commit de cette suppression.
6. Nouvelle mesure de la taille de `.git`.

## Mesures

| Étape | Taille de `.git` |
|-------|-------------------|
| Avant l'ajout du fichier | 0,1043 Mo |
| Après le commit du fichier de 10 Mo | 10,1086 Mo |
| Après suppression du fichier (`git rm` + commit) | 10,1089 Mo |

## Constat

La taille de `.git` **n'a quasiment pas diminué** après la suppression du fichier (elle a même très légèrement augmenté, à cause du nouvel objet créé pour enregistrer le commit de suppression lui-même).

## Explication

`git rm` supprime le fichier du **répertoire de travail** et de l'**index** (staging area), et le commit qui suit enregistre que le fichier n'existe plus **à partir de maintenant**. Mais le commit précédent, celui qui a ajouté le fichier, existe toujours dans l'historique : son contenu (le fichier de 10 Mo) reste stocké tel quel dans la base d'objets de Git (`.git/objects`), car un objet Git n'est jamais modifié ni supprimé une fois créé — seul l'historique des commits peut changer d'état.

Autrement dit, supprimer un fichier avec `git rm` dit à Git "n'inclus plus ce fichier dans les prochains commits", mais ne dit pas "efface ce fichier de l'historique". Tant que le commit qui contient l'ancien fichier reste atteignable dans l'historique (via `git log`, une branche, un tag...), l'objet correspondant reste sur le disque.

## Comment vraiment le faire disparaître (si nécessaire)

Pour réellement effacer le fichier du disque, il faudrait réécrire l'historique (par exemple avec `git filter-repo` ou un rebase interactif supprimant le commit fautif), puis forcer un nettoyage des objets orphelins avec `git gc --aggressive --prune=now`. Cette opération change les hash de tous les commits suivants et casse l'historique partagé : à éviter une fois le code déjà poussé et récupéré par d'autres, sauf en cas de fuite de données sensibles où c'est nécessaire malgré tout.

## Conclusion

Un commit Git n'est jamais vraiment "annulé" par un commit suivant : il reste consultable et son contenu reste stocké tant qu'il est atteignable dans l'historique. Committer un gros fichier par erreur, même si on le supprime aussitôt après, laisse une trace durable dans le poids du dépôt — la vraie prudence consiste à ne jamais commit un fichier volumineux ou sensible en premier lieu (via un `.gitignore` bien configuré), plutôt que de compter sur une suppression a posteriori.