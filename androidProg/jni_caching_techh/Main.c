#include <jni.h>
/*
 * Class:     Main
 * Method:    getArea
 * Signature: (I)F
 */
JNIEXPORT jfloat JNICALL Java_Main_getArea(JNIEnv *pEnv, jclass clazz, jint val)
{
	static jclass gCircleClass = 0;
	jclass CircleClass = 0;
	jmethodID getAreaID;
	float     result;

	// 아무리 static 변수로 선언하더라도 JNI 에서는 local 변수들은 호출 후 값이 유효하지 않게됨
	// 따라서 다른 방법이 필요함
#if 0
	static jclass CircleClass = NULL;
	if (CircleClass == NULL)
		CircleClass = (*pEnv)->FindClass(pEnv, "Circle");
#endif

	if (gCircleClass == NULL)
	{
		CircleClass  = (*pEnv)->FindClass(pEnv, "Circle");
		gCircleClass = (*pEnv)->NewGlobalRef(pEnv,CircleClass);
	}

	getAreaID   = (*pEnv)->GetStaticMethodID(pEnv, gCircleClass, "getArea", "(I)F");

	result = (*pEnv)->CallStaticFloatMethod(pEnv, gCircleClass, getAreaID, val);

	return result;

}

