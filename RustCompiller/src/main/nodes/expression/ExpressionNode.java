package main.nodes.expression;

import main.nodes.TypeNode;
import main.nodes.VarType;
import main.nodes.stmt.StatementListNode;
import main.nodes.stmt.StatementNode;
import main.semantic.FieldTable;
import main.semantic.MethodTable;
import main.semantic.VariableTable;

import java.util.Objects;

import static main.nodes.VarType.*;

public class ExpressionNode {
    public int id;
    public int anInt;
    public float aFloat;
    public boolean aBoolean;
    public String string;
    public String parentId;
    public char aChar;
    public String name;
    public ExpressionType type;
    public ExpressionNode exprLeft;
    public ExpressionNode exprRight;
    public ExpressionListNode exprList;
    public ExpressionNode body;
    public ExpressionNode elseBody;
    public StatementListNode stmtList;

    public ExpressionNode(){

    }

    //конструктор для занесения в тип массива кол-во
    public ExpressionNode(int num){
        type = ExpressionType.INT_LIT;
        anInt = num;
    }

    //для расчета типов expr
    public TypeNode countedType;

    //------Ссылка на элемент таблицы------
    // *Если это локальная переменная
    private int varID;
    private VariableTable variableTable;
    public VariableTable.VariableTableItem variableTableItem(){
        return variableTable.getByID(varID);
    }

    public void setVar(int ID, VariableTable table){
        varID = ID;
        variableTable = table;
    }

    // *Если это поле
    private String fieldName;
    private FieldTable fieldTable;
    public FieldTable.FieldTableItem fieldTableItem(){
        return fieldTable.get(fieldName);
    }

    public void setField(String name, FieldTable table){
        fieldName = name;
        fieldTable = table;
    }

    // *Если это вызов метода
    public String methodName;
    private MethodTable methodTable;
    public MethodTable.MethodTableItem methodTableItem(){
        return methodTable.get(methodName);
    }

    public void setMethod(String name, MethodTable table) {
        methodName = name;
        methodTable = table;
    }


    public void setTypeFromVarOrField() {
        if (variableTableItem() == null && fieldTableItem() == null) {
            throw new IllegalArgumentException("variableTableItem и fieldTableItem равны null в узле " + id);
        }
        else if (variableTableItem() != null) {
            countedType = variableTableItem().type();
        }
        else {
            countedType = fieldTableItem().type();
        }
    }

    public void setTypeFromField(){
        if(fieldTableItem() == null){
            throw new IllegalArgumentException("fieldTableItem равен null в узле " + id);
        }else {
            countedType = fieldTableItem().type();
        }
    }

    public void setTypeFromVar(){
        if(variableTableItem() == null){
            throw new IllegalArgumentException("variableTableItem равен null в узле " + id);
        }else {
            countedType = variableTableItem().type();
        }
    }

    /*------------------------------------------Определение типов expression----------------------------------------------*/
    public void defineTypeOfExpr() {
        if(countedType!=null){
            return;
        }
        switch (type) {
            case PLUS, MINUS, MUL, DIV -> {
                exprLeft.defineTypeOfExpr();
                exprRight.defineTypeOfExpr();
                if (exprLeft.countedType.varType == VarType.INT && exprRight.countedType.varType == VarType.INT) {
                    countedType = new TypeNode(VarType.INT);
                }
                else if (exprLeft.countedType.varType == VarType.FLOAT && exprRight.countedType.varType == VarType.FLOAT) {
                    countedType = new TypeNode(VarType.FLOAT);
                }
                else {
                    throw new IllegalArgumentException("Неверные типы выражений при выполнении арифметических операций");
                }
            }
            case EQUAL, NOT_EQUAL, GREATER, LESS, GREATER_EQUAL, LESS_EQUAL -> {
                exprLeft.defineTypeOfExpr();
                exprRight.defineTypeOfExpr();
                if (exprLeft.countedType.getName() == exprRight.countedType.getName()) {
                    countedType = new TypeNode(VarType.BOOL);
                }
                else {
                    throw new IllegalArgumentException("Несовместимые типы для выполнения операции сравнения");
                }
            }
            case QT -> {
                // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!Лучше забить!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            }
            case U_MINUS -> {
                exprLeft.defineTypeOfExpr();
                if (exprLeft.countedType.varType == VarType.INT) {
                    countedType = new TypeNode(VarType.INT);
                }
                else if (exprLeft.countedType.varType == VarType.FLOAT) {
                    countedType = new TypeNode(VarType.FLOAT);
                }
                else {
                    throw new IllegalArgumentException("Невозможно применить унарный минус к выражению данного типа");
                }
            }
            case NEG -> {
                exprLeft.defineTypeOfExpr();
                if (exprLeft.countedType.varType == VarType.BOOL) {
                    countedType = new TypeNode(VarType.BOOL);
                }
                else {
                    throw new IllegalArgumentException("Невозможно применить отрицание к не boolean выражению");
                }
            }
            case OR, AND -> {
                exprLeft.defineTypeOfExpr();
                exprRight.defineTypeOfExpr();
                if (exprLeft.countedType.varType == VarType.BOOL && exprRight.countedType.varType == VarType.BOOL) {
                    countedType = new TypeNode(VarType.BOOL);
                }
                else {
                    throw new IllegalArgumentException("Невозможно применить логические И / ИЛИ к не boolean выражениям");
                }
            }
            case ASGN, INDEX_ASGN, FIELD_ASGN -> {
                exprLeft.defineTypeOfExpr();
                exprRight.defineTypeOfExpr();
                if (Objects.equals(exprLeft.countedType.getName(), exprRight.countedType.getName())) {
                    countedType = exprLeft.countedType;
                }
                else {
                    throw new IllegalArgumentException("Несовместимые типы для выполнения операции присваивания");
                }
            }
            case BREAK, RETURN, STRUCT_FIELD -> {
                exprLeft.defineTypeOfExpr();
                countedType = exprLeft.countedType;
            }
            case ARRAY -> countedType = defineTypeOfArray(exprList);
            case ARRAY_AUTO_FILL -> {
                exprLeft.defineTypeOfExpr();
                exprRight.defineTypeOfExpr();
                if (exprLeft.countedType.varType == VarType.UNDEFINED || exprRight.countedType.varType != VarType.INT) {
                    throw new IllegalArgumentException("Неверная инициализация массива ARRAY_AUTO_FILL");
                }
                countedType = new TypeNode(VarType.ARRAY);
                countedType.exprArr = exprRight;
                countedType.typeArr = new TypeNode(exprLeft.countedType.varType);
            }
            case INDEX -> {
                exprLeft.defineTypeOfExpr();
                if (exprLeft.countedType.varType != VarType.ARRAY) {
                    throw new IllegalArgumentException("У данного типа нет операции обращения по индексу");
                }
                countedType = exprLeft.countedType.typeArr;
            }
            case RANGE, RANGE_IN, RANGE_LEFT, RANGE_RIGHT, RANGE_IN_RIGHT -> {
                if (exprLeft != null) {
                    exprLeft.defineTypeOfExpr();
                    if (exprLeft.countedType.varType != VarType.INT) {
                        throw new IllegalArgumentException("Не int тип для левого выражения range");
                    }
                }
                if (exprRight != null) {
                    exprRight.defineTypeOfExpr();
                    if (exprRight.countedType.varType != VarType.INT) {
                        throw new IllegalArgumentException("Не int тип для правого выражения range");
                    }
                }
                countedType = new TypeNode("Range");
            }
            case ID -> setTypeFromVarOrField();
            case SELF -> setTypeFromVar();
            case FIELD_ACCESS, FIELD_ACCESS_NEW -> setTypeFromField();
            case IF -> {
                exprLeft.defineTypeOfExpr();
                body.defineTypeOfExpr();
                elseBody.defineTypeOfExpr();
                if (exprLeft.countedType.varType != VarType.BOOL) {
                    throw new IllegalArgumentException("В условии if ожидается bool выражение");
                }
                if (exprLeft.aBoolean) {
                    countedType = body.countedType;
                }
                else if (elseBody != null) {
                    countedType = elseBody.countedType;
                }
            }
            case LOOP -> {
                body.defineTypeOfExpr();
                countedType = body.countedType;
            }
            case LOOP_WHILE, LOOP_FOR, CONTINUE -> countedType = new TypeNode(VOID);
            case BLOCK -> countedType = defineTypeOfBlock(stmtList);
            case INT_LIT -> countedType = new TypeNode(VarType.INT);
            case FLOAT_LIT -> countedType = new TypeNode(VarType.FLOAT);
            case CHAR_LIT -> countedType = new TypeNode(VarType.CHAR);
            case STRING_LIT -> countedType = new TypeNode(VarType.STRING);
            case BOOL_LIT -> countedType = new TypeNode(VarType.BOOL);
            case STRUCT -> countedType = new TypeNode(name);
            case STATIC_METHOD, CALL, METHOD -> countedType = methodTableItem().returnType();
        }
    }

    private TypeNode defineTypeOfArray(ExpressionListNode exprList){
        TypeNode currentType = new TypeNode(ARRAY);
        if(exprList==null){
            currentType.typeArr = new TypeNode(UNDEFINED);
            return currentType;
        }
        TypeNode bufferType;
        if(exprList.list.size()>0){
            exprList.list.get(0).defineTypeOfExpr();
            currentType.typeArr = exprList.list.get(0).countedType;
            for (ExpressionNode expr: exprList.list) {
                expr.defineTypeOfExpr();
                bufferType = expr.countedType;
                if(!bufferType.equals(currentType.typeArr)){
                    throw new IllegalArgumentException("Неверный тип узла " + expr.id + ": " + expr.countedType.getName() + " для массива с элементами типа " + currentType.typeArr.getName());
                }
            }
        }
        currentType.exprArr = new ExpressionNode(exprList.list.size());
        return currentType;
    }

    private TypeNode defineTypeOfBlock(StatementListNode stmtList){
        TypeNode result = new TypeNode(VOID);
        if(stmtList==null){
            return result;
        }

        StatementNode stmt = stmtList.list.get(stmtList.list.size() - 1);
        switch (stmt.type){
            case LET, SEMICOLON -> {
                return result;
            }
            case EXPRESSION -> {
                stmt.expr.defineTypeOfExpr();
                return stmt.expr.countedType;
            }
            default -> throw new IllegalArgumentException("define Type Of Block Error. ID: " + stmt.expr.id);
        }
    }
    
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        ExpressionNode that = (ExpressionNode) o;
        if(type!=that.type){
            return false;
        }
        switch (type){
            case INT_LIT -> {
                return anInt == that.anInt;
            }
            case FLOAT_LIT -> {
                return aFloat == that.aFloat;
            }
            case CHAR_LIT -> {
                return aChar == that.aChar;
            }
            case STRING_LIT -> {
                return Objects.equals(string, that.string);
            }
            case BOOL_LIT -> {
                return aBoolean == that.aBoolean;
            }
            case ID -> {
                return Objects.equals(name, that.name);
            }
            default -> {
                return false;
            }
        }
    }

    @Override
    public int hashCode() {
        return Objects.hash(anInt);
    }
}
