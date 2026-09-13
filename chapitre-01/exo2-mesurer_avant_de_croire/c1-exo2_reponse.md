# Compte rendu — Exo 2 : Mesurer avant de croire

## 1. Cadre corrigé
* **Référence du cours** : 2 641 fichiers source et 1 193 385 lignes (les 286 unités sont des *projets*, pas des fichiers).

## 2. Commandes de mesure (PowerShell)
```powershell
# Brut
(Get-ChildItem -Recurse -File -Include *.cpp, *.h).Count
# Sans Build/
(Get-ChildItem -Recurse -File -Include *.cpp, *.h | Where-Object { $_.FullName -notmatch '\\Build\\' }).Count
# Uniquement .cpp
(Get-ChildItem -Recurse -File -Include *.cpp | Where-Object { $_.FullName -notmatch '\\Build\\' }).Count
# Uniquement .h/.hpp
(Get-ChildItem -Recurse -File -Include *.h, *.hpp | Where-Object { $_.FullName -notmatch '\\Build\\' }).Count