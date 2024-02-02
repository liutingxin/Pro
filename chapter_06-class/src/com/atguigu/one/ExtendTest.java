package com.atguigu.one;

public class ExtendTest extends test{
    ExtendTest() {
//        super(1);
//        System.out.println(super.name);
//        System.out.println("child");
    }

    protected void finalize() {
        System.out.println("垃圾回收器");
    }

    public int age = 123;

    @Override
    public void printInfo() {
        System.out.println("child 输出信息 ");
    }

    void finallizeTest() {
        ExtendTest ee = new ExtendTest();
        ee.printInfo();

        ee = null;
        System.gc();
    }

    public static void main(String[] args) {
        ExtendTest extendTest = new ExtendTest();

        extendTest.finallizeTest();

        System.out.println("------------------------");

//        test e = new ExtendTest();
//        e.printInfo();

//        System.out.println(e.age);
    }

    @Override
    public String toString() {
        return "ExtendTest{" +
                "age=" + age +
                '}';
    }
}



    class test {
    String name = "FATHER";

    test() {
//        System.out.println("father");
    }

    test(int a) {
//        System.out.println("A father");
    }

    public void printInfo(){
        System.out.println("father 输出信息");
    }
}
