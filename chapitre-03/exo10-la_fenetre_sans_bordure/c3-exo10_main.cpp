#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKEvent/NkEventDispatcher.h"

using namespace nkentseu;

static const int32 TITLE_BAR_HEIGHT = 32;
static const int32 BUTTON_WIDTH = 40;

enum class TitleBarZone {
	None,
	Drag,
	Minimize,
	MaximizeRestore,
	Close
};

static TitleBarZone ZoneAt(int32 x, int32 y, uint32 windowWidth) {
	if (y < 0 || y >= TITLE_BAR_HEIGHT) {
		return TitleBarZone::None;
	}

	int32 closeLeft    = static_cast<int32>(windowWidth) - BUTTON_WIDTH;
	int32 maximizeLeft = closeLeft - BUTTON_WIDTH;
	int32 minimizeLeft = maximizeLeft - BUTTON_WIDTH;

	if (x >= closeLeft) return TitleBarZone::Close;
	if (x >= maximizeLeft) return TitleBarZone::MaximizeRestore;
	if (x >= minimizeLeft) return TitleBarZone::Minimize;

	return TitleBarZone::Drag;
}

int nkmain(const NkEntryState &state) {
	NkWindowConfig cfg;
	cfg.title  = "Exercice 10 - Fenetre sans bordure";
	cfg.width  = 960;
	cfg.height = 540;
	cfg.frame  = false;

	NkWindow window(cfg);
	if (!window.IsOpen()) {
		logger.Error("[exo10] creation fenetre echouee");
		return -1;
	}
	window.SetTitle("Ma barre de titre a moi");

	bool dragging = false;
	math::NkVec2u dragWindowStart(0, 0);
	int32 dragMouseStartScreenX = 0, dragMouseStartScreenY = 0;

	logger.Info("[exo10] barre de titre custom active : glissez pour deplacer, "
				"double-cliquez pour agrandir/restaurer");

	while (window.IsOpen()) {
		NkEvent *ev;
		while (NkEvents().PollEvent(ev)) {
			if (ev->Is<NkWindowCloseEvent>()) {
				window.Close();
				break;
			}

			if (auto *press = ev->As<NkMouseButtonPressEvent>()) {
				int32 rawX = press->GetX();
				int32 rawY = press->GetY();
				logger.Info("[exo10][diag] brut x={} y={} taille_fenetre={}x{}",
							rawX, rawY, window.GetSize().x, window.GetSize().y);

				if (press->IsLeft()) {
					TitleBarZone zone = ZoneAt(rawX, rawY, window.GetSize().x);
					logger.Info("[exo10][diag] zone calculee = {}", static_cast<int32>(zone));

					switch (zone) {
						case TitleBarZone::Close:
							logger.Info("[exo10] bouton Close clique");
							window.Close();
							break;

						case TitleBarZone::Minimize:
							logger.Info("[exo10] bouton Minimize clique");
							window.Minimize();
							break;

						case TitleBarZone::MaximizeRestore:
							if (window.IsMaximized()) {
								logger.Info("[exo10] bouton Restore clique (etait maximisee)");
								window.Restore();
							} else {
								logger.Info("[exo10] bouton Maximize clique");
								window.Maximize();
							}
							break;

						case TitleBarZone::Drag:
							logger.Info("[exo10] debut du glisser a x={} y={}", rawX, rawY);
							dragging = true;
							dragWindowStart = window.GetPosition();
							dragMouseStartScreenX = press->GetScreenX();
							dragMouseStartScreenY = press->GetScreenY();
							break;

						default:
							break;
					}
				}
			}

			if (auto *release = ev->As<NkMouseButtonReleaseEvent>()) {
				if (release->IsLeft() && dragging) {
					logger.Info("[exo10] fin du glisser, nouvelle position x={} y={}",
								window.GetPosition().x, window.GetPosition().y);
					dragging = false;
				}
			}

			if (auto *move = ev->As<NkMouseMoveEvent>()) {
				if (dragging) {
					int32 deltaX = move->GetScreenX() - dragMouseStartScreenX;
					int32 deltaY = move->GetScreenY() - dragMouseStartScreenY;
					window.SetPosition(static_cast<int32>(dragWindowStart.x) + deltaX,
										static_cast<int32>(dragWindowStart.y) + deltaY);
				}
			}

			if (auto *dbl = ev->As<NkMouseDoubleClickEvent>()) {
				if (dbl->IsLeft()) {
					TitleBarZone zone = ZoneAt(dbl->GetX(), dbl->GetY(), window.GetSize().x);
					if (zone == TitleBarZone::Drag) {
						if (window.IsMaximized()) {
							logger.Info("[exo10] double-clic : restaure");
							window.Restore();
						} else {
							logger.Info("[exo10] double-clic : maximise");
							window.Maximize();
						}
					}
				}
			}
		}
	}

	return 0;
}