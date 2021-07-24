#pragma once

//Mission Card Enum 0 = capsule, 1 = Lost Chao, 2 = Emeralds Knux, 3 = Beat Sonic, 4 = Final Egg, 5 = Froggy, 6 = LW, 7 = missile, 8 = 100 rings, 9 = rescue tails, 10 = Zero, 11+ Race
enum MissionCard {
	CapsuleCard, LostChaoCard, EmeraldKnuxCard, SonicRaceCard, FinalEggCard, FroggyCard,
	LostWorldCard, MissileRaceCard, RingsCard, RescueTailsCard, BalloonCard, TailsRaceCard, KnuxRaceCard, AmyRaceCard,
	BigRaceCard, GammaRaceCard, EggmanRaceCard, TikalRaceCard, MSRaceCard, E103Card, E104Card, E105Card, EmeraldCasinoCard, EmeraldICCard, EmeraldWVCard, SonicDollCard
};

enum CurMission {

	SADX_Mission, Mission1_Variation, Mission2_100Rings, Mission3_LostChao
};