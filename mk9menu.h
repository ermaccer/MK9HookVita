#pragma once

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