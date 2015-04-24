#include <jni.h>
#include <stdio.h>
#include <stdlib.h>

JNIEXPORT void JNICALL Java_Main_printCharArr (JNIEnv *pEnv, jclass clazz, jcharArray charArr)
{
	int len, i;

	jchar *pArr = (*pEnv)->GetCharArrayElements(pEnv, charArr, 0);
	len = (*pEnv)->GetArrayLength(pEnv, charArr);

	printf("[C] ");
	for (i = 0; i < len; i++)
		printf("%c ", pArr[i]);
	printf("\n");

	(*pEnv)->ReleaseCharArrayElements(pEnv, charArr, pArr, 0);
}

JNIEXPORT jcharArray JNICALL Java_Main_makeCharArr (JNIEnv *pEnv, jclass clazz, jint len)
{
	jcharArray charArr;
	int i;

	jchar *pArr = (jchar*)malloc(sizeof (jchar) * len);

	for (i = 0; i < len; i++) 
		pArr[i] = 'a' + i;
	
	charArr = (*pEnv)->NewCharArray(pEnv, len);

	(*pEnv)->SetCharArrayRegion(pEnv, charArr, 0, len, pArr);

	free(pArr);

	return charArr;
}
