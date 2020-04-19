#pragma once

StartPosition EV_StartPositions[]{
	{ 22, 0,{ 260, 50, 0 }, 0 }
};

DataPointer(char, EggViperHP, 0x3c6e164);
VoidFunc(FUN057ef90, 0x57ef90);
VoidFunc(EggViperBounceHit, 0x441280);

ObjectFunc(EV_RegularLaser, 0x57f430);
ObjectFunc(EV_Explosion, 0x583860);
ObjectFunc(EV_LaserRain, 0x583c20);
ObjectFunc(EV_Hit, 0x582bc0);
ObjectFunc(EV_Test, 0x581f90);
ObjectFunc(EV_DestroyAllPlatforms, 0x57faf0);
ObjectFunc(EV_DestroyOnePlatform, 0x57fdb0);