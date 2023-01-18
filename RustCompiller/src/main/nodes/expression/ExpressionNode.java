package main.nodes.expression;

import main.nodes.TypeNode;
import main.nodes.VarType;
import main.nodes.stmt.StatementListNode;
import main.semantic.FieldTable;
import main.semantic.VariableTable;

import java.util.Objects;

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

    //для расчета типов expr
    public TypeNode countedType;

    //------Ссылка на элемент таблицы (полей или лок. переменных)------
    // *Если это локальная переменная
    private VariableTable.VariableTableItem variableTableItem;


    public void setVar(VariableTable.VariableTableItem item){
        this.variableTableItem = item;
    }

    // *Если это поле
    private FieldTable.FieldTableItem fieldTableItem;

    public void setVar(FieldTable.FieldTableItem item){
        this.fieldTableItem = item;
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
