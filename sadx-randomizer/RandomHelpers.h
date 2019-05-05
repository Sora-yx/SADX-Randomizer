#pragma once

extern int character[6];
extern int level[18];

extern "C" void randomizeCharacter();
extern "C" void randomizeStages();
extern "C" bool isStageAllowedForCharacter(short characterID, char stageID, char actNumber);