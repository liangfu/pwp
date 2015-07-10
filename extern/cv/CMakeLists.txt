cmake_minimum_required(VERSION 2.8.7)

project(cv)

INCLUDE_DIRECTORIES(./include ../cxcore/include)

add_library(cv SHARED
	src/rotcalipers.cpp
	src/grabcut.cpp
	src/phasecorr.cpp
	src/floodfill.cpp
	src/imgwarp.cpp
	src/pyramids.cpp
	src/shapedescr.cpp
	src/morph.cpp
	src/templmatch.cpp
	src/cornersubpix.cpp
	src/deriv.cpp
	src/filter.cpp
	src/samplers.cpp
	src/subdivision2d.cpp
	src/moments.cpp
	src/contours.cpp
	src/convhull.cpp
	src/segmentation.cpp
	src/clahe.cpp
	src/distransform.cpp
	src/accum.cpp
	src/linefit.cpp
	src/avx2/imgwarp_avx2.cpp
	src/tables.cpp
	src/sumpixels.cpp
	src/color.cpp
	src/smooth.cpp
	src/histogram.cpp
	src/geometry.cpp
	src/thresh.cpp
	src/emd.cpp
	src/avx/imgwarp_avx.cpp
	src/gabor.cpp
	src/utils.cpp
	src/featureselect.cpp
	src/approx.cpp
	src/generalized_hough.cpp
	src/matchcontours.cpp
	src/corner.cpp
	src/undistort.cpp
	src/hough.cpp
	src/canny.cpp
	)

#---------------------------------------------------------------------
# Find OpenMP
find_package( OpenMP )

if( OPENMP_FOUND )
  set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}" )
  set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}" )
	IF(WIN32)
	ELSE(WIN32)
		TARGET_LINK_LIBRARIES(cv pthread rt cxcore gomp)
	ENDIF(WIN32)
ELSE (OPENMP_FOUND)
	IF(WIN32)
	ELSE(WIN32)
		TARGET_LINK_LIBRARIES(cv pthread rt cxcore)
	ENDIF(WIN32)
ENDIF(OPENMP_FOUND)

