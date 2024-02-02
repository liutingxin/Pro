package com.atguigu.one;

public class Phone {
    String name;
    double price;

    public void call() {
        System.out.println("拨打电话");
    }

    public void sendMessage(String info){
        System.out.println("发送信息"+info);
    }

    public void playGame() {
        System.out.println("手机玩游戏");
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }


    @Override
    public String toString() {
        return "Phone{" +
                "name='" + name + '\'' +
                ", price=" + price +
                '}';
    }
}
