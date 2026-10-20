#pragma once

#include "stdafx.h"
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include <string>
#include <iostream>
#include <cassert>
#include <sstream>
#include "_lavaGeckoHexConvert.h"
#include "_CodeMenuHeaderConstants.h"
#include "_lavaOutputSplitter.h"
#include "_UtilitySubroutines.h"
using namespace std;

//set to 1 if debugging.  records positions every frame and compares them during replay
#define IS_DEBUGGING 0
#define NORMAL 0
#define PMEX 1
#define PROJECT_PLUS 2
#define BUILD_TYPE PROJECT_PLUS
#define DOLPHIN_BUILD false
#define EON_DEBUG_BUILD false
#define TOURNAMENT_ADDITION_BUILD false

// Selectively un-does a few changes made in the transition to P+ v3.0 which break functionality on earlier versions.
#define ENSURE_PRE_PP30_COMPAT false

// Character List Config Constants
// Defines different base versions of the character lists. 
// Set the characterListVersion variable equal to one of these values to include all characters up to and including that version.
// Eg. "clv_PROJECTM" includes all of vBrawl's characters, the special characters adapted for playability in PM, and the two PM newcomers.
enum characterListVersions
{
	clv_EMPTY = 0,
	clv_vBRAWL,
	clv_vBRAWL_SPECIAL_CHARS,
	clv_PROJECTM,
	clv_PPLUS,
	clv_PPEX_RIDLEY,
	clv_PPEX_WALUIGI,
	clv_PPEX_ALLOYS,
	clv_PPEX_SCEPTILE,
	clv_PPEX_DARK_SAMUS,
	clv_PPEX_ZERO,
	__clv_Count,
};
extern unsigned long characterListVersion;
std::string getCharacterListVersionName(unsigned long versionID);
// P+EX Configuration Macros
#define PROJECT_PLUS_EX_BUILD (true && (BUILD_TYPE == PROJECT_PLUS))
// Controls whether or not externally defined character, rosters, and themes are loaded into their respective lists.
// Relevant constants are defined in "Code Menu.cpp", and relevant code found in "MainCode.cpp".
#define COLLECT_EXTERNAL_EX_CHARACTERS (true)
#define COLLECT_EXTERNAL_ROSTERS (true && PROJECT_PLUS_EX_BUILD)
#define COLLECT_EXTERNAL_THEMES (true) // Note, this isn't locked to P+Ex builds, actually. Should work on any build with a Code Menu!

// Note: Console builds can't use Netplay anyway, so setting DOLPHIN_BUILD to false will force this off as well.
// This is important, as some Netplay codes save data directly to NAND, which is safe on Dolphin but not on console.
// As a result, attempting to run Netplay GCTs on console may brick your Wii. 
#define BUILD_NETPLAY_FILES (false && DOLPHIN_BUILD)

// ASM Output Formatting Settings
#define ALLOW_BLANK_CODE_NAMES_IN_ASM true
extern bool CONFIG_OUTPUT_ASM_INSTRUCTION_DICTIONARY;
extern bool CONFIG_DISABLE_ASM_DISASSEMBLY;
extern bool CONFIG_ENABLE_ASM_HEX_COMMENTS;
extern bool CONFIG_DELETE_ASM_TXT_FILE;
// Allows the builder to implicitly replace MULLIs by powers of 2 with bitshift operations!
extern bool CONFIG_ALLOW_IMPLICIT_OPTIMIZATIONS;
// Enables function calls via BLA! Only valid for builds that have Eon's BLA code installed.
extern bool CONFIG_ALLOW_BLA_FUNCTION_CALLS;
//ROTC floating offsets
#define FS_20_0 -0x7920

//draw buffer offsets
#define DRAW_BUFFER_XPOS_OFFSET 0x2C
#define DRAW_BUFFER_YPOS_OFFSET 0x30

const vector<float> DEFAULT_CAMERA_MATRIX = { 1,0,0,0, 0,1,0,0, 0,0,1,-64 };

extern string MAIN_FOLDER;
bool setMAIN_FOLDER(std::string mainFolderIn);

extern bool CUSTOM_NAME_SUPPLIED;
extern std::string MENU_NAME;

///addresses start

///Function addresses start
#define GET_MEM_ALLOCATOR 0x80024430
#define ALLOC 0x80204e5c
#define MEMMOVE 0x803f602c
#define STRCPY 0x803fa280
#define FA_FOPEN 0x803ebeb8
#define FA_FCLOSE 0x803ebe8c
#define GF_POOL_FREE 0x8002632c
#define GX_SET_CULL_MODE 0x801f136c
#define GX_CLEAR_VTX_DESC 0x801efb10
#define GX_SET_VTX_DESC 0x801ef280
#define GX_SET_VTX_ATTRIBUTE_FORMAT 0x801efb44
#define GET_CAMERA_MTX 0x801a7dbc
#define GX_SET_CURRENT_MTX 0x801f52e4
#define GX_LOAD_POS_MTX_IMM 0x801f51dc
#define GX_SET_Z_MODE 0x801f4774
#define GX_BEGIN 0x801f1088
#define GX_SET_LINE_WIDTH 0x801f12ac
#define GF_DRAW_SETUP_COORD_2D 0x8001abbc
#define GX_DRAW_SET_VTX_COLOR_PRIM_ENVIROMENT 0x8001a5c0
#define GET_FLOAT_WORK_MODULE 0x807acbb4 //r3 = work module ptr, r4 is variable, returns value in f1
#define GF_GET_HEAP 0x800249cc // r3 = Heap ID
#define FT_GET_INPUT 0x8083ae38 // r3 = FighterPtr, RETURNS IN r3 & r4!!
#define FT_MGR_GET_PLAYER_NO 0x80815ad0 // r3 = ftManager pointer, r4 = entryID
#define MU_SET_FRAME_MAT_COL 0x800B7A18
#define SND_PLAY_SE_FIXED_EFFECT 0x80074ECC
#define MU_CHANGE_CLR_ANIM_N_IF 0x800B51F4
///Function addresses end

/// Register Stack Backup Constants
const std::size_t GPRStackBakOffset = 0x8;
const std::size_t GPRStackBakLength = 29 * 0x4;
const std::size_t Reg0CTRStackBakOffset = GPRStackBakOffset + GPRStackBakLength;
const std::size_t Reg0CTRStackBakLength = 0x4 + 0x4;
const std::size_t FPRStackBakOffset = Reg0CTRStackBakOffset + Reg0CTRStackBakLength;
/// Register Stack Backup Constants End


///addresses maintained by Brawl start
#define IS_REPLAY_LOC 0x805BBFC0 //equals 1 if in replay, 2 if in match
#define REPLAY_BUFFER_END_ADDRESS 0x9134CA00 //end of replay buffer
#define BRAWL_REPLAY_PTR_LOC 0x805BBFE8 //address of pointer to where to store input data
#define FRAME_COUNTER_LOC 0x901812A4 //gives the frame count of the match, increments through debug pause
#define PLAY_INPUT_LOC_START 0x805BC068 //the location of P1's inputs.  Add 4 for the next player during playback
#define PLAY_BUTTON_LOC_START 0x805BAD04 //the location of P1's buttons.  Add 0x40 for the next player
#define GCC_CONTROL_STICK_X_START 0x805bad30
#define GCC_CONTROL_STICK_Y_START 0x805bad31
#define WII_BASED_CONTROLLER_START 0x804F7880 //P1 wiimote loc, can't affect inputs from here
#define WII_BASED_CONTROLLER_PORT_OFFSET 0x9A0 //offset between wii controller ports
#define WII_BASED_CONTROLLER_TYPE_OFFSET 0x28 //offset from Wii contoller of byte containing type of controller
#if BUILD_TYPE == PMEX
#define ALT_STAGE_VAL_LOC 0x805858ba //half word that defines what alt stage should be loaded
#else
#define ALT_STAGE_VAL_LOC 0x815e8422 //half word that defines what alt stage should be loaded
#endif
#define REPLAY_BUFFER_BEGIN 0x91301c00 //start of the replay buffer
#define IS_DEBUG_PAUSED 0x805B8A08 //word that equals 1 if game is debug paused, 0x100 if frame advancing
#define IS_AUTO_L_CANCEL 0x9017f36f //byte that is 1 if auto L-cancel is on
#define BUTTON_CONFIG_START 0x805b7480 //start of in game custom control map
#define BASIC_VARIABLE_START_ADDRESS 0x901ae000
#define BASIC_VARIABLE_BLOCK_SIZE 0x870
#define FT_MANAGER_ADDRESS 0x80629a00
///addresses maintained by Brawl end

// Replay Heap Variables
static const int REPLAY_HEAP_VANILLA_ADDRESS = 0x91301B00;
static const int REPLAY_HEAP_REPLAY_BUFFER_BEGIN_OFF = 0x91301c00 - REPLAY_HEAP_VANILLA_ADDRESS;
static const int REPLAY_HEAP_REPLAY_BUFFER_END_OFF = 0x9134CA00 - REPLAY_HEAP_VANILLA_ADDRESS; // Associated accesses not converted yet!
//half word that is used to store which alt stage was loaded
static const int REPLAY_HEAP_ALT_STAGE_STORAGE_OFF = 0x91301f4a - REPLAY_HEAP_VANILLA_ADDRESS;
//half word that stores current and recorded auto L-Cancel settings
static const int REPLAY_HEAP_AUTO_L_CANCEL_SETTING_OFF = 0x91301f4e - REPLAY_HEAP_VANILLA_ADDRESS;
//byte flag == 1 when in stage select menu
static const int IN_STAGE_SELECT_MENU_FLAG = 0x91301f50 - REPLAY_HEAP_VANILLA_ADDRESS;
//word that saves copy of endless rotation queue for replay
static const int REPLAY_HEAP_ENDLESS_ROTATION_QUEUE_OFF = 0x91301f54 - REPLAY_HEAP_VANILLA_ADDRESS;

///reserved memory for storage start
///in replay
///add memory by subtracting the constant above it by the reserved size
#define REGISTER_BUFFER   (REPLAY_BUFFER_END_ADDRESS - 4 * 10) //place where registers are stored
#define CURRENT_FRAME_HEADER_BYTE_LOC   (REGISTER_BUFFER - 4) //stores a pointer to the current head byte
#define INPUT_BUFFER_PTR_LOC   (CURRENT_FRAME_HEADER_BYTE_LOC - 8) //holds current and next ptr inside input buffer
#define CSTICK_ASDI_PTR_LOC   (INPUT_BUFFER_PTR_LOC - 4) //ptr to cstick asdi function input
#define CSTICK_ASDI_COUNT_LOC   (CSTICK_ASDI_PTR_LOC - 4) //how many times cstick asdi was run this frame
#define SYNC_DATA_BUFFER   (CSTICK_ASDI_COUNT_LOC - 4 * 7) //7 is the highest amount of words possible
#define SYNC_DATA_LENGTH   (SYNC_DATA_BUFFER - 4) //how long in bytes the sync data actually is
#define SET_FLOAT_REG_TEMP_MEM  (SYNC_DATA_LENGTH - 8) //used to set floating register and retrieve in value
#define LIGHT_PRESS_TEMP_MEM   (SET_FLOAT_REG_TEMP_MEM - 4) //stores light press during replay
#define CURRENT_FRAME_INPUT_BUFFER   (LIGHT_PRESS_TEMP_MEM - 0x44) //holds inputs that are to be recorded this frame
#define LAST_FRAME_INPUT_BUFFER   (CURRENT_FRAME_INPUT_BUFFER - 0x44) //holds inputs that were recorded or played last frame
#define FRAME_INPUT_BUFFER_OFFSET   (LAST_FRAME_INPUT_BUFFER - 4) //holds current offset of both input buffers
#define SHOULD_STOP_RECORDING   (FRAME_INPUT_BUFFER_OFFSET - 4) //set to 1 if no more memory left for replay
#define B_HELD_FRAME_COUNTER_LOC   (SHOULD_STOP_RECORDING - 4) //counts how many frames z was held consecutively and records state of debug pause from before slo-mo
#define CURRENT_ALT_STAGE_INFO_LOC   (B_HELD_FRAME_COUNTER_LOC - 4) //contains alt stage, used to fix salty runback
#define IS_VERSUS_LOC   (CURRENT_ALT_STAGE_INFO_LOC - 4) //is 1 if in versus, else 0
#define RANDOM_1_TO_1_CPP_FLAG_LOC	(IS_VERSUS_LOC - 4) //flag to communicate with c++ code
#define END_OF_REPLAY_BUFFER   (RANDOM_1_TO_1_CPP_FLAG_LOC - 0x100) //tells when to stop recording inputs
///set END_OF_REPLAY_BUFFER to the last constant - 0x80 to ensure no memory leaks

///reserved memory for storage end

///Control code constants start
#define BUTTON_MENU_SIZE 11
//#define CONTROL_MENU_BASE_SIZE 7
#define CONTROL_MENU_BASE_SIZE 8
#define MENU_WRITE_LOC 0x805b4c00
#define TAG_LIST_START_LOC 0x90172e20
#define TAG_LIST_SIZE 0x124
#define GCC_SETTINGS_TAG_OFFSET 0x14
#define TAG_TIME_OFFSET 0x10
#define MENU_FIRST_CREATION_TIME_LOC 0x90172e30
//state=0, pos=1, size=2, buttonPos=3, buttonCancel=4-5, newSize=6, newPos=7, reopenFlag=8, replaceTimeFlag=9, openFlag=10
const int MENU_STATE_INFO_OFFSET = 0x60;
const int MENU_SIZE_OFFSET = 0x6C;
const int MENU_INDEX_OFFSET = 0x70;
const int MENU_POS_OFFSET = 0x44;
//const int MENU_PORT_OFFSET = 0x47F80;
//const int MENU_PORT1_LOC = 0x81578BDC;
const int MENU_PORT_NUM_OFFSET = 0x57;
const int MENU_SELECTED_TAG_OFFSET = 0x164;
///Control code constants end



///addresses end

///constants start
///primitive types
#define PRIMITIVE_LINE 0xB0
#define PRIMITIVE_QUAD 0x80
///button values
#define BUTTON_DL 0x1
#define BUTTON_DR 0x2
#define BUTTON_DD 0x4
#define BUTTON_DU 0x8
#define BUTTON_Z 0x10
#define BUTTON_R 0x20
#define BUTTON_L 0x40
#define BUTTON_A 0x100
#define BUTTON_B 0x200
#define BUTTON_X 0x400
#define BUTTON_Y 0x800
#define BUTTON_START 0x1000
#define BUTTON_DPAD 0xF
constexpr bool isPowerOf2(unsigned long numberIn)
{
	return (numberIn & (numberIn - 1)) == 0;
}
constexpr unsigned long bitIndexFromButtonHex(unsigned long buttonHex, bool doIndexFromRight = 0)
{
	// If what was passed in was a proper button hex value (power of 2)
	if (isPowerOf2(buttonHex))
	{
		if (doIndexFromRight)
		{
			return int(log2(buttonHex));
		}
		else
		{
			return 31 - (int(log2(buttonHex)));
		}
	}
	return ULONG_MAX;
}
///button values end
#define BUTTON_PORT_OFFSET 0x40
#define WIIMOTE 0
#define WIICHUCK 1
#define CLASSIC 2
#define SP 1 //stack ptr reg
#define WORD_SIZE 32
#define BRANCH_IF_TRUE 0b01100
#define BRANCH_IF_FALSE 0b00100
#define BRANCH_ALWAYS 0b10100
#define BRANCH_IF_DZ 0b10010
#define BRANCH_IF_DNZ 0b10000
#define MAX_IFS 15
#define MAX_LABELS 50
#define MAX_JUMPS 50
#define LESS 0
#define GREATER 1
#define EQUAL 2
#define LESS_OR_EQUAL 4
#define GREATER_OR_EQUAL 3
#define NOT_EQUAL 5
#define LESS_I 10
#define GREATER_I 11
#define EQUAL_I 12
#define LESS_OR_EQUAL_I 14
#define GREATER_OR_EQUAL_I 13
#define NOT_EQUAL_I 15
#define LESS_L 30
#define GREATER_L 31
#define EQUAL_L 32
#define LESS_OR_EQUAL_L 34
#define GREATER_OR_EQUAL_L 33
#define NOT_EQUAL_L 35
#define LESS_I_L 40
#define GREATER_I_L 41
#define EQUAL_I_L 42
#define LESS_OR_EQUAL_I_L 44
#define GREATER_OR_EQUAL_I_L 43
#define NOT_EQUAL_I_L 45
#define IS_ELSE 20
#define LT 0
#define GT 1
#define EQ 2
#define SO 3
constexpr unsigned long crBitInCRF(unsigned long CondRegBit, unsigned long CondRegField)
{
	return CondRegBit + (4 * CondRegField);
}

#define MAX_CSTICK_VALUE 0x55
#define CSTICK_COEFFICIENT 0.011775
#define TERMINATE_REPLAY_VALUE 0x06000000
///constants end

void writeBorderedStringToStream(std::ostream& output, std::string inputStr, std::size_t minBorderLength, char borderChar = '#');

namespace ledger
{
	struct codeLedgerEntry
	{
		std::string codeName = "";
		std::streampos codeStartPos = SIZE_MAX;
		std::streampos codeEndPos = SIZE_MAX;
		std::string codeBlurb = "";

		codeLedgerEntry(std::string codeNameIn, std::streampos codeStartPosIn, std::string codeBlurbIn = "") :
			codeName(codeNameIn), codeStartPos(codeStartPosIn), codeBlurb(codeBlurbIn) {};
		std::size_t length();
	};

	bool openLedgerEntry(std::string codeName, std::string codeBlurb = "");
	bool closeLedgerEntry();

	bool writeCodeToASMStream(std::ostream& output, std::istream& codeStreamIn, std::size_t expectedLength, const std::string codeNameIn = "", const std::string codeBlurbIn = "", bool codeUnattested = 0, bool disableDisassembly = 0);
}

// Branch Conditions, Used for JumpToLabel and BC Operations
struct branchConditionAndConditionBit
{
	int BranchCondition = INT_MAX;
	int ConditionBit = INT_MAX;

	branchConditionAndConditionBit(int BranchConditionIn = INT_MAX, int ConditionBitIn = INT_MAX, unsigned char ConditionRegFieldIn = UCHAR_MAX);

	// Returns a copy of this bCACB, with the ConditionRegField set to the specified value!
	branchConditionAndConditionBit inConditionRegField(unsigned char ConditionRegFieldIn) const;
	branchConditionAndConditionBit andDecrementCTR(bool branchIfCTRIsZero) const;
};
const static branchConditionAndConditionBit bCACB_EQUAL				=		{ BRANCH_IF_TRUE, EQ, 0 };
const static branchConditionAndConditionBit bCACB_NOT_EQUAL			=		{ BRANCH_IF_FALSE, EQ, 0 };
const static branchConditionAndConditionBit bCACB_GREATER			=		{ BRANCH_IF_TRUE, GT, 0};
const static branchConditionAndConditionBit bCACB_GREATER_OR_EQ		=		{ BRANCH_IF_FALSE, LT, 0};
const static branchConditionAndConditionBit bCACB_LESSER			=		{ BRANCH_IF_TRUE, LT, 0 };
const static branchConditionAndConditionBit bCACB_LESSER_OR_EQ		=		{ BRANCH_IF_FALSE, GT, 0 };
const static branchConditionAndConditionBit bCACB_OVERFLOW			=		{ BRANCH_IF_TRUE, SO, 0 };
const static branchConditionAndConditionBit bCACB_NO_OVERFLOW		=		{ BRANCH_IF_FALSE, SO, 0 };
const static branchConditionAndConditionBit bCACB_DZ				=		{ BRANCH_IF_DZ, 0, 0 };
const static branchConditionAndConditionBit bCACB_DNZ				=		{ BRANCH_IF_DNZ, 0, 0 };
const static branchConditionAndConditionBit bCACB_UNSPECIFIED		=		{ INT_MAX, INT_MAX, UCHAR_MAX };

namespace labels
{
	struct labelJump
	{
		int labelNum = INT_MAX;
		std::streampos jumpSourcePos = SIZE_MAX;
		branchConditionAndConditionBit jumpCondition = bCACB_UNSPECIFIED;
		bool setLR = 0;

		labelJump(int labelNumIn = INT_MAX, std::streampos jumpSourcePosIn = SIZE_MAX, branchConditionAndConditionBit jumpConditionIn = bCACB_UNSPECIFIED, bool setLRIn = 0) :
			labelNum(labelNumIn), jumpSourcePos(jumpSourcePosIn), jumpCondition(jumpConditionIn), setLR(setLRIn) {};
	};
}

template <std::size_t specificCaseCount>
class switchTable
{
	int tableStartLabel = INT_MAX;
	int codeStartLabel = INT_MAX;
	int defaultCaseStartLabel = INT_MAX;
	int defaultCaseEndLabel = INT_MAX;

	struct switchCase
	{
		int startLabel = INT_MAX;
		int endLabel = INT_MAX;

		std::size_t getLengthInBytes()
		{
			std::size_t result = SIZE_MAX;

			if (startLabel != INT_MAX && endLabel != INT_MAX)
			{
				result = LabelPosVec[endLabel] - LabelPosVec[startLabel];
			}

			return result;
		}
		std::size_t getLengthInInstructions()
		{
			std::size_t result = getLengthInBytes();

			if (result != SIZE_MAX)
			{
				result /= 0x4;
			}

			return result;
		}
	};
	unsigned short openCaseID = USHRT_MAX;
	std::map<unsigned short, switchCase> cases{};
	switchCase* getCasePtr(unsigned short caseID)
	{
		switchCase* result = nullptr;

		auto findRes = cases.find(caseID);
		if (findRes != cases.end())
		{
			result = &findRes->second;
		}

		return result;
	}
	std::size_t getCaseStartOffsetInBytes(unsigned short caseID)
	{
		std::size_t result = SIZE_MAX;

		switchCase* targetCase = getCasePtr(caseID);
		if (targetCase != nullptr && targetCase->startLabel != INT_MAX && codeStartLabel != INT_MAX)
		{
			result = (LabelPosVec[targetCase->startLabel] - LabelPosVec[codeStartLabel]) / 2;
		}

		return result;
	}
	std::size_t getCaseStartOffsetInInstructions(unsigned short caseID)
	{
		std::size_t result = getCaseStartOffsetInBytes(caseID);

		if (result != SIZE_MAX)
		{
			result /= 0x4;
		}

		return result;
	}
	std::size_t getDefaultCaseOffsetInBytes()
	{
		std::size_t result = SIZE_MAX;

		std::streampos codeStartPos = LabelPosVec[codeStartLabel];
		std::streampos defaultCasePos = LabelPosVec[defaultCaseStartLabel];

		if (codeStartPos != SIZE_MAX && defaultCasePos != SIZE_MAX)
		{
			result = (defaultCasePos - codeStartPos) / 2;
		}

		return result;
	}
	std::size_t getDefaultCaseOffsetInInstructions()
	{
		std::size_t result = getDefaultCaseOffsetInBytes();

		if (result != SIZE_MAX)
		{
			result /= 0x4;
		}

		return result;
	}
public:
	const static bool paddingWordNeeded = (specificCaseCount % 2);
	// First Entry is Case Count + Default Case, Following are CaseWords, Last is Potential Padding
	const static std::size_t sizeInBytes = 0x4 + (specificCaseCount * 0x4) + (paddingWordNeeded ? 0x4 : 0x0);

	switchTable()
	{
		tableStartLabel = GetNextLabel();
		codeStartLabel = GetNextLabel();
		defaultCaseStartLabel = GetNextLabel();
		defaultCaseEndLabel = GetNextLabel();
	}

	void init(unsigned char caseReg, unsigned char workReg1, unsigned char workReg2, unsigned char workReg3)
	{
		// BL past the table!
		JumpToLabel(codeStartLabel, bCACB_UNSPECIFIED, 1);
		// Register Start of Table!
		Label(tableStartLabel);
		WPtr.write(std::array<char, sizeInBytes>().data(), sizeInBytes * 2);
		Label(codeStartLabel);
		// Get Table Address in reg1
		MFLR(workReg1);
		// Add Table Length to Table Addr to get addr of following code.
		ADDI(workReg2, workReg1, sizeInBytes);
		// Set up CTR with the number of specific cases in preparation for our loop.
		LHZ(workReg3, workReg1, 0x00);
		MTCTR(workReg3);
		// Set up LR with default case instruction offset.
		// Load Default offset in bytes.
		LHZ(workReg3, workReg1, 0x02);
		// Add the offset to the code block address...
		ADD(workReg3, workReg2, workReg3);
		// ... and write that to LR.
		MTLR(workReg3);

		int dispatchLoopHead = GetNextLabel();
		Label(dispatchLoopHead);
		// Load the next case's ID...
		LHZU(workReg3, workReg1, 0x04);
		// ... and compare against it!
		CMPL(caseReg, workReg3, 0);
		// If our value is greater than the current case, and we have cases left to check, then restart the loop to try the next case.
		JumpToLabel(dispatchLoopHead, bCACB_GREATER.andDecrementCTR(0));
		// If our value != the current case (ie. is greater than, or we're out of cases), then no case exists for our value, jump to default.
		BCLR(bCACB_NOT_EQUAL);
		// Otherwise, we're at the specific case for this number!
		// Grab the case's offset in bytes.
		LHZ(workReg1, workReg1, 0x02);
		// Add the offset to the code block address...
		ADD(workReg2, workReg2, workReg1);
		// ... write that to LR...
		MTLR(workReg2);
		// ... and branch to it!
		BLR();
	}
	bool finalize()
	{
		bool result = 0;

		std::streampos tableStartPos = LabelPosVec[tableStartLabel];
		std::streampos codeStartPos = LabelPosVec[codeStartLabel];

		// If the default case hasn't been opened yet, just establish it at the bottom of the code block.
		if (LabelPosVec[defaultCaseStartLabel] == SIZE_MAX)
		{
			defaultStart();
			defaultEnd();
		}
		
		// Also mark the end of the default case.
		std::streampos defaultCasePos = LabelPosVec[defaultCaseStartLabel];

		if (tableStartPos != SIZE_MAX && codeStartPos != SIZE_MAX && defaultCasePos != SIZE_MAX)
		{
			std::streampos currStrmLocation = WPtr.tellp();

			WPtr.seekp(tableStartPos);
			WPtr << lava::numToHexStringWithPadding<unsigned short>(specificCaseCount, 0x4);
			WPtr << lava::numToHexStringWithPadding<unsigned short>(getDefaultCaseOffsetInInstructions(), 0x4);
			for (auto currCase : cases)
			{
				WPtr << lava::numToHexStringWithPadding<unsigned short>(currCase.first, 0x04);
				WPtr << lava::numToHexStringWithPadding<unsigned short>(getCaseStartOffsetInInstructions(currCase.first), 0x04);
			}
			if (paddingWordNeeded)
			{
				WPtr << lava::numToHexStringWithPadding<unsigned long>(0xFFFFFFFF, 0x8);
			}

			WPtr.seekp(currStrmLocation);
			result = 1;
		}

		return result;
	}

	bool caseStart(unsigned short caseID)
	{
		bool result = cases.size() < specificCaseCount;

		result &= (getCasePtr(caseID) == nullptr);
		if (result)
		{
			switchCase* newCase = &cases.insert({ caseID, switchCase() }).first->second;
			newCase->startLabel = GetNextLabel();
			Label(newCase->startLabel);
			openCaseID = caseID;
		}

		return result;
	}
	bool caseEnd()
	{
		bool result = openCaseID != USHRT_MAX;

		if (result)
		{
			switchCase* currCase = &cases[openCaseID];
			currCase->endLabel = GetNextLabel();
			Label(currCase->endLabel);
			openCaseID = USHRT_MAX;
		}

		return result;
	}
	void caseBreak()
	{
		JumpToLabel(defaultCaseEndLabel);
		caseEnd();
	}

	void defaultStart()
	{
		Label(defaultCaseStartLabel);
	}
	void defaultEnd()
	{
		Label(defaultCaseEndLabel);
	}

	int getCaseLabel(unsigned short caseID)
	{
		int result = INT_MAX;

		switchCase* targetCase = getCasePtr(caseID);
		if (targetCase != nullptr)
		{
			result = targetCase->startLabel;
		}

		return result;
	}
	int getCaseDefaultLabel()
	{
		return defaultCaseStartLabel;
	}
};

///variables start
extern fstream WPtr;
extern std::vector<ledger::codeLedgerEntry> codeLedger;
static char OpHexBuffer[10] = {};//used for writing 8 char assembly hex to file
static u32 OpHex = 0;//for writing ops to file
static int IfStartPos[MAX_IFS] = {};
static int IfConditionArray[MAX_IFS] = {};
static int IfIndex = 0;
static int WhileConditionArray[MAX_IFS] = {};
static int WhileCompareArray[MAX_IFS] = {};
static int WhileIndex = 0;
static int ASMStartAddress = 0;
extern std::vector<std::streampos> LabelPosVec;
extern std::vector<labels::labelJump> LabelJumpVec;
extern std::streampos currentGeckoEmbedStartPos;  // Used for opening and closing Gecko Embeds!
static vector<int> FPPushRecords;
static vector<int> CounterLoppRecords;
static vector<int> StackIteratorRecords;
///variables end
int HexToDec(char x);

void CodeStart(string FilePath);
void CodeEnd();

void MakeGCT(string TextFilePath, string OldGCTFilePath, string NewGCTFilePath);

// Credit to Kapedani for c++ implementation
// Also credit to Fracture for the original ASMConvert script
bool MakeASM(string TextFilePath, string OutputAsmPath, bool disableDisassembly = CONFIG_DISABLE_ASM_DISASSEMBLY);

int GetHexFromFloat(float Value);
float GetFloatFromHex(int Value);
int GetShiftNum(int endPos);
int GetOpSegment(int val, int size, int pos);
void WriteMenuTextToFile(string Text);
void WriteTextToFile(string Text);
void WriteIntToFile(int val);
void If(int Val1, int Comparision, int Val2);
void EndIf();
void Else();
void While(int Val1, int Comparision, int Val2);
void EndWhile();
void SetRegister(int Register, int value);
void SetRegister(int Register, string value);
void SetFloatingRegister(int FPReg, int TempReg1, int TempReg2, float Value);
void SetFloatingRegister(int FPReg, int TempReg, float Value);
void LoadWordToReg(int Register, int Address);
void LoadHalfToReg(int Register, int Address);
void LoadByteToReg(int Register, int Address);
void LoadWordToReg(int DestReg, int Reg, int Address);
void LoadHalfToReg(int DestReg, int Reg, int Address);
void LoadByteToReg(int DestReg, int Reg, int Address);
void StoreWordAtAddr(int SourceReg, int AddrReg, int Address);
void StoreHalfAtAddr(int SourceReg, int AddrReg, int Address);
void StoreByteAtAddr(int SourceReg, int AddrReg, int Address);
void ConvertIntToFloat(int SourceReg, int TempReg, int ResultReg);
void ASMStart(int BranchAddress, std::string name = "", std::string blurb = "");
void ASMEnd(int Replacement);
void ASMEnd();
void ASMPulseStart(std::string name = "", std::string blurb = "");
void ASMPulseEnd();
void CodeRaw(std::string name, std::string blurb, const std::vector<unsigned long>& rawHexIn);
void CodeRawStart(std::string name, std::string blurb);
void CodeRawEnd();
void Label(int LabelNum);
int GetNextLabel();
void JumpToLabel(int LabelNum, branchConditionAndConditionBit conditionIn = bCACB_UNSPECIFIED, bool setLinkRegister = 0);
void JumpToLabel(int LabelNum, int BranchCondition, int ConditionBit, bool setLinkRegister = 0);
void CompleteJumps();
int CalcBranchOffset(int Location, int Target);
void StrCpy(int Destination, int Source, int Temp);
void GeckoStringWrite(string String, u32 Address);
void Gecko32BitWrite(int Address, int Value);
void Gecko8BitWrite(int Address, int Value, int NumTimes = 1);
void SetGeckoBaseAddress(int Address);
void SetGeckoPointerAddress(int Address);
void LoadIntoGeckoBaseAddress(int Address);
// Set BAPO to 0 to store relative to BA, or to 1 to store relative to PO!
void LoadIntoGeckoBaseAddressRelativeTo(int Offset, bool BAPO);
void LoadIntoGeckoPointer(int Address);
// Set BAPO to 0 to store relative to BA, or to 1 to store relative to PO!
void LoadIntoGeckoPointerRelativeTo(int Offset, bool BAPO);
void LoadIntoGeckoRegister(int Address, int Reg, int size);
void StoreGeckoBaseAddress(int Address);
// Set BAPO to 0 to store relative to BA, or to 1 to store relative to PO!
void StoreGeckoBaseAddressRelativeTo(int Offset, bool BAPO);
void StoreGeckoPointer(int Address);
// Set BAPO to 0 to store relative to BA, or to 1 to store relative to PO!
void StoreGeckoPointerRelativeTo(int Offset, bool BAPO);
void StoreGeckoRegisterAt(int Address, int Reg, int size, int repeats = 0);
void GeckoIf(u32 Address, int Comparison, int Value);
void GeckoEndIf();
void GeckoReset();
// Opens a Gecko Embed. Note: Writes Embed address into BA!
bool GeckoDataEmbedStart();
// Closes the active Gecko Embed, padding for alingment to 0x8 bytes as necessary.
// If AddressStoreLocation is provided, will additionally write Embed Address to that location.
// Also does a BAPO reset by default, which can be skipped using the provided argument.
bool GeckoDataEmbedEnd(u32 AddressStoreLocation = ULONG_MAX, bool skipBAPOReset = 0);
//searches for byte, elementOffset is distance between elements, ResultReg returns index if found, else -1
//StartAddressReg ends with the address of the found element, or an address after the array
void FindInArray(int ValueReg, int StartAddressReg, int numberOfElements, int elementOffset, int ResultReg, int TempReg);
//searches for target, elementOffset is distance between elements, ResultReg returns index if found, else -1
//StartAddressReg ends with the address of the found element, or an address after the array
//ends when end marker is encountered
void FindInTerminatedArray(int ValueReg, int StartAddressReg, int endMarker, int elementOffset, int ResultReg, int TempReg, int searchSize);
void CallBrawlFunc(int Address, int addressReg = 0, bool setLR = 1);
//r3 returns ptr
void Allocate(int SizeReg, int Heap = HeapType::MenuInstance);
void AllocateIfNotExist(int SizeReg, int AddressReg, int EmptyVal);
void Memmove(int DestReg, int SourceReg, int SizeReg);
void SetRegs(int StartReg, vector<int> values);
void SetArgumentsFromRegs(int StartReg, vector<int> ValueRegs);
void SetFloatingArgumentsFromRegs(int FPStartReg, vector<int> FPValueRegs);
void GXSetCullMode(int CullModeReg);
void GXClearVtxDesc();
void GXSetVtxDesc(int AttributeReg, int TypeReg);
void GXSetVtxAttrFmt(int vtxfmtReg, int attrReg, int countReg, int typeReg, int fracReg);
void GetCameraMtx(int StorageLocReg);
void GXSetCurrentMtx(int IDReg);
void GXLoadPosMtxImm(int MtxPtrReg, int IDReg);
void GXSetZMode(int CompareEnabledReg, int FuncTypeReg, int UpdateEnabledReg);
void GXSetLineWidth(int WidthReg, int TexOffsetReg);
void GXBegin(int TypeReg, int VtxAttrFmtReg, int NumVertsReg);
void GFDrawSetupCoord2D();
void GXDrawSetVtxColorPrimEnviroment();
void FreeMem(int AddressReg);
void FreeMemFromFighter(int AddressReg);
void FreeMemIfAllocd(int AddressReg, int EmptyVal);
void FreeAllocdArray(int AllocAddressReg);
void SaveMem(int LocationReg, int SizeReg, int SaveToReg, int Heap = 6);
void SaveAllocedMem(int AddressReg, int SaveToReg, int reg1, int reg2, bool SaveHeader = false, int Heap = 6);
void SaveRegisters();
void SaveRegisters(vector<int> FPRegs);
void SaveRegisters(int NumFPRegs);
void RestoreRegisters();
void Increment(int Reg);
void Decrement(int Reg);
void WriteStringToMem(string Text, int AddressReg);
void WriteVectorToMem(vector<int> Values, int AddressReg);
void WriteVectorToMem(vector<float> Values, int AddressReg);
void CounterLoop(int CounterReg, int startVal, int endVal, int stepVal);
void CounterLoopEnd();
void SprintF(int StrReg, vector<int> ValueRegs, int DestPtrReg = -1);
//can't have default, because overload ambiguity
void SprintF(int StrReg, vector<int> ValueRegs, vector<int> FPValueRegs, int DestPtrReg);
void ClampStick(int FPXValReg, int FPYValReg);
void ConvertIntStickValsToFloating(int StickXReg, int StickYReg, int FPXResultReg, int FPYResultReg, int FPTempReg);
void ConvertFloatingRegToInt(int FPReg, int ResultReg);
void ConvertFloatingRegToInt(int FPReg, int ResultReg, int TempFPReg);
void AddValueToByteArray(u32 value, vector<u8> &Array);
void AddValueToByteArray(u16 value, vector<u8> &Array);
void AddValueToByteArray(u8 value, vector<u8> &Array);
void AddValueToByteArray(int value, vector<u8> &Array);
void AddValueToByteArray(short value, vector<u8> &Array);
void AddValueToByteArray(char value, vector<u8> &Array);
void DrawPrimitive(int type, vector<float> Positions, vector<int> Colors, int VTXAttrFrmt);
void DrawPrimitive(int type, vector<float> Positions, int Color, int VTXAttrFrmt);
void LoadVal(int AddressReg, int size, int offset = 0, int ResultReg = 3);
void GetValueFromPtrPath(vector<int> Path, int StartingReg, int ResultReg = 3);
void GetValueFromPtrPath(int StartingAddress, vector<int> Path, int ResultReg = 3);
void AllocateStack(int size, int Address, int TempReg = 3);
void PushOnStack(int ValueReg, int StackReg, int TempReg = 3);
void PopOffStack(int ResultReg, int StatckReg, int TempReg = 3);
void IterateStack(int ResultReg, int StackReg, int TempReg);
void IterateStackEnd();
void AllocateVector(int size, int Address, int reg);
void ClearVector(int VectorReg);
void CopyVector(int SourceVector, int DestVector);
void IterateVector(int VectorReg, int IteratorReg, int TempReg1, int TempReg2, int StartReg = -1);
void ReverseIterateVector(int VectorReg, int IteratorReg, int TempReg1, int TempReg2, int StartReg = -1);
void RemoveFromVector(int VectorReg, int ValueReg);
void FindInVector(int VectorReg, int ValueReg, int ResultReg);
void ShiftVectorDown(int VectorReg, int StartReg);
void Randi(int ResultReg, int MaxReg = 3, int TempReg = 4);
//void RandomCapped(int HighReg, int reg1, int ResultReg = 3);
void WriteFileToSD(int PathReg, int SizeReg, int DataPtrReg);
void WriteFileToVF(int PathReg, int SizeReg, int DataPtrReg);
void IfInGame(int reg = 3, bool condition = true);
void ClearBitsFromMemory(short BitsToClear, int Address);
void ClearBitsFromMemory(short BitsToClear, int AddressReg, int Offset = 0);
void GetSceneNum(int ResultReg);
void IfInVersus(int reg);
void LoadFile(string filePath, int destination, int reg1, int reg2, bool loadFromSD = true);
void constrainFloat(int floatReg, int tempFReg, int tempReg, float min, float max);
void constrainFloatDynamic(int floatReg, int minFReg, int maxFReg);
void modifyInstruction(int instructionReg, int addressReg);
void IfInSSE(int reg1, int reg2);
void IfNotInSSE(int reg1, int reg2);
void GetHeapAddress(_heapCacheTable::CachedHeaps heapIndex, int destinationReg);
void LoadWordFromHeapAddress(_heapCacheTable::CachedHeaps heapIndex, int loadDestinationReg, int addressDestinationReg, int offset);
void StoreWordToHeapAddress(_heapCacheTable::CachedHeaps heapIndex, int sourceReg, int addressDestinationReg, int offset);
void LoadHalfFromHeapAddress(_heapCacheTable::CachedHeaps heapIndex, int loadDestinationReg, int addressDestinationReg, int offset);
void StoreHalfToHeapAddress(_heapCacheTable::CachedHeaps heapIndex, int sourceReg, int addressDestinationReg, int offset);
void LoadByteFromHeapAddress(_heapCacheTable::CachedHeaps heapIndex, int loadDestinationReg, int addressDestinationReg, int offset);
void StoreByteToHeapAddress(_heapCacheTable::CachedHeaps heapIndex, int sourceReg, int addressDestinationReg, int offset);

void ABS(int DestReg, int SourceReg, int tempReg);
void ADD(int DestReg, int SourceReg1, int SourceReg2, bool SetConditionReg = 0);
void ADDI(int DestReg, int SourceReg, int Immediate);
void ADDIC(int DestReg, int SourceReg, int Immediate, bool SetConditionReg = 0);
void ADDIS(int DestReg, int SourceReg, int Immediate);
void ADDME(int DestReg, int SourceReg, bool SetConditionReg = 0);
void AND(int DestReg, int SourceReg1, int SourceReg2, bool SetConditionReg = 0);
void ANDC(int DestReg, int SourceReg1, int SourceReg2, bool SetConditionReg = 0);
void ANDI(int DestReg, int SourceReg, int Immediate);
void ANDIS(int DestReg, int SourceReg, int Immediate);
void B(int JumpDist);
void BA(int Address);
void BC(int JumpDist, branchConditionAndConditionBit conditionIn, bool setLinkRegister = 0);
void BC(int JumpDist, int BranchCondition, int ConditionBit, bool setLinkRegister = 0);
void BCLR(branchConditionAndConditionBit conditionIn, bool setLinkRegister = 0);
void BCLR(int BranchCondition, int ConditionBit, bool setLinkRegister = 0);
void BCTR();
void BCTRL();
void BL(int JumpDist);
void BLA(int Address);
void BLR();
void CMP(int Reg1, int Reg2, int CondField);
void CMPI(int Reg, int Immediate, int CondField);
void CMPL(int Reg1, int Reg2, int CondField);
void CMPLI(int Reg, int Immediate, int CondField);
void CNTLZW(int DestReg, int SourceReg, bool SetConditionReg = 0);
void CRAND(int DestBit, int SourceBit1, int SourceBit2);
void CRANDC(int DestBit, int SourceBit1, int SourceBit2);
void CREQV(int DestBit, int SourceBit1, int SourceBit2);
void CRNAND(int DestBit, int SourceBit1, int SourceBit2);
void CRNOR(int DestBit, int SourceBit1, int SourceBit2);
void CROR(int DestBit, int SourceBit1, int SourceBit2);
void CRORC(int DestBit, int SourceBit1, int SourceBit2);
void CRXOR(int DestBit, int SourceBit1, int SourceBit2);
//if sourceReg1 == r0, not used
void DCBF(int SourceReg1, int SourceReg2);
void DCBST(int SourceReg1, int SourceReg2);
void DIVW(int DestReg, int DividendReg, int DivisorReg, bool SetConditionReg = 0);
void DIVWU(int DestReg, int DividendReg, int DivisorReg, bool SetConditionReg = 0);
void EQV(int DestReg, int SourceReg1, int SourceReg2, bool SetConditionReg = 0);
void EXTSB(int DestReg, int SourceReg, bool SetConditionReg = 0);
void FABS(int DestReg, int SourceReg, bool SetConditionReg = 0);
void FADD(int DestReg, int SourceReg1, int SourceReg2, bool SetConditionReg = 0);
void FADDS(int DestReg, int SourceReg1, int SourceReg2, bool SetConditionReg = 0);
void FCMPU(int FPReg1, int FPReg2, int CondField);
void FCTIW(int DestReg, int SourceReg, bool SetConditionReg = 0);
void FCTIWZ(int DestReg, int SourceReg, bool SetConditionReg = 0);
void FDIV(int FPDestReg, int FPSourceReg1, int FPSourceReg2, bool SetConditionReg = 0);
void FDIVS(int FPDestReg, int FPSourceReg1, int FPSourceReg2, bool SetConditionReg = 0);
void FMADD(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void FMADDS(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void FMR(int DestReg, int SourceReg, bool SetConditionReg = 0);
void FMSUB(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void FMSUBS(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void FMUL(int DestReg, int SourceReg1, int SourceReg2, bool SetConditionReg = 0);
void FMULS(int DestReg, int SourceReg1, int SourceReg2, bool SetConditionReg = 0);
void FNEG(int DestReg, int SourceReg, bool SetConditionReg = 0);
void FNMADD(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void FNMADDS(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void FNMSUB(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void FNMSUBS(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void FRES(int DestReg, int SourceReg, bool SetConditionReg = 0);
void FRSP(int DestReg, int SourceReg, bool SetConditionReg = 0);
void FRSQRTE(int DestReg, int SourceReg, bool SetConditionReg = 0);
void FSEL(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void FSQRT(int FPDestReg, int FPSourceReg, bool SetConditionReg = 0);
void FSUB(int FPDestReg, int FPSourceReg1, int FPSourceReg2, bool SetConditionReg = 0);
void FSUBS(int FPDestReg, int FPSourceReg1, int FPSourceReg2, bool SetConditionReg = 0);
//if SOurceReg1 == r0, it is not used
void ICBI(int SourceReg1, int SourceReg2);
void ISYNC();
void LBA(int DestReg, int AddressReg, int Immediate);
void LBAU(int DestReg, int AddressReg, int Immediate);
void LBAUX(int DestReg, int AddressReg1, int AddressReg2);
void LBAX(int DestReg, int AddressReg1, int AddressReg2);
void LBZ(int DestReg, int AddressReg, int Immediate);
void LBZU(int DestReg, int AddressReg, int Immediate);
void LBZUX(int DestReg, int AddressReg1, int AddressReg2);
void LBZX(int DestReg, int AddressReg1, int AddressReg2);
void LFD(int DestReg, int AddressReg, int Immediate);
void LFDU(int DestReg, int AddressReg, int Immediate);
void LFDUX(int DestReg, int AddressReg1, int AddressReg2);
void LFDX(int DestReg, int AddressReg1, int AddressReg2);
void LFS(int DestReg, int AddressReg, int Immediate);
void LFSU(int DestReg, int AddressReg, int Immediate);
void LFSUX(int DestReg, int AddressReg, int AddressReg2);
void LFSX(int DestReg, int AddressReg, int AddressReg2);
void LHA(int DestReg, int AddressReg, int Immediate);
void LHAU(int DestReg, int AddressReg, int Immediate);
void LHAUX(int DestReg, int AddressReg1, int AddressReg2);
void LHAX(int DestReg, int AddressReg1, int AddressReg2);
void LHZ(int DestReg, int AddressReg, int Immediate);
void LHZU(int DestReg, int AddressReg, int Immediate);
void LHZUX(int DestReg, int AddressReg1, int AddressReg2);
void LHZX(int DestReg, int AddressReg1, int AddressReg2);
void LWZ(int DestReg, int AddressReg, int Immediate);
void LWZU(int DestReg, int AddressReg, int Immediate);
void LWZUX(int DestReg, int AddressReg1, int AddressReg2);
void LWZX(int DestReg, int AddressReg1, int AddressReg2);
void LMW(int StartReg, int AddressReg, int Immediate);
void LSWI(int StartReg, int AddressReg, int numBytes);
// Note: Must MTXER the Num of Bytes to Load before using this Overload!
void LSWX(int StartReg, int AddressReg1, int AddressReg2);
void LSWX(int StartReg, int AddressReg1, int AddressReg2, int NumArgsReg);
// Note: Function automatically handles swapping top and bottom halves of the SpReg ID!
void MFSPR(int TargetReg, int SpecialRegID);
void MFCTR(int TargetReg);
void MFLR(int TargetReg);
void MFXER(int TargetReg);
void MFCR(int TargetReg);
void MOD(int DestReg, int SourceReg1, int SourceReg2);
void MR(int DestReg, int SourceReg);
// Note: Function automatically handles swapping top and bottom halves of the SpReg ID!
void MTSPR(int SourceReg, int SpecialRegID);
void MTCTR(int TargetReg);
void MTLR(int TargetReg);
void MTXER(int TargetReg);
void MTCRF(int MaskBitfield, int MaskReg);
void MULLI(int DestReg, int SourceReg, int Immediate);
void MULLW(int DestReg, int SourceReg1, int SourceReg2, bool SetConditionReg = 0);
void NEG(int DestReg, int SourceReg, bool SetConditionReg = 0);
void NOP();
void NOR(int DestReg, int SourceReg1, int SourceReg2, bool SetConditionReg = 0);
void OR(int DestReg, int SourceReg1, int SourceReg2, bool SetConditionReg = 0);
void ORC(int DestReg, int SourceReg1, int SourceReg2, bool SetConditionReg = 0);
void ORI(int DestReg, int SourceReg, int Immediate);
void ORIS(int DestReg, int SourceReg, int Immediate);
void PSQ_L(int FPDestReg, int AddressReg, int Immediate, int W, int I);
void PSQ_LU(int FPDestReg, int AddressReg, int Immediate, int W, int I);
void PSQ_LX(int FPDestReg, int AddressReg1, int AddressReg2, int W, int I);
void PSQ_LUX(int FPDestReg, int AddressReg1, int AddressReg2, int W, int I);
void PSQ_ST(int FPSourceReg, int AddressReg, int Immediate, int W, int I);
void PSQ_STU(int FPSourceReg, int AddressReg, int Immediate, int W, int I);
void PSQ_STX(int FPSourceReg, int AddressReg1, int AddressReg2, int W, int I);
void PSQ_STUX(int FPSourceReg, int AddressReg1, int AddressReg2, int W, int I);
void PS_ABS(int FPDestReg, int FPSourceReg, bool SetConditionReg = 0);
void PS_ADD(int FPDestReg, int FPSourceReg1, int FPSourceReg2, bool SetConditionReg = 0);
void PS_CMPO0(int FPReg1, int FPReg2, int CondField);
void PS_CMPO1(int FPReg1, int FPReg2, int CondField);
void PS_CMPU0(int FPReg1, int FPReg2, int CondField);
void PS_CMPU1(int FPReg1, int FPReg2, int CondField);
void PS_DIV(int FPDestReg, int FPSourceReg1, int FPSourceReg2, bool SetConditionReg = 0);
void PS_MADD(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void PS_MADDS0(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void PS_MADDS1(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void PS_MERGE00(int FPDestReg, int FPSourceReg1, int FPSourceReg2, bool SetConditionReg = 0);
void PS_MERGE01(int FPDestReg, int FPSourceReg1, int FPSourceReg2, bool SetConditionReg = 0);
void PS_MERGE10(int FPDestReg, int FPSourceReg1, int FPSourceReg2, bool SetConditionReg = 0);
void PS_MERGE11(int FPDestReg, int FPSourceReg1, int FPSourceReg2, bool SetConditionReg = 0);
void PS_MR(int FPDestReg, int FPSourceReg, bool SetConditionReg = 0);
void PS_MSUB(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void PS_MUL(int FPDestReg, int FPSourceReg1, int FPSourceReg2, bool SetConditionReg = 0);
void PS_MULS0(int FPDestReg, int FPSourceReg1, int FPSourceReg2, bool SetConditionReg = 0);
void PS_MULS1(int FPDestReg, int FPSourceReg1, int FPSourceReg2, bool SetConditionReg = 0);
void PS_NABS(int FPDestReg, int FPSourceReg, bool SetConditionReg = 0);
void PS_NEG(int FPDestReg, int FPSourceReg, bool SetConditionReg = 0);
void PS_NMADD(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void PS_NMSUB(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void PS_RES(int FPDestReg, int FPSourceReg, bool SetConditionReg = 0);
void PS_RSQRTE(int FPDestReg, int FPSourceReg, bool SetConditionReg = 0);
void PS_SEL(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void PS_SUB(int FPDestReg, int FPSourceReg1, int FPSourceReg2, bool SetConditionReg = 0);
void PS_SUM0(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void PS_SUM1(int FPDestReg, int FPSourceReg1, int FPSourceReg2, int FPSourceReg3, bool SetConditionReg = 0);
void RLWIMI(int DestReg, int SourceReg, int ShiftNum, int MaskStart, int MaskEnd, bool SetConditionReg = 0);
void RLWINM(int DestReg, int SourceReg, int ShiftNum, int MaskStart, int MaskEnd, bool SetConditionReg = 0);
void RLWNM(int DestReg, int SourceReg, int ShiftReg, int MaskStart, int MaskEnd, bool SetConditionReg = 0);
void SRAWI(int DestReg, int SourceReg, int ShiftNum, bool SetConditionReg = 0);
void STB(int SourceReg, int AddressReg, int Immediate);
void STB(int SourceReg, int AddressReg, int Immediate);
void STBU(int SourceReg, int AddressReg, int Immediate);
void STBUX(int SourceReg, int AddressReg1, int AddressReg2);
void STBX(int SourceReg, int AddressReg1, int AddressReg2);
void STFD(int SourceReg, int AddressReg, int Immediate);
void STFDU(int SourceReg, int AddressReg, int Immediate);
void STFDUX(int DestReg, int AddressReg1, int AddressReg2);
void STFDX(int DestReg, int AddressReg1, int AddressReg2);
void STFIWX(int SourceReg, int AddressReg1, int AddressReg2);
void STFS(int SourceReg, int AddressReg, int Immediate);
void STFSU(int SourceReg, int AddressReg, int Immediate);
void STH(int SourceReg, int AddressReg, int Immediate);
void STHU(int SourceReg, int AddressReg, int Immediate);
void STHUX(int SourceReg, int AddressReg1, int AddressReg2);
void STHX(int SourceReg, int AddressReg1, int AddressReg2);
void STSWI(int StartReg, int AddressReg, int Immediate);
void STSWX(int StartReg, int AddressReg1, int AddressReg2);
void STSWX(int StartReg, int AddressReg1, int AddressReg2, int NumArgsReg);
void STMW(int StartReg, int AddressReg,  int Immediate);
void STW(int SourceReg, int AddressReg, int Immediate);
void STWU(int SourceReg, int AddressReg, int Immediate);
void STWUX(int SourceReg, int AddressReg1, int AddressReg2);
void STWX(int SourceReg, int AddressReg1, int AddressReg2);
//DestReg = SourceReg1 - SourceReg2
void SUBF(int DestReg, int SourceReg1, int SourceReg2, bool SetConditionReg = 0);
void SUBFIC(int DestReg, int SourceReg, int Immediate);
void SYNC();
void XOR(int DestReg, int SourceReg1, int SourceReg2, bool SetConditionReg = 0);
void XORI(int DestReg, int SourceReg, int Immediate);
void XORIS(int DestReg, int SourceReg, int Immediate);