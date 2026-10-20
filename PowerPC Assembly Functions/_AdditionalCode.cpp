#include "stdafx.h"
#include "_AdditionalCode.h"

namespace lava
{
	const std::string builderVersion = "v1.6.7";
	// This is an optional string that'll print in the header of the produced log output if it's populated.
	// If you intend to edit the builder and redistribute a compiled executable version, I'd suggest editing this to
	// make it easier to find the repo the executable was compiled from in case someone wants to fork or otherwise reference it.
	const std::string builderFlavor = "";
	int CMNUCopyOverride = INT_MAX;
	int ASMCopyOverride = INT_MAX;
	int GCTBuildOverride = INT_MAX;
	int CloseOnFinishBypass = INT_MAX;

	bool copyFile(std::filesystem::path sourceFile, std::filesystem::path targetFile, bool overwriteExistingFile)
	{
		// Record result
		bool result = 0;
		// If the incoming paths don't point to the same file...
		if (sourceFile != targetFile)
		{
			result = std::filesystem::copy_file(sourceFile, targetFile, (overwriteExistingFile) ? 
				std::filesystem::copy_options::overwrite_existing : std::filesystem::copy_options::skip_existing);
		}
		return result;
	}
	bool backupFile(std::string fileToBackup, std::string backupSuffix, bool overwriteExistingBackup)
	{
		return copyFile(fileToBackup, fileToBackup + backupSuffix, overwriteExistingBackup);
	}

	bool yesNoDecision(char yesKey, char noKey)
	{
		char keyIn = ' ';
		yesKey = std::tolower(yesKey);
		noKey = std::tolower(noKey);
		while (keyIn != yesKey && keyIn != noKey)
		{
			keyIn = _getch();
			keyIn = std::tolower(keyIn);
		}
		return (keyIn == yesKey);
	}
	bool offerCopyOverAndBackup(std::string fileToCopy, std::string fileToOverwrite, int decisionOverride)
	{
		bool backupSucceeded = 0;
		bool copySucceeded = 0;

		if (std::filesystem::is_regular_file(fileToCopy) && std::filesystem::is_regular_file(fileToOverwrite))
		{
			std::cout << "\nDetected \"" << fileToOverwrite << "\".\n" <<
				"Would you like to copy \"" << fileToCopy << "\" over it? " <<
				"A backup will be made of the existing file.\n";
			std::cout << "[Press 'Y' for Yes, 'N' for No]\n";
			if ((decisionOverride == INT_MAX && yesNoDecision('y', 'n')) || (decisionOverride != INT_MAX && decisionOverride != 0))
			{
				std::cout << "Making backup... ";
				if (lava::backupFile(fileToOverwrite, ".bak", 1))
				{
					backupSucceeded = 1;
					std::cout << "Successfully backed up file to \"" << fileToOverwrite << ".bak\"!\n";
					if (lava::backupFile(fileToOverwrite, ".orig", 0))
					{
						std::cout << "Note: Did extra backup of file's original state to \"" << fileToOverwrite << ".orig\"!\n";
					}

					std::cout << "Copying over \"" << fileToCopy << "\"... ";
					if (lava::copyFile(fileToCopy, fileToOverwrite, 1))
					{
						copySucceeded = 1;
						std::cout << "Success!\n";
					}
					else
					{
						std::cerr << "Failure! Please ensure that the destination file is able to be written to!\n";
					}
				}
				else
				{
					std::cerr << "Backup failed! Please ensure that \"" << fileToOverwrite << ".bak\" is able to be written to!\n";
				}
			}
			else
			{
				std::cout << "Skipping copy.\n";
			}
		}

		return backupSucceeded && copySucceeded;
	}
	bool offerCopy(std::string fileToCopy, std::string fileToOverwrite, int decisionOverride)
	{
		bool copySucceeded = 0;

		if (std::filesystem::is_regular_file(fileToCopy) && !std::filesystem::is_regular_file(fileToOverwrite))
		{
			std::cout << "\nCouldn't detect \"" << fileToOverwrite << "\".\n" << "Would you like to copy \"" << fileToCopy << "\" to that location?\n";
			std::cout << "[Press 'Y' for Yes, 'N' for No]\n";
			if ((decisionOverride == INT_MAX && yesNoDecision('y', 'n')) || (decisionOverride != INT_MAX && decisionOverride != 0))
			{
				std::cout << "Copying over \"" << fileToCopy << "\"... ";
				if (lava::copyFile(fileToCopy, fileToOverwrite, 1))
				{
					copySucceeded = 1;
					std::cout << "Success!\n";
				}
				else
				{
					std::cerr << "Failure! Please ensure that the destination file is able to be written to!\n";
				}
			}
			else
			{
				std::cout << "Skipping copy.\n";
			}
			std::cout << "\n";
		}

		return copySucceeded;
	}
	bool handleAutoGCTRMProcess(std::ostream& logOutput)
	{
		bool result = 0;

		if (std::filesystem::is_regular_file(GCTRMExePath) && std::filesystem::is_regular_file(mainGCTTextFile) && std::filesystem::is_regular_file(boostGCTTextFile))
		{
			std::cout << "\nDetected \"" << GCTRMExePath << "\".\nWould you like to build \"" << mainGCTFile << "\" and \"" << boostGCTFile << "\"? Backups will be made of any existing files.\n";

			bool mainGCTBackupNeeded = std::filesystem::is_regular_file(mainGCTFile);
			// If no backup is needed, we can consider the backup resolved. If one is, we cannot.
			bool mainGCTBackupResolved = !mainGCTBackupNeeded;
			// Same as above.
			bool boostGCTBackupNeeded = std::filesystem::is_regular_file(boostGCTFile);
			bool boostGCTBackupResolved = !boostGCTBackupNeeded;

			std::cout << "[Press 'Y' for Yes, 'N' for No]\n";
			if ((lava::GCTBuildOverride == INT_MAX && yesNoDecision('y', 'n')) || (lava::GCTBuildOverride != INT_MAX && lava::GCTBuildOverride != 0))
			{
				if (mainGCTBackupNeeded || boostGCTBackupNeeded)
				{
					std::cout << "Backing up files... ";
					if (mainGCTBackupNeeded)
					{
						mainGCTBackupResolved = lava::backupFile(mainGCTFile, ".bak", 1);
					}
					if (boostGCTBackupNeeded)
					{
						boostGCTBackupResolved = lava::backupFile(boostGCTFile, ".bak", 1);
					}
				}
				if (mainGCTBackupResolved && boostGCTBackupResolved)
				{
					std::cout << "Success! Running GCTRM:\n";
					result = 1;
					std::string commandFull = "\"" + GCTRMCommandBase + "\"" + mainGCTTextFile + "\"\"";
					std::cout << "\n" << commandFull << "\n";
					system(commandFull.c_str());
					if (mainGCTBackupNeeded)
					{
						logOutput << "Note: Backed up and rebuilt \"" << mainGCTFile << "\".\n";
					}
					else
					{
						logOutput << "Note: Built \"" << mainGCTFile << "\".\n";
					}

					commandFull = "\"" + GCTRMCommandBase + "\"" + boostGCTTextFile + "\"\"";
					std::cout << "\n" << commandFull << "\n";
					system(commandFull.c_str());
					if (boostGCTBackupNeeded)
					{
						logOutput << "Note: Backed up and rebuilt \"" << boostGCTFile << "\".\n";
					}
					else
					{
						logOutput << "Note: Built \"" << boostGCTFile << "\".";
					}
					std::cout << "\n";
				}
				else
				{
					std::cerr << "Something went wrong while backing up the files. Skipping GCTRM.\n";
				}
			}
			else
			{
				std::cout << "Skipping GCTRM.\n";
			}
		}
		return result;
	}
	bool placeASMInBuild(std::ostream& logOutput)
	{
		bool result = 0;

		std::size_t pathIndex = SIZE_MAX;
		for (std::size_t i = 0; pathIndex == SIZE_MAX && i < asmBuildLocationDirectories.size(); i++)
		{
			if (std::filesystem::is_directory(buildFolder + asmBuildLocationDirectories[i]))
			{
				pathIndex = i;
			}
		}

		if (pathIndex != SIZE_MAX)
		{
			std::string asmBuildLocationFilePath = buildFolder + asmBuildLocationDirectories[pathIndex] + asmFileName;
			if (std::filesystem::is_regular_file(asmBuildLocationFilePath))
			{
				result = lava::offerCopyOverAndBackup(asmOutputFilePath, asmBuildLocationFilePath, lava::ASMCopyOverride);
				if (result)
				{
					logOutput << "Note: Backed up \"" << asmBuildLocationFilePath << "\" and overwrote it with the newly built ASM.\n";
				}
			}
			else
			{
				result = lava::offerCopy(asmOutputFilePath, asmBuildLocationFilePath, lava::ASMCopyOverride);
				if (result)
				{
					logOutput << "Note: Copied newly built ASM to \"" << asmBuildLocationFilePath << "\".\n";
				}
			}
		}

		return result;
	}

	void WriteByteVec(const unsigned char* Bytes, u32 Address, unsigned char addressReg, unsigned char manipReg, std::size_t numToWrite, bool appendNullTerminator)
	{
		if (Address != ULONG_MAX)
		{
			SetRegister(addressReg, Address); // Load destination address into register
		}

		unsigned long fullWordCount = numToWrite / 4; // Get the number of 4 byte words we can make from the given vec.
		unsigned long currWord = 0;
		unsigned long offsetIntoBytes = 0;

		// For each word we can make...
		for (unsigned long i = 0; i < fullWordCount; i++)
		{
			// ... grab it, then store it in our manip register.
			currWord = lava::bytesToFundamental<unsigned long>(Bytes + offsetIntoBytes);
			SetRegister(manipReg, currWord);
			// Then write a command which stores the packed word into the desired location.
			STW(manipReg, addressReg, offsetIntoBytes);
			offsetIntoBytes += 0x04;
		}
		// For the remaining few bytes...
		for (offsetIntoBytes; offsetIntoBytes < numToWrite; offsetIntoBytes++)
		{
			// ... just write them one by one, no other choice really.
			SetRegister(manipReg, Bytes[offsetIntoBytes]);
			STB(manipReg, addressReg, offsetIntoBytes);
		}
		if (appendNullTerminator)
		{
			SetRegister(manipReg, 0x00);
			STB(manipReg, addressReg, offsetIntoBytes);
		}
	}
	void WriteByteVec(std::vector<unsigned char> Bytes, u32 Address, unsigned char addressReg, unsigned char manipReg, std::size_t numToWrite, bool appendNullTerminator)
	{
		WriteByteVec((const unsigned char*)Bytes.data(), Address, addressReg, manipReg, std::min<std::size_t>(Bytes.size(), numToWrite), appendNullTerminator);
	}
	void WriteByteVec(std::string Bytes, u32 Address, unsigned char addressReg, unsigned char manipReg, std::size_t numToWrite, bool appendNullTerminator)
	{
		WriteByteVec((const unsigned char*)Bytes.data(), Address, addressReg, manipReg, std::min<std::size_t>(Bytes.size(), numToWrite), appendNullTerminator);
	}

}