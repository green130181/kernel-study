LOCAL_PATH:= $(call my-dir)

pagemap_src_files := \
  gdb-sample.c \

include $(CLEAR_VARS)
LOCAL_SRC_FILES := $(pagemap_src_files)
LOCAL_CFLAGS += -DHAVE_CONFIG_H
LOCAL_CFLAGS += -D_U_="__attribute__((unused))"
#LOCAL_SHARED_LIBRARIES += libssl libcrypto
#LOCAL_STATIC_LIBRARIES += libpcap
LOCAL_MODULE_PATH := $(TARGET_OUT_OPTIONAL_EXECUTABLES)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := gdb-sample
include $(BUILD_EXECUTABLE)
