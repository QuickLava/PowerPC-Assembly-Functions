#include "stdafx.h"
#include "Code Menu.h"
#include "DrawDI.h"
#include "IASA Overlay.h"
#include "Control Codes.h"
#include "Save States.h"
#include "DBZ Mode.h"
#include <regex>

int MENU_TITLE_CHECK_LOCATION;
int DI_DRAW_INDEX = -1;
int DEBUG_MODE_INDEX = -1;
int DISPLAY_HITBOXES_INDEX = -1;
int DISPLAY_COLLISION_INDEX = -1;
int DISPLAY_LEDGEGRAB_INDEX = -1;
int HUD_DISPLAY_INDEX = -1;
int CHARACTER_SELECT_P1_INDEX = -1;
int CHARACTER_SELECT_P2_INDEX = -1;
int CHARACTER_SELECT_P3_INDEX = -1;
int CHARACTER_SELECT_P4_INDEX = -1;
int INFINITE_SHIELDS_P1_INDEX = -1;
int INFINITE_SHIELDS_P2_INDEX = -1;
int INFINITE_SHIELDS_P3_INDEX = -1;
int INFINITE_SHIELDS_P4_INDEX = -1;
int CAMERA_LOCK_INDEX = -1;
int ENDLESS_FRIENDLIES_MODE_INDEX = -1;
int ENDLESS_FRIENDLIES_STAGE_SELECTION_INDEX = -1;
int RANDOM_1_TO_1_INDEX = -1;
int AUTO_SAVE_REPLAY_INDEX = -1;
int SAVE_STATES_INDEX = -1;
int SAVE_REPLAY_ANYWHERE_INDEX = -1;
int AUTO_SKIP_TO_CSS_INDEX = -1;
int CODE_MENU_ACTIVATION_SETTING_INDEX = -1;
int PERCENT_SELECT_VALUE_P1_INDEX = -1;
int PERCENT_SELECT_ACTIVATOR_P1_INDEX = -1;
int PERCENT_SELECT_VALUE_P2_INDEX = -1;
int PERCENT_SELECT_ACTIVATOR_P2_INDEX = -1;
int PERCENT_SELECT_VALUE_P3_INDEX = -1;
int PERCENT_SELECT_ACTIVATOR_P3_INDEX = -1;
int PERCENT_SELECT_VALUE_P4_INDEX = -1;
int PERCENT_SELECT_ACTIVATOR_P4_INDEX = -1;
int DISABLE_DPAD_P1_INDEX = -1;
int DISABLE_DPAD_P2_INDEX = -1;
int DISABLE_DPAD_P3_INDEX = -1;
int DISABLE_DPAD_P4_INDEX = -1;
int FPS_DISPLAY_INDEX = -1;
int DBZ_MODE_INDEX = -1;
int DBZ_MODE_MAX_SPEED_X_INDEX = -1;
int DBZ_MODE_ACCEL_X_INDEX = -1;
int DBZ_MODE_MAX_SPEED_Y_INDEX = -1;
int DBZ_MODE_ACCEL_Y_INDEX = -1;
int ALT_STAGE_BEHAVIOR_INDEX = -1;
int P1_TAG_STRING_INDEX = -1;
int P2_TAG_STRING_INDEX = -1;
int P3_TAG_STRING_INDEX = -1;
int P4_TAG_STRING_INDEX = -1;
int TAG_COSTUME_TOGGLE_INDEX = -1;
int CROWD_CHEER_TOGGLE_INDEX = -1;
int STALING_TOGGLE_INDEX = -1;
int ALC_P1_INDEX = -1;
int ALC_P2_INDEX = -1;
int ALC_P3_INDEX = -1;
int ALC_P4_INDEX = -1;
int ALC_P1_FLASH_RED_INDEX = -1;
int ALC_P2_FLASH_RED_INDEX = -1;
int ALC_P3_FLASH_RED_INDEX = -1;
int ALC_P4_FLASH_RED_INDEX = -1;
int BIG_HEAD_INDEX = -1;
int RANDOM_ANGLE_INDEX = -1;
int WAR_MODE_INDEX = -1;
int BUFFER_P1_INDEX = -1;
int BUFFER_P2_INDEX = -1;
int BUFFER_P3_INDEX = -1;
int BUFFER_P4_INDEX = -1;
int SCALE_INDEX = -1;
int SPEED_INDEX = -1;
int CSS_VERSION_SETTING_INDEX = -1;
int THEME_SETTING_INDEX = -1;
int DASH_ATTACK_ITEM_GRAB_INDEX = -1;
int TRIP_TOGGLE_INDEX = -1;
int TRIP_RATE_MULTIPLIER_INDEX = -1;
int TRIP_INTERVAL_INDEX = -1;
int PSCC_COLOR_1_INDEX = -1;
int PSCC_COLOR_2_INDEX = -1;
int PSCC_COLOR_3_INDEX = -1;
int PSCC_COLOR_4_INDEX = -1;
int JUMPSQUAT_OVERRIDE_TOGGLE_INDEX = -1;
int JUMPSQUAT_OVERRIDE_FRAMES_INDEX = -1;
int JUMPSQUAT_OVERRIDE_MIN_INDEX = -1;
int JUMPSQUAT_OVERRIDE_MAX_INDEX = -1;
int EXTERNAL_INDEX = -1;	//Used for GCTRM codes that use other indexs for context

//constant overrides
vector<ConstantPair> constantOverrides;
int SDI_DISTANCE_INDEX = -1;
int HITSTUN_MULTIPLIER_INDEX = -1;
int HITLAG_MAXIMUM_INDEX = -1;
int HITLAG_MULTIPLIER_INDEX = -1;
int ELECTRIC_HITLAG_MULTIPLIER_INDEX = -1;
int ASDI_DISTANCE_INDEX = -1;
int WALLJUMP_HORIZONTAL_MULTIPLIER_INDEX = -1;
int MINIMUM_SHIELD_SIZE_SCALING_INDEX = -1;
int SHIELD_DAMAGE_MULTIPLIER_INDEX = -1;
int SHIELD_BASE_DAMAGE_INDEX = -1;
int SHIELD_SIZE_MULTIPLIER_INDEX = -1;
int SHIELD_TILT_MULTIPLIER_INDEX = -1;
int KNOCKBACK_DECAY_MULTIPLIER_INDEX = -1;
int WALL_BOUNCE_KNOCKBACK_MULTIPLIER_INDEX = -1;

vector<string> CHARACTER_LIST{};
vector<u16> CHARACTER_ID_LIST{};
void buildCharacterIDLists()
{
	std::map<std::string, u16> characterNameToIDMap{};
	if (characterListVersion >= characterListVersions::clv_vBRAWL)
	{
		characterNameToIDMap.emplace("Bowser", LCSI_BOWSER);
		characterNameToIDMap.emplace("Captain Falcon", LCSI_CAPTAIN_FALCON);
		characterNameToIDMap.emplace("Charizard", LCSI_CHARIZARD);
		characterNameToIDMap.emplace("Dedede", LCSI_DEDEDE);
		characterNameToIDMap.emplace("Diddy Kong", LCSI_DIDDY_KONG);
		characterNameToIDMap.emplace("Donkey Kong", LCSI_DONKEY_KONG);
		characterNameToIDMap.emplace("Falco", LCSI_FALCO);
		characterNameToIDMap.emplace("Fox", LCSI_FOX);
		characterNameToIDMap.emplace("Ganondorf", LCSI_GANONDORF);
		characterNameToIDMap.emplace("Ice Climbers", LCSI_ICE_CLIMBERS);
		characterNameToIDMap.emplace("Ike", LCSI_IKE);
		characterNameToIDMap.emplace("Ivysaur", LCSI_IVYSAUR);
		characterNameToIDMap.emplace("Jigglypuff", LCSI_JIGGLYPUFF);
		characterNameToIDMap.emplace("Kirby", LCSI_KIRBY);
		characterNameToIDMap.emplace("Link", LCSI_LINK);
		characterNameToIDMap.emplace("Lucario", LCSI_LUCARIO);
		characterNameToIDMap.emplace("Lucas", LCSI_LUCAS);
		characterNameToIDMap.emplace("Luigi", LCSI_LUIGI);
		characterNameToIDMap.emplace("Mario", LCSI_MARIO);
		characterNameToIDMap.emplace("Marth", LCSI_MARTH);
		characterNameToIDMap.emplace("Meta Knight", LCSI_META_KNIGHT);
		characterNameToIDMap.emplace("Mr. Game and Watch", LCSI_MR_GAME_AND_WATCH);
		characterNameToIDMap.emplace("Ness", LCSI_NESS);
		characterNameToIDMap.emplace("Olimar", LCSI_OLIMAR);
		characterNameToIDMap.emplace("Peach", LCSI_PEACH);
		characterNameToIDMap.emplace("Pikachu", LCSI_PIKACHU);
		characterNameToIDMap.emplace("Pit", LCSI_PIT);
		characterNameToIDMap.emplace("R.O.B.", LCSI_ROB);
		characterNameToIDMap.emplace("Samus", LCSI_SAMUS);
		characterNameToIDMap.emplace("Sheik", LCSI_SHEIK);
		characterNameToIDMap.emplace("Snake", LCSI_SNAKE);
		characterNameToIDMap.emplace("Sonic", LCSI_SONIC);
		characterNameToIDMap.emplace("Squirtle", LCSI_SQUIRTLE);
		characterNameToIDMap.emplace("Toon Link", LCSI_TOON_LINK);
		characterNameToIDMap.emplace("Wario", LCSI_WARIO);
		characterNameToIDMap.emplace("Wolf", LCSI_WOLF);
		characterNameToIDMap.emplace("Yoshi", LCSI_YOSHI);
		characterNameToIDMap.emplace("Zelda", LCSI_ZELDA);
		characterNameToIDMap.emplace("Zero Suit Samus", LCSI_ZERO_SUIT_SAMUS);
	}
	if (characterListVersion >= characterListVersions::clv_vBRAWL_SPECIAL_CHARS)
	{
		characterNameToIDMap.emplace("Giga Bowser", LCSI_GIGA_BOWSER);
		characterNameToIDMap.emplace("Sopo", LCSI_SOPO);
		characterNameToIDMap.emplace("Warioman", LCSI_WARIOMAN);
	}
	if (characterListVersion >= characterListVersions::clv_PROJECTM)
	{
		characterNameToIDMap.emplace("Mewtwo", LCSI_MEWTWO);
		characterNameToIDMap.emplace("Roy", LCSI_ROY);
	}
	if (characterListVersion >= characterListVersions::clv_PPLUS)
	{
		characterNameToIDMap.emplace("Knuckles", LCSI_KNUCKLES);
	}
	if (characterListVersion >= characterListVersions::clv_PPEX_RIDLEY)
	{
		characterNameToIDMap.emplace("Ridley", LCSI_RIDLEY);
	}
	if (characterListVersion >= characterListVersions::clv_PPEX_WALUIGI)
	{
		characterNameToIDMap.emplace("Waluigi", LCSI_WALUIGI);
	}
	if (characterListVersion >= characterListVersions::clv_PPEX_ALLOYS)
	{
		characterNameToIDMap.emplace("Red Alloy", LCSI_ALLOY_RED);
		characterNameToIDMap.emplace("Blue Alloy", LCSI_ALLOY_BLUE);
		characterNameToIDMap.emplace("Yellow Alloy", LCSI_ALLOY_YELLOW);
		characterNameToIDMap.emplace("Green Alloy", LCSI_ALLOY_GREEN);
	}
	if (characterListVersion >= characterListVersions::clv_PPEX_SCEPTILE)
	{
		characterNameToIDMap.emplace("Sceptile", LCSI_SCEPTILE);
	}
	if (characterListVersion >= characterListVersions::clv_PPEX_DARK_SAMUS)
	{
		characterNameToIDMap.emplace("Dark Samus", LCSI_DARK_SAMUS);
	}

	unzipMapToVectors(characterNameToIDMap, CHARACTER_LIST, CHARACTER_ID_LIST);
}
bool applyCharacterListVersion(unsigned long targetVersion)
{
	bool result = 0;

	// If the targeted version is valid...
	if (targetVersion < characterListVersions::__clv_Count)
	{
		// ... replace the recorded list version...
		characterListVersion = targetVersion;
		// ... and rebuild the character lists.
		buildCharacterIDLists();
		result = 1;
	}

	return result;
}

vector<string> ROSTER_LIST{};
vector<string> ROSTER_FILENAME_LIST{};
void buildRosterLists()
{
	std::map<std::string, std::string> rosterNameToFileIDMap =
	{
		{"Default", "CSSRoster.dat"}
	};

	unzipMapToVectors(rosterNameToFileIDMap, ROSTER_LIST, ROSTER_FILENAME_LIST);
}

namespace themeConstants
{
	std::array<std::string, tpi__PATH_COUNT> filenames{};
}
void initializeThemeConstants()
{
	themeConstants::filenames.fill("");
	themeConstants::filenames[themeConstants::tpi_MENUMAIN] = "mu_menumain.pac";
	themeConstants::filenames[themeConstants::tpi_SELCHAR] = "sc_selcharacter.pac";
	themeConstants::filenames[themeConstants::tpi_SELCHAR2] = "sc_selcharacter2.pac";
	themeConstants::filenames[themeConstants::tpi_SELMAP] = "sc_selmap.pac";
	themeConstants::filenames[themeConstants::tpi_SELEVENT] = "sc_sel_event.pac";
	themeConstants::filenames[themeConstants::tpi_TITLE] = "sc_title.pac";
}
menuTheme::menuTheme(std::string name)
{
	prefixes[themeConstants::tpi_MENUMAIN] = getThemeFileDefaultPrefix(themeConstants::tpi_MENUMAIN);
	prefixes[themeConstants::tpi_SELCHAR] = getThemeFileDefaultPrefix(themeConstants::tpi_SELCHAR);
	prefixes[themeConstants::tpi_SELCHAR2] = getThemeFileDefaultPrefix(themeConstants::tpi_SELCHAR2);
	prefixes[themeConstants::tpi_SELMAP] = getThemeFileDefaultPrefix(themeConstants::tpi_SELMAP);
	prefixes[themeConstants::tpi_SELEVENT] = getThemeFileDefaultPrefix(themeConstants::tpi_SELEVENT);
	prefixes[themeConstants::tpi_TITLE] = getThemeFileDefaultPrefix(themeConstants::tpi_TITLE);
}
void buildThemeLists()
{
	initializeThemeConstants();
	std::map<std::string, menuTheme> themeNameToThemeSpecMap =
	{
		{"Default", menuTheme("Default")},
	};
	unzipMapToVectors(themeNameToThemeSpecMap, THEME_LIST, THEME_SPEC_LIST);
}
std::string getThemeFileBaseName(themeConstants::themePathIndices fileIndex)
{
	return themeConstants::filenames[fileIndex].substr(themeConstants::prefixLength, std::string::npos);
}
std::string getThemeFileDefaultPrefix(themeConstants::themePathIndices fileIndex)
{
	return themeConstants::filenames[fileIndex].substr(0, themeConstants::prefixLength);
}
std::vector<string> THEME_LIST;
std::vector<menuTheme> THEME_SPEC_LIST{};
std::array<bool, themeConstants::tpi__PATH_COUNT> THEME_FILE_GOT_UNIQUE_PREFIX{};

namespace pscc
{
	namespace psccConstants
	{
		const std::string predefStr = "pd_";
		const std::string menuSuffStr = "_m";
		const std::string ingameSuffStr = "_ig";
		const std::string secSuffStr = "_2";

		const std::string SchemeNameP1 = "P1";
		const std::string SchemeNameP2 = "P2";
		const std::string SchemeNameP3 = "P3";
		const std::string SchemeNameP4 = "P4";
		const std::string SchemeNameRGB = "RGB";

		const std::string ColNameP1_M = predefStr + SchemeNameP1 + menuSuffStr;
		const std::string ColNameP1_M2 = predefStr + SchemeNameP1 + menuSuffStr + secSuffStr;
		const std::string ColNameP1_IG = predefStr + SchemeNameP1 + ingameSuffStr;
		const std::string ColNameP1_IG2 = predefStr + SchemeNameP1 + ingameSuffStr + secSuffStr;
		const std::string ColNameP2_M = predefStr + SchemeNameP2 + menuSuffStr;
		const std::string ColNameP2_M2 = predefStr + SchemeNameP2 + menuSuffStr + secSuffStr;
		const std::string ColNameP2_IG = predefStr + SchemeNameP2 + ingameSuffStr;
		const std::string ColNameP2_IG2 = predefStr + SchemeNameP2 + ingameSuffStr + secSuffStr;
		const std::string ColNameP3_M = predefStr + SchemeNameP3 + menuSuffStr;
		const std::string ColNameP3_M2 = predefStr + SchemeNameP3 + menuSuffStr + secSuffStr;
		const std::string ColNameP3_IG = predefStr + SchemeNameP3 + ingameSuffStr;
		const std::string ColNameP3_IG2 = predefStr + SchemeNameP3 + ingameSuffStr + secSuffStr;
		const std::string ColNameP4_M = predefStr + SchemeNameP4 + menuSuffStr;
		const std::string ColNameP4_M2 = predefStr + SchemeNameP4 + menuSuffStr + secSuffStr;
		const std::string ColNameP4_IG = predefStr + SchemeNameP4 + ingameSuffStr;
		const std::string ColNameP4_IG2 = predefStr + SchemeNameP4 + ingameSuffStr + secSuffStr;
		const std::string ColNameRGB = predefStr + SchemeNameRGB;
	}

	bool color::colorValid() const
	{
		return (hue != FLT_MAX) && (saturation != FLT_MAX) && (luminance != FLT_MAX);
	}

	std::map<std::string, color> colorTable =
	{
		{psccConstants::ColNameP1_M,	{0.015f, 0.95f,  0.48f}},
		{psccConstants::ColNameP2_M,	{3.900f, 0.75f,  0.48f}},
		{psccConstants::ColNameP2_M2,	{3.700f, 0.90f,  0.50f}},
		{psccConstants::ColNameP2_IG2,	{3.450f, 1.00f,  0.40f}},
		{psccConstants::ColNameP3_M,	{0.840f, 1.00f,  0.50f}},
		{psccConstants::ColNameP3_IG,	{0.900f, 0.60f,  0.45f, pscc::color::fb_DISABLE_HUE_MOD}},
		{psccConstants::ColNameP4_M,	{2.135f, 0.86f,  0.32f, pscc::color::fb_DISABLE_HUE_MOD}},
		{psccConstants::ColNameRGB,     {0.000f, 1.00f,  0.50f, pscc::color::fb_DISABLE_HUE_MOD, 0}},
	};
	std::size_t getColorTableSizeInBytes()
	{
		return (colorTable.size() * colorTableEntrySizeInBytes);
	}

	colorScheme::colorScheme(std::string nameIn)
	{
		name = nameIn;
		colors.fill("");
	}
	void colorScheme::downfillEmptySlots()
	{
		if (!colors[colorSchemeColorSlots::cscs_MENU1].empty())
		{
			std::string defaultColor = colors[colorSchemeColorSlots::cscs_MENU1];
			for (std::size_t i = colorSchemeColorSlots::cscs_MENU1 + 1; i < colorSchemeColorSlots::cscs__COUNT; i++)
			{
				if (colors[i].empty())
				{
					colors[i] = defaultColor;
				}
				else
				{
					defaultColor = colors[i];
				}
			}
		}
	}
	bool colorScheme::schemeValid() const
	{
		bool result = 1;

		for (auto i : colors)
		{
			result &= (pscc::colorTable.find(i) != pscc::colorTable.end());
		}

		return result;
	}
	colorSchemeTable::colorSchemeTable()
	{
		entries.resize(schemePredefIDs::spi__COUNT, colorScheme());
		colorScheme* currCol = nullptr;

		currCol = &entries[schemePredefIDs::spi_P1];
		currCol->name = psccConstants::SchemeNameP1;
		currCol->colors[colorSchemeColorSlots::cscs_MENU1] = psccConstants::ColNameP1_M;
		currCol->colors[colorSchemeColorSlots::cscs_MENU2] = psccConstants::ColNameP1_M;
		currCol->colors[colorSchemeColorSlots::cscs_INGAME1] = psccConstants::ColNameP1_M;
		currCol->colors[colorSchemeColorSlots::cscs_INGAME2] = psccConstants::ColNameP1_M;

		currCol = &entries[schemePredefIDs::spi_P2];
		currCol->name = psccConstants::SchemeNameP2;
		currCol->colors[colorSchemeColorSlots::cscs_MENU1] = psccConstants::ColNameP2_M;
		currCol->colors[colorSchemeColorSlots::cscs_MENU2] = psccConstants::ColNameP2_M2;
		currCol->colors[colorSchemeColorSlots::cscs_INGAME1] = psccConstants::ColNameP2_M2;
		currCol->colors[colorSchemeColorSlots::cscs_INGAME2] = psccConstants::ColNameP2_IG2;

		currCol = &entries[schemePredefIDs::spi_P3];
		currCol->name = psccConstants::SchemeNameP3;
		currCol->colors[colorSchemeColorSlots::cscs_MENU1] = psccConstants::ColNameP3_M;
		currCol->colors[colorSchemeColorSlots::cscs_MENU2] = psccConstants::ColNameP3_M;
		currCol->colors[colorSchemeColorSlots::cscs_INGAME1] = psccConstants::ColNameP3_IG;
		currCol->colors[colorSchemeColorSlots::cscs_INGAME2] = psccConstants::ColNameP3_IG;

		currCol = &entries[schemePredefIDs::spi_P4];
		currCol->name = psccConstants::SchemeNameP4;
		currCol->colors[colorSchemeColorSlots::cscs_MENU1] = psccConstants::ColNameP4_M;
		currCol->colors[colorSchemeColorSlots::cscs_MENU2] = psccConstants::ColNameP4_M;
		currCol->colors[colorSchemeColorSlots::cscs_INGAME1] = psccConstants::ColNameP4_M;
		currCol->colors[colorSchemeColorSlots::cscs_INGAME2] = psccConstants::ColNameP4_M;
	}
	std::size_t colorSchemeTable::tableSizeInBytes() const
	{
		return (entries.size() * schemeTableEntrySizeInBytes);
	}
	std::vector<unsigned char> colorSchemeTable::tableToByteVec() const
	{
		std::vector<unsigned char> result(tableSizeInBytes(), 0x00);
		for (std::size_t i = 0, writeIdx = 0; i < entries.size(); i++)
		{
			for (auto u : entries[i].colors)
			{
				result[writeIdx++] = std::distance(colorTable.begin(), colorTable.find(u));
			}
		}
		return result;
	}
	std::size_t getColorTableOffsetToColor(std::string colorName)
	{
		std::size_t result = SIZE_MAX;

		auto findRes = colorTable.find(colorName);
		if (findRes != colorTable.end())
		{
			result = std::distance(colorTable.begin(), findRes) * colorTableEntrySizeInBytes;
		}

		return result;
	}

	colorSchemeTable schemeTable;
}


#if PROJECT_PLUS_EX_BUILD
const std::string menuConfigXMLFileName = "EX_Config.xml";
#else
const std::string menuConfigXMLFileName = "Config.xml";
#endif
const std::string netMenuConfigXMLFileName = "Net-" + menuConfigXMLFileName;
const std::string addonInputFolderPath = "./Addons/";
const std::string addonInputSourceFilename = "Source.asm";
const std::string addonInputConfigFilename = "Definition.xml";
const std::string addonINDEXFileFilename = "idx.dat";
const std::string addonAliasBankFilename = "AddonAliases.asm";
const std::string addonOutputFolderName = "CM_Addons/";
const std::string outputFolder = "./Code_Menu_Output/";
const std::string symbolMapInputFileName = "symbols.map";
const std::string buildFolder = ".././";
const std::string GCTRMExePath = buildFolder + "GCTRealMate.exe";
const std::string GCTRMCommandBase = "\"" + GCTRMExePath + "\" -g -l -q ";

// !!Important Note on cmnuFileName and cmnuBuildLocationDirectory!!
// These variables are also referenced in "Control Codes.cpp"'s "LoadCodeMenu" function,
// in which they're directly used to determine where the game will look for the Code Menu.
// For that reason, please make sure you properly define those variables, as failing
// to do so will cause general weirdness (eg. invisible shields, skipping results screen, etc). 
#if BUILD_TYPE == PROJECT_PLUS
// Constant Confiuguration Block for Project+ Based Builds
	#if BUILD_NETPLAY_FILES == true
	const std::string changelogFileName = "Net-Code_Menu_Changelog.txt";
	const std::string optionsFilename = "Net-Code_Menu_Options.xml";
	const std::string mainGCTName = "NETPLAY";
	const std::string boostGCTName = "NETBOOST";
	const std::string asmFileName = "Net-CodeMenu.asm";
	const std::string asmTextFileName = "Net-CodeMenu.txt";
	const std::string cmnuFileName = "dnet.cmnu";
	const std::vector<std::string> asmBuildLocationDirectories = { "Source/Netplay/" };
	const std::string cmnuBuildLocationDirectory = "pf/menu3/";
	#elif BUILD_NETPLAY_FILES == false
	const std::string changelogFileName = "Code_Menu_Changelog.txt";
	const std::string optionsFilename = "Code_Menu_Options.xml";
	const std::string mainGCTName = "RSBE01";
	const std::string boostGCTName = "BOOST";
	const std::string asmFileName = "CodeMenu.asm";
	const std::string asmTextFileName = "CodeMenu.txt";
	const std::string cmnuFileName = "data.cmnu";
	const std::vector<std::string> asmBuildLocationDirectories = { "Source/CodeMenu/", "Source/Project+/" };
	const std::string cmnuBuildLocationDirectory = "pf/menu3/";
	#endif
#else
// Default Constant Confiuguration Block (used currently by PMEX and LegacyXP)
// Note: These builds don't use the more modern Source Folder based config, just RSBE01.gct
//		As a result, the following constants are left blank on purpose, as they aren't used:
//		- boostGCTName
//		- asmFileName
//		- asmTextFileName
const std::string changelogFileName = "Code_Menu_Changelog.txt";
const std::string optionsFilename = "Code_Menu_Options.xml";
const std::string mainGCTName = "RSBE01";
const std::string boostGCTName = "";
const std::string asmFileName = "";
const std::string asmTextFileName = "";
const std::string cmnuFileName = "cm.bin";
const std::vector<std::string> asmBuildLocationDirectories = {};
const std::string cmnuBuildLocationDirectory = "./";
#endif

const std::string mainGCTFile = buildFolder + mainGCTName + ".GCT";
const std::string mainGCTTextFile = buildFolder + mainGCTName + ".txt";
const std::string boostGCTFile = buildFolder + boostGCTName + ".GCT";
const std::string boostGCTTextFile = buildFolder + boostGCTName + ".txt";
const std::string asmOutputFilePath = outputFolder + asmFileName;
const std::string asmTextOutputFilePath = outputFolder + asmTextFileName;
const std::string cmnuOutputFilePath = outputFolder + cmnuFileName;
const std::string cmnuOptionsOutputFilePath = outputFolder + optionsFilename;
const std::string cmnuBuildLocationFilePath = buildFolder + cmnuBuildLocationDirectory + cmnuFileName;
const std::string addonsOutputFolderPath = outputFolder + addonOutputFolderName;
const std::string addonsBuildLocationFolderPath = buildFolder + "Source/" + addonOutputFolderName;
std::string getCMNUAbsolutePath()
{
	return MAIN_FOLDER + "/" + cmnuBuildLocationDirectory + cmnuFileName;
}

void initMenuFileStream()
{
	MenuFile.open(cmnuOutputFilePath, fstream::out | fstream::binary);
}
__logOutputStruct::__logOutputStruct()
{
	setStandardOutputStream(lava::outputSplitter::sOS_COUT);
	pushStream(lava::outputEntry(std::make_shared<std::ofstream>(outputFolder + changelogFileName), ULONG_MAX), changelogID);
}
std::ostream* __logOutputStruct::getChangelogPtr()
{
	return this->getOutputEntry(changelogID)->targetStream.get();
}
__logOutputStruct ChangelogOutput{};

std::vector<std::string_view> splitLineContentString(const std::string& joinedStringIn)
{
	std::vector<std::string_view> result{};

	std::size_t currEndIndex = 0;
	while (currEndIndex < joinedStringIn.size())
	{
		result.push_back(std::string_view(&joinedStringIn[currEndIndex]));
		currEndIndex += result.back().size() + 1;
	}

	return result;
}
std::string getLineNameFromLineText(const std::string& lineText)
{
	std::string result("");

	if (!lineText.empty())
	{
		std::string_view baseString = splitLineContentString(lineText)[0];
		result = baseString.substr(0, baseString.find(":"));
	}
	
	return result;
}

std::map<lava::shortNameType, Page*> menuPagesMap{};
bool pageShortnameIsFree(lava::shortNameType nameIn)
{
	return menuPagesMap.find(nameIn) == menuPagesMap.end();
}

// === Beginning of Line and Page Type Definitions ===

// Line Type Class Member Definitions
Line::Line() {}
Line::Line(string Text, u16 TextOffset, u8 type, u8 flags, u8 ColorOffset, int* Index) {
	this->Text = Text + "\0"s;
	this->type = type;
	this->Flags = flags;
	this->Color = ColorOffset;
	this->TextOffset = TextOffset;
	this->Index = Index;
	Size = Text.size() + TextOffset + 1;

	Padding = (4 - Size % 4) % 4;
	Size += Padding;

	this->LineName = getLineNameFromLineText(this->Text);
}
void Line::WriteLineData()
{
	WriteLineData({});
}
void Line::WriteLineData(vector<u8> SelectionOffsets)
{
	if (behaviorFlags[Line::lbf_REMOVED]) return; // If the line is explicitly marked as removed, skip it!

	Flags &= ~Line::LINE_FLAG_VALUE_LOCKED;
	if (behaviorFlags[Line::lbf_LOCKED])
	{
		Flags |= Line::LINE_FLAG_VALUE_LOCKED;
	}
	Flags &= ~Line::LINE_FLAG_HIDE_FROM_USER;
	if (behaviorFlags[Line::lbf_HIDDEN])
	{
		Flags |= Line::LINE_FLAG_HIDE_FROM_USER;
	}
	Flags &= ~Line::LINE_FLAG_IGNORE_INDIRECT_RESET;
	if (behaviorFlags[Line::lbf_STICKY])
	{
		Flags |= Line::LINE_FLAG_IGNORE_INDIRECT_RESET;
	}

	vector<u8> output;
	AddValueToByteArray(Size, output);
	if (Size == 0) {
		std::cout << Text << endl;
	}
	AddValueToByteArray(type, output);
	AddValueToByteArray(Flags, output);
	AddValueToByteArray(Color, output);
	AddValueToByteArray(TextOffset, output);
	AddValueToByteArray(lineNum, output);
	//AddValueToByteArray((u8) 0, output);
	AddValueToByteArray(Value, output);
	if (type == PRINT_LINE) {
		AddValueToByteArray(numArgs, output);
	}
	else if (type != COMMENT_LINE) {
		AddValueToByteArray(UpOffset, output);
		AddValueToByteArray(DownOffset, output);
		if (type == SUB_MENU_LINE) {
			AddValueToByteArray(SubMenuOffset, output);
		}
		else {
			AddValueToByteArray(Default, output);
			AddValueToByteArray(Max, output);
			if (type == INTEGER_LINE || type == FLOATING_LINE) {
				AddValueToByteArray(Min, output);
				AddValueToByteArray(Speed, output);
			}
		}
	}
	copy(output.begin(), output.end(), ostreambuf_iterator<char>(MenuFile));
	if (type == SELECTION_LINE)
	{
		Selection* selectionCastPtr = (Selection*)this;
		if (selectionCastPtr->SourceSelectionPtr != nullptr)
		{
			Selection* sourceSelection = selectionCastPtr->SourceSelectionPtr;
			while (sourceSelection->SourceSelectionPtr != nullptr)
			{
				sourceSelection = sourceSelection->SourceSelectionPtr;
			}
			lava::writeRawDataToStream<int>(MenuFile, *sourceSelection->Index);
		}
		else
		{
			lava::writeRawDataToStream<int>(MenuFile, *Index);
		}

		std::copy(SelectionOffsets.begin(), SelectionOffsets.end(), ostreambuf_iterator<char>(MenuFile));
	}
	MenuFile << Text;
	WritePadding();
}
void Line::WritePadding() {
	for (int i = 0; i < Padding; i++) {
		MenuFile << '\0';
	}
}

// Comment Type Class Member Definitions
Comment::Comment(string Text, int* Index)
	: Line(Text, COMMENT_LINE_TEXT_START, COMMENT_LINE, 0, COMMENT_LINE_COLOR_OFFSET, Index) {}
void Comment::WriteLineData()
{
	Line::WriteLineData();
}

// Print Type Class Member Definitions
Print::Print(string Text, vector<int*> args)
	: Line(Text, PRINT_LINE_TEXT_START, PRINT_LINE, 0, COMMENT_LINE_COLOR_OFFSET) {
	this->args = args;
	this->numArgs = args.size();
	Size += args.size() * 4;
	for (auto x : args) {
		argValues.push_back(*x);
	}
	//cout << Size << endl;
}
void Print::WriteLineData()
{
	Line::WriteLineData();
	for (auto x : argValues) {
		sprintf(OpHexBuffer, "%08X", x);
		//cout << Text << ": " << OpHexBuffer << endl;
		x = _byteswap_ulong(x);

		MenuFile.write((const char*)&x, 4);
		//sprintf(OpHexBuffer, "%08X", x);
		//cout << Text << ": " << OpHexBuffer << endl;
		//MenuFile << OpHexBuffer;
	}
}

// Selection Type Class Member Definitions
Selection::Selection(string Text, vector<string> Options, vector<u16> Values, int Default, int& Index)
	: Line(CreateSelectionString(Text + ":  %s", Options), SELECTION_LINE_OFFSETS_START + Options.size() * 4, SELECTION_LINE, 0, NORMAL_LINE_COLOR_OFFSET, &Index)
{
	if (Options.size() != Values.size()) {
		cout << "Mismatched values" << endl;
		exit(-1);
	}
	u16 offset = Text.size() + 5 + 1 + SELECTION_LINE_OFFSETS_START + Options.size() * 4;
	for (int i = 0; i < Options.size(); i++) {
		AddValueToByteArray(offset, OptionOffsets);
		AddValueToByteArray(Values[i], OptionOffsets);
		offset += Options[i].size() + 1;
	}
	Value = Default;
	this->Default = Default;
	this->Max = Options.size() - 1;
}
Selection::Selection(string Text, vector<string> Options, int Default, int& Index)
	: Selection(Text, Options, CreateVector(Options), Default, Index) {}
Selection::Selection(string Text, vector<string> Options, vector<u16> Values, string Default, int& Index)
	: Selection(Text, Options, Values, distance(Options.begin(), find(Options.begin(), Options.end(), Default)), Index) {}
Selection::Selection(string Text, vector<string> Options, string Default, int& Index)
	: Selection(Text, Options, distance(Options.begin(), find(Options.begin(), Options.end(), Default)), Index) {}
string Selection::CreateSelectionString(string Text, vector<string> Options)
{
	for (string x : Options) {
		Text += "\0"s + x;
	}
	return Text;
}
vector<u16> Selection::CreateVector(vector<string> x)
{
	vector<u16> Values;
	for (u16 i = 0; i < x.size(); i++) {
		Values.push_back(i);
	}
	return Values;
}
void Selection::WriteLineData()
{
	Line::WriteLineData(OptionOffsets);
}
std::vector<std::string_view> Selection::getOptionStringViews()
{
	std::vector<std::string_view> result{};

	Selection* sourceSelection = this;
	while (sourceSelection->SourceSelectionPtr != nullptr)
	{
		sourceSelection = sourceSelection->SourceSelectionPtr;
	}

	result = splitLineContentString(sourceSelection->Text);
	result.erase(result.begin());

	return result;
}

// SelectionMirror Type Class Member Definitions
SelectionMirror::SelectionMirror(Selection& SourceSelection, std::string Text, int Default, int& Index, bool inheritFlags)
	: Selection(Text, {}, {}, Default, Index)
{
	this->Min = SourceSelection.Min;
	this->Max = SourceSelection.Max;
	this->SourceSelectionPtr = &SourceSelection;
	if (inheritFlags)
	{
		this->behaviorFlags = SourceSelection.behaviorFlags;
	}
}

// Toggle Type Class Member Definitions
Toggle* Toggle::firstToggleInstancePtr = nullptr;
Toggle::Toggle(string Text, bool Default, int& Index)
	: Selection(Text, 
		((firstToggleInstancePtr == nullptr) ? std::vector<std::string>({"OFF", "ON"}) : std::vector<std::string>()),
		Default, Index)
{
	this->Min = 0;
	this->Max = 1;
	this->isToggleLine = 1;
	if (firstToggleInstancePtr == nullptr)
	{
		firstToggleInstancePtr = this;
	}
	else
	{
		this->SourceSelectionPtr = firstToggleInstancePtr;
	}
}

// SubMenu Type Class Member Definitions
SubMenu::SubMenu() {}
SubMenu::SubMenu(string Text, Page* SubMenuPtr)
	: Line(Text + " >", SUB_MENU_LINE_TEXT_START, SUB_MENU_LINE, 0, NORMAL_LINE_COLOR_OFFSET)
{
	this->SubMenuPtr = SubMenuPtr;
}

// Integer Type Class Member Definitions
Integer::Integer(string Text, int Min, int Max, int Default, int Speed, int& Index, std::string format, u8 flags)
	: Line(Text + ":  " + format, NUMBER_LINE_TEXT_START, INTEGER_LINE, flags, NORMAL_LINE_COLOR_OFFSET, &Index)
{
	this->Min = Min;
	this->Max = Max;
	Value = Default;
	this->Default = Default;
	this->Speed = Speed;
}

// Floating Type Class Member Definitions
Floating::Floating(string Text, float Min, float Max, float Default, float Speed, int& Index, string format)
	: Line(Text + ":  " + format, NUMBER_LINE_TEXT_START, FLOATING_LINE, 0, NORMAL_LINE_COLOR_OFFSET, &Index)
{
	this->Min = GetHexFromFloat(Min);
	this->Max = GetHexFromFloat(Max);
	Value = GetHexFromFloat(Default);
	this->Default = GetHexFromFloat(Default);
	this->Speed = GetHexFromFloat(Speed);
}

// Page Class Member Definitions
Page::Page(string Name, vector<Line*> Lines, lava::shortNameType shortName) {
	if (!shortName.empty())
	{
		auto pageFindRes = menuPagesMap.find(shortName);
		if (pageFindRes == menuPagesMap.end())
		{
			menuPagesMap[shortName] = this;
		}
		else
		{
			std::cerr << "[ERROR] Shortname of page \"" << Name << "\" (" << shortName << ")" <<
				" is already in use by Page \"" << pageFindRes->second->PageName << "\"!\n";
			exit(1);
		}
	}

	CalledFromLine = std::make_shared<SubMenu>(Name, this);
	CalledFromLine->Index = &CalledFromLineIndex;
	PageName = Name;
	PrepareLines(Lines);
}
void Page::PrepareLines()
{
	PrepareLines(this->Lines);
}
void Page::PrepareLines(const std::vector<Line*> LinesIn)
{
	// Reset page size, will be re-tallied in the following loop.
	Size = NUM_WORD_ELEMS * 4;
	this->Lines = LinesIn;
	std::size_t excludedLines = 0;
	// Do some final line attribute assignment stuff...
	for (std::size_t i = 0; i < this->Lines.size(); i++)
	{
		this->Lines[i]->ParentPageName = PageName;
		// If the line is explicitly marked as removed...
		if (this->Lines[i]->behaviorFlags[Line::lbf_REMOVED])
		{
			// ... increment the counter...
			excludedLines++;
			// ... and skip it!
			continue;
		}
		// Subtract the number of excluded lines from i, to ensure excluded lines aren't counted!
		this->Lines[i]->lineNum = i - excludedLines;
		this->Lines[i]->PageOffset = Size;
		Size += this->Lines[i]->Size;
	}
	// ... and connect the lines accordingly!
	ConnectSelectableLines();
}
void Page::WritePage()
{
	vector<u8> output;
	AddValueToByteArray(CurrentLineOffset, output);
	AddValueToByteArray(PrevPageOffset, output);
	AddValueToByteArray(NumChangedLines, output);
	AddValueToByteArray(PrintLowHold, output);
	if (CalledFromLine != nullptr)
	{
		AddValueToByteArray(*CalledFromLine->Index, output);
	}
	else
	{
		AddValueToByteArray(0xFFFFFFFF, output);
	}
	copy(output.begin(), output.end(), ostreambuf_iterator<char>(MenuFile));
	for (auto x : Lines) {
		x->WriteLineData();
	}
}
void Page::ConnectSelectableLines()
{
	vector<int> SelectableLines{};
	GetSelectableLines(SelectableLines);
	if (SelectableLines.size() > 0)
	{
		SelectableLines.insert(SelectableLines.begin(), SelectableLines.back());
		SelectableLines.push_back(SelectableLines[1]);

		for (int i = 1; i < SelectableLines.size() - 1; i++)
		{
			Lines[SelectableLines[i]]->UpOffset = Lines[SelectableLines[i - 1]]->PageOffset;
			Lines[SelectableLines[i]]->DownOffset = Lines[SelectableLines[i + 1]]->PageOffset;
		}

		CurrentLineOffset = Lines[SelectableLines[1]]->PageOffset;
		Lines[SelectableLines[1]]->Color = HIGHLIGHTED_LINE_COLOR_OFFSET;
	}
	else
	{
		CurrentLineOffset = NUM_WORD_ELEMS * 4;
	}
}
void Page::GetSelectableLines(vector<int>& SelectableLines)
{
	for (int i = 0; i < Lines.size(); i++)
	{
		Line* currLine = Lines[i];
		if (currLine->type != COMMENT_LINE && currLine->type != PRINT_LINE)
		{
			if (!currLine->behaviorFlags[Line::lbf_REMOVED])
			{
				SelectableLines.push_back(i);
			}
		}
	}
}

// === End of Line and Page Type Definitions ===


void CodeMenu()
{
#if EON_DEBUG_BUILD
	//testing page
	vector<Line*> TestLines;
	//P2Lines.push_back(new Selection("P2 Identity Crisis", CHARACTER_LIST, CHARACTER_ID_LIST, 0, CHARACTER_SELECT_P2_INDEX));
	cout << "Debug Toggles:\n";
	int toggleLocations[16];
	for(int i = 0; i < 16; i++)
	{
		TestLines.push_back(new Integer(to_string(i), -10000, 10000, 0, 1, toggleLocations[i]));
	}
	Page TestPage("Testing flags", TestLines);
#endif
	
	//player pages
	vector<Line*> P1Lines;
	P1Lines.push_back(new Toggle("Infinite Shield", false, INFINITE_SHIELDS_P1_INDEX));
	Selection* P1CharSelect = new Selection("P1 Character Select", CHARACTER_LIST, CHARACTER_ID_LIST, 0, CHARACTER_SELECT_P1_INDEX);
	if (!CHARACTER_LIST.empty())
	{
		P1Lines.push_back(P1CharSelect);
	}
	P1Lines.push_back(new Floating("Select Percent", 0, 999, 0, 1, PERCENT_SELECT_VALUE_P1_INDEX, "%.0f%%"));
	P1Lines.push_back(new Toggle("Press DPad to select percent", false, PERCENT_SELECT_ACTIVATOR_P1_INDEX));
	P1Lines.push_back(new Toggle("Disable DPad", false, DISABLE_DPAD_P1_INDEX));
	Selection* P1InputBuffer = new Selection("Input Buffer", { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" }, 0, BUFFER_P1_INDEX);
	P1InputBuffer->behaviorFlags[Line::lbf_HIDDEN].value = !PROJECT_PLUS_EX_BUILD;
	Selection* P1ALC = new Selection("Automatic L-Cancelling", { "OFF", "ON", "Modified" }, 0, ALC_P1_INDEX);
	P1ALC->behaviorFlags[Line::lbf_HIDDEN].value = !PROJECT_PLUS_EX_BUILD;
	P1Lines.push_back(P1InputBuffer);
	P1Lines.push_back(P1ALC);
	P1Lines.push_back(new Floating("ALC Modifier", 0.099, 3, 0.5, 0.05, EXTERNAL_INDEX, "%.2fX"));
	P1Lines.back()->behaviorFlags[Line::lbf_HIDDEN].value = !PROJECT_PLUS_EX_BUILD;
	P1Lines.push_back(new Toggle("Red Flash on L-Cancel Failure", false, ALC_P1_FLASH_RED_INDEX));
	P1Lines.back()->behaviorFlags[Line::lbf_HIDDEN].value = !PROJECT_PLUS_EX_BUILD;
	if (xml::CONFIG_DISPLAY_TAG_HEX_ENABLED)
	{
		P1Lines.push_back(new Comment(""));
		P1Lines.push_back(new Print("Tag Hex: %s", { &P1_TAG_STRING_INDEX }));
		P1Lines.push_back(new Comment("For Use With Tag-Based Costumes"));
	}
	Page P1("Player 1 Codes", P1Lines, lava::shortNameType("_PLAYER1"));

	vector<Line*> P2Lines;
	P2Lines.push_back(new Toggle("Infinite Shield", false, INFINITE_SHIELDS_P2_INDEX));
	if (!CHARACTER_LIST.empty())
	{
		P2Lines.push_back(new SelectionMirror(*P1CharSelect, "P2 Character Select", 0, CHARACTER_SELECT_P2_INDEX));
	}
	P2Lines.push_back(new Floating("Select Percent", 0, 999, 0, 1, PERCENT_SELECT_VALUE_P2_INDEX, "%.0f%%"));
	P2Lines.push_back(new Toggle("Press DPad to select percent", false, PERCENT_SELECT_ACTIVATOR_P2_INDEX));
	P2Lines.push_back(new Toggle("Disable DPad", false, DISABLE_DPAD_P2_INDEX));
	P2Lines.push_back(new SelectionMirror(*P1InputBuffer, "Input Buffer", 0, BUFFER_P2_INDEX));
	P2Lines.push_back(new SelectionMirror(*P1ALC, "Automatic L-Cancelling", 0, ALC_P2_INDEX));
	P2Lines.push_back(new Floating("ALC Modifier", 0.099, 3, 0.5, 0.05, EXTERNAL_INDEX, "%.2fX"));
	P2Lines.back()->behaviorFlags[Line::lbf_HIDDEN].value = !PROJECT_PLUS_EX_BUILD;
	P2Lines.push_back(new Toggle("Red Flash on L-Cancel Failure", false, ALC_P2_FLASH_RED_INDEX));
	P2Lines.back()->behaviorFlags[Line::lbf_HIDDEN].value = !PROJECT_PLUS_EX_BUILD;
	if (xml::CONFIG_DISPLAY_TAG_HEX_ENABLED)
	{
		P1Lines.push_back(new Comment(""));
		P1Lines.push_back(new Print("Tag Hex: %s", { &P2_TAG_STRING_INDEX }));
		P1Lines.push_back(new Comment("For Use With Tag-Based Costumes"));
	}
	Page P2("Player 2 Codes", P2Lines, lava::shortNameType("_PLAYER2"));

	vector<Line*> P3Lines;
	P3Lines.push_back(new Toggle("Infinite Shield", false, INFINITE_SHIELDS_P3_INDEX));
	if (!CHARACTER_LIST.empty())
	{
		P3Lines.push_back(new SelectionMirror(*P1CharSelect, "P3 Character Select", 0, CHARACTER_SELECT_P3_INDEX));
	}
	P3Lines.push_back(new Floating("Select Percent", 0, 999, 0, 1, PERCENT_SELECT_VALUE_P3_INDEX, "%.0f%%"));
	P3Lines.push_back(new Toggle("Press DPad to select percent", false, PERCENT_SELECT_ACTIVATOR_P3_INDEX));
	P3Lines.push_back(new Toggle("Disable DPad", false, DISABLE_DPAD_P3_INDEX));
	P3Lines.push_back(new SelectionMirror(*P1InputBuffer, "Input Buffer", 0, BUFFER_P3_INDEX));
	P3Lines.push_back(new SelectionMirror(*P1ALC, "Automatic L-Cancelling", 0, ALC_P3_INDEX));
	P3Lines.push_back(new Floating("ALC Modifier", 0.099, 3, 0.5, 0.05, EXTERNAL_INDEX, "%.2fX"));
	P3Lines.back()->behaviorFlags[Line::lbf_HIDDEN].value = !PROJECT_PLUS_EX_BUILD;
	P3Lines.push_back(new Toggle("Red Flash on L-Cancel Failure", false, ALC_P3_FLASH_RED_INDEX));
	P3Lines.back()->behaviorFlags[Line::lbf_HIDDEN].value = !PROJECT_PLUS_EX_BUILD;
	if (xml::CONFIG_DISPLAY_TAG_HEX_ENABLED)
	{
		P1Lines.push_back(new Comment(""));
		P1Lines.push_back(new Print("Tag Hex: %s", { &P3_TAG_STRING_INDEX }));
		P1Lines.push_back(new Comment("For Use With Tag-Based Costumes"));
	}
	Page P3("Player 3 Codes", P3Lines, lava::shortNameType("_PLAYER3"));

	vector<Line*> P4Lines;
	P4Lines.push_back(new Toggle("Infinite Shield", false, INFINITE_SHIELDS_P4_INDEX));
	if (!CHARACTER_LIST.empty())
	{
		P4Lines.push_back(new SelectionMirror(*P1CharSelect, "P4 Character Select", 0, CHARACTER_SELECT_P4_INDEX));
	}
	P4Lines.push_back(new Floating("Select Percent", 0, 999, 0, 1, PERCENT_SELECT_VALUE_P4_INDEX, "%.0f%%"));
	P4Lines.push_back(new Toggle("Press DPad to select percent", false, PERCENT_SELECT_ACTIVATOR_P4_INDEX));
	P4Lines.push_back(new Toggle("Disable DPad", false, DISABLE_DPAD_P4_INDEX));
	P4Lines.push_back(new SelectionMirror(*P1InputBuffer, "Input Buffer", 0, BUFFER_P4_INDEX));
	P4Lines.push_back(new SelectionMirror(*P1ALC, "Automatic L-Cancelling", 0, ALC_P4_INDEX));
	P4Lines.push_back(new Floating("ALC Modifier", 0.099, 3, 0.5, 0.05, EXTERNAL_INDEX, "%.2fX"));
	P4Lines.back()->behaviorFlags[Line::lbf_HIDDEN].value = !PROJECT_PLUS_EX_BUILD;
	P4Lines.push_back(new Toggle("Red Flash on L-Cancel Failure", false, ALC_P4_FLASH_RED_INDEX));
	P4Lines.back()->behaviorFlags[Line::lbf_HIDDEN].value = !PROJECT_PLUS_EX_BUILD;
	if (xml::CONFIG_DISPLAY_TAG_HEX_ENABLED)
	{
		P1Lines.push_back(new Comment(""));
		P1Lines.push_back(new Print("Tag Hex: %s", { &P4_TAG_STRING_INDEX }));
		P1Lines.push_back(new Comment("For Use With Tag-Based Costumes"));
	}
	Page P4("Player 4 Codes", P4Lines, lava::shortNameType("_PLAYER4"));

	//debug mode
	vector<Line*> DebugLines;
	DebugLines.push_back(new Comment("Debug Mode Commands:"));
	DebugLines.push_back(new Comment("Start = Toggle Frame Advance"));
	DebugLines.push_back(new Comment("Z = Frame Advance | Hold Z = Slow Motion"));
	DebugLines.push_back(new Comment(""));
	DebugLines.push_back(new Toggle("Debug Mode", false, DEBUG_MODE_INDEX));
	DebugLines.push_back(new Selection("Hitbox Display", { "OFF", "ON", "Models Off" }, 0, DISPLAY_HITBOXES_INDEX));
	DebugLines.push_back(new Toggle("Collision Display", false, DISPLAY_COLLISION_INDEX));
	DebugLines.push_back(new Selection("Stage Collisions", { "OFF", "ON", "Background Off" }, 0, DISPLAY_LEDGEGRAB_INDEX));
	DebugLines.push_back(new Toggle("Camera Lock", false, CAMERA_LOCK_INDEX));
	DebugLines.push_back(new Toggle("Draw DI", false, DI_DRAW_INDEX));
	DebugLines.push_back(new Toggle("FPS Display", false, FPS_DISPLAY_INDEX));
	DebugLines.push_back(new Toggle("HUD", true, HUD_DISPLAY_INDEX));
	Page DebugMode("Debug Mode Settings", DebugLines, lava::shortNameType("_DEBUG"));

	//value setting
	vector<Line*> ConstantsLines;
	ConstantsLines.push_back(new Comment("Set attributes to new values"));
	ConstantsLines.push_back(new Comment(""));
	ConstantsLines.push_back(new Floating("Hitstun Multiplier", 0, 999, 0.4, .01, HITSTUN_MULTIPLIER_INDEX, "%.3f"));
	constantOverrides.emplace_back(0x80B87AA8, HITSTUN_MULTIPLIER_INDEX);
	ConstantsLines.push_back(new Floating("Hitlag Multiplier", 0, 999, 1. / 3., .02, HITLAG_MULTIPLIER_INDEX, "%.3f"));
	constantOverrides.emplace_back(0x80B87AEC, HITLAG_MULTIPLIER_INDEX);
	ConstantsLines.push_back(new Floating("Hitlag Maximum", 0, 999, 30, 1, HITLAG_MAXIMUM_INDEX, "%.3f"));
	constantOverrides.emplace_back(0x80B87AE8, HITLAG_MAXIMUM_INDEX);
	ConstantsLines.push_back(new Floating("Electric Hitlag Multiplier", 0, 999, 1.5, .1, ELECTRIC_HITLAG_MULTIPLIER_INDEX, "%.3f"));
	constantOverrides.emplace_back(0x80B87B10, ELECTRIC_HITLAG_MULTIPLIER_INDEX);
	ConstantsLines.push_back(new Floating("SDI Distance", -999, 999, 6, .5, SDI_DISTANCE_INDEX, "%.3f"));
	constantOverrides.emplace_back(0x80B88354, SDI_DISTANCE_INDEX);
	ConstantsLines.push_back(new Floating("ASDI Distance", -999, 999, 3, .5, ASDI_DISTANCE_INDEX, "%.3f"));
	constantOverrides.emplace_back(0x80B88358, ASDI_DISTANCE_INDEX);
	ConstantsLines.push_back(new Floating("Walljump Horizontal Multiplier", -999, 999, 0.9, .05, WALLJUMP_HORIZONTAL_MULTIPLIER_INDEX, "%.3f"));
	constantOverrides.emplace_back(0x80B88420, WALLJUMP_HORIZONTAL_MULTIPLIER_INDEX);
	ConstantsLines.push_back(new Floating("Minimum Shield Size Scale", -999, 999, 0.15, .02, MINIMUM_SHIELD_SIZE_SCALING_INDEX, "%.3f"));
	constantOverrides.emplace_back(0x80B88444, MINIMUM_SHIELD_SIZE_SCALING_INDEX);
	ConstantsLines.push_back(new Floating("Shield Damage Multiplier", -999, 999, 1, .02, SHIELD_DAMAGE_MULTIPLIER_INDEX, "%.3f"));
	constantOverrides.emplace_back(0x80B8845C, SHIELD_DAMAGE_MULTIPLIER_INDEX);
	ConstantsLines.push_back(new Floating("Base Shield Damage", -999, 999, 0, 1, SHIELD_BASE_DAMAGE_INDEX, "%.3f"));
	constantOverrides.emplace_back(0x80B88460, SHIELD_BASE_DAMAGE_INDEX);
	ConstantsLines.push_back(new Floating("Shield Size Multiplier", -999, 999, 1, .05, SHIELD_SIZE_MULTIPLIER_INDEX, "%.3f"));
	constantOverrides.emplace_back(0x80B88478, SHIELD_SIZE_MULTIPLIER_INDEX);
	ConstantsLines.push_back(new Floating("Shield Tilt Multiplier", -999, 999, 0.5, .05, SHIELD_TILT_MULTIPLIER_INDEX, "%.3f"));
	constantOverrides.emplace_back(0x80B88484, SHIELD_TILT_MULTIPLIER_INDEX);
	//ValueLines.push_back(new Floating("Attacker Shield Pushback Friction Multiplier", -999, 999, 1.1, .05, SDI_DISTANCE_INDEX, "%.3f"));
	ConstantsLines.push_back(new Floating("Wall Bounce Knockback Multiplier", -999, 999, 0.80, .02, WALL_BOUNCE_KNOCKBACK_MULTIPLIER_INDEX, "%.3f"));
	constantOverrides.emplace_back(0x80B88510, WALL_BOUNCE_KNOCKBACK_MULTIPLIER_INDEX);
	ConstantsLines.push_back(new Floating("Knockback Decay Rate", -999, 999, 0.051, .001, KNOCKBACK_DECAY_MULTIPLIER_INDEX, "%.3f"));
	constantOverrides.emplace_back(0x80B88534, KNOCKBACK_DECAY_MULTIPLIER_INDEX);
	ConstantsLines.push_back(new Selection("Staling Toggle", { "Default", "ON", "OFF" }, 0, STALING_TOGGLE_INDEX));
	if (xml::CONFIG_DASH_ATTACK_ITEM_GRAB_ENABLED)
	{
		ConstantsLines.push_back(new Toggle("Aerial & Dash Attack Item Grab Toggle", 0, DASH_ATTACK_ITEM_GRAB_INDEX));
	}
	//ConstantsLines.push_back(new Selection("Tripping Toggle", { "OFF", "ON" }, 0, TRIP_TOGGLE_INDEX));
	//ConstantsLines.push_back(new Floating("Tripping Rate", 0, 100, 1.0, 1.0, TRIP_RATE_MULTIPLIER_INDEX, "%.2f%"));
	//ConstantsLines.push_back(new Selection("Tripping Cooldown Toggle", { "ON", "OFF" }, 0, TRIP_INTERVAL_INDEX));
	if (xml::CONFIG_JUMPSQUAT_OVERRIDE_ENABLED)
	{
		const int minFrameCount = 1;
		const int maxFrameCount = 3600;
		ConstantsLines.push_back(new Selection("Jumpsquat Modifier Mode", { "Disabled", "Replace", "Add", "Subtract", "Multiply", "Divide", "Distance From Value", "Random Within Range"}, 0, JUMPSQUAT_OVERRIDE_TOGGLE_INDEX));
		ConstantsLines.push_back(new Integer("Jumpsquat Modifier Value", minFrameCount, maxFrameCount, 3, 1, JUMPSQUAT_OVERRIDE_FRAMES_INDEX, "%d", Integer::INT_FLAG_ALLOW_WRAP));
		ConstantsLines.push_back(new Integer("Jumpsquat Modifier Minimum Length", minFrameCount, maxFrameCount, minFrameCount, 1, JUMPSQUAT_OVERRIDE_MIN_INDEX, "%d", Integer::INT_FLAG_ALLOW_WRAP));
		ConstantsLines.push_back(new Integer("Jumpsquat Modifier Maximum Length", minFrameCount, maxFrameCount, maxFrameCount, 1, JUMPSQUAT_OVERRIDE_MAX_INDEX, "%d", Integer::INT_FLAG_ALLOW_WRAP));
	}
	Page ConstantsPage("Gameplay Modifiers", ConstantsLines, lava::shortNameType("_GMPLMOD"));

	//DBZ Mode settings
	vector<Line*> DBZModeLines;
	DBZModeLines.push_back(new Toggle("Flight Mode", false, DBZ_MODE_INDEX));
	DBZModeLines.push_back(new Floating("Max Horizontal Speed", 0, 100, 2, .05, DBZ_MODE_MAX_SPEED_X_INDEX, "%.3f"));
	DBZModeLines.push_back(new Floating("Max Vertical Speed", 0, 100, 2, .05, DBZ_MODE_MAX_SPEED_Y_INDEX, "%.3f"));
	DBZModeLines.push_back(new Comment("Acceleration Scales Based On Stick Magnitude"));
	DBZModeLines.push_back(new Floating("Horizontal Acceleration", -100, 100, 1, .01, DBZ_MODE_ACCEL_X_INDEX, "%.3f"));
	DBZModeLines.push_back(new Floating("Vertical Acceleration", -100, 100, 1, .01, DBZ_MODE_ACCEL_Y_INDEX, "%.3f"));
	Page DBZModePage("Flight Mode Settings", DBZModeLines, lava::shortNameType("_FLIGHT"));
	
	//Special Mode Settings
	vector<Line*> SpecialModeLines;
	SpecialModeLines.push_back(new Comment("Special Modes"));
	SpecialModeLines.push_back(ConstantsPage.CalledFromLine.get());
	SpecialModeLines.push_back(DBZModePage.CalledFromLine.get());
	SpecialModeLines.push_back(new Selection("Random Angle Mode", {"Off", "True Random", "Static Random"}, 0, RANDOM_ANGLE_INDEX));
	SpecialModeLines.push_back(new Toggle("War Mode", false, WAR_MODE_INDEX));
	// War Mode is only visible by default on P+Ex builds based on pre v3.0 P+.
	SpecialModeLines.back()->behaviorFlags[Line::lbf_HIDDEN].value = !(PROJECT_PLUS_EX_BUILD && ENSURE_PRE_PP30_COMPAT);
	SpecialModeLines.push_back(new Selection("Gameplay Speed Modifier", { "Off", "1.25", "1.5x", "2.0x", "1/2x", "3/4x" }, 0, SPEED_INDEX));
	SpecialModeLines.back()->behaviorFlags[Line::lbf_REMOVED].value = !PROJECT_PLUS_EX_BUILD;
	SpecialModeLines.push_back(new Toggle("Scale Mode", false, SCALE_INDEX));
	SpecialModeLines.back()->behaviorFlags[Line::lbf_REMOVED].value = !PROJECT_PLUS_EX_BUILD;
	SpecialModeLines.push_back(new Floating("Scale Modifier", 0.5, 3, 1, 0.05, EXTERNAL_INDEX, "%.2fX"));
	SpecialModeLines.back()->behaviorFlags[Line::lbf_REMOVED].value = !PROJECT_PLUS_EX_BUILD;
	SpecialModeLines.push_back(new Selection("Big Head Mode", { "Off", "On", "Larger", "Largest", "Largerest" }, 0, BIG_HEAD_INDEX));
	Page SpecialModePage("Special Modes", SpecialModeLines, lava::shortNameType("_SPECIAL"));


	

	//main page
	vector<Line*> MainLines;
	// Writes the Menu's Title, appending the netplay suffix only if the config file didn't specify its own title.
	MainLines.push_back(new Comment(MENU_NAME + ((!CUSTOM_NAME_SUPPLIED && BUILD_NETPLAY_FILES) ? " (Netplay)" : "")));
	if (!xml::CONFIG_DELETE_CONTROLS_COMMENTS)
	{
		MainLines.push_back(new Comment("Green = Comments | Blue = Changed"));
		MainLines.push_back(new Comment("A = Enter Submenu | B = Back/Exit"));
		MainLines.push_back(new Comment("X = Reset Selection | Y = Reset Page"));
		MainLines.push_back(new Comment("Hold Z = Scroll Faster"));
		MainLines.push_back(new Comment(""));
	}
	for (std::size_t i = 0; i < xml::CONFIG_INCOMING_COMMENTS.size(); i++)
	{
		MainLines.push_back(new Comment(xml::CONFIG_INCOMING_COMMENTS[i]));
	}
	

#if EON_DEBUG_BUILD
	MainLines.push_back(&TestPage.CalledFromLine);
#endif
	
	MainLines.push_back(DebugMode.CalledFromLine.get());
	//	MainLines.push_back(new Selection("Endless Friendlies", { "OFF", "Same Stage", "Random Stage", "Round Robin" }, 0, INFINITE_FRIENDLIES_INDEX));
	MainLines.push_back(new Selection("Endless Friendlies Mode", { "OFF", "All Stay", "Winner Stays", "Loser Stays", "Rotation"}, 0, ENDLESS_FRIENDLIES_MODE_INDEX));
	MainLines.push_back(new Selection("Endless Friendlies Stage Selection", { "Random", "Same" }, 0, ENDLESS_FRIENDLIES_STAGE_SELECTION_INDEX));
#if TOURNAMENT_ADDITION_BUILD
	MainLines.push_back(new Selection("Random 1-1", { "OFF", "ON" }, 0, RANDOM_1_TO_1_INDEX));
#endif
	MainLines.push_back(new Selection("Alternate Stages", { "Enabled", "Random", "OFF" }, 0, ALT_STAGE_BEHAVIOR_INDEX));
	MainLines.push_back(new Toggle("Autoskip Results Screen", false, AUTO_SKIP_TO_CSS_INDEX));
#if DOLPHIN_BUILD
	MainLines.push_back(new Toggle("Autosave Replays", true, AUTO_SAVE_REPLAY_INDEX));
#else
	MainLines.push_back(new Toggle("Autosave Replays", false, AUTO_SAVE_REPLAY_INDEX));
#endif
	MainLines.push_back(new Toggle("Save Previous Replay", false, SAVE_REPLAY_ANYWHERE_INDEX));
	MainLines.push_back(new Selection("Tag-Based Costumes", { "ON", "ON + Teams", "OFF" }, 0, TAG_COSTUME_TOGGLE_INDEX));
	MainLines.push_back(P1.CalledFromLine.get());
	MainLines.push_back(P2.CalledFromLine.get());
	MainLines.push_back(P3.CalledFromLine.get());
	MainLines.push_back(P4.CalledFromLine.get());
	MainLines.push_back(SpecialModePage.CalledFromLine.get());

	
	// HUD Color Settings
	vector<Line*> HUDColorLines;
	HUDColorLines.push_back(new Comment("Replacement HUD Colors"));
	std::vector<std::string> schemeNames(pscc::schemeTable.entries.size(), "");
	for (std::size_t i = 0; i < pscc::schemeTable.entries.size(); i++)
	{
		schemeNames[i] = pscc::schemeTable.entries[i].name;
	}
	Selection* P1ColorLine = new Selection("Player 1", schemeNames, pscc::schemePredefIDs::spi_P1, PSCC_COLOR_1_INDEX);
	P1ColorLine->behaviorFlags[Line::lbf_STICKY].value = 1;
	HUDColorLines.push_back(P1ColorLine);
	HUDColorLines.push_back(new SelectionMirror(*P1ColorLine, "Player 2", pscc::schemePredefIDs::spi_P2, PSCC_COLOR_2_INDEX));
	HUDColorLines.push_back(new SelectionMirror(*P1ColorLine, "Player 3", pscc::schemePredefIDs::spi_P3, PSCC_COLOR_3_INDEX));
	HUDColorLines.push_back(new SelectionMirror(*P1ColorLine, "Player 4", pscc::schemePredefIDs::spi_P4, PSCC_COLOR_4_INDEX));
	Page HUDColorsPage("HUD Colors", HUDColorLines);
	if (xml::CONFIG_PSCC_ENABLED && (pscc::schemeTable.entries.size() >= 4))
	{
		MainLines.push_back(HUDColorsPage.CalledFromLine.get());
	}


#if BUILD_TYPE == PROJECT_PLUS
	MainLines.push_back(new Toggle("Crowd Cheers", false, CROWD_CHEER_TOGGLE_INDEX));
#endif

	MainLines.push_back(new Selection("Code Menu Activation", { "Default", "PM 3.6", "OFF" }, 0, CODE_MENU_ACTIVATION_SETTING_INDEX));
	if (ROSTER_LIST.size() > 1)
	{
		MainLines.push_back(new Selection("CSS Roster Version", ROSTER_LIST, 0, CSS_VERSION_SETTING_INDEX));
	}

	if (THEME_LIST.size() > 1)
	{
		MainLines.push_back(new Selection("Active Theme", THEME_LIST, 0, THEME_SETTING_INDEX));
	}
	
	Page Main("Main", MainLines, lava::shortNameType("_MAIN"));
	
	//Unclepunch fps code
	CodeRaw("[CM: Code Menu] FPS Code [UnclePunch]", "", {
		3254926684, 3, 2288895028, 946012161, 2557330484, 2283733000, 1610612736, 0, 3254926716, 6, 2288895029, 946012161, 2557330485, 738394172, 1098907672, 2288895028, 2959983670, 945815552, 2557330484, 2557330485, 2147549204, 0
		});

	CreateMenu(Main);

	PrintCodeMenu();

#if ENSURE_PRE_PP30_COMPAT
	PrimeCodeMenu();	// In post P+ v3.0 based builds, this is applied directly to sora_menu_main instead
#endif

	ControlCodeMenu();

	ActualCodes();

	utilitySubroutines();

#if EON_DEBUG_BUILD
	for(auto TOGGLE_LOC: toggleLocations)
	{
		printf("%0X\n", TOGGLE_LOC);
	}
	cout << endl;
#endif
	
	//printf("%X", P1_TAG_STRING_INDEX);

	//printf("%0Xu\n", KnucklesTemp + 8);

	MenuFile.close();
}

void printMenuSetters() {

	//Could probably set the string indexes to the hex buffers during compile, since they never change

	int resultPtrReg = 31;
	int tagPtrReg = 30;
	int hexCharReg = 29;
	int stringReg = 28;
	int tagMenuReg = 27;
	int tagMenuPtrReg = 26;
	int resultHexStartReg = 25;
	int counterReg = 24;

	//set string to convert
	SetRegister(3, "%02X");
	SetRegister(stringReg, STRING_BUFFER + 0x80);
	STW(3, stringReg, 0);
	SetRegister(3, 0);
	STW(3, stringReg, 4);

	SetRegister(resultHexStartReg, P1_TAG_HEX_LOC + 1);

	if (xml::CONFIG_DISPLAY_TAG_HEX_ENABLED)
	{
		SetRegister(tagMenuPtrReg, 0x805882e0 - 4); //this needs wiiztec's 0 to death code

		for (auto tagIndex : { P1_TAG_STRING_INDEX, P2_TAG_STRING_INDEX, P3_TAG_STRING_INDEX, P4_TAG_STRING_INDEX }) {
			if (tagIndex != -1) {
				MR(resultPtrReg, resultHexStartReg);

				//get menu location
				LWZU(tagMenuReg, tagMenuPtrReg, 4);
				If(tagMenuReg, NOT_EQUAL_I, 0); {
					ADDI(tagMenuReg, tagMenuReg, 0x1FC);
					LWZ(3, tagMenuReg, MENU_POS_OFFSET);
					ADDI(3, 3, -1);
					//check if initialized
					If(3, LESS_I_L, 120); {
						//get tag location
						MULLI(3, 3, 2);
						ADDI(3, 3, MENU_INDEX_OFFSET);
						LHZX(3, tagMenuReg, 3);
						If(3, LESS_I_L, 120); {
							MULLI(3, 3, TAG_LIST_SIZE);
							SetRegister(tagPtrReg, TAG_LIST_START_LOC);
							ADD(tagPtrReg, tagPtrReg, 3);

							//convert tag hex to string
							//check if entire half is not 0, then convert byte.  Might be able to just convert half, doesn't really matter
							SetRegister(counterReg, 0);
							LHZ(hexCharReg, tagPtrReg, 0);
							While(hexCharReg, NOT_EQUAL_I, 0); {
								//don't loop too many times
								If(counterReg, LESS_OR_EQUAL_I, 4); {
									LBZ(hexCharReg, tagPtrReg, 0);
									MR(3, resultPtrReg);
									MR(4, stringReg);
									MR(5, hexCharReg);
									WriteIntToFile(0x4cc63182); //clclr 6, 6
									CallBrawlFunc(0x803f89fc); //sprintf

									ADD(resultPtrReg, resultPtrReg, 3);
									LHZU(hexCharReg, tagPtrReg, 1);
								} Else(); {
									//exit
									SetRegister(hexCharReg, 0);
								} EndIf();
							} EndWhile();
						} EndIf();
					} EndIf();
				} EndIf();

				//null terminator
				SetRegister(3, 0);
				STB(3, resultPtrReg, 0);

				SetRegister(3, tagIndex);
				ADDI(4, resultHexStartReg, -1); //move back one for $
				STW(4, 3, 0);

				//next sting buffer
				ADDI(resultHexStartReg, resultHexStartReg, P2_TAG_HEX_LOC - P1_TAG_HEX_LOC);
			}
		}
	}
}

void stopAnouncer() {
	ASMStart(0x809580b4, "[CM: Code Menu] Stop Announcer");
	//SaveRegisters();
	
	int reg1 = 4;

	LoadWordToReg(reg1, ENDLESS_FRIENDLIES_MODE_INDEX + Line::VALUE);
	If(reg1, GREATER_OR_EQUAL_I, 2); {
		BLR();
	} EndIf();

	//RestoreRegisters();
	ASMEnd(0x9421ffe0); //stwu sp, -0x20 (sp)
}

void endlessFriendlies() {
	stopAnouncer();

	//r3 + 0x5D is flag
	//r3 + 0x28 ^ 0x20 is port num (0 based)
	ASMStart(0x809489ec, "[CM: Code Menu] Endless Friendlies");
	SaveRegisters();

	int reg1 = 31;
	int reg2 = 30;
	int reg3 = 29;
	int reg4 = 28;
	int reg5 = 27;
	int reg6 = 26;
	int flagReg = 25;

	
	SetRegister(flagReg, -1); //Doesn't do anything unless changed

	LoadWordToReg(reg1, ENDLESS_FRIENDLIES_MODE_INDEX + Line::VALUE);
	If(reg1, GREATER_OR_EQUAL_I, 2); {
		LoadWordToReg(reg2, reg1, ENDLESS_ROTATION_QUEUE_LOC);
		If(reg2, NOT_EQUAL_I, 0); {
			SetRegister(flagReg, 1);

			LWZ(reg3, 3, 0x48);
			ADDI(reg3, reg3, 1); //port num

			SetRegister(reg4, P1_STOP_LOAD_FLAG_PTR_LOC - 4);
			MULLI(reg5, reg3, 4);
			ADDI(reg6, 3, 0x5D);
			STWX(reg6, reg4, reg5);

			RLWINM(reg4, reg2, 8, 24, 31); //>>24
			If(reg4, EQUAL, reg3); {
				SetRegister(flagReg, 0);
			} EndIf();

			RLWINM(reg4, reg2, 16, 24, 31); //>>16 & 0xFF
			If(reg4, EQUAL, reg3); {
				SetRegister(flagReg, 0);
			} EndIf();
		} Else(); {
			IfInVersus(reg3); {
				SetRegister(flagReg, 0);
			} EndIf();
		} EndIf();
	} EndIf();

	If(flagReg, EQUAL_I, 0);
	{
		LBZ(reg3, 3, 0x5D);
		ANDI(reg3, reg3, ~0x8); //clear flag
		STB(reg3, 3, 0x5D);
	} EndIf();
	If(flagReg, EQUAL_I, 1);
	{
		LBZ(reg3, 3, 0x5D);
		ORI(reg3, reg3, 0x8); //set flag
		STB(reg3, 3, 0x5D);
	} EndIf();
	

	RestoreRegisters();
	ASMEnd(0x8803005d); //lbz r0, 0x5D (r3)
}

void ActualCodes()
{
	endlessFriendlies();

	if (DI_DRAW_INDEX != -1) {
		DrawDI();
	}

	if (SAVE_STATES_INDEX != -1) {
		AddArticle();

		RemoveArticle();
	}

	if(!constantOverrides.empty()) {
		constantOverride();
	}

	if(DBZ_MODE_INDEX != -1) {
		DBZMode();
	}

	if(ALT_STAGE_BEHAVIOR_INDEX != -1) {
		//ASMStart(0x8094a168);
#if BUILD_TYPE == PROJECT_PLUS
		ASMStart(0x8010f990, "[CM: Code Menu] Alt Stage Behavior");
#else
		ASMStart(0x8094bf60);
#endif
		SaveRegisters();

		int Reg1 = 3;
		int Reg2 = 4;
		int Reg3 = 5;
		int Reg4 = 6;

		LoadWordToReg(Reg1, ALT_STAGE_BEHAVIOR_INDEX + Line::VALUE);
		If(Reg1, EQUAL_I, 2); //disable
		{
			SetRegister(Reg1, 0);
			SetRegister(Reg2, 0x800B9EA2);
			STH(Reg1, Reg2, 0);
			SetRegister(Reg2, ALT_STAGE_VAL_LOC);
			STH(Reg1, Reg2, 0);
		} Else(); If(Reg1, EQUAL_I, 1); //random
		{
#if BUILD_TYPE == PROJECT_PLUS
			vector<int> alts = { 0, BUTTON_L, BUTTON_R, BUTTON_Z, BUTTON_Y };
#else
			vector<int> alts = { 0, BUTTON_L, BUTTON_Z, BUTTON_START };
#endif
			LoadWordToReg(Reg1, Reg2, RANDOM_ALTS_MATCH_START_FLAG);
			If(Reg1, EQUAL_I, 1); {
				//set new rng value and clear flag
				LoadWordToReg(Reg4, 0x805a00bc); //random val
				//RLWINM(Reg1, Reg1, 32 - 8, 30, 31);
				SetRegister(Reg3, alts.size());
				MOD(Reg1, Reg4, Reg3);
				SetRegister(Reg3, RANDOM_ALTS_RNG);
				STW(Reg1, Reg3, 0);
				SetRegister(Reg1, 0);
				STW(Reg1, Reg2, 0);
			} EndIf();
			
			LoadWordToReg(Reg3, RANDOM_ALTS_RNG);

			//SetRegister(Reg2, 4);
			//MOD(Reg3, Reg1, Reg2);
			for (int i = 0; i < alts.size(); i++) {
				If(Reg3, EQUAL_I, i); {
					SetRegister(Reg4, alts[i]);
				} EndIf();
			}
			/*If(Reg3, EQUAL_I, 1);
			{
				SetRegister(Reg3, BUTTON_L);
			} EndIf();
			If(Reg3, EQUAL_I, 2);
			{
				SetRegister(Reg3, BUTTON_START);
			} EndIf();
			If(Reg3, EQUAL_I, 3);
			{
				SetRegister(Reg3, BUTTON_Z);
			} EndIf();*/
			SetRegister(Reg2, 0x800B9EA2);
			STH(Reg4, Reg2, 0);
			SetRegister(Reg2, ALT_STAGE_VAL_LOC);
			STH(Reg4, Reg2, 0);
		} EndIf(); EndIf();

		RestoreRegisters();
#if BUILD_TYPE == PROJECT_PLUS
		ASMEnd(0x7cbd2b78); //mr r29, r5
#else
		ASMEnd(0x7fe3fb78); //mr r3, r31
#endif
		//ASMEnd(0x809d0038); //lwz r4, r29, 0x38
	}

	if (CROWD_CHEER_TOGGLE_INDEX != -1) {
		ASMStart(0x8081AD54, "[CM: Code Menu] Crowd Cheer Toggle");
		SaveRegisters();

		int reg1 = 31;

		LoadWordToReg(reg1, CROWD_CHEER_TOGGLE_INDEX + Line::VALUE);
		If(reg1, EQUAL_I, false); {
			RestoreRegisters();
			SetRegister(3, 0);
			BLR();
		} EndIf();

		RestoreRegisters();
		ASMEnd(0x9421ffd0); //stwu sp, -0x30(sp)
	}

	if (STALING_TOGGLE_INDEX != -1) {
		ASMStart(0x808e00a4, "[CM: Code Menu] Staling Toggle");
		
		LoadWordToReg(6, STALING_TOGGLE_INDEX + Line::VALUE);
		If(6, EQUAL_I, 1); {
			SetRegister(0, 8);
		} EndIf();
		If(6, EQUAL_I, 2); {
			SetRegister(0, 0);
		} EndIf();

		SetRegister(6, 0x808E0000);
		ASMEnd(0x5400efff); //rlwinm. r0, r0, 29, 31, 31
	}

	ControlCodes();
}

void CreateMenu(Page& MainPage)
{
	if (!xml::collectedAddons.empty())
	{
		xml::applyCollectedAddons(ChangelogOutput);
	}
	xml::applyLineSettingsFromMenuOptionsTree(MainPage, cmnuOptionsOutputFilePath, ChangelogOutput);
	xml::buildMenuOptionsTreeFromMenu(MainPage, cmnuOptionsOutputFilePath);

	//make pages
	CurrentOffset = START_OF_CODE_MENU;
	vector<Page*> Pages(1, &MainPage);
	vector<int> CalledPageOffsets(1, 0);
	int EndOffset = MainPage.Size;
	for (int i = 0; i < Pages.size(); i++) {
		CurrentOffset += Page::NUM_WORD_ELEMS * 4;
		for (Line* &x : Pages[i]->Lines) {
			if (x->behaviorFlags[Line::lbf_REMOVED]) continue; // If the line is explicitly marked as removed, skip it!
			if (x->Index != nullptr) {
				*(x->Index) = CurrentOffset;
			}
			//printf("%X\n", CurrentOffset);
			CurrentOffset += x->Size;
			if (x->type == PRINT_LINE) {
				int offset = CurrentOffset - x->numArgs * 4;
				//printf("%d\n%X\n%X\n", x->Size, CurrentOffset, offset);
				for (auto arg : x->args) {
					*arg = offset;
					offset += 4;
				}
			}
			if (x->type == SUB_MENU_LINE) {
				x->SubMenuOffset = EndOffset - CalledPageOffsets[i];
				Pages.push_back(x->SubMenuPtr);
				CalledPageOffsets.push_back(EndOffset);
				EndOffset += x->SubMenuPtr->Size;
			}
		}
		//Pages[i]->Lines.back()->Size = 0;
	}

	//setup header
	vector<u8> Header;
	AddValueToByteArray(START_OF_CODE_MENU, Header); //current page ptr
	AddValueToByteArray(START_OF_CODE_MENU, Header); //main page ptr
	//button combos
	AddValueToByteArray(BUTTON_L | BUTTON_R | BUTTON_Y , Header); //salty runback
	AddValueToByteArray(BUTTON_L | BUTTON_R | BUTTON_X, Header); //skip results
	// Float Conversion Space
	AddValueToByteArray(0x43300000, Header); // Conversion Constant
	AddValueToByteArray(0x00000000, Header);
	AddValueToByteArray(0x43300000, Header); // Conversion Staging Space
	AddValueToByteArray(0x00000000, Header);
	AddValueToByteArray(0x00000000, Header); // Extra Staging Word
	//frame timers
	AddValueToByteArray(0, Header); //move frame timer
	AddValueToByteArray(0, Header); //value frame timer
	AddValueToByteArray(0, Header); //frame advance frame timer
	//control flags
	AddValueToByteArray(CODE_MENU_CLOSED, Header); //prev flag
	AddValueToByteArray(CODE_MENU_CLOSED, Header); //current flag
	AddValueToByteArray(0, Header); //infinite friendlies flag
	AddValueToByteArray(0, Header); //auto save replays flag
	AddValueToByteArray(0, Header); //group records flag
	//button mask
	AddValueToByteArray(0, Header); //code menu mask
	AddValueToByteArray(0, Header); //button activator mask
	for(int i = 0; i < 8; i++) { AddValueToByteArray(0, Header); } //main mask
	//old debug state
	AddValueToByteArray(0, Header); //old debug state
	AddValueToByteArray(0, Header); //camera lock state
	//old camera pos
	AddValueToByteArray(0, Header); //old camera pos
	//save state buffer ptr
	AddValueToByteArray(0, Header);
	AddValueToByteArray(0, Header); //article ptr
	AddValueToByteArray(0, Header); //article ID ptr
	AddValueToByteArray(0, Header); //article resource ptr
	AddValueToByteArray(0, Header); //locations to update ptr locs
	AddValueToByteArray(0, Header); //locations to clear ptr locs
	AddValueToByteArray(0, Header); //saved article ptr list
	//reset line stack
	AddValueToByteArray(RESET_LINES_STACK_LOC, Header); //reset line stack
	for (int i = 0; i < MAX_SUBPAGE_DEPTH + 1; i++) { AddValueToByteArray(0, Header); }

	AddValueToByteArray(0, Header); // \ Space reclaimed from lowering MAX_SUBPAGE_DEPTH from 20 to 16! 
	AddValueToByteArray(0, Header); // | Ensure you update _CodeMenuHeaderConstants.h if you use these.
	AddValueToByteArray(0, Header); // /
	AddValueToByteArray(ALT_STAGE_BEHAVIOR_INDEX, Header); // Alternate Stage Line INDEX

	//address arrays
	//character switcher
	AddValueToByteArray(CHARACTER_SELECT_P1_INDEX, Header); //P1
	AddValueToByteArray(CHARACTER_SELECT_P2_INDEX, Header); //P2
	AddValueToByteArray(CHARACTER_SELECT_P3_INDEX, Header); //P3
	AddValueToByteArray(CHARACTER_SELECT_P4_INDEX, Header); //P4
	//infinite shields
	AddValueToByteArray(INFINITE_SHIELDS_P1_INDEX, Header); //P1
	AddValueToByteArray(INFINITE_SHIELDS_P2_INDEX, Header); //P2
	AddValueToByteArray(INFINITE_SHIELDS_P3_INDEX, Header); //P3
	AddValueToByteArray(INFINITE_SHIELDS_P4_INDEX, Header); //P4
	//percent selection values
	AddValueToByteArray(PERCENT_SELECT_VALUE_P1_INDEX, Header); //P1
	AddValueToByteArray(PERCENT_SELECT_VALUE_P2_INDEX, Header); //P2
	AddValueToByteArray(PERCENT_SELECT_VALUE_P3_INDEX, Header); //P3
	AddValueToByteArray(PERCENT_SELECT_VALUE_P4_INDEX, Header); //P4
	//percent selection activators
	AddValueToByteArray(PERCENT_SELECT_ACTIVATOR_P1_INDEX, Header); //P1
	AddValueToByteArray(PERCENT_SELECT_ACTIVATOR_P2_INDEX, Header); //P2
	AddValueToByteArray(PERCENT_SELECT_ACTIVATOR_P3_INDEX, Header); //P3
	AddValueToByteArray(PERCENT_SELECT_ACTIVATOR_P4_INDEX, Header); //P4
	//disable DPad activators
	AddValueToByteArray(DISABLE_DPAD_P1_INDEX, Header); //P1
	AddValueToByteArray(DISABLE_DPAD_P2_INDEX, Header); //P2
	AddValueToByteArray(DISABLE_DPAD_P3_INDEX, Header); //P3
	AddValueToByteArray(DISABLE_DPAD_P4_INDEX, Header); //P4
	//Endless Rotation player queue
	AddValueToByteArray(0, Header);
	AddValueToByteArray(0, Header);
	//Endless Rotation sort buffer
	AddValueToByteArray(0, Header);
	AddValueToByteArray(0, Header);
	AddValueToByteArray(0, Header);
	AddValueToByteArray(0, Header);
	//Endless Rotation comp func
	AddValueToByteArray(0x80630000, Header);
	AddValueToByteArray(0x80840000, Header);
	AddValueToByteArray(0x7C641850, Header);
	AddValueToByteArray(0x4E800020, Header);
	//replay buffers
	for(int i = 0; i < 5; i++) { AddValueToByteArray(0, Header); } //nte buffer
	for(int i = 0; i < 2; i++) { AddValueToByteArray(0, Header); } //section buffer
	for(int i = 0; i < 12; i++) { AddValueToByteArray(0, Header); } //crypto buffer
	//button conversion tables
	Header.insert(Header.end(), CODE_MENU_WIIMOTE_CONVERSION_TABLE.begin(), CODE_MENU_WIIMOTE_CONVERSION_TABLE.end());
	Header.insert(Header.end(), CODE_MENU_WIICHUCK_CONVERSION_TABLE.begin(), CODE_MENU_WIICHUCK_CONVERSION_TABLE.end());
	Header.insert(Header.end(), CODE_MENU_CLASSIC_CONVERSION_TABLE.begin(), CODE_MENU_CLASSIC_CONVERSION_TABLE.end());
	//Display tag hex
	for (auto x : { P1_TAG_HEX_LOC, P2_TAG_HEX_LOC, P3_TAG_HEX_LOC, P4_TAG_HEX_LOC }) {
		AddValueToByteArray('$', Header);
		for (int i = 0; i < 23; i++) { AddValueToByteArray((u8)0, Header); }
	}
	//Endless Friendlies rotation ptrs
	AddValueToByteArray(0, Header);
	AddValueToByteArray(0, Header);
	AddValueToByteArray(0, Header);
	AddValueToByteArray(0, Header);
	
	//random alts
	//rng
	AddValueToByteArray(0, Header);
	//start match flag
	AddValueToByteArray(1, Header);

	//TEAM_SETTINGS_LOC
	AddValueToByteArray(0, Header);
	//TAG_LOAD_FLAGS_LOC
	AddValueToByteArray(0, Header);

	//PREV_TAG_COSTUMES_SETTING_LOC
	AddValueToByteArray(0, Header);

	//DOLPHIN_MOUNT_VF_LOC
	AddValueToByteArray(0, Header);

	//CODE_MENU_OLD_CAMERA_MATRIX_LOC
	for (int i = 0; i < 12; i++) { AddValueToByteArray(0, Header); }
	//CODE_MENU_NEED_TO_SAVE_CAMERA_MATRIX_FLAG_LOC
	AddValueToByteArray(0, Header);

	//SHOULD_DISPLAY_HUD_FLAG_LOC
	AddValueToByteArray(0, Header);

	//SHOULD_RESET_HITBOX_DISPLAY_FLAG_LOC
	AddValueToByteArray(0, Header);
	//SHOULD_RESET_STAGE_COLLISIONS_FLAG_LOC
	AddValueToByteArray(0, Header);

	//Auto L-Cancelling
	AddValueToByteArray(ALC_P1_INDEX, Header);
	AddValueToByteArray(ALC_P2_INDEX, Header);
	AddValueToByteArray(ALC_P3_INDEX, Header);
	AddValueToByteArray(ALC_P4_INDEX, Header);
	
	//Big Head Mode Index
	AddValueToByteArray(BIG_HEAD_INDEX, Header);

	//Random Angle Mode
	AddValueToByteArray(RANDOM_ANGLE_INDEX, Header);

	//War Mode Index
	AddValueToByteArray(WAR_MODE_INDEX, Header);

	//Input Buffer
	AddValueToByteArray(BUFFER_P1_INDEX, Header);
	AddValueToByteArray(BUFFER_P2_INDEX, Header);
	AddValueToByteArray(BUFFER_P3_INDEX, Header);
	AddValueToByteArray(BUFFER_P4_INDEX, Header);

	//Scale Modifier
	AddValueToByteArray(SCALE_INDEX, Header);

	//Scale Modifier
	AddValueToByteArray(SPEED_INDEX, Header);

	// CSS VER Modifier
	AddValueToByteArray(CSS_VERSION_SETTING_INDEX, Header);

	// Theme Setting
	AddValueToByteArray(THEME_SETTING_INDEX, Header);

	// Dash Attack Item Grab Setting
	AddValueToByteArray(DASH_ATTACK_ITEM_GRAB_INDEX, Header);
	
	// Tripping Toggle
	AddValueToByteArray(TRIP_TOGGLE_INDEX, Header);
	// Tripping Rate Multiplier
	AddValueToByteArray(TRIP_RATE_MULTIPLIER_INDEX, Header);
	// Tripping Cooldown Toggle
	AddValueToByteArray(TRIP_INTERVAL_INDEX, Header);

	// PSCC Settings
	AddValueToByteArray(PSCC_COLOR_1_INDEX, Header);
	AddValueToByteArray(PSCC_COLOR_2_INDEX, Header);
	AddValueToByteArray(PSCC_COLOR_3_INDEX, Header);
	AddValueToByteArray(PSCC_COLOR_4_INDEX, Header);
	//PSCC_TEAM_BATTLE_STORE_LOC
	// First byte is an offset used to lbzx to either VALUE or DEFAULT quickly (init to VALUE).
	AddValueToByteArray(Line::VALUE << 0x18, Header);
	// Player Slot Color Float Table Address
	AddValueToByteArray(0, Header);

	// Jumpsquat Override
	AddValueToByteArray(JUMPSQUAT_OVERRIDE_TOGGLE_INDEX, Header);
	AddValueToByteArray(JUMPSQUAT_OVERRIDE_FRAMES_INDEX, Header);
	AddValueToByteArray(JUMPSQUAT_OVERRIDE_MIN_INDEX, Header);
	AddValueToByteArray(JUMPSQUAT_OVERRIDE_MAX_INDEX, Header);

	// Player Slot Color Callback Table Address
	AddValueToByteArray(0xFFFFFFFF, Header);
	
	//draw settings buffer
	vector<u32> DSB(0x200 / 4, 0);
	DSB[0x4 / 4] = 0xFFFFFFFF;
	DSB[0x38 / 4] = 1;
	DSB[0x3C / 4] = 1;
	DSB[0x4C / 4] = 0x01000000;
	DSB[0x50 / 4] = 0x3D800000;
	DSB[0x58 / 4] = 0x3f793cde;
	DSB[(0x100 + 0x4C) / 4] = DRAW_SETTINGS_BUFFER_LOC + 0x100;
	DSB[0x1D0 / 4] = DRAW_SETTINGS_BUFFER_LOC + 0x100;
	for (auto x : DSB) {
		AddValueToByteArray(x, Header);
	}

	// If there are MEM2Constants...
	if (MEM2_CONSTANTS_LENGTH > 0)
	{
		// ... reserve space for them in the CMNU!
		Header.resize(Header.size() + MEM2_CONSTANTS_LENGTH, 0xCC);
	}

	// PSCC Quick Font Loc
	AddValueToByteArray(0xFF, Header);
	AddValueToByteArray(0xFF, Header);
	AddValueToByteArray(0xFF, Header);
	AddValueToByteArray(0xA8, Header);

	if (LINE_COLOR_TABLE.table_size() > 0)
	{
		for (std::size_t i = 0; i < LINE_COLOR_TABLE.__COLOR_COUNT; i++)
		{
			AddValueToByteArray(LINE_COLOR_TABLE.COLORS_ARR[i], Header);
		}
	}

	if (HEAP_ADDRESS_TABLE.table_size() > 0)
	{
		// Reserve space for Address Table (just initialized to zeroes, value populated in-game).
		Header.resize(Header.size() + HEAP_ADDRESS_TABLE.address_array_size(), 0x00);
		// Write ID Array to Header.
		Header.insert(Header.end(), HEAP_ADDRESS_TABLE.idArray.cbegin(), HEAP_ADDRESS_TABLE.idArray.cend());
	}

	// Utility Function Dead Hook Loc
	AddValueToByteArray(0x00000000, Header);

	if (START_OF_CODE_MENU - START_OF_CODE_MENU_HEADER != Header.size()) {
		std::cout << "Messed up header\n";
		exit(-1);
	}

	copy(Header.begin(), Header.end(), ostreambuf_iterator<char>(MenuFile));

	for (auto x : Pages) {
		x->WritePage();
	}

	std::vector<char> padding(0x10 - (MenuFile.tellp() % 0x10), 0x00);
	copy(padding.begin(), padding.end(), ostreambuf_iterator<char>(MenuFile));
	xml::generateAddonEmbeds(MenuFile);
	padding.resize(0x10 - (MenuFile.tellp() % 0x10), 0x00);
	if (padding.size() < 0x10)
	{
		copy(padding.begin(), padding.end(), ostreambuf_iterator<char>(MenuFile));
	}
}

void constantOverride() {
	ASMStart(0x80023d60, std::string("[CM: Code Menu] Constant Overrides") + 
		std::string(xml::CONFIG_PSCC_ENABLED ? " + Run PSCC Color Update Callbacks" : ""));

	int reg1 = 11;
	int reg2 = 12;
	int reg3 = 10;

	unsigned short prevIndexHiHalf = 0xFFFF;
	unsigned short prevDestHiHalf = 0xFFFF;
	std::sort(constantOverrides.begin(), constantOverrides.end());
	for(auto& x : constantOverrides) {

		unsigned short indexHiHalf = *x.index >> 0x10;
		unsigned short indexLoHalf = (*x.index & 0xFFFF) + Line::VALUE;
		indexHiHalf += bool(indexLoHalf >= 0x8000);
		if (indexHiHalf != prevIndexHiHalf)
		{
			ADDIS(reg1, 0, indexHiHalf);
		}
		switch (x.writeSize)
		{
			case ConstantPair::ds_BYTE_A: { LBZ(reg3, reg1, indexLoHalf); break; }
			case ConstantPair::ds_BYTE_B: { LBZ(reg3, reg1, indexLoHalf + 1); break; }
			case ConstantPair::ds_BYTE_C: { LBZ(reg3, reg1, indexLoHalf + 2); break; }
			case ConstantPair::ds_BYTE_D: { LBZ(reg3, reg1, indexLoHalf + 3); break; }
			case ConstantPair::ds_HALF_A: { LHZ(reg3, reg1, indexLoHalf); break; }
			case ConstantPair::ds_HALF_B: { LHZ(reg3, reg1, indexLoHalf + 2); break; }
			case ConstantPair::ds_WORD: { LWZ(reg3, reg1, indexLoHalf); break; }
		}
		prevIndexHiHalf = indexHiHalf;

		unsigned short destHiHalf = x.address >> 0x10;
		unsigned short destLoHalf = x.address & 0xFFFF;
		destHiHalf += bool(destLoHalf >= 0x8000);
		if (destHiHalf != prevDestHiHalf)
		{
			ADDIS(reg2, 0, destHiHalf);
		}
		switch (x.writeSize)
		{
			case ConstantPair::ds_BYTE_A: case ConstantPair::ds_BYTE_B:
			case ConstantPair::ds_BYTE_C: case ConstantPair::ds_BYTE_D: 
			{ STB(reg3, reg2, destLoHalf);  break; }
			case ConstantPair::ds_HALF_A: case ConstantPair::ds_HALF_B:
			{ STH(reg3, reg2, destLoHalf); break; }
			case ConstantPair::ds_WORD:
			{ STW(reg3, reg2, destLoHalf); break; }
		}
		prevDestHiHalf = destHiHalf;
	}

	if (xml::CONFIG_PSCC_ENABLED)
	{
		int menuNotLoadedLabel = GetNextLabel();
		// If reg1 isn't already loaded with the top half of START_OF_CODE_MENU_HEADER...
		if (prevIndexHiHalf != unsigned short(START_OF_CODE_MENU_HEADER >> 0x10))
		{
			// ... set up its value!
			ADDIS(reg1, 0, START_OF_CODE_MENU_HEADER >> 0x10);
		}
		// Try to load START_OF_CODE_MENU from the header.
		LWZ(reg2, reg1, (START_OF_CODE_MENU_HEADER & 0xFFFF) + 4);
		// Use reg3 to store the full START_OF_CODE_MENU value into reg3...
		ADDI(reg3, reg1, START_OF_CODE_MENU & 0xFFFF);
		// ... then compare the two: the loaded value vs the expected value.
		CMPL(reg3, reg2, 0);
		// And if the two aren't equal, then we know the menu isn't loaded, skip to notLoaded tag!
		JumpToLabel(menuNotLoadedLabel, bCACB_NOT_EQUAL);

		// Otherwise, we're free to run our callbacks!
		// Load the pointer for the callback array...
		LWZ(reg2, reg1, PSCC_CALLBACK_TABLE_LOC & 0xFFFF);
		// ...and do a register backup!
		// Allocate a stack frame for r14 and up!
		STWU(1, 1, -0x60);
		// Store r0 (we need its value for the comparison at the end of this hook!)
		STW(0, 1, 0x8);
		// Backup and store LR
		MFLR(0);
		STW(0, 1, 0x4);
		// Store r14 through r31
		STMW(14, 1, 0xC);

		// Setup our own variables starting at r31
		int callbackArrayPtr = 31;
		int colorTablePtr = 30;
		int currentColorOffset = 29;

		// Copy callback array pointer out of reg2
		MR(callbackArrayPtr, reg2);
		// Zero our Offset register
		ADDI(currentColorOffset, 0, 0);
		// Grab a pointer to our color table.
		LWZ(colorTablePtr, reg1, PSCC_FLOAT_TABLE_LOC & 0xFFFF);

		// Run our callback loop!
		int callbackLoopHeadLabel = GetNextLabel();
		int funcBadLabel = GetNextLabel();
		Label(callbackLoopHeadLabel);
		ADD(3, colorTablePtr, currentColorOffset);
		LBZ(reg2, 3, 0x7);
		CMPLI(reg2, pscc::callbackTableEntryCount, 0);
		JumpToLabel(funcBadLabel, bCACB_GREATER_OR_EQ);
		RLWINM(reg2, reg2, 2, 0, 0x1D);
		LWZX(reg2, callbackArrayPtr, reg2);
		CMPLI(reg2, 0x00, 0);
		JumpToLabel(funcBadLabel, bCACB_EQUAL);
		MTCTR(reg2);
		BCTRL();
		Label(funcBadLabel);
		ADDI(currentColorOffset, currentColorOffset, pscc::colorTableEntrySizeInBytes);
		CMPLI(currentColorOffset, pscc::getColorTableSizeInBytes(), 0);
		JumpToLabel(callbackLoopHeadLabel, bCACB_LESSER);
		
		// Finally, restore register backups!
		// Restore LR
		LWZ(0, 1, 0x4);
		MTLR(0);
		// Restore r0
		LWZ(0, 1, 0x8);
		// Restore r14 through r31
		LMW(14, 1, 0xC);
		// Deallocate stack frame!
		ADDI(1, 1, 0x60);
		Label(menuNotLoadedLabel);
	}
	
	ASMEnd(0x2c000000); //cmpwi, r0, 0
}

void ControlCodeMenu()
{
	// Establish Subroutines!
	ResetLineSubroutineLabel = GetNextLabel();
	ModifyLineValueSubroutineLabel = GetNextLabel();

	ASMStart(0x80029574, "[CM: Code Menu] Control Code Menu");
	SaveRegisters(14);

	printMenuSetters();

	int Reg1 = 31;
	int Reg2 = 30;
	int Reg3 = 29;
	int Reg4 = 28;
	int Reg5 = 27;
	int Reg6 = 26;
	int Reg7 = 25;
	int Reg8 = 24;
	int Reg9 = 23;
	int CharacterBufferReg = 21;
	int MainBufferReg = 20;
	int OpenFlagReg = 19;
	int ControlStickXReg = 18;
	int ControlStickYReg = 17;
	int CounterReg = 16;
	int ButtonReg = 15;
	int ActionReg = 14;

	int NotLoaded = GetNextLabel();

	// Rewritten check for whether or not menu is loaded!
	// Load the main page pointer from just past the Menu Header Loc into Reg4 (this should be START_OF_CODE_MENU).
	ADDIS(Reg1, 0, START_OF_CODE_MENU_HEADER >> 0x10);
	LWZ(Reg4, Reg1, (START_OF_CODE_MENU_HEADER & 0xFFFF) + 4);
	// Add the bottom half of START_OF_CODE_MENU to Reg1, so Reg1 should *also* now be START_OF_CODE_MENU.
	ADDI(Reg1, Reg1, START_OF_CODE_MENU & 0xFFFF);
	// Compare the two as unsigned integers.
	CMPL(Reg1, Reg4, EQUAL_L);
	// And if the two aren't equal, then we know the menu isn't loaded, skip to notLoaded tag!
	JumpToLabel(NotLoaded, bCACB_NOT_EQUAL);

	LoadWordToReg(Reg4, HUD_DISPLAY_INDEX + Line::VALUE);
	If(Reg4, EQUAL_I, 0);
	{
		SetRegister(Reg4, SHOULD_DISPLAY_HUD_FLAG_LOC);
		SetRegister(Reg1, 1);
		STW(Reg1, Reg4, 0);
		
		//Remove HUD
		SetRegister(3, 0x80672f40);
		SetRegister(4, 8);
		SetRegister(5, 0);
		CallBrawlFunc(0x8000D234); //setLayerDispStatus[gfSceneRoot]
	} Else();
	{
		LoadWordToReg(Reg1, Reg4, SHOULD_DISPLAY_HUD_FLAG_LOC);
		If(Reg1, EQUAL_I, 1);
		{
			//Show HUD
			SetRegister(3, 0x80672f40);
			SetRegister(4, 8);
			SetRegister(5, 1);
			CallBrawlFunc(0x8000D234); //setLayerDispStatus[gfSceneRoot]

			SetRegister(Reg1, 0);
			STW(Reg1, Reg4, 0);
		} EndIf();
	} EndIf();
	
	
	LoadWordToReg(OpenFlagReg, Reg4, CODE_MENU_CONTROL_FLAG);

	//GCC input
	SetRegister(Reg1, PLAY_BUTTON_LOC_START - BUTTON_PORT_OFFSET);
	SetRegister(Reg7, 0x804DE4B0 - 8);
	SetRegister(ButtonReg, 0);
	SetRegister(ControlStickXReg, 0);
	SetRegister(ControlStickYReg, 0);
	CounterLoop(CounterReg, 0, 4, 1); {
		LHZU(Reg8, Reg7, 8);
		LWZU(Reg2, Reg1, BUTTON_PORT_OFFSET);
		If(Reg8, GREATER_OR_EQUAL_I_L, 0x2000);
		{
			SetRegister(Reg8, 0);
		}EndIf();
		ANDI(Reg8, Reg8, 0x1000);
		OR(ButtonReg, ButtonReg, Reg2);
		OR(ButtonReg, ButtonReg, Reg8);

		ANDI(Reg8, Reg2, BUTTON_L | BUTTON_R | BUTTON_DD);
		If(Reg8, GREATER_I, BUTTON_L | BUTTON_R); {
			//L + R + DDown is pressed
			If(OpenFlagReg, NOT_EQUAL_I, CODE_MENU_OPEN); {
				SetRegister(OpenFlagReg, CODE_MENU_TRIGGERED);
			}EndIf();
		}EndIf();
		
		LBA(Reg2, Reg1, GCC_CONTROL_STICK_X_START - PLAY_BUTTON_LOC_START);
		ADD(ControlStickXReg, ControlStickXReg, Reg2);

		LBA(Reg2, Reg1, GCC_CONTROL_STICK_Y_START - PLAY_BUTTON_LOC_START);
		ADD(ControlStickYReg, ControlStickYReg, Reg2);
	}CounterLoopEnd();

	//Wiimote control stick
	CounterLoop(CounterReg, 0, 4, 1); {
		ADDI(Reg1, Reg1, BUTTON_PORT_OFFSET);

		LBA(Reg2, Reg1, GCC_CONTROL_STICK_X_START - PLAY_BUTTON_LOC_START);
		ADD(ControlStickXReg, ControlStickXReg, Reg2);

		LBA(Reg2, Reg1, GCC_CONTROL_STICK_Y_START - PLAY_BUTTON_LOC_START);
		ADD(ControlStickYReg, ControlStickYReg, Reg2);
	}CounterLoopEnd();

	//Wiimote input
	SetRegister(Reg1, WII_BASED_CONTROLLER_START - WII_BASED_CONTROLLER_PORT_OFFSET);
	SetRegister(Reg3, 1);
	CounterLoop(Reg8, 0, 4, 1); {
		//Reg8 is loop counter, Reg3 is 1, Reg1 is wiimote location, Reg2 is storage loc, Reg9 is activation address, Reg6 is conversion
		//Reg5 has wiimote buttons
		LHZU(Reg5, Reg1, WII_BASED_CONTROLLER_PORT_OFFSET); //get buttons
		SetRegister(Reg6, CODE_MENU_WIIMOTE_CONVERSION_TABLE_LOC);
		LBZ(Reg7, Reg1, WII_BASED_CONTROLLER_TYPE_OFFSET); //get type
		If(Reg7, EQUAL_I, 2); {
			//is classic
			LHZ(Reg5, Reg1, WII_BASED_CONTROLLER_TYPE_OFFSET + 2); //buttons are in different place
			ANDI(Reg9, Reg5, 0xC003); //get if DPad pressed
			If(Reg9, NOT_EQUAL_I, 0); {
				ANDI(Reg9, Reg5, 0x2200);
				If(Reg9, EQUAL_I, 0x2200); {
					If(OpenFlagReg, NOT_EQUAL_I, CODE_MENU_OPEN); {
						SetRegister(OpenFlagReg, CODE_MENU_TRIGGERED);
					}EndIf();
				}EndIf();
			}EndIf();
		}Else(); {
			ANDI(Reg9, Reg5, 0x1900);
			If(Reg9, EQUAL_I, 0x1900); {
				If(OpenFlagReg, NOT_EQUAL_I, CODE_MENU_OPEN); {
					SetRegister(OpenFlagReg, CODE_MENU_TRIGGERED);
				}EndIf();
			}EndIf();
		}EndIf();
		MULLI(Reg7, Reg7, 16);
		ADD(Reg6, Reg6, Reg7); //get proper conversion table

		While(Reg5, GREATER_I, 0); {
			//convert buttons
			ANDI(Reg7, Reg5, 1);
			If(Reg7, NOT_EQUAL_I, 0); {
				//button pressed
				LBZ(Reg7, Reg6, 0);
				RLWNM(Reg7, Reg3, Reg7, 15, 31);
				OR(ButtonReg, ButtonReg, Reg7);
			}EndIf();

			ADDI(Reg6, Reg6, 1);
			RLWINM(Reg5, Reg5, 31, 15, 31);
		}EndWhile();
	}CounterLoopEnd();


	LoadWordToReg(Reg3, Reg5, IS_DEBUG_PAUSED);
	
	// If we're hovering over the Code Menu button in the Main Menu...
	If(OpenFlagReg, EQUAL_I, CODE_MENU_PRIMED); {
		//check for A press
		SetRegister(OpenFlagReg, CODE_MENU_CLOSED);

		ANDI(Reg8, ButtonReg, BUTTON_A | BUTTON_START);
		If(Reg8, NOT_EQUAL_I, 0); {
			//A or start is pressed
			SetRegister(OpenFlagReg, CODE_MENU_TRIGGERED); //set open
		}EndIf();
	}
	// Additionally, if the Activation Setting line is present in the menu...
	if (CODE_MENU_ACTIVATION_SETTING_INDEX != -1) {
		// ... do another round of checks if the Code Menu has just been triggered via input.
		Else(); If(OpenFlagReg, EQUAL_I, CODE_MENU_TRIGGERED);

		int codeMenuEnabledLabel = GetNextLabel();

		// Load the Activation Flag...
		LoadWordToReg(Reg2, CODE_MENU_ACTIVATION_SETTING_INDEX + Line::VALUE);
		// ... and do a single comparison against 1, since that'll do enough to distinguish 0, 1, and 2
		CMPLI(Reg2, 1, 1);
		// If we're on setting 0 (ie. Default), then code menu is always enabled.
		JumpToLabel(codeMenuEnabledLabel, bCACB_LESSER.inConditionRegField(1));

		// Otherwise, if we're in-game...
		LoadWordToReg(Reg2, IS_IN_GAME_FLAG);
		CMPLI(Reg2, 1, 0);
		// ... AND we're on setting 1 (ie. 3.6)...	
		CRANDC(EQ, crBitInCRF(EQ, 1), EQ);
		// ... then code menu is enabled.
		JumpToLabel(codeMenuEnabledLabel, bCACB_EQUAL);

		// Otherwise, if we're on option 2 (ie. Off), or option 1 and in-game, we'll prevent the menu from opening.
		SetRegister(OpenFlagReg, CODE_MENU_CLOSED);

		Label(codeMenuEnabledLabel);
		EndIf();
	}
	EndIf();

	If(OpenFlagReg, EQUAL_I, CODE_MENU_TRIGGERED); {
		SetRegister(Reg2, OLD_DEBUG_STATE_LOC);
		SetRegister(OpenFlagReg, CODE_MENU_OPEN); //set open
		STW(Reg3, Reg2, 0); //store debug state

		//save and set camera pos
		SetRegister(Reg3, OLD_CAMERA_POS_LOC);
		LoadWordToReg(Reg1, 0x805b6df8);
		STW(Reg1, Reg3, 0);

		SetRegister(Reg2, CODE_MENU_BUTTON_MASK_LOC);
		STW(ButtonReg, Reg2, 0);

		// Play sound for opening menu.
		ADDI(4, 0, sii_SND_SE_SYSTEM_INFOWINDOW_OPEN);
		JumpToLabel(getPlaySELabel(), bCACB_UNSPECIFIED, 1);
	}EndIf();

	//get only pressed button
	LoadWordToReg(Reg2, Reg3, CODE_MENU_BUTTON_MASK_LOC);
	ORI(Reg9, Reg2, ~(BUTTON_Z | BUTTON_DPAD));
	AND(Reg9, ButtonReg, Reg9);
	STW(Reg9, Reg3, 0); //update mask
	ANDC(ButtonReg, ButtonReg, Reg2);

	STW(OpenFlagReg, Reg4, 0); //set flag

	If(OpenFlagReg, EQUAL_I, CODE_MENU_OPEN); {
		//prevent buttons from affecting the game
		SetRegister(Reg2, 0xFFFFFFFF);
		SetRegister(Reg3, MAIN_BUTTON_MASK_LOC - 4);
		CounterLoop(CounterReg, 0, 8, 1); {
			STWU(Reg2, Reg3, 4);
		}CounterLoopEnd();

		//stop stick inputs
		SetRegister(Reg1, GCC_CONTROL_STICK_X_START - BUTTON_PORT_OFFSET);
		SetRegister(Reg2, 0);
		CounterLoop(CounterReg, 0, 8, 1); {
			STHU(Reg2, Reg1, BUTTON_PORT_OFFSET); //clear stick input
		}CounterLoopEnd();

		SetRegister(Reg1, 1);
		STW(Reg1, Reg5, 0); //set debug paused

		GetActionFromInputs(ButtonReg, ControlStickXReg, ControlStickYReg, ActionReg);

		ExecuteAction(ActionReg, Reg1);

	}EndIf(); //run logic
	
	//button negate
	SetRegister(Reg1, PLAY_BUTTON_LOC_START - BUTTON_PORT_OFFSET);
	SetRegister(Reg2, MAIN_BUTTON_MASK_LOC - 4);
	CounterLoop(CounterReg, 0, 8, 1); {
		LWZU(Reg3, Reg2, 4); //mask
		LWZU(Reg4, Reg1, BUTTON_PORT_OFFSET); //buttons

		AND(Reg5, Reg4, Reg3);
		STW(Reg5, Reg2, 0); //update mask
		ANDC(Reg4, Reg4, Reg3); //apply mask
		STW(Reg4, Reg1, 0); //store new buttons
	}CounterLoopEnd();

	//LoadWordToReg(Reg6, ON_GROUP_RECORDS_FLAG_LOC);
	SetRegister(Reg6, 0);
	If(Reg6, EQUAL_I, 1); {
		SetRegister(Reg1, PLAY_BUTTON_LOC_START - BUTTON_PORT_OFFSET);
		SetRegister(Reg2, ~(BUTTON_A | BUTTON_START));
		CounterLoop(CounterReg, 0, 8, 1); {
			LWZU(Reg4, Reg1, BUTTON_PORT_OFFSET); //buttons
			AND(Reg4, Reg4, Reg2);
			STW(Reg4, Reg1, 0); //store new buttons
		}CounterLoopEnd();
	}EndIf();

	int SkipDebugNegation = GetNextLabel();

	if (CODE_MENU_ACTIVATION_SETTING_INDEX != -1) {
		LoadWordToReg(Reg2, IS_IN_GAME_FLAG);
		If(Reg2, EQUAL_I, 1); {
			LoadWordToReg(Reg2, CODE_MENU_ACTIVATION_SETTING_INDEX + Line::VALUE);
			If(Reg2, EQUAL_I, 1); {
				LoadWordToReg(Reg2, CODE_MENU_CONTROL_FLAG);
				If(Reg2, EQUAL_I, CODE_MENU_CLOSED); {
					JumpToLabel(SkipDebugNegation);
				}EndIf();
			}EndIf();
		}EndIf();
	}

	LoadWordToReg(Reg1, Reg3, 0x80584000);
	LoadWordToReg(Reg2, CODE_MENU_CONTROL_FLAG);
	ANDI(Reg6, ButtonReg, BUTTON_Z);
	If(Reg2, EQUAL_I, CODE_MENU_OPEN); // prevent z frame advance in menu
	{
		SetRegister(Reg6, 0);
	} EndIf();
	LoadWordToReg(Reg4, Reg5, FRAME_ADVANCE_FRAME_TIMER);
	SetRegister(Reg2, ~(0x10000000 | 0x00100000)); //stop all debug commands except pause and frame advance
	If(Reg6, NOT_EQUAL_I, 0); {
		Decrement(Reg4);
		If(Reg4, LESS_OR_EQUAL_I, 0); {
			If(Reg4, LESS_I, 0); {
				SetRegister(Reg4, FIRST_FRAME_ADVANCE_NUM_WAIT_FRAMES - FRAME_ADVANCE_NUM_WAIT_FRAMES);
			}EndIf();
			ANDIS(Reg1, Reg1, ~0x0010); //allow frame advance
			ADDI(Reg4, Reg4, FRAME_ADVANCE_NUM_WAIT_FRAMES);

			CounterLoop(Reg7, 0, 32, 8); //The actual suggested fix
			{
				LHZX(Reg8, Reg3, Reg7);
				ANDI(Reg8, Reg8, ~0x0010);
				STHX(Reg8, Reg3, Reg7);
			} CounterLoopEnd();
		}EndIf();
	}Else(); {
		SetRegister(Reg4, 0);
	}EndIf();
	STW(Reg4, Reg5, 0);

	If(OpenFlagReg, EQUAL_I, CODE_MENU_OPEN); {
		SetRegister(Reg2, -1); //stop all debug commands
	}EndIf();

	//Eon's Project+ 2.28 Fix
	SetRegister(Reg4, 0);
	While(Reg4, NOT_EQUAL_I, 32);
	{
		LWZX(Reg1, Reg3, Reg4);
		OR(Reg1, Reg2, Reg1);
		STWX(Reg1, Reg3, Reg4);
		ADDI(Reg4, Reg4, 0x8);
	}
	EndWhile();
	//Lines that were removed by Eon's P+ 2.28 Fix. 
	//OR(Reg1, Reg1, Reg2);
	//STW(Reg1, Reg3, 0);
	//stop Z and start if in menu

	ApplyMenuSetting(DEBUG_MODE_INDEX, 0x80583FFC + 3, Reg1, Reg2, 1);

	ApplyMenuSetting(DISPLAY_HITBOXES_INDEX, 0x80583FFC + 1, Reg1, Reg2, 1);

	ApplyMenuSetting(DISPLAY_LEDGEGRAB_INDEX, 0x80583FF8 + 1, Reg1, Reg2, 1);

	ApplyMenuSetting(DISPLAY_COLLISION_INDEX, 0x80583FF4 + 3, Reg1, Reg2, 1);

	ApplyMenuSetting(CAMERA_LOCK_INDEX, 0x80583FF8 + 3, Reg1, Reg2, 1);

	if (RANDOM_1_TO_1_INDEX != -1) {
		ApplyMenuSetting(RANDOM_1_TO_1_INDEX, RANDOM_1_TO_1_CPP_FLAG_LOC, Reg1, Reg2, 1);
		printf("1 to 1 location %0X\n", RANDOM_1_TO_1_CPP_FLAG_LOC);
	}

	Label(SkipDebugNegation);

	//dumb solution to code menu closing problem
	LoadWordToReg(OpenFlagReg, CODE_MENU_CONTROL_FLAG);

	//port based codes
	LoadWordToReg(Reg7, IS_IN_GAME_FLAG);
	If(OpenFlagReg, NOT_EQUAL_I, CODE_MENU_OPEN); {
		If(Reg7, EQUAL_I, 1); {
			//in match
			LoadWordToReg(MainBufferReg, MAIN_BUFFER_PTR);
			LWZU(CharacterBufferReg, MainBufferReg, 4);
			While(CharacterBufferReg, NOT_EQUAL_I, 0); {
				LWZ(Reg8, CharacterBufferReg, CHR_BUFFER_PORT_OFFSET);

				if (DISABLE_DPAD_P1_INDEX != -1) {
					LWZ(Reg2, CharacterBufferReg, CHR_BUFFER_INFO_PTR_OFFSET);
					RunIfPortToggle(DISABLE_DPAD_ACTIVATOR_ARRAY_LOC, Reg8); {
						LBZ(Reg2, Reg2, 7); //controller num
						SetRegister(Reg3, PLAY_BUTTON_LOC_START - 0x40);
						MULLI(Reg2, Reg2, BUTTON_PORT_OFFSET);
						LWZUX(Reg2, Reg3, Reg2); //get buttons
						ANDI(Reg2, Reg2, ~BUTTON_DPAD);
						STW(Reg2, Reg3, 0);
					}EndIf(); EndIf(); EndIf();
				}

				if (PERCENT_SELECT_ACTIVATOR_P1_INDEX != -1 && PERCENT_SELECT_VALUE_P1_INDEX != -1) {
					GetArrayValueFromIndex(PERCENT_SELCTION_ACTIVATOR_ARRAY_LOC, Reg8, 0, 3); {
						LWZ(5, 3, Line::VALUE); //get setting
						LWZ(Reg2, CharacterBufferReg, CHR_BUFFER_INFO_PTR_OFFSET);
						If(5, EQUAL_I, 1); {
							ANDI(Reg1, ButtonReg, 0xF);
							If(Reg1, NOT_EQUAL_I, 0); {
								GetArrayValueFromIndex(PERCENT_SELCTION_VALUE_ARRAY_LOC, Reg8, 0, 3); {
									LFS(1, 3, Line::VALUE);

									LWZ(Reg3, 13, -0x4150); // Get IfMngr Pointer
									RLWINM(Reg4, Reg8, 2, 0, 31); //<< 2
									ADD(Reg3, Reg3, Reg4);	//Reg8 changed to Reg4, P+ 2.28 fix
									LWZ(Reg3, Reg3, 0x4C);

									FCTIWZ(0, 1);
									STFD(0, 1, -0x30);
									LWZ(Reg4, 1, -0x2C);
									STW(Reg4, Reg3, 0x18);
									ADDI(Reg1, Reg4, 1);

									STW(Reg1, Reg3, 0x1C);
									LWZ(Reg3, CharacterBufferReg, 0x3C);
									LWZ(Reg3, Reg3, 0x60);
									LWZ(Reg3, Reg3, 0xD8);
									LWZ(Reg3, Reg3, 0x38);
									LWZ(Reg3, Reg3, 0x40);
									STFS(1, Reg3, 0xC);

									LWZ(3, CharacterBufferReg, CHR_BUFFER_HEAD_OF_FIGHTER_OFFSET);
									CallBrawlFunc(0x8083ae24); //getOwner
									LWZ(3, 3, 0);
									STFS(1, 3, 0x24);


									
									/*LWZ(3, CharacterBufferReg, CHR_BUFFER_HEAD_OF_FIGHTER_OFFSET);
									CallBrawlFunc(0x8083ae24); //getOwner
									//SetRegister(4, 1);
									ConvertFloatingRegToInt(1, Reg1, 0);
									CallBrawlFunc(0x8081bdcc); //set damage

									LoadWordToReg(Reg3, 0x805A02D0);
									LBZ(Reg4, Reg2, 3); //player num
									MULLI(Reg4, Reg4, 4);
									ADD(Reg3, Reg3, Reg4);
									LWZ(Reg3, Reg3, 0x4C);

									ADDI(4, Reg1, 1);
									If(Reg1, GREATER_I, 999); {
										SetRegister(4, 998);
									}EndIf();
									MR(3, Reg3);
									SetRegister(5, 0);
									CallBrawlFunc(0x800e14a4); //updateDamageHP

									MR(4, Reg1);
									MR(3, Reg3);
									SetRegister(5, 1);
									CallBrawlFunc(0x800e14a4); //updateDamageHP*/


									
								}EndIf(); EndIf();
							}EndIf();
						}EndIf();
					}EndIf(); EndIf();
				}

				if (CHARACTER_SELECT_P1_INDEX != -1) {
					If(OpenFlagReg, EQUAL_I, CODE_MENU_CLOSING); {
						GetArrayValueFromIndex(CHARACTER_SWITCHER_ARRAY_LOC, Reg8, 0, 3); {
							LWZ(5, 3, Line::VALUE); //get setting
							STW(5, 3, Line::DEFAULT);
							LWZ(Reg2, CharacterBufferReg, CHR_BUFFER_INFO_PTR_OFFSET);
							RLWINM(5, 5, 2, 0, 31); //<<2
							LBZ(4, Reg2, 0); //get current ID
							ADDI(5, 5, Selection::SELECTION_LINE_OFFSETS_START + 2);
							LWZ(Reg1, 3, Selection::SELECTION_LINE_SOURCE_SELECTION_INDEX);
							LHZX(5, Reg1, 5);
							If(4, NOT_EQUAL, 5); { // If the New ID and Old ID don't match...
								SetRegister(Reg1, 0);
								STB(5, Reg2, 0); // Overwrite Old ID with New one
								// This seems to trigger a line at 0x809463C4 in "processBegin/[stLoaderPlayer]/st_loader_player.o" (0x80954350 in Ghidra)
								// which ultimately leads to the line:
								//		(*(code *)this->vtable->stLoaderPlayer$$removeEntity)(this); Starting @ 0x809543d4 in Ghidra
								// This, I assume, is the thing that kills the entity and prompts spawning the new one.
								// There's *also*, however, 0x80946358 (Ghidra: 0x809542e4), which directly checks whether or not the Slot ID
								// recorded in the PlayerInitStruct is different from the currently selected one, along with some other conditions.
								// If so, then we run the following:
								//		(*(code *)this->vtable->stLoaderPlayer$$removeEntity)(this); Starting @ 0x8095431c in Ghidra
								// Either one of these could be the thing responsible for ultimately causing the change to happen,
								// not sure which it is for sure.
								// In either case, should end up calling "removeEntity/[stLoaderPlayer]" 0x80948da8 (0x80956d34 in Ghidra)
								// Messing with the r3 value at 0x809463C4 does prompt a reload
								// Messing with the r0 value at 0x80946358 DOES NOT! Neither in SSE, nor in VS

								SetRegister(Reg3, 0x43AD8);
								LoadWordToReg(Reg4, 0x805A00E0); // Get ptr to GameGlobal Struct
								LWZ(Reg4, Reg4, 0x10); // Get ptr to gmSelCharData (0x90180b40 in testing)
								ADD(Reg4, Reg4, Reg3); // Add 0x43AD8 to addr of this struct (901c4618)? Way beyond the listed range in Ghidra
								LWZ(Reg3, CharacterBufferReg, CHR_BUFFER_PORT_OFFSET); // Get port for character to change...
								MULLI(Reg3, Reg3, 0x5C); // ... and multiply it by 0x5C, probably to index into a list of entries
								STWX(Reg1, Reg4, Reg3); // Write 0 into (&gmSelCharData + 0x43AD8 + OffsetIntoListForTargetPort), Setting to 1 gives RAlt?

								STB(Reg1, Reg2, 5); // force costume to 0
								STB(Reg1, Reg2, 6); // force HUD to 0
							}EndIf();
						}EndIf(); EndIf();
					}EndIf();
				}

				if (INFINITE_SHIELDS_P1_INDEX != -1) {
					GetArrayValueFromIndex(INIFINITE_SHIELDS_ARRAY_LOC, Reg8, 0, 3); {
						LWZ(3, 3, Line::VALUE);
						If(3, EQUAL_I, 1); {
							LWZ(Reg1, CharacterBufferReg, CHR_BUFFER_VARIABLES_ADDRESS_OFFSET);
							SetRegister(Reg2, 0x42700000);
							STW(Reg2, Reg1, 0x19C);
						}EndIf();
					}EndIf(); EndIf();
				}

				LWZU(CharacterBufferReg, MainBufferReg, 8);
			}EndWhile();
		}EndIf();
	}EndIf();

	If(OpenFlagReg, EQUAL_I, CODE_MENU_CLOSING); {
		LoadWordToReg(3, 4, PREV_CODE_MENU_CONTROL_FLAG);
		STW(3, 4, CODE_MENU_CONTROL_FLAG - PREV_CODE_MENU_CONTROL_FLAG);
	}EndIf();

	if (AUTO_SAVE_REPLAY_INDEX != -1) {
		LoadWordToReg(Reg3, IS_REPLAY_LOC);
		SetRegister(Reg2, AUTO_SAVE_REPLAY_FLAG_LOC);
		If(Reg3, EQUAL_I, 2); {
			STW(Reg3, Reg2, 0); //set flag
		}EndIf();
		LoadWordToReg(Reg1, AUTO_SAVE_REPLAY_INDEX + Line::VALUE);
		If(Reg1, NOT_EQUAL_I, 1); {
			SetRegister(Reg1, 0);
			STW(Reg1, Reg2, 0); //clear flag
		}EndIf();
	}

	if (SAVE_REPLAY_ANYWHERE_INDEX != -1) {
		If(OpenFlagReg, EQUAL_I, CODE_MENU_CLOSING); {
			SetRegister(Reg2, SAVE_REPLAY_ANYWHERE_INDEX);
			LWZ(Reg1, Reg2, Line::VALUE);
			If(Reg1, EQUAL_I, 1); {
				SetRegister(Reg1, 0);
				LBZ(Reg3, Reg2, Line::COLOR);
				STW(Reg1, Reg2, Line::VALUE); //clear setting
				ANDI(Reg3, Reg3, ~8);
				STB(Reg3, Reg2, Line::COLOR);

				IfInGame(3, false); {
					SaveReplay();
				}EndIf();
			}EndIf();
		}EndIf();
	}

	//stage collisions
	LoadByteToReg(Reg1, 0x80583FF8 + 1);
	If(Reg1, EQUAL_I, 2);
	{
		SetRegister(Reg2, 1);
		SetRegister(Reg3, SHOULD_RESET_STAGE_COLLISIONS_FLAG_LOC);
		STW(Reg2, Reg3, 0);
	} Else();
	{
		LoadWordToReg(Reg2, Reg3, SHOULD_RESET_STAGE_COLLISIONS_FLAG_LOC);
		If(Reg2, EQUAL_I, 1);
		{
			SetRegister(Reg2, 0);
			STW(Reg2, Reg3, 0);
			
			//reset
			SetRegister(3, 0x80672f40);
			SetRegister(4, 0);
			SetRegister(5, 1);
			CallBrawlFunc(0x8000d234); //setLayerDispStatus
			ADDI(Reg1, Reg1, 1);
		} EndIf();
	} EndIf();


	//hitbox display
	LoadByteToReg(Reg1, 0x80583FFC + 1);
	If(Reg1, EQUAL_I, 2);
	{
		SetRegister(Reg2, 1);
		SetRegister(Reg3, SHOULD_RESET_HITBOX_DISPLAY_FLAG_LOC);
		STW(Reg2, Reg3, 0);
	} Else();
	{
		LoadWordToReg(Reg2, Reg3, SHOULD_RESET_HITBOX_DISPLAY_FLAG_LOC);
		If(Reg2, EQUAL_I, 1);
		{
			SetRegister(Reg2, 0);
			STW(Reg2, Reg3, 0);

			//reset
			SetRegister(Reg1, 1);
			While(Reg1, LESS_OR_EQUAL_I, 5);
			{
				SetRegister(3, 0x80672f40);
				MR(4, Reg1);
				SetRegister(5, 1);
				CallBrawlFunc(0x8000d234); //setLayerDispStatus
				ADDI(Reg1, Reg1, 1);
			} EndWhile();
		} EndIf();
	} EndIf();
	

	//can't trust register values after here
	//need to change when save states are active again
	if (SAVE_STATES_INDEX != -1) {
		LoadWordToReg(Reg1, IS_IN_GAME_FLAG);
		If(Reg1, EQUAL_I, 1); {
			//LoadWordToReg(OpenFlagReg, CODE_MENU_CONTROL_FLAG);
			If(OpenFlagReg, EQUAL_I, CODE_MENU_CLOSED); {
				ANDI(Reg1, ButtonReg, BUTTON_DL);
				If(Reg1, NOT_EQUAL_I, 0); {
					SaveState();
				}Else(); {
					ANDI(Reg1, ButtonReg, BUTTON_DR);
					If(Reg1, NOT_EQUAL_I, 0); {
						RestoreState();
					}EndIf();
				}EndIf();
			}EndIf();
		}EndIf();
	}

	Label(NotLoaded);

	RestoreRegisters();
	BLR();

	// Beginning of Subroutines
	ModifyLineValueSubroutine();
	ResetLineSubroutine(Reg1);

	ASMEnd();
}

void ApplyMenuSetting(int Index, int Destination, int reg1, int reg2, int size)
{
	if (Index != -1) {
		LoadWordToReg(reg1, Index + Line::VALUE);
		SetRegister(reg2, Destination);
		if (size == 4) { STW(reg1, reg2, 0); }
		if (size == 2) { STH(reg1, reg2, 0); }
		if (size == 1) { STB(reg1, reg2, 0); }
	}
}

/* 
// This was written as a test of the new Switch Statement implementation!
// I'd hoped this would shake out to be smaller, but it actually winds up a fair bit larger unfortunately.
// Still an interesting exploration, and a good demo of how the Switch system is used, so I'm leaving this here.
void switchTest_ExecuteAction(int ActionReg)
{
	int PageReg = 4;
	int LineReg = 5;
	int TempReg1 = 6;
	int TypeReg = 7;
	int TempReg2 = 8;
	int TempReg3 = 9;
	int TempReg4 = 10;
	int TempReg5 = 11;
	int TempReg6 = 12;

	LoadWordToReg(PageReg, CURRENT_PAGE_PTR_LOC);
	LWZ(LineReg, PageReg, Page::CURRENT_LINE_OFFSET);
	ADD(LineReg, LineReg, PageReg);
	LBZ(TypeReg, LineReg, Line::TYPE);
	ADDI(TempReg1, 0, 0);
	ADDIS(TempReg2, 0, START_OF_CODE_MENU_HEADER >> 0x10);

	switchTable<8> menuActionSwitch;
	menuActionSwitch.init(ActionReg, 10, 11, 12);
	menuActionSwitch.caseStart(MOVE_DOWN);
	{
		ADDI(TempReg1, 0, 1);
		menuActionSwitch.caseEnd();
	}
	menuActionSwitch.caseStart(MOVE_UP);
	{
		Move(LineReg, PageReg, TempReg1, TempReg2, TempReg3);
		menuActionSwitch.caseBreak();
	}
	menuActionSwitch.caseStart(DECREMENT);
	{
		ADDI(TempReg1, 0, 1);
		menuActionSwitch.caseEnd();
	}
	menuActionSwitch.caseStart(INCREMENT);
	{
		JumpToLabel(ModifyLineValueSubroutineLabel, bCACB_UNSPECIFIED, 1);
		menuActionSwitch.caseBreak();
	}
	menuActionSwitch.caseStart(ENTER_SUB_MENU);
	{
		CMPLI(TypeReg, SUB_MENU_LINE, 0);
		JumpToLabel(menuActionSwitch.getCaseLabel(INCREMENT), bCACB_NOT_EQUAL);
		EnterMenu(LineReg, PageReg, TypeReg, TempReg1, TempReg2);
		menuActionSwitch.caseBreak();
	}
	menuActionSwitch.caseStart(RESET_LINE);
	{
		ORI(TempReg1, TempReg2, RESET_LINES_STACK_LOC & 0xFFFF);
		ResetLine(LineReg, PageReg, TempReg1, TypeReg, TempReg2, TempReg3, TempReg4, 0);
		menuActionSwitch.caseBreak();
	}
	menuActionSwitch.caseStart(RESET_PAGE);
	{
		ORI(TempReg1, TempReg2, RESET_LINES_STACK_LOC & 0xFFFF);
		PushOnStack(PageReg, TempReg1, TempReg2);
		ResetPage(TempReg1, TempReg2, TempReg3, TempReg4, TempReg5, TempReg6, 3);
		menuActionSwitch.caseBreak();
	}
	menuActionSwitch.caseStart(LEAVE_SUB_MENU);
	{
		LeaveMenu(PageReg, TempReg1, TempReg2, TempReg3, TempReg4, TempReg5, TempReg6, ActionReg);
		menuActionSwitch.caseEnd();
	}
	menuActionSwitch.defaultStart(); menuActionSwitch.defaultEnd();
	menuActionSwitch.finalize();

	If(ActionReg, EQUAL_I_L, EXIT_MENU);
	{
		SetRegister(TempReg1, CODE_MENU_CLOSING);
		ORI(TempReg2, TempReg2, CODE_MENU_CONTROL_FLAG & 0xFFFF);
		STW(TempReg1, TempReg2, 0);
		ExitMenu();
	}EndIf();
}
*/

void ExecuteAction(int ActionReg, int ResetAccumulatorReg)
{
	int LineReg = 3;
	int TypeReg = 4;
	int PageReg = 5;

	int TempReg1 = 6;
	int TempReg2 = 7;
	int TempReg3 = 8;
	int TempReg4 = 9;
	int TempReg5 = 10;
	int TempReg6 = 11;
	int TempReg7 = 12;

	int retryActionLabel = GetNextLabel();
	int abortActionLabel = GetNextLabel();

	Label(retryActionLabel);
	LoadWordToReg(PageReg, CURRENT_PAGE_PTR_LOC);
	LWZ(LineReg, PageReg, Page::CURRENT_LINE_OFFSET);
	ADD(LineReg, LineReg, PageReg);
	LBZ(TypeReg, LineReg, Line::TYPE);

	//move
	int doMoveLabel = GetNextLabel();
	If(ActionReg, EQUAL_I, MOVE_UP); {
		//move up
		LHZ(TempReg1, LineReg, Line::UP);

		JumpToLabel(doMoveLabel);
	}EndIf();
	If(ActionReg, EQUAL_I, MOVE_DOWN); {
		//move down
		LHZ(TempReg1, LineReg, Line::DOWN);

		Label(doMoveLabel);
		// Attempt the move...
		Move(LineReg, PageReg, TempReg1, TempReg2, TempReg3);
		// ... and compare the line we landed on with the current line.
		CMPL(LineReg, TempReg1, 0);
		// If we landed back in the same place, this is the only selectable line on the page, so abort the move.
		JumpToLabel(abortActionLabel, bCACB_EQUAL);

		// Otherwise, if we did land on a new line, grab its flag byte...
		LBZ(TempReg1, TempReg2, Line::FLAGS);
		// ... and see if it's hidden from printing. If so...
		ANDI(TempReg1, TempReg1, Line::LINE_FLAG_HIDE_FROM_USER);
		// ... then we want to skip over it instead of selecting it, so we'll just retry the move!
		JumpToLabel(retryActionLabel, bCACB_NOT_EQUAL);

		// If we've successfully moved, we can now play the sound for moving to a different line.
		ADDI(4, 0, sii_SND_SE_SYSTEM_CURSOR);
		JumpToLabel(getPlaySELabel(), bCACB_UNSPECIFIED, 1);
	}EndIf();

	//change value
	// Assume by default that we're gonna increment here, so set r6 to 0!
	ADDI(6, 0, 0);
	// And if action is INCREMENT or ENTER_SUB_MENU...
	CMPLI(ActionReg, INCREMENT, 0);
	CMPLI(ActionReg, ENTER_SUB_MENU, 1);
	CROR(EQ, EQ, crBitInCRF(EQ, 1));
	// ... then branch.
	JumpToLabel(ModifyLineValueSubroutineLabel, bCACB_EQUAL, 1);
	
	// If we're decrementing though set r6 so we decrement instead...
	ADDI(6, 0, 1);
	// ... and attempt the branch!
	CMPLI(ActionReg, DECREMENT, 0);
	JumpToLabel(ModifyLineValueSubroutineLabel, bCACB_EQUAL, 1);

	//navigate menu
	If(ActionReg, EQUAL_I, ENTER_SUB_MENU); {
		EnterMenu(LineReg, PageReg, TypeReg, TempReg1, TempReg2);
	}EndIf();

	If(ActionReg, EQUAL_I, LEAVE_SUB_MENU); {
		LeaveMenu(PageReg, TempReg1, TempReg2, TempReg3, TempReg4, TempReg5, TempReg6, ActionReg);
	}EndIf();

	If(ActionReg, EQUAL_I, EXIT_MENU); {
		SetRegister(TempReg1, CODE_MENU_CLOSING);
		SetRegister(TempReg2, CODE_MENU_CONTROL_FLAG);
		STW(TempReg1, TempReg2, 0);
		ExitMenu();

		// Play sound for closing menu.
		ADDI(4, 0, sii_SND_SE_SYSTEM_PLATE_CATCH);
		JumpToLabel(getPlaySELabel(), bCACB_UNSPECIFIED, 1);
	}EndIf();

	// --- Reset Actions! ---
	// These are last because the ResetPage code modifies the Line, Type, and Page registers.
	// Attempting to perform an action after that without first reacquiring those registers' values will cause undefined behavior!
	// Set Stack Pointer, since we'll need this for all of what we're about to do.
	SetRegister(7, RESET_LINES_STACK_LOC);
	// Also zero the reset line accumulator, we need this to know whether to play the reset sound afterwards!
	ADDI(ResetAccumulatorReg, 0, 0);

	// If we're resetting a line...
	CMPLI(ActionReg, RESET_LINE, 0);
	// ... then set IsIndirect to 0 (since we're resetting the line directly)...
	ADDI(6, 0, 0);
	// ... and call the subroutine. Importantly, if the current line is a subpage, it'll get pushed onto the reset stack!
	JumpToLabel(ResetLineSubroutineLabel, bCACB_EQUAL, 1);

	// If we instead are resetting a page...
	If(ActionReg, EQUAL_I, RESET_PAGE); {
		// ... then push the current page's ptr onto the reset stack.
		PushOnStack(PageReg, 7, 8);
	}EndIf();

	// Iterate through any pages on the reset stack, and reset the lines therein!
	// Note: This modifes the Line, Type, and Page registers as it iterates; don't add actions beneath this unless you reload those values!
	ResetPage();

	// If the Reset Accumulator is non-zero, in one of the previous actions we reset a line!
	CMPLI(ResetAccumulatorReg, 0, 0);
	// Queue up the reset sound's ID...
	ADDI(4, 0, sii_SND_SE_SYSTEM_CANCEL);
	// ... and play it if the Accumulator wasn't 0 (ie. the previous check against 0 returned not equal).
	JumpToLabel(getPlaySELabel(), bCACB_NOT_EQUAL, 1);

	Label(abortActionLabel);
}

// r3 = LineReg, r4 = LineTypeReg, r5 = PageReg, r6 = IsIndirectReg, r7 = StackReg, r8 - r12 = Work Regs (modifed)
int ResetLineSubroutineLabel = INT_MAX;
void ResetLineSubroutine(int ResetAccumulatorReg)
{
	int LineReg = 3;
	int TypeReg = 4;
	int PageReg = 5;
	int IsIndirectReg = 6;
	int StackReg = 7;

	int TempReg1 = 8;
	int TempReg2 = 9;
	int TempReg3 = 10;

	Label(ResetLineSubroutineLabel);

	int notIndirectLabel = GetNextLabel();
	int setPageLineColorLabel = GetNextLabel();

	// Grab Line Color early, since whether we're direct or not we'll need it for setting the page color!
	LBZ(TempReg2, LineReg, Line::COLOR);

	LBZ(TempReg3, LineReg, Line::FLAGS);
	ANDI(TempReg1, TempReg3, Line::LINE_FLAG_VALUE_LOCKED);
	JumpToLabel(setPageLineColorLabel, bCACB_NOT_EQUAL);

	CMPLI(IsIndirectReg, 1, 0);
	JumpToLabel(notIndirectLabel, bCACB_NOT_EQUAL);
	ANDI(TempReg1, TempReg3, Line::LINE_FLAG_IGNORE_INDIRECT_RESET);
	JumpToLabel(setPageLineColorLabel, bCACB_NOT_EQUAL);

	Label(notIndirectLabel);
	LWZ(TempReg1, PageReg, Page::NUM_CHANGED_LINES);
	
	// Load the changed bit of the line's color into TempReg3, will be 1 if changed, 0 otherwise.
	RLWINM(TempReg3, TempReg2, 29, 31, 31);
	ANDI(TempReg2, TempReg2, ~0x8);
	SUBF(TempReg1, TempReg1, TempReg3);
	STB(TempReg2, LineReg, Line::COLOR);
	STW(TempReg1, PageReg, Page::NUM_CHANGED_LINES);

	If(TypeReg, LESS_OR_EQUAL_I, HAS_VALUE_LIMIT); {
		// Add the changed bit to the ResetAccumulator to tally that a line's value was reset.
		ADD(ResetAccumulatorReg, ResetAccumulatorReg, TempReg3);
		LWZ(TempReg1, LineReg, Line::DEFAULT);
		STW(TempReg1, LineReg, Line::VALUE);
	}Else(); If(TypeReg, EQUAL_I, SUB_MENU_LINE); {
		LHZ(TempReg1, LineReg, Line::SUB_MENU);
		ADD(TempReg1, TempReg1, PageReg);
		PushOnStack(TempReg1, StackReg, TempReg3);
	}EndIf(); EndIf();

	Label(setPageLineColorLabel);
	// Load the current page's submenu line...
	LWZ(TempReg3, PageReg, Page::CALLED_FROM_LINE);
	// ... and if no such line existed...
	CMPI(TempReg3, 0xFFFF, 0);
	// ... then return early to skip the below.
	BCLR(bCACB_EQUAL);
	// Otherwise though, grab that line's color value...
	LBZ(TempReg1, TempReg3, Line::COLOR);
	// ... and isolate the changed bit.
	ANDI(TempReg2, TempReg2, 0x8);
	// OR that into the parent page's line color...
	OR(TempReg1, TempReg1, TempReg2);
	// ... and write it into place!
	STB(TempReg1, TempReg3, Line::COLOR);

	BLR();
}

// r7 = StackReg, r3 - r6, r8 - r12 = Work Regs (modifed)
void ResetPage()
{
	int LineReg = 3;
	int TypeReg = 4;
	int PageReg = 5;
	int IsIndirectReg = 6;
	int StackReg = 7;

	int ItrReg1 = 12;

	// Set IsIndirect flag to 1 (we only need to do this once, we guarantee that the register won't be modified in the loop.
	ADDI(IsIndirectReg, 0, 1);

	// Iterate through each page address pushed onto the stack (skipping of course if there are none).
	IterateStack(PageReg, StackReg, ItrReg1);
	{
		// Point LineReg to this page's first line.
		ADDI(LineReg, PageReg, Page::FIRST_LINE_OFFSET); 
		// Get this first line's size, only do loop if that size isn't 0 (ie. line exists).
		LHZ(ItrReg1, LineReg, Line::SIZE);
		// Then iterate through each line in the page.
		While(ItrReg1, NOT_EQUAL_I, 0); 
		{
			// Load the line's Type into TypeReg
			LBZ(TypeReg, LineReg, Line::TYPE);
			// ... and call the ResetLine Subroutine!
			JumpToLabel(ResetLineSubroutineLabel, bCACB_UNSPECIFIED, 1);

			// Use the Size in ItrReg to push LineReg to next line, and load that next line's size.
			LHZUX(ItrReg1, LineReg, ItrReg1); 
		}EndWhile();
	}IterateStackEnd();
}

void ExitMenu()
{
	LoadWordToReg(3, OLD_DEBUG_STATE_LOC);
	SetRegister(4, IS_DEBUG_PAUSED);
	STW(3, 4, 0);
}

void EnterMenu(int LineReg, int PageReg, int TypeReg, int TempReg1, int TempReg2)
{
	If(TypeReg, EQUAL_I, SUB_MENU_LINE); {
		LHZ(TempReg1, LineReg, SubMenu::SUB_MENU);
		ADD(TempReg2, PageReg, TempReg1);
		NEG(TempReg1, TempReg1);
		STW(TempReg1, TempReg2, Page::PREV_PAGE);
		SetRegister(TempReg1, CURRENT_PAGE_PTR_LOC);
		STW(TempReg2, TempReg1, 0);

		// Play sound for entering page.
		ADDI(4, 0, sii_SND_SE_SYSTEM_PAGE_CHANGE);
		JumpToLabel(getPlaySELabel(), bCACB_UNSPECIFIED, 1);
	}EndIf();
}

void LeaveMenu(int PageReg, int TempReg1, int TempReg2, int TempReg3, int TempReg4, int TempReg5, int TempReg6, int ActionReg)
{
	LWZ(TempReg1, PageReg, Page::PREV_PAGE);
	ADD(TempReg2, PageReg, TempReg1);
	SetRegister(TempReg1, CURRENT_PAGE_PTR_LOC);
	STW(TempReg2, TempReg1, 0);

	//reg2 == super page
	LWZ(TempReg1, TempReg2, Page::CURRENT_LINE_OFFSET);
	ADD(TempReg1, TempReg1, TempReg2); //super page current line
	LBZ(TempReg3, TempReg1, Line::COLOR); //color of super line
	RLWINM(TempReg4, TempReg3, 29, 31, 31);
	LWZ(TempReg5, TempReg2, Page::NUM_CHANGED_LINES); //super page num changed lines
	ANDI(TempReg3, TempReg3, ~0x8);
	SUBF(TempReg5, TempReg5, TempReg4);
	LWZ(TempReg4, PageReg, Page::NUM_CHANGED_LINES);
	SetRegister(TempReg6, 0);
	ANDI(TempReg4, TempReg4, 0x1F);
	BC(2, bCACB_EQUAL);
	SetRegister(TempReg6, 1);
	ADD(TempReg5, TempReg5, TempReg6);
	RLWINM(TempReg6, TempReg6, 3, 0, 31); //<<3
	STW(TempReg5, TempReg2, Page::NUM_CHANGED_LINES);
	OR(TempReg3, TempReg3, TempReg6);
	STB(TempReg3, TempReg1, Line::COLOR);

	// Play sound for leaving page.
	ADDI(4, 0, sii_SND_SE_SYSTEM_CURSOR_L);
	JumpToLabel(getPlaySELabel(), bCACB_UNSPECIFIED, 1);
}

// r3 = LineReg, r4 = LineTypeReg, r5 = PageReg, r6 = DoDecrReg, r7 - r12 = Work Regs (modifed)
int ModifyLineValueSubroutineLabel = INT_MAX;
void ModifyLineValueSubroutine()
{
	int LineReg = 3;
	int TypeReg = 4;
	int PageReg = 5;
	// 0 = Incr, 1 = Decr
	int DoDecrReg = 6;

	int TempReg1 = 12;
	int TempReg2 = 11;
	int TempReg3 = 10;
	int TempReg4 = 9;
	int TempReg5 = 8;

	int TempFReg1 = 1;
	int TempFReg2 = 2;
	int TempFReg3 = 3;

	int exitLabel = GetNextLabel();

	Label(ModifyLineValueSubroutineLabel);

	// First, check that this line is a type which has an actual value to change.
	CMPLI(TypeReg, HAS_VALUE_LIMIT, 0);
	// If not, skip to the end of the subroutine.
	JumpToLabel(exitLabel, bCACB_GREATER);

	// Also check if the value lock bit is set...
	LBZ(TempReg1, LineReg, Line::FLAGS);
	ANDI(TempReg1, TempReg1, Line::LINE_FLAG_VALUE_LOCKED);
	// ... and if so, also skip to the end of the subroutine.
	JumpToLabel(exitLabel, bCACB_NOT_EQUAL);

	// Pre-compare the Change Direction into CR7, since we need it for every case.
	CMPLI(DoDecrReg, 0, 7);

	If(TypeReg, EQUAL_I, FLOATING_LINE);
	{
		// Load the Current Value and Speed as Floats...
		LFS(TempFReg1, LineReg, Line::VALUE);
		LFS(TempFReg2, LineReg, Floating::SPEED);
		// ... and apply the requested operation.
		// If we're subtracting instead of adding...
		BC(2, bCACB_EQUAL.inConditionRegField(7));
		// ... then negate the Speed value before we add, so we subtract instead!
		FNEG(TempFReg2, TempFReg2);
		// And actually do the addition.
		FADDS(TempFReg3, TempFReg1, TempFReg2);

		// Then clamp the value between the Min and Max!
		// Load the relevant values...
		LFS(TempFReg1, LineReg, Floating::MIN);
		LFS(TempFReg2, LineReg, Floating::MAX);
		// If we're below the Minimum...
		FCMPU(TempFReg3, TempFReg1, 1);
		BC(2, bCACB_GREATER_OR_EQ.inConditionRegField(1));
		// ... then set Value to Maximum!
		FMR(TempFReg3, TempFReg2);
		// And if we're above the Maximum...
		FCMPU(TempFReg3, TempFReg2, 1);
		BC(2, bCACB_LESSER_OR_EQ.inConditionRegField(1));
		// ... then set Value to Minimum!
		FMR(TempFReg3, TempFReg1);

		// And store the result to apply it!
		STFS(TempFReg3, LineReg, Line::VALUE);
	}
	Else();
	{
		// Load the line's current value.
		LWZ(TempReg1, LineReg, Line::VALUE);
		// Prepare our Speed and Min values (initializing to 1 and 0, respectively, to accommodate Selection lines).
		ADDI(TempReg2, 0, 1);
		ADDI(TempReg3, 0, 0);

		// If we *aren't* looking at a Selection line though...
		CMPLI(TypeReg, SELECTION_LINE, 0);
		BC(3, bCACB_EQUAL);
		// ... we'll grab the actual Speed and Min values from the line itself!
		LWZ(TempReg2, LineReg, Line::SPEED);
		LWZ(TempReg3, LineReg, Line::MIN);

		// Now apply the actual operation.
		// If we're subtracting instead of adding...
		BC(2, bCACB_EQUAL.inConditionRegField(7));
		// ... then negate the Speed value before we add, so we subtract instead!
		NEG(TempReg2, TempReg2);
		// And actually do the addition.
		ADD(TempReg1, TempReg1, TempReg2);

		// Then clamp the value between the Min and Max!
		// We don't need the Speed value anymore, so we'll load the Max over it.
		LWZ(TempReg2, LineReg, Line::MAX);

		// First, if we're below the Minimum...
		CMP(TempReg1, TempReg3, 0);
		BC(2, bCACB_GREATER_OR_EQ);
		// ... then set Value to the Maximumum to wrap back around!
		MR(TempReg1, TempReg2);
		// And if we're above the Maximum...
		CMP(TempReg1, TempReg2, 0);
		BC(2, bCACB_LESSER_OR_EQ);
		// ... then set Value to the Minimum to wrap back around!
		MR(TempReg1, TempReg3);

		// And store the result to apply it!
		STW(TempReg1, LineReg, Line::VALUE);
	}
	EndIf();

	//set changed flag
	LWZ(TempReg1, LineReg, Line::VALUE);
	LBZ(TempReg2, LineReg, Line::COLOR);
	LWZ(TempReg3, LineReg, Line::DEFAULT);
	LWZ(TempReg5, PageReg, Page::NUM_CHANGED_LINES);
	RLWINM(TempReg4, TempReg2, 29, 31, 31);
	ANDI(TempReg2, TempReg2, ~0x8);
	If(TempReg1, NOT_EQUAL, TempReg3);
	{
		//not default
		Increment(TempReg5);
		ORI(TempReg2, TempReg2, 0x8);
	}
	EndIf();
	SUBF(TempReg5, TempReg5, TempReg4);
	STB(TempReg2, LineReg, Line::COLOR);
	STW(TempReg5, PageReg, Page::NUM_CHANGED_LINES);

	ADDI(4, 0, sii_SND_SE_SYSTEM_COUNTER);
	JumpToLabel(getPlaySELabel(), bCACB_UNSPECIFIED, 0);

	Label(exitLabel);
	BLR();
}

// Returns New Line Address in TempReg1!
void Move(int LineReg, int PageReg, int NextLineOffset, int TempReg1, int TempReg2) {
	LBZ(TempReg2, LineReg, Line::COLOR);
	XORI(TempReg2, TempReg2, 0x4);
	STB(TempReg2, LineReg, Line::COLOR);

	STW(NextLineOffset, PageReg, Page::CURRENT_LINE_OFFSET);

	ADD(TempReg1, NextLineOffset, PageReg);
	LBZ(TempReg2, TempReg1, Line::COLOR);
	XORI(TempReg2, TempReg2, 0x4);
	STB(TempReg2, TempReg1, Line::COLOR);
}

void GetActionFromInputs(int ButtonReg, int ControlStickXReg, int ControlStickYReg, int ResultReg)
{
	//action checks at the bottom have a higher priority
	SetRegister(ResultReg, NO_ACTION); //default

	//set Z for fast
	int notZPressLabel = GetNextLabel();
	ANDI(4, ButtonReg, BUTTON_Z);
	JumpToLabel(notZPressLabel, bCACB_EQUAL);
	//set frame timers to 3
	LoadWordToReg(4, 7, MOVE_FRAME_TIMER_LOC);
	LoadWordToReg(6, 8, INCREMENT_FRAME_TIMER_LOC);
	SetRegister(5, 3);
	If(4, GREATER, 5); {
		STW(5, 7, 0);
	}EndIf();
	If(6, GREATER, 5); {
		STW(5, 8, 0);
	}EndIf();
	Label(notZPressLabel);

	// D-Pad Move Up
	ANDI(4, ButtonReg, BUTTON_DU);
	BC(2, bCACB_EQUAL);
	ADDI(ControlStickYReg, 0, MOVE_THRESHHOLD);

	// D-Pad Move Down
	ANDI(4, ButtonReg, BUTTON_DD);
	BC(2, bCACB_EQUAL);
	ADDI(ControlStickYReg, 0, -MOVE_THRESHHOLD);

	SetControlStickAction(ControlStickYReg, MOVE_FRAME_TIMER_LOC, MOVE_NUM_WAIT_FRAMES, FIRST_MOVE_NUM_WAIT_FRAMES, MOVE_THRESHHOLD, MOVE_UP, MOVE_DOWN, ResultReg);

	// D-Pad Increment
	ANDI(4, ButtonReg, BUTTON_DR);
	BC(2, bCACB_EQUAL);
	ADDI(ControlStickXReg, 0, INCREMENT_THRESHHOLD);

	// D-Pad Decrement
	ANDI(4, ButtonReg, BUTTON_DL);
	BC(2, bCACB_EQUAL);
	ADDI(ControlStickXReg, 0, -INCREMENT_THRESHHOLD);

	SetControlStickAction(ControlStickXReg, INCREMENT_FRAME_TIMER_LOC, INCREMENT_NUM_WAIT_FRAMES, FIRST_INCREMENT_NUM_WAIT_FRAMES, INCREMENT_THRESHHOLD, INCREMENT, DECREMENT, ResultReg);


	// Reset Line
	ANDI(4, ButtonReg, TRIGGER_RESET_LINE_BUTTON);
	BC(2, bCACB_EQUAL);
	ADDI(ResultReg, 0, RESET_LINE);

	// Leave Sub Menu
	ANDI(4, ButtonReg, TRIGGER_RESET_PAGE_BUTTON);
	BC(2, bCACB_EQUAL);
	ADDI(ResultReg, 0, RESET_PAGE);

	// Enter Sub Menu
	ANDI(4, ButtonReg, TRIGGER_ENTER_SUB_MENU_BUTTON);
	BC(2, bCACB_EQUAL);
	ADDI(ResultReg, 0, ENTER_SUB_MENU);

	// Leave Sub Menu
	int exitMenuInstrLabel = GetNextLabel();
	int notLeaveSubMenuLabel = GetNextLabel();
	ANDI(4, ButtonReg, TRIGGER_LEAVE_SUB_MENU_BUTTON);
	JumpToLabel(notLeaveSubMenuLabel, bCACB_EQUAL);
	// Assume by default we're just leaving a sub menu.
	ADDI(ResultReg, 0, LEAVE_SUB_MENU);
	// But we also need to support closing the menu if we're on the main page!
	// Grab pointers to the currnet page and main page...
	ADDIS(4, 0, MAIN_PAGE_PTR_LOC >> 0x10);
	LWZ(5, 4, CURRENT_PAGE_PTR_LOC & 0xFFFF);
	LWZ(4, 4, MAIN_PAGE_PTR_LOC & 0xFFFF);
	// ... compare them...
	CMPL(4, 5, 0);
	// ... and if they're the same, overriding the action!
	JumpToLabel(exitMenuInstrLabel, bCACB_EQUAL);
	Label(notLeaveSubMenuLabel);

	// Leave Menu
	ANDI(4, ButtonReg, BUTTON_START);
	BC(2, bCACB_EQUAL);
	Label(exitMenuInstrLabel);
	ADDI(ResultReg, 0, EXIT_MENU);
}

void SetControlStickAction(int StickValReg, int TimerLoc, int NumWaitFrames, int FirstTimeNumWaitFrames, int Threshhold, int PositiveAction, int NegativeAction, int ResultReg)
{
	int FrameTimerReg = 6;
	LoadWordToReg(FrameTimerReg, 7, TimerLoc);
	ABS(8, StickValReg, 3);
	Decrement(FrameTimerReg);
	If(8, GREATER_OR_EQUAL_I, Threshhold); {
		If(FrameTimerReg, LESS_OR_EQUAL_I, 0); {
			If(FrameTimerReg, LESS_I, 0); {
				//first move
				SetRegister(FrameTimerReg, FirstTimeNumWaitFrames - NumWaitFrames);
			}EndIf();
			ADDI(FrameTimerReg, FrameTimerReg, NumWaitFrames + 1);
			SetRegister(ResultReg, NegativeAction);
			If(StickValReg, GREATER_OR_EQUAL_I, Threshhold); {
				SetRegister(ResultReg, PositiveAction);
			}EndIf();
		}EndIf();
	}Else(); {
		SetRegister(FrameTimerReg, 0);
	}EndIf();
	STW(FrameTimerReg, 7, 0);
}

void printFPS() {
	int reg1 = 31;
	int reg2 = 30;
	int reg3 = 29;
	int reg4 = 28;
	int reg5 = 27;
	int reg6 = 26;
	int reg7 = 25;
	int reg8 = 24;
	int fontHolderReg = 23;
	int fontHolderReg2 = 22;

	LoadWordToReg(reg1, FPS_DISPLAY_INDEX + Line::VALUE);
	If(reg1, EQUAL_I, 1);
	{
		SetRegister(reg1, 0);
		LWZ(fontHolderReg, 13, -0x42AC); //save font ptr if exist
		LWZ(fontHolderReg2, 13, -0x42A8); //save other font ptr if exist
		STW(reg1, 13, -0x42AC); //clear font ptr
		STW(reg1, 13, -0x42A8); //clear other font ptr

		SetRegister(reg1, STRING_BUFFER + 0x80);
		WriteStringToMem("FPS: %2d", reg1);
		LoadHalfToReg(reg2, 0x805a0856);
		SprintF(reg1, { reg2 });
		SetRegister(reg1, STRING_BUFFER - 1);
		MR(reg6, 3);
		SetRegister(reg3, DRAW_SETTINGS_BUFFER_LOC);

		SetupPrintText(reg3);

		SetRegs(3, { (int) 0x805B71F0, 0 });
		CallBrawlFunc(0x801f51dc);

		
		SetRegister(reg4, 0x805b6df8);
		LFS(1, reg4, 0); //scale factor

		SetFloatingRegister(2, reg4, 0.33);
		FMULS(2, 2, 1);
		STFS(2, reg3, 0x50); //size

		/*SetFloatingRegister(2, reg4, -160.0);
		FDIVS(2, 2, 1);
		STFS(2, reg3, DRAW_BUFFER_XPOS_OFFSET); //x pos

		SetFloatingRegister(2, reg4, -128.0);
		FDIVS(2, 2, 1);
		STFS(2, reg3, DRAW_BUFFER_YPOS_OFFSET); //y pos*/


		//SetRegister(reg4, GetHexFromFloat(0.10));
		//SetRegister(reg4, GetHexFromFloat(0.15));
		//STW(reg4, reg3, 0x50); //set size

		//set initial text pos
		SetRegister(reg4, GetHexFromFloat(-165));
		SetRegister(reg5, GetHexFromFloat(-115));
		//SetRegister(reg4, GetHexFromFloat(-192));
		//SetRegister(reg5, GetHexFromFloat(-128));
		SetTextPos(reg4, reg5, reg3);

		LoadHalfToReg(reg4, 0x805a0856);
		If(reg2, LESS_I, 60);
		{
			SetRegister(reg2, RED);
		} Else();
		{
			SetRegister(reg2, BLUE);
		} EndIf();
		SetTextColor(reg2, reg3);

		STW(fontHolderReg, 13, -0x42AC);
		STW(fontHolderReg2, 13, -0x42A8);
		PrintString(reg1, reg6, reg3);
	} EndIf();

}

void PrintCodeMenu()
{
	ASMStart(0x80017928, "[CM: Code Menu] Print Code Menu");
	SaveRegisters(14);

	int Reg1 = 31;
	int Reg2 = 30;
	int Reg3 = 29;
	int Reg4 = 28;
	int Reg5 = 27;
	int Reg6 = 26;
	int Reg7 = 25;
	int Reg8 = 24;

	LoadWordToReg(Reg1, CODE_MENU_CONTROL_FLAG);
	LoadWordToReg(Reg2, Reg4, OLD_CAMERA_POS_LOC);
	OR(Reg3, Reg1, Reg2);
	If(Reg3, GREATER_OR_EQUAL_I, CODE_MENU_OPEN); {
		//code menu is open, or old camera pos is not 0
		SetRegister(Reg3, 0x805b6d20);
		LoadWordToReg(4, 5, CODE_MENU_NEED_TO_SAVE_CAMERA_MATRIX_FLAG_LOC);
		If(4, EQUAL_I, 0);
		{
			SetRegister(6, 1);
			STW(6, 5, 0);
			SetRegister(Reg2, CODE_MENU_OLD_CAMERA_MATRIX_LOC);
			SetRegister(6, 4 * 12);
			Memmove(Reg2, Reg3, 6);
		} EndIf();
		WriteVectorToMem(DEFAULT_CAMERA_MATRIX, Reg3);
		DrawBlackBackground();
	}EndIf();

	If(Reg1, EQUAL_I, CODE_MENU_OPEN); {
		SetRegister(Reg2, 0x805b6df8);
		SetRegister(Reg1, 0x3eb2b8c2);
		STW(Reg1, Reg2, 0);

		LoadWordToReg(Reg1, CURRENT_PAGE_PTR_LOC);
		SetRegister(Reg2, DRAW_SETTINGS_BUFFER_LOC);
		PrintPage(Reg1, Reg2, Reg3, Reg4, Reg5, Reg6, Reg7, Reg8);
	}Else(); {
		If(Reg2, NOT_EQUAL_I, 0); {
			//need to reset camera and wait a frame
			SetRegister(Reg3, 0x805b6df8);
			SetRegister(Reg1, 0);
			STW(Reg2, Reg3, 0); //reset camera
			STW(Reg1, Reg4, 0); //clear saved camera

			SetRegister(3, 0x805b6d20);
			SetRegister(4, CODE_MENU_OLD_CAMERA_MATRIX_LOC);
			SetRegister(Reg2, 4 * 12);
			Memmove(3, 4, Reg2);
			SetRegister(3, 0);
			SetRegister(4, CODE_MENU_NEED_TO_SAVE_CAMERA_MATRIX_FLAG_LOC);
			STW(3, 4, 0);
		}Else(); {
			//printFPS();
			CallBrawlFunc(0x8002e844); //render
			if (FPS_DISPLAY_INDEX != -1) {
				printFPS();
			}
		}EndIf();
	}EndIf();

	RestoreRegisters();
	ASMEnd();
}

void PrimeCodeMenu()
{
	GeckoIf(0x8119969c, EQUAL, 0x9421fff0);
	//r3 + 0x40 has location
	ASMStart(0x8119969c, "[CM: Code Menu] Prime Code Menu");
	SaveRegisters();

	int Reg1 = 31;
	int Reg2 = 30;
	int Reg3 = 29;
	int Reg4 = 28;
	int Reg5 = 27;
	int Reg6 = 26;
	int Reg7 = 25;
	int Reg8 = 24;

	LWZ(Reg3, 3, 0x54);
	If(Reg3, EQUAL_I, 1); {
		LWZ(Reg3, 3, 0x40);
		If(Reg3, EQUAL_I, 8); {
			//on tourney
			LoadWordToReg(Reg1, Reg2, CODE_MENU_CONTROL_FLAG);
			If(Reg1, NOT_EQUAL_I, CODE_MENU_OPEN); {
				SetRegister(Reg2, CODE_MENU_CONTROL_FLAG);
				SetRegister(Reg1, CODE_MENU_PRIMED);
				STW(Reg1, Reg2, 0);
			}EndIf();
		}EndIf();
	} EndIf();
	

	SetRegister(Reg2, ON_GROUP_RECORDS_FLAG_LOC);
	SetRegister(Reg1, 0);
	If(Reg3, EQUAL_I, 0x4E); {
		//SetRegister(Reg1, 1);
	}EndIf();
	STW(Reg1, Reg2, 0);

	RestoreRegisters();
	ASMEnd(0x9421fff0); //stwu sp, sp, -0x10
	GeckoEndIf();
}

void SetTextColor(int ColorReg, int SettingsPtrReg)
{
	STW(ColorReg, SettingsPtrReg, 0x8);
	STW(ColorReg, SettingsPtrReg, 0xC);
	STW(ColorReg, SettingsPtrReg, 0x10);
	STW(ColorReg, SettingsPtrReg, 0x14);
}

void SetTextXPos(int XPosReg, int SettingPtrReg)
{
	STW(XPosReg, SettingPtrReg, DRAW_BUFFER_XPOS_OFFSET);
}

void SetTextYPos(int YPosReg, int SettingPtrReg)
{
	STW(YPosReg, SettingPtrReg, DRAW_BUFFER_YPOS_OFFSET);
}

void SetTextPos(int XPosReg, int YPosReg, int SettingPtrReg)
{
	SetTextXPos(XPosReg, SettingPtrReg);
	SetTextYPos(YPosReg, SettingPtrReg);
}

void SetTextSize(int FPSizeReg, int SettingsPtrReg)
{
	STFS(FPSizeReg, SettingsPtrReg, 0x50);
}

void NewLine(int SettingsPtrReg)
{
	SetRegister(3, GetHexFromFloat(INITIAL_XPOS));
	LFS(0, SettingsPtrReg, DRAW_BUFFER_YPOS_OFFSET);
	SetFloatingRegister(1, 4, LINE_HEIGHT);
	FADD(0, 0, 1);
	STW(3, SettingsPtrReg, DRAW_BUFFER_XPOS_OFFSET);
	STFS(0, SettingsPtrReg, DRAW_BUFFER_YPOS_OFFSET);
}

//r3 is SettingsPtr, r4 is CharReg
void PrintChar(int SettingsPtrReg, int CharReg)
{
	SetArgumentsFromRegs(3, { SettingsPtrReg, CharReg });
	CallBrawlFunc(0x8006fe50); //printChar
}

//StringPtr should be 1 less than start
//StringPtr gets moved to end of string, numCharsReg gets set to 0
void PrintString(int StringPtrReg, int NumCharsReg, int SettingsPtrReg)
{
	While(NumCharsReg, GREATER_I, 0); //print loop

	LBZU(4, StringPtrReg, 1);
	PrintChar(SettingsPtrReg, 4);

	Decrement(NumCharsReg);
	EndWhile(); //print loop
}

void SetupPrintText(int SettingPtrReg)
{
	ADDI(3, SettingPtrReg, 0);
	SetRegs(4, { 0, 9 });
	CallBrawlFunc(0x8006a964); //SetDefaultEnv

	CallBrawlFunc(0x80019FA4); //(getManager[cameraManager])

	CallBrawlFunc(0x80018DE4); //(setGX[camera])

	SetRegister(3, DRAW_SETTINGS_BUFFER_LOC + 0x48);
	SetRegister(4, 0x80497e44);
	STW(4, 3, 0); //set font
}

void DrawBlackBackground()
{
	CallBrawlFunc(0x80019FA4); //(getManager[cameraManager])

	CallBrawlFunc(0x80018DE4); //(setGX[camera])

	CallBrawlFunc(0x8001A5C0); //gfDrawSetVtxColorPrimEnvrment

	vector<float> positions;
	float size = 0x1000;
	positions.push_back(-size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(size);
	positions.push_back(-size);
	positions.push_back(-size);
	positions.push_back(-size);
	DrawPrimitive(PRIMITIVE_QUAD, positions, BLACK, 1);
}

void getSelectedLineNum(int PageReg, int resultReg) {
	LWZ(resultReg, PageReg, Page::CURRENT_LINE_OFFSET);
	ADD(resultReg, PageReg, resultReg); //ptr to selected line
	LBZ(resultReg, resultReg, Line::LINE_NUM);
}

void getNewHold(int PageReg, int resultReg, int reg1, int reg2) {
	LWZ(resultReg, PageReg, Page::PRINT_LOW_HOLD);
	getSelectedLineNum(PageReg, reg1);
	If(reg1, GREATER, resultReg);
	{
		MR(resultReg, reg1);
	} Else();
	{
		ADDI(reg2, reg1, SCROLL_DISTANCE - 5);
		If(reg2, LESS, resultReg);
		{
			MR(resultReg, reg2);
		} EndIf();
	} EndIf();
}

void PrintPage(int PageReg, int SettingsPtrReg, int Reg1, int Reg2, int Reg3, int Reg4, int Reg5, int Reg6)
{
	SetupPrintText(SettingsPtrReg);

	SetRegister(Reg5, LINE_COLOR_TABLE.table_start());

	//set initial text pos
	SetRegister(Reg1, GetHexFromFloat(INITIAL_XPOS));
	SetRegister(Reg2, GetHexFromFloat(INITIAL_YPOS));
	getNewHold(PageReg, Reg4, Reg6, Reg3);
	STW(Reg4, PageReg, Page::PRINT_LOW_HOLD); //save

	If(Reg4, GREATER_I, SCROLL_DISTANCE);
	{
		ADDI(Reg3, Reg4, -SCROLL_DISTANCE);
		MULLI(Reg3, Reg3, -LINE_HEIGHT);
		ConvertIntToFloat(Reg3, Reg4, Reg6);
		SetRegister(Reg3, STRING_BUFFER);
		STW(Reg6, Reg3, 0);
		LFS(0, Reg3, 0);
		STW(Reg2, Reg3, 0);
		LFS(1, Reg3, 0);
		FADDS(0, 0, 1);
		STFS(0, Reg3, 0);
		LWZ(Reg2, Reg3, 0);
	} EndIf();

	SetTextPos(Reg1, Reg2, SettingsPtrReg);

	SetRegister(Reg1, GetHexFromFloat(0.06));
	STW(Reg1, SettingsPtrReg, 0x50); //set size

	ADDI(Reg2, PageReg, Page::FIRST_LINE_OFFSET); //first line
	SetRegister(3, 1);
	While(3, NOT_EQUAL_I, 0); {
		PrintCodeMenuLine(Reg2, SettingsPtrReg, Reg5, Reg3, Reg4);

		LHZ(3, Reg2, Line::SIZE);
		LHZUX(3, Reg2, 3);
	}EndWhile();
}

void PrintCodeMenuLine(int LinePtrReg, int SettingsPtrReg, int ColorArrayPtrReg, int TempReg1, int TempReg2)
{
	int skipPrintingLabel = GetNextLabel();
	// Load flag byte to TempReg2!
	LBZ(TempReg2, LinePtrReg, Line::FLAGS);
	// If the flag for hiding a line is active...
	ANDI(TempReg1, TempReg2, Line::LINE_FLAG_HIDE_FROM_USER);
	// ... skip printing it!
	JumpToLabel(skipPrintingLabel, bCACB_NOT_EQUAL);

	// If we are printing, then instead check if the flag for locking a line is active, storing result in CR0.
	int skipToLoadColorLabel = GetNextLabel();
	ANDI(TempReg1, TempReg2, Line::LINE_FLAG_VALUE_LOCKED);
	// Load current color byte.ss
	LBZ(TempReg1, LinePtrReg, Line::COLOR);
	// If the line isn't locked, just use the color as is.
	JumpToLabel(skipToLoadColorLabel, bCACB_EQUAL);
	// Otherwise though, convert it to the Locked variant of the given color!
	ADDI(TempReg1, TempReg1, LOCKED_NORMAL_LINE_COLOR_OFFSET);
	Label(skipToLoadColorLabel);
	LWZX(TempReg1, ColorArrayPtrReg, TempReg1);
	LBZ(TempReg2, LinePtrReg, Line::TYPE);
	SetTextColor(TempReg1, SettingsPtrReg);

	LHZ(4, LinePtrReg, Line::TEXT_OFFSET);
	ADD(4, 4, LinePtrReg);

	If(TempReg2, EQUAL_I, PRINT_LINE); {
		LWZ(TempReg1, LinePtrReg, Line::PRINT_LINE_NUM_ARGS);
		LHZ(TempReg2, LinePtrReg, Line::SIZE);
		MULLI(TempReg1, TempReg1, 4);
		SUBF(TempReg2, TempReg2, TempReg1);
		LSWX(5, TempReg2, LinePtrReg, TempReg1);

		SetRegister(3, STRING_BUFFER);
		WriteIntToFile(0x4cc63182); //clclr 6, 6
		CallBrawlFunc(0x803f89fc); //sprintf
	} Else(); If(TempReg2, EQUAL_I, FLOATING_LINE); {
		LFS(1, LinePtrReg, Line::VALUE);
		SprintF(4, {},  { 1 }, -1);
	} Else(); {
		LWZ(5, LinePtrReg, Line::VALUE); //get setting

		If(TempReg2, EQUAL_I, SELECTION_LINE); {
			LWZ(TempReg2, LinePtrReg, Selection::SELECTION_LINE_SOURCE_SELECTION_INDEX);
			ADDI(TempReg1, TempReg2, Selection::SELECTION_LINE_OFFSETS_START);
			RLWINM(5, 5, 2, 0, 31); //<< 2
			LHZX(5, TempReg1, 5); //get string offset
			ADD(5, 5, TempReg2); //get string offset
		}EndIf();

		SprintF(4, { 5 });
	} EndIf(); EndIf();

	MR(TempReg2, 3); //num chars
	SetRegister(TempReg1, STRING_BUFFER - 1);
	PrintString(TempReg1, TempReg2, SettingsPtrReg);

	NewLine(SettingsPtrReg);

	Label(skipPrintingLabel);
}

//requires 2 endifs
void GetArrayValueFromIndex(int ArrayLoc, int IndexReg, int min, int max, int ResultReg)
{
	If(IndexReg, LESS_OR_EQUAL_I, max); {
		If(IndexReg, GREATER_OR_EQUAL_I, min); {
			RLWINM(4, IndexReg, 2, 0, 31); //<< 2
			SetRegister(ResultReg, ArrayLoc - (min * 4));
			LWZX(ResultReg, ResultReg, 4);
		}
	}
}

void SaveReplay()
{
	int NTEBufferReg = 31;
	int SectionBufferReg = 30;
	int HighTimeReg = 29;
	int LowTimeReg = 28;
	int CryptoBufferReg = 27;
	int PathPtrReg = 26;
	int reg1 = 25;
	int reg2 = 24;
	int reg3 = 23;
	int reg4 = 22;
	int reg5 = 21;
	int reg6 = 20;
	int reg7 = 19;

#if DOLPHIN_BUILD
	SetRegister(reg5, STRING_BUFFER);
	WriteStringToMem("nand:/collect.vff\0"s, reg5);
	SetRegs(3, { DOLPHIN_MOUNT_VF_LOC, 0, STRING_BUFFER });
	CallBrawlFunc(0x80020f90); //mountVF
	SetRegs(3, { 0, 607500 * 3});
	CallBrawlFunc(0x801e1a80); //OSSleepTicks
#endif

	//set buffer ptrs
	SetRegister(NTEBufferReg, REPLAY_NTE_DATA_BUFFER_LOC);
	SetRegister(SectionBufferReg, REPLAY_CREATE_SECTION_BUFFER_LOC);
	SetRegister(CryptoBufferReg, REPLAY_CRYPTO_BUFFER_LOC);

	//setup buffers
	//section buffer
	SetRegister(3, 0);
	STW(3, SectionBufferReg, 0);
	STW(3, SectionBufferReg, 4);
	vector<int> is = { 0x4e0341de, (int) 0xe6bbaa41, 0x6419b3ea, (int) 0xe8f53bd9 };
	//crypto buffer
	vector<int> stupid = is;
	WriteVectorToMem(stupid, CryptoBufferReg);
	SetRegister(3, 0x2A);
	SetRegister(4, 1);
	STW(3, CryptoBufferReg, 0x18);
	STW(4, CryptoBufferReg, 0x1C);

	CallBrawlFunc(0x801e1b34); //OSGetTime
	MR(HighTimeReg, 3);
	MR(LowTimeReg, 4);

	SetRegs(3, { REPLAY_NTE_DATA_BUFFER_LOC, 42 });
	CallBrawlFunc(0x80152b5c); //ctnteFileReplay

	GetHeapAddress(HEAP_ADDRESS_TABLE.CACHED_REPLAY_HEAP, 4);
	ADDI(4, 4, REPLAY_HEAP_REPLAY_BUFFER_BEGIN_OFF);
	CallBrawlFunc(0x80152c4c); //setData

	SetArgumentsFromRegs(3, { SectionBufferReg, NTEBufferReg, HighTimeReg, LowTimeReg });
	SetRegs(7, { 0x2A, 0, 0 });
	CallBrawlFunc(0x80153610); //createSection

	LWZ(3, SectionBufferReg, 0);
	STW(3, CryptoBufferReg, 0x10);
	LWZ(3, 3, 0x1C);
	ADDI(3, 3, 0x20);
	STW(3, CryptoBufferReg, 0x14);
	ADDI(3, CryptoBufferReg, -832);
#if DOLPHIN_BUILD == false
	CallBrawlFunc(0x8003d1cc); //run crypto
#endif
	
	SetRegister(PathPtrReg, STRING_BUFFER + 0xA0);
	//WriteStringToMem("/LegacyTE/rp/rp_%d%d.bin\0"s, PathPtrReg);
	//SprintF(PathPtrReg, { HighTimeReg, LowTimeReg });
	SetRegister(reg1, STRING_BUFFER);
	SetArgumentsFromRegs(3, { HighTimeReg, LowTimeReg, reg1 });
	CallBrawlFunc(0x801e1d80); //OSTicksToCalenderTime
	LWZ(reg7, reg1, 0); //second
	LWZ(reg2, reg1, 4); //minute
	LWZ(reg3, reg1, 8); //hour
	LWZ(reg4, reg1, 0xC); //day
	LWZ(reg5, reg1, 0x10); //month
	LWZ(reg6, reg1, 0x14); //year
	ADDI(reg5, reg5, 1);
	SetRegister(3, 100);
	MR(4, reg6);
	MOD(reg6, 4, 3);
#if DOLPHIN_BUILD
	WriteStringToMem("/rp/rp_%02d%02d%02d_%02d%02d_%02d.bin\0"s, PathPtrReg);
#else
	WriteStringToMem("/" + MAIN_FOLDER + "/rp/rp_%02d%02d%02d_%02d%02d_%02d.bin\0"s, PathPtrReg);
#endif
	SprintF(PathPtrReg, { reg6, reg5, reg4, reg3, reg2, reg7 });
	SetRegister(PathPtrReg, STRING_BUFFER);
#if DOLPHIN_BUILD
	LWZ(reg2, SectionBufferReg, 0);
	LWZ(reg1, reg2, 0x1C);
	ADDI(reg1, reg1, 0x20);
#else
	LWZ(reg1, CryptoBufferReg, 0x2C); //size
	LWZ(reg2, CryptoBufferReg, 0x28); //ptr
#endif
	SetRegister(reg3, 0x2000);
	Allocate(reg3);
	MR(reg3, 1);
	ADDI(1, 3, 0x1F00);
	MR(reg4, 3);

#if DOLPHIN_BUILD
	int tryWriteLabel = GetNextLabel();
	int writeFinishedLabel = GetNextLabel();

	// Initialize a counter for how many times we're allowed to try loading.
	ADDI(reg7, 0, 0x8);

	Label(tryWriteLabel);
	WriteFileToVF(PathPtrReg, reg1, reg2);
	// If writing the replay succeeded, we can continue.
	CMPLI(3, 0x00, 0);
	JumpToLabel(writeFinishedLabel, bCACB_EQUAL);
	// If not, decrement our retry counter...
	ADDIC(reg7, reg7, -1, 1);
	// ... and if the counter winds up below 0, we're out of tries, give up.
	JumpToLabel(writeFinishedLabel, bCACB_LESSER);
	// Otherwise though, we need to retry. Wait for a while...
	SetRegs(3, { 0, 607500 * 3 });
	CallBrawlFunc(0x801e1a80); //OSSleepTicks
	// ... then try the write again.
	JumpToLabel(tryWriteLabel);

	// Once we're done though, unmount and prepare to exit.
	Label(writeFinishedLabel);
	SetRegs(3, { DOLPHIN_MOUNT_VF_LOC, 0 });
	CallBrawlFunc(0x80021038); //unmountVF
	SetRegister(reg1, 0);
	SetRegister(reg2, DOLPHIN_MOUNT_VF_LOC);
	STW(reg1, reg2, 0);
#else
	WriteFileToSD(PathPtrReg, reg1, reg2);
#endif
	MR(1, reg3);
	FreeMem(reg4);

	//deallocate
	MR(3, NTEBufferReg);
	SetRegister(4, 0);
	CallBrawlFunc(0x80152bdc); //dtnteFileReplay
	LWZ(reg1, CryptoBufferReg, 0x28);
	FreeMem(reg1);
	LWZ(reg1, SectionBufferReg, 0);
	FreeMem(reg1);
}

//requires 3 endifs
//r3 returns setting address
void RunIfPortToggle(int ARRAY_LOC, int PortReg) {
	GetArrayValueFromIndex(ARRAY_LOC, PortReg, 0, 3); {
		LWZ(5, 3, Line::VALUE); //get setting
		If(5, EQUAL_I, 1); {
		}
	}
}

