LOCAL_PATH:= $(call my-dir)

# LedService
include $(CLEAR_VARS)
LOCAL_SRC_FILES := BnBacklightService.cpp service_main.cpp IBacklightService.cpp
LOCAL_SHARED_LIBRARIES := libbinder libcutils libutils
LOCAL_MODULE := BacklightService
include $(BUILD_EXECUTABLE)

# LedClient
include $(CLEAR_VARS)
LOCAL_SRC_FILES := BpBacklightService.cpp client_main.cpp IBacklightService.cpp
LOCAL_SHARED_LIBRARIES := libbinder libcutils libutils
LOCAL_MODULE := BacklightClient
include $(BUILD_EXECUTABLE)
