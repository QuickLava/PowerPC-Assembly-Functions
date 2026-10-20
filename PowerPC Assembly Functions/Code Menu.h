#pragma once

#include "stdafx.h"
#include "PowerPC Assembly Functions.h"

#include <filesystem>
#include <map>
#include <array>
#include "ConstantOverrides.h"
#include "_XMLProcessing.h"

//active codes
extern int MENU_TITLE_CHECK_LOCATION; // No longer used!
extern int DI_DRAW_INDEX;
extern int DEBUG_MODE_INDEX;
extern int DISPLAY_HITBOXES_INDEX;
extern int DISPLAY_COLLISION_INDEX;
extern int DISPLAY_LEDGEGRAB_INDEX;
extern int HUD_DISPLAY_INDEX;
extern int CHARACTER_SELECT_P1_INDEX;
extern int CHARACTER_SELECT_P2_INDEX;
extern int CHARACTER_SELECT_P3_INDEX;
extern int CHARACTER_SELECT_P4_INDEX;
extern int COSTUME_SELECT_P1_INDEX;
extern int COSTUME_SELECT_P2_INDEX;
extern int COSTUME_SELECT_P3_INDEX;
extern int COSTUME_SELECT_P4_INDEX;
extern int INFINITE_SHIELDS_P1_INDEX;
extern int INFINITE_SHIELDS_P2_INDEX;
extern int INFINITE_SHIELDS_P3_INDEX;
extern int INFINITE_SHIELDS_P4_INDEX;
extern int CAMERA_LOCK_INDEX;
extern int ENDLESS_FRIENDLIES_MODE_INDEX;
extern int ENDLESS_FRIENDLIES_STAGE_SELECTION_INDEX;
extern int RANDOM_1_TO_1_INDEX;
extern int AUTO_SAVE_REPLAY_INDEX;
extern int SAVE_STATES_INDEX;
extern int SAVE_REPLAY_ANYWHERE_INDEX;
extern int AUTO_SKIP_TO_CSS_INDEX;
extern int CODE_MENU_ACTIVATION_SETTING_INDEX;
extern int PERCENT_SELECT_VALUE_P1_INDEX;
extern int PERCENT_SELECT_ACTIVATOR_P1_INDEX;
extern int PERCENT_SELECT_VALUE_P2_INDEX;
extern int PERCENT_SELECT_ACTIVATOR_P2_INDEX;
extern int PERCENT_SELECT_VALUE_P3_INDEX;
extern int PERCENT_SELECT_ACTIVATOR_P3_INDEX;
extern int PERCENT_SELECT_VALUE_P4_INDEX;
extern int PERCENT_SELECT_ACTIVATOR_P4_INDEX;
extern int DISABLE_DPAD_P1_INDEX;
extern int DISABLE_DPAD_P2_INDEX;
extern int DISABLE_DPAD_P3_INDEX;
extern int DISABLE_DPAD_P4_INDEX;
extern int FPS_DISPLAY_INDEX;
extern int DBZ_MODE_INDEX;
extern int DBZ_MODE_MAX_SPEED_X_INDEX;
extern int DBZ_MODE_ACCEL_X_INDEX;
extern int DBZ_MODE_MAX_SPEED_Y_INDEX;
extern int DBZ_MODE_ACCEL_Y_INDEX;
extern int ALT_STAGE_BEHAVIOR_INDEX;
extern int P1_TAG_STRING_INDEX;
extern int P2_TAG_STRING_INDEX;
extern int P3_TAG_STRING_INDEX;
extern int P4_TAG_STRING_INDEX;
extern int TAG_COSTUME_TOGGLE_INDEX;
extern int CROWD_CHEER_TOGGLE_INDEX;
extern int ALC_P1_INDEX;
extern int ALC_P2_INDEX;
extern int ALC_P3_INDEX;
extern int ALC_P4_INDEX;
extern int ALC_P1_FLASH_RED_INDEX;
extern int ALC_P2_FLASH_RED_INDEX;
extern int ALC_P3_FLASH_RED_INDEX;
extern int ALC_P4_FLASH_RED_INDEX;
extern int BIG_HEAD_INDEX;
extern int RANDOM_ANGLE_INDEX;
extern int WAR_MODE_INDEX;
extern int BUFFER_P1_INDEX;
extern int BUFFER_P2_INDEX;
extern int BUFFER_P3_INDEX;
extern int BUFFER_P4_INDEX;
extern int SCALE_INDEX;
extern int SPEED_INDEX;
extern int CSS_VERSION_SETTING_INDEX;
extern int THEME_SETTING_INDEX;
extern int DASH_ATTACK_ITEM_GRAB_INDEX;
extern int TRIP_TOGGLE_INDEX;
extern int TRIP_RATE_MULTIPLIER_INDEX;
extern int TRIP_INTERVAL_INDEX;
extern int PSCC_COLOR_1_INDEX;
extern int PSCC_COLOR_2_INDEX;
extern int PSCC_COLOR_3_INDEX;
extern int PSCC_COLOR_4_INDEX;
extern int JUMPSQUAT_OVERRIDE_TOGGLE_INDEX;
extern int JUMPSQUAT_OVERRIDE_FRAMES_INDEX;
extern int JUMPSQUAT_OVERRIDE_MIN_INDEX;
extern int JUMPSQUAT_OVERRIDE_MAX_INDEX;

//constant overrides
extern vector<ConstantPair> constantOverrides;
extern int SDI_DISTANCE_INDEX;
extern int HITSTUN_MULTIPLIER_INDEX;
extern int HITLAG_MAXIMUM_INDEX;
extern int HITLAG_MULTIPLIER_INDEX;
extern int ELECTRIC_HITLAG_MULTIPLIER_INDEX;
extern int ASDI_DISTANCE_INDEX;
extern int WALLJUMP_HORIZONTAL_MULTIPLIER_INDEX;
extern int MINIMUM_SHIELD_SIZE_SCALING_INDEX;
extern int SHIELD_DAMAGE_MULTIPLIER_INDEX;
extern int SHIELD_BASE_DAMAGE_INDEX;
extern int SHIELD_SIZE_MULTIPLIER_INDEX;
extern int SHIELD_TILT_MULTIPLIER_INDEX;
extern int KNOCKBACK_DECAY_MULTIPLIER_INDEX;
extern int WALL_BOUNCE_KNOCKBACK_MULTIPLIER_INDEX;
extern int STALING_TOGGLE_INDEX;

//dpad same, + is start, 2 is A, 1 is B, A is Y, B is X, - is Z
const vector<u8> CODE_MENU_WIIMOTE_CONVERSION_TABLE = { 2, 3, 1, 0, 12, 31, 31, 31, 8, 9, 10, 11, 4, 31, 31, 31 };
//dpad same, + and - are start, A and B are A and B, C is Y, Z is start, 1 is X, 2 is Z
//dpad same, + is start, A and B are A and B, C is Y, Z is Z, - is X
const vector<u8> CODE_MENU_WIICHUCK_CONVERSION_TABLE = { 0, 1, 2, 3, 12, 31, 31, 31, 31, 31, 9, 8, 10, 4, 11, 31 };
const vector<u8> CODE_MENU_CLASSIC_CONVERSION_TABLE = { 3, 0, 4, 10, 8, 11, 9, 4, 31, 5, 12, 31, 12, 6, 2, 1 }; //1 to 1

// Enumeration of all predefined characters' Slot IDs.
enum LAVA_CHARA_SLOT_IDS
{
	LCSI_BOWSER = 0x0C,
	LCSI_CAPTAIN_FALCON = 0x0A,
	LCSI_CHARIZARD = 0x1E,
	LCSI_DEDEDE = 0x23,
	LCSI_DIDDY_KONG = 0x1C,
	LCSI_DONKEY_KONG = 0x01,
	LCSI_FALCO = 0x15,
	LCSI_FOX = 0x07,
	LCSI_GANONDORF = 0x16,
	LCSI_GIGA_BOWSER = 0x2C,
	LCSI_ICE_CLIMBERS = 0x10,
	LCSI_IKE = 0x25,
	LCSI_IVYSAUR = 0x22,
	LCSI_JIGGLYPUFF = 0x27,
	LCSI_KIRBY = 0x06,
	LCSI_LINK = 0x02,
	LCSI_LUCARIO = 0x24,
	LCSI_LUCAS = 0x1B,
	LCSI_LUIGI = 0x09,
	LCSI_MARIO = 0x00,
	LCSI_MARTH = 0x13,
	LCSI_META_KNIGHT = 0x18,
	LCSI_MR_GAME_AND_WATCH = 0x14,
	LCSI_NESS = 0x0B,
	LCSI_OLIMAR = 0x1A,
	LCSI_PEACH = 0x0D,
	LCSI_PIKACHU = 0x08,
	LCSI_PIT = 0x19,
	LCSI_POKETRAINER = 0x48,
	LCSI_POKETRAINER_CHARIZARD = 0x1D,
	LCSI_POKETRAINER_IVYSAUR = 0x21,
	LCSI_POKETRAINER_SQUIRTLE = 0x1F,
	LCSI_ROB = 0x26,
	LCSI_SAMUS = 0x03,
	LCSI_SHEIK = 0x0F,
	LCSI_SNAKE = 0x2A,
	LCSI_SONIC = 0x2B,
	LCSI_SOPO = 0x11,
	LCSI_SQUIRTLE = 0x20,
	LCSI_TOON_LINK = 0x28,
	LCSI_WARIO = 0x17,
	LCSI_WARIOMAN = 0x2D,
	LCSI_WOLF = 0x29,
	LCSI_YOSHI = 0x05,
	LCSI_ZELDA = 0x0E,
	LCSI_ZERO_SUIT_SAMUS = 0x04,
	LCSI_ROY = 0x32,
	LCSI_MEWTWO = 0x33,
	LCSI_KNUCKLES = 0x35,
	LCSI_RIDLEY = 0x38,
	LCSI_WALUIGI = 0x39,
	LCSI_DARK_SAMUS = 0x40,
	LCSI_SCEPTILE = 0x62,
	LCSI_ALLOY_RED = 0x6A,
	LCSI_ALLOY_BLUE = 0x6B,
	LCSI_ALLOY_YELLOW = 0x6C,
	LCSI_ALLOY_GREEN = 0x6D,
	LCSI_ZERO = 0x67,
};

template <typename T1, typename T2>
bool zipVectorsToMap(const std::vector<T1>& vec1, const std::vector<T2>& vec2, std::map<T1, T2>& destinationMap)
{
	bool result = 0;

	if (vec1.size() == vec2.size())
	{
		result = 1;
		destinationMap.clear();
		for (std::size_t i = 0; i < vec1.size(); i++)
		{
			auto res = destinationMap.emplace(vec1[i], vec2[i]);
			if (res.second == 1)
			{
				res.first->second = vec2[i];
			}
		}
	}

	return result;
}
template <typename T1, typename T2>
void unzipMapToVectors(const std::map<T1, T2>& sourceMap, std::vector<T1>& vec1, std::vector<T2>& vec2)
{
	vec1.resize(sourceMap.size());
	vec2.resize(sourceMap.size());
	std::size_t index = 0;
	for (auto itr = sourceMap.begin(); itr != sourceMap.end(); itr++)
	{
		vec1[index] = itr->first;
		vec2[index] = itr->second;
		index++;
	}
}

// Declares existence of the two main character lists, populated by the function below.
// If COLLECT_EXTERNAL_EX_CHARACTERS (in "PowerPC Assembly Functions.h") is set to true,
// additional EX Character declarations will be collected from the file described by exCharInputFilename (see "Code Menu.cpp").
extern vector<string> CHARACTER_LIST;
extern vector<u16> CHARACTER_ID_LIST;
constexpr unsigned char CHARACTER_ID_MAX_VALUE = 0x7F;
void buildCharacterIDLists();
bool applyCharacterListVersion(unsigned long targetVersion);

// Declares existence of the two main roster lists, populated by the function below.
// If COLLECT_EXTERNAL_ROSTERS (in "PowerPC Assembly Functions.h") is set to true,
// additional Roster declarations will be collected from the file described by rosterInputFilename (see "Code Menu.cpp").
extern vector<string> ROSTER_LIST;
extern vector<string> ROSTER_FILENAME_LIST;
void buildRosterLists();

// Declares existence of two main theme lists, populated by the function below.
// If COLLECT_EXTERNAL_THEMES (in "PowerPC Assembly Functions.h") is set to true,
// additional Theme declarations will be collected from the file described by themeInputFilename (see "Code Menu.cpp").
namespace themeConstants
{
	enum themePathIndices
	{
		tpi_MENUMAIN = 0,
		tpi_SELCHAR,
		tpi_SELCHAR2,
		tpi_SELMAP,
		tpi_SELEVENT,
		tpi_TITLE,
		tpi__PATH_COUNT
	};

	constexpr unsigned long prefixLength = 0x03;
	
	extern std::array<std::string, tpi__PATH_COUNT> filenames;
}
struct menuTheme
{
	std::string name = "";
	std::array<std::string, themeConstants::tpi__PATH_COUNT> prefixes{};
	menuTheme(std::string name = "");
};
void initializeThemeConstants();
void buildThemeLists();
std::string getThemeFileBaseName(themeConstants::themePathIndices fileIndex);
std::string getThemeFileDefaultPrefix(themeConstants::themePathIndices fileIndex);
extern vector<string> THEME_LIST;
extern std::vector<menuTheme> THEME_SPEC_LIST;
// Notes, for each theme-able file, whether or not any specified themes actually use a non-standard prefix for it.
// Used to determine whether or not we actually need to output the hook for a given theme-able file.
extern std::array<bool, themeConstants::tpi__PATH_COUNT> THEME_FILE_GOT_UNIQUE_PREFIX;

namespace pscc
{
	struct color
	{
		enum flagBits
		{
			fb_INVERT_HUE_MOD       = 0b00000001,
			fb_DISABLE_HUE_MOD      = 0b00000010,
			fb_DISABLE_SAT_MOD_UP   = 0b00000100,
			fb_DISABLE_SAT_MOD_DOWN = 0b00001000,
			fb_DISABLE_LUM_MOD_UP   = 0b00010000,
			fb_DISABLE_LUM_MOD_DOWN = 0b00100000,
		};

		float hue;
		float saturation;
		float luminance;
		unsigned char flags;
		unsigned char callbackFunctionIndex;

		color(float hueIn = 0.0f, float satIn = 1.0f, float lumIn = 1.0f, unsigned char flagsIn = 0x00, unsigned char callbackIdxIn = UCHAR_MAX) :
			hue(hueIn), saturation(satIn), luminance(lumIn), flags(flagsIn), callbackFunctionIndex(callbackIdxIn) {};
		bool colorValid() const;
	};
	extern std::map<std::string, color> colorTable;
	static constexpr std::size_t colorTableEntrySizeInBytes = 0x8;
	static constexpr std::size_t callbackTableEntryCount = 0x8;
	std::size_t getColorTableSizeInBytes();
	std::size_t getColorTableOffsetToColor(std::string colorName);


	enum schemePredefIDs
	{
		spi_P1 = 0,
		spi_P2,
		spi_P3,
		spi_P4,
		spi__COUNT
	};
	enum colorSchemeColorSlots
	{
		cscs_MENU1 = 0,
		cscs_MENU2,
		cscs_INGAME1,
		cscs_INGAME2,
		cscs__COUNT
	};
	struct colorScheme
	{
		std::string name;
		std::array<std::string, cscs__COUNT> colors;
		colorScheme(std::string nameIn = "");
		void downfillEmptySlots();
		bool schemeValid() const;
	};
	struct colorSchemeTable
	{
		std::vector<colorScheme> entries;
		colorSchemeTable();
		static constexpr std::size_t schemeTableEntrySizeInBytes = colorSchemeColorSlots::cscs__COUNT;
		std::size_t tableSizeInBytes() const;
		std::vector<unsigned char> tableToByteVec() const;
	};
	extern colorSchemeTable schemeTable;
	
	std::size_t getFullEmbedSizeInWords();
}

// Logging and Input Constants
extern const std::string outputFolder;
extern const std::string menuConfigXMLFileName;
extern const std::string netMenuConfigXMLFileName;
extern const std::string addonInputFolderPath;
extern const std::string addonInputSourceFilename;
extern const std::string addonInputConfigFilename;
extern const std::string addonINDEXFileFilename;
extern const std::string addonAliasBankFilename;
extern const std::string addonOutputFolderName;
extern const std::string symbolMapInputFileName;
extern const std::string changelogFileName;
extern const std::string optionsFilename;
// Code Menu Output Constants
extern const std::string asmFileName;
extern const std::string asmTextFileName;
extern const std::string cmnuFileName;
extern const std::string asmOutputFilePath;
extern const std::string cmnuOutputFilePath;
extern const std::string cmnuOptionsOutputFilePath;
extern const std::string asmTextOutputFilePath;
extern const std::vector<std::string> asmBuildLocationDirectories;
extern const std::string cmnuBuildLocationDirectory;
extern const std::string cmnuBuildLocationFilePath;
extern const std::string addonsOutputFolderPath;
extern const std::string addonsBuildLocationFolderPath;
std::string getCMNUAbsolutePath();
// AutoGCTRM Constants
extern const std::string buildFolder;
extern const std::string GCTRMExePath;
extern const std::string GCTRMCommandBase;
extern const std::string mainGCTName;
extern const std::string mainGCTFile;
extern const std::string mainGCTTextFile;
extern const std::string boostGCTName;
extern const std::string boostGCTFile;
extern const std::string boostGCTTextFile;

// The stream for the MenuFile.
// Path is no longer specified in this line, is instead controlled by the above paths and applied in initMenuFileStream().
static fstream MenuFile;
void initMenuFileStream();
// The output bundle for logging purposes!
struct __logOutputStruct : public lava::outputSplitter
{
	static constexpr unsigned long changelogID = 0x10000;
	__logOutputStruct();
	std::ostream* getChangelogPtr();
};
extern __logOutputStruct ChangelogOutput;

std::vector<std::string_view> splitLineContentString(const std::string& joinedStringIn);
std::string getLineNameFromLineText(const std::string& lineText);

static const int START_OF_CODE_MENU = END_OF_CODE_MENU_HEADER;
static int CurrentOffset = START_OF_CODE_MENU;

#define CODE_MENU_GECKO_IF(MenuIndex) if(MenuIndex != -1) {\
									GeckoIf(MenuIndex, EQUAL, 1); {
#define CODE_MENU_GECKO_ENDIF }GeckoEndIf(); }

//code menu flags
#define CODE_MENU_CLOSED 0
#define CODE_MENU_PRIMED 1
#define CODE_MENU_TRIGGERED 2
#define CODE_MENU_CLOSING 3
#define CODE_MENU_OPEN 4

//line types
#define SELECTION_LINE 0
#define INTEGER_LINE 1
#define FLOATING_LINE 2
#define HAS_VALUE_LIMIT 2
#define SUB_MENU_LINE 3
#define COMMENT_LINE 4
#define PRINT_LINE 5

//default code menu settings
#define INITIAL_XPOS -200
#define INITIAL_YPOS -150
#define LINE_HEIGHT 18
#define MOVE_THRESHHOLD 65
#define INCREMENT_THRESHHOLD 50
#define MOVE_NUM_WAIT_FRAMES 5
#define FIRST_MOVE_NUM_WAIT_FRAMES 15
#define INCREMENT_NUM_WAIT_FRAMES 5
#define FIRST_INCREMENT_NUM_WAIT_FRAMES 15
#define FRAME_ADVANCE_NUM_WAIT_FRAMES 4
#define FIRST_FRAME_ADVANCE_NUM_WAIT_FRAMES 16
#define TRIGGER_ENTER_SUB_MENU_BUTTON BUTTON_A
#define TRIGGER_LEAVE_SUB_MENU_BUTTON BUTTON_B
#define TRIGGER_RESET_LINE_BUTTON BUTTON_X
#define TRIGGER_RESET_PAGE_BUTTON BUTTON_Y
#define SCROLL_DISTANCE 15

//action types
#define NO_ACTION 0
#define MOVE_UP 1
#define MOVE_DOWN 2
#define ENTER_SUB_MENU 3
#define LEAVE_SUB_MENU 4
#define INCREMENT 5
#define DECREMENT 6
#define EXIT_MENU 7
#define RESET_LINE 8
#define RESET_PAGE 9

#define FRAMES_UNTIL_SLOW_MOTION 12
#define FRAMES_WAITED_DURING_SLOW_MOTION 3

class Page;
// Maps page shortnames to their respective structs.
extern std::map<lava::shortNameType, Page*> menuPagesMap;
// Returns true if a given page shortname is free to use.
bool pageShortnameIsFree(lava::shortNameType nameIn);

class Line
{
public:
	enum LineBehaviorFlags
	{
		lbf_LOCKED = 0,
		lbf_HIDDEN,
		lbf_STICKY,
		lbf_REMOVED,
		lbf__COUNT
	};
	struct LineBehaviorFlagSetting
	{
		bool forceXMLOutput = 0;
		bool value = 0;
		operator bool() const
		{
			return value;
		}
	};
	std::array<LineBehaviorFlagSetting, LineBehaviorFlags::lbf__COUNT> behaviorFlags{};

	// Note: The top 4 bits of the Flags Byte are line-specific flags, bottom 4 are line-agnostic flags (see Line::LINE_FLAGS_FIELDS enum)!
	enum LINE_FLAGS_FIELDS
	{
		// Makes line immune to being reset to its default value!
		LINE_FLAG_IGNORE_INDIRECT_RESET = 0b00000001,
		// Makes line unselectable and invisible!
		LINE_FLAG_HIDE_FROM_USER        = 0b00000010,
		// Disables changing the line's value manually!
		LINE_FLAG_VALUE_LOCKED          = 0b00000100,
	};

	Line();
	Line(string Text, u16 TextOffset, u8 type, u8 flags, u8 ColorOffset, int* Index = nullptr);
	virtual void WriteLineData();
	void WriteLineData(vector<u8> SelectionOffsets);
	void WritePadding();

	int* Index = nullptr;
	u32 numArgs;
	u32 Value = 0xFFFFFFFF;
	u32 Default;
	u32 Max;
	u32 Min;
	u32 Speed;
	Page *SubMenuPtr;
	u16 SubMenuOffset;
	int PageOffset;
	u8 type;
	u8 Color;
	// Note: The top 4 bits of the Flags Byte are line-specific flags, bottom 4 are line-agnostic flags (see Line::LINE_FLAGS_FIELDS enum)!
	u8 Flags = 0;
	u16 TextOffset;
	u16 DownOffset = 0;
	u16 UpOffset = 0;
	string Text;
	u16 Size;
	u8 lineNum;
	int Padding;
	vector<int*> args;

	// Truncated version of the Text field. Just everything before the first colon (":") in the first delimited string.
	std::string LineName = "";
	// Parent Page's Name
	std::string ParentPageName = "";
	// Allows a line to be forcibly hidden from the Options XML (mostly just here to hide the Toggle base line).
	bool hideFromOptionsXML = 0;

	//offsets
	static const int SIZE = 0; //2
	static const int TYPE = SIZE + 2; //1
	// Note: The top 4 bits of the Flags Byte are line-specific flags, bottom 4 are line-agnostic flags (see Line::LINE_FLAGS_FIELDS enum)!
	static const int FLAGS = TYPE + 1; //1
	static const int COLOR = FLAGS + 1; //1
	static const int TEXT_OFFSET = COLOR + 1; //2
	static const int LINE_NUM = TEXT_OFFSET + 2; //1
	static const int VALUE = LINE_NUM + 1; //4
	static const int PRINT_LINE_NUM_ARGS = VALUE + 4; //4
	static const int PRINT_LINE_TEXT_START = PRINT_LINE_NUM_ARGS + 4;
	static const int COMMENT_LINE_TEXT_START = VALUE + 4;
	static const int UP = VALUE + 4; //2
	static const int DOWN = UP + 2; //2
	static const int SUB_MENU = DOWN + 2; //2
	static const int SUB_MENU_LINE_TEXT_START = SUB_MENU + 2;
	static const int DEFAULT = DOWN + 2; //4
	static const int MAX = DEFAULT + 4; //4
	static const int SELECTION_LINE_SOURCE_SELECTION_INDEX = MAX + 4; // 0x4
	static const int SELECTION_LINE_OFFSETS_START = SELECTION_LINE_SOURCE_SELECTION_INDEX + 4; // 0x4
	static const int MIN = MAX + 4; //4
	static const int SPEED = MIN + 4; //4
	static const int NUMBER_LINE_TEXT_START = SPEED + 4;
};

class Comment : public Line
{
public:
	Comment(string Text, int* Index = nullptr);
	void WriteLineData();
};

class Print : public Line {
public:
	Print(string Text, vector<int*> args = {});
	void WriteLineData();
private:
	vector<int> argValues;
};

class Selection : public Line
{
public:
	Selection(string Text, vector<string> Options, vector<u16> Values, int Default, int& Index);
	Selection(string Text, vector<string> Options, int Default, int& Index);
	Selection(string Text, vector<string> Options, vector<u16> Values, string Default, int& Index);
	Selection(string Text, vector<string> Options, string Default, int& Index);
	string CreateSelectionString(string Text, vector<string> Options);
	vector<u16> CreateVector(vector<string> x);
	void WriteLineData();
	std::vector<std::string_view> getOptionStringViews();

	bool isToggleLine = 0;
	Selection* SourceSelectionPtr = nullptr;
	vector<u8> OptionOffsets;
};

class SelectionMirror : public Selection
{
public:
	SelectionMirror(Selection& SourceSelection, std::string Text, int Default, int& Index, bool inheritFlags = 1);
};

class Toggle : public Selection
{
private:
	static Toggle* firstToggleInstancePtr;
public:
	Toggle(string Text, bool Default, int &Index);
};

class SubMenu : public Line
{
public:
	SubMenu();
	SubMenu(string Text, Page* SubMenuPtr);
};

class Integer : public Line
{
public:
	enum INTEGER_FLAGS_FIELDS
	{
		INT_FLAG_ALLOW_WRAP = 0b10000000,
	};

	Integer(string Text, int Min, int Max, int Default, int Speed, int& Index, std::string format = "%d", u8 flags = 0);
};

class Floating : public Line
{
public:
	Floating(string Text, float Min, float Max, float Default, float Speed, int& Index, string format = "%f");
	bool forceHexXMLOutput = 0;
};

class Page
{
public:
	string PageName = "";
	u32 CurrentLineOffset;
	u32 Size;
	u32 PrevPageOffset = 0;
	u32 NumChangedLines = 0;
	u32 PrintLowHold = 0;
	vector<Line*> Lines;
	int CalledFromLineIndex = -1;
	std::shared_ptr<SubMenu> CalledFromLine;
	static const int NUM_WORD_ELEMS = 5;
	static const int CURRENT_LINE_OFFSET = 0;
	static const int PREV_PAGE = CURRENT_LINE_OFFSET + 4;
	static const int NUM_CHANGED_LINES = PREV_PAGE + 4;
	static const int PRINT_LOW_HOLD = NUM_CHANGED_LINES + 4;
	static const int CALLED_FROM_LINE = PRINT_LOW_HOLD + 4;
	static const int FIRST_LINE_OFFSET = NUM_WORD_ELEMS * 4;

	Page(string Name, vector<Line*> Lines, lava::shortNameType shortName = lava::shortNameType(""));
	void PrepareLines();
	void PrepareLines(const std::vector<Line*> LinesIn);
	void WritePage();
	void ConnectSelectableLines();
	void GetSelectableLines(vector<int>& SelectableLines);
};

void PrintChar(int SettingsPtrReg, int CharReg);
void PrintString(int StringPtrReg, int NumCharsReg, int SettingsPtrReg);
void DrawBlackBackground();
void PrintPage(int PageReg, int SettingPtrReg, int Reg1, int Reg2, int Reg3, int Reg4, int Reg5, int Reg6);
void PrintCodeMenuLine(int LinePtrReg, int SettingsPtrReg, int ColorArrayPtrReg, int TempReg1, int TempReg2);
void SetTextColor(int ColorReg, int SettingsPtrReg);
void SetTextSize(int FPSizeReg, int SettingsPtrReg);
void CodeMenu();
void ActualCodes();
void ControlCodeMenu();
void PrintCodeMenu();
void PrimeCodeMenu();
void CreateMenu(Page& MainPage);
void ExecuteAction(int ActionReg, int ResetAccumulatorReg);
extern int ResetLineSubroutineLabel;
void ResetLineSubroutine(int ResetAccumulatorReg);
extern int ModifyLineValueSubroutineLabel;
void ModifyLineValueSubroutine();
void ResetPage();
void ExitMenu();
void EnterMenu(int LineReg, int PageReg, int TypeReg, int TempReg1, int TempReg2);
void LeaveMenu(int PageReg, int TempReg1, int TempReg2, int TempReg3, int TempReg4, int TempReg5, int TempReg6, int ActionReg);
void Move(int LineReg, int PageReg, int NextLineOffset, int TempReg1, int TempReg2);
void GetActionFromInputs(int ButtonReg, int ControlStickXReg, int ControlStickYReg, int ResultReg);
void SetControlStickAction(int StickValReg, int TimerLoc, int NumWaitFrames, int FirstTimeNumWaitFrames, int Threshhold, int PositiveAction, int NegativeAction, int ResultReg);
void ApplyMenuSetting(int Index, int Destination, int reg1, int reg2, int size = 4);
void GetArrayValueFromIndex(int ArrayLoc, int IndexReg, int min, int max, int ResultReg = 3);
void RunIfPortToggle(int ARRAY_LOC, int PortReg);
void SaveReplay();
void SetupPrintText(int SettingPtrReg);
void SetTextPos(int XPosReg, int YPosReg, int SettingPtrReg);
void constantOverride();
