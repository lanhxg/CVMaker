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
    
    public VideoMaker(String file) {
        
    }
    
    public void addImage(String file) {
        nativeAddImage(file);
    }
    
    public void saveFrames(){
        nativeSave();
    }
    
    public void release() {
        nativeRelease();
    }
    
    private native void nativeInit(String file, int fps, int w, int h, boolean bcolor);
    private native void nativeAddImage(String img);
    private native void nativeSave();
    private native void nativeRelease();
    
    private long mNativeHandle;
}