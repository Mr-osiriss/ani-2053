#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"

int nkmain(const nkentseu::NkEntryState& state) {
    nkentseu::NkWindowConfig windowCfg;
    windowCfg.title = "Fenetre a taille minimale";
    windowCfg.minWidth = (300);
    windowCfg.minHeight = (250);

    nkentseu::NkWindow window;
    if (!window.Create(windowCfg)) {
        logger.Error("Echec de creation de la fenetre");
    
        return -1;
    }

    while (window.IsOpen()) {
        while (nkentseu::NkEvent* event = nkentseu::NkEvents().PollEvent()) {
        if (event->Is<nkentseu::NkWindowCloseEvent>()) {
            auto size = window.GetSize();
            logger.Info("X = {}", size.x);
            logger.Info("Y = {}", size.y);
         
        window.Close();
        }
        }
    }
    return 0;
}