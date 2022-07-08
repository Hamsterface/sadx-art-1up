#include "pch.h"
#include "IniFile.hpp"
// or #include "stdafx.h" for previous Visual Studio versions

#define ReplacePVM(a, b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM")

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		// Executed at startup, contains helperFunctions and the path to your mod (useful for getting the config file.)
		// This is where we override functions, replace static data, etc.
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

		bool borders = config->getBool("", "Borders", true);
		bool altSuper = config->getBool("", "AltSuper", false);
		if (!borders) {
			ReplacePVM("OBJ_REGULAR", "OBJ_REGULAR_NOBORDER");

			if (altSuper) {
				ReplacePVM("SUPERSONIC_EXTRA", "SUPERSONIC_EXTRA_ALTERNATE_NOBORDER");
			}
			else {
				ReplacePVM("SUPERSONIC_EXTRA", "SUPERSONIC_EXTRA_NOBORDER");
			}
		}
		else {
			ReplacePVM("OBJ_REGULAR", "OBJ_REGULAR_HD"); // Redundant with HD GUI but ensures compatibility
			if (altSuper) {
				ReplacePVM("SUPERSONIC_EXTRA", "SUPERSONIC_EXTRA_ALTERNATE");
			}
		}
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer }; // This is needed for the Mod Loader to recognize the DLL.
}