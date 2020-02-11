#pragma once
#include "stdafx.h"

//Major function of random acts, depending on the characters and the stages.
 //void randomacts();

//Custom layout Act
void EC_Layout();
void IC_Layout();
void Casino_Layout();
void TwinklePark_Layout();
void SpeedHighway_Layout();
void RedMountain_Layout();
void HotShelter_Layout();
void WindyValley_Layout();
void SkyDeck_Layout();
void LW_Layout();
void FinalEgg_Layout();

//Camera fixs.
void CamSpeedHighway();
void CamRedMountain();
void CamFinalEgg();
void CamHotShelter();
void EC_Cam();
void Cam_WV();
void Cam_SkyDeck();
void Cam_LW();
void TP_CAM();

int HedgehogHammerTrick();
void FixGoldenAndCoin();
int Chaos6_ReturnCharacter();
void Chaos6_Layout(); 
int Switch_Gravity();
void LoadTriggerObjHS();
void TriggerObjHS_Main(ObjectMaster* obj);