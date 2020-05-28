#pragma once


void DynCol_Add(ObjectMaster* a1, uint8_t col);
void DynCol_Delete(ObjectMaster* a1);
bool DynColRadius(ObjectMaster* a1, float radius, uint8_t col);
ModelInfo* LoadObjectModel(const char* name);
void FreeMDL(ModelInfo* pointer);