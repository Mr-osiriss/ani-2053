# Exercice 2 : les trois endroits

## 1. Après modification (avant add)

​```
On branch main
Your branch is ahead of 'origin/main' by 3 commits.
  (use "git push" to publish your local commits)

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   c2-exo2_reponse.md

no changes added to commit (use "git add" and/or "git commit -a")
​```

## 2. Après git add

​```
On branch main
Your branch is ahead of 'origin/main' by 3 commits.
  (use "git push" to publish your local commits)

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   c2-exo2_reponse.md
​```

## 3. Après git commit

​```
[main d488ba0] Complete la réponse de l'exercice 2
 1 file changed, 4 insertions(+), 1 deletion(-)

On branch main
Your branch is ahead of 'origin/main' by 4 commits.
  (use "git push" to publish your local commits)

no changes added to commit (use "git add" and/or "git commit -a")
​```

## Ce qui change entre les trois

- **Avant `add`** : le fichier est modifié dans le *working directory* seulement. Git le voit ("Changes not staged for commit") mais ne l'inclura pas dans le prochain commit.

- **Après `add`** : le fichier passe dans la *staging area* (index). Il apparaît dans "Changes to be committed" : Git est prêt à l'enregistrer.

- **Après `commit`** : le contenu de la staging area est enregistré définitivement dans l'historique du dépôt (commit `d488ba0`). Le fichier ne réapparaît plus comme modifié.