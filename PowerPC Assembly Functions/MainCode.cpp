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

// Set asm output path here:
#if DOLPHIN_BUILD
//static string OutputAsmPath = "C:\\Users\\Ilir\\Documents\\Games\\Brawl\\Project+Modding\\ProjectMCodes\\GCTRM\\Tourney+\\Source\\Netplay\\Net-CodeMenu.asm";
static string OutputAsmPath = "./Net-CodeMenu.asm";
#else
//static string OutputAsmPath = "C:\\Users\\Ilir\\Documents\\Games\\Brawl\\Project+Modding\\ProjectMCodes\\GCTRM\\Tourney+\\Source\\Project+\\CodeMenu.asm";
static string OutputAsmPath = "./CodeMenu.asm";
#endif

// --- Optional Settings ---
// GCTRM settings (assumes GCTRM, RSBE01.txt, and boost.txt is in folder)
static bool RunGCTRM = false;
static string BuildFolder = "C:\\Users\\Ilir\\Documents\\Games\\Brawl\\Project+ Modding\\Experimental\\SD\\Project+\\";

// Virtual SD Sync settings
static bool RunVSDSync = false;
static string VSDExePath = "C:\\Users\\Ilir\\Documents\\Games\\Brawl\\Project+ Modding\\VSDSync-0.1.3.2\\VSDSync.exe";

int main()
{	

	string TextPath = "../ASM.txt";


#if COLLECT_EXTERNAL_EX_CHARACTERS == true
	std::ofstream codeMenuLogOutput;
	codeMenuLogOutput.open(changelogFileName);
	codeMenuLogOutput << "PowerPC Assembly Functions (Code Menu Building Utility)\n";
	std::cout << "PowerPC Assembly Functions (Code Menu Building Utility)\n";
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


	CodeStart(TextPath);
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

	MakeASM(TextPath, OutputAsmPath);

	// Assemble using GCTRM
	if (RunGCTRM) {
		string GCTRMExePath = BuildFolder + "\\GCTRealMate.exe";
#if DOLPHIN_BUILD
		string mainGCTTextfile = BuildFolder + "\\NETPLAY.txt";
		string boostGCTTextfile = BuildFolder + "\\NETBOOST.txt";
#else	
		string mainGCTTextfile = BuildFolder + "\\RSBE01.txt";
		string boostGCTTextfile = BuildFolder + "\\BOOST.txt";
#endif
		system(("\"\"" + GCTRMExePath + "\"" + " -g -l \"" + mainGCTTextfile + "\"\"").c_str());
		system(("\"\"" + GCTRMExePath + "\"" + " -g -l \"" + boostGCTTextfile + "\"\"").c_str());
	}

	if (RunVSDSync) {
		system(("\"\"" + VSDExePath + "\"\"").c_str());
	}

}