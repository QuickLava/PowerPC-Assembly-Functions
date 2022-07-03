# PowerPC Assembly Functions (Code Menu Building Utility)
A fork of the P+EX code menu which implements the ability to add characters to the ode menu without having to manually edit and recompile anything.
Adding new characters along with their IDs to the provided "EX_Characters.txt" and running the program is all you need to do.
Additionally, to avoid the need to manually specify output directories, output files will be created in the "Code_Menu_Output" directory (see below notes for further details). Note that a new file ("Code_Menu_Changelog.txt") will be generated when the program runs, outlining applied changes and the end state of the list.

## Instructions For Use Without Code Editing

If you're going to use this fork and don't intend to edit the code at all, simply download the [latest Release version](https://github.com/QuickLava/PowerPC-Assembly-Functions/releases), no need to download the source code. From there, extract the provided "PowerPC Assembly Functions", add new character entries as described below, then run the executable appropriate for your build:
- "PowerPC Assembly Functions.exe": Builds a code menu for console P+EX, producing the following files in the output folder:
	- data.cmnu (goes in pf/menu3/)
	- CodeMenu.txt
	- CodeMenu.asm (the above ASM.txt converted into assembly, goes in Source/Project+/)
	- Code_Menu_Changelog.txt
- "PowerPC Assembly Functions.exe (Dolphin)": Builds a code menu for offline Dolphin P+EX, producing the following files in the output folder:
	- data.cmnu (goes in pf/menu3/)
	- CodeMenu.txt
	- CodeMenu.asm (the above ASM.txt converted into assembly, goes in Source/Project+/)
	- Code_Menu_Changelog.txt
- "PowerPC Assembly Functions.exe (Netplay)": Builds a code menu for netplay Dolphin P+EX, producing the following files in the output folder:
	- dnet.cmnu (goes in pf/menu3/)
	- Net-CodeMenu.txt
	- Net-CodeMenu.asm (the above ASM.txt converted into assembly, goes in Source/Project+/)
	- Net-Code_Menu_Changelog.txt

Review the character list in the produced changelog to ensure that your characters were added correctly. If they were, place the produced files in their appropiate locations, run GCTRM to update your .gct files, and you should be good to go.

## Info On Automatic File Placement and GCTRM

If you place the included "PowerPC Assembly Functions" folder in its entirety into your build folder (ie. such that the entire folder is where your "pf", "rp", and "Source" folders are), the program will additionally offer to copy the produced files into their appropriate locations (as well as backup any existing files). If the program also detects the GCTRM executable and the necessary code files ("RSBE01.txt" and "BOOST.txt" for offline builds, or "NETPLAY.txt" and "NETBOOST.txt" for netplay builds), the program will also offer to run GCTRM for you, backing up and updating your .GCTs automatically.

Note: If the program offers to copy your files into the appropriate locations, but *doesn't* prompt you to run GCTRM, it's because it couldn't find the necessary code files in the build folder. This is especially prone to happenning when trying to run the "Netplay" executable without having "NETPLAY.txt" or "NETBOOST.txt" files in your build folder, as these files do not come with some versions of P+EX. Make sure those exist in your build folder, then run the program again.

Note: Unlike previous releases of this program, you need to copy the full "PowerPC Assembly Functions" folder in its entirety into your build folder in order to enable these automation features.

## Adding to EX_Characters.txt
New lines are added in the following format:

	"Character Name" = ID
	
So, for example, the following line...

	"Daisy" = 80
	
...would add an entry for a character called Daisy with an ID of 80.

You can change the IDs for existing characters this way as well. For example, adding the line...

	"Mario" = 10
	
...would change Mario's ID from 0 to 10.

ID values are processed in decimal by default, but hex values (prefixed with "0x") are supported as well. So the following line...
	
	"Daisy" = 0x50
	
... would be functionally identical to the earlier Daisy example.

You can also use quotes in character names by escaping them with a backslash ('\\'). So the line...

	"\"Daisy\"" = 80

... would create a clone with the name "Daisy", *with quotes*.

Lastly, adding a hashtag ('#') or forward slash ('/') to the beginning of a line will comment out that line, having the program disregard it completely. So the following lines...

	#This is a comment
	//So is this, as well as the next one
	/"Daisy" = 80

... will all be treated as comments and ignored by the program.

***Important Note***: Characters in this file are added *in addition to* the characters present in stock P+EX. This includes Knuckles and Ridley, and in the future will include any other characters added to the base build. This means that the only characters you need to add to this file are ones not present in the base P+EX.

# Other Changes
- A Character Slot ID enum has been added to "Code Menu.h". This is purely to make manually adding IDs a bit more straightforward, and doesn't alter the functionality of the program at all.

- The top of "PowerPC Assembly Functions.h" now features some additional configuration options. Of particular note is the "MAIN_FOLDER" value, which determines what the expected name of the build folder will be. Another useful option is the "COLLECT_EXTERNAL_EX_CHARACTERS" toggle, which enables or disables reading in characters from external text files. Note that this is actually useable on non P+EX builds as well.

- "Code Menu.cpp" is now where default character lists and most other string constants (eg. those that govern file names, autoGCTRM and fileplacement, etc.) are now defined.

- "ControlCodes.cpp" has been edited to dynamically piece together the path to code menu from the string constants defined in "PowerPC Assembly Functions.cpp" and in "Code Menu.cpp".

