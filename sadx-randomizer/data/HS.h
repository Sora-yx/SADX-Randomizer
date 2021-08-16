#pragma once

void E105Enemy_Main_R(ObjectMaster* obj);

//Object

ObjectListEntry HotShelter1ObjectList_list[] = {
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x450370, "RING   " } /* "RING   " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4C30, "SPRING " } /* "SPRING " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4E50, "SPRINGB" } /* "SPRINGB" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4450, "O AXPNL" } /* "O AXPNL" */,
	{ 6, 3, 1, 62500, 0, (ObjectFuncPtr)0x7A4260, "O IRONB" } /* "O IRONB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A3E50, "O FeBJG" } /* "O FeBJG" */,
	{ 2, 3, 1, 32400, 0, (ObjectFuncPtr)0x7A30E0, "O TOGE" } /* "O TOGE" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x4A3420, "O EME P" } /* "O EME P" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x46B170, "O RELEASE" } /* "O RELEASE" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBA80, "O SWITCH" } /* "O SWITCH" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x7A2B60, "CMN KUSA" } /* "CMN KUSA" */,
	{ 14, 3, 0, 0, 0, (ObjectFuncPtr)0x7A26F0, "CMN_DRING" } /* "CMN_DRING" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A21C0, "O BALOON" } /* "O BALOON" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x4D7170, "O ITEMBOX" } /* "O ITEMBOX" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA530, "Rocket H" } /* "Rocket H" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA660, "Rocket HS" } /* "Rocket HS" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA7D0, "Rocket V" } /* "Rocket V" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA900, "Rocket VS" } /* "Rocket VS" */,
	{ 2, 2, 1, 4000000, 0, (ObjectFuncPtr)0x4B8DC0, "O JPanel" } /* "O JPanel" */,
	{ 15, 6, 0, 0, 0, (ObjectFuncPtr)0x44F540, "O Save Point" } /* "O Save Point" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D4850, "WALL   " } /* "WALL   " */,
	{ 2, 3, 1, 1600, 0, (ObjectFuncPtr)0x7A8A60, "BUBBLE1" } /* "BUBBLE1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBDE0, "DYNAMITE" } /* "DYNAMITE" */,
	{ 2, 2, 1, 10000, 0, (ObjectFuncPtr)0x7B0C80, "C SCENECHANGER" } /* "C SCENECHANGER" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x4C07D0, "O ITEMBOXAIR" } /* "O ITEMBOXAIR" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7B0A70, "EROB COLLI" } /* "EROB COLLI" */,
	{ 2, 2, 1, 78400, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 2, 2, 1, 78400, 0, (ObjectFuncPtr)0x7A9C60, "O HINTBOX" } /* "O HINTBOX" */,
	{ 2, 2, 1, 78400, 0, (ObjectFuncPtr)0x5A3520, "C SWITCH" } /* "C SWITCH" */,
	{ 2, 2, 1, 78400, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 1, 78400, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 1, 78400, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 1, 78400, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x4AD140, "E SARU" } /* "E SARU" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x4A6700, "E ROBO" } /* "E ROBO" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x4A85C0, "E LEON" } /* "E LEON" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A33D0, "O ENTOTSU" } /* "O ENTOTSU" */,
	{ 2, 3, 1, 78400, 0, (ObjectFuncPtr)0x5A3210, "O LIGHT1" } /* "O LIGHT1" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x5A3030, "O LIGHT2" } /* "O LIGHT2" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x5A2F10, "O LIGHT3" } /* "O LIGHT3" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x5A2DC0, "O CONTAINER" } /* "O CONTAINER" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x5A2950, "O KAITENKEY" } /* "O KAITENKEY" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x5A2490, "O KAITENMETER" } /* "O KAITENMETER" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2250, "O BIRIBIRI" } /* "O BIRIBIRI" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x5A2120, "O GATE1" } /* "O GATE1" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A1D70, "O ELEVATOR" } /* "O ELEVATOR" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x5A16B0, "O BRIDGE" } /* "O BRIDGE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0C50, "O SASAE1A" } /* "O SASAE1A" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0B10, "O SASAE1B" } /* "O SASAE1B" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A09D0, "O SASAE1C" } /* "O SASAE1C" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0890, "O SASAE1D" } /* "O SASAE1D" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x5A0720, "O HAGURUMA1" } /* "O HAGURUMA1" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x5A0540, "O HAGURUMA2" } /* "O HAGURUMA2" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x5A0230, "O HAGURUMA3" } /* "O HAGURUMA3" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x59FF30, "O HAGURUMA4" } /* "O HAGURUMA4" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x59FD50, "O HAGURUMA5" } /* "O HAGURUMA5" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x59FA40, "O HAGURUMA6" } /* "O HAGURUMA6" */,
	{ 3, 3, 1, 90000, 0, (ObjectFuncPtr)0x59CA60, "O GATE2" } /* "O GATE2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59F770, "O TUKIKOU" } /* "O TUKIKOU" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59F620, "O PROPELLER" } /* "O PROPELLER" */,
	{ 7, 3, 1, 48400, 0, (ObjectFuncPtr)0x59F470, "O KAIDAN" } /* "O KAIDAN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EFE0, "O DRUMCAN" } /* "O DRUMCAN" */,
	{ 2, 3, 1, 90000, 0, (ObjectFuncPtr)0x59EEA0, "O KAZARI1" } /* "O KAZARI1" */,
	{ 2, 3, 1, 90000, 0, (ObjectFuncPtr)0x59ED50, "O KAZARI2" } /* "O KAZARI2" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x59EBF0, "O SYOUMEI" } /* "O SYOUMEI" */,
	{ 6, 3, 1, 90000, 0, (ObjectFuncPtr)0x59EB00, "O COMPUTER" } /* "O COMPUTER" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x59E940, "O KAITENDAI" } /* "O KAITENDAI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59E660, "O TOILE_DOOR" } /* "O TOILE_DOOR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59E430, "O DARUMA" } /* "O DARUMA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59E170, "O HAKO" } /* "O HAKO" */,
	{ 7, 3, 1, 78400, 0, (ObjectFuncPtr)0x59DFA0, "O UKIJIMA" } /* "O UKIJIMA" */,
	{ 3, 3, 1, 90000, 0, (ObjectFuncPtr)0x59D970, "O HASIGO" } /* "O HASIGO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D840, "O GATESIDE" } /* "O GATESIDE" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x59D760, "O BLUELIGHT" } /* "O BLUELIGHT" */,
	{ 2, 3, 1, 62500, 0, (ObjectFuncPtr)0x59D5C0, "O LIGHT4" } /* "O LIGHT4" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x59D460, "O HIKARI" } /* "O HIKARI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D350, "O FENS" } /* "O FENS" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D1F0, "O KANSO" } /* "O KANSO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D0D0, "O WCMARK1" } /* "O WCMARK1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59CFB0, "O WCMARK1" } /* "O WCMARK1" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59CDF0, "O KAITENASHIBA" } /* "O KAITENASHIBA" */,
	{ 3, 3, 1, 250000, 0, (ObjectFuncPtr)0x59CA90, "GATE13" } /* "GATE13" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A5960, "O GATE SW" } /* "O GATE SW" */,
	{ 2, 3, 1, 48400, 0, (ObjectFuncPtr)0x5A9A90, "O KOWARESUISOU" } /* "O KOWARESUISOU" */,
	{ 6, 3, 1, 160000, 0, (ObjectFuncPtr)0x5A9100, "O SUIMEN" } /* "O SUIMEN" */,
	{ 6, 3, 1, 160000, 0, (ObjectFuncPtr)0x5A8E60, "O HIYOKOYUKA" } /* "O HIYOKOYUKA" */,
	{ 3, 3, 1, 57600, 0, (ObjectFuncPtr)0x5977F0, "S BASS " } /* "S BASS " */,
	{ 3, 3, 1, 57600, 0, (ObjectFuncPtr)0x7A7AD0, "S KAERU" } /* "S KAERU" */,
	{ 3, 3, 1, 62500, 0, (ObjectFuncPtr)0x597660, "S GENE " } /* "S GENE " */,
	{ 3, 3, 1, 62500, 0, (ObjectFuncPtr)0x59B9F0, "O KURAGE" } /* "O KURAGE" */,
	{ 6, 3, 1, 160000, 0, (ObjectFuncPtr)0x5A87D0, "O BREAK KABE" } /* "O BREAK KABE" */,
	{ 6, 3, 1, 62500, 0, (ObjectFuncPtr)0x5A7B30, "O BREAK GLASS" } /* "O BREAK GLASS" */,
	{ 2, 0, 1, 90000, 0, (ObjectFuncPtr)0x4D4E10, "NO WATER" } /* "NO WATER" */,
	{ 2, 0, 1, 90000, 0, (ObjectFuncPtr)0x4D4BE0, "BIGWJUMP" } /* "BIGWJUMP" */,
	{ 2, 2, 1, 1600, 0, (ObjectFuncPtr)0x7A8E50, "O BUBBLE" } /* "O BUBBLE" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG" }, /* "O FROG" */
	{ LoadObj_Data1, 3, 1, 1000000.0f, 0, MysticMelody_Main, "O KNUDAI" }, //Mystic Melody
	{ LoadObj_Data1, 3, 0, 0, 0, PlatformMM_Main, "O KDASIBA" }
};

ObjectListEntry HotShelter2ObjectList_list[] = {
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x450370, "RING   " } /* "RING   " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4C30, "SPRING " } /* "SPRING " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4E50, "SPRINGB" } /* "SPRINGB" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4450, "O AXPNL" } /* "O AXPNL" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4260, "O IRONB" } /* "O IRONB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A3E50, "O FeBJG" } /* "O FeBJG" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A30E0, "O TOGE" } /* "O TOGE" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x4A3420, "O EME P" } /* "O EME P" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x46B170, "O RELEASE" } /* "O RELEASE" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBA80, "O SWITCH" } /* "O SWITCH" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x7A2B60, "CMN KUSA" } /* "CMN KUSA" */,
	{ 14, 3, 0, 0, 0, (ObjectFuncPtr)0x7A26F0, "CMN_DRING" } /* "CMN_DRING" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A21C0, "O BALOON" } /* "O BALOON" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D6F10, "O ITEMBOX" } /* "O ITEMBOX" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA530, "Rocket H" } /* "Rocket H" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA660, "Rocket HS" } /* "Rocket HS" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA7D0, "Rocket V" } /* "Rocket V" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA900, "Rocket VS" } /* "Rocket VS" */,
	{ 2, 2, 1, 4000000, 0, (ObjectFuncPtr)0x4B8DC0, "O JPanel" } /* "O JPanel" */,
	{ 15, 6, 0, 0, 0, (ObjectFuncPtr)0x44F540, "O Save Point" } /* "O Save Point" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D4850, "WALL   " } /* "WALL   " */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A8A60, "BUBBLE1" } /* "BUBBLE1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBDE0, "DYNAMITE" } /* "DYNAMITE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7B0C80, "C SCENECHANGER" } /* "C SCENECHANGER" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x4C07D0, "O ITEMBOXAIR" } /* "O ITEMBOXAIR" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7B0A70, "EROB COLLI" } /* "EROB COLLI" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A9C60, "O HINTBOX" } /* "O HINTBOX" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x5A3520, "C SWITCH" } /* "C SWITCH" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4AD140, "E SARU" } /* "E SARU" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4A6700, "E ROBO" } /* "E ROBO" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4A85C0, "E LEON" } /* "E LEON" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A33D0, "O ENTOTSU" } /* "O ENTOTSU" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A3210, "O LIGHT1" } /* "O LIGHT1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A3030, "O LIGHT2" } /* "O LIGHT2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2F10, "O LIGHT3" } /* "O LIGHT3" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2DC0, "O CONTAINER" } /* "O CONTAINER" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2950, "O KAITENKEY" } /* "O KAITENKEY" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2490, "O KAITENMETER" } /* "O KAITENMETER" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2250, "O BIRIBIRI" } /* "O BIRIBIRI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2120, "O GATE1" } /* "O GATE1" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A1D70, "O ELEVATOR" } /* "O ELEVATOR" */,
	{ 6, 3, 1, 1690000, 0, (ObjectFuncPtr)0x5A16B0, "O BRIDGE" } /* "O BRIDGE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0C50, "O SASAE1A" } /* "O SASAE1A" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0B10, "O SASAE1B" } /* "O SASAE1B" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A09D0, "O SASAE1C" } /* "O SASAE1C" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0890, "O SASAE1D" } /* "O SASAE1D" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x5A0720, "O HAGURUMA1" } /* "O HAGURUMA1" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x5A0540, "O HAGURUMA2" } /* "O HAGURUMA2" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x5A0230, "O HAGURUMA3" } /* "O HAGURUMA3" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x59FF30, "O HAGURUMA4" } /* "O HAGURUMA4" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x59FD50, "O HAGURUMA5" } /* "O HAGURUMA5" */,
	{ 6, 3, 1, 902500, 0, (ObjectFuncPtr)0x59FA40, "O HAGURUMA6" } /* "O HAGURUMA6" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59CA60, "O GATE2" } /* "O GATE2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59F770, "O TUKIKOU" } /* "O TUKIKOU" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59F620, "O PROPELLER" } /* "O PROPELLER" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59F470, "O KAIDAN" } /* "O KAIDAN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EFE0, "O DRUMCAN" } /* "O DRUMCAN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EEA0, "O KAZARI1" } /* "O KAZARI1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59ED50, "O KAZARI2" } /* "O KAZARI2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EBF0, "O SYOUMEI" } /* "O SYOUMEI" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x59EB00, "O COMPUTER" } /* "O COMPUTER" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x59E940, "O KAITENDAI" } /* "O KAITENDAI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59E660, "O TOILE_DOOR" } /* "O TOILE_DOOR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59E430, "O DARUMA" } /* "O DARUMA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59E170, "O HAKO" } /* "O HAKO" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59DFA0, "O UKIJIMA" } /* "O UKIJIMA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59D970, "O HASIGO" } /* "O HASIGO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D840, "O GATESIDE" } /* "O GATESIDE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D760, "O BLUELIGHT" } /* "O BLUELIGHT" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D5C0, "O LIGHT4" } /* "O LIGHT4" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D460, "O HIKARI" } /* "O HIKARI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D350, "O FENS" } /* "O FENS" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D1F0, "O KANSO" } /* "O KANSO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D0D0, "O WCMARK1" } /* "O WCMARK1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59CFB0, "O WCMARK2" } /* "O WCMARK2" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59CDF0, "O KAITENASHIBA" } /* "O KAITENASHIBA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59CA90, "GATE13" } /* "GATE13" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A5960, "O GATE SW" } /* "O GATE SW" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A70C0, "O BANJI" } /* "O BANJI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A6EB0, "O SUB TV" } /* "O SUB TV" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A6BB0, "O ROBO TV" } /* "O ROBO TV" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A6800, "O Crash TV" } /* "O Crash TV" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A5B70, "O Box Ana" } /* "O Box Ana" */,
	{ 3, 3, 1, 62500, 0, (ObjectFuncPtr)0x59AAF0, "O BOX SWITCH" } /* "O BOX SWITCH" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG " }, /* "O FROG " */
	{ LoadObj_Data1, 3, 1, 1000000.0f, 0, MysticMelody_Main, "O KNUDAI" }, //Mystic Melody
	{ LoadObj_Data1, 3, 0, 0, 0, PlatformMM_Main, "O KDASIBA" }
};


ObjectListEntry HotShelter3ObjectList_list[] = {
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x450370, "RING   " } /* "RING   " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4C30, "SPRING " } /* "SPRING " */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A4E50, "SPRINGB" } /* "SPRINGB" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4450, "O AXPNL" } /* "O AXPNL" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x7A4260, "O IRONB" } /* "O IRONB" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A3E50, "O FeBJG" } /* "O FeBJG" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A30E0, "O TOGE" } /* "O TOGE" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x4A3420, "O EME P" } /* "O EME P" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x46B170, "O RELEASE" } /* "O RELEASE" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBA80, "O SWITCH" } /* "O SWITCH" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x7A2B60, "CMN KUSA" } /* "CMN KUSA" */,
	{ 14, 3, 0, 0, 0, (ObjectFuncPtr)0x7A26F0, "CMN_DRING" } /* "CMN_DRING" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A21C0, "O BALOON" } /* "O BALOON" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D6F10, "O ITEMBOX" } /* "O ITEMBOX" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA530, "Rocket H" } /* "Rocket H" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA660, "Rocket HS" } /* "Rocket HS" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA7D0, "Rocket V" } /* "Rocket V" */,
	{ 14, 2, 0, 0, 0, (ObjectFuncPtr)0x4CA900, "Rocket VS" } /* "Rocket VS" */,
	{ 2, 2, 1, 4000000, 0, (ObjectFuncPtr)0x4B8DC0, "O JPanel" } /* "O JPanel" */,
	{ 15, 6, 0, 0, 0, (ObjectFuncPtr)0x44F540, "O Save Point" } /* "O Save Point" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4D4850, "WALL   " } /* "WALL   " */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x7A8A60, "BUBBLE1" } /* "BUBBLE1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x4CBDE0, "DYNAMITE" } /* "DYNAMITE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7B0C80, "C SCENECHANGER" } /* "C SCENECHANGER" */,
	{ 10, 3, 0, 0, 0, (ObjectFuncPtr)0x4C07D0, "O ITEMBOXAIR" } /* "O ITEMBOXAIR" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7B0A70, "EROB COLLI" } /* "EROB COLLI" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A1AA0, "O TIKAL" } /* "O TIKAL" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x7A9C60, "O HINTBOX" } /* "O HINTBOX" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x5A3520, "C SWITCH" } /* "C SWITCH" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4700, "C SPHERE" } /* "C SPHERE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4770, "C CYLINDER" } /* "C CYLINDER" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D47E0, "C CUBE" } /* "C CUBE" */,
	{ 2, 2, 0, 0, 0, (ObjectFuncPtr)0x4D4B70, "OTTOTTO" } /* "OTTOTTO" */,
	{ 2, 3, 1, 360000, 0, (ObjectFuncPtr)0x4AD140, "E SARU" } /* "E SARU" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4A6700, "E ROBO" } /* "E ROBO" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4A85C0, "E LEON" } /* "E LEON" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A33D0, "O ENTOTSU" } /* "O ENTOTSU" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A3210, "O LIGHT1" } /* "O LIGHT1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A3030, "O LIGHT2" } /* "O LIGHT2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2F10, "O LIGHT3" } /* "O LIGHT3" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2DC0, "O CONTAINER" } /* "O CONTAINER" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2950, "O KAITENKEY" } /* "O KAITENKEY" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2490, "O KAITENMETER" } /* "O KAITENMETER" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2250, "O BIRIBIRI" } /* "O BIRIBIRI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A2120, "O GATE1" } /* "O GATE1" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A1D70, "O ELEVATOR" } /* "O ELEVATOR" */,
	{ 6, 3, 1, 2250000, 0, (ObjectFuncPtr)0x5A16B0, "O BRIDGE" } /* "O BRIDGE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0C50, "O SASAE1A" } /* "O SASAE1A" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0B10, "O SASAE1B" } /* "O SASAE1B" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A09D0, "O SASAE1C" } /* "O SASAE1C" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A0890, "O SASAE1D" } /* "O SASAE1D" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x5A0720, "O HAGURUMA1" } /* "O HAGURUMA1" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x5A0540, "O HAGURUMA2" } /* "O HAGURUMA2" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x5A0230, "O HAGURUMA3" } /* "O HAGURUMA3" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x59FF30, "O HAGURUMA4" } /* "O HAGURUMA4" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x59FD50, "O HAGURUMA5" } /* "O HAGURUMA5" */,
	{ 6, 3, 1, 4000000, 0, (ObjectFuncPtr)0x59FA40, "O HAGURUMA6" } /* "O HAGURUMA6" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59CA60, "O GATE2" } /* "O GATE2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59F770, "O TUKIKOU" } /* "O TUKIKOU" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59F620, "O PROPELLER" } /* "O PROPELLER" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59F470, "O KAIDAN" } /* "O KAIDAN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EFE0, "O DRUMCAN" } /* "O DRUMCAN" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EEA0, "O KAZARI1" } /* "O KAZARI1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59ED50, "O KAZARI2" } /* "O KAZARI2" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59EBF0, "O SYOUMEI" } /* "O SYOUMEI" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x59EB00, "O COMPUTER" } /* "O COMPUTER" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x59E940, "O KAITENDAI" } /* "O KAITENDAI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59E660, "O TOILE_DOOR" } /* "O TOILE_DOOR" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59E430, "O DARUMA" } /* "O DARUMA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59E170, "O HAKO" } /* "O HAKO" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59DFA0, "O UKIJIMA" } /* "O UKIJIMA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59D970, "O HASIGO" } /* "O HASIGO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D840, "O GATESIDE" } /* "O GATESIDE" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D760, "O BLUELIGHT" } /* "O BLUELIGHT" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D5C0, "O LIGHT4" } /* "O LIGHT4" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D460, "O HIKARI" } /* "O HIKARI" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D350, "O FENS" } /* "O FENS" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D1F0, "O KANSO" } /* "O KANSO" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59D0D0, "O WCMARK1" } /* "O WCMARK1" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x59CFB0, "O WCMARK2" } /* "O WCMARK2" */,
	{ 7, 3, 0, 0, 0, (ObjectFuncPtr)0x59CDF0, "O KAITENASHIBA" } /* "O KAITENASHIBA" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x59CA90, "GATE13" } /* "GATE13" */,
	{ 2, 3, 0, 0, 0, (ObjectFuncPtr)0x5A5960, "O GATE SW" } /* "O GATE SW" */,
	{ 3, 3, 0, 0, 0, (ObjectFuncPtr)0x5A55A0, "O CRANE" } /* "O CRANE" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x59C620, "O CARGO" } /* "O CARGO" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x59C3D0, "O CARGOTOP" } /* "O CARGOTOP" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x59C0B0, "O CARGOCONTAINER" } /* "O CARGOCONTAINER" */,
	{ 6, 3, 1, 1000000, 0, (ObjectFuncPtr)0x59BDA0, "O ENEMYCONTAINER" } /* "O ENEMYCONTAINER" */,
	{ 2, 3, 1, 1000000, 0, (ObjectFuncPtr)0x59BB40, "O CONNECTION" } /* "O CONNECTION" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A4D70, "O CARGOSTART" } /* "O CARGOSTART" */,
	{ 6, 3, 0, 0, 0, (ObjectFuncPtr)0x5A4D70, "O CARGOSTART" } /* "O CARGOSTART" */,
	{ 2, 2, 0, 0, 0, E105Enemy_Main_R, "E E105" } /* "E E105" */,
	{ 2, 3, 1, 160000, 0, (ObjectFuncPtr)0x4FA320, "O FROG " } /* "O FROG " */,
	{ LoadObj_Data1, 3, 1, 1000000.0f, 0, MysticMelody_Main, "O KNUDAI" }, //Mystic Melody
	{ LoadObj_Data1, 3, 0, 0, 0, PlatformMM_Main, "O KDASIBA" }
};


ObjectList HotShelter1ObjectList = { arraylengthandptrT(HotShelter1ObjectList_list, int) };
ObjectList HotShelter2ObjectList = { arraylengthandptrT(HotShelter2ObjectList_list, int) };
ObjectList HotShelter3ObjectList = { arraylengthandptrT(HotShelter3ObjectList_list, int) };

DataArray(DeathZone*, HotShelterDeathZones, 0x17c45b8, 3);

//HS act Gamma Kill Plane
//Add a Kill Plane below the train in case the player fall.

NJS_MATERIAL matlist_013C389C[] = {
	{ { 0xFFBFBFBF }, { 0xFFFFFFFF }, 6, 0, NJD_D_100 | NJD_FILTER_BILINEAR | NJD_DA_INV_SRC | NJD_SA_SRC }
};

Sint16 poly_013C38B0[] = {
	6, 0, 1, 2, 3, 4, 5
};

NJS_MESHSET_SADX meshlist_013C38C0[] = {
	{ NJD_MESHSET_TRIMESH | 0, 1, poly_013C38B0, NULL, NULL, NULL, NULL, NULL }
};

NJS_VECTOR vertex_013C38E0[] = {
	{ -342, 136.4f, -3958 },
	{ -342, 136.4f, -3271 },
	{ 1, 136.4f, -3958 },
	{ 1, 136.4f, -3271 },
	{ 336, 136.4f, -3958 },
	{ 336, 136.4f, -3271 }
};

NJS_VECTOR normal_013C3928[] = {
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

NJS_MODEL_SADX attach_013C3970 = { vertex_013C38E0, normal_013C3928, LengthOfArray<Sint32>(vertex_013C38E0), meshlist_013C38C0, matlist_013C389C, LengthOfArray<Uint16>(meshlist_013C38C0), LengthOfArray<Uint16>(matlist_013C389C), { -3, 136.4f, -3614.5f }, 482.6109f, NULL };

NJS_OBJECT object_013C399C = { NJD_EVAL_UNIT_POS | NJD_EVAL_UNIT_ANG | NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_013C3970, 0, 0, 0, 0, 0, 0, 1, 1, 1, NULL, NULL };

NJS_MATERIAL matlist_013C3714[] = {
	{ { 0xFFBFBFBF }, { 0xFFFFFFFF }, 6, 0, NJD_D_100 | NJD_FILTER_BILINEAR | NJD_DA_INV_SRC | NJD_SA_SRC }
};

Sint16 poly_013C3728[] = {
	6, 1, 2, 4, 5, 7, 8,
	6, 7, 6, 4, 3, 1, 0
};

NJS_MESHSET_SADX meshlist_013C3744[] = {
	{ NJD_MESHSET_TRIMESH | 0, 2, poly_013C3728, NULL, NULL, NULL, NULL, NULL }
};

NJS_VECTOR vertex_013C3760[] = {
	{ -433.2128f, -316, -1490.935f },
	{ -433.2128f, -316, -838 },
	{ -433.2128f, -316, -185.0647f },
	{ -21, -316, -1490.935f },
	{ -21, -316, -838 },
	{ -21, -316, -185.0647f },
	{ 391.2128f, -316, -1490.935f },
	{ 391.2128f, -316, -838 },
	{ 391.2128f, -316, -185.0647f }
};

NJS_VECTOR normal_013C37D0[] = {
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

NJS_MODEL_SADX attach_013C383C = { vertex_013C3760, normal_013C37D0, LengthOfArray<Sint32>(vertex_013C3760), meshlist_013C3744, matlist_013C3714, LengthOfArray<Uint16>(meshlist_013C3744), LengthOfArray<Uint16>(matlist_013C3714), { -21, -316, -838 }, 772.1683f, NULL };

NJS_OBJECT object_013C3868 = { NJD_EVAL_UNIT_POS | NJD_EVAL_UNIT_ANG | NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_013C383C, 0, 0, 0, 0, 0, 0, 1, 1, 1, NULL, NULL };

NJS_MATERIAL matlist_013C417C[] = {
	{ { 0xFFBFBFBF }, { 0xFFFFFFFF }, 6, 0, NJD_D_100 | NJD_FILTER_BILINEAR | NJD_DA_INV_SRC | NJD_SA_SRC }
};

Sint16 poly_013C4190[] = {
	6, 1, 2, 4, 5, 7, 8,
	6, 7, 6, 4, 3, 1, 0
};

NJS_MESHSET_SADX meshlist_013C41AC[] = {
	{ NJD_MESHSET_TRIMESH | 0, 2, poly_013C4190, NULL, NULL, NULL, NULL, NULL }
};

NJS_VECTOR vertex_013C41C8[] = {
	{ -399, 0, -2260 },
	{ -399, 0, -1860 },
	{ -399, 0, -1460 },
	{ 1, 0, -2260 },
	{ 1, 0, -1860 },
	{ 1, 0, -1460 },
	{ 401, 0, -2260 },
	{ 401, 0, -1860 },
	{ 401, 0, -1460 }
};

NJS_VECTOR normal_013C4238[] = {
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

NJS_MODEL_SADX attach_013C42A4 = { vertex_013C41C8, normal_013C4238, LengthOfArray<Sint32>(vertex_013C41C8), meshlist_013C41AC, matlist_013C417C, LengthOfArray<Uint16>(meshlist_013C41AC), LengthOfArray<Uint16>(matlist_013C417C), { 1, 0, -1860 }, 565.6854f, NULL };

NJS_OBJECT object_013C42D0 = { NJD_EVAL_UNIT_POS | NJD_EVAL_UNIT_ANG | NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_013C42A4, 0, 0, 0, 0, 0, 0, 1, 1, 1, NULL, NULL };

NJS_MATERIAL matlist_013C4400[] = {
	{ { 0xFFBFBFBF }, { 0xFFFFFFFF }, 6, 0, NJD_D_100 | NJD_FILTER_BILINEAR | NJD_DA_INV_SRC | NJD_SA_SRC }
};

Sint16 poly_013C4414[] = {
	0x8000u | 6, 0, 3, 1, 4, 2, 5
};

NJS_MESHSET_SADX meshlist_013C4424[] = {
	{ NJD_MESHSET_TRIMESH | 0, 1, poly_013C4414, NULL, NULL, NULL, NULL, NULL }
};

NJS_VECTOR vertex_013C4440[] = {
	{ -4294.995f, -545.7822f, -6115.803f },
	{ -4294.995f, -545.7822f, -3112.957f },
	{ -4294.995f, -545.7822f, -110.1114f },
	{ 512.1854f, -545.7822f, -6115.803f },
	{ 512.1854f, -545.7822f, -3112.957f },
	{ 512.1854f, -545.7822f, -110.1114f }
};

NJS_VECTOR normal_013C4488[] = {
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

NJS_MODEL_SADX attach_013C44D0 = { vertex_013C4440, normal_013C4488, LengthOfArray<Sint32>(vertex_013C4440), meshlist_013C4424, matlist_013C4400, LengthOfArray<Uint16>(meshlist_013C4424), LengthOfArray<Uint16>(matlist_013C4400), { -1891.405f, -545.7822f, -3112.957f }, 3846.34f, NULL };

NJS_OBJECT object_013C44FC = { NJD_EVAL_UNIT_ANG | NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_013C44D0, 0, -250.7f, 0, 0, 0, 0, 1, 1, 1, NULL, NULL };

NJS_MATERIAL matlist_01C319B8[] = {
	{ { 0xFFBFBFBF }, { 0xFFFFFFFF }, 6, 0, NJD_D_100 | NJD_DA_INV_SRC | NJD_SA_SRC }
};

Sint16 poly_01C319CC[] = {
	0, 1, 3, 2
};

NJS_MESHSET_SADX meshlist_01C319D4[] = {
	{ NJD_MESHSET_4 | 0, 1, poly_01C319CC, NULL, NULL, NULL, NULL, NULL }
};

NJS_VECTOR vertex_01C319F0[] = {
	{ -1013, -3100.614f, -819 },
	{ -1013, -3100.614f, 2805 },
	{ 6884, -3100.614f, 2877 },
	{ 6876, -3100.614f, -827 }
};

NJS_VECTOR normal_01C31A20[] = {
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 0 }
};

NJS_MODEL_SADX attach_01C31A50 = { vertex_01C319F0, normal_01C31A20, LengthOfArray<Sint32>(vertex_01C319F0), meshlist_01C319D4, matlist_01C319B8, LengthOfArray<Uint16>(meshlist_01C319D4), LengthOfArray<Uint16>(matlist_01C319B8), { 2935.5f, -3100.614f, 1025 }, 4361.256f, NULL };

NJS_OBJECT object_01C31A10 = { NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_01C31A50, 500, 12930.38f, -400, 0, 0xFFFFC50A, 0, 1, 1, 1, NULL, NULL };

DeathZone HotShelter3DeathZones[] = {
	{ CharacterFlags_Sonic | CharacterFlags_Eggman | CharacterFlags_Tails | CharacterFlags_Knuckles | CharacterFlags_Tikal | CharacterFlags_Amy | CharacterFlags_Gamma | CharacterFlags_Big, &object_013C399C },
	{ CharacterFlags_Sonic | CharacterFlags_Eggman | CharacterFlags_Tails | CharacterFlags_Knuckles | CharacterFlags_Tikal | CharacterFlags_Amy | CharacterFlags_Gamma | CharacterFlags_Big, &object_013C3868 },
	{ CharacterFlags_Sonic | CharacterFlags_Eggman | CharacterFlags_Tails | CharacterFlags_Knuckles | CharacterFlags_Tikal | CharacterFlags_Amy | CharacterFlags_Gamma | CharacterFlags_Big, &object_013C42D0 },
	{ CharacterFlags_Sonic | CharacterFlags_Eggman | CharacterFlags_Tails | CharacterFlags_Knuckles | CharacterFlags_Tikal | CharacterFlags_Amy | CharacterFlags_Gamma | CharacterFlags_Big, &object_013C44FC },
	{ CharacterFlags_Sonic | CharacterFlags_Eggman | CharacterFlags_Tails | CharacterFlags_Knuckles | CharacterFlags_Tikal | CharacterFlags_Amy | CharacterFlags_Gamma | CharacterFlags_Big, &object_01C31A10 },
	{ 0 }
};
