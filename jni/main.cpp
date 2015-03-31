#include "internal/common.h"
static JavaVM *g_jvm;

/////////////////////////////////////////////////////
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    g_jvm = vm;
}

/////////////////////////////////////////////////////


JNIEnv * AttachCurrentThread() {
    JNIEnv *env = NULL;
    jint ret = g_jvm->AttachCurrentThread(&env, NULL);
    return env;
}
