#pragma once

#include <starlet.h>
#include <MenuLayer.h>

SX_HOOK_CLASS_DECL(MenuLayer)
{
public:
	bool SX_HOOK_DECL(init)();
};
