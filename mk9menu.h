#pragma once

enum eMenuItems {
	MENU_P1MODIFIER,
	MENU_P1MODIFIER_CHAR,
	MENU_P2MODIFIER,
	MENU_P2MODIFIER_CHAR,
	MENU_STAGE,
	MENU_STAGEMODIFIER,
	TOTAL_MENUS
};

struct menu {
	int p1Modifier;
	int p2Modifier;
	char* p1ModifierChar;
	char* p2ModifierChar;
	int stageModifier;
	char* stage;
};

void MK9Menu_Init();
void MK9Menu_Update();
void MK9Menu_Draw();
int  IsCharNPC(char* name);

struct menu MK9Menu_Get();