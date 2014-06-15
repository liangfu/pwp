LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := cxcore
LOCAL_SRC_FILES := ../obj/local/armeabi/libcxcore.a
include $(PREBUILT_STATIC_LIBRARY)
include $(CLEAR_VARS)
LOCAL_MODULE    := cv
LOCAL_SRC_FILES := ../obj/local/armeabi/libcv.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := cvext
LOCAL_C_INCLUDES := \
				$(LOCAL_PATH)/../../include \
        $(LOCAL_PATH)/../../extern/cxcore/include \
        $(LOCAL_PATH)/../../extern/cv/include 

LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -ldl -llog 
# LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -ldl -llog 
# 								-L$(TARGET_OUT) -lcxcore -lcv #-lhighgui
LOCAL_STATIC_LIBRARIES := cxcore cv

LOCAL_SRC_FILES := cvjnimain.cpp \
				   cvfacedetector.cpp 

# .				../src/cvext_common.cpp 
# 				../src/cvext_io.cpp 
# 				../src/cvshapedesc.cpp 
# 				../src/cvshapeprior.cpp 
# 				../src/cvimgwarp.cpp 
# 				../src/cvlevelset.cpp 
# 				../src/cvinvcomp.cpp 
# 				../src/cvlda.cpp 
# 				../src/cvpwptracker.cpp 

include $(BUILD_SHARED_LIBRARY)

# $(call import-module,cxcore)
# $(call import-module,cvext)
