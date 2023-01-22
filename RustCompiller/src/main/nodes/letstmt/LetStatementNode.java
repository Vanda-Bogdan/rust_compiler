package main.nodes.letstmt;

import main.nodes.Mutable;
import main.nodes.TypeNode;
import main.nodes.expression.ExpressionNode;
import main.semantic.FieldTable;
import main.semantic.VariableTable;

public class LetStatementNode {
    public int id;
    public String name;
    public Mutable mut;
    public TypeNode type;
    public ExpressionNode expr;

    //------Ссылка на таблицу лок. переменных------
    private int varID;
    private VariableTable variableTable;
    public VariableTable.VariableTableItem variableTableItem(){
        return variableTable.getByID(varID);
    }

    public void setVar(int ID, VariableTable table){
        varID = ID;
        variableTable = table;
    }

    public void setVarType(TypeNode newType){
        type=newType;
        variableTable.resetType(varID, newType);
    }

}
