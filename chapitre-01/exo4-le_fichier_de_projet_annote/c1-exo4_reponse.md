# Compte rendu — Chapitre 01, Exercice 4 : Fichier de projet annoté

## Analyse ligne par ligne (`NKCore.jenga`)
```text
Project "NKCore" {                     // Déclaration de la cible de build
    Kind: StaticLib,                   // Type de sortie : bibliothèque statique
    Language: Cpp,                     // Langage utilisé : C++
    Files: {                           // Chemins des sources incluses
        "Source/**.cpp",               // Tous les fichiers .cpp du répertoire Source/
        "Include/**.h"                 // Tous les fichiers .h du répertoire Include/
    },
    Dependencies: {                    // Modules requis en amont
        "NKMbedTLS"                    // Dépendance explicite (TLS/crypto)
    },
    Defines: { "NK_CORE_BUILD" },      // Macros de préprocesseur de la cible
    Filter "Configurations:Debug" {    // Surcharge conditionnelle pour la configuration Debug
        Optimize: Off                  // Désactivation des optimisations du compilateur
    }
}