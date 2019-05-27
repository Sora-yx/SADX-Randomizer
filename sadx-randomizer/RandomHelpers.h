#pragma once

extern int character[6];
extern int level[18];
extern int actrng[2];
extern int actHS[2];
extern int actIC[2];

extern char stage;
extern char act;

void randomizeCharacter();
void randomizeStages();
void randomstage(char stage, char act);
void nextcutscene(char stage, char act);
void quitstage();
void credits();
void acts();
bool isStageAllowedForCharacter(short characterID, char stageID, char actNumber);

DataPointer(char, Emblem, 0x974AE0);
DataPointer(unsigned char, LevelList, 0x3B2C5F8);
DataPointer(unsigned char, SelectedCharacter, 0x3B2A2FD);