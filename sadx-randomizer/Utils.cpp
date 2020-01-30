#include "stdafx.h"
#include "Utils.h"

bool isValueInArray(int* array, int value, int size)
{
	for (int i = 0; i < size; i++) {
		if (array[i] == value)
			return true;
	}

	return false;
}