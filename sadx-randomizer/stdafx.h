#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

#include <SADXModLoader.h>
#include "LandTableInfo.h"
#include "Trampoline.h"
#include "ModelInfo.h"
#include "IniFile.hpp"

#include "SADXFunctions.h"
#include "SADXVariables.h"
#include "FunctionHook.h"
#include "startup.h"
#include "RandomHelpers.h"
#include "CharactersSettings.h"
#include "objects.h"
#include "Credits.h"
#include "hud.h"
#include "StageSettings.h"
#include "utils.h"
#include "Cutscene.h"
#include "level.h"

#include "sound.h"