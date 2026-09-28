#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include <sstream>  
#include <string>   

// Reconstruit le titre a partir de l'etat courant (nom, taille, modif) et l'applique.
static void RafraichirTitre(nkentseu::NkWindow &window, const std::string &docName, bool dirty) {
    auto currentSize = window.GetSize();
    std::ostringstream composedTitle;
    composedTitle << docName << (dirty ? "*" : "") << " - " << currentSize.x << "x" << currentSize.y;
    window.SetTitle(composedTitle.str().c_str());
}

int nkmain(const nkentseu::NkEntryState& state) {
    nkentseu::NkWindowConfig windowCfg;
    windowCfg.title  = "MonTitre, etape 02";
    windowCfg.width  = 800;  
    windowCfg.height = 600;   
    nkentseu::NkWindow window;
    if (!window.Create(windowCfg)) {
        logger.Error("Echec de creation de la fenetre");
        return -1;
    }

    std::string docName = "MonTitre, etape 02"; 
    bool dirty = false;                            
    RafraichirTitre(window, docName, dirty);           

    while (window.IsOpen()) {
        while (nkentseu::NkEvent* event = nkentseu::NkEvents().PollEvent()) {
            if (event->Is<nkentseu::NkWindowCloseEvent>()) {
                window.Close();
            }

            if (event->Is<nkentseu::NkWindowResizeEvent>()) {
                RafraichirTitre(window, docName, dirty);
            }

            
            if (event->Is<nkentseu::NkKeyPressEvent>()) {
                dirty = true;
                RafraichirTitre(window, docName, dirty);
            }
        }
    }
    return 0;
}