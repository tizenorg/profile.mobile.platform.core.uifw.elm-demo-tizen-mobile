CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(ui-controls C)
SET(PACKAGE org.tizen.ui-controls)

SET(SRCS
	src/main.c
	src/accessibility.c
	src/accessibility/screen_reader.c
	src/accessibility/screen_reader/description.c
	src/accessibility/screen_reader/reading_order.c
	src/accessibility/screen_reader/primitives_ui.c
	src/accessibility/screen_reader/custom_frame.c
	src/bg.c
	src/button.c
	src/calendar.c
	src/check.c
	src/colorselector.c
	src/ctxpopup.c
	src/datetime.c
	src/entry.c
	src/fastscroll.c
	src/flipselector.c
	src/gengrid.c
	src/genlist.c
	src/handler.c
	src/hoversel.c
	src/indicator.c
	src/label.c
	src/label_colorstyles.c
	src/label_ellipsis.c
	src/label_linebreakmodes.c
	src/label_slide.c
	src/label_fontsizes.c
	src/multibuttonentry.c
	src/naviframe.c
	src/nocontents.c
	src/pagecontrol.c
	src/pagecontrol_horizontal.c
	src/pagecontrol_horizontal_loop.c
	src/popup.c
	src/progressbar.c
	src/radio.c
	src/slider.c
	src/spinner.c
	src/toolbar.c
	src/toolbar_navigationbar.c
	src/toolbar_tab.c
	src/vector.c
	)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/inc)

FIND_LIBRARY(LIB_M m)
#FIXME: pthread is added for preventing build error
SET(PKG_LDFLAGS "-pthread ${LIB_M} -pie")
SET(PKG_CFLAGS "-g -Wall -fPIE")

INCLUDE(FindPkgConfig)
pkg_check_modules(BASE_PKG REQUIRED elementary efl-extension)
FOREACH(flag ${BASE_PKG_CFLAGS})
	SET(PKG_CFLAGS "${PKG_CFLAGS} ${flag}")
ENDFOREACH(flag)
FOREACH(flag ${BASE_PKG_LDFLAGS})
	SET(PKG_LDFLAGS "${PKG_LDFLAGS} ${flag}")
ENDFOREACH(flag)

pkg_check_modules(TIZEN_PKG REQUIRED capi-appfw-application capi-system-system-settings appcore-efl)
FOREACH(flag ${TIZEN_PKG_CFLAGS})
	SET(PKG_CFLAGS "${PKG_CFLAGS} ${flag}")
ENDFOREACH(flag)
FOREACH(flag ${TIZEN_PKG_LDFLAGS})
	SET(PKG_LDFLAGS "${PKG_LDFLAGS} ${flag}")
ENDFOREACH(flag)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${PKG_CFLAGS}")

# install desktop file & icon
SET(PREFIX ${CMAKE_INSTALL_PREFIX})
SET(BINDIR "${PREFIX}/bin")
SET(RESDIR "${PREFIX}/res")
SET(DATADIR "${PREFIX}/data")
SET(LOCALEDIR "${RESDIR}/locale")
SET(IMGDIR "${RESDIR}/images")

ADD_DEFINITIONS("-DPACKAGE=\"${PACKAGE}\"")
ADD_DEFINITIONS("-DPREFIX=\"${CMAKE_INSTALL_PREFIX}\"")
ADD_DEFINITIONS("-DRESDIR=\"${RESDIR}\"")
ADD_DEFINITIONS("-DDATADIR=\"${DATADIR}\"")
ADD_DEFINITIONS("-DLOCALE_DIR=\"${LOCALEDIR}\"")
ADD_DEFINITIONS("-DICON_DIR=\"${IMGDIR}\"")
ADD_DEFINITIONS("-DELM_DEMO_EDJ=\"${RESDIR}/${PROJECT_NAME}.edj\"")

ADD_EXECUTABLE(${PROJECT_NAME} ${SRCS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${PKG_LDFLAGS})

ADD_CUSTOM_TARGET(${PROJECT_NAME}.edj
	COMMAND edje_cc -no-save -id ${CMAKE_CURRENT_SOURCE_DIR}/edje/images
	${CMAKE_SOURCE_DIR}/res/${PROJECT_NAME}.edc ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.edj
	DEPENDS ${CMAKE_SOURCE_DIR}/res/${PROJECT_NAME}.edc
	)
ADD_DEPENDENCIES(${PROJECT_NAME} ${PROJECT_NAME}.edj)

INSTALL(TARGETS ${PROJECT_NAME} DESTINATION ${BINDIR})
# for workaround taskmanager behaviour
INSTALL(FILES ${CMAKE_SOURCE_DIR}/data/${PACKAGE}.png DESTINATION /usr/share/icons/default/small/)
INSTALL(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.edj DESTINATION ${RESDIR})
INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/res/images/ DESTINATION ${IMGDIR} FILES_MATCHING PATTERN "*.png")
INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/res/images/ DESTINATION ${IMGDIR} FILES_MATCHING PATTERN "*.jpg")
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${PACKAGE}.xml DESTINATION /usr/share/packages/)

# i18n
ADD_SUBDIRECTORY(po)
