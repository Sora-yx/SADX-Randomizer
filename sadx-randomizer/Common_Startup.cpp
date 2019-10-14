#include "stdafx.h"
#include "Utils.h"
#include "RandomHelpers.h"

HelperFunctions help;

void __cdecl Startup_Init(const char* path, const HelperFunctions& helperFunctions)
{

	//Initiliaze data
	help = helperFunctions; //so we can use it everywhere

	helperFunctions.ReplaceFile("system\\AVA_GTITLE0_E.PVM", "system\\textures\\AVA_GTITLE0_E.PVM"); //replace title screen
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\3000.wma", "system\\voices\\SuperSonicTransformation.wma"); //Introduce Super Sonic voice transformation
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\3001.wma", "system\\voices\\LoadAura.wma"); //Introduce Super Sonic Aura Sound.
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\2053.wma", "system\\voices\\StageLoad.wma"); //Introduce Stage Load Sound
	helperFunctions.ReplaceFile("system\\A_STAGE01_E.PVR", "system\\textures\\RandomTitleCard.pvr");

	helperFunctions.ReplaceFile("system\\ENDBG_SONIC_0.PVM", "system\\textures\\ENDBG_RANDOMIZER_0.pvmx"); //background credits

	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4000.wma", "system\\voices\\ReadyAnyTimeSonic.wma"); //Introduce Sonic Switch
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4001.wma", "system\\voices\\AlSetTails.wma"); //Introduce Tails Switch
	help.ReplaceFile("system\\sounddata\\voice_us\\wma\\4002.wma", "system\\voices\\ReadyAnyTimeAmy.wma"); //Introduce Tails Switch

}



NJS_TEXNAME MISSION_TEXNAME[1];
NJS_TEXLIST MISSION_TEXLIST = { arrayptrandlength(MISSION_TEXNAME) };
//bool TexturesLoaded = false;



void MissionObject(ObjectMaster* obj) {
	EntityData1* entity = obj->Data1;
	NJS_QUAD_TEXTURE MissionSprite = { 0, 0, 0, 0, 0, 0, 1, 0 };


	if (!MissedFrames) {
		njSetTexture(&MISSION_TEXLIST);
		SetDefaultAlphaBlend();
		Direct3D_SetZFunc(7u);
		Direct3D_EnableHudAlpha(1);
		NJS_COLOR color = { 0xFFFFFFFF };
		color.argb.a = entity->CharID;
		SetHudColorAndTextureNum(0, color);
		DrawRectPoints((NJS_POINT2*)& MissionSprite, 1);

		Direct3D_ResetZFunc();
	}
}