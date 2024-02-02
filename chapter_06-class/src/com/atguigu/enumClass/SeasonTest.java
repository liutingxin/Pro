package com.atguigu.enumClass;

public class SeasonTest {

    public static void main(String[] args) {
        System.out.println(Season.AUTUMN);
    }
}


//java 5.0之前定义枚举类的方式
class Season {
    private final String SEASONAL;
    private final String SEASONED;

    //1. 私有化构造器

    private Season(String SEASONAL, String SEASONED) {
        this.SEASONED = SEASONED;
        this.SEASONAL = SEASONAL;
    }

    public static final Season SPRING = new Season("春天", "春暖花开");
    public static final Season SUMMER = new Season("夏天", "夏日炎炎");
    public static final Season AUTUMN = new Season("秋天", "秋高气爽");
    public static final Season WINTER = new Season("冬天", "冰天雪地");

    public String getSEASONAL() {
        return SEASONAL;
    }

    public String getSEASONED() {
        return SEASONED;
    }

    @Override
    public String toString() {
        return "Season{" +
                "SEASONNAME='" + SEASONAL + '\'' +
                ", SEASONDESC='" + SEASONED + '\'' +
                '}';
    }
}
