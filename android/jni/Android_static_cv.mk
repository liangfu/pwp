LOCAL_PATH:= $(call my-dir)


include $(CLEAR_VARS)
LOCAL_MODULE    := cv
LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/../../extern/cxcore/include \
        $(LOCAL_PATH)/../../extern/cv/src \
        $(LOCAL_PATH)/../../extern/cv/include 
LOCAL_EXPORT_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)
LOCAL_EXPORT_LDLIBS := -L$(SYSROOT)/usr/lib -ldl -L$(TARGET_OUT) -lcxcore
# LOCAL_SHARED_LIBRARIES := cxcore 
LOCAL_STATIC_LIBRARIES := cxcore 
LOCAL_SRC_FILES := \
        ../../extern/cv/src/cvaccum.cpp \
        ../../extern/cv/src/cvapprox.cpp \
        ../../extern/cv/src/cvcanny.cpp \
        ../../extern/cv/src/cvcolor.cpp \
        ../../extern/cv/src/cvcontours.cpp \
        ../../extern/cv/src/cvfilter.cpp \
        ../../extern/cv/src/cvderiv.cpp \
        ../../extern/cv/src/cvdistransform.cpp \
        ../../extern/cv/src/cvgeometry.cpp \
        ../../extern/cv/src/cvhistogram.cpp \
        ../../extern/cv/src/cvposit.cpp \
        ../../extern/cv/src/cvprecomp.cpp \
        ../../extern/cv/src/cvshapedescr.cpp \
        ../../extern/cv/src/cvsmooth.cpp \
        ../../extern/cv/src/cvsumpixels.cpp \
        ../../extern/cv/src/cvtables.cpp \
        ../../extern/cv/src/cvtemplmatch.cpp \
        ../../extern/cv/src/cvthresh.cpp \
        ../../extern/cv/src/cvmatchcontours.cpp \
        ../../extern/cv/src/cvmoments.cpp \
        ../../extern/cv/src/cvimgwarp.cpp \
        ../../extern/cv/src/cvutils.cpp \
        ../../extern/cv/src/cvhaar.cpp 
include $(BUILD_STATIC_LIBRARY)
# include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := cvext
LOCAL_C_INCLUDES := \
		$(LOCAL_PATH)/../../include \
        $(LOCAL_PATH)/../../extern/cxcore/include \
        $(LOCAL_PATH)/../../extern/cv/include 

LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -ldl -llog \
				-L$(TARGET_OUT) -lcxcore -lcv #-lhighgui 

LOCAL_SRC_FILES := cvjnitest.cpp 
# 				   cvfacedetector.cpp 

# .				../src/cvext_common.cpp \
# 				../src/cvext_io.cpp \
# 				../src/cvshapedesc.cpp \
# 				../src/cvshapeprior.cpp \
# 				../src/cvimgwarp.cpp \
# 				../src/cvlevelset.cpp \
# 				../src/cvinvcomp.cpp \
# 				../src/cvlda.cpp \
# 				../src/cvpwptracker.cpp \

LOCAL_STATIC_LIBRARIES := cxcore cv # highgui
# LOCAL_SHARED_LIBRARIES := cxcore cv # highgui

include $(BUILD_SHARED_LIBRARY)


# $(call import-module,cpufeatures)

# $(call import-module,cxcore)
# $(call import-module,cvext)


