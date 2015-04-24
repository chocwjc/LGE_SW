#include <jni.h>
#include <stdio.h>
#include <stdlib.h>

JNIEXPORT void JNICALL Java_Main_printIntArr (JNIEnv *pEnv, jclass clazz, jintArray intArr)
{
	int len, i;

	jint *pArr = (*pEnv)->GetIntArrayElements(pEnv, intArr, 0);
	len = (*pEnv)->GetArrayLength(pEnv, intArr);

	printf("[C] ");
	for (i = 0; i < len; i++)
		printf("%d ", pArr[i]);
	printf("\n");

	(*pEnv)->ReleaseIntArrayElements(pEnv, intArr, pArr, 0);
}

JNIEXPORT jintArray JNICALL Java_Main_makeIntArr (JNIEnv *pEnv, jclass clazz, jint len)
{
	jintArray intArr;
	int i;

	int *pArr = (int*)malloc(sizeof (jint) * len);

	for (i = 0; i < len; i++) 
		pArr[i] = i + 1;
	
	intArr = (*pEnv)->NewIntArray(pEnv, len);

	(*pEnv)->SetIntArrayRegion(pEnv, intArr, 0, len, pArr);

	free(pArr);

	return intArr;
}
