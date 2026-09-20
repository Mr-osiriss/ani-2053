# Règles Git de l'équipe

voila les regles que devoient suivre 4 personne d'un meme groupe de travail.

## Nommage des branches

On nomme les branches comme ça : `type/ce-qu-on-fait`

Exemples :
- `feat/ajout-menu` pour une nouvelle fonctionnalité
- `fix/bug-collision` pour corriger un bug
- `docs/readme` pour de la doc

Pas de branche avec juste son prénom `julien-branche`, ça ne dit rien sur ce qu'il y a dedans. Le nom doit dire ce qu'on fait, pas qui le fait.

Une branche = un seul truc à faire. Si on commence un autre truc, on fait une autre branche.

## Ce qu'un commit doit contenir

Un commit = une seule chose faite. Pas deux trucs différents mélangés dans le même commit, sinon si jamais il faut annuler un changement plus tard on ne peut pas annuler juste un des deux trucs.

Pour le message : on essaie d'écrire clairement ce qu'on a fait.

Avant de commit, on fait un `git status` pour vérifier qu'on ajoute que ce qu'il faut (pas des fichiers qu'on a pas fait exprès de modifier).

## Qui relit quoi

Personne ne push direct sur main. On passe toujours par une pull request.

Une personne du groupe (pas celle qui a écrit le code) doit relire avant qu'on merge. Elle vérifie que ça marche et que le code est compréhensible.

Celui qui a fait le code n'a pas le droit de merger sa propre pull request tout seul, il faut l'accord de quelqu'un d'autre.

## Ce qui est interdit

- Push force sur main (ça peut écraser le travail des autres)
- Commit direct sur main sans passer par une branche
- Mettre des fichiers persos (config de l'IDE, mots de passe, etc) dans le dépôt
- Faire des commits "wip" ou "test" qui restent dans l'historique final sans être nettoyés avant la pull request

## Si quelqu'un casse main

1. On prévient tout de suite le groupe, pas la peine d'essayer de réparer dans son coin en ajoutant d'autres commits par dessus
2. On regarde avec `git log` c'est quel commit qui a cassé
3. On annule ce commit avec `git revert` plutôt que de tout réécrire, pour pas embêter les autres qui bossent en même temps
4. Une fois que c'est réparé, on en discute en groupe pour comprendre pourquoi personne ne l'a vu avant (peut-être qu'on a pas assez testé avant de merger)

## Pourquoi ces règles

 c'est surtout pour pas se marcher dessus à 4 sur le même projet. Si les commits sont clairs et que quelqu'un relit avant de merger, on évite de casser le travail des autres sans faire exprès, et on comprend plus facilement l'historique quand on doit revenir en arrière.