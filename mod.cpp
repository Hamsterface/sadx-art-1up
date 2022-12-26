#include "pch.h"
#include "IniFile.hpp"

using namespace std;

extern "C"
{
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		// texture names in obj_regular to replace
		const char* namesToReplace[7] = {
			"item_1up",
			"1uptails",
			"1upknuck",
			"1upamy",
			"1upbig",
			"1up102",
			"1upmetal"
		};

		// respective indices for above list
		uint32_t gbix[7] = {
			4031,
			4004,
			4000,
			4001,
			4002,
			4003,
			710226
		};

		string moddir = path;

		// Read config
		const IniFile* config = new IniFile(moddir + "\\config.ini");

		bool borders = config->getBool("", "Borders", true);
		string style = config->getString("", "Style", "Default");

		bool shuffle = (style == "Shuffle");
		bool altSuper = shuffle || (style == "Shuffle Super Sonic");

		// Replaced textures use suffixes for alternates, e.g. item_1up_SHUFFLE_NOBORDERS.png
		string suffix = shuffle ? "_SHUFFLE" : "";
		if (!borders) suffix += "_NOBORDER";

		const char* filepath = "";
		for (int i = 0; i < 7; i++)
		{
			// e.g.   <mod folder> \replacetex\1UP_CUSTOM\         item_1up        _SHUFFLE   .png
			filepath = (moddir + "\\replacetex\\1UP_CUSTOM\\" + namesToReplace[i] + suffix + ".png").c_str();
			
			helperFunctions.ReplaceTexture("OBJ_REGULAR", namesToReplace[i], filepath, gbix[i], 128, 128);
		}

		// Super Sonic has an additional option
		suffix = altSuper ? "_SHUFFLE" : "";
		if (!borders) suffix += "_NOBORDER";
		
		// e.g.   <mod folder> \replacetex\1UP_CUSTOM\  1upsuper   _SHUFFLE   .png
		filepath = (moddir + "\\replacetex\\1UP_CUSTOM\\1upsuper" + suffix + ".png").c_str();
		helperFunctions.ReplaceTexture("SUPERSONIC_EXTRA", "1upsuper", filepath, 6544685, 128, 128);
		
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}