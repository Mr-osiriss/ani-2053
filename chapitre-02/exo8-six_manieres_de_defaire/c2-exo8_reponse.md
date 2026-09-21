# Exercice 8 : six manières de défaire

## 1. Une modification non voulue

**Provoquer :** modification du fichier sans `add`.

**Défaire :**
​```
git restore notes.md
​```
Remet le fichier dans l'état du dernier commit, tant que la modification n'a pas été ajoutée au staging.

## 2. Un `add` de trop

**Provoquer :** `git add` sur une modification qu'on ne voulait pas encore mettre en staging.

**Défaire :**
​```
git restore --staged notes.md
​```
Retire le fichier du staging sans perdre la modification (elle repasse en "Changes not staged").

## 3. Un commit de trop (pas encore poussé)

**Provoquer :** `git commit` fait par erreur, mais jamais poussé.

**Défaire :**
​```
git reset --soft HEAD~1
​```
Le commit disparaît de l'historique, mais son contenu revient en staging : rien n'est perdu.

## 4. Un commit poussé qu'il faut annuler

**Provoquer :** `git commit` + `git push`, déjà sur `origin/main`.

**Défaire :**
​```
git revert <hash-du-commit>
git push origin main
​```
On ne réécrit pas l'historique déjà partagé. `git revert` crée un **nouveau commit** qui applique l'inverse du commit fautif. L'ancien commit reste visible dans l'historique, mais son effet est annulé.

## 5. Un travail en cours qu'il faut mettre de côté

**Provoquer :** modification en cours, pas prête à être commitée.

**Mettre de côté :**
​```
git stash
​```
**Récupérer plus tard :**
​```
git stash pop
​```
Range la modification sans la committer ; le répertoire de travail redevient propre entretemps, puis la modification revient à l'identique.

## 6. Un commit « perdu » à retrouver par le reflog

**Provoquer :** `git reset --hard HEAD~1`, qui fait disparaître un commit de `git log`.

**Retrouver :**
​```
git reflog
​```
Le commit reste listé dans le reflog, avec son hash, même s'il n'est plus atteignable depuis aucune branche.

**Récupérer :**
​```
git cherry-pick <hash-retrouve>
​```
Rejoue ce commit par-dessus l'état actuel (avec un nouveau hash), sans avoir besoin de retaper le travail perdu.

## Ce que ça montre

- Plus une modification avance dans le cycle Git (working directory → staging → commit local → commit poussé), plus l'annuler demande un outil différent : `restore` pour les deux premiers, `reset` pour un commit local, `revert` dès qu'un commit est partagé avec d'autres.
- `reset --hard` ne supprime pas vraiment les commits : ils restent accessibles via le reflog tant que Git ne les a pas nettoyés (le nettoyage automatique intervient après plusieurs semaines par défaut). Le reflog est donc un vrai filet de sécurité contre les erreurs de manipulation de l'historique.
- `revert` et `reset` répondent au même besoin ("annuler un commit"), mais `revert` garde une trace explicite de l'annulation dans l'historique (utile quand d'autres personnes ont déjà récupéré le commit fautif), alors que `reset` fait comme si le commit n'avait jamais existé (à réserver au travail encore local).