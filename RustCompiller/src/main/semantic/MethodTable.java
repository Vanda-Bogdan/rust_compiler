package main.semantic;

import main.nodes.Mutable;
import main.nodes.expression.ExpressionNode;
import main.nodes.function.FunctionNode;
import main.nodes.function.FunctionParamListNode;
import main.nodes.function.FunctionType;
import main.nodes.letstmt.LetStatementNode;
import main.nodes.stmt.StatementNode;
import main.nodes.stmt.StatementType;

import java.util.ArrayList;

public class MethodTable {

    public ArrayList<MethodTableItem> items = new ArrayList<>();

    public void add(FunctionNode funcNode) {

        VariableTable variableTable = new VariableTable();

        //--------Заполнение таблицы методов
        //self
        if(funcNode.paramList.type != FunctionType.ASSOCIATED){
            variableTable.add("self", Mutable.NOT_MUT);
        }

        //параметры
        funcNode.paramList.list.forEach((item)-> variableTable.add(item.name, item.mut, item.type.getName()));

        //переменные в теле
        if(funcNode.body!=null){
            bodyVariables(funcNode.body, variableTable);
        }

        //добавление метода в таблицу
        items.add(new MethodTableItem(funcNode.name, funcNode.returnType.getName(), variableTable, funcNode.body!=null, funcNode.paramList.type));
    }

    private void bodyVariables(ExpressionNode body, VariableTable variableTable){
        body.stmtList.list.forEach((n)->stmtVariables(n, variableTable));
    }

    private void stmtVariables(StatementNode stmt, VariableTable variableTable){
        if(stmt.type == StatementType.LET){
            letVariables(stmt.letStmt, variableTable);
        }
    }

    private void letVariables(LetStatementNode let, VariableTable variableTable){
        variableTable.add(let.name, let.mut, let.type.getName());
    }

    private record MethodTableItem(String name, String returnType, VariableTable variableTable, boolean hasBody, FunctionType functionType) {//todo мб поменять string на TypeNode
    }
}
