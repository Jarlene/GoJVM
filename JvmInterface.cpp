
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
    std::string subfix = "-Djava.class.path=/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/charsets.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/deploy.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/ext/cldrdata.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/ext/dnsns.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/ext/jaccess.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/ext/jfxrt.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/ext/localedata.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/ext/nashorn.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/ext/sunec.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/ext/sunjce_provider.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/ext/sunpkcs11.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/ext/zipfs.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/javaws.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/jce.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/jfr.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/jfxswt.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/jsse.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/management-agent.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/plugin.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/resources.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/rt.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/lib/ant-javafx.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/lib/dt.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/lib/javafx-mx.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/lib/jconsole.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/lib/packager.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/lib/sa-jdi.jar:/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/lib/tools.jar:";
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
    mainClass = this->env->FindClass(klass);
    return *this;
}

JVMInterface &JVMInterface::call(Param &param, ...) {
    jmethodID method = NULL;
    va_list args;
    va_start(args, param);
    switch (param.methodType) {
        case STATIC :
            method = env->GetStaticMethodID(mainClass, param.methodName, param.signature);
            CALL_STATIC_METHOD(env, mainClass, method, param.methodType, res, args)
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






