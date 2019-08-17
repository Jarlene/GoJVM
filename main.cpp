
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

    JVMInterface jvm("./:./featureAlgo-1.0-SNAPSHOT-jar-with-dependencies.jar:./scala-library-2.10.4.jar:../unsafe-mock-8.92.1.jar");

    Param p;
    p.methodType = MethodType::STATIC;
    p.returnType = MethodReturnType::Int;
    p.methodName = "square";
    p.signature = "(I)I";

    jvalue res = jvm.on("helloWorld").
            call(p, 3).
            get();
    std::cout << "res: " << res.i << std::endl;
    p.methodName = "power";
    p.signature = "(II)I";
    res = jvm.call(p, 3,4).
            get();
    std::cout << "res: " << res.i << std::endl;
    p.returnType = MethodReturnType::VOID;
    p.methodName = "main";
    p.signature = "([Ljava/lang/String;)V";
    jvm.call(p);


    double  a = 6.0;
    double  b = 4.0;
    p.returnType = MethodReturnType::OBJECT;
    p.methodName = "div";
    p.signature = "()Lscala/Function2;";
    jvm.on("com/didiglobal/saturn/featurealgo/CommonOp").
    call(p)
    .on("scala/Function2");

    p.methodType = MethodType::INSTANCE;
    p.methodName = "apply";
    p.signature = "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;";
    jvm.call(p, a, b)
    .get();
    std::cout << "res: " << res.l << std::endl;
    return 0;
}