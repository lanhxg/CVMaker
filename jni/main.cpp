#include "internal/common.h"
#include <jni.h>

extern void RegisterVideoMakerClass(JNIEnv * env);
static JavaVM *g_jvm;

/////////////////////////////////////////////////////
void InitMaker(JNIEnv * env) {
    RegisterVideoMakerClass(env);
}

/////////////////////////////////////////////////////
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    g_jvm = vm;
    jint result = -1;

    JNIEnv * env = NULL;
    
    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        LOGE("GetEnv failed");
        goto fail;
    }

    InitMaker(env);
    result = JNI_VERSION_1_6;
    LOGV("Load success");

fail:
    return result;
}

/////////////////////////////////////////////////////


JNIEnv * AttachCurrentThread() {
    JNIEnv *env = NULL;
    jint ret = g_jvm->AttachCurrentThread(&env, NULL);
    return env;
}
