/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_pzque_sparkdl_saoclib_nativeapi_CLEnv__ */

#ifndef _Included_com_pzque_sparkdl_saoclib_nativeapi_CLEnv__
#define _Included_com_pzque_sparkdl_saoclib_nativeapi_CLEnv__
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_pzque_sparkdl_saoclib_nativeapi_CLEnv__
 * Method:    newInstance
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_pzque_sparkdl_saoclib_nativeapi_CLEnv_00024_newInstance
  (JNIEnv *, jobject);

/*
 * Class:     com_pzque_sparkdl_saoclib_nativeapi_CLEnv__
 * Method:    destroyInstance
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_pzque_sparkdl_saoclib_nativeapi_CLEnv_00024_destroyInstance
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_pzque_sparkdl_saoclib_nativeapi_CLEnv__
 * Method:    initOpenCL
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_pzque_sparkdl_saoclib_nativeapi_CLEnv_00024_initOpenCL
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_pzque_sparkdl_saoclib_nativeapi_CLEnv__
 * Method:    getNumDevices
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_pzque_sparkdl_saoclib_nativeapi_CLEnv_00024_getNumDevices
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_pzque_sparkdl_saoclib_nativeapi_CLEnv__
 * Method:    getDeviceIDList
 * Signature: (J)[J
 */
JNIEXPORT jlongArray JNICALL Java_com_pzque_sparkdl_saoclib_nativeapi_CLEnv_00024_getDeviceIDList
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_pzque_sparkdl_saoclib_nativeapi_CLEnv__
 * Method:    getDeviceID
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_com_pzque_sparkdl_saoclib_nativeapi_CLEnv_00024_getDeviceID
  (JNIEnv *, jobject, jlong, jint);

#ifdef __cplusplus
}
#endif
#endif
