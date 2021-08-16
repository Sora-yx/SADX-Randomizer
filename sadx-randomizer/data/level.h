#pragma once
#define AddSet(A, B) helperFunctions.ReplaceFile("system\\" A ".bin", "system\\sets\\" B ".bin")
#define AddCam(C, D) helperFunctions.ReplaceFile("system\\" C ".bin", "system\\cam\\" C ".bin")

void FixCasinoSoundEffects();
void Set_ZeroChase();
void BackRing_CheckAndApply();
void Check_Display_BackRing_Common(ObjectMaster* a1);
extern NJS_MODEL_SADX model_0;
extern NJS_OBJECT object_GoalRing;

extern NJS_TEXLIST GoalRingTextures;
void TwinkleCircuit_Init();
void init_E100Series();

