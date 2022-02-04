#pragma once

#include "starlet.h"
#include <cocos2d.h>

#include "FLAlertLayer.h"

class MenuLayer : public cocos2d::CCLayer, public FLAlertLayerProtocol
{
public:
	static void SX_INIT(uintptr_t handle);

	SX_FUNC_DECL(bool, MenuLayer, init);
	SX_FUNC_DECL(void, MenuLayer, onPlay, cocos2d::CCObject *obj) { SX_ORIG(this, onPlay)(obj); }
	SX_FUNC_DECL(void, MenuLayer, onQuit, cocos2d::CCObject *obj) { SX_ORIG(this, onQuit)(obj); }
	SX_FUNC_DECL(void, MenuLayer, onGarage, cocos2d::CCObject *obj) { SX_ORIG(this, onGarage)(obj); }
	SX_FUNC_DECL(void, MenuLayer, onCreator, cocos2d::CCObject *obj) { SX_ORIG(this, onCreator)(obj); }
};

