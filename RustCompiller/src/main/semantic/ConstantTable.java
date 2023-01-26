package main.semantic;

import main.generation.utils.Utils;
import main.nodes.TypeNode;
import main.nodes.function.FunctionParamListNode;
import main.nodes.function.FunctionParamNode;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Objects;

public class ConstantTable {

    public ConstantTable(){
        add(Constant.UTF8, "Code");
        add(Constant.UTF8, "<init>");
    }

    public ArrayList<ConstantTableItem> items = new ArrayList<>();

    public int add(Constant constant, int num1) {
        if(contains(constant, num1)){
            return getConstNumber(constant, num1);
        }
        else {
            items.add(new ConstantTableItem(constant, num1));
            return items.size() - 1;
        }
    }

    public int add(Constant constant, int num1, int num2) {
        if(contains(constant, num1, num2)){
            return getConstNumber(constant, num1, num2);
        }
        else {
            items.add(new ConstantTableItem(constant, num1, num2));
            return items.size() - 1;
        }
    }

    public int add(Constant constant, String utf8) {
        if(contains(constant, utf8)){
            return getConstNumber(constant, utf8);
        }
        else {
            items.add(new ConstantTableItem(constant, utf8));
            return items.size() - 1;
        }
    }

    public boolean contains(Constant constant, String utf8){
        return items.contains(new ConstantTableItem(constant, utf8));
    }

    public boolean contains(Constant constant, int num1){
        return items.contains(new ConstantTableItem(constant, num1));
    }

    public boolean contains(Constant constant, int num1, int num2){
        return items.contains(new ConstantTableItem(constant, num1, num2));
    }

    public int getConstNumber(Constant constant){
        for (ConstantTableItem item: items) {
            if(item.type==constant){
                return items.indexOf(item);
            }
        }
        return -1;
    }

    public int getConstNumber(Constant constant, String utf8){
        for (ConstantTableItem item: items) {
            if(item.type==constant && Objects.equals(item.utf8, utf8)){
                return items.indexOf(item);
            }
        }
        return -1;
    }

    public int getConstNumber(Constant constant, int num1){
        for (ConstantTableItem item: items) {
            if(item.type==constant && item.firstVal==num1){
                return items.indexOf(item);
            }
        }
        return -1;
    }

    public int getConstNumber(Constant constant, int num1, int num2){
        for (ConstantTableItem item: items) {
            if(item.type==constant && item.firstVal==num1 && item.secondVal==num2){
                return items.indexOf(item);
            }
        }
        return -1;
    }

    public int addClass(String name){
        for (ConstantTableItem item: items) {
            if(item.type==Constant.CLASS && Objects.equals(items.get(item.firstVal).utf8(), name)){
                return items.indexOf(item);
            }
        }
        return add(Constant.CLASS, add(Constant.UTF8, name));
    }

    public int addMethodRef(String className, String name, String type){
        int natNum = add(Constant.NAME_AND_TYPE, add(Constant.UTF8, name), add(Constant.UTF8, type));
        return add(Constant.METHOD_REF, addClass(className), natNum);
    }

    public record ConstantTableItem(Constant type, String utf8, int firstVal, int secondVal) {

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

    // -----------------------------------Перевод таблицы констант в массив байт--------------------------------------//
    public byte[] constantTableToByteArray() throws IOException {

        ArrayList<byte[]> result = new ArrayList<>();
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        DataOutputStream dout = new DataOutputStream(out);

        for (ConstantTableItem item : items) {
            switch (item.type()) {
                case UTF8 -> {
                    dout.write(item.type.code);
                    dout.writeShort(item.utf8().length());
                    dout.write(item.utf8().getBytes());
                }
                case INTEGER -> {
                    dout.write(item.type.code);
                    dout.writeInt(item.firstVal);
                }
                case FLOAT -> {
                    dout.write(item.type.code);
                }
                case STRING, CLASS -> {
                    dout.write(item.type.code);
                    dout.writeShort(item.firstVal() + 1);
                }
                case NAME_AND_TYPE, FIELD_REF, METHOD_REF -> {
                    dout.write(item.type.code);
                    dout.writeShort(item.firstVal() + 1);
                    dout.writeShort(item.secondVal() + 1);
                }
            }
        }
        return out.toByteArray();
    }


    public static String funcTypeForTable(TypeNode returnType, FunctionParamListNode paramList){
        String result = "(";
        if(paramList!=null){
            for(FunctionParamNode param : paramList.list){
                result+=param.type.getNameForTable();
            }
        }
        result+= ")" + returnType.getNameForTable();
        return result;
    }
}

