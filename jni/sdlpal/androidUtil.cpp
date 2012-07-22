#include <jni.h>
#include "SDL.h"

int g_width = 0, g_height = 0;
extern unsigned short  g_wInitialWidth;
extern unsigned short  g_wInitialHeight;

// Resize
extern "C" void Java_org_libsdl_app_SDLActivity_nativeSetSize(
                                    JNIEnv* env, jclass jcls,
                                    jint width, jint height)
{
    LOGI("preSetWindowSiz: %d  %d", width, height);
    g_wInitialWidth = width;
    g_wInitialHeight = height;
}

// 传0 sdl会自动全屏
extern "C" void getScreenSize(int* width, int *height)
{
    if (width) {
        *width = g_width;
    }

    if (height) {
        *height = g_height;
    }
}

extern "C" void closeAds()
{
}

extern "C" void initButton()
{
}

extern "C" void hideMenu()
{
}

extern "C" void showMenu()
{
}
