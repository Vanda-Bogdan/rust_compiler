package main.semantic;

import main.nodes.Mutable;
import main.nodes.expression.ExpressionNode;
import main.nodes.function.FunctionNode;
import main.nodes.function.FunctionParamListNode;
import main.nodes.function.FunctionType;
import main.nodes.letstmt.LetStatementNode;
import main.nodes.stmt.StatementNode;
import main.nodes.stmt.StatementType;

import java.util.HashMap;

public class MethodTable {

    public HashMap<String, MethodTableItem> items = new HashMap<>();

    public void add(FunctionNode funcNode) {

        VariableTable variableTable = new VariableTable();

        //--------Заполнение таблицы локальных переменных
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


        //-----------------Добавление метода в таблицу
        items.put(funcNode.name, new MethodTableItem(funcNode.returnType.getName(), variableTable, funcNode.body!=null, funcNode.paramList.type));
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

    public record MethodTableItem(String returnType, VariableTable variableTable, boolean hasBody, FunctionType functionType) {//todo мб поменять string на TypeNode
    }
}
