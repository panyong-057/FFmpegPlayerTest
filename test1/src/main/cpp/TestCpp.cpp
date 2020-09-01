//
// Created by Administrator on 2020/8/27.
//
#include <jni.h>
#include <string>
#include "TestCpp.h"
#include <android/log.h>
#define JNI_REG_CLASS "com/example/test1/MainActivity" // path of Java file
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,"JNI",__VA_ARGS__)
using namespace std;
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_test1_MainActivity_testNdk__(JNIEnv *env, jobject instance) {

    char *hello = "Hello from C++";
    return env->NewStringUTF(hello);
}
extern "C"
JNIEXPORT jstring  JNICALL
Java_com_example_test1_MainActivity_testNdk1(JNIEnv *env, jobject instance, jstring str_) {
    char *hello = "env->GEtChar";
    std::string helloStr = "Hello";
    const char *str1 = helloStr.c_str();
    const char *str2 = env->GetStringUTFChars(str_, 0);
    return env->NewStringUTF(str2);
}
extern "C"
JNIEXPORT jstring  JNICALL
Java_com_example_test1_MainActivity_testNdk2__Ljava_lang_String_2(JNIEnv *env, jobject instance,
                                                                  jstring str_) {
    const char *str2 = env->GetStringUTFChars(str_, 0);
    return env->NewStringUTF(str2);
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_test1_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    string hello = "Hello from C++";
//    Animal *animal = new Animal;
//    animal->showName();
//    delete animal;
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_test1_MainActivity_stringFromJNI1(JNIEnv *env, jobject instance, jintArray iArr_,
                                                    jobjectArray strArr_) {
    jint *iArr = env->GetIntArrayElements(iArr_, NULL);

    jsize len = env->GetArrayLength(iArr_);

    for (int i = 0; i < len; ++i) {
        __android_log_print(ANDROID_LOG_ERROR, "JNI", "%d", *(iArr + i));
    }

    //0 刷新数组  释放数组
    // 1 只刷新数组
    // 2  释放数组  对Java层没影响
    env->ReleaseIntArrayElements(iArr_, iArr, 0);

    int str_len = env->GetArrayLength(strArr_);
    for (int i = 0; i < str_len; ++i) {
        jstring str = (jstring) env->GetObjectArrayElement(strArr_, i);
        const char *s = env->GetStringUTFChars(str, 0);
        LOGE("获得的java参数是:%s", s);
        env->ReleaseStringUTFChars(str, s);
    }

    return env->NewStringUTF("hello world");
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_test1_MainActivity_stringFromJNI2(JNIEnv *env, jobject instance, jobject jobject_,
                                                    jstring str_) {

    const char *str = env->GetStringUTFChars(str_, 0);
    // TODO

    //1、获取类对象
    jclass activityCls = env->GetObjectClass(jobject_);
    //2、通过签名获取方法  参数  类对象 方法名  签名 (参数  返回类型)
    jmethodID getIndex = env->GetMethodID(activityCls, "getIndex", "()I");
    //3、调用方法
    env->CallIntMethod(jobject_, getIndex);


    jmethodID setIndex = env->GetMethodID(activityCls, "setIndex", "(I)V");
    env->CallVoidMethod(jobject_, setIndex, 100);

    jmethodID showText = env->GetStaticMethodID(activityCls,"showText" , "(Ljava/lang/String;)V");
    jstring str2=env->NewStringUTF("我是静态方法，被C++调用");
    env->CallStaticVoidMethod(activityCls,showText,str2);

    //释放局部引用
    env->DeleteLocalRef(str2);
    env->ReleaseStringUTFChars(str_, str);
    return env->NewStringUTF(str);
}




JNIEXPORT jstring JNICALL get_hello(JNIEnv *env, jobject clazz) {
    return env->NewStringUTF("hello from jni");
}

JNIEXPORT jint JNICALL meaning_of_the_universe(JNIEnv *env, jobject clazz) {
    return 42;
}

static JNINativeMethod g_methods[] = {
        { "getHello", "()Ljava/lang/String;", (void*)get_hello},
        { "meaningOfTheUniverse", "()I", (void*)meaning_of_the_universe},
};

// must define this function
JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm,void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env,JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    jclass javaClass = env->FindClass(JNI_REG_CLASS);
    if (javaClass == NULL){
        return JNI_ERR;
    }

    int method_count = sizeof(g_methods) / sizeof(g_methods[0]);
    if (env->RegisterNatives(javaClass, g_methods, method_count) < 0) {
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}