#include <jni.h>
#include <stdlib.h>
void Java_Main_print2DIntArr (JNIEnv *pEnv, jclass clazz, jobjectArray objArr)
{
	int i, j;
	jint (*pArr)[3] = (jint (*)[3])malloc(sizeof (jint) * 2 * 3);

	for (i = 0; i < 2; i++) {

		jintArray intArr = (jintArray)(*pEnv)->GetObjectArrayElement(pEnv, objArr, i);

		GetObjectArrayElement

		jint *p = (*pEnv)->GetIntArrayElements(pEnv, intArr, 0);

		for (j = 0; j < 3; j++)
			pArr[i][j] = p[j];
	}


	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++) {
			printf("%d ", pArr[i][j]);
		}
	}
	printf("\n");
	free(pArr);
}

jobjectArray Java_Main_make2DIntArr (JNIEnv *pEnv, jclass clazz, jint row, jint col)
{
	int i;
	jobjectArray objArr;
	jintArray    intArr;
	jclass       intArrayClass;

	intArrayClass = (*pEnv)->FindClass(pEnv, "[I");

	objArr = (*pEnv)->NewObjectArray(pEnv, 2, intArrayClass, 0);

	for (i = 0; i < row; i++) {
		
		jint tempArr[128] = {0,};

		intArr = (*pEnv)->NewIntArray(pEnv, col);
		(*pEnv)->SetIntArrayRegion(pEnv, intArr, 0, col, tempArr);
		(*pEnv)->SetObjectArrayElement(pEnv, objArr, i, intArr);
		(*pEnv)->DeleteLocalRef(pEnv, intArr);
	}

	return objArr;
}
