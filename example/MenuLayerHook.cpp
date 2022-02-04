#include "MenuLayerHook.h"

#include <iostream>

bool SX_HOOK_DEF(MenuLayer, init)()
{
	if (SX_ORIG(this, MenuLayer::init)())
	{
		std::cout << "heyyyyy\n";

		return true;
	}

	return false;
}
