
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

    JVMInterface jvm("../:../featureAlgo-1.0-SNAPSHOT-jar-with-dependencies.jar:../scala-library-2.10.4.jar");

    Param p({MethodType::STATIC, MethodReturnType::Int, "square", "(I)I"});

    jvalue res = jvm.on("helloWorld").
            call(p, 3).
            get();
    std::cout << "res: " << res.i << std::endl;
    p.methodName = "power";
    p.signature = "(II)I";
    res = jvm.call(p, 3,4).get();
    std::cout << "res: " << res.i << std::endl;
    p.returnType = MethodReturnType::VOID;
    p.methodName = "main";
    p.signature = "([Ljava/lang/String;)V";
    jvm.call(p);


    double  a = 6.0;
    double  b = 4.0;
    p.returnType = MethodReturnType::OBJECT;
    p.methodName = "logExpr";
    p.signature = "()Lscala/Function1;";
    res = jvm.on("com/didiglobal/saturn/featurealgo/CommonOp").call(p).get();
    p.methodType = INSTANCE;
    p.returnType = DOUBLE;
    p.methodName = "apply";
    p.signature = "(D)D";
//    auto pr = jvm.newDouble(5, a, b, a, a, a);
    res = jvm.on(res.l).call(p, a).get();
    std::cout << "res: " << res.d << std::endl;
//    jvm.deleteDouble(pr);
    return 0;
}