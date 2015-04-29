
#include "VideoMaker.h"

/////////////////////////////////////////////////////
jmethodID VideoMaker::g_init;
jmethodID VideoMaker::g_addImg;
jmethodID VideoMaker::g_save;
jmethodID VideoMaker::g_release;

#define VideoMakerClassName "com/video/maker/VideoMaker"

void VideoMaker::Init(JNIEnv *env) {
    static bool isInited = false;
    if (!isInited) {
        isInited = true;

        jclass clzz = env->FindClass(VideoMakerClassName);

        g_init = env->GetMethodID(clzz, "nativeInit", "(Ljava/lang/String;IIIZ)V");
        g_addImg = env->GetMethodID(clzz, "nativeAddImg", "(Ljava/lang/String;)V");
        g_save = env->GetMethodID(clzz, "nativeRelease", "()V");
        g_nativeHandleField = env->GetFieldID(clzz, "mNativeHandle", "J");

        env->DeleteLocalRef(clzz);
    }
}

void VideoMaker::nativeInit(JNIEnv * env, jobject obj, jstring video, jint fps, jint frameWidth, jint frameHeight, jboolean bColor) {
    VideoMaker * tv = fromObject(env, obj);
    if (!tv) { 
        LOGE("fail to get VideoMaker Object");
        return;
    };
    const char * str =  env->GetStringUTFChars(video, NULL);
    string file(str);
    env->ReleaseStringUTFChars(video, str);

    tv->init(file, fps, frameWidth, frameHeight, bColor);
}

void VideoMaker::nativeAddImg(JNIEnv * env, jobject obj, jstring img) {
    VideoMaker * tv = fromObject(env, obj);
    if (!tv) {
        LOGE("fail to get VideoMaker Object");
        return;
    }

    const char * str = env->GetStringUTFChars(img, NULL);
    string file(str);
    tv->addImg(file);
}

void VideoMaker::nativeRelease(JNIEnv *env, jobject obj) {
    VideoMaker * tv = fromObject(env, obj);
    if (!tv) {
        LOGE("fail to get VideoMaker Object");
        return;
    }
    tv->release();
}

/////////////////////////////////////////////////////////////////////
#define NATIVE_METHOD(name, signature) \
{"native"#name, signature, (void*)(VideoMaker::native##name)}
JNINativeMethod VideoMaker::_native_methods[] = {
    NATIVE_METHOD(Init,"(Ljava/lang/String;IIIZ)V"),
    NATIVE_METHOD(AddImg, "(Ljava/lang/String)V"),
    NATIVE_METHOD(Release, "()V"),
};
#undef NATIVE_METHOD

void VideoMaker::registerVideoMaker(JNIEnv * env) {

    jclass clzz = env->FindClass(VideoMakerClassName);
    env->RegisterNatives(clzz, _native_methods, sizeof(_native_methods)/sizeof(_native_methods[0]));

    env->DeleteLocalRef(clzz);
}

void RegisterVideoMakerClass(JNIEnv * env) {
    VideoMaker::registerVideoMaker(env);
}
