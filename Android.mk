# Copyright 2006 The Android Open Source Project

# Setting LOCAL_PATH will mess up all-subdir-makefiles, so do it beforehand.
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm
LOCAL_PRELINK_MODULE := false

LOCAL_LDFLAGS += -L$(LOCAL_PATH) 

# 
LOCAL_PREBUILTS_LIBS := libTICPUBLT.so
include $(BUILD_MULTI_PREBUILT)

# libTICPUBLT_TI need rebuilt
LOCAL_SHARED_LIBRARIES := libTICPUBLT


LOCAL_INCLUDES += $(LOCAL_PATH)/include

LOCAL_SRC_FILES += src/tibltMain.c \
                   src/usecases.c \
                   src/UC001050.c \
                   src/UC002203.c \
                   src/UC002300.c \
                   src/UC002401.c \
                   src/UC003010.c \
                   src/UC003011.c \
                   src/UC003012.c \
                   src/UC003020.c \
                   src/UC003021.c \
                   src/UC003022.c \
                   src/UC004010.c \
                   src/UC002700.c

LOCAL_MODULE:= tibltMain
include $(BUILD_EXECUTABLE)

# dead codes
#LOCAL_C_INCLUDES += $(LOCAL_PATH)/src
#LOCAL_SRC_FILES += main.c
#LOCAL_STATIC_LIBRARIES := libTICPUBLT_TI
#LOCAL_LDLIBS += -Wl,-z,origin
# libTICPUBLT_TI need not be rebuilt
#LOCAL_LDLIBS += -lTICPUBLT_TI 

