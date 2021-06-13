#pragma once
#include <taihen.h>
#include "draw.h"


enum eHooks {
	HOOK_FIGHTER,
	HOOK_VERSUS,
	HOOK_STAGE,
	HOOK_SCREEN,
	TOTAL_HOOKS
};

void InitHooks();
void KillHooks();



int sceDisplaySetFrameBuf_patched(const SceDisplayFrameBuf *pParam, int sync);