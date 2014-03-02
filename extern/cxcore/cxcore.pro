######################################################################
# Automatically generated by qmake (2.01a) Thu Feb 13 11:02:06 2014
######################################################################

! include ( ../common.pri ){
 error( "Couldn't find the common.pri file!" )
}
INCLUDEPATH += . src include
DEFINES += CVAPI_EXPORTS

# Input
HEADERS += include/cvver.h \
           include/cvwimage.h \
           include/cxcore.h \
           include/cxcore.hpp \
           include/cxerror.h \
           include/cxmisc.h \
           include/cxtypes.h \
           src/_cxcore.h \
           src/_cxipp.h
SOURCES += src/cxalloc.cpp \
           src/cxarithm.cpp \
           src/cxarray.cpp \
           src/cxcmp.cpp \
           src/cxconvert.cpp \
           src/cxcopy.cpp \
           src/cxdatastructs.cpp \
           src/cxdrawing.cpp \
           src/cxdxt.cpp \
           src/cxerror.cpp \
           src/cximage.cpp \
           src/cxjacobieigens.cpp \
           src/cxlogic.cpp \
           src/cxlut.cpp \
           src/cxmathfuncs.cpp \
           src/cxmatmul.cpp \
           src/cxmatrix.cpp \
           src/cxmean.cpp \
           src/cxmeansdv.cpp \
           src/cxminmaxloc.cpp \
           src/cxnorm.cpp \
           src/cxouttext.cpp \
           src/cxpersistence.cpp \
           src/cxprecomp.cpp \
           src/cxrand.cpp \
           src/cxsumpixels.cpp \
           src/cxsvd.cpp \
           src/cxswitcher.cpp \
           src/cxtables.cpp \
           src/cxutils.cpp