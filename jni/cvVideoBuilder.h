#ifndef CV_VIDEO_BUILDER_H__
#define CV_VIDEO_BUILDER_H__

#include "internal/common.h"

#include <cv.h>
#include <highgui.h>

#include <vector>
#include <string>

using std::string;
using std::vector;

class cvVideoBuilder: public VideoBuilder {
    CvVideoWriter* m_writer;
public:
    cvVideoBuilder(): m_writer(NULL){}

    void init(const string& file, int fps, int fw, int fh, bool bcolor) {
        release();
        m_writer = cvCreateVideoWriter(file.c_str(),
                    CV_FOURCC('X','V','I','D'),
                    fps,
                    cvSize(fw,fh),
                    bolor);
    }

    void save(const string& img) {
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

    ~cvVideoBuilder() {release();}
};
#endif
