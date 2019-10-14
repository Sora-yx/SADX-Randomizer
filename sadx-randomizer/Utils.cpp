#include "stdafx.h"
#include "Utils.h"

bool isValueInArray(int *array, int value, int size)
{
	for (int i = 0; i < size; i++) {
		if (array[i] == value)
			return true;
	}

	return false;
}

int isvalid(int nombre, int* tab, int taille)
{
	int i;
	for (i = 0; i < taille; i++)
		if (tab[i] == nombre)
			return 0;
	return 1;
}