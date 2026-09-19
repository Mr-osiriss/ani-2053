# Exercice 7 : le conflit qui n'en est pas un

## Démarche

1. Un fichier de base à 7 lignes a été créé et poussé sur `main` depuis le clone 1.
2. Le clone 2 a récupéré ce fichier.
3. Le **clone 1** a modifié la **ligne 1** (le début du fichier) et poussé sans problème.
4. Le **clone 2**, sans avoir pull entretemps, a modifié la **ligne 7** (la fin du fichier) — une zone complètement différente du fichier.
5. Le push du clone 2 a été **refusé** (comme à l'exercice 6), car `origin/main` contenait déjà un commit inconnu du clone 2.
6. Un `git pull` a été lancé côté clone 2 : cette fois, Git a **fusionné automatiquement**, sans demander aucune intervention.

## 1. Le refus (identique à l'exercice 6)

​```
To https://github.com/Mr-osiriss/ani-2053.git
 ! [rejected]        main -> main (fetch first)
error: failed to push some refs to 'https://github.com/Mr-osiriss/ani-2053.git'
hint: Updates were rejected because the remote contains work that you do not
hint: have locally. This is usually caused by another repository pushing to
hint: the same ref. If you want to integrate the remote changes, use
hint: 'git pull' before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
​```

## 2. La fusion automatique (pas de conflit !)

​```
Auto-merging chapitre-02/exo7-le_conflit_qui_n_en_est_pas_un/c2-exo7_reponse.md
Merge made by the 'ort' strategy.
 chapitre-02/exo7-le_conflit_qui_n_en_est_pas_un/c2-exo7_reponse.md | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
​```

Aucune ligne `CONFLICT`, aucune intervention manuelle requise.

## 3. Le résultat final

​```
Ligne 1 : MODIFIEE par le clone 1
Ligne 2
Ligne 3
Ligne 4
Ligne 5
Ligne 6
Ligne 7 : MODIFIEE par le clone 2
​```

Les deux modifications cohabitent dans le fichier final, chacune conservée intégralement.

## Ce que ça montre

- **Le refus de push** (fetch first) se produit dans les deux cas (conflit ou non) : c'est une protection systématique de Git dès que l'historique distant a avancé sans que le local le sache, indépendamment du contenu des changements.
- **La différence se joue au moment du merge, pas du push.** Git compare les modifications ligne par ligne (plus précisément, par "hunks" de lignes voisines) entre la version commune (ancêtre), la version du clone 1, et la version du clone 2.
- Puisque les deux modifications touchent des **zones du fichier suffisamment éloignées** (ligne 1 vs ligne 7, avec des lignes inchangées entre les deux), Git peut appliquer les deux changements indépendamment, sans ambiguïté sur ce qu'il faut garder : il n'y a donc **aucun conflit**, contrairement à l'exercice 6 où la même ligne était modifiée des deux côtés.
- Ça illustre bien que Git ne raisonne pas "au fichier" mais **par zones de lignes modifiées** : deux personnes peuvent travailler sur le même fichier sans jamais se gêner, tant qu'elles ne touchent pas aux mêmes lignes (ou à des lignes trop proches l'une de l'autre).