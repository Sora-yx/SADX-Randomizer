#include "stdafx.h"
#include <shellapi.h>
#include <fstream>
#include <iostream>

#define AddVoices(A, B) helperFunctions.ReplaceFile("system\\sounddata\\voice_us\\wma\\" A ".wma", "system\\voices\\" B ".adx")
#define AddVoices2(A, B) helperFunctions.ReplaceFile("system\\sounddata\\voice_jp\\wma\\" A ".wma", "system\\voices\\" B ".adx")
extern bool SA2Voices;

static Trampoline* PlayVoice_t = nullptr;
extern int getCurVoice;

//randomize voices

static void __cdecl PlayRandomVoice(int a1)
{

	getCurVoice = rand() % 2045;
	a1 = getCurVoice;

	auto original = reinterpret_cast<decltype(PlayRandomVoice)*>(PlayVoice_t->Target());
	original(a1);
}



void PlayVoice_Original(int a1) {

	if (VoicesEnabled != 0) {
		CurrentVoiceNumber = a1;
	}

	return;
}

bool DoesConfigExist(const std::string& file)
{
	std::ifstream fichier(file.c_str());
	return !fichier.fail();
}


void SA2VoicesCheck() {

	HMODULE IsSA2Voices = GetModuleHandle(L"SA2-Voices");

	const char* Path = "mods\\SA2 Voices\\system\\sounddata\\voice_us\\wma\\7010.adx";

	if (IsSA2Voices && RNGVoices)
		SA2Voices = true;

	if (!DoesConfigExist("RandoConfig.txt") && RNGVoices)
	{
		std::ofstream ConfigFile("RandoConfig.txt");

		if (SA2Voices)
		{
			ConfigFile << "Sa2Voices=1";
			ConfigFile.close();
			return;
		}

		int msgboxID = MessageBoxA(WindowHandle, "It looks like you have the Randomized Voices option enabled, but you don't have the Sonic Adventure 2 voices, would you like to download them? (Once the download is complete, simply extract and install it just like a regular mod and don't forget to enable it on the mod loader.)", "SADX Randomizer", MB_YESNO);
		switch (msgboxID)
		{
		case IDYES:
			ShellExecute(0, 0, L"https://gamebanana.com/dl/453829", 0, 0, SW_SHOW);
			ConfigFile << "Sa2Voices=1";
			ConfigFile.close();
			Exit();
			break;
		case IDNO:
		default:
			ConfigFile << "Sa2Voices=0";
			ConfigFile.close();
			break;
		}
	}

	return;
}

void __cdecl StartupVoices_Init(const char* path, const HelperFunctions& helperFunctions) {

	//ENGLISH VOICES
	AddVoices("4010", "BigVictory"); //Add Big Victory Stage voice
	AddVoices("4011", "BigWouhou"); //Add Big Victory Boss / other voice
	AddVoices("4012", "EggmanYosh"); //Add Eggman Victory voice

	AddVoices("5000", "Bounce"); //Introduce Sonic bounce sfx
	AddVoices("5001", "BackRingHit");
	AddVoices("5002", "ChaoCry1");
	AddVoices("5003", "ChaoCry2");
	AddVoices("5004", "teleport");


	AddVoices("5010", "Congratulations_Sonic");
	AddVoices("5011.", "Congratulations_Tails");
	AddVoices("5012", "sCongratulations_Knux");
	AddVoices("5013", "Congratulations_Amy");

	AddVoices("5020", "amyyesyes");
	AddVoices("5021", "biggotit");
	AddVoices("5022", "bighehe");
	AddVoices("5023", "gammagetitem");

	AddVoices("6010", "ZeroArm");
	AddVoices("6011", "ZeroHit");
	AddVoices("6013", "ZeroTarget");
	AddVoices("6014", "ZeroThink");

	//Use 6050 Here

	//JP VOICES
	AddVoices2("4010", "BigVictory"); //Add Big Victory Stage voice
	AddVoices2("4011", "BigWouhou"); //Add Big Victory Boss / other voice
	AddVoices2("4012", "EggmanYosh"); //Add Eggman Victory voice

	AddVoices2("5000", "Bounce"); //Introduce Sonic bounce sfx
	AddVoices2("5001", "BackRingHit");
	AddVoices2("5002", "ChaoCry1");
	AddVoices2("5003", "ChaoCry2");
	AddVoices2("5004", "teleport");

	AddVoices2("5010", "Congratulations_Sonic");
	AddVoices2("5011.", "Congratulations_Tails");
	AddVoices2("5012", "sCongratulations_Knux");
	AddVoices2("5013", "Congratulations_Amy");

	AddVoices2("5020", "amyyesyes");
	AddVoices2("5021", "biggotit");
	AddVoices2("5022", "bighehe");
	AddVoices2("5023", "gammagetitem");

	WriteCall((void*)0x45be57, PlayVoice_Original);

	if (RNGVoices)
	{
		PlayVoice_t = new Trampoline((int)PlayVoice, (int)PlayVoice + 0x5, PlayRandomVoice);
		//SA2VoicesCheck();
	}

	if (isAIAllowed)
	{
		WriteCall((void*)0x47fc9e, FixAISFXGamma);
		WriteCall((void*)0x483294, FixAISFXGamma);
		WriteCall((void*)0x47fd07, FixAISFXGamma2);
		WriteCall((void*)0x481dac, FixAISFXGamma3);
		WriteCall((void*)0x47fcca, FixAISFXGamma4);

		//fix victory voice result (ai swap)

		WriteData<5>((void*)0x414280, 0x90); //remove Sonic Voice
		WriteData<5>((void*)0x414264, 0x90); //Remove Sonic Boss Voice;
		WriteData<5>((void*)0x41560d, 0x90); //remove knux play voice
		WriteData<5>((void*)0x41562a, 0x90); //remove knux victory boss voice
		WriteData<5>((void*)0x41567e, 0x90); //remove Amy play voice
		WriteData<5>((void*)0x415776, 0x90); //remove delete sound big-
	}
}