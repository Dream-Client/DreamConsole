#pragma once


#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <Windows.h>

#include <shellapi.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <codecvt>

#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <sstream>
#include <filesystem>

using namespace std;

#include "enums.h"
#include "Utils.h"
#include "Logger.h"