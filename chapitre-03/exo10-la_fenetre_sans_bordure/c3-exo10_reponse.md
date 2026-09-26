# Exercice 10 : la fenêtre sans bordure

## Fenêtre sans bordure

​```cpp
NkWindowConfig cfg;
cfg.frame = false;
​```

`frame = false` désactive la barre de titre et les bordures natives de l'OS : la fenêtre devient une simple zone rectangulaire vide, à nous de reconstruire tout ce qui manque.

## Ma barre de titre

Comme le module de rendu n'a pas encore été vu en cours, cette réponse implémente la **logique** de la barre de titre custom (déplacement, agrandissement, boutons cliquables), sans dessin visuel — le rendu graphique viendra avec le module de rendu (chapitre suivant).

- **Le titre** : posé via `window.SetTitle("Ma barre de titre a moi")` dès l'ouverture (même sans bordure, ce titre reste utile pour la barre des tâches de l'OS).
- **Trois boutons** : trois zones cliquables (`Minimize`, `MaximizeRestore`, `Close`) calculées par `ZoneAt()`, alignées à droite sur les 32 premiers pixels de hauteur de la fenêtre.
- **Déplacement à la souris** : un clic gauche dans le reste de la barre de titre (zone `Drag`) démarre un glisser — la position de la fenêtre est recalculée à chaque `NkMouseMoveEvent` en fonction du déplacement de la souris en coordonnées écran (`GetScreenX/Y`, qui ne sont pas affectées par le déplacement de la fenêtre elle-même, contrairement aux coordonnées client).
- **Le double-clic qui agrandit** : `NkMouseDoubleClickEvent` sur la zone `Drag` bascule entre `Maximize()` et `Restore()` selon `IsMaximized()`.

## Pourquoi calculer les zones plutôt que stocker des rectangles

`ZoneAt()` recalcule la position des boutons à chaque clic à partir de la largeur actuelle de la fenêtre (`window.GetSize().x`). Ça évite de devoir mettre à jour des coordonnées stockées à chaque redimensionnement.

## Temps passé

*cet exercice ma pris environs 1h30 de temps,ecrire le code etait compliqué vu que je n'ai pas de grande connaissance en c++, l'API encore je ne la connaissais pas, je devais encore comprendre des trucs comme GetScreenX et GetX*