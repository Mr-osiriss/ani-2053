# Compte rendu — Exo 3 : Le module seul (`NKMath`)

## 1. Commande exécutée
```bash
jenga build --target NKMath --config Debug

Build Order (5 projects):
  1. NKPlatform [STATIC_LIB] →
  2. NKCore [STATIC_LIB] (depends: NKPlatform) →
  3. NKMemory [STATIC_LIB] (depends: NKCore, NKPlatform) →
  4. NKContainers [STATIC_LIB] (depends: NKCore, NKMemory, NKPlatform) →
  5. NKMath [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform)

  NKPlatform
   │
   ▼
 NKCore ────────┐
   │            │
   ▼            ▼
NKMemory ───► NKContainers
   │               │
   └───────┬───────┘
           ▼
         NKMath