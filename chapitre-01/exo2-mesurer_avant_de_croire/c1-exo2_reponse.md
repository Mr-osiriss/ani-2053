# Compte rendu — Exo 2 : Mesurer avant de croire

j'ai fait le tour de l'arborescence Nkentseu pour estimer les sources et les lignes.

## Mes choix de comptage
- **Dossier `Build/`** : Ignoré direct. Je vais pas compter les fichiers objets, caches et binaires générés par les toolchains, ça représente pas l'effort de dev.
- **En-têtes (`.h` / `.hpp`)** : Séparés des `.cpp`. Je compte les specs d'interface à part, sinon le volume de lignes de code réel est faussé (surtout avec les 5 toolchains qui dupliquent ou configuent des trucs).
- **Fichiers de test (`TestSuite`)** : Isolés des 57 libs statiques core. Les 63 suites de test, c'est de la vérif, pas le code runtime du moteur.

## Pourquoi ça peut différer du cours
Le cours donne le scope Jenga macro (les 286 projets). Si mon comptage diffère, c'est parce que j'enlève tout ce qui est généré/build et que je sépare strictement le code core des tests et des en-têtes utilitaires cross-platform (`clang-cross-linux`, etc.).