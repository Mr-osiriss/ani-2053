# Exercice 9 : l'histoire d'un fichier

## Fichier choisi

`Kernel/Runtime/NKMedia/ROADMAP.md` dans le dépôt [Rihen-Universe/Nkentseu](https://github.com/Rihen-Universe/Nkentseu).

Ce fichier a 115 commits.

## Commande utilisée

​```
git log --follow --oneline -- Kernel/Runtime/NKMedia/ROADMAP.md
​```

`--follow` permet de garder l'historique même si le fichier a été renommé ou déplacé entre-temps.

Pour trouver les commits qui ont le plus changé le fichier, j'ai comparé le nombre de lignes ajoutées + supprimées à chaque commit.

## 1. La création

**Commit `d6795b5a7`, le 10 juillet 2026 :**

> feat(nkmedia): nouveau module NKMedia - brique 1 NkMediaProbe (demux d'en-tete ISOBMFF/MP4 + EBML/WebM from-scratch) ; identifie conteneur+codec+params. Valide sur corpus reel (Bassa->MP4/AAC, ghomala->WebM/Opus). ROADMAP conteneurs/codecs staged

Le module NKMedia commence avec une première brique : un lecteur d'en-têtes de fichiers audio/vidéo (MP4 et WebM), écrit sans dépendance externe et testé sur des vrais fichiers. Le ROADMAP est créé en même temps que cette brique, pour suivre ce qu'il reste à faire.

## 2. Les trois moments où le fichier a le plus changé

### a) `6f79e7ea` — 23 juillet 2026 — le plus gros changement (100 lignes)

> fix(nkmedia): VP9 brique 6 - TRAMES INTER RESOLU, bit-exact vs ffmpeg [...]. Trois bugs independants trouves via vpxdec instrumente [...]

Trois bugs corrigés d'un coup dans le décodeur VP9 : les probabilités n'étaient pas adaptées entre les trames, un calcul de position de bloc oubliait un décalage (ce qui cassait tout sauf le tout premier bloc), et une vérification était trop stricte. Le message explique chaque bug et comment il a été trouvé (en comparant avec un décodeur de référence).

### b) `12b8c339` — 14 août 2026 (99 lignes)

> Feuilles de route : remettre d'aplomb ce que le code dément

Celui-ci ne touche pas au code, il corrige le ROADMAP lui-même. Douze affirmations fausses sont reprises. La plus marquante : une ligne disait "rien n'existe" pour un lecteur PDF alors que la fonctionnalité avait été codée des semaines plus tôt.