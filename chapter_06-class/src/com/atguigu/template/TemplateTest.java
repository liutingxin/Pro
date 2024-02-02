package com.atguigu.template;

public class TemplateTest {
    public static void main(String[] args) {
        PrintPrimeNumber printPrimeNumber = new PrintPrimeNumber();

        printPrimeNumber.spendTime();

    }
}

abstract class Template {
    public void spendTime() {
        long start = System.currentTimeMillis();

        code();

        long end = System.currentTimeMillis();

        System.out.println("花费的时间"+ (end - start));
    }

    public abstract void code();
}


class PrintPrimeNumber extends Template{
    @Override
    public void code() {
        for (int i = 0; i < 10000; i++) {
            System.out.println("asdfghjkl");
        }
    }
}