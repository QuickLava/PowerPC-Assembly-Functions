#ifndef XML_PROCESSING_H_V1
#define XML_PROCESSING_H_V1

#include "stdafx.h"
#include "Code Menu.h"
#include "pugi/pugixml.hpp"
#include "_lavaBytes.h"
#include <conio.h>
#include <filesystem>

class Page;
class Line;

namespace xml
{
	// ==================== Menu Config Parsing and Constants =====================

	// Parses the specified Configuration XML and applies any changes it requests to the menu.
	bool parseAndApplyConfigXML(std::string configFilePath, lava::outputSplitter& logOutput);

	// ============================================================================

	// =======================  Addon Parsing and Constants =======================

	// Enumeration of the xml-definable line fields.
	enum lineFields
	{
		lf_ValDefault = 0,
		lf_ValMin,
		lf_ValMax,
		lf_Speed,
		lf_Options,
		lc__COUNT
	};
	typedef std::array<bool, lineFields::lc__COUNT> fieldChangeArr;

	// Addon Type Forward Decl
	struct addon;

	// A bundle which holds the details for an addon line!
	struct addonLine
	{
		// Fullname used for display and logging purposes.
		std::string lineName = "";
		// Shortname used for linking.
		lava::shortNameType shortName = "";
		int INDEX = INT_MAX;
		std::shared_ptr<Line> linePtr = nullptr;
		fieldChangeArr populated{};

		u32 overrideAddr = 0x00;
		ConstantPair::dataSize overrideDataSize = ConstantPair::ds_WORD;

	private:
		void buildSubmenuLine(const pugi::xml_node& sourceNode);
		void buildIntegerLine(const pugi::xml_node& sourceNode);
		void buildFloatLine(const pugi::xml_node& sourceNode);
		void buildToggleLine(const pugi::xml_node& sourceNode);
		void buildSelectionLine(const pugi::xml_node& sourceNode);
		void buildSelectionMirrorLine(const pugi::xml_node& sourceNode, const addon* parentAddon);
		void buildCommentLine(const pugi::xml_node& sourceNode);
	public:
		addonLine() {};
		bool populate(const pugi::xml_node& sourceNode, lava::outputSplitter& logOutput, const addon* parentAddon = nullptr);
	};
	struct addonPageTarget
	{
		// Shortname used for linking.
		lava::shortNameType shortName = "";
		// Collected lines in order.
		std::vector<std::shared_ptr<addonLine>> lines{};
		// Map of line shortnames to their structs.
		std::map<lava::shortNameType, std::shared_ptr<addonLine>> lineMap{};

		bool populate(const pugi::xml_node& sourceNode, lava::outputSplitter& logOutput, const addon* parentAddon = nullptr);
		bool lineShortNameIsFree(lava::shortNameType nameIn) const;
	};
	struct addon
	{
		// Fullname used for display and logging purposes.
		std::string addonName = "";
		// Shortname used for linking.
		lava::shortNameType shortName = "";
		// Version, for reporting purposes.
		std::string versionName = "";
		// Input Folder.
		std::filesystem::path inputDirPath = "";
		// Maps page shortnames to their structs!
		std::map<lava::shortNameType, addonPageTarget> targetPages{};
		// The amount of extra memory to set aside for this addon.
		std::size_t workingMemorySize = 0x00;
		// Denotes where this addons' line INDEX values start in memory.
		std::size_t baseLOC = SIZE_MAX;
		// Denotes whether we need to create an INDEX file in the output directory for this addon.
		bool needsINDEXFile = 0;

		addon() {};
		bool populate(std::string inputDirPathIn, lava::outputSplitter& logOutput);
		std::filesystem::path getInputXMLPath();
		std::filesystem::path getInputASMPath();
		std::filesystem::path getOutputDirPath();
		std::filesystem::path getBuildASMPath();

		void writeEmbedsToMenuFileAndBank(std::ostream& menuFile, std::ostream& aliasBankFile);
		bool generateINDEXFile();
	};
	constexpr unsigned long c_maxSingleAddonWorkingSpaceSize = 0x400;
	constexpr unsigned long c_maxAddonCount = 0x100;

	extern std::map<lava::shortNameType, std::shared_ptr<Page>> collectedNewPages;
	extern std::vector<addon> collectedAddons;
	// Returns true if a given addon shortname is free to use.
	bool addonShortNameIsFree(lava::shortNameType nameIn);

	// Adds the lines defined in each Addon to their respective pages within the code menu.
	void applyCollectedAddons(lava::outputSplitter& logOutput);
	// Creates space for each Addon's LOC values, and generates the AddonAliases file for referencing those values in code.
	void generateAddonEmbeds(std::ostream& outputStream);
	// Adds .include statements for each Addon's source file to the end of the generated Code Menu .asm file.
	void appendAddonIncludesToASM();
	// Copies the generated Addons folder into it the target build's Source folder.
	bool copyAddonsFolderIntoBuild();

	// ============================================================================


	// ==================== Menu Options Parsing and Constants ====================

	// Incoming Configuration XML Variables (See "Code Menu.cpp" for defaults, and "_XMLProcessing.cpp" for relevant Config Parsing code!)
	extern std::vector<std::string> CONFIG_INCOMING_COMMENTS;
	extern bool CONFIG_DELETE_CONTROLS_COMMENTS;
	extern bool CONFIG_PSCC_ENABLED;
	extern bool CONFIG_DASH_ATTACK_ITEM_GRAB_ENABLED;
	extern bool CONFIG_JUMPSQUAT_OVERRIDE_ENABLED;
	extern bool CONFIG_DISPLAY_TAG_HEX_ENABLED;

	void applyLineSettingsFromMenuOptionsTree(Page& mainPageIn, const pugi::xml_document& xmlDocumentIn, lava::outputSplitter& logOutput);
	bool applyLineSettingsFromMenuOptionsTree(Page& mainPageIn, std::string xmlPathIn, lava::outputSplitter& logOutput);
	bool buildMenuOptionsTreeFromMenu(Page& mainPageIn, std::string xmlPathOut);
}

#endif

