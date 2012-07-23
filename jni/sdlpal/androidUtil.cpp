#include <jni.h>
#include "SDL.h"
#include "video.h"

extern unsigned short  g_wInitialWidth;
extern unsigned short  g_wInitialHeight;

static jmethodID g_methodCloseAds;
static JNIEnv* g_env;
static jclass g_class;

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
}

extern "C" void closeAds()
{
    if (!g_env || !g_methodCloseAds) {
        return;
    }

    g_env->CallStaticVoidMethod(g_class, g_methodCloseAds);

//    VIDEO_Resize(g_wInitialWidth, g_wInitialHeight);
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
