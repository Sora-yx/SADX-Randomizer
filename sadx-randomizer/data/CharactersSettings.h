#pragma once

void SetGammaTimer();  //force to 6 min instead of 3
void BigWeightHook(); //force to 2000g

void CheckAndSetUpgrades();
void FixCharacterSFX();

void SuperAuraStuff();

void LoadTails_AI_R();
void LoadTails_AI_Original(); //Normal AI (Tails Only)

void ShowActionButton();


void FixVictoryTailsVoice();
void Characters_Init();
int AmyCartImprovement();
int KnuxRadarEmeraldCheck();
void EmeraldRadar_R();
void CheckAndLoadSuperSonic_Tex(int curChara);

extern void PlayVoice_Original(int a1);
void FixAISFXJump();
extern int level[23];

void FixAISFXSonic();
void FixAISFXAmy();
void FixAISFXAmy2();
void FixAISFXAmy3();
void FixAISFXAmy4();
void FixAISFXAmy5();
void FixAISFXAmy6();


int GetCharacter0ID();
int GetCharacter1ID();

void ResultVoiceFix();

void Load_Cart_R();
void PlayCharaVoice_EmeraldGet(ObjectMaster* a1);
void SuperSonic_TransformationCheck();

void RosterBanCheck();

void initSuperSonicSettings();