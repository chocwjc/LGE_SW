#include <stdio.h>
#include <jni.h>

void Java_com_lge_Main_printHello(JNIEnv *pEnv, jclass clazz)
{
	printf("[c] Hello\n");
}
void Java_com_lge_Main_printWorld(JNIEnv *pEnv, jobject obj)
{
	printf("[c] World\n");
}
