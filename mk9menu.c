#include "mk9menu.h"
#include <stdio.h>
#include <vitasdk.h>
#include "draw.h"

int menu_active = 1;
int menu_pos = 0;
int menu_items = 4;


char* szCharacters[] = {
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
	"NPC_JC_Meat",
	"NPC_TarkatanSoldierA",
	"NPC_Zombie_Male",

	"CHAR_Goro",
	"CHAR_Kintaro",
	"CHAR_ShaoKahn",
	"CHAR_Baraka",
	"CHAR_Baraka_B",
	"CHAR_CyberZero",
	"CHAR_CyberZero_C",
	"CHAR_Cyrax",
	"CHAR_Cyrax_B",
	"CHAR_Cyrax_C",
	"CHAR_Cyrax_CT",
	"CHAR_Ermac",
	"CHAR_Ermac_B",
	"CHAR_Ermac_C",
	"CHAR_Ermac_D",
	"CHAR_Ermac_E",
	"CHAR_FreddyKrueger",
	"CHAR_Jade",
	"CHAR_Jade_B",
	"CHAR_Jade_C",
	"CHAR_Jade_D",
	"CHAR_Jax",
	"CHAR_Jax_B",
	"CHAR_JohnnyCage",
	"CHAR_JohnnyCage_B",
	"CHAR_Kabal",
	"CHAR_Kabal_B",
	"CHAR_Kano",
	"CHAR_Kano_B",
	"CHAR_Kenshi",
	"CHAR_Kenshi_B",
	"CHAR_Kitana",
	"CHAR_Kitana_B",
	"CHAR_Kitana_C",
	"CHAR_Kitana_CT",
	"CHAR_Kitana_D",
	"CHAR_Kratos",
	"CHAR_Kratos_B",
	"CHAR_KungLao",
	"CHAR_KungLao_B",
	"CHAR_LiuKang",
	"CHAR_LiuKang_B",
	"CHAR_Mileena",
	"CHAR_Mileena_B",
	"CHAR_Mileena_C",
	"CHAR_Mileena_D",
	"CHAR_Mileena_E",
	"CHAR_Nightwolf",
	"CHAR_Nightwolf_B",
	"CHAR_Noob",
	"CHAR_Noob_B",
	"CHAR_Noob_D",
	"CHAR_Noob_E",
	"CHAR_QuanChi",
	"CHAR_QuanChi_B",
	"CHAR_Raiden",
	"CHAR_Raiden_B",
	"CHAR_Rain",
	"CHAR_Rain_E",
	"CHAR_Reptile",
	"CHAR_Reptile_B",
	"CHAR_Reptile_C",
	"CHAR_Reptile_D",
	"CHAR_Reptile_E",
	"CHAR_Scorpion",
	"CHAR_Scorpion_B",
	"CHAR_Scorpion_C",
	"CHAR_Scorpion_D",
	"CHAR_Scorpion_E",
	"CHAR_Sektor",
	"CHAR_Sektor_B",
	"CHAR_Sektor_C",
	"CHAR_ShangTsung",
	"CHAR_ShangTsung_B",
	"CHAR_Sheeva",
	"CHAR_Sheeva_B",
	"CHAR_Sindel",
	"CHAR_Sindel_B",
	"CHAR_Skarlet",
	"CHAR_Skarlet_B",
	"CHAR_Skarlet_C",
	"CHAR_Skarlet_D",
	"CHAR_Smoke",
	"CHAR_Smoke_B",
	"CHAR_Smoke_CT",
	"CHAR_Smoke_D",
	"CHAR_Smoke_E",
	"CHAR_Sonya",
	"CHAR_Sonya_B",
	"CHAR_Stryker",
	"CHAR_Stryker_B",
	"CHAR_SubZero",
	"CHAR_SubZero_B",
	"CHAR_SubZero_C",
	"CHAR_SubZero_D",
	"CHAR_SubZero_E",
	"CHAR_SubZero_F",
};

char* szStages[] = {
	"BGND_Armory",
	"BGND_BellTower",
	"BGND_BioViewer",
	"BGND_ChallengeBalance",
	"BGND_ChallengeSlice",
	"BGND_ChallengeTower",
	"BGND_Courtyard",
	"BGND_CourtyardN",
	"BGND_DeadPool",
	"BGND_Desert",
	"BGND_FleshPits",
	"BGND_GorosLair",
	"BGND_Graveyard",
	"BGND_Hell",
	"BGND_KahnsColiseum",
	"BGND_KombatTomb",
	"BGND_KOTH",
	"BGND_KOTH_S",
	"BGND_Krypt",
	"BGND_LivingForest",
	"BGND_Nekropolis",
	"BGND_Pit",
	"BGND_PitBottom",
	"BGND_PitDay",
	"BGND_RnD_EnvTest",
	"BGND_RooftopDawn",
	"BGND_RooftopDay",
	"BGND_RooftopDusk",
	"BGND_SKThrone",
	"BGND_SoulChamber",
	"BGND_STGardens",
	"BGND_STGardensN",
	"BGND_Street",
	"BGND_STThrone",
	"BGND_Subway",
	"BGND_Temple",
	"BGND_Tower",
	"BGND_Wastelands"
};
int char_index = 0;
int char_index_p2 = 0;
int stage_index = 0;
int stage_total = 0;
int char_total = 5;

struct menu TheMenu;

void MK9Menu_Init()
{
	menu_items = TOTAL_MENUS;
	TheMenu.p1Modifier = 0;
	TheMenu.p2Modifier = 0;
	TheMenu.p1ModifierChar = szCharacters[0];
	TheMenu.p2ModifierChar = szCharacters[0];
	TheMenu.stageModifier = 0;
	TheMenu.stage = szStages[0];
	char_total = sizeof(szCharacters) / sizeof(szCharacters[0]);
	stage_total = sizeof(szStages) / sizeof(szStages[0]);
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
			case MENU_P1MODIFIER: // p1 modifier
				TheMenu.p1Modifier ^= 1;
				break;
			case MENU_P2MODIFIER: // p1 modifier
				TheMenu.p2Modifier ^= 1;
				break;
			case MENU_STAGE: // Stage Modifer
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
			case MENU_P1MODIFIER_CHAR: // p1 modifier char
				char_index--;

				if (char_index > char_total - 1)
					char_index = 0;

				if (char_index < 0)
					char_index = char_total - 1;

				TheMenu.p1ModifierChar = szCharacters[char_index];
				break;
			case MENU_P2MODIFIER_CHAR: // p1 modifier char
				char_index_p2--;

				if (char_index_p2 > char_total - 1)
					char_index_p2 = 0;

				if (char_index_p2 < 0)
					char_index_p2 = char_total - 1;

				TheMenu.p2ModifierChar = szCharacters[char_index_p2];
				break;
			case MENU_STAGE:
				stage_index--;

				if (stage_index > stage_total - 1)
					stage_index = 0;

				if (stage_index < 0)
					stage_index = stage_total - 1;

				TheMenu.stage = szStages[stage_index];
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
			case MENU_P1MODIFIER_CHAR: // p1 modifier char
				char_index++;

				if (char_index > char_total - 1)
					char_index = 0;

				if (char_index < 0)
					char_index = char_total - 1;

				TheMenu.p1ModifierChar = szCharacters[char_index];
				break;
			case MENU_P2MODIFIER_CHAR: // p1 modifier char
				char_index_p2++;

				if (char_index_p2 > char_total - 1)
					char_index_p2 = 0;

				if (char_index_p2 < 0)
					char_index_p2 = char_total - 1;

				TheMenu.p2ModifierChar = szCharacters[char_index_p2];
				break;
			case MENU_STAGEMODIFIER:
				stage_index++;

				if (stage_index > stage_total - 1)
					stage_index = 0;

				if (stage_index < 0)
					stage_index = stage_total - 1;

				TheMenu.stage = szStages[stage_index];
				break;
			default:
				break;
			}
		}
	}

}

void MK9Menu_Draw()
{
	if (menu_active)
	{
		drawStringF(10, 20, "MK9HookVita (0.1) by ermaccer (L1+SELECT on/off)");
		int baseY = 60;
		char buff[256];
		memset(buff, 0, sizeof(buff));
		char* itm = " ";
		for (int i = 0; i < TOTAL_MENUS; i++)
		{
			if (menu_pos == i)
				itm = "-->";
			else
				itm = " ";
			switch (i)
			{
			case MENU_P1MODIFIER: // p1 modifier
				sprintf(buff, "%sP1 Modifier - %d", itm, TheMenu.p1Modifier);
				break;
			case MENU_P1MODIFIER_CHAR: // p1 modifier char
				sprintf(buff, "%sP1 Character - %s (%d/%d)", itm, TheMenu.p1ModifierChar,char_index + 1, char_total);
				break;
			case MENU_P2MODIFIER: // p2 modifier
				sprintf(buff, "%sP2 Modifier - %d", itm, TheMenu.p2Modifier);
				break;
			case MENU_P2MODIFIER_CHAR: // p2 modifier char
				sprintf(buff, "%sP2 Character - %s (%d/%d)", itm, TheMenu.p2ModifierChar, char_index_p2 + 1, char_total);
				break;
			case MENU_STAGE: // Stage Modifer
				sprintf(buff, "%sStage Modifier - %d", itm, TheMenu.stageModifier);
				break;
			case MENU_STAGEMODIFIER: // Stage Modifer stage
				sprintf(buff, "%sStage - %s (%d/%d)", itm, TheMenu.stage, stage_index + 1, stage_total);
				break;
			default:
				break;
			}
			drawStringF(10, baseY + (20 * i), buff);

		}
	}

}

int IsCharNPC(char * name)
{
	static const char* szNPCs[] = {
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
	"NPC_JC_Meat",
	"NPC_TarkatanSoldierA",
	"NPC_Zombie_Male",

	"CHAR_Goro",
	"CHAR_Kintaro",
	"CHAR_ShaoKahn",
	};
	for (int i = 0; i < sizeof(szNPCs) / sizeof(szNPCs[0]); i++)
	{
		if (strcmp(name, szNPCs[i]) == 0)
			return 1;
	}



	return 0;
}

struct menu MK9Menu_Get()
{
	return TheMenu;
}
