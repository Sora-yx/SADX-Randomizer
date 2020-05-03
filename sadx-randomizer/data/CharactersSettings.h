#pragma once

void SetGammaTimer();  //force to 6 min instead of 3
void BigWeightHook(); //force to 2000g

extern int CurrentAI;
extern short CurrentMission;

void AllUpgrades();
void FixCharacterSFX();

void SuperAuraStuff();

void LoadTails_AI_R();
void LoadTails_AI_Original(); //Normal AI (Tails Only)

void ShowActionButton();
VoidFunc(PushMSIcon, 0x425e6d);
VoidFunc(CharSel_LoadThing, 0x512bc0);

FunctionPointer(ObjectMaster*, CheckLoadBird, (), 0x4C6820);
DataPointer(float, EggViperFloatThing, 0x3c6e330);
DataPointer(char, InitUpgrade, 0x3c5a954);
DataPointer(int, BigWeight, 0x3C52510);


void FixVictoryTailsVoice();
void Characters_Management();
void character_settings_onFrames();
int AmyCartImprovement();
int KnuxRadarEmeraldCheck();
void EmeraldRadar_R();

extern void PlayVoice_R(int a1);
void FixAISFXJump();
extern int level[23];

void FixAISFXSonic();
void FixAISFXAmy();
void FixAISFXAmy2();
void FixAISFXAmy3();
void FixAISFXAmy4();
void FixAISFXAmy5();
void FixAISFXAmy6();
VoidFunc(SomethingAboutWater2, 0x4497b6);

int GetCharacter0ID();
int GetCharacter1ID();

void ResultVoiceFix();

void Load_Cart_R();
DataPointer(char, EmeraldKnuxCheck, 0x3c52c04);
void PlayCharaVoice_EmeraldGet(ObjectMaster* a1);

enum CharacterStageVersion2 {

	NormalCheck = -1,
	AmyTPCheck,
	BigTPCheck,
	SonicSHCheck,
	TailsSHCheck,
	SonicFECheck,
	AmyFECheck,
	AmyHSCheck,
	BigHSCheck
};