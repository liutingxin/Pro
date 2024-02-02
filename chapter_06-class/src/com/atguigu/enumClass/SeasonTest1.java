package com.atguigu.enumClass;

public class SeasonTest1 {

    public static void main(String[] args) {
        System.out.println(Season1.SPRING.getClass());
        System.out.println(Season1.SPRING.getClass().getSuperclass());


        System.out.println(Season1.AUTUMN.toString());

        System.out.println(Season1.AUTUMN.name());

        Season1[] values = Season1.values();
        for(Season1 s:values){
            System.out.println(s);
        }

        Season1 ss = Season1.valueOf("WINTER");
        System.out.println(ss);

        System.out.println(Season1.AUTUMN.ordinal());
        

        Season1.WINTER.show();
    }
}


interface Info1 {
    public void show();
}

//java 5.0使用enum关键字定义枚举类
enum Season1 implements Info1 {
    //1. 必须在枚举类的开头声明多个对象，使用逗号隔开每个对象
    SPRING("春天", "春暖花开"),
    SUMMER("夏天", "夏日炎炎"),
    AUTUMN("秋天", "秋高气爽"),
    WINTER("冬天", "冰天雪地");

    //2. 声明当前类的示例变量,使用private final修饰
    private final String SEASONAL;
    private final String SEASONED;

    //3. 私有化构造器

    private Season1(String SEASONAL, String SEASONED) {
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
