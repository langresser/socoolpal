#include <jni.h>
#include "SDL.h"
#include "video.h"
#include "input.h"
#include "hack.h"
#include "util.h"

extern unsigned short  g_wInitialWidth;
extern unsigned short  g_wInitialHeight;

static jmethodID g_methodCloseAds;
static jmethodID g_methodShowJoystick;
static jmethodID g_methodHideJoystick;
static jmethodID g_methodShowBack;
static jmethodID g_methodHideBack;
static jmethodID g_methodShowSearch;
static jmethodID g_methodHideSearch;
static JNIEnv* g_env;
static jclass g_class;

static bool g_isJoystickShow = false;
static bool g_isSearchShow = false;
static bool g_isBackShow = false;
static bool g_useJoyStick = true;


static bool g_hasInMainGame = false;

// Resize
extern "C" void Java_org_libsdl_app_SDLActivity_nativeSetSize(
                                    JNIEnv* env, jclass jcls,
                                    jint width, jint height)
{
    if (width != 0 && height != 0) {
        g_wInitialWidth = (width >= height ? width : height);
        g_wInitialHeight = (width >= height ? height : width);
    }
}

extern "C" void Java_org_libsdl_app_SDLActivity_nativeDirChange(
                                    JNIEnv* env, jclass jcls,
                                    jint dir)
{
    switch (dir) {
        case 1:
            g_InputState.dir = kDirNorth;
            break;
        case 2:
            g_InputState.dir = kDirSouth;
            break;
        case 3:
            g_InputState.dir = kDirWest;
            break;
        case 4:
            g_InputState.dir = kDirEast;
            break;
        default:
            g_InputState.dir = kDirUnknown;
            break;
    }
}

extern "C" void Java_org_libsdl_app_SDLActivity_nativeSearch(
                                    JNIEnv* env, jclass jcls)
{
    g_InputState.dwKeyPress |= kKeySearch;
}


extern "C" void Java_org_libsdl_app_SDLActivity_nativeBack(
                                    JNIEnv* env, jclass jcls)
{
    g_InputState.dwKeyPress |= kKeyMenu;
}

extern "C" void Java_org_libsdl_app_SDLActivity_nativeHack(JNIEnv* env, jclass jcls, jint type, jint value)
{
    switch (type) {
        case 0:
        setFlyMode(value != 0);
        break;
        case 1:
        uplevel();
        break;
        case 2:
        addMoney();
        break;
    }
}

extern "C" int Java_org_libsdl_app_SDLActivity_nativeGetFlyMode(JNIEnv* env, jclass jcls)
{
    return isFlyMode();
}

extern "C" void Java_org_libsdl_app_SDLActivity_nativeChangeBattleMode(
                                    JNIEnv* env, jclass jcls, jint mode)
{
    extern BOOL g_isClassicMode;
    g_isClassicMode = mode != 0 ? true : false;
}


extern "C" void Java_org_libsdl_app_SDLActivity_nativeChangeJoystick(
                                    JNIEnv* env, jclass jcls, jint mode)
{
    g_useJoyStick = mode != 0 ? true : false;

    if (!g_hasInMainGame)
    {
        return;
    }

    if (!g_useJoyStick && g_isJoystickShow)
    {
        hideJoystick();
    }

    if (g_useJoyStick && !g_isJoystickShow)
    {
        showJoystick();
    }
}



// 传0 sdl会自动全屏
extern "C" void getScreenSize(int* width, int *height)
{
    if (width) {
        *width = 0;
    }

    if (height) {
        *height = 0;
    }
}

extern "C" void initJNI(JNIEnv* env, jclass cls)
{
    if (!env) {
        return;
    }

    g_env = env;
    g_class = cls;
    g_methodCloseAds = env->GetStaticMethodID(cls,
                                "closeAds","()V");
    g_methodShowJoystick = env->GetStaticMethodID(cls, "showJoystick", "()V");
    g_methodShowBack = env->GetStaticMethodID(cls, "showBackButton", "()V");
    g_methodShowSearch = env->GetStaticMethodID(cls, "showSearchButton", "()V");

    g_methodHideJoystick = env->GetStaticMethodID(cls, "hideJoystick", "()V");
    g_methodHideBack = env->GetStaticMethodID(cls, "hideBackButton", "()V");
    g_methodHideSearch = env->GetStaticMethodID(cls, "hideSearchButton", "()V");
}

extern "C" void closeAds()
{
    if (!g_env || !g_methodCloseAds || !g_class) {
        return;
    }

    g_env->CallStaticVoidMethod(g_class, g_methodCloseAds);

//    VIDEO_Resize(g_wInitialWidth, g_wInitialHeight);
}

extern "C" void initButton()
{
    if (!g_env || !g_methodCloseAds || !g_class) {
        return;
    }
}

extern "C" void hideMenu()
{
    hideJoystick();
    hideSearchButton();
}

extern "C" void showMenu()
{
    if (!g_env || !g_methodCloseAds || !g_class) {
        return;
    }

// 显示菜单按钮，android下面只需要显示调查按钮
    if (g_isSearchShow == false) {
        g_env->CallStaticVoidMethod(g_class, g_methodShowSearch);
        g_isSearchShow = true;
    }
}

extern "C" void showJoystick()
{
    if (!g_env || !g_methodCloseAds || !g_class) {
        return;
    }

    g_hasInMainGame = true;

    if (!g_useJoyStick)
    {
        return;
    }

    if (g_isJoystickShow == false)
    {
        g_env->CallStaticVoidMethod(g_class, g_methodShowJoystick);
        g_isJoystickShow = true;
    }
}

extern "C" void hideJoystick()
{
    if (!g_env || !g_methodCloseAds || !g_class) {
        return;
    }

    if (g_isJoystickShow == true)
    {
        g_env->CallStaticVoidMethod(g_class, g_methodHideJoystick);
        g_isJoystickShow = false;
    }
}

extern "C" void initDir()
{
}

extern "C" void showBackButton()
{
    if (!g_env || !g_methodCloseAds || !g_class) {
        return;
    }

    if (g_isBackShow == false)
    {
        g_env->CallStaticVoidMethod(g_class, g_methodShowBack);
        g_isBackShow = true;
    }
};
extern "C" void hideBackButton()
{
    if (!g_env || !g_methodCloseAds || !g_class) {
        return;
    }

    if (g_isBackShow == true)
    {
        g_env->CallStaticVoidMethod(g_class, g_methodHideBack);
        g_isBackShow = false;
    }
    
};
extern "C" void hideSearchButton()
{
    if (!g_env || !g_methodCloseAds || !g_class) {
        return;
    }

    if (g_isSearchShow == true)
    {
        g_env->CallStaticVoidMethod(g_class, g_methodHideSearch);
        g_isSearchShow = false;
    }
};


extern "C" void switchShowMenu()
{
    extern BOOL g_showSystemMenu;
    if (g_showSystemMenu) {
        g_InputState.dwKeyPress |= kKeyMenu;
    } else {
        g_InputState.dwKeyPress |= kKeyMainMenu;
    }
}