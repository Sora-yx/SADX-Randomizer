#include "stdafx.h"

int FastTimer = 0;

extern "C" {

	__declspec(dllexport) void SpawnSpring() {
		int number = rand() % 2;

		ObjectMaster* spring = LoadObject((LoadObj)2, 2, SpringB_Main);
		spring->Data1->Rotation = { rand() % 0x8000, rand() % 0x8000, rand() % 0x8000 };
		spring->Data1->Scale.y = rand() % 4 + 1 * 2.5;
		spring->Data1->Position = EntityData1Ptrs[0]->Position;

		if (number)
		{
			ObjectMaster* spring2 = LoadObject((LoadObj)2, 2, SpringB_Main);
			spring2->Data1->Rotation = { rand() % 0x8000, rand() % 0x8000, rand() % 0x8000 };
			spring2->Data1->Scale.y = rand() % 5 + 10 * 2.5;
			spring2->Data1->Position = EntityData1Ptrs[0]->Position;
			spring2->Data1->Position.y += rand() % 10 + 1 * 9;
			spring2->Data1->Position.z += rand() % 10 + 1 * 9;
		}

		return;
	}

	__declspec(dllexport) void SpawnSpeedPad() {
		int number = rand() % 2;

		ObjectMaster* speed = LoadObject((LoadObj)3, 3, DashPanel_Main);
		speed->Data1->Scale.x = rand() % 5 + 10 * 2.5;
		speed->Data1->Rotation.y = rand() % 0x8000;
		speed->Data1->Position = EntityData1Ptrs[0]->Position;

		if (number)
		{
			ObjectMaster* speed2 = LoadObject((LoadObj)3, 3, DashPanel_Main);
			speed2->Data1->Scale.x = rand() % 5 + 10 * 2.5;
			speed2->Data1->Rotation.y = rand() % 0x8000;
			speed2->Data1->Position = EntityData1Ptrs[0]->Position;
			speed2->Data1->Position.z += rand() % 10 + 1 * 9;
		}

		return;
	}

	__declspec(dllexport) void SpawnSpikeBall() {
		int number = rand() % 2;

		ObjectMaster* spike = LoadObject((LoadObj)6, 3, SwingSpikeBall_Load);
		spike->Data1->Rotation.y = rand() % 80 + 1000;
		spike->Data1->Scale.x = rand() % 5 + 10 * 2.5;
		spike->Data1->Position = EntityData1Ptrs[0]->Position;
		spike->Data1->Position.y += 2;
		spike->Data1->Position.x += 80;

		if (number) {
			ObjectMaster* spike2 = LoadObject((LoadObj)6, 3, SwingSpikeBall_Load);
			spike2->Data1->Rotation.y = rand() % 80 + 1000;
			spike2->Data1->Scale.x = rand() % 5 + 10 * 2.5;
			spike2->Data1->Position = EntityData1Ptrs[0]->Position;
			spike2->Data1->Position.y += 2;
			spike2->Data1->Position.z += rand() % 10 + 1 * 9;
		}

		return;
	}

	__declspec(dllexport) void StopPlayer() {
		CharObj2Ptrs[0]->Speed = { 0, 0, 0 };
		return;
	}

	__declspec(dllexport) void SuperJump() {
		CharObj2Ptrs[0]->Speed.y = CharObj2Ptrs[0]->PhysicsData.VSpeedCap;
		return;
	}

	__declspec(dllexport) void GottaGoFast() {
		FastTimer = 120;
		return;
	}


	__declspec(dllexport) void HurtPlayer() {
		if (Rings > 0)
			return HurtCharacter(0);
	}

	__declspec(dllexport) void GivePowerUP(int id) {

		if (id < 0 || id > 8) //failsafe
			id = rand() % 9;

		if (!id)
			GiveSpeedShoes(EntityData1Ptrs[0]); //fix funny crash
		else
			ItemBoxPowerups[id].Function(EntityData1Ptrs[0]);

		DoThingWithItemBoxPowerupIndex(id);
	}

	__declspec(dllexport) void GrowCharacter() {
		for (int i = 0; i < 21; i++) {
			SONIC_OBJECTS[i]->scl[0] = 4;
			SONIC_OBJECTS[i]->scl[1] = 4;
			SONIC_OBJECTS[i]->scl[2] = 4;
		}
		return;
	}


	__declspec(dllexport) void ShrinkCharacter() {
		for (int i = 0; i < 21; i++) {
			SONIC_OBJECTS[i]->scl[0] = 0.5;
			SONIC_OBJECTS[i]->scl[1] = 0.5;
			SONIC_OBJECTS[i]->scl[2] = 0.5;
		}
		return;
	}


	__declspec(dllexport) void SwapMusic(int id) {

		if (id < 0 || id > 124)
			id = rand() % 125; //failsafe

		CurrentSong = id;
		LastSong = CurrentSong;
		return;
	}


	__declspec(dllexport) void ManiaPlayVoice(int id) {
		if (id < 0 || id > 2042) //failsafe
			id = rand() % 2043;

		PlayVoice_R(id);
		return;
	}
}

void RandomMadnessOnFrames() {
	if (!CharObj2Ptrs[0] || !vsChat || GameState != 15 || CurrentLevel == LevelIDs_SkyChase1 || CurrentLevel == LevelIDs_SkyChase2 || CurrentLevel >= LevelIDs_SSGarden)
		return;

	if (FastTimer > 0) {
		FastTimer--;
		CharObj2Ptrs[0]->Speed.x = CharObj2Ptrs[0]->PhysicsData.HSpeedCap;
	}
}

void InitVsChat(const char* path)
{
	if (vsChat) {
		char buf[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH, buf);
		SetCurrentDirectoryA(path);
		HMODULE hm = LoadLibraryA("SADXVsChat.dll");
		if (hm == NULL)
		{
			SetCurrentDirectoryA(buf);
			MessageBoxA(WindowHandle, "SADX Vs Twitch Chat: Error, failed to load helper DLL, Chat Command will not function!", "SADX Randomizer Error", MB_ICONINFORMATION);
			return;
		}
		GetProcAddress(hm, "Main")();
		SetCurrentDirectoryA(buf);
	}
}