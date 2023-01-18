package main.nodes;

import main.nodes.expression.ExpressionNode;

import java.util.Objects;

public class TypeNode {
    public int id;
    public VarType varType;
    public String name;
    public TypeNode typeArr;
    public ExpressionNode exprArr;

    public String getName() {
        if(varType == VarType.ID){
            return name;
        }
        else if(varType != VarType.ARRAY){
            return varType.toString();
        }
        else {
            return "[" + typeArr.getName() + "; " + exprArr.anInt + "]";
        }
    }

    public String getNameForTable(){
        if(varType == VarType.ID){
            return name;    // TODO сделать i32, f64 ключевыми словами языка
        }
        else if(varType != VarType.ARRAY){
            return typeParse(varType);
        }
        else {
            return "[" + typeArr.getArrayName();
        }
    }

    public String getArrayName(){
        if(varType == VarType.ID){
            return "L" + name + ";";
        }
        else if(varType != VarType.ARRAY){
            return "L" + varType.toString() + ";";
        }
        else {
            return "[" + typeArr.getArrayName();
        }
    }

    private static String typeParse(VarType type) {
        switch (type) {
            case INT -> {
                return "I";
            }
            case CHAR -> {
                return "C";
            }
            case STRING -> {
                return "S";
            }
            case FLOAT -> {
                return "F";
            }
            case BOOL -> {
                return "B";
            }
            case EMPTY_TYPE -> {
                return "V";
            }
            default -> {
                return null;
            }
        }
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        TypeNode typeNode = (TypeNode) o;

        if(!varType.equals(typeNode.varType)){
            return false;
        }
        else {
            if(varType==VarType.ARRAY){
                return exprArr.equals(typeNode.exprArr) && typeArr.equals(typeNode.typeArr)
            }
            else {
                return true;
            }
        }
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, name);
    }
}
