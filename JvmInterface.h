
/**
* @DESCRIPTION 
* @AUTHOR didi
* @CREATE 2019-08-15.
* 
*/
//

#include <jni.h>
#include <jni_md.h>
#include <string>
#include <memory>

#ifndef GOJVM_JVMINTERFACE_H
#define GOJVM_JVMINTERFACE_H

enum MethodType{
    Int,
    CHAR,
    SHORT,
    BOOL,
    BYTE,
    LONG,
    DOUBLE,
    FLOAT,
    STRING,
    VOID,
    OBJECT
} ;

class JVMInterface {
public:
    JVMInterface(const char* class_path);

    jmethodID  getMethodID(const char* clazz, const char *name, const char *sig) ;

    jmethodID  getStaticMethodID(const char* clazz, const char *name, const char *sig);

    jvalue callStaticMethod(MethodType type, jmethodID methodId, ...);

    jvalue callMethod(MethodType type, jmethodID methodId, ...);

    jvalue callMethod(jobject object, MethodType type, jmethodID methodId, ...);

    ~JVMInterface();

private:
    JNIEnv *create_jvm(JavaVM **jvm, const char *class_path) ;


private:
    JNIEnv *env;
    jclass mainClass;
    JavaVM *jvm;
    jobject obj;
};


#endif //GOJVM_JVMINTERFACE_H
