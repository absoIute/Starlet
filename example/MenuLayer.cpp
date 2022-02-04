#include "MenuLayer.h"

SX_FUNC_DEF(MenuLayer, init);
SX_FUNC_DEF(MenuLayer, onPlay);
SX_FUNC_DEF(MenuLayer, onQuit);
SX_FUNC_DEF(MenuLayer, onGarage);
SX_FUNC_DEF(MenuLayer, onCreator);

void MenuLayer::SX_INIT(uintptr_t handle)
{
	SX_FUNC_INIT(0x1907B0, init);
	SX_FUNC_INIT(0x191B50, onPlay);
	SX_FUNC_INIT(0x191FA0, onQuit);
	SX_FUNC_INIT(0x191DC0, onGarage);
	SX_FUNC_INIT(0x191CD0, onCreator);
}
