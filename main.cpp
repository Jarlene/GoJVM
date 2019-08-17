
/**
* @DESCRIPTION 
* @AUTHOR didi
* @CREATE 2019-08-15.
* 
*/
//
#include "JvmInterface.h"
#include <iostream>
int main() {

    JVMInterface jvm("./featureAlgo-1.0-SNAPSHOT-jar-with-dependencies.jar:./scala-library-2.10.4.jar");
//    jmethodID  square = jvm.getStaticMethodID("square", "(I)I");
//    jmethodID  power = jvm.getStaticMethodID("power", "(II)I");
//    jmethodID  main = jvm.getStaticMethodID("main", "([Ljava/lang/String;)V");
    jmethodID div = jvm.getStaticMethodID("com/didiglobal/saturn/featurealgo/CommonOp", "div", "()Lscala/Function2;");
    if(div == NULL) {
        std::cerr << "get static method  error " << std::endl;
        return 1;
    }

//    jvm.callStaticMethod(MethodType::VOID, main);
    jvalue  res = jvm.callStaticMethod(MethodType::OBJECT, div);
    div = jvm.getMethodID("scala/Function2", "apply", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    jdouble  a = 6.0;
    jdouble  b = 4.0;
    res = jvm.callMethod(res.l, MethodType::OBJECT, div, a, b);
//    std::cout << "res: " << res.i << std::endl;
//    res = jvm.callStaticMethod(MethodType::Int, square, 2);
//    std::cout << "res: " << res.l << std::endl;

    return 0;
}