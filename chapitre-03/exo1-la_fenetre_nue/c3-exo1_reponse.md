# Exercice 1 : la fenêtre nue

## Le programme

Le plus petit programme qui ouvre une fenêtre, la garde ouverte, et se termine proprement. Il tient en 24 lignes, dont 3 vides, soit **21 lignes de code**.

## Ligne par ligne, avec sa source dans le chapitre

| Ligne | Contenu | Rôle | Où c'est expliqué dans le chapitre |
|---|---|---|---|
| 1 | `#include "NKWindow/NKMain.h"` | Fournit le vrai point d'entrée natif de chaque plateforme | « Vous n'écrivez pas de `main` » |
| 2 | `#include "NKWindow/NKWindow.h"` | Donne accès à `NkWindow` et `NkWindowConfig` | « Le plus petit programme » |
| 4 | `int nkmain(const nkentseu::NkEntryState& state)` | Le point d'entrée qu'on écrit à la place de `main` | « Vous n'écrivez pas de `main` » |
| 5 | `nkentseu::NkWindowConfig cfg;` | Déclare la configuration de la fenêtre | « Configurer et piloter la fenêtre » |
| 6-8 | `cfg.title`, `cfg.width`, `cfg.height` | Titre et taille de la fenêtre | Même section : « l'identité et la taille » |
| 10 | `nkentseu::NkWindow window;` | Déclare l'objet fenêtre | — |
| 11 | `if (!window.Create(cfg))` | Vérifie que la création a réussi avant de continuer | « On vérifie `IsOpen` » : une création peut échouer, un programme qui continue après travaille dans le vide |
| 12 | `logger.Error(...)` | Trace la cause de l'échec | « Le plus petit programme » |
| 13 | `return -1;` | Sort proprement en cas d'échec | Même section |
| 16 | `while (window.IsOpen())` | Boucle tant que la fenêtre est ouverte | « Le plus petit programme » |
| 17 | `while (... NkEvents().PollEvent())` | Vide la file d'événements à chaque tour | Première hauteur pour lire les entrées : « la file » |
| 18 | `if (event->Is<NkWindowCloseEvent>())` | Reconnaît l'événement de fermeture | Famille `WINDOW`, parmi les douze familles |
| 19 | `window.Close();` | Déclenche réellement la fermeture | — |
| 23 | `return 0;` | Sortie propre du programme | — |

## Pourquoi la ligne 18-19 est nécessaire

Testé sans ce bloc : la fenêtre reste ouverte, impossible de la fermer avec la croix. Cette ligne est donc indispensable — contrairement à une variable genre `running`, qui n'aurait servi à rien ici puisque `window.IsOpen()` joue déjà ce rôle.

## Compilation

```
PS C:\Users\BEST-COMPUTER\Desktop\dd\FirstWindow> jenga build

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
│  ✓ Build Successful                                                             Time: 4.57s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           4.57s
Status:         ✓ SUCCESS
═════════════════════════════════════════════════════════════
```

## Exécution

```
PS C:\Users\BEST-COMPUTER\Desktop\dd\FirstWindow> jenga run  

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
     C:\Users\BEST-COMPUTER\Desktop\dd\FirstWindow\Build\Bin\Debug-Windows\Window\Window.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (3.20s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```