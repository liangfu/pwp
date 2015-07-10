cmake_minimum_required(VERSION 2.8.7)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()

if(POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW) # CMake 3.0
endif()

project(compvis)

# this is EXTREMELY important to put these setting before add_library/executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(extern/cxcore)
add_subdirectory(extern/cv)
add_subdirectory(extern/highgui)
add_subdirectory(extern/cvutil)

# find_package(OpenCV REQUIRED opencv_core opencv_highgui)

# Set your files and resources here
set( Srcs 
	# res/appicon.rc
	# src/bneditablelabel.cpp
	# src/bnmainwindow.cpp
	# src/bnmainwindow_dti.cpp
	# src/bnmainwindow_gui.cpp
	# src/bnmainwindow_odf.cpp
	# src/bnoverlaymgr.cpp
	# src/bnsliceimageview.cpp
	# src/bnpropertywidget.cpp 
	# src/bnvtkcanvasmgr.cpp 
	# src/bnutility.cpp 
	# src/bndlgcreateroi_impl.cpp
	# src/bndlgfiberpruning_impl.cpp
	# src/bndlgregistration_impl.cpp
	src/main.cpp
	src/mainwindow.cpp
	# src/mediaplayer.cpp
	src/videoplayer.cpp
	src/videowidget.cpp
	src/objectdialog.cpp
	# src/videowidgetsurface.cpp
)

set( Hdrs 
	# include/bneditablelabel.h
	# include/bnmainwindow.h
	# include/bndlgregistration_impl.h
	# include/bndlgcreateroi_impl.h
	# include/bndlgfiberpruning_impl.h
	# include/bnoverlaymgr.h
	# include/bnsliceimageview.h
	# include/_vatool.h
	# include/bnutility.h
	# include/bnpropertywidget.h 
	# include/bnvtkcanvasmgr.h
	# include/mediaplayer.h
	include/mainwindow.h
	include/videoplayer.h
	include/videowidget.h
	include/objectdialog.h
	# include/videowidgetsurface.h
)

set( UIs 
	src/mainwindow.ui
	# src/settings.ui
	# src/bndlgregistration.ui 
	# src/bndlgcreateroi.ui 
	# src/bndlgfiberpruning.ui
)
set( QRC_Files res/mediaplayer.qrc)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
	include
	src
	extern/cxcore/include
	extern/cv/include
	extern/highgui/include
)

# Instruct CMake to run moc automatically when needed.
# set(CMAKE_AUTOMOC ON)

if(VTK_QT_VERSION VERSION_GREATER "4")
  find_package(Qt5Widgets REQUIRED QUIET)

  set(QT_QMAKE_EXECUTABLE ${VTK_QT_QMAKE_EXECUTABLE} CACHE FILEPATH "")
  set(QT_MOC_EXECUTABLE ${VTK_QT_MOC_EXECUTABLE} CACHE FILEPATH "")
  set(QT_UIC_EXECUTABLE ${VTK_QT_UIC_EXECUTABLE} CACHE FILEPATH "")
  
  qt5_wrap_ui(UI_Srcs ${UIs})
  qt5_wrap_cpp(Hdrs_MOC ${Hdrs})
  qt5_add_resources(RCC_Files ${QRC_Files})
  
  # CMAKE_AUTOMOC in ON so the MocHdrs will be automatically wrapped.
  # add_executable(QtVTKRenderWindows ${Srcs} ${Hdrs} ${UI_Srcs} ${MOC_Hdrs})
  # qt5_use_modules(QtVTKRenderWindows Core Gui Widgets)
  # target_link_libraries(QtVTKRenderWindows vtkDICOM vis utils ${VTK_LIBRARIES})
	
  add_executable(compvis ${Srcs} ${Hdrs_MOC} ${UI_Srcs} ${RCC_Files})
  qt5_use_modules(compvis Core Gui Widgets)
  target_link_libraries(compvis 
		cxcore
		# ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} phonon Qt4::QtCore
		${QT_LIBRARIES} 
		)
else()
  find_package(Qt4 4.8.6 REQUIRED QtCore QtGui QtMultimedia)
	if (MSVC)
	  set(QT_ROOT_DIR "D:/Qt/4.8.6")
	else(MSVC)
		set(QT_ROOT_DIR "/usr/local/Trolltech/Qt-4.8.6")
	endif (MSVC)
  include(${QT_USE_FILE})
  # Use what VTK built with
  # set(QT_QMAKE_EXECUTABLE ${VTK_QT_QMAKE_EXECUTABLE} CACHE FILEPATH "")
  # set(QT_MOC_EXECUTABLE ${VTK_QT_MOC_EXECUTABLE} CACHE FILEPATH "")
  # set(QT_UIC_EXECUTABLE ${VTK_QT_UIC_EXECUTABLE} CACHE FILEPATH "")
  qt4_wrap_cpp(Hdrs_MOC ${Hdrs})
  qt4_wrap_ui(UI_Srcs ${UIs})
  qt4_add_resources(RCC_Files ${QRC_Files})

  add_executable(compvis ${Srcs} ${Hdrs_MOC} ${UI_Srcs} ${RCC_Files})
	# qt4_use_modules(compvis Core Gui Network)
  target_link_libraries(compvis 
		# opencv_core opencv_highgui opencv_imgproc
		cxcore cv highgui 
		# ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} phonon -L/usr/local/Trolltech/Qt-4.8.6/lib
		${QT_LIBRARIES} 
		)
endif()

