/// The VERGE 3 Project is originally by Ben Eirich and is made available via
///  the BSD License.
///
/// Please see LICENSE in the project's root directory for the text of the
/// licensing agreement.  The CREDITS file in the same directory enumerates the
/// folks involved in this public build.
///
/// If you have altered this source file, please log your name, date, and what
/// changes you made below this line.


/******************************************************************
 * verge3: g_startup.cpp                                          *
 * copyright (c) 2001 vecna                                       *
 ******************************************************************/

#include "xerxes.h"
#include "garlick.h"
#include "lua_main.h"
#include "opcodes.h"

#include <memory>
#include <functional>

/****************************** data ******************************/

int v3_xres=320, v3_yres=240, v3_bpp;
int v3_window_xres=0, v3_window_yres = 0;
// Overkill (2010-04-29): Aspect ratio enforcing.
ScaleFormat v3_scale_win = SCALE_FORMAT_ASPECT, v3_scale_full = SCALE_FORMAT_STRETCH;

bool windowmode = true;
bool sound = true;
bool cheats = false;
char mapname[255];
bool automax = true;
bool editcode = false;
int gamerate = 100;
int soundengine = 0;

int cf_r1, cf_g1, cf_b1;
int cf_r2, cf_g2, cf_b2;
int cf_rr, cf_gr, cf_br;

/****************************** code ******************************/

void LoadConfig()
{
	cfg_Init("verge.cfg");
	cfg_SetDefaultKeyValue("startmap", "");

	if (cfg_KeyPresent("xres"))
		v3_xres = cfg_GetIntKeyValue("xres");
	if (cfg_KeyPresent("yres"))
		v3_yres = cfg_GetIntKeyValue("yres");
    // Overkill (2010-04-29): Scaling policies.
    if (cfg_KeyPresent("scalewin"))
    {
        int value = cfg_GetIntKeyValue("scalewin");
        if(value >= 0 && value < SCALE_FORMAT_COUNT)
        {
            v3_scale_win = (ScaleFormat) value;
        }
    }
    if (cfg_KeyPresent("scalefull"))
    {
        int value = cfg_GetIntKeyValue("scalefull");
        if(value >= 0 && value < SCALE_FORMAT_COUNT)
        {
            v3_scale_full = (ScaleFormat) value;
        }
    }
	if (cfg_KeyPresent("window_x_res"))
		v3_window_xres = cfg_GetIntKeyValue("window_x_res");
	if (cfg_KeyPresent("window_y_res"))
		v3_window_yres = cfg_GetIntKeyValue("window_y_res");

	if (cfg_KeyPresent("windowmode"))
		windowmode = cfg_GetIntKeyValue("windowmode") ? true : false;
	if (cfg_KeyPresent("nosound"))
		sound = cfg_GetIntKeyValue("nosound") ? false : true;
	if (cfg_KeyPresent("soundengine"))
		soundengine = cfg_GetIntKeyValue("soundengine");
	if (cfg_KeyPresent("automax"))
		automax = cfg_GetIntKeyValue("automax") ? true : false;
	if (cfg_KeyPresent("startmap"))
		strcpy(mapname, cfg_GetKeyValue("startmap"));
	if (cfg_KeyPresent("appname"))
		setWindowTitle(cfg_GetKeyValue("appname"));
	if (cfg_KeyPresent("gamerate"))
		gamerate = cfg_GetIntKeyValue("gamerate");
	if (cfg_KeyPresent("v3isuberlikethetens"))
		cheats = true;
	if (cfg_KeyPresent("editcode"))
		editcode = cfg_GetIntKeyValue("editcode") ? true : false;
	if (cfg_KeyPresent("logconsole"))
	{
		logconsole = true;
		initConsole();
	} else if (cfg_KeyPresent("logconsole-normalstdout")) {
		logconsole = true;
	}

	void platform_ProcessConfig();
	platform_ProcessConfig();
}

int getInitialWindowXres() {
	return v3_window_xres;
}

int getInitialWindowYres() {
	return v3_window_yres;
}

void InitVideo()
{
	//initialize the image handles
	//allocate one dummy, one for screen, and one for the active vsp
	Handle::forceAlloc(HANDLE_TYPE_IMAGE,3);

	if (!windowmode)
	{
		int result = vid_SetMode(v3_xres, v3_yres, v3_bpp, 0, MODE_SOFTWARE);
		if (!result)
			result = vid_SetMode(v3_xres, v3_yres, v3_bpp, 1, MODE_SOFTWARE);
		if (!result)
			err("Could not set video mode!");
		return;
	}
	if (windowmode)
	{
		int result = vid_SetMode(v3_xres, v3_yres, v3_bpp, 1, MODE_SOFTWARE);
		if (!result)
			err("Could not set video mode!");
		return;
	}
}

void ShowPage()
{
	HookTimer();
	TimedProcessSprites();
	RenderSprites();
	Flip();
}

#ifndef NOSPLASHSCREEN
#ifdef __APPLE__
#include "macsplash.h"
#endif
#ifdef __LINUX__
#include "vcsplash.h"
#endif
#ifdef __WIN32__
#include "vcsplash.h"
#endif
#endif

#ifdef ALLOW_SCRIPT_COMPILATION
void DisplayCompileImage()
{
#ifndef NOSPLASHSCREEN
	FILE *f = fopen("__temp__img$$$.gif","wb");
	if (!f) return; // oh well, we tried
	fwrite(compileimg, 1, COMPILEIMG_LEN, f);
	fclose(f);
	image *splash = xLoadImage("__temp__img$$$.gif");
	remove("__temp__img$$$.gif");
	DrawRect(0, 0, screen->width, screen->height, 0, screen);
	Blit((screen->width/2)-(splash->width/2), (screen->height/2)-(splash->height/2), splash, screen);
	delete splash;
	ShowPage();
#endif
}
#endif

//---
//setup garlick to use vfile
void *Garlick_vf_open(const char *fname) { return vopen(fname); }
void Garlick_vf_close(void *handle) { vclose((VFILE*)handle); }
size_t Garlick_vf_read(void *ptr, size_t elemsize, size_t amt, void *handle) { return vread((char *)ptr, elemsize*amt,(VFILE*)handle); }
long Garlick_vf_tell(void *handle) { return vtell((VFILE*)handle); }
int Garlick_vf_seek(void *handle, long offset, int origin) { vseek((VFILE*)handle,offset,origin); return 0; }
void Garlick_error(const char *msg) { err(msg); }
void InitGarlick() {
	Garlick_cb_open = Garlick_vf_open;
	Garlick_cb_close = Garlick_vf_close;
	Garlick_cb_read = Garlick_vf_read;
	Garlick_cb_tell = Garlick_vf_tell;
	Garlick_cb_seek = Garlick_vf_seek;
	Garlick_cb_error = Garlick_error;
}

#ifdef ALLOW_SCRIPT_COMPILATION
bool CompileMaps(const char *ext, MapScriptCompiler *compiler, char *directory = NULL)
{
	if (!directory)
		directory = ".";

	std::string pattern = std::string(directory);
	pattern.append("/*");

	std::vector<std::string> filenames;
	listFilePattern(filenames, pattern.c_str());
	for(std::vector<std::string>::iterator i = filenames.begin();
		i != filenames.end();
		i++)
	{
		if (ExtensionIs(i->c_str(),"map"))
		{
			std::string fullpath(directory);
			fullpath.append("/");
			fullpath.append(*i);

			char *s = stripext(fullpath.c_str());
			if (Exist(va("%s.%s", s,ext))) 
				if(!compiler->CompileMap(s))
					return false;
		}
		else if (i->at(0) != '.')
		{
			// for now, if it's not a .map then try to use it as a directory
			std::string newpath(directory);
			newpath.append("/");
			newpath.append(*i);
			CompileMaps(ext,compiler,(char *)newpath.c_str());
		}
	}


	//log ("");
	return true;
}
#endif


//---
void xmain(int argc, char *argv[])
{
	vc_initBuiltins();
	vc_initLibrary();

	InitGarlick();
	Handle::init();

	strcpy(mapname,"");

	LoadConfig();
	if (argc == 2)
	{
		if (strlen(argv[1]) > 254)
			err("Mapname argument too long!");
		strcpy(mapname, argv[1]);
	}

	InitVideo();

	mouse_Init();
	InitKeyboard();
	joy_Init();
	InitScriptEngine();

	gameWindow->setTitle(APPNAME);

	if (sound) snd_Init(soundengine);

	win_movie_init();
	ResetSprites();
	timer_Init(gamerate);

	LUA *lua;
	se = lua = new LUA();
	
	#ifdef ALLOW_SCRIPT_COMPILATION
	DisplayCompileImage();
	lua->compileSystem();
	CompileMaps("lua", lua);
	#endif
	
	se->ExecAutoexec();

	while (true && strlen(mapname))
		Engine_Start(mapname);
	err("");
}
