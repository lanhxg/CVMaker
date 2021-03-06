LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

OPENCV_INSTALL_MODULES:=on
OPENCV_CAMERA_MODULES:=off
OPENCV_LIB_TYPE:=SHARE

include $(OPENCV_PACKAGE_DIR)/sdk/native/jni/OpenCV.mk

LOCAL_CFLAGS += -I. \
				-D_STLP_USE_NEWALLOC

LOCAL_LDLIBS += -llog 

EXTERN_LIB_PATH=$(LOCAL_PATH)/lib


#LOCAL_LDFLAGS += -L$(EXTERN_LIB_PATH) \
				  $(EXTERN_LIB_PATH)/libgnustl_static.a

LOCAL_MODULE := vmaker
LOCAL_SRC_FILES :=main.cpp \
	              VideoMaker.cpp \
				  cvVideoBuilder.cpp

LOCAL_ALLOW_UNDEFINED_SYMBOLS := true
LOCAL_WHOLE_STATIC_LIBRARIES += android_support
include $(BUILD_SHARED_LIBRARY)
