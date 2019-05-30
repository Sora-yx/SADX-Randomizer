#pragma once

extern int character[6];
extern int level[18];

extern char stage;
extern char act;

extern "C" void randomstage(char stage, char act);
extern "C" void quitstage();
extern "C" bool isStageAllowedForCharacter(short characterID, char stageID, char actNumber);

extern "C" void CancelResetPosition();
extern "C" void showcredits();
extern "C" void regularbanned();
extern "C" void StartLevelCutscene_(__int16 a1);

VoidFunc(PauseQuitThing, 0x413f70);

DataPointer(char, Emblem, 0x974AE0);
DataPointer(unsigned char, LevelList, 0x3B2C5F8);
DataPointer(unsigned char, SelectedCharacter, 0x3B2A2FD);
DataPointer(char, RNGDoor, 0x3C7457C);