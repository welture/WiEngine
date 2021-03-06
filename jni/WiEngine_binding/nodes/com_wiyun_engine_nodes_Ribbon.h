/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_wiyun_engine_nodes_Ribbon */

#ifndef _Included_com_wiyun_engine_nodes_Ribbon
#define _Included_com_wiyun_engine_nodes_Ribbon
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_wiyun_engine_nodes_Ribbon
 * Method:    forceFirstPoint
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_wiyun_engine_nodes_Ribbon_forceFirstPoint
  (JNIEnv *, jobject);

/*
 * Class:     com_wiyun_engine_nodes_Ribbon
 * Method:    addPoint
 * Signature: (Lcom/wiyun/engine/types/WYPoint;)V
 */
JNIEXPORT void JNICALL Java_com_wiyun_engine_nodes_Ribbon_addPoint
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_wiyun_engine_nodes_Ribbon
 * Method:    update
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_com_wiyun_engine_nodes_Ribbon_update
  (JNIEnv *, jobject, jfloat);

/*
 * Class:     com_wiyun_engine_nodes_Ribbon
 * Method:    nativeGetTexture
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_wiyun_engine_nodes_Ribbon_nativeGetTexture
  (JNIEnv *, jobject);

/*
 * Class:     com_wiyun_engine_nodes_Ribbon
 * Method:    setTexture
 * Signature: (Lcom/wiyun/engine/opengl/Texture2D;)V
 */
JNIEXPORT void JNICALL Java_com_wiyun_engine_nodes_Ribbon_setTexture
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_wiyun_engine_nodes_Ribbon
 * Method:    getBlendFuncSrc
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_wiyun_engine_nodes_Ribbon_getBlendFuncSrc
  (JNIEnv *, jobject);

/*
 * Class:     com_wiyun_engine_nodes_Ribbon
 * Method:    getBlendFuncDst
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_wiyun_engine_nodes_Ribbon_getBlendFuncDst
  (JNIEnv *, jobject);

/*
 * Class:     com_wiyun_engine_nodes_Ribbon
 * Method:    setBlendFunc
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_wiyun_engine_nodes_Ribbon_setBlendFunc
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     com_wiyun_engine_nodes_Ribbon
 * Method:    reset
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_wiyun_engine_nodes_Ribbon_reset
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
