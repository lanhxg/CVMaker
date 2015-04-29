/**
 * 
 */
/**
 * @author lanhxg
 *
 */

package com.video.maker;


public class VideoMaker{
    static {
        System.loadLibrary("vmaker");
    }
    
    private static final String LOG_TAG = "VideoMaker";
    
    public VideoMaker(String file, int fps, int w, int h, boolean color) {
        nativeInit(file, fps, w, h, color);
    }
    
    public void addImage(String file) {
        nativeAddImg(file);
    }
    
    public void saveFrames(){
        nativeSave();
    }
    
    public void release() {
        nativeRelease();
    }
    
    private native void nativeInit(String file, int fps, int w, int h, boolean bcolor);
    private native void nativeAddImg(String img);
    private native void nativeSave();
    private native void nativeRelease();
    
    private long mNativeHandle;
}