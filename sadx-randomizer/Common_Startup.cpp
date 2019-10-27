#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"

HelperFunctions help;

NJS_TEXNAME Missions[10];
int CurrentMission = 0;

void LoadStageMissionImage_r() {
	if (GetLevelType) {
		StageMissionTexlist.textures = Missions;
		StageMissionTexlist.nbTexture = LengthOfArray(Missions);
		LoadPVM("textures\\Missions", &StageMissionTexlist);
		MissionSpriteAnim.texid = CurrentMission;

		ObjectMaster *obj = LoadObject(LoadObj_Data1, 6, (ObjectFuncPtr)0x457B60);
		obj->Data1->InvulnerableTime = 120;
		obj->Data1->Position.x = 320.0;
		obj->Data1->Position.y = 360.0;
		obj->DeleteSub = FreeStageMissionImage;
	}
}

int LoadTitleCardTexture_r(int minDispTime) {
	SoundManager_Delete2();
	dword_03b28114 = 0;
	ScreenTextureVer();
	SetFrameRateMode(1, 1);
	SetDefaultAlphaBlend();
	DisableFog();
	SetGlobalPoint2Col_Colors(0xff000000, 0xff000000, 0xff000000);
	Direct3D_SetNearFarPlanes(-1.0, -3000.0);
	TitleCardStuff = 2;
	TitleCardStuff2 = 0;
	GetLevelType = 1;

	TitleCardDispTime = 180;
	if (minDispTime) {
		TitleCardDispTime = minDispTime;
	}

	LoadPVM("textures\\RandomTitleCard", &CurrentCardTexture);
	CurrentCardTexturePtr = &CurrentCardTexture;

	return 1;
}

void __cdecl Startup_Init(const char* path, const HelperFunctions& helperFunctions)
{
	//Initiliaze data
	help = helperFunctions; //so we can use it everywhere

	helperFunctions.ReplaceFile("system\\AVA_GTITLE0_E.PVM", "system\\textures\\AVA_GTITLE0_E.PVM"); //replace title screen
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\3000.wma", "system\\voices\\SuperSonicTransformation.wma"); //Introduce Super Sonic voice transformation
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\3001.wma", "system\\voices\\LoadAura.wma"); //Introduce Super Sonic Aura Sound.
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\2053.wma", "system\\voices\\StageLoad.wma"); //Introduce Stage Load Sound

	helperFunctions.ReplaceFile("system\\ENDBG_SONIC_0.PVM", "system\\textures\\ENDBG_RANDOMIZER_0.pvmx"); //background credits

	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4000.wma", "system\\voices\\SonicHereWeGo.wma"); //Introduce Sonic Switch
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4001.wma", "system\\voices\\TailsLeaveItToMe.wma"); //Introduce Tails Switch
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4002.wma", "system\\voices\\KnuxGotIt.wma"); //Introduce Knux Switch
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4003.wma", "system\\voices\\AmyHereWeGo.wma"); //Introduce Amy Switch
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4005.wma", "system\\voices\\EggmanSwap.wma"); //Introduce Amy Switch

	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4010.wma", "system\\voices\\BigVictory.wma"); //Add Big Victory Stage voice
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4011.wma", "system\\voices\\BigWouhou.wma"); //Add Big Victory Boss / other voice
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4012.wma", "system\\voices\\EggmanYosh.wma"); //Add Eggman Victory voice

	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\5000.wma", "system\\voices\\Bounce.wma"); //Introduce Sonic bounce sfx
	
	//help.ReplaceFile("system\\CON_REGULAR.pvm", "system\\textures\\CON_REGULAR_E.PVMX"); //Test

	WriteJump(j_LoadTitleCardTexture, LoadTitleCardTexture_r);
	WriteJump(LoadStageMissionImage, LoadStageMissionImage_r);
}