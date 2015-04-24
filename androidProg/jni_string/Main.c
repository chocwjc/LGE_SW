#include <jni.h>
#include <stdio.h>
#include "Main.h"
JNIEXPORT void JNICALL Java_Main_printString (JNIEnv *pEnv, jclass clazz, jstring data)
{
	const char *p = (*pEnv)->GetStringUTFChars(pEnv, data, 0);
	if (p == NULL)
		return;

	printf("[C] %s\n", p);
	(*pEnv)->ReleaseStringUTFChars(pEnv, data, p);
}
JNIEXPORT jstring JNICALL Java_Main_getHelloWorld (JNIEnv *pEnv, jclass clazz)
{
	return (*pEnv)->NewStringUTF(pEnv, "Hello, World");
}

