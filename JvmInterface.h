
/**
* @DESCRIPTION 
* @AUTHOR didi
* @CREATE 2019-08-15.
* 
*/
//

#include <jni_md.h>
#include <jvmti.h>
#include <string>
#include <memory>

#ifndef GOJVM_JVMINTERFACE_H
#define GOJVM_JVMINTERFACE_H

enum MethodType {
    STATIC,
    INSTANCE
};

enum MethodReturnType{
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


struct Param{
    MethodType methodType;
    MethodReturnType returnType;
    char * methodName;
    char * signature;
};


class JVMInterface {
public:
    JVMInterface(const char* class_path);

    JVMInterface(const JVMInterface &jvm);

    JVMInterface &on(const char* klass);

    JVMInterface &call(Param param, ...);

    jvalue get();

    ~JVMInterface();

private:
    static JNIEnv *create_jvm(JavaVM **jvm, const char *class_path) ;


private:
    JNIEnv *env = NULL;
    jclass mainClass = NULL;
    JavaVM *jvm = NULL;
    jobject obj = NULL;
    jvalue res;
};


#endif //GOJVM_JVMINTERFACE_H
