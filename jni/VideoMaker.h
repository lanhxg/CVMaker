#ifndef VIDEO_MAKER_H__
#define VIDEO_MAKER_H__

#include "internal/common.h"

#include <cv.h>
#include <highgui.h>

#include <vector>
#include <string>

using std::string;
using std::vector;
class VideoMaker {
    
public:
    VideoMaker(): m_writer(NULL){ }

    void addImageFile(string file) {
        m_fileList.push_back(file);
    }

    void createVideoWriter(string file, int fps, int frameW, int frameH, bool isColor) {
        release();

        m_writer = cvCreateVideoWriter(file.c_str(),
                    CV_FOURCC('X','V','I','D'),
                    fps,
                    cvSize(frameW,frameH),
                    isColor);
    }

    void saveFrames() {
        IplImage* img = NULL;
        for (FileList::iterator it = m_fileList.begin() ; it != m_fileList.end(); ++it) {
            img = cvLoadImage(it->c_str());
            cvWriteFrame(m_writer, img);
        }
    }

    void release() {
        if (m_writer) {
            cvReleaseVideoWriter(&m_writer);
            m_writer = NULL;
        }
    }
    
    ~VideoMaker() { release(); }
private:
    static void nativeAddImgFiles(JNIEnv* env, jobject obj, jstring file) {
    }
private:
    typedef vector<string> FileList;
    FileList m_fileList;
    CvVideoWriter* m_writer;
};
#endif
