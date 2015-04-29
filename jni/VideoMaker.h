#ifndef VIDEO_MAKER_H__
#define VIDEO_MAKER_H__

#include "internal/common.h"
#include <vector>
#include <string>
#include <jni.h>

using std::string;
using std::vector;

class VideoBuilder {
public:
    virtual void init(const string& file, int fps, int fw, int fh, bool bcolor) = 0;
    virtual void save(const string& img) = 0;
    virtual void release() = 0;
    virtual ~VideoBuilder() {}
};

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
class VideoMaker{
    typedef vector<string> FileList;
    FileList m_fileList;
    VideoBuilder* m_builder;

    string m_video;
    int m_fps;
    int m_frameWith;
    int m_frameHeight;
    bool m_bColor;

    static jmethodID g_init;
    static jmethodID g_addImg;
    static jmethodID g_save;
    static jmethodID g_release;

    static jfieldID g_nativeHandleField;

public:
    VideoMaker(VideoBuilder* builder): m_builder(builder) {}

    void attachObject(JNIEnv *env, jobject obj) {
        env->SetLongField(obj, g_nativeHandleField, (jlong)this);
    }

    void create() {
        if (!m_builder) {
            LOGE("get empty video builder");
            return ;
        }

        m_builder->init(m_video, m_fps, m_frameWith, m_frameHeight, m_bColor);

        for (FileList::iterator it = m_fileList.begin(); it != m_fileList.end(); ++it) {
            m_builder->save(*it);
        }
    }

    void init(const string& video, int fps, int w, int h, bool color) {
        m_video = video;
        m_fps = fps;
        m_frameWith = w;
        m_frameHeight = h;
        m_bColor = color;
    }

    void release() {
        if (m_builder) {
            m_builder->release();
            m_builder = NULL;
        }
    }

    void addImg(const string& img) {
        m_fileList.push_back(img);
    }

    ~VideoMaker() { release(); }


    friend void RegisterVideoMakerClass(JNIEnv *env);
private:
    static void Init(JNIEnv *);

    static void nativeInit(JNIEnv *, jobject, jstring, jint, jint, jint, jboolean);
    static void nativeAddImg(JNIEnv *, jobject, jstring);
    static void nativeRelease(JNIEnv *, jobject);
    static void registerVideoMaker(JNIEnv *);
    static VideoMaker* fromObject(JNIEnv *env, jobject obj) {
        return reinterpret_cast<VideoMaker*>(env->GetLongField(obj, g_nativeHandleField));
    }

    static JNINativeMethod _native_methods[];
};
#endif

