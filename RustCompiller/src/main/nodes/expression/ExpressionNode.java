package main.nodes.expression;

import main.nodes.TypeNode;
import main.nodes.VarType;
import main.nodes.stmt.StatementListNode;
import main.nodes.stmt.StatementNode;
import main.semantic.FieldTable;
import main.semantic.MethodTable;
import main.semantic.StandardFunctionList;
import main.semantic.VariableTable;

import java.util.ArrayList;
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

    public boolean isReturn = false;

    //------Ссылка на элемент таблицы------
    public IdType idType;

    // *Если это локальная переменная
    public int varID;
    public VariableTable variableTable;
    public VariableTable.VariableTableItem variableTableItem(){
        return variableTable.getByID(varID);
    }

    public void setVar(int ID, VariableTable table){
        varID = ID;
        variableTable = table;
        idType = IdType.LOCAL;
    }

    public void setInitializated(){
        variableTable.setInitializated(varID);
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
        idType = IdType.FIELD;
    }

    // *Если это вызов метода
    public String methodName;
    public String standardMethodName;
    public MethodTable methodTable;
    private StandardFunctionList standardFunctionList;
    public boolean isRTLMethod = false;

    public MethodTable.MethodTableItem methodTableItem(){
        if(methodName!=null){
            return methodTable.get(methodName);
        }
        else {
            standardFunctionList = new StandardFunctionList();
            return standardFunctionList.method(standardMethodName);
        }
    }

    public void setMethod(String name, MethodTable table) {
        methodName = name;
        methodTable = table;
    }

    public void setStandartMethod(String name){
        this.standardMethodName = name;
        this.isRTLMethod = true;
    }

    public String className(){
        if(fieldName!=null){
            return fieldTable.className;
        }else if(methodName!=null){
            return methodTable.className;
        }else if(standardMethodName!=null){
            return "Main";
        }else {
            return null;
        }
    }

    public void setTypeFromVarOrField() {
        if (variableTableItem() == null && fieldTableItem() == null) {
            throw new IllegalArgumentException("variableTableItem и fieldTableItem равны null в узле " + id);
        }
        else if (variableTableItem() != null) {
            VariableTable.VariableTableItem item = variableTableItem();
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
            case PLUS, MINUS, MUL, DIV, U_MINUS, ASGN, BREAK, RETURN, STRUCT_FIELD -> countedType = exprLeft.countedType;
            case EQUAL, NOT_EQUAL, GREATER, LESS, GREATER_EQUAL, LESS_EQUAL, NEG, OR, AND, BOOL_LIT -> countedType = new TypeNode(VarType.BOOL);
            case ARRAY_AUTO_FILL -> {
                countedType = new TypeNode(VarType.ARRAY);
                countedType.exprArr = exprRight;
                countedType.typeArr = exprLeft.countedType;
            }
            case INDEX -> countedType = exprLeft.countedType.typeArr;
            case RANGE, RANGE_IN, RANGE_LEFT, RANGE_RIGHT, RANGE_IN_RIGHT -> countedType = new TypeNode("Range");
            case ID -> setTypeFromVarOrField();
            case SELF -> setTypeFromVar();
            case FIELD_ACCESS, FIELD_ACCESS_NEW -> setTypeFromField();
            case LOOP -> countedType = this.defineTypeOfLoopBody();
            case LOOP_WHILE, LOOP_FOR, CONTINUE -> countedType = new TypeNode(VOID);
            case BLOCK -> countedType = defineTypeOfBlock(stmtList);
            case INT_LIT -> countedType = new TypeNode(VarType.INT);
            case FLOAT_LIT -> countedType = new TypeNode(VarType.FLOAT);
            case CHAR_LIT -> countedType = new TypeNode(VarType.CHAR);
            case STRING_LIT -> countedType = new TypeNode(VarType.STRING);
            case STRUCT -> countedType = new TypeNode(name);
            case STATIC_METHOD, CALL, METHOD -> countedType = methodTableItem().returnType();
        }
    }

    private TypeNode defineTypeOfLoopBody() {
        // Массив break
        ArrayList<ExpressionNode> breaks = new ArrayList<>();

        // Получение возвращаемого типа break и проверка идентичности типов во всех break
        body.findBreakInBlock(breaks);
        for (int i = 0; i < breaks.size(); i++) {
            breaks.get(i).defineTypeOfExpr();
            if (i > 0 && breaks.get(0).countedType.getName() != breaks.get(i).countedType.getName()) {
                throw new IllegalArgumentException("В break ожидается тип " + breaks.get(0).countedType.getName()
                        + ", получен " + breaks.get(i).countedType.getName() + "(ID: " + breaks.get(i).id + ")");
            }
        }

        if (breaks.size() == 0)
            return new TypeNode(VarType.VOID);
        else
            return breaks.get(0).countedType;
    }

    public void findBreakInBlock(ArrayList<ExpressionNode> breaks) {
        switch (this.type) {
            case BLOCK -> {
                for (StatementNode item : this.stmtList.list) {
                    if(item.expr!=null){
                        if (item.expr.type == ExpressionType.BREAK) {
                            breaks.add(item.expr);
                        }
                        item.expr.findBreakInBlock(breaks);
                    }
                }
            }
            case LOOP_FOR, LOOP_WHILE -> {}
            default -> {
                if (body != null) {
                    body.findBreakInBlock(breaks);
                }
                if (elseBody != null) {
                    elseBody.findBreakInBlock(breaks);
                }
            }
        }
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

    public enum IdType {
        LOCAL, FIELD
    }
}
