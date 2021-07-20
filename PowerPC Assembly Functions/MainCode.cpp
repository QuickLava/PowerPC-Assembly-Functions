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
//#include "FPS Display.h"
using namespace std;

bool MakeASM(string TextFilePath, string OutputAsmPath);
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
	string OutputTextPath = "C:\\Users\\AZPM\\Downloads\\DesiacXs_Code_Menu\\PowerPC-Assembly-Functions-master\\output\\asm.txt";
	string OutputAsmPath = "C:\\Users\\AZPM\\Downloads\\DesiacXs_Code_Menu\\PowerPC-Assembly-Functions-master\\output\\CodeMenu.asm";

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

	MakeASM(OutputTextPath, OutputAsmPath);
}