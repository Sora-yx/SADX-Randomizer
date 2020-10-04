#include "stdafx.h"

char oldRand = -1;
int Maniatimer = 0;

void RandomSpring(EntityData1* p1) {
	int number = rand() % 2;

	ObjectMaster* spring = LoadObject((LoadObj)2, 2, SpringB_Main);	
	spring->Data1->Rotation = { rand() % 0x8000, rand() % 0x8000, rand() % 0x8000 };
	spring->Data1->Scale.y = rand() % 4 + 1 * 2.5;
	spring->Data1->Position = p1->Position;

	if (number)
	{
		ObjectMaster* spring2 = LoadObject((LoadObj)2, 2, SpringB_Main);
		spring2->Data1->Rotation = { rand() % 0x8000, rand() % 0x8000, rand() % 0x8000 };
		spring2->Data1->Scale.y = rand() % 5 + 10 * 2.5;
		spring2->Data1->Position = p1->Position;
		spring2->Data1->Position.y += rand() % 10 + 1 * 9;
		spring2->Data1->Position.z += rand() % 10 + 1 * 9;
	}

	return;
}

void RandomSpeedPad(EntityData1* p1) {
	int number = rand() % 2;

	ObjectMaster* speed = LoadObject((LoadObj)3, 3, DashPanel_Main);
	speed->Data1->Scale.x = rand() % 5 + 10 * 2.5;
	speed->Data1->Rotation.y = rand() % 0x8000;
	speed->Data1->Position = p1->Position;

	if (number)
	{
		ObjectMaster* speed2 = LoadObject((LoadObj)3, 3, DashPanel_Main);
		speed2->Data1->Scale.x = rand() % 5 + 10 * 2.5;
		speed2->Data1->Rotation.y = rand() % 0x8000;
		speed2->Data1->Position = p1->Position;
		speed2->Data1->Position.z += rand() % 10 + 1 * 9;
	}

	return;
}

void RandomSpikeBall(EntityData1* p1) {
	int number = rand() % 2;
	

	ObjectMaster* spike = LoadObject((LoadObj)6, 3, SwingSpikeBall_Load);
	spike->Data1->Rotation.y = rand() % 80 + 1000;
	spike->Data1->Scale.x = rand() % 5 + 10 * 2.5;
	spike->Data1->Position = p1->Position;
	spike->Data1->Position.y += 2;
	spike->Data1->Position.x += 80;

	if (number) {
		ObjectMaster* spike2 = LoadObject((LoadObj)6, 3, SwingSpikeBall_Load);
		spike2->Data1->Rotation.y = rand() % 80 + 1000;
		spike2->Data1->Scale.x = rand() % 5 + 10 * 2.5;
		spike2->Data1->Position = p1->Position;
		spike2->Data1->Position.y += 2;
		spike2->Data1->Position.z += rand() % 10 + 1 * 9;
	}

	return;
}

void RandomKillMomentum(CharObj2* p1) {
	p1->Speed = { 0, 0, 0 };
	return;
}

void RandomVSpeed(CharObj2* p1) {
	p1->Speed.y = p1->PhysicsData.VSpeedCap;
	return;
}

void RandomHSpeed(CharObj2* p1) {
	p1->Speed.x = p1->PhysicsData.HSpeedCap;
	return;
}
	

void RandomHurt() {
	if (Rings > 0)
		return HurtCharacter(0);
}

void RandomPowerUP(EntityData1* P1) {

	int randomUp = rand() % 9;
	
	if (!randomUp)
		GiveSpeedShoes(P1); //fix funny crash
	else
		ItemBoxPowerups[randomUp].Function(P1);

	
	DoThingWithItemBoxPowerupIndex(randomUp);
}

void MGiantScale(EntityData1* p1) {
	for (int i = 0; i < 21; i++) {
		SONIC_OBJECTS[i]->scl[0] = 4;
		SONIC_OBJECTS[i]->scl[1] = 4;
		SONIC_OBJECTS[i]->scl[2] = 4;
	}
	return;
}


void MSmallScale(EntityData1* p1) {
	for (int i = 0; i < 21; i++) {
		SONIC_OBJECTS[i]->scl[0] = 0.5;
		SONIC_OBJECTS[i]->scl[1] = 0.5;
		SONIC_OBJECTS[i]->scl[2] = 0.5;
	}
	return;
}


void RandomSwapMusic() {

	do {
		CurrentSong = rand() % 125;
	} while (LastSong == CurrentSong);

	LastSong = CurrentSong;
	return;
}


void ManiaPlayVoice_rng() {
	int a1 = rand() % 2043;
	PlayVoice_R(a1);
	return;
}




typedef void(__cdecl* ManiaEnt)(EntityData1*);
typedef void(__cdecl* ManiaCharObj)(CharObj2*);
typedef void(__cdecl* ManiaNull)();


struct ManiaS {
	ManiaEnt func;
	ManiaCharObj func2;
	ManiaNull func3;
};

ManiaS ManiaArray[10]{

	{ RandomSpring, nullptr, nullptr, },
	{ RandomSpeedPad, nullptr, nullptr, },
	{ RandomSpikeBall, nullptr, nullptr, },
	{ RandomPowerUP, nullptr, nullptr, },
	{ nullptr, RandomKillMomentum, nullptr, },
	{ nullptr, RandomVSpeed, nullptr, },
	{ nullptr, RandomHSpeed, nullptr, },
	{ nullptr, nullptr, RandomSwapMusic },
	{ nullptr, nullptr, ManiaPlayVoice_rng},
	{ nullptr, nullptr, RandomHurt },
};


void RandomMadnessOnFrames() {
	if (!CharObj2Ptrs[0] || GameState != 15 || CurrentLevel == LevelIDs_SkyChase1 || CurrentLevel == LevelIDs_SkyChase2 || CurrentLevel >= LevelIDs_SSGarden)
		return;

	if (Maniatimer < 200)
		Maniatimer++;

	if (Maniatimer >= 200)
	{
		char curRand = 0;

		do {
			curRand = rand() % LengthOfArray(ManiaArray);
		} while (oldRand == curRand);

		if (ManiaArray[curRand].func != nullptr)
			ManiaArray[curRand].func(EntityData1Ptrs[0]);
		else if (ManiaArray[curRand].func2 != nullptr)
			ManiaArray[curRand].func2(CharObj2Ptrs[0]);
		else
			ManiaArray[curRand].func3();

		oldRand = curRand;
		Maniatimer = 0;
	}
}

__declspec(dllexport) void InitVsChat(const char* path, const HelperFunctions& helperFunctions)
{
	if (vsChat) {
		char buf[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH, buf);
		SetCurrentDirectoryA(path);
		HMODULE hm = LoadLibraryA("SADXVsChatNET.dll");
		if (hm == NULL)
		{
			SetCurrentDirectoryA(buf);
			PrintDebug("Rando SADXVsChat: Failed to load helper DLL, mod will not function!");
			return;
		}
		GetProcAddress(hm, "Main")();
		SetCurrentDirectoryA(buf);
	}
}