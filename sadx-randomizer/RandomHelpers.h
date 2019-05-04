#pragma once

extern int character[6];
extern int level[18];
extern bool Regular;

extern "C" void randomizeCharacter();
extern "C" void randomizeStages();
extern "C" bool isStageAllowedForCharacter(Characters characterID, int stageID);