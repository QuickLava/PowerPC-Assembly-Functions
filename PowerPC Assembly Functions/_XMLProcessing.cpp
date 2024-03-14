#include "stdafx.h"
#include "_XMLProcessing.h"

namespace xml
{
	// ==================== Menu Config Parsing and Constants =====================

	// Config XML Parsing Constants
	namespace configXMLConstants
	{
		// Debug
		const std::string _debugOptionsTag = "debugOptions";
		const std::string _implicitOptimizationsTag = "allowImplicitOptimizations";
		const std::string _allowBLAFuncCalls = "allowBLAFuncCalls";
		const std::string _deleteASMTxtTag = "deleteASMTxt";
		const std::string _asmDictTag = "makeASMDictionary";
		const std::string _disableDisassemmblerTag = "disableDisassembler";
		const std::string _enableASMHexCommentsTag = "enableASMHexComments";

		// General
		const std::string codeMenuTag = "codeMenu";
		const std::string menuConfigTag = "codeMenuConfig";
		const std::string cmnuPathTag = "cmnuPath";
		const std::string enabledTag = "enabled";
		const std::string editableTag = "editable";
		const std::string nameTag = "name";
		const std::string textTag = "text";
		const std::string filenameTag = "filename";
		const std::string codeModeTag = "codeMode";
		const std::string indexTag = "index";
		const std::string valueTag = "value";
		const std::string flagTag = "flag";
		const std::string callbackTag = "callback";

		// Line Values
		const std::string menuLinePageTag = "codeMenuPage";
		const std::string menuLineSubmenuTag = "codeMenuSubmenu";
		const std::string menuLineSelectionTag = "codeMenuSelection";
		const std::string menuLineToggleTag = "codeMenuToggle";
		const std::string menuLineIntTag = "codeMenuInt";
		const std::string menuLineFloatTag = "codeMenuFloat";
		const std::string menuLineCommentTag = "codeMenuComment";
		const std::string speedTag = "speed";
		const std::string valueMinTag = "minValue";
		const std::string valueMaxTag = "maxValue";
		const std::string valueDefaultTag = "defaultValue";
		const std::string selectionDefaultTag = "defaultOption";
		const std::string selectionOptionTag = "option";

		// Line Behavior Flag Tags
		struct lbfTagVec : std::vector<std::string>
		{
			lbfTagVec()
			{
				resize(Line::LineBehaviorFlags::lbf__COUNT, "BAD_TAG");
				(*this)[Line::LineBehaviorFlags::lbf_UNSELECTABLE] = "locked";
				(*this)[Line::LineBehaviorFlags::lbf_HIDDEN] = "hidden";
				(*this)[Line::LineBehaviorFlags::lbf_STICKY] = "sticky";
				(*this)[Line::LineBehaviorFlags::lbf_REMOVED] = "excluded";
			}
		} const lineBehaviorFlagTags;


		// Menu Properties
		const std::string menuPropsTag = "menuProperties";
		const std::string baseFolderTag = "buildBaseFolder";
		const std::string menuTitleTag = "menuTitle";
		const std::string menuCommentsTag = "menuComments";
		const std::string commentTag = "comment";
		const std::string deleteOrigCommentsTag = "deleteControlsComments";

		// Line Colors
		const std::string menuLineColorsTag = "menuLineColors";
		const std::string lineColorTag = "lineColor";
		const std::string lineKindTag = "lineKind";
		const std::string colorHexTag = "colorHex";

		// EX Characters
		const std::string characterListTag = "characterList";
		const std::string baseCharListTag = "baseListVersion";
		const std::string characterTag = "character";
		const std::string slotIDTag = "slotID";

		// Code Settings
		const std::string codeSettingsTag = "codeSettings";

		// EX Rosters
		const std::string roseterDeclsTag = "rosterChanger";
		const std::string rosterTag = "roster";

		// Themes
		const std::string themeDeclsTag = "themeChanger";
		const std::string themeTag = "menuTheme";
		const std::string themeFileTag = "themeFile";
		const std::string prefixTag = "replacementPrefix";

		// Dash Attack Item Grab
		const std::string dashAttackItemGrabTag = "vBrawlItemGrab";

		// PSCC
		const std::string slotColorDeclsTag = "slotColorChanger";
		const std::string colorTag = "color";
		const std::string colorDefsTag = "colorDefinitions";
		const std::string colorP1Tag = "colorP1";
		const std::string colorP2Tag = "colorP2";
		const std::string colorP3Tag = "colorP3";
		const std::string colorP4Tag = "colorP4";
		const std::string colorHueTag = "hue";
		const std::string colorSatTag = "saturation";
		const std::string colorLumTag = "luminance";
		const std::string colorSchemeTag = "scheme";
		const std::string colorSchemeDefsTag = "schemeDefinitions";
		const std::string colorSchemeMenu1Tag = "menuColor1";
		const std::string colorSchemeMenu2Tag = "menuColor2";
		const std::string colorSchemeIngame1Tag = "ingameColor1";
		const std::string colorSchemeIngame2Tag = "ingameColor2";
		const std::vector<std::string> colorFlagNames =
		{
			"InvertHueMod",
			"DisableHueMod",
			"DisableSatModUp",
			"DisableSatModDown",
			"DisableLumModUp",
			"DisableLumModDown",
		};

		// Jumpsquat Override
		const std::string jumpsquatOverrideTag = "jumpsquatModifier";

		// Addons
		const std::string addonsBlockTag = "addonIncludes";
		const std::string addonTag = "addon";
		const std::string shortnameTag = "shortName";
		const std::string localLOCtag = "localLOC";
	}

	void fixIndentationOfChildNodes(pugi::xml_node& targetNode)
	{
		// Indentation string is gonna be for the children of the current node, so we include a tab to start.
		std::string indentationString = "\n\t";
		// Then for each level up we can go through the parents of this node...
		for (pugi::xml_node_iterator currNode = targetNode.parent(); !currNode->parent().empty(); currNode = currNode->parent())
		{
			// ... add an additional tab!
			indentationString += "\t";
		}

		// Lastly, to apply the fixed indentation string, iterate through every child node...
		for (auto currChild : targetNode.children())
		{
			// ... and if we run into a pcData node...
			if (currChild.type() == pugi::xml_node_type::node_pcdata)
			{
				// ... grab a copy of it's string.
				std::string pcStr = currChild.value();
				// Then, iterate backwards through the string to find the first non-space char...
				auto charItr = pcStr.rbegin();
				for (charItr; charItr != pcStr.rend(); charItr++)
				{
					if (!std::isspace(*charItr)) break;
				}
				// ... and if we wind up finding one...
				if (charItr != pcStr.rend())
				{
					// ... then chop off any whitespace characters, and instead append our indentation string.
					pcStr = std::string(pcStr.begin(), charItr.base()) + indentationString;
				}
				// Otherwise...
				else
				{
					// ... simply overwrite the string with our indentation.
					pcStr = indentationString;
				}
				// And write the result out to the pcData node!
				currChild.set_value(pcStr.c_str());
			}
		}
	}

	bool addOrApplyDebugOptionInNode(pugi::xml_node& debugOptionsNode, const std::string& debugSettingString, bool& destinationBool)
	{
		bool result = 0;

		if (debugOptionsNode)
		{
			pugi::xml_node childNode = debugOptionsNode.child(debugSettingString.c_str());
			if (!childNode)
			{
				result = 1;
				debugOptionsNode.append_child(debugSettingString.c_str()).append_attribute(configXMLConstants::enabledTag.c_str()).set_value(destinationBool);
			}
			else
			{
				destinationBool = childNode.attribute(configXMLConstants::enabledTag.c_str()).as_bool(0);
			}
		}

		return result;
	}
	bool handleDebugOptions(pugi::xml_node& documentRoot)
	{
		bool result = 0;

		pugi::xml_node debugOptionsNode = documentRoot.child(configXMLConstants::_debugOptionsTag.c_str());
		if (debugOptionsNode)
		{
			result |= addOrApplyDebugOptionInNode(debugOptionsNode, configXMLConstants::_asmDictTag, CONFIG_OUTPUT_ASM_INSTRUCTION_DICTIONARY);
			result |= addOrApplyDebugOptionInNode(debugOptionsNode, configXMLConstants::_implicitOptimizationsTag, CONFIG_ALLOW_IMPLICIT_OPTIMIZATIONS);
			result |= addOrApplyDebugOptionInNode(debugOptionsNode, configXMLConstants::_allowBLAFuncCalls, CONFIG_ALLOW_BLA_FUNCTION_CALLS);
			result |= addOrApplyDebugOptionInNode(debugOptionsNode, configXMLConstants::_deleteASMTxtTag, CONFIG_DELETE_ASM_TXT_FILE);
			result |= addOrApplyDebugOptionInNode(debugOptionsNode, configXMLConstants::_disableDisassemmblerTag, CONFIG_DISABLE_ASM_DISASSEMBLY);
			result |= addOrApplyDebugOptionInNode(debugOptionsNode, configXMLConstants::_enableASMHexCommentsTag, CONFIG_ENABLE_ASM_HEX_COMMENTS);
		}
		if (result)
		{
			fixIndentationOfChildNodes(debugOptionsNode);
		}

		return result;
	}

	// Line Color Handling
	bool applyLineColorValues(const pugi::xml_node_iterator& colorDeclNodeItr)
	{
		bool result = 0;

		// Collect any line color entries contained in the node.
		for (pugi::xml_node_iterator colorItr = colorDeclNodeItr->begin(); colorItr != colorDeclNodeItr->end(); colorItr++)
		{
			// If we're looking at a proper line color entry...
			if (colorItr->name() == configXMLConstants::lineColorTag)
			{
				// ... try grabbing the line kind it affects.
				unsigned long lineKind = colorItr->attribute(configXMLConstants::lineKindTag.c_str()).as_uint(ULONG_MAX);
				// If the grabbed kind is within range of the table...
				if (lineKind < LINE_COLOR_TABLE.__COLOR_COUNT)
				{
					// ... then additionally grab the rgba hex from the node.
					unsigned long rgbaIn = colorItr->attribute(configXMLConstants::colorHexTag.c_str()).as_uint(0xDEADBEEF);
					// Provided we've successfully done that as well...
					if (rgbaIn != 0xDEADBEEF)
					{
						// ... set the relevant value in the line color table!
						LINE_COLOR_TABLE.COLORS_ARR[lineKind] = rgbaIn;
						// Additionally, mark that we've successfully set at least one color.
						result = 1;
					}
				}
			}
		}

		return result;
	}

	// EX Character Handling
	// Adds any collected entries to the destination vector, and returns the number of entries collected in this call.
	std::size_t collectEXCharactersFromPlaintext(std::istream& streamIn, std::vector<std::pair<std::string, u16>>& destinationVector)
	{
		std::size_t originalCount = destinationVector.size();

		if (streamIn.good())
		{
			std::string currentLine = "";
			std::string manipStr = "";
			while (std::getline(streamIn, currentLine))
			{
				// Disregard the current line if it's empty, or is marked as a comment
				if (!currentLine.empty() && currentLine[0] != '#' && currentLine[0] != '/')
				{
					// Clean the string
					// Removes any space characters from outside of quotes. Note, quotes can be escaped with \\.
					manipStr = "";
					bool inQuote = 0;
					bool doEscapeChar = 0;
					for (std::size_t i = 0; i < currentLine.size(); i++)
					{
						if (currentLine[i] == '\"' && !doEscapeChar)
						{
							inQuote = !inQuote;
						}
						else if (currentLine[i] == '\\')
						{
							doEscapeChar = 1;
						}
						else if (inQuote || !std::isspace(currentLine[i]))
						{
							doEscapeChar = 0;
							manipStr += currentLine[i];
						}
					}
					// Determines the location of the delimiter, and ensures that there's something before and something after it.
					// Line is obviously invalid if that fails, so we skip it.
					std::size_t delimLoc = manipStr.find('=');
					if (delimLoc != std::string::npos && delimLoc > 0 && delimLoc < (manipStr.size() - 1))
					{
						// Store character name portion of string
						std::string characterNameIn = manipStr.substr(0, delimLoc);
						// Initialize var for character id portion of string
						u16 characterSlotIDIn = SHRT_MAX;
						// Handles hex input for character id
						characterSlotIDIn = lava::stringToNum(manipStr.substr(delimLoc + 1, std::string::npos), 1, SHRT_MAX);
						// Insert new entry into list.
						destinationVector.push_back(std::make_pair(characterNameIn, characterSlotIDIn));
					}
				}
			}
		}

		return destinationVector.size() - originalCount;
	}
	std::vector<std::pair<std::string, u16>> collectEXCharactersFromXML(pugi::xml_node_iterator& characterDeclNodeItr, bool& collectedPlaintextEntry)
	{
		std::vector<std::pair<std::string, u16>> result{};

		// Collect any entries contained in the node.
		for (pugi::xml_node_iterator characterItr = characterDeclNodeItr->begin(); characterItr != characterDeclNodeItr->end(); characterItr++)
		{
			// If we're looking at a proper character node, we can just parse its XML contents as normal.
			if (characterItr->name() == configXMLConstants::characterTag)
			{
				std::pair<std::string, u16> tempPair("", USHRT_MAX);
				tempPair.first = characterItr->attribute(configXMLConstants::nameTag.c_str()).as_string("");
				tempPair.second = characterItr->attribute(configXMLConstants::slotIDTag.c_str()).as_int(USHRT_MAX);

				if (!tempPair.first.empty() && (tempPair.second != USHRT_MAX))
				{
					result.push_back(tempPair);
				}
			}
			// The only other thing we care about are plaintext nodes, since those *could* contain old-school entries.
			else if (characterItr->type() == pugi::node_pcdata)
			{
				// For these, populate a stringstream with the node's text, 
				// and attempt to pull any entries from the text. This'll return the number of nodes, so if it's greater than 0...
				if (collectEXCharactersFromPlaintext(std::stringstream(characterItr->value()), result) > 0)
				{
					// ... then flag that we've collected a plaintext entry...
					collectedPlaintextEntry = 1;
					// ... and delete the plaintext entries!
					characterItr->set_value("");
					// Note: this removes those plaintext entries from the tree, they'll be re-generated later so that they use proper XML syntax!
				}
			}
		}

		return result;
	}
	void addCollectedEXCharactersToMenuLists(const std::vector<std::pair<std::string, u16>>& nameIDPairs, lava::outputSplitter& logOutput)
	{
		// If there are entries to include:
		if (nameIDPairs.size())
		{
			// Builds a map from the predefined character and character ID lists.
			// Doing it this way ensures that paired values stay together, and handles sorting automatically when we insert new entries.
			std::map<std::string, u16> zippedIDMap{};
			zipVectorsToMap(CHARACTER_LIST, CHARACTER_ID_LIST, zippedIDMap);
			std::set<u16> uniqueIDList{};
			uniqueIDList.insert(CHARACTER_ID_LIST.cbegin(), CHARACTER_ID_LIST.cend());

			for (int i = 0; i < nameIDPairs.size(); i++)
			{
				const std::pair<std::string, u16>* currPair = &nameIDPairs[i];

				// If this entry has an invalid ID...
				if (currPair->second == SHRT_MAX)
				{
					// ... report the error...
					logOutput.write("[ERROR] Invalid Slot ID specified! The character \"" + currPair->first + "\" will not be added to the Code Menu!\n",
						ULONG_MAX, lava::outputSplitter::sOS_CERR);
					// ... and skip to next entry!
					continue;
				}

				const std::map<std::string, u16>::const_iterator zipEndItr = zippedIDMap.cend();
				std::map<std::string, u16>::iterator entryWithSameName = zippedIDMap.find(currPair->first);
				std::map<std::string, u16>::iterator entryWithSameID = zippedIDMap.end();
				// If the incoming ID isn't unique, then populate entryWithSameID!
				if (uniqueIDList.find(currPair->second) != uniqueIDList.end())
				{
					// Find the entry already using that ID...
					for (auto zipMapItr = zippedIDMap.begin(); zipMapItr != zipEndItr; zipMapItr++)
					{
						if (zipMapItr->second == currPair->second)
						{
							// ... and write its iterator to entryWithSameID!
							entryWithSameID = zipMapItr;
							break;
						}
					}
				}

				// If both values are unique in this map...
				if ((entryWithSameName == zipEndItr) && (entryWithSameID == zipEndItr))
				{
					// ... we can simply add the entry to the map, and the ID into the set!
					auto insertItr = zippedIDMap.insert(*currPair);
					uniqueIDList.insert(insertItr.first->second);
					// Then report the addition!
					logOutput << "[ADDED] \"" << insertItr.first->first << "\" (Slot ID = 0x" << lava::numToHexStringWithPadding(insertItr.first->second, 2) << ")\n";
				}
				// Otherwise, if only name is unique (so we need to change an existing entry's name)...
				else if (entryWithSameName == zipEndItr)
				{
					// ... then we can record the old name, erase the old entry from the map...
					std::string oldName = entryWithSameID->first;
					zippedIDMap.erase(entryWithSameID);
					// ... and insert our new entry!
					auto insertItr = zippedIDMap.insert(*currPair);
					logOutput << "[CHANGED] \"" << oldName << "\" (Slot ID: 0x" << lava::numToHexStringWithPadding(insertItr.first->second, 2) << "): ";
					logOutput << "Name = \"" << insertItr.first->first << "\"\n";
				}
				// Otherwise, if only ID is unique (so we need to change an existing entry's ID)...
				else if (entryWithSameID == zipEndItr)
				{
					// ... then we can record the old ID, erase the old ID from the set...
					u16 oldID = entryWithSameName->second;
					uniqueIDList.erase(entryWithSameName->second);
					// ... change the ID of the existing entry...
					entryWithSameName->second = currPair->second;
					// ... and add the new ID to the set!
					uniqueIDList.insert(entryWithSameName->second);
					logOutput << "[CHANGED] \"" << entryWithSameName->first << "\" (Slot ID: 0x" << lava::numToHexStringWithPadding(oldID, 2) << "): ";
					logOutput << "Slot ID = 0x" << lava::numToHexStringWithPadding(entryWithSameName->second, 2) << "\n";
				}
				// Otherwise, if neither are unique...
				else
				{
					// ... then we can't do the addition at all! Report the error:
					logOutput << "[ERROR] Unable to process entry \"" <<
						currPair->first << "\" (Slot ID = 0x" << lava::numToHexStringWithPadding(currPair->second, 2) << ")!\n";
					logOutput << "\tName is used by: \"" <<
						entryWithSameName->first << "\" (Slot ID = 0x" << lava::numToHexStringWithPadding(entryWithSameName->second, 2) << ")!\n";
					logOutput << "\tSlot ID is used by: \"" <<
						entryWithSameID->first << "\" (Slot ID = 0x" << lava::numToHexStringWithPadding(entryWithSameID->second, 2) << ")!\n";
				}
			}

			// Write the newly edited list back into the list vectors
			CHARACTER_LIST.clear();
			CHARACTER_ID_LIST.clear();
			unzipMapToVectors(zippedIDMap, CHARACTER_LIST, CHARACTER_ID_LIST);
		}
		else
		{
			logOutput << "[WARNING] Character Declaration block parsed, but no valid entries were found!\n";
		}
	}
	void regenEXCharacterDeclsInXML(pugi::xml_node_iterator& characterDeclNodeItr, const std::vector<std::pair<std::string, u16>>& nameIDPairs)
	{
		// Remove all the proper character nodes from the XML...
		while (characterDeclNodeItr->remove_child(configXMLConstants::characterTag.c_str())) {}

		// And for each nameID pair...
		for (std::size_t i = 0; i < nameIDPairs.size(); i++)
		{
			// ... generate a proper character node for it.
			pugi::xml_node tempCharNode = characterDeclNodeItr->append_child(configXMLConstants::characterTag.c_str());
			tempCharNode.append_attribute(configXMLConstants::nameTag.c_str()) = nameIDPairs[i].first.c_str();
			tempCharNode.append_attribute(configXMLConstants::slotIDTag.c_str()) = ("0x" + lava::numToHexStringWithPadding(nameIDPairs[i].second, 2)).c_str();
		}
	}

	// EX Roster Handling
	// Adds any collected entries to the destination vector, and returns the number of entries collected in this call.
	std::size_t collectEXRostersFromPlaintext(std::istream& streamIn, std::vector<std::pair<std::string, std::string>>& destinationVector)
	{
		std::size_t originalCount = destinationVector.size();

		if (streamIn.good())
		{
			std::string currentLine = "";
			std::string manipStr = "";
			while (std::getline(streamIn, currentLine))
			{
				// Disregard the current line if it's empty, or is marked as a comment
				if (!currentLine.empty() && currentLine[0] != '#' && currentLine[0] != '/')
				{
					// Clean the string
					// Removes any space characters from outside of quotes. Note, quotes can be escaped with \\.
					manipStr = "";
					bool inQuote = 0;
					bool doEscapeChar = 0;
					for (std::size_t i = 0; i < currentLine.size(); i++)
					{
						if (currentLine[i] == '\"' && !doEscapeChar)
						{
							inQuote = !inQuote;
						}
						else if (currentLine[i] == '\\')
						{
							doEscapeChar = 1;
						}
						else if (inQuote || !std::isspace(currentLine[i]))
						{
							doEscapeChar = 0;
							manipStr += currentLine[i];
						}
					}
					// Determines the location of the delimiter, and ensures that there's something before and something after it.
					// Line is obviously invalid if that fails, so we skip it.
					std::size_t delimLoc = manipStr.find('=');
					if (delimLoc != std::string::npos && delimLoc > 0 && delimLoc < (manipStr.size() - 1))
					{
						// Store roster name portion of string
						std::string rosterNameIn = manipStr.substr(0, delimLoc);
						// Store roster filename portion of string
						std::string fileNameIn = manipStr.substr(delimLoc + 1, std::string::npos);
						// Insert new entry into list.
						destinationVector.push_back(std::make_pair(rosterNameIn, fileNameIn));
					}
				}
			}
		}

		return destinationVector.size() - originalCount;
	}
	std::vector<std::pair<std::string, std::string>> collectEXRostersFromXML(const pugi::xml_node_iterator& rosterDeclNodeItr, bool& collectedPlaintextEntry)
	{
		std::vector<std::pair<std::string, std::string>> result{};

		// Collect proper node entries.
		for (pugi::xml_node_iterator rosterItr = rosterDeclNodeItr->begin(); rosterItr != rosterDeclNodeItr->end(); rosterItr++)
		{
			// If we're looking at a proper roster node, we can just parse its XML contents as normal.
			if (rosterItr->name() == configXMLConstants::rosterTag)
			{
				std::pair<std::string, std::string> tempPair("", "");
				tempPair.first = rosterItr->attribute(configXMLConstants::nameTag.c_str()).as_string("");
				tempPair.second = rosterItr->attribute(configXMLConstants::filenameTag.c_str()).as_string("");

				if (!tempPair.first.empty() && !tempPair.second.empty())
				{
					result.push_back(tempPair);
				}
			}
			// The only other thing we care about are plaintext nodes, since those *could* contain old-school entries.
			else if (rosterItr->type() == pugi::node_pcdata)
			{
				// For these, populate a stringstream with the node's text, 
				// and attempt to pull any entries from the text. This'll return the number of nodes, so if it's greater than 0...
				if (collectEXRostersFromPlaintext(std::stringstream(rosterItr->value()), result) > 0)
				{
					// ... then flag that we've collected a plaintext entry...
					collectedPlaintextEntry = 1;
					// ... and delete the plaintext entries!
					rosterItr->set_value("");
					// Note: this removes those plaintext entries from the tree, they'll be re-generated later so that they use proper XML syntax!
				}
			}
		}

		return result;
	}
	void addCollectedEXRostersToMenuLists(const std::vector<std::pair<std::string, std::string>>& tempRosterList, lava::outputSplitter& logOutput)
	{
		// If we actually retrieved any valid rosters from the file, process them!
		if (!tempRosterList.empty())
		{
			// For each newly collected roster...
			for (int i = 0; i < tempRosterList.size(); i++)
			{
				const std::pair<std::string, std::string>* currPair = &tempRosterList[i];

				// ... check to see if a roster of the same name already exists in our lists.
				auto itr = std::find(ROSTER_LIST.begin(), ROSTER_LIST.end(), currPair->first);

				// If one by that name doesn't already exist...
				if (itr == ROSTER_LIST.end())
				{
					// Add it to our list...
					ROSTER_LIST.push_back(currPair->first);
					ROSTER_FILENAME_LIST.push_back(currPair->second);
					// ... and announce that a roster has been successfully collected.
					logOutput << "[ADDED]";
				}
				// Otherwise, if one by that name *does* already exist...
				else
				{
					// ... overwrite the roster currently associated with that name...
					ROSTER_FILENAME_LIST[itr - ROSTER_LIST.begin()] = currPair->second;
					// ... and announce that the roster has been changed.
					logOutput << "[CHANGED]";
				}
				logOutput << "\"" << currPair->first << "\" (Filename: " << currPair->second << ")\n";
			}
		}
		// Otherwise, note that nothing was found.
		else
		{
			logOutput << "[WARNING] Roster Declaration block parsed, but no valid entries were found!\n";
		}
	}
	void regenRosterDeclsInXML(pugi::xml_node_iterator& rosterDeclNodeItr, const std::vector<std::pair<std::string, std::string>>& tempRosterList)
	{
		// Remove all the proper roster nodes from the XML.
		while (rosterDeclNodeItr->remove_child(configXMLConstants::rosterTag.c_str())) {}

		// And for each roster string pair...
		for (std::size_t i = 0; i < tempRosterList.size(); i++)
		{
			// ... generate a proper roster node for it.
			pugi::xml_node tempCharNode = rosterDeclNodeItr->append_child(configXMLConstants::rosterTag.c_str());
			tempCharNode.append_attribute(configXMLConstants::nameTag.c_str()) = tempRosterList[i].first.c_str();
			tempCharNode.append_attribute(configXMLConstants::filenameTag.c_str()) = tempRosterList[i].second.c_str();
		}
	}

	// Theme Handling
	std::vector<menuTheme> collectThemesFromXML(const pugi::xml_node_iterator& themeDeclNodeItr)
	{
		std::vector<menuTheme> result{};

		for (pugi::xml_node_iterator themeItr = themeDeclNodeItr->begin(); themeItr != themeDeclNodeItr->end(); themeItr++)
		{
			if (themeItr->name() == configXMLConstants::themeTag)
			{
				menuTheme tempTheme;
				tempTheme.name = themeItr->attribute(configXMLConstants::nameTag.c_str()).as_string(tempTheme.name);
				// If the entry has no name, skip to next node.
				if (tempTheme.name.empty()) continue;

				for (pugi::xml_node_iterator themeFileItr = themeItr->begin(); themeFileItr != themeItr->end(); themeFileItr++)
				{
					if (themeFileItr->name() == configXMLConstants::themeFileTag)
					{
						std::size_t filenameIndex = SIZE_MAX;

						for (pugi::xml_attribute_iterator themeFileAttrItr = themeFileItr->attributes_begin(); themeFileAttrItr != themeFileItr->attributes_end(); themeFileAttrItr++)
						{
							if (themeFileAttrItr->name() == configXMLConstants::nameTag)
							{
								auto filenameItr = std::find(themeConstants::filenames.begin(), themeConstants::filenames.end(), themeFileAttrItr->as_string());
								if (filenameItr != themeConstants::filenames.end())
								{
									filenameIndex = filenameItr - themeConstants::filenames.begin();
								}
							}
							else if (filenameIndex != SIZE_MAX && themeFileAttrItr->name() == configXMLConstants::prefixTag)
							{
								tempTheme.prefixes[filenameIndex] = themeFileAttrItr->as_string().substr(0, themeConstants::prefixLength);
								THEME_FILE_GOT_UNIQUE_PREFIX[filenameIndex] |= themeConstants::filenames[filenameIndex].find(tempTheme.prefixes[filenameIndex]) != 0x00;
							}
						}
					}
				}
				result.push_back(tempTheme);
			}
		}

		return result;
	}
	void addCollectedThemesToMenuLists(const std::vector<menuTheme>& tempThemeList, lava::outputSplitter& logOutput)
	{
		// If we actually retrieved any valid themes from the file, process them!
		if (!tempThemeList.empty())
		{
			// For each newly collected theme...
			for (int i = 0; i < tempThemeList.size(); i++)
			{
				const menuTheme* currTheme = &tempThemeList[i];

				// ... check to see if a theme of the same name already exists in our map.
				auto itr = std::find(THEME_LIST.begin(), THEME_LIST.end(), currTheme->name);

				// If one by that name doesn't already exist...
				if (itr == THEME_LIST.end())
				{
					// Add it to our list...
					THEME_LIST.push_back(currTheme->name);
					THEME_SPEC_LIST.push_back(*currTheme);
					// ... and announce that a theme has been successfully collected.
					logOutput << "[ADDED]";
				}
				// Otherwise, if a theme by that name *does* already exist...
				else
				{
					// ... overwrite the theme currently associated with that name...
					THEME_SPEC_LIST[itr - THEME_LIST.begin()] = *currTheme;
					// ... and announce that a theme has been changed.
					logOutput << "[CHANGED]";
				}
				// Describe the processed theme.
				logOutput << " \"" << currTheme->name << "\"\n";
			}
		}
		// Otherwise, note that nothing was found.
		else
		{
			logOutput << "[WARNING] Theme Declaration block parsed, but no valid entries were found!\n";
		}
	}

	// Color Handling
	std::vector<std::pair<std::string, pscc::color>> collectColorsFromXML(const pugi::xml_node_iterator& colorDeclNodeItr)
	{
		std::vector<std::pair<std::string, pscc::color>> result;

		for (pugi::xml_node colorNode : colorDeclNodeItr->children(configXMLConstants::colorTag.c_str()))
		{
			pscc::color tempColor;
			std::string colorName = colorNode.attribute(configXMLConstants::nameTag.c_str()).as_string("");
			// If the entry has no name, skip to next node.
			if (colorName.empty()) continue;

			tempColor.hue = colorNode.attribute(configXMLConstants::colorHueTag.c_str()).as_float(FLT_MAX);
			if (tempColor.hue != FLT_MAX)
			{
				tempColor.hue /= 60.0f;
			}
			tempColor.saturation = colorNode.attribute(configXMLConstants::colorSatTag.c_str()).as_float(FLT_MAX);
			tempColor.luminance = colorNode.attribute(configXMLConstants::colorLumTag.c_str()).as_float(FLT_MAX);

			for (auto flagNode : colorNode.children(configXMLConstants::flagTag.c_str()))
			{
				const std::vector<std::string>* flagNames = &configXMLConstants::colorFlagNames;
				auto flagNameItr = std::find(
					flagNames->cbegin(), flagNames->cend(), flagNode.attribute(configXMLConstants::nameTag.c_str()).as_string(""));
				if (flagNameItr == flagNames->cend()) continue;
				unsigned char flagValue = flagNode.attribute(configXMLConstants::valueTag.c_str()).as_bool(1);
				tempColor.flags |= flagValue << std::distance(flagNames->cbegin(), flagNameItr);
			}

			pugi::xml_node callbackNode = colorNode.child(configXMLConstants::callbackTag.c_str());
			if (callbackNode)
			{
				tempColor.callbackFunctionIndex = callbackNode.attribute(configXMLConstants::indexTag.c_str()).as_uint(UCHAR_MAX);
			}

			result.push_back(std::make_pair(colorName, tempColor));
		}

		return result;
	}
	void addCollectedColorsToMenuLists(const std::vector<std::pair<std::string, pscc::color>>& extraColors, lava::outputSplitter& logOutput)
	{
		for (std::size_t i = 0; i < extraColors.size(); i++)
		{
			const std::string* currColorName = &extraColors[i].first;
			const pscc::color* currColor = &extraColors[i].second;

			if (currColorName->empty())
			{
				logOutput << "[ERROR] XML Color Definition #" << i << " provided no name! Skipping color!\n";
				continue;
			}
			if (!currColor->colorValid())
			{
				logOutput << "[ERROR] Color \"" << *currColorName << "\" invalid! Skipping color!\n";
				continue;
			}

			if (pscc::colorTable.find(*currColorName) != pscc::colorTable.end())
			{
				logOutput << "[CHANGED] \"" << *currColorName << "\"!\n";
			}
			else
			{
				logOutput << "[ADDED] \"" << *currColorName << "\"!\n";
			}
			pscc::colorTable[*currColorName] = *currColor;
		}
	}
	std::vector<pscc::colorScheme> collectSchemesFromXML(const pugi::xml_node_iterator& schemeDeclNodeItr)
	{
		std::vector<pscc::colorScheme> result;

		for (pugi::xml_node_iterator schemeItr = schemeDeclNodeItr->begin(); schemeItr != schemeDeclNodeItr->end(); schemeItr++)
		{
			if (schemeItr->name() == configXMLConstants::colorSchemeTag)
			{
				pscc::colorScheme tempScheme;
				tempScheme.name = schemeItr->attribute(configXMLConstants::nameTag.c_str()).as_string("");
				// If the entry has no name, skip to next node.
				if (tempScheme.name.empty()) continue;

				tempScheme.colors[pscc::cscs_MENU1] = schemeItr->attribute(configXMLConstants::colorSchemeMenu1Tag.c_str()).as_string("");
				tempScheme.colors[pscc::cscs_MENU2] = schemeItr->attribute(configXMLConstants::colorSchemeMenu2Tag.c_str()).as_string("");
				tempScheme.colors[pscc::cscs_INGAME1] = schemeItr->attribute(configXMLConstants::colorSchemeIngame1Tag.c_str()).as_string("");
				tempScheme.colors[pscc::cscs_INGAME2] = schemeItr->attribute(configXMLConstants::colorSchemeIngame2Tag.c_str()).as_string("");
				tempScheme.downfillEmptySlots();

				result.push_back(tempScheme);
			}
		}

		return result;
	}
	void addCollectedSchemesToMenuLists(const std::vector<pscc::colorScheme> collectedSchemes, lava::outputSplitter& logOutput)
	{
		std::map<std::string, std::size_t> tempSchemeList{};
		for (std::size_t i = 0; i < pscc::schemeTable.entries.size(); i++)
		{
			tempSchemeList[pscc::schemeTable.entries[i].name] = i;
		}

		for (std::size_t i = 0; i < collectedSchemes.size(); i++)
		{
			const pscc::colorScheme* currScheme = &collectedSchemes[i];

			if (currScheme->name.empty())
			{
				logOutput << "[ERROR] XML Color Scheme Definition #" << i << " provided no name! Skipping color!\n";
				continue;
			}
			if (!currScheme->schemeValid())
			{
				logOutput << "[ERROR] Color Scheme \"" << currScheme->name << "\" invalid! Skipping color!\n";
				continue;
			}
			auto findRes = tempSchemeList.find(currScheme->name);
			if (findRes != tempSchemeList.end())
			{
				logOutput << "[CHANGED]";
				pscc::schemeTable.entries[findRes->second] = *currScheme;
			}
			else
			{
				logOutput << "[ADDED]";
				tempSchemeList[currScheme->name] = pscc::schemeTable.entries.size();
				pscc::schemeTable.entries.push_back(*currScheme);
			}
			logOutput << " \"" << currScheme->name << "\"!\n";
		}
	}

	// Generic Code Handling
	// Reads in the requested code version from the from the incoming node, and (if it's less than the mode count passed in) stores it in the storage var.
	// Returns the applied mode value, or UCHAR_MAX (0xFF) if either no mode was specified or the requested value was invalid.
	unsigned char setCodeModeFromXML(const pugi::xml_node_iterator& codeNodeItr, unsigned char& modeStorageVariable, unsigned char modeCount, lava::outputSplitter& logOutput)
	{
		unsigned char result = UCHAR_MAX;

		// Determine the result value:
		// If a mode attribute exists for the code's node...
		pugi::xml_attribute modeAttrObj = codeNodeItr->attribute(configXMLConstants::codeModeTag.c_str());
		if (modeAttrObj)
		{
			// ... try to interpret its value as a number.
			result = lava::stringToNum<unsigned char>(modeAttrObj.as_string(), 0, UCHAR_MAX, 0);
			// If the result is valid...
			if (result < modeCount)
			{
				// ... note the success and store the value!
				modeStorageVariable = result;
				logOutput << "[SUCCESS] Mode is now: " << +modeStorageVariable << "!\n";
			}
			// Otherwise...
			else
			{
				// ... leave the value as is and note the invalid specification.
				logOutput << "[WARNING] Invalid mode specified (" << +result << ")! Mode is still: " << +modeStorageVariable << "!\n";
			}
		}
		// Otherwise...
		else
		{
			// ... leave the value as is and note the lack of a mode specification.
			logOutput << "[WARNING] No mode specified! Mode is still: " << +modeStorageVariable << "!\n";
		}

		return result;
	}
	// Reads in whether or not the code is enabled or disabled by the incoming node, and sets the storage var accordingly.
	// Always returns the end value of the storage variable.
	bool setCodeEnabledFromXML(const pugi::xml_node_iterator& codeNodeItr, bool& enabledStorageVariable, lava::outputSplitter& logOutput)
	{
		// If an "enabled" attribute exists for the code's node...
		pugi::xml_attribute modeAttrObj = codeNodeItr->attribute(configXMLConstants::enabledTag.c_str());
		if (modeAttrObj)
		{
			// ... interpret its value as a bool, and note the success.
			enabledStorageVariable = modeAttrObj.as_bool(enabledStorageVariable);
			logOutput << "[SET] Feature is now " << ((enabledStorageVariable) ? "included" : "excluded") << "!\n";
		}
		// Otherwise...
		else
		{
			// ... we leave the value as is and note the lack of a mode specification.
			logOutput << "[WARNING] No value specified! Feature is still " << ((enabledStorageVariable) ? "included" : "excluded") << "!\n";
		}

		return enabledStorageVariable;
	}

	// Core Functions
	bool declNodeIsEnabled(const pugi::xml_node_iterator& declNodeItr)
	{
		// Note, we default to enabled if no value is specified!
		bool result = 1;

		// If an "enabled" attribute is present in this node...
		pugi::xml_attribute enabledAttr = declNodeItr->attribute(configXMLConstants::enabledTag.c_str());
		if (enabledAttr)
		{
			// ... attempt to read it as a bool, store its value in the result.
			result = enabledAttr.as_bool(1);
		}

		return result;
	}
	bool parseAndApplyConfigXML(std::string configFilePath, lava::outputSplitter& logOutput)
	{
		// If the config file doesn't exist, we can exit.
		if (!std::filesystem::is_regular_file(configFilePath)) return 0;

		// Otherwise, create our configDoc object and attempt to populate it from the file...
		pugi::xml_document configDoc;
		pugi::xml_parse_result res = configDoc.load_file(configFilePath.c_str(), pugi::parse_default | pugi::parse_comments | pugi::parse_ws_pcdata);
		// ... and return 0 if the document doesn't successfully parse.
		if (res.status != pugi::xml_parse_status::status_ok) return 0;

		// Attempt to grab the config root node from the document...
		pugi::xml_node configRoot = configDoc.child(configXMLConstants::menuConfigTag.c_str());
		// ... and return 0 if we fail to find one.
		if (!configRoot) return 0;

		bool doRebuild = 0;

		// Check for the debug options node, apply any settings found in it, and add any settings not present.
		doRebuild = handleDebugOptions(configRoot);

		// If we've successfully reached our config root node, we can begin iterating through its child nodes!
		for (pugi::xml_node_iterator declNodeItr = configRoot.begin(); declNodeItr != configRoot.end(); declNodeItr++)
		{
			// If a menu properties block exists...
			if (declNodeItr->name() == configXMLConstants::menuPropsTag)
			{
				// ... apply the contained values.
				logOutput << "\nApplying Menu Properties from \"" << configFilePath << "\"...\n";

				// Used for pulling values from potential nodes!
				pugi::xml_node foundNode{};
				std::string bufferStr("");

				// Check if a base folder declaration node exists in the properties block.
				foundNode = declNodeItr->child(configXMLConstants::baseFolderTag.c_str());
				// If one was actually found, and its value isn't empty...
				bufferStr = foundNode.attribute(configXMLConstants::nameTag.c_str()).as_string("");
				if (!bufferStr.empty())
				{
					// ... attempt to use the retrieved value to set MAIN_FOLDER.
					logOutput << "Build Base Folder argument detected, applying settings...\n";
					if (setMAIN_FOLDER(bufferStr))
					{
						logOutput << "[SUCCESS] Build Base Folder is now \"" << MAIN_FOLDER << "\"!\n";
					}
					else
					{
						logOutput << "[WARNING] Invalid Folder specified, using default value (\"" << MAIN_FOLDER << "\")!\n";
					}
				}

				// Check if a menu title declaration node exists in the properties block.
				foundNode = declNodeItr->child(configXMLConstants::menuTitleTag.c_str());
				// If one was actually found, and its value isn't empty...
				bufferStr = foundNode.attribute(configXMLConstants::textTag.c_str()).as_string("");
				if (!bufferStr.empty())
				{
					// ... use the value to overwrite MENU_NAME.
					MENU_NAME = bufferStr;
					CUSTOM_NAME_SUPPLIED = 1;
					logOutput << "Menu Title argument detected, applying settings...\n";
					logOutput << "[SUCCESS] Menu title is now \"" << MENU_NAME << "\"!\n";
				}

				// Check if a menu comments declaration block exists in the properties block.
				foundNode = declNodeItr->child(configXMLConstants::menuCommentsTag.c_str());
				// If the node is present, and it actually has comment declarations in it...
				if (foundNode)
				{
					logOutput << "Menu header comments block detected! Parsing contents...\n";
					xml::CONFIG_DELETE_CONTROLS_COMMENTS = foundNode.attribute(configXMLConstants::deleteOrigCommentsTag.c_str()).as_bool(0);
					if (xml::CONFIG_DELETE_CONTROLS_COMMENTS)
					{
						logOutput << "[NOTE] Menu Controls comment block will be omitted!\n";
					}
					if (foundNode.child(configXMLConstants::commentTag.c_str()))
					{
						logOutput << "Header Comments detected! Collecting comments...\n";
						for (pugi::xml_node_iterator commentItr = foundNode.begin(); commentItr != foundNode.end(); commentItr++)
						{
							if (commentItr->name() == configXMLConstants::commentTag)
							{
								pugi::xml_attribute tempAttr = commentItr->attribute(configXMLConstants::textTag.c_str());
								if (tempAttr)
								{
									xml::CONFIG_INCOMING_COMMENTS.push_back(tempAttr.as_string());
									logOutput << "\t[ADDED] \"" << tempAttr.as_string() << "\"\n";
								}
							}
						}
					}
					else
					{
						logOutput << "[WARNING] Comment Declaration block parsed, but no valid entries were found!\n";
					}
				}
			}

			// If a line colors block exists...
			if (declNodeItr->name() == configXMLConstants::menuLineColorsTag)
			{
				// ... note that we're parsing it...
				logOutput << "\nApplying Line Colors from \"" << configFilePath << "\"...\n";
				// ... and try to apply its values.
				bool colorApplied = applyLineColorValues(declNodeItr);
				// If we successfully applied at least one color...
				if (colorApplied)
				{
					// ... summarize the table!
					__LineColorsTable* table = &LINE_COLOR_TABLE;
					logOutput << "[SUCCESS] Final Line Color List:\n";
					logOutput << "\tNormal: 0x" << lava::numToHexStringWithPadding(table->COLORS_ARR[table->COLOR_NORMAL], 0x8) << "\n";
					logOutput << "\tSelected: 0x" << lava::numToHexStringWithPadding(table->COLORS_ARR[table->COLOR_HIGHL], 0x8) << "\n";
					logOutput << "\tChanged: 0x" << lava::numToHexStringWithPadding(table->COLORS_ARR[table->COLOR_CH_NORMAL], 0x8) << "\n";
					logOutput << "\tChanged & Selected: 0x" << lava::numToHexStringWithPadding(table->COLORS_ARR[table->COLOR_CH_HIGHL], 0x8) << "\n";
					logOutput << "\tComment: 0x" << lava::numToHexStringWithPadding(table->COLORS_ARR[table->COLOR_COMMENT], 0x8) << "\n";
					logOutput << "\tLocked: 0x" << lava::numToHexStringWithPadding(table->COLORS_ARR[table->COLOR_LOCKED], 0x8) << "\n";
				}
				else
				{
					logOutput << "[WARNING] Line Colors Block parsed, but no valid entries found!\n";
				}
			}

			// If looking at the character list block...
			if (declNodeItr->name() == configXMLConstants::characterListTag)
			{
				logOutput << "\nParsing Character List block from \"" << configFilePath << "\"...\n";

				// Check if a character list version argument was given...
				unsigned long requestedCharListVersion =
					lava::stringToNum(declNodeItr->attribute(configXMLConstants::baseCharListTag.c_str()).as_string(), 0, ULONG_MAX);
				if (requestedCharListVersion != ULONG_MAX)
				{
					// ... and attempt to apply it if so.
					logOutput << "Base Character List argument detected, applying settings...\n";
					if (applyCharacterListVersion(requestedCharListVersion))
					{
						logOutput << "[SUCCESS] Base Character list changed to \"" << characterListVersionNames[characterListVersion] << "\"!\n";
					}
					else
					{
						logOutput << "[WARNING] Invalid list requested! Using \"" << characterListVersionNames[characterListVersion] << "\" list instead!\n";
					}
				}

				// If we're set to additionally collect externally defined Characters...
				if (COLLECT_EXTERNAL_EX_CHARACTERS)
				{
					// ... collect character entries from the XML, then add them to the menu.
					bool collectedPlaintextEntry = 0;
					// Populate our entry list...
					std::vector<std::pair<std::string, u16>> nameIDPairs = collectEXCharactersFromXML(declNodeItr, collectedPlaintextEntry);
					// ... and if that list doesn't end up empty...
					if (!nameIDPairs.empty())
					{
						// ... then we'll note that we're adding characters...
						logOutput << "Adding Characters to Character List...\n";
						// ... and add those to the menu lists proper.
						addCollectedEXCharactersToMenuLists(nameIDPairs, logOutput);
						// Additionally, if we pulled any entries from plaintext...
						if (collectedPlaintextEntry)
						{
							// ... then we need to promote them to properly formatted entries, so regen the entries...
							regenEXCharacterDeclsInXML(declNodeItr, nameIDPairs);
							// ... and fix the indentation on them!
							fixIndentationOfChildNodes(*declNodeItr);
							// Additionally, flag that we need to do a rebuild later.
							doRebuild = 1;
						}
					}
				}

				//Do final character list summary.
				logOutput << "Final Character List (Base List = \"" << characterListVersionNames[characterListVersion] << "\")\n";
				for (std::size_t i = 0; i < CHARACTER_LIST.size(); i++)
				{
					logOutput << "\t\"" << CHARACTER_LIST[i] << "\" (Slot ID = 0x" << lava::numToHexStringWithPadding(CHARACTER_ID_LIST[i], 2) << ")\n";
				}
			}

			// If an addons block exists...
			if (declNodeItr->name() == configXMLConstants::addonsBlockTag)
			{
				logOutput << "\nParsing Addon Includes block from \"" << configFilePath << "\"...\n";

				for (pugi::xml_node addonNode : declNodeItr->children(configXMLConstants::addonTag.c_str()))
				{
					std::string addonName = addonNode.attribute(configXMLConstants::nameTag.c_str()).as_string("");
					addon tempAddon;
					if (tempAddon.populate(addonInputFolderPath + addonName + "/"))
					{
						collectedAddons.push_back(tempAddon);
					}
				}
			}

			// If we've reached the code configuration block...
			if (declNodeItr->name() == configXMLConstants::codeSettingsTag)
			{
				for (pugi::xml_node_iterator codeNodeItr = declNodeItr->begin(); codeNodeItr != declNodeItr->end(); codeNodeItr++)
				{
					// If we're looking at the EX Rosters block...
					if (COLLECT_EXTERNAL_ROSTERS && declNodeIsEnabled(codeNodeItr) && codeNodeItr->name() == configXMLConstants::roseterDeclsTag)
					{
						logOutput << "\nAdding Rosters to Code Menu from \"" << configFilePath << "\"...\n";

						// ... collect roster entries from the XML, then add them to the menu.
						bool collectedPlaintextEntry = 0;
						// Populate our entry list...
						std::vector<std::pair<std::string, std::string>> tempRosterList = collectEXRostersFromXML(codeNodeItr, collectedPlaintextEntry);
						addCollectedEXRostersToMenuLists(tempRosterList, logOutput);
						// Additionally, if we pulled any entries from plaintext...
						if (collectedPlaintextEntry)
						{
							// ... then we need to promote them to properly formatted entries, so regen the entries...
							regenRosterDeclsInXML(codeNodeItr, tempRosterList);
							// ... and fix the indentation on them!
							fixIndentationOfChildNodes(*codeNodeItr);
							// Additionally, flag that we need to do a rebuild later.
							doRebuild = 1;
						}

						//Do final roster list summary.
						logOutput << "Final Roster List:\n";
						for (std::size_t i = 0; i < ROSTER_LIST.size(); i++)
						{
							logOutput << "\t\"" << ROSTER_LIST[i] << "\" (Filename: " << ROSTER_FILENAME_LIST[i] << ")\n";
						}
					}
					// If we're looking at the Themes block...
					else if (COLLECT_EXTERNAL_THEMES && declNodeIsEnabled(codeNodeItr) && codeNodeItr->name() == configXMLConstants::themeDeclsTag)
					{
						logOutput << "\nAdding Themes to Code Menu from \"" << configFilePath << "\"...\n";

						// ... collect theme entries from the XML, then add them to the menu.
						std::vector<menuTheme> tempThemeList = collectThemesFromXML(codeNodeItr);
						addCollectedThemesToMenuLists(tempThemeList, logOutput);

						// Do final theme list summary.
						logOutput << "Final Theme List:\n";
						for (std::size_t i = 0; i < THEME_LIST.size(); i++)
						{
							logOutput << "\t\"" << THEME_LIST[i] << "\", Replacement Prefixes Are:\n";
							for (std::size_t u = 0; u < THEME_SPEC_LIST[i].prefixes.size(); u++)
							{
								logOutput << "\t\t\"" << themeConstants::filenames[u] << "\": \"" << THEME_SPEC_LIST[i].prefixes[u] << "\"\n";
							}
						}
					}
					// If we're looking at the Item Grab block...
					else if (codeNodeItr->name() == configXMLConstants::dashAttackItemGrabTag)
					{
						logOutput << "\nSetting Dash Attack Item Grab Toggle status...\n";
						// ... handle enabling/disabling it.
						setCodeEnabledFromXML(codeNodeItr, xml::CONFIG_DASH_ATTACK_ITEM_GRAB_ENABLED, logOutput);
					}
					// If we're looking at the Jumpsquat Override block...
					else if (codeNodeItr->name() == configXMLConstants::jumpsquatOverrideTag)
					{
						logOutput << "\nSetting Jumpsquat Modifier status...\n";
						// ... handle enabling/disabling it.
						setCodeEnabledFromXML(codeNodeItr, xml::CONFIG_JUMPSQUAT_OVERRIDE_ENABLED, logOutput);
					}
					// If we're looking at the Slot Colors block...
					else if (codeNodeItr->name() == configXMLConstants::slotColorDeclsTag)
					{
						logOutput << "\nSetting Player Slot Color Changer status... \n";
						// ... handle enabling/disabling it.
						// And if we end up enabling it...
						if (setCodeEnabledFromXML(codeNodeItr, xml::CONFIG_PSCC_ENABLED, logOutput))
						{
							pugi::xml_node targetNode = codeNodeItr->child(configXMLConstants::colorDefsTag.c_str());
							if (targetNode)
							{
								logOutput << "Parsing Color Definitions... \n";
								std::vector<std::pair<std::string, pscc::color>> extraColors = collectColorsFromXML(targetNode);
								if (!extraColors.empty())
								{
									addCollectedColorsToMenuLists(extraColors, logOutput);
								}
								else
								{
									logOutput << "[WARNING] Color Definition Block parsed, but no valid entries found!\n";
								}
							}

							targetNode = codeNodeItr->child(configXMLConstants::colorSchemeDefsTag.c_str());
							if (targetNode)
							{
								logOutput << "Parsing Color Scheme Definitions... \n";
								std::vector<pscc::colorScheme> extraSchemes = collectSchemesFromXML(targetNode);
								if (!extraSchemes.empty())
								{
									addCollectedSchemesToMenuLists(extraSchemes, logOutput);
								}
								else
								{
									logOutput << "[WARNING] Scheme Definition Block parsed, but no valid entries found!\n";
								}
							}

							//Do final scheme list summary.
							logOutput << "Final Color Scheme List:\n";
							for (std::size_t i = 0; i < pscc::schemeTable.entries.size(); i++)
							{
								const pscc::colorScheme* currScheme = &pscc::schemeTable.entries[i];
								logOutput << std::setw(0x10) << ("\"" + currScheme->name + "\" ");
								switch (i)
								{
								case pscc::schemePredefIDs::spi_P1: { logOutput << "[P1 + Red Team]"; break; }
								case pscc::schemePredefIDs::spi_P2: { logOutput << "[P2 + Blue Team]"; break; }
								case pscc::schemePredefIDs::spi_P3: { logOutput << "[P3]"; break; }
								case pscc::schemePredefIDs::spi_P4: { logOutput << "[P4 + Green Team]"; break; }
								default: { break; }
								}
								logOutput << "\n";
							}

							pscc::schemeTable.tableToByteVec();
						}
					}
				}
			}
		}

		if (doRebuild)
		{
			configDoc.save_file(configFilePath.c_str());
		}

		return 1;
	}

	// ============================================================================


	// =======================  Addon Parsing and Constants =======================

	

	// Line Parsing
	std::array<bool, Line::LineBehaviorFlags::lbf__COUNT> applyLineBehaviorFlagsFromNode(const pugi::xml_node& sourceNode, Line* targetLine)
	{
		std::array<bool, Line::LineBehaviorFlags::lbf__COUNT> result{};

		if (targetLine != nullptr)
		{
			// For each kind of LineBehaviorFlag...
			for (std::size_t lbfItr = 0; lbfItr < Line::LineBehaviorFlags::lbf__COUNT; lbfItr++)
			{
				// ... check for a corresponding attribute on the current node.
				pugi::xml_attribute tempAttr = sourceNode.attribute(configXMLConstants::lineBehaviorFlagTags[lbfItr].c_str());
				// If one exists...
				if (tempAttr)
				{
					// ... grab its incoming value.
					bool incomingValue = tempAttr.as_bool();
					// Record whether or not it's value changed...
					result[lbfItr] = targetLine->behaviorFlags[lbfItr] != incomingValue;
					// ... write the incoming value over the current one...
					targetLine->behaviorFlags[lbfItr].value = incomingValue;
					// ... and force enable XML output for the flag!
					targetLine->behaviorFlags[lbfItr].forceXMLOutput = 1;
				}
			}
		}

		return result;
	}
	fieldChangeArr applyIntegerLineSettingsFromNode(const pugi::xml_node& sourceNode, Line* targetLine, fieldChangeArr allowedChanges)
	{
		std::array<bool, lineFields::lc__COUNT> result{};

		pugi::xml_node minValNode = sourceNode.child(configXMLConstants::valueMinTag.c_str());
		if (minValNode && allowedChanges[lineFields::lf_ValMin])
		{
			u32 currentVal = targetLine->Min;
			u32 incomingVal = minValNode.attribute(configXMLConstants::valueTag.c_str()).as_uint(currentVal);
			result[lineFields::lf_ValMin] = incomingVal != currentVal;

			targetLine->Min = incomingVal;
		}

		pugi::xml_node maxValNode = sourceNode.child(configXMLConstants::valueMaxTag.c_str());
		if (maxValNode && allowedChanges[lineFields::lf_ValMax])
		{
			u32 currentVal = targetLine->Max;
			u32 incomingVal = maxValNode.attribute(configXMLConstants::valueTag.c_str()).as_uint(currentVal);
			result[lineFields::lf_ValMax] = incomingVal != currentVal;

			targetLine->Max = incomingVal;
		}

		pugi::xml_node defaultValNode = sourceNode.child(configXMLConstants::valueDefaultTag.c_str());
		if (defaultValNode && allowedChanges[lineFields::lf_ValDefault])
		{
			u32 currentVal = GetFloatFromHex(targetLine->Default);
			u32 incomingVal = defaultValNode.attribute(configXMLConstants::valueTag.c_str()).as_float(currentVal);
			incomingVal = std::min(std::max(incomingVal, targetLine->Min), targetLine->Max);
			result[lineFields::lf_ValDefault] = incomingVal != currentVal;

			targetLine->Default = GetHexFromFloat(incomingVal);
			targetLine->Value = targetLine->Default;
		}

		pugi::xml_node speedNode = sourceNode.child(configXMLConstants::speedTag.c_str());
		if (speedNode && allowedChanges[lineFields::lf_Speed])
		{
			u32 currentVal = targetLine->Speed;
			u32 incomingVal = speedNode.attribute(configXMLConstants::valueTag.c_str()).as_uint(currentVal);
			result[lineFields::lf_Speed] = incomingVal != currentVal;

			targetLine->Speed = incomingVal;
		}

		return result;
	}
	fieldChangeArr applyFloatLineSettingsFromNode(const pugi::xml_node& sourceNode, Line* targetLine, fieldChangeArr allowedChanges)
	{
		std::array<bool, lineFields::lc__COUNT> result{};

		pugi::xml_node minValNode = sourceNode.child(configXMLConstants::valueMinTag.c_str());
		if (minValNode && allowedChanges[lineFields::lf_ValMin])
		{
			float currentVal = GetFloatFromHex(targetLine->Min);
			float incomingVal = minValNode.attribute(configXMLConstants::valueTag.c_str()).as_float(currentVal);
			result[lineFields::lf_ValMin] = std::abs(incomingVal - currentVal) > 0.00001f;

			targetLine->Min = GetHexFromFloat(incomingVal);
		}

		pugi::xml_node maxValNode = sourceNode.child(configXMLConstants::valueMaxTag.c_str());
		if (maxValNode && allowedChanges[lineFields::lf_ValMax])
		{
			float currentVal = GetFloatFromHex(targetLine->Max);
			float incomingVal = maxValNode.attribute(configXMLConstants::valueTag.c_str()).as_float(currentVal);
			result[lineFields::lf_ValMax] = std::abs(incomingVal - currentVal) > 0.00001f;

			targetLine->Max = GetHexFromFloat(incomingVal);
		}

		pugi::xml_node defaultValNode = sourceNode.child(configXMLConstants::valueDefaultTag.c_str());
		if (defaultValNode && allowedChanges[lineFields::lf_ValDefault])
		{
			float currentVal = GetFloatFromHex(targetLine->Default);
			float incomingVal = defaultValNode.attribute(configXMLConstants::valueTag.c_str()).as_float(currentVal);
			float maxVal = GetFloatFromHex(targetLine->Max);
			float minVal = GetFloatFromHex(targetLine->Min);
			incomingVal = std::min(std::max(incomingVal, minVal), maxVal);
			result[lineFields::lf_ValDefault] = std::abs(incomingVal - currentVal) > 0.00001f;

			targetLine->Default = GetHexFromFloat(incomingVal);
			targetLine->Value = targetLine->Default;
		}

		pugi::xml_node speedNode = sourceNode.child(configXMLConstants::speedTag.c_str());
		if (speedNode && allowedChanges[lineFields::lf_Speed])
		{
			float currentVal = GetFloatFromHex(targetLine->Speed);
			float incomingVal = speedNode.attribute(configXMLConstants::valueTag.c_str()).as_float(currentVal);
			result[lineFields::lf_Speed] = std::abs(incomingVal - currentVal) > 0.00001f;

			targetLine->Speed = GetHexFromFloat(incomingVal);
		}

		return result;
	}
	fieldChangeArr applyToggleLineSettingsFromNode(const pugi::xml_node& sourceNode, Line* targetLine, fieldChangeArr allowedChanges)
	{
		std::array<bool, lineFields::lc__COUNT> result{};

		pugi::xml_node defaultValNode = sourceNode.child(configXMLConstants::valueDefaultTag.c_str());
		if (defaultValNode && allowedChanges[lineFields::lf_ValDefault])
		{
			bool currentVal = targetLine->Default;
			bool incomingVal = defaultValNode.attribute(configXMLConstants::valueTag.c_str()).as_bool(currentVal);
			result[lineFields::lf_ValDefault] = incomingVal != currentVal;

			targetLine->Default = incomingVal;
			targetLine->Value = targetLine->Default;
		}

		return result;
	}

	// Addons
	void addonLine::buildSubmenuLine(const pugi::xml_node& sourceNode)
	{
		if (!shortName.empty())
		{
			if (pageShortnameIsFree(shortName))
			{
				auto newPage = collectedNewPages.insert(std::make_pair(shortName, std::make_shared<Page>(lineName, std::vector<Line*>{}, shortName)));
				linePtr = newPage.first->second->CalledFromLine;
			}
			shortName.set("");
		}
	}
	void addonLine::buildIntegerLine(const pugi::xml_node& sourceNode)
	{
		linePtr = std::make_shared<Integer>(lineName, INT_MAX, INT_MAX, INT_MAX, INT_MAX, this->INDEX);
		fieldChangeArr allowedChanges{};
		allowedChanges[lineFields::lf_ValMin] = 1;
		allowedChanges[lineFields::lf_ValMax] = 1;
		allowedChanges[lineFields::lf_ValDefault] = 1;
		allowedChanges[lineFields::lf_Speed] = 1;
		populated = applyIntegerLineSettingsFromNode(sourceNode, linePtr.get(), allowedChanges);
	}
	void addonLine::buildFloatLine(const pugi::xml_node& sourceNode)
	{
		linePtr = std::make_shared<Floating>(lineName, FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX, this->INDEX);
		fieldChangeArr allowedChanges{};
		allowedChanges[lineFields::lf_ValMin] = 1;
		allowedChanges[lineFields::lf_ValMax] = 1;
		allowedChanges[lineFields::lf_ValDefault] = 1;
		allowedChanges[lineFields::lf_Speed] = 1;
		populated = applyFloatLineSettingsFromNode(sourceNode, linePtr.get(), allowedChanges);
	}
	void addonLine::buildToggleLine(const pugi::xml_node& sourceNode)
	{
		linePtr = std::make_shared<Toggle>(lineName, 0, this->INDEX);
		fieldChangeArr allowedChanges{};
		allowedChanges[lineFields::lf_ValDefault] = 1;
		populated = applyToggleLineSettingsFromNode(sourceNode, linePtr.get(), allowedChanges);
	}
	void addonLine::buildSelectionLine(const pugi::xml_node& sourceNode)
	{
		std::vector<std::string> options{};
		for (auto optionNode : sourceNode.children(configXMLConstants::selectionOptionTag.c_str()))
		{
			options.push_back(optionNode.attribute(configXMLConstants::valueTag.c_str()).as_string(""));
		}

		std::size_t defaultIndex =
			sourceNode.child(configXMLConstants::selectionDefaultTag.c_str()).attribute(configXMLConstants::indexTag.c_str()).as_uint(0);
		defaultIndex = std::min(defaultIndex, options.size());

		linePtr = std::make_shared<Selection>(lineName, options, defaultIndex, this->INDEX);
	}
	void addonLine::buildCommentLine(const pugi::xml_node& sourceNode)
	{
		std::string text = sourceNode.attribute(configXMLConstants::textTag.c_str()).as_string("");
		linePtr = std::make_shared<Comment>(text);
	}
	addonLine::addonLine(const pugi::xml_node& sourceNode)
	{
		populate(sourceNode);
	}
	bool addonLine::populate(const pugi::xml_node& sourceNode)
	{
		lineName = sourceNode.attribute(configXMLConstants::nameTag.c_str()).as_string("");
		lineName = getLineNameFromLineText(lineName);
		shortName = sourceNode.attribute(configXMLConstants::shortnameTag.c_str()).as_string("");

		if (sourceNode.name() == configXMLConstants::menuLineCommentTag)
		{
			buildCommentLine(sourceNode);
		}
		else if (!shortName.empty())
		{
			if (sourceNode.name() == configXMLConstants::menuLineSubmenuTag)
			{
				buildSubmenuLine(sourceNode);
			}
			else if (sourceNode.name() == configXMLConstants::menuLineIntTag)
			{
				buildIntegerLine(sourceNode);
			}
			else if (sourceNode.name() == configXMLConstants::menuLineFloatTag)
			{
				buildFloatLine(sourceNode);
			}
			else if (sourceNode.name() == configXMLConstants::menuLineSelectionTag)
			{
				buildSelectionLine(sourceNode);
			}
			else if (sourceNode.name() == configXMLConstants::menuLineToggleTag)
			{
				buildToggleLine(sourceNode);
			}
			if (linePtr.get() != nullptr)
			{
				applyLineBehaviorFlagsFromNode(sourceNode, linePtr.get());
			}
		}

		return linePtr.get() != nullptr;
	}

	bool addonPageTarget::populate(const pugi::xml_node& sourceNode)
	{
		shortName = sourceNode.attribute(configXMLConstants::shortnameTag.c_str()).as_string("");

		for (pugi::xml_node childNode : sourceNode.children())
		{
			if (childNode.name() == configXMLConstants::menuLinePageTag) continue;
			std::shared_ptr<addonLine> tempLine = std::make_shared<addonLine>();
			if (tempLine->populate(childNode))
			{
				lines.push_back(tempLine);
				if (!tempLine->shortName.empty())
				{
					lineMap[tempLine->shortName] = tempLine;
				}
			}
		}

		return !lines.empty();
	}

	addon::addon(std::string inputDirPathIn)
	{
		populate(inputDirPathIn);
	}
	bool addon::populate(std::string inputDirPathIn)
	{
		bool result = 0;

		// Only continue with construction if all the necessary folders and files exist...
		if (!std::filesystem::is_directory(inputDirPathIn)) return result;
		if (!std::filesystem::is_regular_file(inputDirPathIn + "/" + addonInputSourceFilename)) return result;
		if (!std::filesystem::is_regular_file(inputDirPathIn + "/" + addonInputConfigFilename)) return result;
		// ... and the config document parses successfully!
		pugi::xml_document configDoc;
		if (!configDoc.load_file(std::string(inputDirPathIn + "/" + addonInputConfigFilename).c_str())) return result;
		// Locate the root node...
		pugi::xml_node rootNode = configDoc.child(configXMLConstants::addonTag.c_str());
		// ... and if it exists...
		if (rootNode)
		{
			addonName = rootNode.attribute(configXMLConstants::nameTag.c_str()).as_string("");
			shortName = rootNode.attribute(configXMLConstants::shortnameTag.c_str()).as_string("");

			inputDirPath = inputDirPathIn;

			// First, grab every page node.
			for (pugi::xml_node pageNode : rootNode.children(configXMLConstants::menuLinePageTag.c_str()))
			{
				addonPageTarget tempPage;
				tempPage.populate(pageNode);
				if (!tempPage.shortName.empty() && !tempPage.lines.empty())
				{
					targetPages[tempPage.shortName] = tempPage;
					result = 1;
				}
			}
		}

		return result;
	}
	std::string addon::getInputXMLPath()
	{
		return inputDirPath + addonInputConfigFilename;
	}
	std::string addon::getInputASMPath()
	{
		return inputDirPath + addonInputSourceFilename;

	}
	std::string addon::getOutputASMPath()
	{
		return addonsOutputLocation + shortName.str() + ".asm";
	}
	std::string addon::getBuildASMPath()
	{
		return "Source/" + addonOutputFolderPath + shortName.str() + ".asm";
	}


	std::map<lava::shortNameType, std::shared_ptr<Page>> collectedNewPages{};
	std::vector<addon> collectedAddons{};

	void applyCollectedAddons()
	{
		for (addon currAddon : collectedAddons)
		{
			for (auto currPageItr : currAddon.targetPages)
			{
				auto pageFindRes = menuPagesMap.find(currPageItr.first);
				if (pageFindRes != menuPagesMap.end())
				{
					for (std::shared_ptr<addonLine> currLine : currPageItr.second.lines)
					{
						pageFindRes->second->Lines.push_back(currLine->linePtr.get());
					}
					pageFindRes->second->PrepareLines();
				}
			}
		}
	}
	void generateAddonEmbeds(std::ostream& outputStream)
	{
		std::size_t startingAddr = std::size_t(START_OF_CODE_MENU_HEADER) + outputStream.tellp();
		std::size_t currAddr = startingAddr;

		std::filesystem::remove_all(addonsOutputLocation);
		if (!collectedAddons.empty())
		{
			std::filesystem::create_directory(addonsOutputLocation);
			std::ofstream addonMacroDefs(addonsOutputLocation + addonAliasBankFilename);
			if (!addonMacroDefs.is_open())
			{
				std::cerr << "[ERROR] Unable to write Addon Macro Bank! Aborting Embeds!\n";
			}
			else
			{
				std::string macroBankHeaderText = "#[CM_Addons] Code Menu Addons Line Alias LOC Bank";
				addonMacroDefs <<
					std::string(macroBankHeaderText.size(), '#') << "\n" <<
					macroBankHeaderText << "\n" <<
					std::string(macroBankHeaderText.size(), '#') << "\n";

				for (addon currAddon : collectedAddons)
				{
					std::filesystem::copy_file(currAddon.getInputASMPath(), currAddon.getOutputASMPath());

					addonMacroDefs << "# Addon \"" << currAddon.addonName << "\" Lines\n";
					currAddon.baseLOC = currAddr;
					for (auto currPageTarget : currAddon.targetPages)
					{
						for (auto currLine : currPageTarget.second.lineMap)
						{
							std::string locNameBase = currAddon.shortName.str() + "_" + currLine.first.str() + "_LOC";
							addonMacroDefs << "# Line \"" << currLine.second->lineName << "\" in \"" << currAddon.addonName << "\"\n";
							addonMacroDefs << ".alias " << locNameBase << " = 0x" << lava::numToHexStringWithPadding(currAddr, 0x8) << "\n";
							addonMacroDefs << ".alias " << locNameBase << "_HI = 0x" << lava::numToHexStringWithPadding(currAddr >> 0x10, 0x4) << "\n";
							addonMacroDefs << ".alias " << locNameBase << "_LO = 0x" << lava::numToHexStringWithPadding(currAddr & 0xFFFF, 0x4) << "\n";
							lava::writeRawDataToStream(outputStream, currLine.second->INDEX);
							currAddr += 0x4;
						}
					}
					addonMacroDefs << "\n";
				}
			}
		}
	}
	void appendAddonIncludesToASM()
	{
		std::ofstream asmAppendStream(asmOutputFilePath, std::ios::out | std::ios::app);
		if (!collectedAddons.empty() && std::filesystem::is_regular_file(asmOutputFilePath))
		{
			std::string addonIncludesHeader = "[CM_Addons] Code Menu Addon Includes";
			asmAppendStream << std::string(addonIncludesHeader.size(), '#') << "\n" <<
				addonIncludesHeader << "\n" <<
				std::string(addonIncludesHeader.size(), '#') << "\n";
			for (addon currAddon : collectedAddons)
			{
				asmAppendStream << ".include \"" << currAddon.getBuildASMPath() << "\"\n";
			}
		}
	}

	bool copyAddonsFolderIntoBuild()
	{
		bool result = 0;

		std::filesystem::remove_all(addonsBuildLocation);
		if (std::filesystem::is_directory(addonsOutputLocation))
		{
			std::filesystem::copy(addonsOutputLocation, addonsBuildLocation);
			result = 1;
		}

		return result;
	}



	// ============================================================================


	// ==================== Menu Options Parsing and Constants ====================


	// Incoming Configuration XML Variables
	std::vector<std::string> CONFIG_INCOMING_COMMENTS{};
	bool CONFIG_DELETE_CONTROLS_COMMENTS = false;
	bool CONFIG_PSCC_ENABLED = false;
	bool CONFIG_DASH_ATTACK_ITEM_GRAB_ENABLED = 1;
	bool CONFIG_JUMPSQUAT_OVERRIDE_ENABLED = 1;

	// Options XML
	bool loadMenuOptionsTree(std::string xmlPathIn, pugi::xml_document& destinationDocument)
	{
		bool result = 0;

		if (std::filesystem::is_regular_file(xmlPathIn))
		{
			if (destinationDocument.load_file(xmlPathIn.c_str()))
			{
				result = 1;
			}
		}

		return result;
	}
	void recursivelyFindPages(Page& currBasePageIn, std::vector<Page*>& collectedPointers)
	{
		for (unsigned long i = 0; i < currBasePageIn.Lines.size(); i++)
		{
			const Line* currLine = currBasePageIn.Lines[i];
			if (currLine->type == SUB_MENU_LINE)
			{
				bool pointerNotPreviouslyCollected = 1;
				for (unsigned long u = 0; pointerNotPreviouslyCollected && u < collectedPointers.size(); u++)
				{
					pointerNotPreviouslyCollected &= collectedPointers[u] != currLine->SubMenuPtr;
				}
				if (pointerNotPreviouslyCollected)
				{
					collectedPointers.push_back(currLine->SubMenuPtr);
					recursivelyFindPages(*currLine->SubMenuPtr, collectedPointers);
				}
			}
		}
	}
	void findPagesInOptionsTree(const pugi::xml_document& optionsTree, std::map<std::string, pugi::xml_node>& collectedNodes)
	{
		// Request the code menu base node from the optionsTree...
		pugi::xml_node menuNode = optionsTree.child(configXMLConstants::codeMenuTag.c_str());
		// ... and if it was validly returned...
		if (menuNode)
		{
			// ... get the collection of page nodes from the menu.
			pugi::xml_object_range pageNodes = menuNode.children(configXMLConstants::menuLinePageTag.c_str());
			// For each of these pages...
			for (pugi::xml_named_node_iterator pageItr = pageNodes.begin(); pageItr != pageNodes.end(); pageItr++)
			{
				// ... request its name attribute...
				pugi::xml_attribute pageNameAttr = pageItr->attribute(configXMLConstants::nameTag.c_str());
				// ... and if it's validly returned...
				if (pageNameAttr)
				{
					// ... record the page and its name in our map.
					collectedNodes[pageNameAttr.value()] = *pageItr;
				}
			}
		}
	}
	void findLinesInPageNode(const pugi::xml_node& pageNode, std::map<std::string, pugi::xml_node>& collectedNodes)
	{
		for (pugi::xml_node_iterator lineItr = pageNode.begin(); lineItr != pageNode.end(); lineItr++)
		{
			if (lineItr->name() == configXMLConstants::menuLineSelectionTag || lineItr->name() == configXMLConstants::menuLineFloatTag || lineItr->name() == configXMLConstants::menuLineIntTag)
			{
				// Request the name attribute from the current node...
				pugi::xml_attribute nameAttr = lineItr->attribute(configXMLConstants::nameTag.c_str());
				// ... and if the returned attribute is valid...
				if (nameAttr)
				{
					// ... record it and the corresponding line in the output map.
					collectedNodes[nameAttr.value()] = *lineItr;
				}
			}
		}
	}
	void applyLineSettingsFromMenuOptionsTree(Page& mainPageIn, const pugi::xml_document& xmlDocumentIn, lava::outputSplitter& logOutput)
	{
		// Get a list of all the pages in the menu, including the main page.
		std::vector<Page*> Pages{ &mainPageIn };
		recursivelyFindPages(mainPageIn, Pages);

		// And find every page present in the XML.
		std::map<std::string, pugi::xml_node> pageNodeMap;
		findPagesInOptionsTree(xmlDocumentIn, pageNodeMap);

		// For each of the pages we found in our actual menu structure...
		for (Page* currPage : Pages)
		{
			// ... see if there was a corresponding page in the XML document...
			auto pageFindItr = pageNodeMap.find(currPage->PageName);
			if (pageFindItr == pageNodeMap.end()) continue;

			// ... and if so, apply any behavior flags attributes on the node, and note which have changed!
			std::array<bool, Line::LineBehaviorFlags::lbf__COUNT> pageLBFsChanged =
				applyLineBehaviorFlagsFromNode(pageFindItr->second, currPage->CalledFromLine.get());
			// If an LBF changed...
			bool pageLBFChanged = std::find(pageLBFsChanged.begin(), pageLBFsChanged.end(), 1) != pageLBFsChanged.end();
			if (pageLBFChanged)
			{
				// ... note that the page has changed...
				logOutput << "[CHANGED] \"" << currPage->PageName << "\"\n";
				// ... then for each one...
				for (std::size_t lbfItr = 0; lbfItr < Line::LineBehaviorFlags::lbf__COUNT; lbfItr++)
				{
					// ... if that LBF changed...
					if (!pageLBFsChanged[lbfItr]) continue;
					// ... note its current state!
					logOutput << "\t- Page " <<
						(currPage->CalledFromLine->behaviorFlags[lbfItr] ? "is now " : "is no longer ") <<
						configXMLConstants::lineBehaviorFlagTags[lbfItr] << "!\n";
				}
			}

			// If there was, we need to apply the default values from the lines in that page node!
			// Additionally, get a list of all the line nodes in this page node.
			std::map<std::string, pugi::xml_node> lineNodeMap;
			findLinesInPageNode(pageFindItr->second, lineNodeMap);
			// Then, for each line in the current page struct...
			for (Line* currLine : currPage->Lines)
			{
				// ... check if a corresponding node is present in this page node.
				std::vector<std::string_view> deconstructedText = splitLineContentString(currLine->Text);
				auto lineFindItr = lineNodeMap.find(deconstructedText[0].data());
				if (lineFindItr == lineNodeMap.end()) continue;

				// If so, pull the default value from the XML and write it into each line struct (based on the line type), and note if it changed!
				bool lineDefaultChanged = 0;
				switch (currLine->type)
				{
				case SELECTION_LINE:
				{
					pugi::xml_node defaultValNode = lineFindItr->second.child(configXMLConstants::selectionDefaultTag.c_str());
					if (defaultValNode)
					{
						pugi::xml_attribute defaultIndexAttr = defaultValNode.attribute(configXMLConstants::indexTag.c_str());
						if (defaultIndexAttr)
						{
							u32 valueIn = defaultIndexAttr.as_uint(currLine->Default);
							valueIn = std::min<unsigned long>(std::max(0u, valueIn), deconstructedText.size() - 2);
							lineDefaultChanged = valueIn != currLine->Default;
							currLine->Default = valueIn;
							currLine->Value = valueIn;
						}
					}
					break;
				}
				case INTEGER_LINE:
				{
					pugi::xml_node defaultValNode = lineFindItr->second.child(configXMLConstants::valueDefaultTag.c_str());
					if (defaultValNode)
					{
						pugi::xml_attribute defaultValueAttr = defaultValNode.attribute(configXMLConstants::valueTag.c_str());
						if (defaultValueAttr)
						{
							int valueIn = defaultValueAttr.as_int(currLine->Default);
							valueIn = std::min(std::max(valueIn, (int)currLine->Min), (int)currLine->Max);
							lineDefaultChanged = valueIn != currLine->Default;
							currLine->Default = valueIn;
							currLine->Value = valueIn;
						}
					}
					break;
				}
				case FLOATING_LINE:
				{
					pugi::xml_node defaultValNode = lineFindItr->second.child(configXMLConstants::valueDefaultTag.c_str());
					if (defaultValNode)
					{
						pugi::xml_attribute defaultValueAttr = defaultValNode.attribute(configXMLConstants::valueTag.c_str());
						if (defaultValueAttr)
						{
							float valueIn = defaultValueAttr.as_float(GetFloatFromHex(currLine->Default));
							float currDefaultVal = GetFloatFromHex(currLine->Default);
							float maxVal = GetFloatFromHex(currLine->Max);
							float minVal = GetFloatFromHex(currLine->Min);
							valueIn = std::min(std::max(valueIn, minVal), maxVal);
							lineDefaultChanged = std::abs(valueIn - currDefaultVal) > 0.00001f;
							if (lineDefaultChanged)
							{
								currLine->Default = GetHexFromFloat(valueIn);
								currLine->Value = currLine->Default;
							}
						}
					}
					break;
				}
				default:
				{
					break;
				}
				}

				// Additionally, apply any behavior flags attributes on the node, and note which have changed!
				std::array<bool, Line::LineBehaviorFlags::lbf__COUNT> lineLBFsChanged =
					applyLineBehaviorFlagsFromNode(lineFindItr->second, currLine);

				// If either the default value or one of the LBFs have changed...
				bool lineLBFChanged = std::find(lineLBFsChanged.begin(), lineLBFsChanged.end(), 1) != lineLBFsChanged.end();
				if (lineDefaultChanged || lineLBFChanged)
				{
					// ... print the relevant changes!
					logOutput << "[CHANGED] \"" << currPage->PageName << " > " << currLine->LineName << "\"\n";
					// If the line's default value changed...
					if (lineDefaultChanged)
					{
						// ... note the change in value (according to the line type).
						logOutput << "\t- ";
						switch (currLine->type)
						{
						case FLOATING_LINE: { logOutput << "Default Value is now " << GetFloatFromHex(currLine->Default); break; }
						case SELECTION_LINE: { logOutput << "Default Index is now " << currLine->Default; break; }
						default: { logOutput << "Default Value is now " << currLine->Default; break; }
						}
						logOutput << "\n";
					}
					// If an LBF changed...
					if (lineLBFChanged)
					{
						// ... for each one...
						for (std::size_t lbfItr = 0; lbfItr < Line::LineBehaviorFlags::lbf__COUNT; lbfItr++)
						{
							// ... if that LBF changed...
							if (!lineLBFsChanged[lbfItr]) continue;
							// ... note its current state!
							logOutput << "\t- Line " <<
								(currLine->behaviorFlags[lbfItr] ? "is now " : "is no longer ") <<
								configXMLConstants::lineBehaviorFlagTags[lbfItr] << "!\n";
						}
					}
				}
			}
		}
		// And lastly, for each page...
		for (Page* currPage : Pages)
		{
			// ... re-prepare the lines in them, to ensure that anything with changed visibility actually honors that designation.
			currPage->PrepareLines();
		}
	}
	bool applyLineSettingsFromMenuOptionsTree(Page& mainPageIn, std::string xmlPathIn, lava::outputSplitter& logOutput)
	{
		bool result = 0;

		logOutput << "\nParsing Options XML from \"" << xmlPathIn << "\"...\n";
		pugi::xml_document tempDoc;
		if (loadMenuOptionsTree(xmlPathIn, tempDoc))
		{
			logOutput << "[SUCCESS] Applying settings...\n";
			std::shared_ptr<std::ostream> changelogStreamPtr = logOutput.getOutputEntry(__logOutputStruct::changelogID)->targetStream;
			std::streampos outputPos = changelogStreamPtr->tellp();
			applyLineSettingsFromMenuOptionsTree(mainPageIn, tempDoc, logOutput);
			if (outputPos == changelogStreamPtr->tellp())
			{
				logOutput << "[NOTE] XML parsed successfully, no changes detected!\n";
			}
			result = 1;
		}
		else
		{
			logOutput.write("[WARNING] Failed to parse Options XML! Proceeding with default settings.\n", ULONG_MAX, lava::outputSplitter::sOS_CERR);
		}

		return result;
	}
	bool buildMenuOptionsTreeFromMenu(Page& mainPageIn, std::string xmlPathOut)
	{
		bool result = 1;

		pugi::xml_document MenuOptionsTree;

		pugi::xml_node commentNode = MenuOptionsTree.append_child(pugi::node_comment);
		commentNode.set_value("PowerPC Assembly Functions (Code Menu Building Utility)");
		commentNode = MenuOptionsTree.append_child(pugi::node_comment);
		commentNode.set_value("Important Note: Only change values noted as editable! Changing anything else will not work!");

		pugi::xml_node menuBaseNode = MenuOptionsTree.append_child(configXMLConstants::codeMenuTag.c_str());
		pugi::xml_attribute menuPathAttr = menuBaseNode.append_attribute(configXMLConstants::cmnuPathTag.c_str());
		menuPathAttr.set_value(getCMNUAbsolutePath().c_str());

		std::vector<Page*> Pages{ &mainPageIn };
		recursivelyFindPages(mainPageIn, Pages);

		for (unsigned long i = 0; i < Pages.size(); i++)
		{
			const Page* currPage = Pages[i];

			pugi::xml_node pageNode = menuBaseNode.append_child(configXMLConstants::menuLinePageTag.c_str());
			pugi::xml_attribute pageNameAttr = pageNode.append_attribute(configXMLConstants::nameTag.c_str());
			pageNameAttr.set_value(currPage->PageName.c_str());
			// For each kind of LineBehaviorFlag...
			for (std::size_t lbfItr = 0; lbfItr < Line::LineBehaviorFlags::lbf__COUNT; lbfItr++)
			{
				// ... grab its setting from the page!
				Line::LineBehaviorFlagSetting flagSetting = currPage->CalledFromLine->behaviorFlags[lbfItr];
				// If it's either on or forced labeling is on for it...
				if (flagSetting || flagSetting.forceXMLOutput)
				{
					// ... append the attribute with the appropriate value!
					pageNode.append_attribute(configXMLConstants::lineBehaviorFlagTags[lbfItr].c_str()).set_value(flagSetting);
				}
			}

			for (unsigned long u = 0; u < currPage->Lines.size(); u++)
			{
				const Line* currLine = currPage->Lines[u];

				std::vector<std::string_view> deconstructedText = splitLineContentString(currLine->Text);
				pugi::xml_node lineNode{};
				switch (currLine->type)
				{
				case SELECTION_LINE:
				{
					lineNode = pageNode.append_child(configXMLConstants::menuLineSelectionTag.c_str());
					pugi::xml_attribute lineNameAttr = lineNode.append_attribute(configXMLConstants::nameTag.c_str());
					lineNameAttr.set_value(deconstructedText[0].data());
					pugi::xml_node defaultValNode = lineNode.append_child(configXMLConstants::selectionDefaultTag.c_str());
					defaultValNode.append_attribute(configXMLConstants::indexTag.c_str()).set_value(std::to_string(currLine->Default).c_str());
					defaultValNode.append_attribute(configXMLConstants::editableTag.c_str()).set_value("true");
					for (unsigned long i = 1; i < deconstructedText.size(); i++)
					{
						pugi::xml_node optionNode = lineNode.append_child(configXMLConstants::selectionOptionTag.c_str());
						pugi::xml_attribute optionValueAttr = optionNode.append_attribute(configXMLConstants::valueTag.c_str());
						optionValueAttr.set_value(deconstructedText[i].data());
					}
					break;
				}
				case INTEGER_LINE:
				{
					lineNode = pageNode.append_child(configXMLConstants::menuLineIntTag.c_str());
					pugi::xml_attribute lineNameAttr = lineNode.append_attribute(configXMLConstants::nameTag.c_str());
					lineNameAttr.set_value(deconstructedText[0].data());
					pugi::xml_node minValNode = lineNode.append_child(configXMLConstants::valueMinTag.c_str());
					minValNode.append_attribute(configXMLConstants::valueTag.c_str()).set_value(std::to_string(currLine->Min).c_str());
					pugi::xml_node defaultValNode = lineNode.append_child(configXMLConstants::valueDefaultTag.c_str());
					defaultValNode.append_attribute(configXMLConstants::valueTag.c_str()).set_value(std::to_string(currLine->Default).c_str());
					defaultValNode.append_attribute(configXMLConstants::editableTag.c_str()).set_value("true");
					pugi::xml_node maxValNode = lineNode.append_child(configXMLConstants::valueMaxTag.c_str());
					maxValNode.append_attribute(configXMLConstants::valueTag.c_str()).set_value(std::to_string(currLine->Max).c_str());
					break;
				}
				case FLOATING_LINE:
				{
					lineNode = pageNode.append_child(configXMLConstants::menuLineFloatTag.c_str());
					pugi::xml_attribute lineNameAttr = lineNode.append_attribute(configXMLConstants::nameTag.c_str());
					lineNameAttr.set_value(deconstructedText[0].data());
					pugi::xml_node minValNode = lineNode.append_child(configXMLConstants::valueMinTag.c_str());
					minValNode.append_attribute(configXMLConstants::valueTag.c_str()).set_value(std::to_string(GetFloatFromHex(currLine->Min)).c_str());
					pugi::xml_node defaultValNode = lineNode.append_child(configXMLConstants::valueDefaultTag.c_str());
					defaultValNode.append_attribute(configXMLConstants::valueTag.c_str()).set_value(std::to_string(GetFloatFromHex(currLine->Default)).c_str());
					defaultValNode.append_attribute(configXMLConstants::editableTag.c_str()).set_value("true");
					pugi::xml_node maxValNode = lineNode.append_child(configXMLConstants::valueMaxTag.c_str());
					maxValNode.append_attribute(configXMLConstants::valueTag.c_str()).set_value(std::to_string(GetFloatFromHex(currLine->Max)).c_str());
					break;
				}
				default:
				{
					break;
				}
				}
				if (lineNode)
				{
					// For each kind of LineBehaviorFlag...
					for (std::size_t lbfItr = 0; lbfItr < Line::LineBehaviorFlags::lbf__COUNT; lbfItr++)
					{
						// ... grab its setting from the line!
						Line::LineBehaviorFlagSetting flagSetting = currLine->behaviorFlags[lbfItr];
						// If it's either on or forced labeling is on for it...
						if (flagSetting || flagSetting.forceXMLOutput)
						{
							// ... append the attribute with the appropriate value!
							lineNode.append_attribute(configXMLConstants::lineBehaviorFlagTags[lbfItr].c_str()).set_value(flagSetting);
						}
					}
				}
			}
		}

		MenuOptionsTree.save_file(xmlPathOut.c_str());

		return result;
	}
}