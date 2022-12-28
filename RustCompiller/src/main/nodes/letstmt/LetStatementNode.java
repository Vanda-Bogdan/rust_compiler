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
    private VariableTable variableTable;

    //номер в таблице лок. переменных
    private int localVarNumber;

    public VariableTable.VariableTableItem localTableItem(){
        return variableTable.get(this.localVarNumber);
    }

    public void setVar(VariableTable variableTable, int num){
        this.variableTable = variableTable;
        this.localVarNumber = num;
    }

}
