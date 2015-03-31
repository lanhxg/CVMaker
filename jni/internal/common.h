#ifndef _INTERNAL_COMMON_H__
#define _INTERNAL_COMMON_H__
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>

#include <android/log.h>

JNIEnv* AttachCurrentThread();

#define LOG_TAG  "VedioMaker-JNI"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGV(...) do{ if (g_show_debug) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG,__VA_ARGS__); }while(0)
#define LOGD(...) do{ if (g_show_debug) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__); } while(0)


#endif
