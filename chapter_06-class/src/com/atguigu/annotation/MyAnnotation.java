package com.atguigu.annotation;

public @interface MyAnnotation {
    String value() default "no value";
}
