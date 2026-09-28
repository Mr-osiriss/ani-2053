# Exercice 3 : taille minimale de la fenêtre

## Ce qui a été ajouté

Pour fixer une taille minimale :
```cpp
windowCfg.minWidth = (300);
windowCfg.minHeight = (250);
```

Pour afficher la taille réelle de la fenêtre au moment de sa fermeture :
```cpp
auto size = window.GetSize();
logger.Info("X = {}", size.x);
logger.Info("Y = {}", size.y);
```

## 1. Fixer une taille minimale

Tailles minimales demandées : **300** (largeur) et **250** (hauteur).

Compilé avec `jenga build`, exécuté avec `jenga run`. En réduisant la fenêtre au maximum, le terminal affiche :

```
  ▶  EXECUTION  —  Window.exe
     C:\Ngangoum\FirstWindow\Build\Bin\Debug-Windows\Window\Window.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

[2026-09-26 20:37:02.578] [INF] [default] [main.cpp:21 in nkmain] -> X = 278
[2026-09-26 20:37:02.579] [INF] [default] [main.cpp:22 in nkmain] -> Y = 194
```

Résultat obtenu : largeur **278**, hauteur **194** — alors que les valeurs demandées étaient 300 et 250. `minWidth`/`minHeight` ne sont donc pas respectées telles quelles par le système.

## 2. La plus petite taille que le système accepte

Test refait sans `minWidth`/`minHeight`. En réduisant la fenêtre jusqu'à la limite, le terminal affiche :

```
▶  EXECUTION  —  Window.exe
     C:\Ngangoum\FirstWindow\Build\Bin\Debug-Windows\Window\Window.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

[2026-09-26 20:46:36.182] [INF] [default] [main.cpp:20 in nkmain] -> X = 176
[2026-09-26 20:46:36.183] [INF] [default] [main.cpp:21 in nkmain] -> Y = 34
```

Taille minimale imposée par le système, sans contrainte du code : **largeur = 176**, **hauteur = 34**.

## Conclusion

La taille minimale réellement obtenue avec `minWidth`/`minHeight` fixés (278×194) est plus proche de la valeur demandée (300×250) que la taille plancher du système seul (176×34), mais reste en dessous des valeurs demandées. `minWidth`/`minHeight` semble donc influencer la taille minimale sans la garantir exactement — le système applique ses propres contraintes par-dessus (bordures, décorations de fenêtre, ou arrondi interne).