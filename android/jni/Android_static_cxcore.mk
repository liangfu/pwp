LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := cxcore
LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/../../extern/cxcore/include 
LOCAL_EXPORT_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)
LOCAL_EXPORT_LDLIBS := -L$(SYSROOT)/usr/lib -ldl
LOCAL_SRC_FILES := \
        ../../extern/cxcore/src/cxerror.cpp \
        ../../extern/cxcore/src/cxarray.cpp \
        ../../extern/cxcore/src/cxmatrix.cpp \
        ../../extern/cxcore/src/cxalloc.cpp \
        ../../extern/cxcore/src/cxarithm.cpp \
        ../../extern/cxcore/src/cxcmp.cpp \
        ../../extern/cxcore/src/cxconvert.cpp \
        ../../extern/cxcore/src/cxcopy.cpp \
        ../../extern/cxcore/src/cxdatastructs.cpp \
        ../../extern/cxcore/src/cxdrawing.cpp \
        ../../extern/cxcore/src/cxdxt.cpp \
        ../../extern/cxcore/src/cximage.cpp \
        ../../extern/cxcore/src/cxjacobieigens.cpp \
        ../../extern/cxcore/src/cxlogic.cpp \
        ../../extern/cxcore/src/cxlut.cpp \
        ../../extern/cxcore/src/cxmathfuncs.cpp \
        ../../extern/cxcore/src/cxmatmul.cpp \
        ../../extern/cxcore/src/cxmean.cpp \
        ../../extern/cxcore/src/cxmeansdv.cpp \
        ../../extern/cxcore/src/cxminmaxloc.cpp \
        ../../extern/cxcore/src/cxnorm.cpp \
        ../../extern/cxcore/src/cxouttext.cpp \
        ../../extern/cxcore/src/cxpersistence.cpp \
        ../../extern/cxcore/src/cxprecomp.cpp \
        ../../extern/cxcore/src/cxrand.cpp \
        ../../extern/cxcore/src/cxsumpixels.cpp \
        ../../extern/cxcore/src/cxsvd.cpp \
        ../../extern/cxcore/src/cxswitcher.cpp \
        ../../extern/cxcore/src/cxtables.cpp \
        ../../extern/cxcore/src/cxutils.cpp
# include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := cvext
LOCAL_C_INCLUDES := \
		$(LOCAL_PATH)/../../include \
        $(LOCAL_PATH)/../../extern/cxcore/include \
        $(LOCAL_PATH)/../../extern/cv/include 
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -ldl -llog \
				-L$(TARGET_OUT) -lcxcore # -lcv -lhighgui 

LOCAL_SRC_FILES := cvjnitest.cpp 

LOCAL_STATIC_LIBRARIES := cxcore # cv highgui
# LOCAL_SHARED_LIBRARIES := cxcore cv # highgui

include $(BUILD_SHARED_LIBRARY)



