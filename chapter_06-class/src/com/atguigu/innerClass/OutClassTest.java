package com.atguigu.innerClass;

public class OutClassTest {
    public static void main(String[] args) {

        //1. new Person的静态成员内部类
        Person.Dog dog = new Person.Dog();

        dog.eat();

        Person.Dog dog2 = new Person.Dog();

        /*
          java中的==和equals()最大的区别是：
          1.一个是运算符，一个是方法。
          2.==操作符专门用来比较变量的值是否相同，
                   引用类型对象变量其实是一个引用，它们的值是指向对象所在的内存地址。
          3.equals方法常用来比较对象的内容是否相同，equals()方法存在于Object类中。
         */

        System.out.println(dog);
        System.out.println(dog2);


        //2. new Person的非静态成员内部类
        // Person.Bird bird = Person.new Bird;

        Person p1 = new Person();
        Person.Bird bird = p1.new Bird();

        bird.fly();
    }

}


class Person {//外部类

    String name = "person";
    //静态的成员内部类
    static class Dog {
        public void eat() {
            System.out.println("dog eat");
        }
    }

    //非静态的成员内部类
    class Bird {
        String name = "bird";
        public void fly() { System.out.println("bird fly"); }

        public void showName(String name){
            System.out.println("name:" + this.name);

            System.out.println("Person's name: " + Person.this.name);
        }
    }
}