# Exercice 3 : le message qui sert

## Les trois commits analysés

Dépôt étudié : [Rihen-Universe/Nkentseu](https://github.com/Rihen-Universe/Nkentseu)

| # | Message | Hash |
|---|---------|------|
| 1 | transit : huit chantiers fusionnés, 226/226, prêt pour relecture (#89) | 9c3fad3 |
| 2 | Garde des chemins partages rapatriee vers main : et elle rougit VRAI | 07845c6 |
| 3 | Banc de coherence du registre de modules : DETECTER, et ne rien reparer | 8b86924 |

## Jugement

### 1. `9c3fad3` — "transit : huit chantiers fusionnés, 226/226, prêt pour relecture"

- **Dit-il ce qu'il fait ?** À moitié. On comprend qu'il y a eu une fusion, mais pas quels changements sont réellement inclus.
- **Pourquoi ?** Non. "Prêt pour relecture" est un statut de workflow, pas une raison.
- **Un seul sujet ?** Non. Le message assume lui-même fusionner huit chantiers différents en un seul commit.
- **Verdict : faible.** Message de "checkpoint d'intégration", pas exploitable individuellement (un `git bisect` ou `git revert` deviendrait ingérable).

### 2. `07845c6` — "Garde des chemins partages rapatriee vers main : et elle rougit VRAI"

- **Dit-il ce qu'il fait ?** Oui, en partie : un garde-fou sur les chemins partagés est rapatrié vers `main`.
- **Pourquoi ?** Non. "Elle rougit VRAI" est du jargon interne, incompréhensible pour un tiers.
- **Un seul sujet ?** Oui.
- **Verdict : moyen.** L'action est claire mais le style trop familier nuit à la compréhension future.

### 3. `8b86924` — "Banc de coherence du registre de modules : DETECTER, et ne rien reparer"

- **Dit-il ce qu'il fait ?** Oui