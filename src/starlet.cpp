#include "starlet.h"

#include <MinHook.h>

/* change this to suit the hooking lib of your choice */

bool sx_init()
{
	return MH_Initialize() == MH_OK;
}

bool sx_hook_method(void **original, void *hook)
{
	void *og = *original;

	if (MH_CreateHook(og, hook, original) != MH_OK)
		return false;

	return MH_EnableHook(og) == MH_OK;
}

/* detours!
bool sx_hook_method(void **original, void *hook)
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(original, hook);
	return DetourTransactionCommit() == NO_ERROR;
}
*/