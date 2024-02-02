package com.atguigu.innerClass;

public class OutClassTest2 {

    public static void main(String[] args) {

        //
        SubA a = new SubA();
        a.method1();

        //1 提供接口匿名实现的内部类对象
        A a1 = new A() {
            @Override
            public void method1() {
                System.out.println("a1");
            }
        };
        a1.method1();

        //2 提供了接口匿名实现类的匿名对象
        new A() {
            @Override
            public void method1() {
                System.out.println("a2");
            }
        }.method1();

        //
        SubB b1 = new SubB();
        b1.method2();

        //3
        new SubB(){
            @Override
            public void method2() {
                System.out.println("b2");
            }
        }.method2();

        //4 提供了继承与抽象类的子类的对象
        B b = new B() {
            @Override
            public void method2() {
                System.out.println("继承与抽象类的子类调用的方法");
            }
        };
        b.method2();

        System.out.println(b.getClass());
        System.out.println(b.getClass().getSuperclass());


        //5 提供了一个继承于C的匿名子类的对象
        C c = new C(){};
        c.method1();
        System.out.println(c.getClass());
        System.out.println(c.getClass().getSuperclass());
    }
}


interface A {
    public void method1();

}

abstract class B {
    public abstract void method2();
}

class SubA implements A {
    @Override
    public void method1() {
        System.out.println("SubA");
    }
}

class SubB extends B {
    @Override
    public void method2() {
        System.out.println("SubB");
    }
}

class C {
    public void method1() {
        System.out.println("c");
    }
}