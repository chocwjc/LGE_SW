LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := liblog 
LOCAL_SRC_FILES := led_service3.c binder.c
LOCAL_MODULE := led_service3
include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := liblog 
LOCAL_SRC_FILES := led_client3.c binder.c
LOCAL_MODULE := led_client3
include $(BUILD_EXECUTABLE)
