# Compte rendu — Exo 4 : Le fichier de projet annoté (`NKCore.jenga`)

## 1. Code source réel (`Kernel\Foundation\NKCore\NKCore.jenga`)
```python
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
NKCore — Types, macros, assertions, opérations bit (C++20)
===========================================================
S'appuie sur NKPlatform pour les types fixes et macros fondamentaux
réutilisés par toutes les couches supérieures.
"""

from Jenga import *
from jengaconfig import *

with project("NKCore"):
    language("C++")
    cppdialect("C++20")
    location(".")

    nkentseudependson(
        ["NKPlatform"],
        selfexport="NKCore",
        extra_includes=["src", "pch"],
    )

    pchheader("pch/pch.h")
    pchsource("pch/pch.cpp")

    files([
        "src/NKCore/**.cpp",
        "src/NKCore/**.h",
    ])

    objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
    targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}")

    with filter("system:Windows && options:windows-runtime=uwp"):
        objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}-uwp/%{prj.name}")
        targetdir("%{wks.location}/Build/Lib/%{cfg.buildcfg}-%{cfg.system}-uwp")

    with filter("system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !system:XboxOne"):
        usetoolchain(TC_WINDOWS)
    with filter("system:UWP || system:Windows && options:windows-runtime=uwp"):
        usetoolchain("xbox-clang")
    with filter("system:macOS"):
        usetoolchain("clang-native")
    with filter("system:Android"):
        pchheader("")
        pchsource("")
        usetoolchain("android-ndk")
    with filter("system:HarmonyOS"):
        pchheader("")
        pchsource("")
        usetoolchain("ohos-ndk")
    with filter("system:Web"):
        usetoolchain("emscripten")
    with filter("system:XboxSeries || system:XboxOne"):
        usetoolchain("xbox-clang")

    with filter("config:Debug"):
        defines(["_DEBUG", "DEBUG", "NKENTSEU_DEBUG"])
        optimize("Off")
        symbols(True)
    with filter("config:Release"):
        defines(["NDEBUG", "RELEASE", "NKENTSEU_RELEASE"])
        optimize("Speed")
        symbols(False)

    with filter("(system:Linux || system:macOS || (system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !system:XboxOne)) && !system:Android && !system:iOS || system:Web"):
        with test():
            testfiles(["tests/**.cpp"])