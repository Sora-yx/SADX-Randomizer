#include "stdafx.h"


static uint8_t enemyID = 0;
const static uint8_t enemyMax = 30;

ObjectFuncPtr enemyList[] = { Kiki_Load, RhinoTank_Main, Sweep_Load, EPolice,
ESman, UnidusA_Main, UnidusB_Main, UnidusC_Main, (ObjectFuncPtr)0x5B03B0, BoaBoa_Main, ERobo_0, SpinnerA_Main, SpinnerB_Main, SpinnerC_Main };

ObjectFuncPtr SpinnerList[] = { SpinnerA_Main, SpinnerB_Main, SpinnerC_Main };

PVMEntry enemyTex[] = {
	{ "E_SAI", &E_SAI_TEXLIST}, //rhino tank
	{ "E_snowman", &E_SNOWMAN_TEXLIST},
	{ "E_snake", &E_SNAKE_TEXLIST}, //giant caterpillar?
	{ "E_ROBO", &E_ROBO_TEXLIST},
	{ "E_LEON", &E_LEON_TEXLIST},
	{ "E_BOMB", &E_BOMB_TEXLIST},
	{ "E_SARU", &E_SARU_TEXLIST},
	{ "E_amenbo", &E_AMENBO_TEXLIST}, //sweep
	{ "Supi_supi", &SUPI_SUPI_TEXLIST}, //spinner
	{ "Nisepat", &NISEPAT_TEXLIST}, //police
	{ "Uni_a_unibody", &UNI_A_UNIBODY_TEXLIST}, //uni_B uses uni_a textures
	{ "Uni_c_unibody", &UNI_C_UNIBODY_TEXLIST},
	{ "GACHAPON", &GACHAPON_TEXLIST},
	{ "Togeball_togeball", &TOGEBALL_TOGEBALL_TEXLIST}
};

PVMEntry MinimalPVMs[]{
	{ "GOMA", &GOMA_TEXLIST },
	{ "PEN", &PEN_TEXLIST },
	{ "RAKO", &RAKO_TEXLIST },
	{ "KUJA", &KUJA_TEXLIST },
	{ "TUBA", &TUBA_TEXLIST },
	{ "OUM", &OUM_TEXLIST },
	{ "BANB", &BANB_TEXLIST },
	{ "USA", &USA_TEXLIST },
	{ "WARA", &WARA_TEXLIST },
	{ "GORI", &GORI_TEXLIST },
	{ "LION", &LION_TEXLIST },
	{ "ZOU", &ZOU_TEXLIST },
	{ "MOGU", &MOGU_TEXLIST },
	{ "KOAR", &KOAR_TEXLIST },
	{ "SUKA", &SUKA_TEXLIST },
};

void LoadEnemyAndMiniMalTex()
{
	for (uint8_t j = 0; j < LengthOfArray(MinimalPVMs); ++j)
	{
		LoadPVM(MinimalPVMs[j].Name, MinimalPVMs[j].TexList);
	}

	for (uint8_t i = 0; i < LengthOfArray(enemyTex); i++)
	{
		LoadPVM(enemyTex[i].Name, enemyTex[i].TexList);
	}
}

//patch sweep crash with bomb
void Sweep_Main_r(task* obj);
TaskHook Sweep_Main_t((intptr_t)Sweep_Main, Sweep_Main_r);

void Sweep_Main_r(task* obj)
{
	taskwk* data = obj->twp;
	ObjectData2* objdata2 = (ObjectData2*)obj->mwp;

	if (data && objdata2) 
	{
		if (data->mode < 3)
		{
			if (OhNoImDead((EntityData1*)data, objdata2))
			{
				data->mode = 3;
				data->counter.b[1] = 0;
				data->counter.b[2] = 1;
				data->wtimer = 0;
				data->scl.z = 0.34999999f;
				return;
			}
		}
	}

	Sweep_Main_t.Original(obj);
}


void SetRandomEnemy(RandomizedEntry* entry)
{
	if (!entry)
		return;

	for (uint8_t i = 0; i < LengthOfArray(entry->enemy); i++)
	{
		entry->enemy[i].count = rand() % 6 + 1;
		entry->enemy[i].enemyID = rand() % LengthOfArray(enemyList);
	}
}

static void SetCount(uint8_t& count)
{
	if (enemyID >= enemyMax - 1)
	{
		enemyID = 0;
	}

	count = randomizedSets[levelCount].enemy[enemyID].count;

	if (CurrentCharacter == Characters_Big || CurrentCharacter == Characters_Amy)
	{
		if (count >= 3)
			count = 2;
	}

	if (count < 0)
		count = 0;
}


//since spinner fly we need to replace them with enemy that don't have ground detection otherwise they will keep falling
void Load_Random_EnemySpiner(task* tp)
{
	auto twp = tp->twp;
	Float diff = 15.0f + rand() % 20 + 1;

	if (!CheckRangeOut(tp) && !twp->mode)
	{
		uint8_t count = 0;
		SetCount(count);

		for (uint8_t i = 0; i < count - 1; i++)
		{
			uint8_t curID = count + i;

			if (curID >= enemyMax)
				curID = 0;

			ObjectFuncPtr enemyTask = (rand() % 2) ? Kiki_Load : BoaBoa_Main;
			task* enemy = CreateElementalTask(2, 3, (TaskFuncPtr)enemyTask);
			if (enemy && twp)
			{
				enemy->twp->pos = twp->pos;
				enemy->twp->scl = { 1, 1, 1 };
				enemy->twp->ang = twp->ang;
				enemy->twp->pos.x -= diff;
				enemy->twp->pos.z += diff;

				auto ocp = tp->ocp;
				if (ocp)
				{
					OBJ_CONDITION condition{};
					memcpy(&condition, tp->ocp, sizeof(OBJ_CONDITION));
					enemy->ocp = &condition;
					enemy->ocp->pTask = enemy;
				}

				diff += 12.0f;
			}
		}
	}

	tp->exec = (TaskFuncPtr)Kiki_Load;
}


void Load_Random_Enemy(task* tp)
{
	auto twp = tp->twp;

	if (!CheckRangeOut(tp) && !twp->mode)
	{
		Float diff = rand() % 15 + 1;
		uint8_t count = 0;

		SetCount(count);

		for (uint8_t i = 0; i < count - 1; i++)
		{
			uint8_t curID = count + i;

			if (curID >= enemyMax)
				curID = 0;

			task* enemy = CreateElementalTask(2, 3, (TaskFuncPtr)enemyList[randomizedSets[levelCount].enemy[curID].enemyID]);
			if (enemy && twp)
			{
				enemy->twp->pos = twp->pos;
				enemy->twp->scl = { 1, 1, 1 };
				enemy->twp->ang = twp->ang;
				enemy->twp->pos.x += diff;
				enemy->twp->pos.z += diff;
				auto ocp = tp->ocp;
				if (ocp)
				{
					OBJ_CONDITION condition{};
					memcpy(&condition, tp->ocp, sizeof(OBJ_CONDITION));
					enemy->ocp = &condition;
					enemy->ocp->pTask = enemy;
				}

				diff += 12.0f;
			}

		}

	}

	enemyID++;
	tp->exec = (TaskFuncPtr)enemyList[randomizedSets[levelCount].enemy->enemyID];
}

void SetRandomEnemyObjList(ObjectListEntry* objlist, const uint16_t size)
{
	if (!RNGEnemies)
		return;

	for (uint16_t i = 0; i < size; i++)
	{
		for (uint8_t k = 0; k < LengthOfArray(SpinnerList); k++)
		{
			if (objlist[i].LoadSub == SpinnerList[k])
			{
				objlist[i].LoadSub = (ObjectFuncPtr)Load_Random_EnemySpiner;
				objlist[i].Distance += 15000;
			}
		}

		for (uint8_t j = 0; j < LengthOfArray(enemyList); j++)
		{
			if (objlist[i].LoadSub == enemyList[j])
			{
				objlist[i].LoadSub = (ObjectFuncPtr)Load_Random_Enemy;
				objlist[i].Distance += 15000;
			}
		}


	}
}

