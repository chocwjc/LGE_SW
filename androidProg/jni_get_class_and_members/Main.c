#include <jni.h>
#include <stdio.h>
jfloat Java_Main_getCircleArea(JNIEnv *pEnv, jclass clazz, jint r)
{
	jclass CircleClass;
	jmethodID getCircleArea;
	jfloat result;

	// 1. Find class info.
	CircleClass = (*pEnv)->FindClass(pEnv, "Circle");

	// 2. Find class method info.
	getCircleArea = (*pEnv)->GetStaticMethodID(pEnv, CircleClass, "getArea", "(I)F");

	// 3. Call method (when it is static function)
	result =  (*pEnv)->CallStaticFloatMethod(pEnv, CircleClass, getCircleArea, r);

	// 4. Find member variable (static)
	jfieldID PIid;
	jfloat PI;

	PIid = (*pEnv)->GetStaticFieldID(pEnv, CircleClass, "PI", "F");
	PI = (*pEnv)->GetStaticFloatField(pEnv, CircleClass, PIid);

	printf("%f\n", PI);


	return result;
}
	
