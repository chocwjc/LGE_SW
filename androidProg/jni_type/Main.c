#include <jni.h>
#include <stdio.h>
#include "Main.h"

JNIEXPORT void JNICALL Java_Main_printInt(JNIEnv *pEnv, jclass clazz, jint data)
{
	printf("[c - int] %d\n", data);
}

JNIEXPORT void JNICALL Java_Main_printByte(JNIEnv *pEnv, jclass clazz, jbyte data)
{
	printf("[c - byte] %d\n", data);
}

// typedef unit16_t jchar
JNIEXPORT void JNICALL Java_Main_printChar(JNIEnv *pEnv, jclass clazz, jchar data)
{
	printf("[c - char] %c\n", data);
}

JNIEXPORT void JNICALL Java_Main_printShort(JNIEnv *pEnv, jclass clazz, jshort data)
{
	printf("[c - short] %d\n", data);
}

// typedef uint64_t jlong
JNIEXPORT void JNICALL Java_Main_printLong(JNIEnv *pEnv, jclass clazz, jlong data)
{
	printf("[c - long] %ld\n", data);
}

// typedef float jfloat
JNIEXPORT void JNICALL Java_Main_printFloat(JNIEnv *pEnv, jclass clazz, jfloat data)
{
	printf("[c] %f\n", data);
}

// typedef double jdouble
JNIEXPORT void JNICALL Java_Main_printDouble(JNIEnv *pEnv, jclass clazz, jdouble data)
{
	printf("[c] %lf\n", data);
}

// typedef uint8 jboolean
JNIEXPORT void JNICALL Java_Main_printBoolean(JNIEnv *pEnv, jclass clazz, jboolean data)
{
	printf("[c] %d\n", data);
}

