package com.atguigu.singleton;

public class BankTest1 {

    public static void main(String[] args) {
//        Bank bank = new Bank()；
        Bank1 bank1 = Bank1.instance;

        //⑤

        System.out.println(GIRLFRIEND.XIAO_LI);
    }

}


//jdk5.0之前使用的枚举类定义单例模式
class Bank1 {

    //1. 私有化构造器
    private Bank1() {}

    //2.创建类的静态实例
    public static final Bank1 instance = new Bank1();

}


//jdk5.0使用的枚举类定义单例模式
enum GIRLFRIEND {
    XIAO_LI(15);

    private final int age;

    private GIRLFRIEND(int age) {
        this.age = age;
    }

}