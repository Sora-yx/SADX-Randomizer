#pragma once

extern int character[6];
extern int level[20];
extern int SameLevel[20];
extern int CharacterCopy;
extern int RNGSong;

extern char stage;
extern char act;

extern char param_1;
extern char param_2;
extern int SonicRand;

extern "C" void randomstage(char stage, char act);
extern "C" void randomacts();
extern "C" void BigWeightHook();


extern "C" void SetGammaTimer(char param_1, char param_2);
extern "C" void DisableTimeStuff();
extern "C" void RandomVoice();
extern "C" void RandomMusic();

extern "C" void CancelResetPosition();

extern "C" void SuperAuraStuff();
extern "C" void SuperSonicStuff();
extern "C" void LoadEggmanAI();
extern "C" void LoadZero();

extern "C" void credits();
extern "C" void HotShelterSecretSwitch();
extern "C" void FixGammaBounce();


VoidFunc(PauseQuitDisplay, 0x415450);
VoidFunc(E101ShootThing, 0x567ac0);
VoidFunc(Tails_CheckRaceResult, 0x461560);

VoidFunc(SetupZero, 0x4b3eb0);
VoidFunc(CheckLoadZero, 0x486a40);


DataPointer(char, BossHP, 0x3C58150);
DataPointer(char, Emblem, 0x974AE0);
DataPointer(unsigned char, LevelList, 0x3B2C5F8);
DataPointer(unsigned char, SelectedCharacter, 0x3B2A2FD);
DataPointer(int, BigWeight, 0x3C52510);
DataPointer(char, RNGDoor, 0x3C7457C);
DataPointer(char, FirstHotShelterSwitch, 0x3c72a40);
DataPointer(char, SomethingAboutHotShelterSwitch, 0x3c72a4c);
DataPointer(char, SecretWaterSwitch, 0x3C5B37E);