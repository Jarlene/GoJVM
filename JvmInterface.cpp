
/**
* @DESCRIPTION 
* @AUTHOR didi
* @CREATE 2019-08-15.
* 
*/
//

#include "JvmInterface.h"


#define CALL_STATIC_METHOD(env, clazz, methodId, type, jval, args) \
    switch (type) { \
        case MethodReturnType::Int : \
            jval.i = env->CallStaticIntMethodV(clazz, methodId, args);\
            break; \
        case MethodReturnType::FLOAT : \
            jval.f = env->CallStaticFloatMethodV(clazz, methodId, args);\
            break;\
        case MethodReturnType::LONG : \
            jval.j = env->CallStaticLongMethodV(clazz, methodId, args);\
            break;\
        case MethodReturnType::DOUBLE : \
            jval.d =env->CallStaticDoubleMethodV(clazz, methodId, args);\
            break;\
        case MethodReturnType::STRING : \
            jval.l = env->CallStaticObjectMethodV(clazz, methodId, args);\
            break;\
        case MethodReturnType::OBJECT : \
            jval.l = env->CallStaticObjectMethodV(clazz, methodId, args);\
            break;\
        case MethodReturnType::CHAR : \
            jval.c = env->CallStaticCharMethodV(clazz, methodId, args);\
            break;\
        case MethodReturnType::SHORT : \
            jval.s = env->CallStaticShortMethodV(clazz, methodId,args);\
            break;\
        case MethodReturnType::BOOL : \
            jval.z =env->CallStaticBooleanMethodV(clazz, methodId, args);\
            break;\
        case MethodReturnType::BYTE : \
            jval.b = env->CallStaticByteMethodV(clazz, methodId, args);\
            break;\
        default: \
            env->CallStaticVoidMethodV(clazz, methodId, args);\
            break;\
}

#define CALL_METHOD(env, obj, methodId, type, jval, args) \
    switch (type) { \
        case MethodReturnType::Int : \
            jval.i = env->CallIntMethodV(obj, methodId, args);\
            break; \
        case MethodReturnType::FLOAT : \
            jval.f = env->CallFloatMethodV(obj, methodId, args);\
            break;\
        case MethodReturnType::LONG : \
            jval.j = env->CallLongMethodV(obj, methodId, args);\
            break;\
        case MethodReturnType::DOUBLE : \
            jval.d =env->CallDoubleMethodV(obj, methodId, args);\
            break;\
        case MethodReturnType::STRING : \
            jval.l = env->CallObjectMethodV(obj, methodId, args);\
            break;\
        case MethodReturnType::OBJECT : \
            jval.l = env->CallObjectMethodV(obj, methodId, args);\
            break;\
        case MethodReturnType::CHAR : \
            jval.c = env->CallCharMethodV(obj, methodId, args);\
            break;\
        case MethodReturnType::SHORT : \
            jval.s = env->CallShortMethodV(obj, methodId,args);\
            break;\
        case MethodReturnType::BOOL : \
            jval.z =env->CallBooleanMethodV(obj, methodId, args);\
            break;\
        case MethodReturnType::BYTE : \
            jval.b = env->CallByteMethodV(obj, methodId, args);\
            break;\
        default: \
            env->CallVoidMethodV(obj, methodId, args);\
            break;\
}


JNIEnv *JVMInterface::create_jvm(JavaVM **jvm, const char *class_path) {
    JNIEnv *env;
    JavaVMInitArgs args;
    JavaVMOption options;
    args.version = JNI_VERSION_1_6;
    args.nOptions = 1;
    std::string subfix = "-Djava.class.path=";
    auto classPath =  subfix +  std::string(class_path);
    options.optionString = const_cast<char *>(classPath.c_str());
    args.options = &options;
    args.ignoreUnrecognized = 0;
    int rv;
    rv = JNI_CreateJavaVM(jvm, (void **) &env, &args);
    if (rv < 0 || !env)
        printf("Unable to Launch JVM %d\n", rv);
    else
        printf("Launched JVM! \n");
    return env;
}





JVMInterface::~JVMInterface() {
    if (env != NULL) {
        env->DeleteGlobalRef(obj);
        obj = NULL;
        env->DeleteGlobalRef(mainClass);
        mainClass = NULL;
    }
    if (jvm != NULL) {
        jvm->DestroyJavaVM();
        jvm = NULL;
    }

}

JVMInterface::JVMInterface(const char *class_path) {
    env = create_jvm(&jvm, class_path);
}




JVMInterface::JVMInterface(const JVMInterface &jvm) {
        this->env = jvm.env;
        this->jvm = jvm.jvm;
}

JVMInterface &JVMInterface::on(const char *klass) {
    if (mainClass != NULL) {
        env->DeleteGlobalRef(mainClass);
        mainClass = NULL;
    }
    mainClass = this->env->FindClass(klass);
    return *this;
}

JVMInterface &JVMInterface::call(Param param, ...) {
    jmethodID method = NULL;
    va_list args;
    va_start(args, param);
    switch (param.methodType) {
        case STATIC :
            method = env->GetStaticMethodID(mainClass, param.methodName, param.signature);
            CALL_STATIC_METHOD(env, mainClass, method, param.returnType, res, args)
            break;
        case INSTANCE:
            method = env->GetMethodID(mainClass, param.methodName, param.signature);
            if(obj != NULL) {
                CALL_METHOD(env, obj, method, param.returnType, res, args)
            } else {
                CALL_METHOD(env, res.l, method, param.returnType, res, args)
            }
            break;
    }
    va_end(args);
    return *this;
}

jvalue JVMInterface::get() {
    return res;
}

JVMInterface &JVMInterface::on(jobject obj) {
    if (this->obj != NULL) {
        env->DeleteGlobalRef(obj);
        this->obj = NULL;
    }
    this->mainClass = env->GetObjectClass(obj);
    this->obj = obj;
    return *this;
}

jstring JVMInterface::newString(const char *str) {
    return  env->NewStringUTF(str);
}

void JVMInterface::deleteString(jstring str) {
        if (str != NULL) {
            env->DeleteLocalRef(str);
        }
}

jdoubleArray JVMInterface::newDouble(int cnt, ...) {
    jdoubleArray  res;
    va_list args;
    va_start(args, cnt);
    res = env->NewDoubleArray(cnt);
    for (int i = 0; i < cnt; ++i) {
        const double re = va_arg(args, double);
        env->SetDoubleArrayRegion(res, i, 1, &re);
    }
    va_end(args);
    return res;
}

void JVMInterface::deleteDouble(jdoubleArray array) {
    if (array != NULL) {
        env->DeleteLocalRef(array);
    }
}





