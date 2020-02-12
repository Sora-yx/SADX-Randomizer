#pragma once
#include "stdafx.h"
#include "SADXModLoader.h"

void ChaoObj_Init(ObjectMaster* a1);
void ChaoObj_Delete(ObjectMaster* a1);
void ChaoObj_Reset(ObjectMaster* a1);
void Chao_LoadFiles();
void ChaoFix();
extern bool TPAmyVersion;