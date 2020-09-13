#pragma once

StartPosition EW_StartPositions[]{
	{ 21, 0,{ -480, 19, 1000}, 0 }
};



ObjectFunc(EW_Bomb, 0x57a110);
DataPointer(char, EWDamageCheck, 0x3C6CC98);
DataPointer(char, EWHit, 0x3c6cc9c);
