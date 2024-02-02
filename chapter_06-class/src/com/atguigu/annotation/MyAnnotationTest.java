package com.atguigu.annotation;

@MyAnnotation(value = "hello")
public class MyAnnotationTest {

    public static void main(String[] args) {
        com.atguigu.one.ArgsTest argsTest = new com.atguigu.one.ArgsTest();
        argsTest.print(123);
        argsTest.print();

        System.out.println(argsTest.getClass().getSuperclass());
    }

//    public ArgsTest() {
//        System.out.println("构造器");
//    }

//    ~ArgsTest() {
//        System.out.println("析构器");
//    }

    public void print(int ... nums) {//可变形参就是数组，通过数组的方式取值
        if(nums.length >= 1)
            System.out.println("asd"+nums[0]);
        else
            System.out.println("No");
    }
}



