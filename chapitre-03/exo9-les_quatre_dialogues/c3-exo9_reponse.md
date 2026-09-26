# Exercice 9 : les quatre dialogues

## Les quatre dialogues natifs employés

D'après `NKWindow/Core/NkDialogs.h`, quatre dialogues renvoient un `NkDialogResult` (avec un champ `confirmed` à vérifier) :

1. `NkDialogs::OpenFileDialog(filter, title)` — sélection d'un fichier existant
2. `NkDialogs::SaveFileDialog(defaultExt, title)` — choix d'un emplacement de sauvegarde
3. `NkDialogs::OpenFolderDialog(title)` — sélection d'un dossier
4. `NkDialogs::ColorPicker(initial)` — sélection d'une couleur

(`OpenMessageBox` existe aussi dans le module, mais c'est une simple boîte d'information sans notion d'annulation à gérer — elle n'est pas de la même famille que les quatre autres.)

## Comment l'annulation est traitée

Chaque appel renvoie un `NkDialogResult` dont le champ `confirmed` indique si l'utilisateur a validé ou fermé la boîte sans rien choisir. Le code ne touche jamais à `res.path` ou `res.color` avant d'avoir vérifié `res.confirmed` :

​```cpp
static void LogDialogResult(const NkString &nomDialogue, const NkDialogResult &res) {
	if (!res.confirmed) {
		logger.Info("[exo9] %s : annule par l'utilisateur", nomDialogue.CStr());
		return;
	}
	logger.Info("[exo9] %s : confirme, path=\"%s\", color=%u",
				nomDialogue.CStr(), res.path.CStr(), res.color);
}
​```

Cette fonction est appelée après chacun des quatre dialogues. Si `confirmed` est faux, on se contente de logger l'annulation et on sort immédiatement — aucun accès à `path` ou `color` n'a lieu dans ce cas, donc aucun risque de lire une valeur vide/invalide par erreur.

## Déclenchement

Le programme ouvre une fenêtre et écoute les événements `KEYBOARD` (famille vue en cours) :
- `O` → ouvrir un fichier
- `S` → enregistrer sous
- `D` → choisir un dossier
- `C` → choisir une couleur
- `Échap` → fermer la fenêtre

## Vérification

Testé en fermant chaque boîte de dialogue sans rien choisir (bouton "Annuler" ou croix de fermeture) : le programme continue de tourner normalement dans les quatre cas, sans plantage, et affiche simplement le message d'annulation correspondant dans le log.