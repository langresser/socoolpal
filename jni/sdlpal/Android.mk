LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := sdlpal

APP_SUBDIRS := $(LOCAL_PATH)/adplug \
				$(LOCAL_PATH)/libmad
LOCAL_CFLAGS += -Isdl/include \
				-DPAL_CLASSIC \
				-ggdb
# Add more subdirs here, like src/subdir1 src/subdir2

#Change C++ file extension as appropriate
LOCAL_CPP_EXTENSION := .cpp

LOCAL_SRC_FILES += adplug/binfile.cpp \
					adplug/binio.cpp \
					adplug/dosbox_opl.cpp \
					adplug/emuopl.cpp \
					adplug/fmopl.c \
					adplug/player.cpp \
					adplug/fprovide.cpp \
					adplug/rix.cpp \
					adplug/surroundopl.cpp
LOCAL_SRC_FILES += battle.c \
				   ending.c fight.c font.c game.c getopt.c \
				   global.c input.c itemmenu.c magicmenu.c \
					main.c map.c palcommon.c palette.c \
					play.c private.c res.c rixplay.cpp rngplay.c \
					scene.c script.c sound.c text.c ui.c uibattle.c \
					uigame.c util.c video.c yj1.c androidUtil.cpp hack.c

LOCAL_SRC_FILES += libmad/bit.c \
					libmad/decoder.c \
					libmad/fixed.c \
					libmad/frame.c \
					libmad/huffman.c \
					libmad/layer3.c \
					libmad/layer12.c \
					libmad/music_mad.c \
					libmad/stream.c \
					libmad/synth.c \
					libmad/timer.c

LOCAL_SRC_FILES += ../sdl/src/main/android/SDL_android_main.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL_ttf

LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog -lz -lGLESv2

include $(BUILD_SHARED_LIBRARY)
