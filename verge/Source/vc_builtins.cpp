/// The VERGE 3 Project is originally by Ben Eirich and is made available via
///  the BSD License.
///
/// Please see LICENSE in the project's root directory for the text of the
/// licensing agreement.  The CREDITS file in the same directory enumerates the
/// folks involved in this public build.
///
/// If you have altered this source file, please log your name, date, and what
/// changes you made below this line.

#include "xerxes.h"
#include "opcodes.h"
#include <vector>


static VcFunctionDecl _libfuncs[NUM_LIBFUNCS] = {
	{"5", "Exit", "3" },
	{"5", "Log", "3" },
	{"1", "NewImage", "11" },
	{"1", "MakeColor", "111" },
	{"5", "SetLucent", "1" },
	{"5", "SetClip", "11111" },
	{"1", "LoadImage", "3" },
	{"1", "LoadImage0", "3" },
	{"5", "ShowPage", "" },
	{"5", "UpdateControls", "" },
	{"5", "Blit", "1111" },
	{"5", "TBlit", "1111" },
	{"5", "AdditiveBlit", "1111" },
	{"5", "TAdditiveBlit", "1111" },
	{"5", "SubtractiveBlit", "1111" },
	{"5", "TSubtractiveBlit", "1111" },
	{"5", "WrapBlit", "1111" },
	{"5", "TWrapBlit", "1111" },
	{"5", "ScaleBlit", "111111" },
	{"5", "TScaleBlit", "111111" },
	{"1", "RGB", "111" },
	{"5", "SetPixel", "1111" },
	{"1", "GetPixel", "111" },
	{"5", "Line", "111111" },
	{"5", "Rect", "111111" },
	{"5", "RectFill", "111111" },
	{"5", "Circle", "111111" },
	{"5", "CircleFill", "111111" },
	{"1", "GetR", "1" },
	{"1", "GetG", "1" },
	{"1", "GetB", "1" },
	{"5", "RotScale", "111111" },
	{"5", "FreeImage", "1" },
	{"1", "LoadSong", "3" },
	{"5", "PlaySong", "1" },
	{"5", "StopSong", "1" },
	{"5", "PlayMusic", "3" },
	{"5", "StopMusic", "" },
	{"5", "StopSound", "1" },
	{"5", "FreeSong", "1" },
	{},
	{"5", "Silhouette", "11111" },
	{"5", "GrabRegion", "11111111" },
	{"5", "TGrabRegion", "11111111" },
	{"5", "Mosaic", "111" },
	{"1", "DuplicateImage", "1" },
	{"5", "Triangle", "11111111" },
	{"5", "BlitTile", "1111" },
	{"5", "TBlitTile", "1111" },
	{},
	{},
	{"1", "ImageWidth", "1" },
	{"1", "ImageHeight", "1" },
	{"1", "LoadFontEx", "311" },
	{"5", "EnableVariableWidth", "1" },
	{"5", "PrintString", "11113" },
	{"5", "PrintRight", "11113" },
	{"5", "PrintCenter", "11113" },
	{"1", "TextWidth", "13" },
	{"1", "FreeFont", "1" },
	{"1", "Random", "11" },
	{"1", "len", "3" },
	{"1", "val", "3" },
	{"1", "Unpress", "1" },
	{"1", "DebugBreakpoint", "" },
	{"1", "FileOpen", "31" },
	{"5", "FileClose", "1" },
	{"5", "FileWrite", "13" },
	{"5", "FileWriteln", "13" },
	{"3", "FileReadln", "1" },
	{"3", "FileReadToken", "1" },
	{"5", "FileSeekLine", "11" },
	{"1", "LoadSound", "3" },
	{"5", "FreeSound", "1" },
	{"1", "PlaySound", "11" },
	{"1", "CallFunction", "34" }, // Overkill (2007-05-02}: Callfunction accepts varargs.
	{"1", "AssignArray", "13" },
	{"5", "FileSeekPos", "111" },
	{"1", "FileCurrentPos", "1" },
	{"5", "FileWriteByte", "11" },
	{"5", "FileWriteWord", "11" },
	{"5", "FileWriteQuad", "11" },
	{"5", "FileWriteString", "13" },
	{"1", "FileReadByte", "1" },
	{"1", "FileReadWord", "1" },
	{"1", "FileReadQuad", "1" },
	{"3", "FileReadString", "1" },
	{"1", "sqrt", "1" },
	{"1", "pow", "11" },
	{"5", "SetAppName", "3" },
	{"5", "SetResolution", "11" },
	{"5", "BlitLucent", "11111" },
	{"5", "TBlitLucent", "11111" },
	{"5", "Map", "3" },
	{"1", "strcmp", "33" },
	{"3", "strdup", "31" },
	{"5", "HookTimer", "8" },
	{"5", "HookRetrace", "8" },
	{"5", "HookEntityRender", "13" },
	{"5", "HookKey", "13" },
	{"5", "HookButton", "13" },
	{"5", "BlitEntityFrame", "11111" },
	{"5", "SetEntitiesPaused", "7" },
	{"7", "GetObsPixel", "11" },
	{"1", "GetTile", "111" },
	{"5", "SetTile", "1111" },
	{"1", "GetZone", "11" },
	{"5", "SetZone", "111" },
	{"5", "MessageBox", "3" },
	{"1", "sin", "1" },
	{"1", "cos", "1" },
	{"1", "tan", "1" },
	{"5", "SuperSecretThingy", "11111" },
	{"5", "BlitWrap", "1111" },
	{"5", "ColorFilter", "11" },
	{"1", "ImageShell", "11111" },
	{"1", "malloc", "1" },
	{"5", "MemFree", "1" },
	{"5", "MemCopy", "111" },
	{"1", "asin", "1" },
	{"1", "acos", "1" },
	{"1", "atan", "1" },
	{"1", "AlphaBlit", "11111" },
	{"1", "WindowCreate", "11113" },
	{"1", "WindowGetImage", "1" },
	{"5", "WindowClose", "1" },
	{"5", "WindowSetSize", "111" },
	{"5", "WindowSetResolution", "111" },
	{"5", "WindowSetPosition", "111" },
	{"5", "WindowSetTitle", "13" },
	{"5", "WindowHide", "1" },
	{"5", "WindowShow", "1" },
	{"1", "WindowGetXRes", "1" },
	{"1", "WindowGetYRes", "1" },
	{"1", "WindowGetWidth", "1" },
	{"1", "WindowGetHeight", "1" },
	{"5", "WindowPositionCommand", "1111" },
	{"5", "SetSongPaused", "17" },
	{"5", "SetSongVolume", "11" },
	{"1", "GetSongVolume", "1" },
	{"1", "GetSongPos", "1" },
	{"5", "SetSongPos", "11" },
	{"1", "TokenCount", "33" },
	{"3", "GetToken", "331" },
	{"3", "ToUpper", "3" },
	{"3", "ToLower", "3" },
	{"1", "LoadFont", "3" },
	{"1", "FontHeight", "1" },
	{"1", "MixColor", "111" },
	{"3", "chr", "1" },
	{"1", "PlayMovie", "3" },
	{"1", "MovieLoad", "31" },
	{"1", "MoviePlay", "11" },
	{"1", "MovieGetImage", "1" },
	{"5", "MovieRender", "1" },
	{"5", "MovieClose", "1" },
	{"1", "MovieGetCurrFrame", "1" },
	{"1", "MovieGetFramerate", "1" },
	{"5", "MovieNextFrame", "1" },
	{"5", "MovieSetFrame", "11" },
	{"5", "Render", "" },
	{"1", "GetObs", "11" },
	{"5", "SetObs", "111" },
	{"1", "EntitySpawn", "113" },
	{"5", "SetPlayer", "1" },
	{"5", "EntityStalk", "11" },
	{"5", "EntityMove", "13" },
	{"5", "SetMusicVolume", "1" },
	{"5", "PlayerMove", "3" },
	{"5", "ChangeCHR", "13" },
	{"5", "EntitySetWanderZone", "1" },
	{"5", "EntitySetWanderRect", "11111" },
	{"5", "EntityStop", "1" },
	{"5", "EntitySetWanderDelay", "11" },
	{"5", "SetRandSeed", "1" },
	{"5", "ResetSprites", "" },
	{"1", "GetSprite", "" },
	{"5", "RenderMap", "111" },
	{"5", "SetButtonKey", "11" },
	{"5", "SetButtonJB", "11" },
	{}, // {"7", "FunctionExists", "3" }, was promoted to an opcode.
	{"1", "atan2", "11" },
	{"5", "CopyImageToClipboard", "1" },
	{"1", "GetImageFromClipboard", "" },
	{"5", "SetInt", "31" },
	{"1", "GetInt", "3" },
	{"5", "SetString", "33" },
	{"3", "GetString", "3" },
	{"5", "SetIntArray", "311" },
	{"1", "GetIntArray", "31" },
	{"5", "SetStringArray", "313" },
	{"3", "GetStringArray", "31" },
	{"5", "FlipBlit", "117711" },
	{"1", "Connect", "3" },
	{"1", "GetConnection", "" },
	{"7", "SocketConnected", "1" },
	{"7", "SocketHasData", "1" },
	{"3", "SocketGetString", "1" },
	{"5", "SocketSendString", "13" },
	{"5", "SocketClose", "1" },
	{"5", "Sleep", "1" },
	{"5", "SetCustomColorFilter", "11" },
	{"5", "SocketSendInt", "11" },
	{"1", "SocketGetInt", "1" },
	{},
	{},
	{"3", "GetUrlText", "3" },
	{"1", "GetUrlImage", "3" },
	{"5", "SocketSendFile", "13" },
	{"3", "SocketGetFile", "13" },
	{"3", "ListFilePattern", "3" },
	{"7", "ImageValid", "1"},
	{"1", "asc", "3"},
	{"7", "FileEOF", "1"},
	{"1", "DictNew", ""},
	{"5", "DictFree", "1"},
	{"3", "DictGetString", "13"},
	{"5", "DictSetString", "133"},
	{"7", "DictContains", "13"},
	{"1", "DictSize", "1"},
	{"1", "DictGetInt", "13"},
	{"5", "DictSetInt", "131"},
	{"5", "DictRemove", "13"},
	{"1", "LoadImage8", "3" },
	{"5", "AbortMovie", "" },
	{"1", "max", "11" },
	{"1", "min", "11" },
	{"1", "abs", "1" },
	{"1", "sgn", "1" },
	{"1", "GetTokenPos", "3311"},
	{"3", "TokenLeft", "331"},
	{"3", "TokenRight", "331"},
	{"1", "strpos", "331"},
	{"3", "strovr", "331"},
	{"3", "WrapText", "131"},
	{"5", "RectVGrad", "1111111"}, // Overkill (2006-02-04, 2006-06-25}: Vertical gradient
	{"5", "RectHGrad", "1111111"}, // Overkill (2006-02-04, 2006-06-25}: Horizontal gradient
	{"1", "cbrt", "1"}, // Overkill (2006-06-25}: Returns the cube root of a number.
	{"3", "GetKeyBuffer", ""}, // Overkill (2006-06-30}: Gets the contents of the key buffer.
	{"5", "FlushKeyBuffer", ""}, // Overkill (2006-06-30}: Clears the contents of the key buffer.
	{"5", "SetKeyDelay", "1"}, // Overkill (2006-06-30}: Sets the delay in centiseconds before key repeat.
	{"5", "FileWriteCHR", "11"}, // Overkill (2006-07-20}: Saves a CHR file, using an open file handle, saving the specified entity.
	{"5", "FileWriteMAP", "1"}, // Overkill (2006-07-20}: Saves a MAP file, using an open file handle, saving the current map.
	{"5", "FileWriteVSP", "1"}, // Overkill (2006-07-20}: Saves a VSP file, using an open file handle, saving the current map's VSP.
	{"5", "CompileMap", "3"}, // Overkill (2006-07-20}: Compiles the specified MAP filename.
	{"5", "RectRGrad", "1111111"}, // janus (2006-07-22}: Radial gradient
	{"5", "Rect4Grad", "111111111"}, // janus (2006-07-22}: 4-point (4-corner} gradient
	{"3", "ListStructMembers", "3"}, // Overkill (2006-08-16}: Lists the members of a struct.
	{"1", "CopyArray", "33"}, // Overkill (2006-08-16}: Copies an array to another array.
	{"7", "SoundIsPlaying", "1"}, // Overkill (2006-11-20}: Determines whether or not a given sound channel is in use.
	{"1", "GetH", "1"}, // Overkill (2007-05-04}: Gets the hue of a color
	{"1", "GetS", "1"}, // Overkill (2007-05-04}: Gets the saturation of a color
	{"1", "GetV", "1"}, // Overkill (2007-05-04}: Gets the value/brightness of a color
	{"1", "HSV", "111"}, // Overkill (2007-05-04}: Creates a color using the HSV color model.
	{"5", "HueReplace", "1111"}, // Overkill (2007-05-04}: Finds a hue range and replaces it with another hue in an image
	{"5", "ColorReplace", "111"}, // Overkill (2007-05-04}: Finds a color and replaces it with another color in an image
	{"1", "fatan", "1"}, // Overkill (2006-09-18}: Fixed point angles for precision!
	{"1", "fatan2", "11"},
	{"1", "fasin", "1"},
	{"1", "facos", "1"},
	{"1", "fsin", "1"},
	{"1", "fcos", "1"},
	{"1", "ftan", "1"},
	{"1", "SetCharacterWidth", "111"},
	{"3", "DictListKeys", "13"},
	{"3", "ListBuiltinFunctions", ""},
	{"3", "ListBuiltinVariables", ""},
	{"3", "ListBuiltinDefines", ""},
	{"1", "GetPlayer", ""}, // Kildorf (2007-10-12}: Return the entity number of the player.
	{"1", "GetUserSystemVcFunctionCount", ""},	// Grue
	{"3", "GetUserSystemVcFunctionByIndex", "1"},	// Grue
	{"5", "SetConnectionPort", "1"}, // Overkill (2008-04-17}: Socket port can be switched to something besides 45150.
	{"3", "SocketGetRaw", "11"}, // Overkill (2008-04-17}: Sockets can send and receive raw length-delimited strings
	{"5", "SocketSendRaw", "13"},
	{"1", "SocketByteCount", "1"}, // Overkill (2008-04-20}: Peek at how many bytes are in buffer. Requested by ustor.
	{"3", "GetSystemSaveDir", "3"},
	{"1", "GetInputKillSwitch", ""},
	{"5", "SetInputKillSwitch", "1"},
	{"7", "IntExists", "3"},		// Grue, (2008-12-26)
	{"7", "StrExists", "3"},
	{"5", "BlitObs", "1111" },
	{"5", "HookMapLoad", "8" }   // kdf (2011-01-10)
};

std::vector<VcFunction> libfuncs;

void vc_initBuiltins() {
	libfuncs.reserve(NUM_LIBFUNCS);
	for(int i=0;i<NUM_LIBFUNCS;i++)
		libfuncs.emplace_back(_libfuncs[i]);
}

char* libvars[NUM_HVARS][3] = {
// type,    identifier,    dimlist
	{"1", "systemtime", "" }, // index 0
	{"1", "timer", "" },
	{"7", "key", "1" }, // Now a "boolean" in Lua.
	{"1", "lastpressed", "" },
	{"1", "mouse.x", "" },
	{"1", "mouse.y", "" },
	{"7", "mouse.l", "" },
	{"7", "mouse.r", "" },
	{"7", "mouse.m", "" },
	{"1", "mouse.w", "" },
	{"1", "sysdate.year", "" },// index 10
	{"1", "sysdate.month", "" },
	{"1", "sysdate.day", "" },
	{"1", "sysdate.dayofweek", "" },
	{"1", "systime.hour", "" },
	{"1", "systime.minute", "" },
	{"1", "systime.second", "" },
	{"1", "joystick", "" },
	{"7", "joy.active", "" },
	{"7", "joy.up", "" },
	{"7", "joy.down" ,"" },// index 20
	{"7", "joy.left", "" },
	{"7", "joy.right", "" },
	{"1", "joy.analogx", "" },
	{"1", "joy.analogy", "" },
	{"7", "joy.button", "1" },
	{"7", "up", "" },
	{"7", "down", "" },
	{"7", "left", "" },
	{"7", "right", "" },
	{"7", "b1", "" },// index 30
	{"7", "b2", "" },
	{"7", "b3", "" },
	{"7", "b4", "" },
	{"1", "event.tx", "" },
	{"1", "event.ty", "" },
	{"1", "event.zone", "" },
	{"1", "event.entity", "" },
	{"1", "event.param", "" },
	{"1", "xwin", "" },
	{"1", "ywin", "" },// index 40
	{"1", "cameratracking", "" },
	{"1", "entities", "" }, //entities 42
	{"1", "entity.x", "1" },
	{"1", "entity.y", "1" },
	{"1", "entity.specframe", "1" },
	{"1", "entity.frame", "1" },
	{"1", "entity.hotx", "1" },
	{"1", "entity.hoty", "1" },
	{"1", "entity.hotw", "1" },
	{"1", "entity.hoth", "1" },// index 50
	{"1", "transcolor", "" },
	{"1", "_skewlines", "1" },
	{"1", "dma.byte", "1" },
	{"1", "dma.word", "1" },
	{"1", "dma.quad", "1" },
	{"1", "dma.sbyte", "1" },
	{"1", "dma.sword", "1" },
	{"1", "dma.squad", "1" },
	{"1", "gamewindow", "" },
	{"1", "lastkey", ""},// index 60
	{"1", "entity.movecode", "1"},
	{"1", "entity.face", "1"},
	{"1", "entity.speed", "1"},
	{"7", "entity.visible", "1"},
	{"3", "entity.script", "1" },
	{"1", "sprite.x", "1" },
	{"1", "sprite.y", "1" },
	{"1", "sprite.sc", "1" },
	{"1", "sprite.image", "1" },
	{"1", "sprite.lucent", "1" },// index 70
	{"1", "sprite.addsub", "1" },
	{"1", "sprite.alphamap", "1"},
	{"1", "sprite.thinkrate", "1" }, //ni 73
	{"3", "sprite.thinkproc", "1" }, //ni 74
	{"1", "sprite.xflip", "1"}, //ni 75
	{"1", "sprite.yflip", "1"}, //ni 76
	{"1", "sprite.ybase", "1"}, //ni 77
	{"7", "entity.obstruct", "1"},
	{"7", "entity.obstructable", "1"},	//79
	{"1", "curmap.w", ""},// index 80
	{"1", "curmap.h", ""},
	{"1", "curmap.startx", ""},
	{"1", "curmap.starty", ""},
	{"3", "curmap.name", ""},
	{"3", "curmap.rstring", ""},
	{"3", "curmap.music", ""},
	{"1", "curmap.tileset", ""}, //87
	{"3", "zone.name", "1"},	// Overkill (2006-06-25):
	{"3", "zone.event", "1"},	// Now these two variables have a use!
	{"1", "event.sprite", ""},// index 90
	{"1", "layer.w", "1" },
	{"1", "layer.h", "1" },
	{"7", "layer.visible", "1" }, //93
	{"1", "layer.lucent", "1" },
	{"3", "clipboard.text", "" },
	{"1", "cameratracker", "" },//96
    {"1", "layer.parallaxx", "1"},
    {"1", "layer.parallaxy", "1"},
    {"3", "curmap.path", ""},
    {"3", "entity.chr", "1"},// index 100
	{"1", "playerstep", ""},
	{"1", "playerdiagonals", ""},
	{"7", "window.active", ""},
	{"3", "curmap.savevsp", "" }, // Overkill (2006-07-20): The VSP to save as.
	{"1", "sprite.ent", "1" },
	{"1", "sprite.silhouette", "1" },
	{"1", "sprite.color", "1" },
	{"1", "sprite.wait", "1" },
	{"1", "sprite.onmap", "1" },
	{"1", "sprite.layer", "1" },// index 110
	{"1", "entity.lucent", "1" },
	{"1", "sprite.timer", "1" },
	{"1", "entity.framew", "1" },
	{"1", "entity.frameh", "1" },
	{"3", "entity.description", "1" }, // Overkill (2006-07-30): Fix: Now it's a string!
	{"1", "@__argument.length", "" }, // Overkill (2007-05-02): The vararg builtins, keep these things private!
	{"1", "@__argument.int", "1" },
	{"1", "@__argument.is_int", "1" },
	{"1", "@__argument.is_string", "1" },
	{"3", "@__argument.string", "1" },// index 120
	{"3", "trigger.onStep", "" },// index 121
	{"3", "trigger.afterStep", "" },// index 122
	{"3", "trigger.beforeEntityScript", "" },// index 123
	{"3", "trigger.afterEntityScript", "" },// index 124
	{"3", "trigger.onEntityCollide", "" },// index 125
	{"1", "event.entity_hit", "" }, //126
	{"3", "trigger.after_playermove", "" }, //127
	{"1", "curmap.layers", "" }, //128

	{"1", "zone.method", "1"},	// 129
	{"1", "zone.percent", "1"},	// 130
	{"1", "zone.delay", "1"},	// 131
	{"1", "curmap.zones", ""},	// 132
	
	{"1", "curmap.numobs", ""}, // 133
	{"3", "curmap.startupscript", ""}, // 134
	
	
}; //when adding, remember to increment NUM_HVARS

HdefDecl hdefs[NUM_HDEFS] = {
  /* identifier,    value */
	{"_version",	DEF_VERSION, Define::Type_PleaseQuote },
	{"_build",      DEF_BUILD, Define::Type_PleaseQuote },
    {"_os",         DEF_OS, Define::Type_PleaseQuote},
	{"screen",		"1", Define::Type_Raw },
	{"FILE_READ",	"1", Define::Type_Raw  },
	{"FILE_WRITE",	"2", Define::Type_Raw  },
	{"FILE_WRITE_APPEND",	"3", Define::Type_Raw  }, // Overkill (2006-07-05): Append mode added.
	{"SEEK_SET",    "0", Define::Type_Raw  },
	{"SEEK_CUR",    "1", Define::Type_Raw  },
	{"SEEK_END",    "2", Define::Type_Raw  },
	{"SCAN_ESC",	"01", Define::Type_Raw  },
	{"SCAN_1",		"02", Define::Type_Raw  },
	{"SCAN_2",		"03", Define::Type_Raw  },
	{"SCAN_3",		"04", Define::Type_Raw  },
	{"SCAN_4",		"05", Define::Type_Raw  },
	{"SCAN_5",		"06", Define::Type_Raw  },
	{"SCAN_6",		"07", Define::Type_Raw  },
	{"SCAN_7",		"08", Define::Type_Raw  },
	{"SCAN_8",		"09", Define::Type_Raw  },
	{"SCAN_9",		"10", Define::Type_Raw  },
	{"SCAN_0",		"11", Define::Type_Raw  },
	{"SCAN_MINUS",	"12", Define::Type_Raw  },
	{"SCAN_EQUALS", "13", Define::Type_Raw  },
	{"SCAN_BACKSP", "14", Define::Type_Raw  },
	{"SCAN_TAB",	"15", Define::Type_Raw  },
	{"SCAN_Q",		"16", Define::Type_Raw  },
	{"SCAN_W",		"17", Define::Type_Raw  },
	{"SCAN_E",		"18", Define::Type_Raw  },
	{"SCAN_R",		"19", Define::Type_Raw  },
	{"SCAN_T",		"20", Define::Type_Raw  },
	{"SCAN_Y",		"21", Define::Type_Raw  },
	{"SCAN_U",		"22", Define::Type_Raw  },
	{"SCAN_I",		"23", Define::Type_Raw  },
	{"SCAN_O",		"24", Define::Type_Raw  },
	{"SCAN_P",		"25", Define::Type_Raw  },
	{"SCAN_LANGLE",	"26", Define::Type_Raw  },
	{"SCAN_RANGLE",	"27", Define::Type_Raw  },
	{"SCAN_ENTER",	"28", Define::Type_Raw  },
	{"SCAN_CTRL",	"29", Define::Type_Raw  },
	{"SCAN_A",		"30", Define::Type_Raw  },
	{"SCAN_S",		"31", Define::Type_Raw  },
	{"SCAN_D",		"32", Define::Type_Raw  },
	{"SCAN_F",		"33", Define::Type_Raw  },
	{"SCAN_G",		"34", Define::Type_Raw  },
	{"SCAN_H",		"35", Define::Type_Raw  },
	{"SCAN_J",		"36", Define::Type_Raw  },
	{"SCAN_K",		"37", Define::Type_Raw  },
	{"SCAN_L",		"38", Define::Type_Raw  },
	{"SCAN_SCOLON", "39", Define::Type_Raw  },
	{"SCAN_QUOTA",  "40", Define::Type_Raw  },
	{"SCAN_RQUOTA", "41", Define::Type_Raw  },
	{"SCAN_LSHIFT",	"42", Define::Type_Raw  },
	{"SCAN_BSLASH", "43", Define::Type_Raw  },
	{"SCAN_Z",		"44", Define::Type_Raw  },
	{"SCAN_X",		"45", Define::Type_Raw  },
	{"SCAN_C",		"46", Define::Type_Raw  },
	{"SCAN_V",		"47", Define::Type_Raw  },
	{"SCAN_B",		"48", Define::Type_Raw  },
	{"SCAN_N",		"49", Define::Type_Raw  },
	{"SCAN_M",		"50", Define::Type_Raw  },
	{"SCAN_COMMA",	"51", Define::Type_Raw  },
	{"SCAN_DOT",	"52", Define::Type_Raw  },
	{"SCAN_SLASH",	"53", Define::Type_Raw  },
	{"SCAN_RSHIFT",	"54", Define::Type_Raw  },
	{"SCAN_STAR",	"55", Define::Type_Raw  },
	{"SCAN_ALT",	"56", Define::Type_Raw  },
	{"SCAN_SPACE",	"57", Define::Type_Raw },
	{"SCAN_CAPS",	"58", Define::Type_Raw  },
	{"SCAN_F1",		"59", Define::Type_Raw  },
	{"SCAN_F2",		"60", Define::Type_Raw  },
	{"SCAN_F3",		"61", Define::Type_Raw  },
	{"SCAN_F4",		"62", Define::Type_Raw  },
	{"SCAN_F5",		"63", Define::Type_Raw  },
	{"SCAN_F6",		"64", Define::Type_Raw  },
	{"SCAN_F7",		"65", Define::Type_Raw  },
	{"SCAN_F8",		"66", Define::Type_Raw  },
	{"SCAN_F9",		"67", Define::Type_Raw  },
	{"SCAN_F10",	"68", Define::Type_Raw  },
	{"SCAN_NUMLOCK","69", Define::Type_Raw  },
	{"SCAN_SCRLOCK","70", Define::Type_Raw  },
	{"SCAN_HOME",	"71", Define::Type_Raw  },
	{"SCAN_UP",		"72", Define::Type_Raw  },
	{"SCAN_PGUP",	"73", Define::Type_Raw  },
	{"SCAN_GMINUS",	"74", Define::Type_Raw  },
	{"SCAN_LEFT",	"75", Define::Type_Raw  },
	{"SCAN_PAD_5",	"76", Define::Type_Raw  },
	{"SCAN_RIGHT",	"77", Define::Type_Raw  },
	{"SCAN_GPLUS",	"78", Define::Type_Raw  },
	{"SCAN_END",	"79", Define::Type_Raw  },
	{"SCAN_DOWN",	"80", Define::Type_Raw  },
	{"SCAN_PGDN",	"81", Define::Type_Raw  },
	{"SCAN_INSERT",	"82", Define::Type_Raw  },
	{"SCAN_DEL",	"83", Define::Type_Raw  },
	{"SCAN_F11",	"87", Define::Type_Raw  },
	{"SCAN_F12",	"88", Define::Type_Raw  },
	{"CF_NONE",		"0", Define::Type_Raw   },
    {"CF_GREY",     "1", Define::Type_Raw },
    {"CF_GREYINV",  "2", Define::Type_Raw },
    {"CF_INV",      "3", Define::Type_Raw },
    {"CF_RED",      "4", Define::Type_Raw },
    {"CF_GREEN",    "5", Define::Type_Raw },
    {"CF_BLUE",     "6", Define::Type_Raw },
	{"CF_CUSTOM",   "7", Define::Type_Raw },
	{"FIXED_PI",	"205887", Define::Type_Raw },

	{"FACE_UP",		"1", Define::Type_Raw },
	{"FACE_DOWN",	"2", Define::Type_Raw },
	{"FACE_LEFT",	"3", Define::Type_Raw },
	{"FACE_RIGHT",	"4", Define::Type_Raw },

	{"TRUE",		"1", Define::Type_Raw },
	{"FALSE",		"0", Define::Type_Raw },

	{"UNPRESS_ALL",	"9", Define::Type_Raw },

};
