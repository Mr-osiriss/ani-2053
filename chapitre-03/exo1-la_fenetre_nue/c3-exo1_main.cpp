#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"

int nkmain(const nkentseu::NkEntryState& state) {
    nkentseu::NkWindowConfig cfg;
    cfg.title  = "Fenetre minimale";
    cfg.width  = 800;
    cfg.height = 600;

    nkentseu::NkWindow window;
    if (!window.Create(cfg)) {
        logger.Error("Echec de creation de la fenetre");
        return -1;
    }

    while (window.IsOpen()) {
        while (nkentseu::NkEvent* event = nkentseu::NkEvents().PollEvent()) {
            if (event->Is<nkentseu::NkWindowCloseEvent>()) {
                window.Close();
            }
        }
    }
    return 0;
}