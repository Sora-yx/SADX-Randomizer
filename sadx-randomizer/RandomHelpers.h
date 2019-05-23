#pragma once

extern int character[6];
extern int level[18];

extern char stage;
extern char act;

extern "C" void randomizeCharacter();
extern "C" void randomizeStages();
extern "C" void randomstage(char stage, char act);
extern "C" bool isStageAllowedForCharacter(short characterID, char stageID, char actNumber);
