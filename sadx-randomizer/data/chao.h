#pragma once

//Lost Chao Location //To do: add the last lost chao for: WV Gamma, HS Big, knux sky deck maybe? Also Casino except for tails
SetLevelPosition ChaoLevelPosition[26] {

	{ GammaVersion, LevelAndActIDs_EmeraldCoast1, 1599, 114.75, 840, 0x0 - 0x4000 },
	{ SonicVersion, LevelAndActIDs_EmeraldCoast2, 3857.76, 596.395, -2896.18, 0x8000 },
	{ BigVersion, LevelAndActIDs_EmeraldCoast3, 6103.9, 559.725, 630.345, 0xBDAC},
	{ SonicVersion, LevelAndActIDs_WindyValley3, 3489.99, -4340.27, -2132.28, 0x8000 },
	{ SonicVersion, LevelAndActIDs_Casinopolis1, 361, 380, -40, 0x8000 },
	{ TailsVersion, LevelAndActIDs_Casinopolis2, -1565.96, -2205, 2654.24, 0x8000 },
	{ SonicVersion, LevelAndActIDs_IceCap1, -90.96932, 2620.706, -2577.356 },
	{ BigVersion, LevelAndActIDs_IceCap4, 1790.85, 371.968811, 11.265, 0x8000 },
	{ SonicVersion, LevelAndActIDs_TwinklePark2, -89.1414, 830, -991.721, 0x8000 }, //Sonic Version
	{ BigVersion, LevelAndActIDs_TwinklePark2, 604, 338, 237, 0x8000 }, //Big Version
	{ AmyVersion, LevelAndActIDs_TwinklePark3, -41.43054199, 50, 290.7596436, 0x0 - 0x4000  }, //Amy Version
	{ SonicVersion, LevelAndActIDs_SpeedHighway1, 4455, -386.135, 2930.18, 4.479076996E-43 - 0x4000},
	{ TailsVersion, LevelAndActIDs_SpeedHighway1, 8570.973, -950.125, 8984.435, 0x8000 + 0x4000 },
	{ KnucklesVersion, LevelAndActIDs_SpeedHighway3, -232.625, 483.875, -2216, 2.0  },
	{ SonicVersion, LevelAndActIDs_RedMountain1, -3861.85, 883.96, -2974.81, 13754 - 0x3200 },
	{ GammaVersion, LevelAndActIDs_RedMountain2, -119.452, 1051.5, 3375.85, 40880},
	{ KnucklesVersion, LevelAndActIDs_RedMountain3, -1761.775, 71.5, -1862.41, 5.479076996E-43 + 0x4000 },
	//{ KnucklesVersion, LevelAndActIDs_SkyDeck3, 779, 169, 322, 0x0 },
	{ KnucklesVersion, LevelAndActIDs_SkyDeck3, 291, -105, -587, 0x0 },
	{ SonicVersion, LevelAndActIDs_LostWorld2, 909.875, 164.625, 152.5, 0x0 + 0x4000 },
	{ KnucklesVersion, LevelAndActIDs_LostWorld2, 7410, -1965, 1316, 0x8000 },
	{ AmyVersion, LevelAndActIDs_FinalEgg1, 2974.897, 5663.096, -1992.15, -1.681558157E-44 + 0x4000 },
	{ GammaVersion, LevelAndActIDs_FinalEgg3, 1939, -3174.049561, -128, 0x8000 }, //Gamma Version
	{ SonicVersion, LevelAndActIDs_FinalEgg3, 2659.293457, -2888.063965, -946.1408081, 0x8000 }, //Sonic Version
	{ BigVersion, LevelAndActIDs_HotShelter1, -157.615, 418.875, -271.49, 0x8000 }, //Big Version 
	{ AmyVersion, LevelAndActIDs_HotShelter2, 716.4085693, 677.8605957, -2952.347412, 0x16200 }, //Amy version SADX VANILLA
	{ GammaVersion, LevelAndActIDs_HotShelter3, 2.01, 3221, -3136, 0x8000 },
};

//Player end position when reaching Chao
SetLevelPosition M3_PlayerEndPosition[26] { 
	{ GammaVersion, LevelAndActIDs_EmeraldCoast1, { 1590.68, 115, 833.759 }, 0x6000},
	{ SonicVersion, LevelAndActIDs_EmeraldCoast2, { 3855.29, 596.009, -2901.52 }, 0x4000 },
	{ BigVersion, LevelAndActIDs_EmeraldCoast3, { 6096.56, 559.897, 625.399 }, 0 },
	{ SonicVersion, LevelAndActIDs_WindyValley3, { 3496.49, -4340.27, -2138.91 }, 0x4000 },
	{ SonicVersion, LevelAndActIDs_Casinopolis1, 361, 380, -40, 0x8000 },
	{ TailsVersion, LevelAndActIDs_Casinopolis2, -1573.51, -2205, 2654.24, 0x8000 },
	{ SonicVersion, LevelAndActIDs_IceCap1, -84.1479, 2623.706, -2559.488, 0x4000 },
	{ BigVersion, LevelAndActIDs_IceCap4, 1799.06, 371.969, 8.94554, 0x8000 },
	{ SonicVersion, LevelAndActIDs_TwinklePark2, -89.1414, 830, -991.721, 0x8000 }, //Sonic Version
	{ BigVersion, LevelAndActIDs_TwinklePark2, 604, 338, 237, 0x8000 }, //Big Version
	{ AmyVersion, LevelAndActIDs_TwinklePark3, -41.43054199, 50, 290.7596436, 0x0 - 0x4000  }, //Amy Version
	{ SonicVersion, LevelAndActIDs_SpeedHighway1, 4455, -386.135, 2930.18, 4.479076996E-43 - 0x4000},
	{ TailsVersion, LevelAndActIDs_SpeedHighway1, 8570.973, -950.125, 8984.435, 0x8000 + 0x4000 },
	{ KnucklesVersion, LevelAndActIDs_SpeedHighway3, -232.625, 483.875, -2216, 2.0  },
	{ SonicVersion, LevelAndActIDs_RedMountain1, -3861.85, 883.96, -2974.81, 13754 - 0x3200 },
	{ GammaVersion, LevelAndActIDs_RedMountain2, -119.452, 1051.5, 3375.85, 40880},
	{ KnucklesVersion, LevelAndActIDs_RedMountain3, -1749.18, 72.0189, -1871.87, 5.479076996E-43 },
	{ KnucklesVersion, LevelAndActIDs_SkyDeck3, 280, -104, -580, 0x8000 },
	{ SonicVersion, LevelAndActIDs_LostWorld2, 909.875, 164.625, 152.5, 0x0 + 0x4000 },
	{ KnucklesVersion, LevelAndActIDs_LostWorld2, 7410, -1965, 1316, 0x8000 },
	{ AmyVersion, LevelAndActIDs_FinalEgg1, 2974.897, 5663.096, -1992.15, -1.681558157E-44 + 0x4000 },
	{ GammaVersion, LevelAndActIDs_FinalEgg3, 1939, -3174.049561, -128, 0x8000 }, //Gamma Version
	{ SonicVersion, LevelAndActIDs_FinalEgg3, 2659.293457, -2888.063965, -946.1408081, 0x8000 }, //Sonic Version
	{ BigVersion, LevelAndActIDs_HotShelter1, -157.615, 418.875, -271.49, 0x8000 }, //Big Version 
	{ AmyVersion, LevelAndActIDs_HotShelter2, 736.793, 677.861, -2953.76, 0x0 }, //Amy version SADX VANILLA
	{ GammaVersion, LevelAndActIDs_HotShelter3, 2.01, 3221, -3136, 0x8000 },
};

//Mysitc Melody teleport close to the Chao
SetLevelPosition PlayerAroundChaoPosition[17]{

	{ BigVersion, LevelAndActIDs_EmeraldCoast3, 5901.4, 537.225, 568.47, 0x8000 },
	{ SonicVersion, LevelAndActIDs_WindyValley3, 3608.115, -4250.02, -2132.28, 0x8000 },
	{ SonicVersion, LevelAndActIDs_TwinklePark2, 330.48, 942.379, -133.624, 0x8000 },
	{ BigVersion, LevelAndActIDs_TwinklePark2, 608.112, 499.01, -55.8172, 0x8000 },
	{ SonicVersion, LevelAndActIDs_SpeedHighway1, 3653.31, -127.07, 2924.58, 0x8000 },
	{ TailsVersion, LevelAndActIDs_SpeedHighway1, 8019, -597, 8868, 0x8000 },
	{ KnucklesVersion, LevelAndActIDs_SpeedHighway3, -230.366, 410.935, -1891.33, 324.125 },
	{ SonicVersion, LevelAndActIDs_RedMountain1, -3855.28, 1000.21, -2946.56 },
	{ GammaVersion, LevelAndActIDs_RedMountain2, -430, 1200, 3141 },
	//{ KnucklesVersion, LevelAndActIDs_SkyDeck3, 774, 188, 184, 324.125 },
	{ KnucklesVersion, LevelAndActIDs_SkyDeck3, 60, -44, -420, 324.125 },
	{ KnucklesVersion, LevelAndActIDs_LostWorld2, 7421, -1580, 1403 },	
	{ SonicVersion, LevelAndActIDs_IceCap1, -83.74668, 2654.081, -2558.437 },
	{ AmyVersion, LevelAndActIDs_FinalEgg1, 2897.51, 5810.17, -1993.62},
	{ GammaVersion, LevelAndActIDs_FinalEgg3, 1517.56, -3139.29, -274.385},
	{ BigVersion, LevelAndActIDs_HotShelter1, -211.615, 418.875, -275.99 },
	{ AmyVersion, LevelAndActIDs_HotShelter2, 1060.4085693, 750.8605957, -2952.347412 },
	{ GammaVersion, LevelAndActIDs_HotShelter3, -1302.44, 3378.13, -3116.41 },
};


enum ChaoActions {
	ChaoAction_Init,
	ChaoAction_LoadChao,
	ChaoAction_CheckHit,
	ChaoAction_Hit,
	ChaoAction_Transition,
	ChaoAction_Free,
	Action_ItemBox,
};

void ChaoObj_Delete(ObjectMaster* a1);
void __cdecl ChaoGameplayCheck();
bool DoesChaoNeedGravity(_int16 CurLevel);
void Chao_LoadFiles();

extern bool TPAmyVersion;

void Chao_LoadFiles();
