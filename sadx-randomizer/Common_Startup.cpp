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
	//ResizeTextureList(&CON_REGULAR_TEXLIST, 75);
}





int LoadTitleCardTexture_r(int param_1)

{
	int iVar1;
	char* pcVar2;
	int Character;
	int LvlAct;

	SoundManager_Delete2();
	dword_03b28114 = 0;
	ScreenTextureVer();
	SetFrameRateMode(1, 1);
	SetDefaultAlphaBlend();
	DisableFog();
	SetGlobalPoint2Col_Colors(0xff000000, 0xff000000, 0xff000000);
	Direct3D_SetNearFarPlanes(0xbf800000, 0xc53b8000);
	TitleCardStuff = 2;
	TitleCardStuff2 = 0;
	TitleCardDispTime = 0xb4;
	if (param_1 != 0) {
		TitleCardDispTime = (int)param_1;
	}

	if (CurrentLevel > 15 || CurrentLevel > 25)
		GetLevelType = 1;
	else
		GetLevelType = 0;


		/*DWORD_03c53ac4 = &;0091c548

	iVar1 = njLoadTexture_Wrapper(*DWORD_03c53ac4);
	return (int)(iVar1 != -1) - 1;*/

}


