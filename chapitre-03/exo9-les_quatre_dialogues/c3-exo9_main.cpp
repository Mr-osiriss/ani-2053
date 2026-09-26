#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkDialogs.h"
#include "NKEvent/NkEventDispatcher.h"

using namespace nkentseu;

// Affiche un resultat de dialogue en gerant proprement l'annulation :
// si l'utilisateur ferme la boite sans rien choisir, "confirmed" vaut
// false et il ne faut surtout pas utiliser "path" ou "color" ensuite.
static void LogDialogResult(const NkString &nomDialogue, const NkDialogResult &res) {
	if (!res.confirmed) {
		logger.Info("[exo9] %s : annule par l'utilisateur", nomDialogue.CStr());
		return;
	}
	logger.Info("[exo9] %s : confirme, path=\"%s\", color=%u",
				nomDialogue.CStr(), res.path.CStr(), res.color);
}

int nkmain(const NkEntryState &state) {
	NkWindowConfig cfg;
	cfg.title  = "Exercice 9 - Les quatre dialogues";
	cfg.width  = 960;
	cfg.height = 540;

	NkWindow window(cfg);
	if (!window.IsOpen()) {
		logger.Error("[exo9] creation fenetre echouee");
		return -1;
	}

	logger.Info("[exo9] O = ouvrir un fichier | S = enregistrer sous | "
				"D = choisir un dossier | C = choisir une couleur | Echap = quitter");

	while (window.IsOpen()) {
		NkEvent *ev;
		while (NkEvents().PollEvent(ev)) {
			if (ev->Is<NkWindowCloseEvent>()) {
				window.Close();
				break;
			}

			if (auto *key = ev->As<NkKeyPressEvent>()) {
				switch (key->GetKey()) {
					case NkKey::NK_ESCAPE:
						window.Close();
						break;

					// 1) Dialogue d'ouverture de fichier
					case NkKey::NK_O: {
						NkDialogResult res = NkDialogs::OpenFileDialog("*.*", "Ouvrir un fichier");
						LogDialogResult("OpenFileDialog", res);
						break;
					}

					// 2) Dialogue d'enregistrement de fichier
					case NkKey::NK_S: {
						NkDialogResult res = NkDialogs::SaveFileDialog("txt", "Enregistrer sous");
						LogDialogResult("SaveFileDialog", res);
						break;
					}

					// 3) Dialogue de selection de dossier
					case NkKey::NK_D: {
						NkDialogResult res = NkDialogs::OpenFolderDialog("Choisir un dossier");
						LogDialogResult("OpenFolderDialog", res);
						break;
					}

					// 4) Selecteur de couleur
					case NkKey::NK_C: {
						NkDialogResult res = NkDialogs::ColorPicker(0xFFFFFFFF);
						LogDialogResult("ColorPicker", res);
						break;
					}

					default:
						break;
				}
			}
		}
	}

	return 0;
}