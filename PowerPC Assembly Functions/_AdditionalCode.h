#ifndef ADDITIONAL_CODE_H
#define ADDITIONAL_CODE_H

#include "Code Menu.h"
#include <conio.h>
#include <iomanip>
#include <sstream>

namespace lava
{
	const std::string version = "v1.0.0-TournamentAddition";

	// General Utility
	int stringToNum(const std::string& stringIn, bool allowNeg = 1, int defaultVal = INT_MAX);
	std::string numToHexStringWithPadding(std::size_t numIn, std::size_t paddingLength);
	std::string numToDecStringWithPadding(std::size_t numIn, std::size_t paddingLength);

	// File System Management
	bool fileExists(std::string filepathIn);
	bool folderExists(std::string folderpathIn);
	bool copyFile(std::string sourceFile, std::string targetFile, bool overwriteExistingFile = 0);
	bool backupFile(std::string fileToBackup, std::string backupSuffix = ".bak", bool overwriteExistingBackup = 0);

	// Prompts and User-Interaction
	bool yesNoDecision(char yesKey, char noKey);
	bool offerCopyOverAndBackup(std::string fileToCopy, std::string fileToOverwrite);
	bool offerCopy(std::string fileToCopy, std::string fileToOverwrite);
	bool handleAutoGCTRMProcess(std::ostream& logOutput);

	// EX Character Functions
	std::vector<std::pair<std::string, u16>> collectNameSlotIDPairs(std::string exCharInputFilePath, bool& fileOpened);
}

#endif