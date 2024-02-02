package com.atguigu.innerClass;

public class OutClassTest1 {

    public static void main(String[] args) {

    }


    //1. 局部内部类的使用
    public void method1() {
        //局部内部类
        class A {
            public void eat() {
                //可以声明属性和方法
            }
        }
    }

    public OutClassTest1() {
    }

    public Comparable getInstance() {

        // 方法一
        //提供了接口的实现类的的匿名对象
//        class MyComparable implements Comparable {
//            @Override
//            public int compareTo(Object o) {
//                return 0;
//            }
//        }
//
//        return new MyComparable();


        // 方法二
        //提供了接口的匿名实现类的匿名对象
//            return new Comparable(){
//                @Override
//                public int compareTo(Object o) {
//                    return 0;
//                }
//            };

        // 方法三
        // 提供了接口的有名实现类的匿名对象
        Comparable comparable = new Comparable() {
            @Override
            public int compareTo(Object o) {
                return 0;
            }
        };
        return comparable;

    }
}


