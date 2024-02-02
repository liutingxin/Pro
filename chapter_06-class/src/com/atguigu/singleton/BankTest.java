package com.atguigu.singleton;

public class BankTest {

    public static void main(String[] args) {
//        Bank bank = new Bank()；
        Bank bank1 = Bank.getInstance();
        Bank bank2 = Bank.getInstance();
        //⑤

        System.out.println(bank1.equals(bank2));
    }

}


class Bank {

    //1. 私有化构造器
    private Bank() {}

    //2.创建类的静态实例
    private static final Bank instance = new Bank();

    //3.创建类的静态返回方法
    public static Bank getInstance() {
        return instance;
    }

}
