#include "stdafx.h"
#include "ReplayFix.h"
#include "Controls.h"
#include "StopStartAlts.h"
#include "Save States.h"
#include "Miscellaneous Code.h"
#include "StopDPadOnSSS (except Wiimote).h"
#include "DrawDI.h"
#include "Code Menu.h"
#include "IASA Overlay.h"
#include "Control Codes.h"
#include "Last Character Auto Select.h"
#include "Tag Based Costumes.h"
#include "Light Shield.h"
#include "IkeClimbers.h"
#include "AIDisplay.h"
#include "C++Injection.h"
#include "_AdditionalCode.h"
//#include "FPS Display.h"
using namespace std;

bool MakeASM(string TextFilePath, string OutputAsmPath)
{
	string codeString;

	ifstream textFile(TextFilePath);
	if (textFile.is_open())
	{
		getline(textFile, codeString);
	}

	else {
		cout << "Error: Unable to open txt file";
		return false;
	}

	ofstream asmFile(OutputAsmPath);
	if (asmFile.is_open())
	{
		for (int i = 0; i < codeString.length(); i += 16) {
			asmFile << "* " << codeString.substr(i + 0, 8) << " " << codeString.substr(i + 8, 8) << "\n";
		}

		asmFile.close();
	}

	else {
		cout << "Unable to open ASM file, check the OutputAsmPath";
		return false;
	}
}



int main()
{
	std::cout << "PowerPC Assembly Functions (Code Menu Building Utility " << lava::version << ")\n";
	if (lava::folderExists(outputFolder))
	{
		initMenuFileStream();
		string OutputTextPath = asmTextOutputFilePath;

		std::ofstream codeMenuLogOutput;
		codeMenuLogOutput.open(outputFolder + changelogFileName);
		codeMenuLogOutput << "PowerPC Assembly Functions (Code Menu Building Utility " << lava::version << ")\n";
		codeMenuLogOutput << "Building \"" << cmnuFileName << "\" for ";
		std::cout << "Building \"" << cmnuFileName << "\" for ";
		switch (BUILD_TYPE)
		{
		case NORMAL:
		{
			codeMenuLogOutput << "LegacyTE";
			std::cout << "LegacyTE";
			break;
		}
		case PMEX:
		{
			codeMenuLogOutput << "Project M EX";
			std::cout << "Project M EX";
			break;
		}
		case PROJECT_PLUS:
		{
			if (PROJECT_PLUS_EX_BUILD == true)
			{
				codeMenuLogOutput << "Tournament Addition EX";
				std::cout << "Tournament Addition EX";
			}
			else
			{
				codeMenuLogOutput << "Tournament Addition";
				std::cout << "Tournament Addition";
			}
			break;
		}
		default:
		{
			codeMenuLogOutput << "Unknown";
			std::cout << "Unknown";
			break;
		}
		}
		if (BUILD_NETPLAY_FILES == true)
		{
			codeMenuLogOutput << " Netplay";
			std::cout << " Netplay";
		}
		if (DOLPHIN_BUILD == true)
		{
			codeMenuLogOutput << " (Dolphin)";
			std::cout << " (Dolphin)";
		}
		else
		{
			codeMenuLogOutput << " (Console)";
			std::cout << " (Console)";
		}
		codeMenuLogOutput << "\n";
		std::cout << "\n";
		if (DOLPHIN_BUILD == true)
		{
			codeMenuLogOutput << "Note: This code menu was configured for use with Dolphin only, and IS NOT COMPATIBLE with consoles!\n";
			codeMenuLogOutput << "Attempting to use this code menu on console can (and likely will) damage your system.\n";
			std::cout << "Note: This code menu was configured for use with Dolphin only, and IS NOT COMPATIBLE with consoles!\n";
			std::cout << "Attempting to use this code menu on console can (and likely will) damage your system.\n";
		}
		if (IS_DEBUGGING == true)
		{
			codeMenuLogOutput << "Note: General Debug Flag is ON!\n";
			std::cout << "Note: General Debug Flag is ON!\n";
		}
		if (EON_DEBUG_BUILD == true)
		{
			codeMenuLogOutput << "Note: Eon's Debug Flag is ON!\n";
			std::cout << "Note: Eon's Debug Flag is ON!\n";
		}

		codeMenuLogOutput << "\n";
		std::cout << "\n";

#if COLLECT_EXTERNAL_EX_CHARACTERS == true
		codeMenuLogOutput << "Adding Characters to Code Menu from \"" << exCharInputFileName << "\"...\n";
		std::cout << "Adding Characters to Code Menu from \"" << exCharInputFileName << "\"...\n";

		bool exCharInputOpenedSuccessfully = 0;
		std::vector<std::pair<std::string, u16>> nameIDPairs = lava::collectNameSlotIDPairs(exCharInputFileName, exCharInputOpenedSuccessfully);
		if (exCharInputOpenedSuccessfully)
		{
			if (nameIDPairs.size())
			{
				// Builds a map from the predefined character and character ID lists.
				// Doing it this way ensures that paired values stay together, and handles sorting automatically when we insert new entries.
				std::map<std::string, u16> zippedIDMap;
				for (int i = 0; i < CHARACTER_LIST.size(); i++)
				{
					zippedIDMap.insert(std::make_pair(CHARACTER_LIST[i], CHARACTER_ID_LIST[i]));
				}
				for (int i = 0; i < nameIDPairs.size(); i++)
				{
					std::pair<std::string, u16>* currPair = &nameIDPairs[i];
					if (currPair->second != SHRT_MAX)
					{
						auto itr = zippedIDMap.insert(*currPair);
						// If the entry was newly added to the list (ie. not overwriting existing data), announce it.
						if (itr.second)
						{
							std::cout << "[ADDED] " << itr.first->first << " (Slot ID = 0x" << lava::numToHexStringWithPadding(itr.first->second, 2) << ")\n";
							codeMenuLogOutput << "[ADDED] " << itr.first->first << " (Slot ID = 0x" << lava::numToHexStringWithPadding(itr.first->second, 2) << ")\n";
						}
						// Otherwise, announce what was changed.
						else if (itr.first != zippedIDMap.end())
						{
							itr.first->second = currPair->second;
							std::cout << "[CHANGED] " << itr.first->first << " (Slot ID = 0x" << lava::numToHexStringWithPadding(itr.first->second, 2) << ")\n";
							codeMenuLogOutput << "[CHANGED] " << itr.first->first << " (Slot ID = 0x" << lava::numToHexStringWithPadding(itr.first->second, 2) << ")\n";
						}
					}
					else
					{
						std::cerr << "[ERROR] Invalid Slot ID specified! The character \"" << currPair->first << "\" will not be added to the Code Menu!\n";
						codeMenuLogOutput << "[ERROR] Invalid Slot ID specified! The character \"" << currPair->first << "\" will not be added to the Code Menu!\n";
					}
				}

				// Write the newly edited list back into the list vectors
				CHARACTER_LIST.clear();
				CHARACTER_ID_LIST.clear();
				for (auto itr = zippedIDMap.begin(); itr != zippedIDMap.end(); itr++)
				{
					CHARACTER_LIST.push_back(itr->first);
					CHARACTER_ID_LIST.push_back(itr->second);
				}
			}
			else
			{
				std::cout << "[WARNING] \"" << exCharInputFileName << "\" was opened successfully, but no valid character entries could be found.\n";
				codeMenuLogOutput << "[WARNING] \"" << exCharInputFileName << "\" was opened successfully, but no valid character entries could be found.\n";
			}
		}
		else
		{
			std::cout << "[ERROR] Couldn't open \"" << exCharInputFileName << "\"! Ensure that the file is present in this folder and try again!\n";
			codeMenuLogOutput << "[ERROR] Couldn't open \"" << exCharInputFileName << "\"! Ensure that the file is present in this folder and try again!\n";
		}
		//Print the results.
		std::cout << "\nFinal Character List:\n";
		codeMenuLogOutput << "\nFinal Character List:\n";
		for (std::size_t i = 0; i < CHARACTER_LIST.size(); i++)
		{
			std::cout << "\t" << CHARACTER_LIST[i] << " (Slot ID = 0x" << lava::numToHexStringWithPadding(CHARACTER_ID_LIST[i], 2) << ")\n";
			codeMenuLogOutput << "\t" << CHARACTER_LIST[i] << " (Slot ID = 0x" << lava::numToHexStringWithPadding(CHARACTER_ID_LIST[i], 2) << ")\n";
		}

		std::cout << "\n";
		codeMenuLogOutput << "\n";
#endif

		CodeStart(OutputTextPath);
		//place all ASM code here

		//ReplayFix();

		//NameIsFound();

		//MenuControlCodes();

		//StopStartAltFunctions();

		//StopPokemonTrainerSwitch();

		//StopDPadOnSSS();

		//ConvertButtons();

		//ItemSpawnControl();

		//ClearASLData();

		//SetTeamAttackTraining();

		//LXPGreenOverlayFix();

		CodeMenu(); tagBasedCostumes();

		//musicPercentCode();

		//DoubleFighterTest();

		//UCF();

		//CStickSlowFix();

		//FixStickyRAlts();

		//SelectLastCharacter();

		//FixTr4shTeamToggle();

		//cstickTiltTest();

		//FPSDisplay();

		//CStickTiltFix();

		//DBZModeTest();

		//slipperyTechs();

		//lightShield();

		//IkeClimbers();

		//fixStanimaTextBug();

		//AIDisplay();

		//loadCppCodes(); writeInjectionsRepeat();

		CodeEnd();

		std::cout << "\n";
		if (lava::fileExists(cmnuBuildLocationFilePath))
		{
			if (lava::offerCopyOverAndBackup(cmnuOutputFilePath, cmnuBuildLocationFilePath))
			{
				codeMenuLogOutput << "Note: Backed up \"" << cmnuBuildLocationFilePath << "\" and overwrote it with the newly built Code Menu.\n";
			}
		}
		else if (lava::folderExists(buildFolder + cmnuBuildLocationDirectory))
		{
			if (lava::offerCopy(cmnuOutputFilePath, cmnuBuildLocationFilePath))
			{
				codeMenuLogOutput << "Note: Copied newly built Code Menu to \"" << cmnuBuildLocationFilePath << "\".\n";
			}
		}
		if (MakeASM(OutputTextPath, asmOutputFilePath))
		{
			if (lava::fileExists(asmBuildLocationFilePath))
			{
				if (lava::offerCopyOverAndBackup(asmOutputFilePath, asmBuildLocationFilePath))
				{
					codeMenuLogOutput << "Note: Backed up \"" << asmBuildLocationFilePath << "\" and overwrote it with the newly built ASM.\n";
				}
			}
			else if (lava::folderExists(buildFolder + asmBuildLocationDirectory))
			{
				if (lava::offerCopy(asmOutputFilePath, asmBuildLocationFilePath))
				{
					codeMenuLogOutput << "Note: Copied newly built ASM to \"" << asmBuildLocationFilePath << "\".\n";
				}
			}
			if (lava::handleAutoGCTRMProcess(codeMenuLogOutput) && BUILD_NETPLAY_FILES)
			{
				codeMenuLogOutput << "Note: The built GCTs are configured for use in Dolphin Netplay only, and ARE NOT COMPATIBLE with consoles!\n";
				codeMenuLogOutput << "Attempting to use them on console can (and likely will) damage your system.\n\n";
			}
		}
	}
	else
	{
		std::cerr << "[ERROR] The expected output folder (\"" << outputFolder << "\") couldn't be found in this folder. Ensure that the specified folder exists in the same folder as this program and try again.\n\n";
	}
	std::cout << "Press any key to exit.\n";
	_getch();
}