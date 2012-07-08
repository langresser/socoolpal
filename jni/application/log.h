#pragma once

#include <android/log.h>

#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,"JNI",__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,"JNI",__VA_ARGS__)
