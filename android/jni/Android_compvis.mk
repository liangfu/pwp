LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := cxcore
LOCAL_SRC_FILES := ../obj/local/armeabi/libcxcore.a
include $(PREBUILT_STATIC_LIBRARY)
include $(CLEAR_VARS)
LOCAL_MODULE    := cv
LOCAL_SRC_FILES := ../obj/local/armeabi/libcv.a
include $(PREBUILT_STATIC_LIBRARY)

# include $(CLEAR_VARS)
# LOCAL_MODULE    := highgui
# LOCAL_C_INCLUDES := \
#         $(LOCAL_PATH)/../../thirdparty/cv/src \
#         $(LOCAL_PATH)/../../thirdparty/cv/include \
#         $(LOCAL_PATH)/cxcore/include \
#         $(LOCAL_PATH)/highgui
# LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)
# LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -ldl -llog \
# 				-L$(TARGET_OUT) -lcxcore
# LOCAL_SRC_FILES := \
#         highgui/bitstrm.cpp \
#         highgui/grfmt_base.cpp \
#         highgui/grfmt_bmp.cpp \
#         highgui/grfmt_exr.cpp \
#         highgui/grfmt_imageio.cpp \
#         highgui/grfmt_jpeg.cpp \
#         highgui/grfmt_jpeg2000.cpp \
#         highgui/grfmt_png.cpp \
#         highgui/grfmt_pxm.cpp \
#         highgui/grfmt_sunras.cpp \
#         highgui/grfmt_tiff.cpp \
#         highgui/image.cpp \
#         highgui/loadsave.cpp \
#         highgui/precomp.cpp \
#         highgui/utils.cpp \
#         highgui/cvcap.cpp \
#         highgui/cvcap_socket.cpp
# include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := cvext
LOCAL_C_INCLUDES := \
		$(LOCAL_PATH)/../../include \
        $(LOCAL_PATH)/../../extern/cxcore/include \
        $(LOCAL_PATH)/../../extern/cv/include 
#         $(LOCAL_PATH)/highgui \
LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -ldl -llog \
				-L$(TARGET_OUT) -lcxcore -lcv #-lhighgui 

LOCAL_SRC_FILES := cvjnimain.cpp \
				   cvfacedetector.cpp 

# .				../src/cvext_common.cpp \
# 				../src/cvext_io.cpp \
# 				../src/cvshapedesc.cpp \
# 				../src/cvshapeprior.cpp \
# 				../src/cvimgwarp.cpp \
# 				../src/cvlevelset.cpp \
# 				../src/cvinvcomp.cpp \
# 				../src/cvlda.cpp \
# 				../src/cvpwptracker.cpp \

# LOCAL_STATIC_LIBRARIES := cxcore # cv highgui
# LOCAL_SHARED_LIBRARIES := cxcore cv # highgui

include $(BUILD_SHARED_LIBRARY)


# $(call import-module,cpufeatures)

# $(call import-module,cxcore)
# $(call import-module,cvext)
