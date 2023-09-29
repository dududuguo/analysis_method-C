package org.example;

/*
    test file
 */

public class test {
    int aa=10;
    int bb=20;
    void foo(){
        int a=10;
    }


    public static void main(String[] args) {
        test t = new test();
        t.foo();
        t.aa=30;
        int i3=t.bb;
        int i = 10;
        int i2 = 20;
        int c = i + i2;
        i2 = 30;
    }
}
