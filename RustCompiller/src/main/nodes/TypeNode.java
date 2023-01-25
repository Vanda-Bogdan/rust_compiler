package main.nodes;

import main.nodes.expression.ExpressionNode;

import java.util.Objects;
//[i32;2]
public class TypeNode {
    public int id;
    public VarType varType;
    public String name;
    public TypeNode typeArr;
    public ExpressionNode exprArr;

    public TypeNode(VarType varType){
        this.varType = varType;
    }

    //конструктор для ID и Enum
    public TypeNode(String name){
        this.varType = VarType.ID;
        this.name = name;
    }

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

    public String getConstNameForTable(){
        if(varType == VarType.ID){
            return name;
        }
        else if(varType != VarType.ARRAY){
            return typeParse(varType);
        }
        else {
            return "[" + typeArr.getArrayName();
        }
    }

    public String getNameForTable(){
        if(varType == VarType.ID){
            return "L" + name + ";";
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
            case VOID -> {
                return "V";
            }
            case UNDEFINED -> {
                return "UNDEFINED";
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
                return exprArr.equals(typeNode.exprArr) && typeArr.equals(typeNode.typeArr);
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
