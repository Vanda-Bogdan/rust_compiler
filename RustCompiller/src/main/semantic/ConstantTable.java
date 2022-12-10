package main.semantic;

import java.util.ArrayList;

public class ConstantTable {

    public ArrayList<ConstantTableItem> items = new ArrayList<>();

    public int add(Constant constant, int num1) {
        items.add(new ConstantTableItem(constant, num1));
        return items.size();
    }

    public int add(Constant constant, int num1, int num2) {
        items.add(new ConstantTableItem(constant, num1, num2));
        return items.size();
    }

    public int add(Constant constant, String utf8) {
        items.add(new ConstantTableItem(constant, utf8));
        return items.size();
    }


    public boolean exists(Constant constant, String utf8){
        return items.contains(new ConstantTableItem(constant, utf8));
    }

    public boolean exists(Constant constant, int num1){
        return items.contains(new ConstantTableItem(constant, num1));
    }

    public boolean exists(Constant constant, int num1, int num2){
        return items.contains(new ConstantTableItem(constant, num1, num2));
    }

    /*public int searchByUtf8(String utf8) {
        for (ConstantTableItem element : items) {
            if (element.type().code == Constant.UTF8.code && element.utf8() == utf8) {
                return element.type().code;
            }
        }
        return -1;
    }*/

    private record ConstantTableItem(Constant type, String utf8, int firstVal, int secondVal) {

        ConstantTableItem(Constant type, String utf8){
            this(type, utf8, -1, -1);
        }

        ConstantTableItem(Constant type, int num1){
            this(type, "", num1, -1);
        }

        ConstantTableItem(Constant type, int num1, int num2){
            this(type, "", num1, num2);
        }
    }
}

