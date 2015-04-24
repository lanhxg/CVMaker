#ifndef VIDEO_MAKER_H__
#define VIDEO_MAKER_H__

#include "internal/common.h"
#include <vector>
#include <string>

using namespace std::string;
using namespace std::vector;
class VideoMaker {
    
public:
    VideoMaker(): writer(NULL){ }

    void addJPEGGFile(string file) {
        m_fileList.push_back(file);
    }

    void createVideoWriter(string file, int fps, int w, int h, bool isColor) {
        if (m_Writer) {
            cvReleaseVideoWriter(&m_Writer);
        }
    }
    

private:
    static void nativeAddJPEGFile(JNIEnv* env, jobject obj, jstring file) {
    }
    
private:
    typedef vector<string> FileList;
    FileList m_fileList;
    CvVideoWriter* m_writer;
};
#endif
