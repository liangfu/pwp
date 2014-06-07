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

# include $(CLEAR_VARS)
# LOCAL_MODULE    := cv
# LOCAL_C_INCLUDES := \
#         $(LOCAL_PATH)/../../extern/cxcore/include \
#         $(LOCAL_PATH)/../../extern/cv/src \
#         $(LOCAL_PATH)/../../extern/cv/include 
# LOCAL_EXPORT_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)
# LOCAL_EXPORT_LDLIBS := -L$(SYSROOT)/usr/lib -ldl -L$(TARGET_OUT) -lcxcore
# # LOCAL_SHARED_LIBRARIES := cxcore 
# LOCAL_STATIC_LIBRARIES := cxcore 
# LOCAL_SRC_FILES := \
#         ../../extern/cv/src/cvaccum.cpp \
#         ../../extern/cv/src/cvapprox.cpp \
#         ../../extern/cv/src/cvcolor.cpp \
#         ../../extern/cv/src/cvcontours.cpp \
#         ../../extern/cv/src/cvfilter.cpp \
#         ../../extern/cv/src/cvderiv.cpp \
#         ../../extern/cv/src/cvdistransform.cpp \
#         ../../extern/cv/src/cvgeometry.cpp \
#         ../../extern/cv/src/cvhistogram.cpp \
#         ../../extern/cv/src/cvposit.cpp \
#         ../../extern/cv/src/cvprecomp.cpp \
#         ../../extern/cv/src/cvshapedescr.cpp \
#         ../../extern/cv/src/cvsmooth.cpp \
#         ../../extern/cv/src/cvsumpixels.cpp \
#         ../../extern/cv/src/cvtables.cpp \
#         ../../extern/cv/src/cvtemplmatch.cpp \
#         ../../extern/cv/src/cvthresh.cpp \
#         ../../extern/cv/src/cvmatchcontours.cpp \
#         ../../extern/cv/src/cvhaar.cpp 
# # include $(BUILD_STATIC_LIBRARY)
# include $(BUILD_SHARED_LIBRARY)

# include $(CLEAR_VARS)
# LOCAL_MODULE    := cxcore
# LOCAL_SRC_FILES := ../obj/local/armeabi/libcxcore.a
# include $(PREBUILT_STATIC_LIBRARY)
# include $(CLEAR_VARS)
# LOCAL_MODULE    := cv
# LOCAL_SRC_FILES := ../obj/local/armeabi/libcv.a
# include $(PREBUILT_STATIC_LIBRARY)

# include $(CLEAR_VARS)
# LOCAL_MODULE    := highgui
# LOCAL_C_INCLUDES := \
#         $(LOCAL_PATH)/../../extern/cv/src \
#         $(LOCAL_PATH)/../../extern/cv/include \
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

# include $(CLEAR_VARS)

# LOCAL_MODULE    := cvext
# LOCAL_C_INCLUDES := \
# 		$(LOCAL_PATH)/../../include \
#         $(LOCAL_PATH)/../../extern/cxcore/include \
#         $(LOCAL_PATH)/../../extern/cv/include 
# #         $(LOCAL_PATH)/highgui \
# LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)
# LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -ldl -llog \
# 				-L$(TARGET_OUT) -lcxcore -lcv #-lhighgui 

# LOCAL_SRC_FILES := cvjnimain.cpp \
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

# include $(BUILD_SHARED_LIBRARY)


# $(call import-module,cpufeatures)

# $(call import-module,cxcore)
# $(call import-module,cvext)


