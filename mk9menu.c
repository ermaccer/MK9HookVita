#include "mk9menu.h"
#include <vitasdk.h>
#include "draw.h"

int menu_active = 1;
int menu_pos = 0;
int menu_items = 4;


const char* szCharacters[] = {
	"NPC_Tremor",
	"NPC_BaseMale",
	"NPC_ClassicJade",
	"NPC_ClassicNoob",
	"NPC_ClassicReptile",
	"NPC_ClassicSmoke",
	"NPC_CyberNinja_LK4D4",
	"NPC_GenericFighterA",
	"NPC_GenericFighterB",
	"NPC_GL_Oni",
	"NPC_JC_Director",
	"NPC_TarkatanSoldierA",
	"NPC_Zombie_Male",
	"CHAR_Goro",
	"CHAR_Kintaro",
	"CHAR_ShaoKahn"
};
int char_index = 0;
int char_total = 5;

struct menu TheMenu;

void MK9Menu_Init()
{
	TheMenu.p1Modifier = 0;
	TheMenu.p2Modifier = 0;
	TheMenu.p1ModifierChar = szCharacters[0];
	TheMenu.p2ModifierChar = szCharacters[0];
	TheMenu.stageModifier = 0;
	TheMenu.stage = "BGND_Nekropolis";
	char_total = sizeof(szCharacters) / sizeof(szCharacters[0]);
}

void MK9Menu_Update()
{
	SceCtrlData pad;
	memset(&pad, 0, sizeof(pad));
	sceCtrlPeekBufferPositive(0, &pad, 1);

	if ((pad.buttons & SCE_CTRL_SELECT) && (pad.buttons & SCE_CTRL_LTRIGGER))
	{
		sceKernelDelayThread(1000000 / 10);
		menu_active ^= 1;
	}
	if (menu_active)
	{

		if (menu_pos > menu_items - 1)
			menu_pos = 0;
		if (menu_pos < 0)
			menu_pos = menu_items - 1;




		if (pad.buttons & SCE_CTRL_DOWN)
		{
			sceKernelDelayThread(1000000 / 9);
			menu_pos++;
		}
		if (pad.buttons & SCE_CTRL_UP)
		{
			sceKernelDelayThread(1000000 / 9);
			menu_pos--;
		}

		if (pad.buttons & SCE_CTRL_CROSS)
		{
			sceKernelDelayThread(1000000 / 10);
			switch (menu_pos)
			{
			case 0: // p1 modifier
				TheMenu.p1Modifier ^= 1;
				break;
			case 2: // Stage Modifer
				TheMenu.stageModifier ^= 1;
				break;
			default:
				break;
			}
		}

		if (pad.buttons & SCE_CTRL_LEFT)
		{
			sceKernelDelayThread(1000000 / 10);
			switch (menu_pos)
			{
			case 1: // p1 modifier char
				char_index--;

				if (char_index > char_total - 1)
					char_index = 0;

				if (char_index < 0)
					char_index = char_total - 1;

				TheMenu.p1ModifierChar = szCharacters[char_index];
				break;
			default:
				break;
			}
		}
		if (pad.buttons & SCE_CTRL_RIGHT)
		{
			sceKernelDelayThread(1000000 / 10);
			switch (menu_pos)
			{
			case 1: // p1 modifier char
				char_index++;

				if (char_index > char_total - 1)
					char_index = 0;

				if (char_index < 0)
					char_index = char_total - 1;

				TheMenu.p1ModifierChar = szCharacters[char_index];
				break;
			default:
				break;
			}
		}

		if (pad.buttons & SCE_CTRL_TRIANGLE)
		{

			//play_as_tremor ^= 1;


		}
		if (pad.buttons & SCE_CTRL_SQUARE)
		{
			sceKernelDelayThread(1000000 / 10);
			//nekropolis_stage ^= 1;

		}
	}

}

void MK9Menu_Draw()
{
	if (menu_active)
	{
		drawStringF((1 - 2 / 2) * (896 - 16), 20, "MK9HookVita (test) by ermaccer (L1+SELECT on/off)");
		int baseY = 40;
		char buff[256];
		memset(buff, 0, sizeof(buff));
		char* itm = " ";
		for (int i = 0; i < menu_items; i++)
		{
			if (menu_pos == i)
				itm = "-->";
			else
				itm = " ";
			switch (i)
			{
			case 0: // p1 modifier
				sprintf(buff, "%sP1 Modifier - %d", itm, TheMenu.p1Modifier);
				break;
			case 1: // p1 modifier char
				sprintf(buff, "%sP1 Character - %s (%d/%d)", itm, TheMenu.p1ModifierChar,char_index + 1, char_total);
				break;
			case 2: // Stage Modifer
				sprintf(buff, "%sStage Modifier - %d", itm, TheMenu.stageModifier);
				break;
			case 3: // Stage Modifer stage
				sprintf(buff, "%sStage - %s", itm, TheMenu.stage);
				break;
			default:
				break;
			}
			drawStringF((1 - 2 / 2) * (896 - 16), baseY + (20 * i), buff);

		}
	}

}

int IsCharNPC(char * name)
{

	for (int i = 0; i < sizeof(szCharacters) / sizeof(szCharacters[0]); i++)
	{
		if (strcmp(name, szCharacters[i]) == 0)
			return 1;
	}



	return 0;
}

struct menu MK9Menu_Get()
{
	return TheMenu;
}
