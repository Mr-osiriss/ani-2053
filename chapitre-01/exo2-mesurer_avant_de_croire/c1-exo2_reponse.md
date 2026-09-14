# Compte rendu — Exo 2 : Mesurer avant de croire

## 1. Commandes PowerShell exécutées
```powershell
# Brut global
(Get-ChildItem -Recurse -File -Include *.cpp, *.h).Count

# Sans Build/
(Get-ChildItem -Recurse -File -Include *.cpp, *.h | Where-Object { $_.FullName -notmatch '\\Build\\' }).Count

# Uniquement .cpp (hors build)
(Get-ChildItem -Recurse -File -Include *.cpp | Where-Object { $_.FullName -notmatch '\\Build\\' }).Count

# Uniquement .h/.hpp (hors build)
(Get-ChildItem -Recurse -File -Include *.h, *.hpp | Where-Object { $_.FullName -notmatch '\\Build\\' }).Count