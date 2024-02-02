package com.atguigu.enumClass;

interface Info {
    public void show();
}

public class SeasonTest2 {

    public static void main(String[] args) {

        Season2[] sea2 = Season2.values();
        for(Season2 s2 : sea2) {
            s2.show();
        }

    }
}


interface Info2 {
    public void show();
}

//java 5.0使用enum关键字定义枚举类
enum Season2 implements Info1 {
    //1. 必须在枚举类的开头声明多个对象，使用逗号隔开每个对象
    SPRING("春天", "春暖花开"){
        @Override
        public void show() {
            System.out.println("This is a Season of SPRING from interface Info");
        }
    },
    SUMMER("夏天", "夏日炎炎"){
        @Override
        public void show() {
            System.out.println("This is a Season of Summer from interface Info");
        }
    },
    AUTUMN("秋天", "秋高气爽"){
        @Override
        public void show() {
            System.out.println("This is a Season of AUTUMN from interface Info");
        }
    },
    WINTER("冬天", "冰天雪地"){
        @Override
        public void show() {
            System.out.println("This is a Season of WINTER from interface Info");
        }
    };

    //2. 声明当前类的示例变量,使用private final修饰
    private final String SEASONAL;
    private final String SEASONED;

    //3. 私有化构造器

    private Season2(String SEASONAL, String SEASONED) {
        this.SEASONED = SEASONED;
        this.SEASONAL = SEASONAL;
    }


    //4. 提供示例变量的get方法
    public String getSEASONAL() {
        return SEASONAL;
    }

    public String getSEASONED() {
        return SEASONED;
    }

    //枚举类有一个默认的父类Enum类
    @Override
    public String toString() {
        return "Season{" +
                "SEASONNAME='" + SEASONAL + '\'' +
                ", SEASONDESC='" + SEASONED + '\'' +
                '}';
    }


    @Override
    public void show() {
        System.out.println("This is a function from interface Info");
    }
}
