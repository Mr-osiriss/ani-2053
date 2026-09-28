# Exercice 9 : les quatre dialogues

## Les quatre dialogues natifs employés

D'après `NKWindow/Core/NkDialogs.h`, quatre dialogues renvoient un `NkDialogResult` (avec un champ `confirmed` à vérifier) :

1. `NkDialogs::OpenFileDialog(filter, title)` — sélection d'un fichier existant
2. `NkDialogs::SaveFileDialog(defaultExt, title)` — choix d'un emplacement de sauvegarde
3. `NkDialogs::OpenFolderDialog(title)` — sélection d'un dossier
4. `NkDialogs::ColorPicker(initial)` — sélection d'une couleur

(`OpenMessageBox` existe aussi dans le module, mais c'est une simple boîte d'information sans notion d'annulation à gérer — elle n'est pas de la même famille que les quatre autres.)

## Comment l'annulation est traitée

Chaque appel renvoie un `NkDialogResult` dont le champ `confirmed` indique si l'utilisateur a validé ou fermé la boîte sans rien choisir :

```cpp
static void LogDialogResult(const NkString &nomDialogue, const NkDialogResult &res) {
	if (!res.confirmed) {
		logger.Info("[exo9] {} : annule par l'utilisateur", nomDialogue.CStr());
		return;
	}
	logger.Info("[exo9] {} : confirme, path=\"{}\", color={}",
				nomDialogue.CStr(), res.path.CStr(), res.color);
}
```

Le code ne touche jamais à `res.path` ou `res.color` avant d'avoir vérifié `res.confirmed`.

## Déclenchement

Le programme ouvre une fenêtre et écoute les événements clavier :
- `O` → ouvrir un fichier
- `S` → enregistrer sous
- `D` → choisir un dossier
- `C` → choisir une couleur
- `Échap` → fermer la fenêtre

## Test réel : les quatre annulations

Compilé avec `jenga build`, exécuté avec `jenga run`. Les quatre dialogues ont été ouverts puis annulés l'un après l'autre :

```
PS C:\Ngangoum\FirstWindow> jenga build

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.3             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. Window [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Window                                                          Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Window\Window.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 7.72s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           7.72s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

PS C:\Ngangoum\FirstWindow> jenga run  

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.3             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  Window.exe
     C:\Ngangoum\FirstWindow\Build\Bin\Debug-Windows\Window\Window.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

[2026-09-28 23:07:09.154] [INF] [default] [main.cpp:32 in nkmain] -> [exo9] O = ouvrir un fichier | S = enregistrer sous | D = choisir un dossier | C = choisir une couleur | Echap = quitter
[2026-09-28 23:07:16.983] [INF] [default] [main.cpp:13 in LogDialogResult] -> [exo9] OpenFileDialog : annule par l'utilisateur
[2026-09-28 23:07:22.572] [INF] [default] [main.cpp:13 in LogDialogResult] -> [exo9] SaveFileDialog : annule par l'utilisateur
[2026-09-28 23:07:34.760] [INF] [default] [main.cpp:13 in LogDialogResult] -> [exo9] OpenFolderDialog : annule par l'utilisateur
[2026-09-28 23:07:38.531] [INF] [default] [main.cpp:13 in LogDialogResult] -> [exo9] ColorPicker : annule par l'utilisateur

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (37.67s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

## Conclusion

Les quatre dialogues ont été ouverts puis fermés sans rien choisir : dans les quatre cas, le message "annulé par l'utilisateur" s'affiche correctement et le programme se termine normalement (`termine normalement`, 37.67s), sans plantage.