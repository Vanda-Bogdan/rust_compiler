package main.semantic;

import main.nodes.Mutable;
import main.nodes.expression.ExpressionNode;
import main.nodes.expression.ExpressionType;
import main.nodes.function.FunctionNode;
import main.nodes.function.FunctionParamListNode;
import main.nodes.function.FunctionType;
import main.nodes.letstmt.LetStatementNode;
import main.nodes.stmt.StatementNode;
import main.nodes.stmt.StatementType;

import java.util.HashMap;

public class MethodTable {

    public HashMap<String, MethodTableItem> items = new HashMap<>();

    private String currentMethod = "";

    public void add(FunctionNode funcNode) {

        VariableTable variableTable = new VariableTable();
        currentMethod = funcNode.name;
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
        VariableTable bodyTable = new VariableTable();
        body.stmtList.list.forEach((n)->stmtVariables(n, bodyTable));
        variableTable.merge(bodyTable);
    }

    private void stmtVariables(StatementNode stmt, VariableTable variableTable){
        if(stmt.type == StatementType.LET){
            letVariables(stmt.letStmt, variableTable);
        }
        else if (stmt.type == StatementType.EXPRESSION){
            exprStmtVariables(stmt.expr, variableTable);
        }
    }

    private void exprStmtVariables(ExpressionNode expression, VariableTable variableTable){
        switch (expression.type){
            case IF -> ifVariables(expression, variableTable);
            case LOOP -> loopVariables(expression, variableTable);
            case LOOP_FOR -> loopForVariables(expression, variableTable);
            case LOOP_WHILE -> loopWhileVariables(expression, variableTable);
        }
    }

    private void ifVariables(ExpressionNode ifNode, VariableTable variableTable){
        bodyVariables(ifNode.body, variableTable);
        if(ifNode.elseBody!=null){
            bodyVariables(ifNode.elseBody, variableTable);
        }
    }

    private void loopVariables(ExpressionNode loop, VariableTable variableTable){
        bodyVariables(loop.body, variableTable);
    }

    private void loopForVariables(ExpressionNode loopFor, VariableTable variableTable){
        ExpressionType type = loopFor.exprLeft.type;
        if(type!= ExpressionType.RANGE && type!=ExpressionType.RANGE_IN && type!=ExpressionType.RANGE_RIGHT
                && type!=ExpressionType.RANGE_IN_RIGHT && type!=ExpressionType.RANGE_LEFT && type!=ExpressionType.ID){
            throw new IllegalArgumentException("Неверное RANGE выражение в цикле for. ID узла: " + loopFor.id);
        }
        variableTable.add(loopFor.name, Mutable.MUT, "i32");
        bodyVariables(loopFor.body, variableTable);
    }

    private void loopWhileVariables(ExpressionNode loopWhile, VariableTable variableTable){
        bodyVariables(loopWhile.body, variableTable);
    }

    private void letVariables(LetStatementNode let, VariableTable variableTable){
        if(variableTable.contains(let.name)){
            throw new IllegalArgumentException("Переопределение переменной " + let.name + " для функции " + currentMethod);
        }
        variableTable.add(let.name, let.mut, let.type.getName());
    }

    public record MethodTableItem(String returnType, VariableTable variableTable, boolean hasBody, FunctionType functionType) {//todo мб поменять string на TypeNode
    }
}
