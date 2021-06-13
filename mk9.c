#include "mk9.h"
#include <psp2/ctrl.h> 
#include <psp2/kernel/threadmgr.h> 
#include "draw.h"
#include "mk9menu.h"
tai_hook_ref_t HOOK_REFS[TOTAL_HOOKS];
int			   HOOK_IDS[TOTAL_HOOKS];


int HookSetCharacter(int player, int unk, char* name)
{
	if (player == 0)
	{
		if (MK9Menu_Get().p1Modifier)
			name = MK9Menu_Get().p1ModifierChar;
	}

	return TAI_CONTINUE(int, HOOK_REFS[0], player, unk, name);
}

// will assign scorpion vs to any non playable char
int HookLoadPlayerVersusScreen(int a1, char* name, int a3, int a4)
{
	if (IsCharNPC(name))
		name = "CHAR_Scorpion";

	return TAI_CONTINUE(int, HOOK_REFS[1], a1, name, a3, a4);
}


int HookSetStage(char* name)
{
	if (MK9Menu_Get().stageModifier)
		name = MK9Menu_Get().stage;

	return TAI_CONTINUE(int, HOOK_REFS[2], name);
}




void InitHooks()
{

	tai_module_info_t tai_info;
	tai_info.size = sizeof(tai_module_info_t);
	taiGetModuleInfo(TAI_MAIN_MODULE, &tai_info);


	HOOK_IDS[0] = taiHookFunctionOffset(&HOOK_REFS[0], tai_info.modid, 0, 0x506D82, 1, HookSetCharacter);
	HOOK_IDS[1] = taiHookFunctionOffset(&HOOK_REFS[1], tai_info.modid, 0, 0x50889C, 1, HookLoadPlayerVersusScreen);
	HOOK_IDS[2] = taiHookFunctionOffset(&HOOK_REFS[2], tai_info.modid, 0, 0x506A48, 1, HookSetStage);
	HOOK_IDS[3] = taiHookFunctionImport(&HOOK_REFS[3], TAI_MAIN_MODULE, 0x4FAACD11, 0x7A410B64, sceDisplaySetFrameBuf_patched);
}

void KillHooks()
{
	for (int i = 0; i < TOTAL_HOOKS; i++)
		if (HOOK_IDS[i] >= 0) taiHookRelease(HOOK_IDS[i], HOOK_REFS[i]);
}

int sceDisplaySetFrameBuf_patched(const SceDisplayFrameBuf *pParam, int sync) {
	updateFrameBuf(pParam);
	setColor(WHITE, BLACK);


	MK9Menu_Draw();

	return TAI_CONTINUE(int, HOOK_REFS[3], pParam, sync);
}