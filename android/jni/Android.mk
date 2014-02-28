LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := cxcore
LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/../../thirdparty/cxcore/include 
LOCAL_EXPORT_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)
LOCAL_EXPORT_LDLIBS := -L$(SYSROOT)/usr/lib -ldl
LOCAL_SRC_FILES := \
        ../../thirdparty/cxcore/src/cxerror.cpp \
        ../../thirdparty/cxcore/src/cxarray.cpp \
        ../../thirdparty/cxcore/src/cxmatrix.cpp \
        ../../thirdparty/cxcore/src/cxalloc.cpp \
        ../../thirdparty/cxcore/src/cxarithm.cpp \
        ../../thirdparty/cxcore/src/cxcmp.cpp \
        ../../thirdparty/cxcore/src/cxconvert.cpp \
        ../../thirdparty/cxcore/src/cxcopy.cpp \
        ../../thirdparty/cxcore/src/cxdatastructs.cpp \
        ../../thirdparty/cxcore/src/cxdrawing.cpp \
        ../../thirdparty/cxcore/src/cxdxt.cpp \
        ../../thirdparty/cxcore/src/cximage.cpp \
        ../../thirdparty/cxcore/src/cxjacobieigens.cpp \
        ../../thirdparty/cxcore/src/cxlogic.cpp \
        ../../thirdparty/cxcore/src/cxlut.cpp \
        ../../thirdparty/cxcore/src/cxmathfuncs.cpp \
        ../../thirdparty/cxcore/src/cxmatmul.cpp \
        ../../thirdparty/cxcore/src/cxmean.cpp \
        ../../thirdparty/cxcore/src/cxmeansdv.cpp \
        ../../thirdparty/cxcore/src/cxminmaxloc.cpp \
        ../../thirdparty/cxcore/src/cxnorm.cpp \
        ../../thirdparty/cxcore/src/cxouttext.cpp \
        ../../thirdparty/cxcore/src/cxpersistence.cpp \
        ../../thirdparty/cxcore/src/cxprecomp.cpp \
        ../../thirdparty/cxcore/src/cxrand.cpp \
        ../../thirdparty/cxcore/src/cxsumpixels.cpp \
        ../../thirdparty/cxcore/src/cxsvd.cpp \
        ../../thirdparty/cxcore/src/cxswitcher.cpp \
        ../../thirdparty/cxcore/src/cxtables.cpp \
        ../../thirdparty/cxcore/src/cxutils.cpp
# include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := cv
LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/../../thirdparty/cxcore/include \
        $(LOCAL_PATH)/../../thirdparty/cv/src \
        $(LOCAL_PATH)/../../thirdparty/cv/include 
LOCAL_EXPORT_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)
LOCAL_EXPORT_LDLIBS := -L$(SYSROOT)/usr/lib -ldl -L$(TARGET_OUT) -lcxcore
# LOCAL_SHARED_LIBRARIES := cxcore 
LOCAL_STATIC_LIBRARIES := cxcore 
LOCAL_SRC_FILES := \
        ../../thirdparty/cv/src/cvaccum.cpp \
        ../../thirdparty/cv/src/cvapprox.cpp \
        ../../thirdparty/cv/src/cvcolor.cpp \
        ../../thirdparty/cv/src/cvcontours.cpp \
        ../../thirdparty/cv/src/cvfilter.cpp \
        ../../thirdparty/cv/src/cvderiv.cpp \
        ../../thirdparty/cv/src/cvdistransform.cpp \
        ../../thirdparty/cv/src/cvgeometry.cpp \
        ../../thirdparty/cv/src/cvhistogram.cpp \
        ../../thirdparty/cv/src/cvposit.cpp \
        ../../thirdparty/cv/src/cvprecomp.cpp \
        ../../thirdparty/cv/src/cvshapedescr.cpp \
        ../../thirdparty/cv/src/cvsmooth.cpp \
        ../../thirdparty/cv/src/cvsumpixels.cpp \
        ../../thirdparty/cv/src/cvtables.cpp \
        ../../thirdparty/cv/src/cvtemplmatch.cpp \
        ../../thirdparty/cv/src/cvthresh.cpp \
        ../../thirdparty/cv/src/cvmatchcontours.cpp \
        ../../thirdparty/cv/src/cvhaar.cpp # \
        # ../../thirdparty/cv/src/cvadapthresh.cpp \
        # ../../thirdparty/cv/src/cvcalccontrasthistogram.cpp \
        # ../../thirdparty/cv/src/cvcalcimagehomography.cpp \
        # ../../thirdparty/cv/src/cvcalibinit.cpp \
        # ../../thirdparty/cv/src/cvcalibration.cpp \
        # ../../thirdparty/cv/src/cvcamshift.cpp \
        # ../../thirdparty/cv/src/cvcanny.cpp \
        # ../../thirdparty/cv/src/cvcondens.cpp \
        # ../../thirdparty/cv/src/cvcontourtree.cpp \
        # ../../thirdparty/cv/src/cvconvhull.cpp \
        # ../../thirdparty/cv/src/cvcorner.cpp \
        # ../../thirdparty/cv/src/cvcornersubpix.cpp \
        # ../../thirdparty/cv/src/cvdominants.cpp \
        # ../../thirdparty/cv/src/cvemd.cpp \
        # ../../thirdparty/cv/src/cvfeatureselect.cpp \
        # ../../thirdparty/cv/src/cvfloodfill.cpp \
        # ../../thirdparty/cv/src/cvfundam.cpp \
        # ../../thirdparty/cv/src/cvhough.cpp \
        # ../../thirdparty/cv/src/cvimgwarp.cpp \
        # ../../thirdparty/cv/src/cvinpaint.cpp \
        # ../../thirdparty/cv/src/cvkalman.cpp \
        # ../../thirdparty/cv/src/cvlinefit.cpp \
        # ../../thirdparty/cv/src/cvlkpyramid.cpp \
        # ../../thirdparty/cv/src/cvmoments.cpp \
        # ../../thirdparty/cv/src/cvmorph.cpp \
        # ../../thirdparty/cv/src/cvmotempl.cpp \
        # ../../thirdparty/cv/src/cvoptflowbm.cpp \
        # ../../thirdparty/cv/src/cvoptflowhs.cpp \
        # ../../thirdparty/cv/src/cvoptflowlk.cpp \
        # ../../thirdparty/cv/src/cvpgh.cpp \
        # ../../thirdparty/cv/src/cvpyramids.cpp \
        # ../../thirdparty/cv/src/cvpyrsegmentation.cpp \
        # ../../thirdparty/cv/src/cvrotcalipers.cpp \
        # ../../thirdparty/cv/src/cvsamplers.cpp \
        # ../../thirdparty/cv/src/cvsegmentation.cpp \
        # ../../thirdparty/cv/src/cvsnakes.cpp \
        # ../../thirdparty/cv/src/cvstereobm.cpp \
        # ../../thirdparty/cv/src/cvstereogc.cpp \
        # ../../thirdparty/cv/src/cvsubdivision2d.cpp \
        # ../../thirdparty/cv/src/cvsurf.cpp \
        # ../../thirdparty/cv/src/cvswitcher.cpp \
        # ../../thirdparty/cv/src/cvundistort.cpp \
        # ../../thirdparty/cv/src/cvutils.cpp 
include $(BUILD_STATIC_LIBRARY)

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
        $(LOCAL_PATH)/../../thirdparty/cxcore/include \
        $(LOCAL_PATH)/../../thirdparty/cv/include 
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
