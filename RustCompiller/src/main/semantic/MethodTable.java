package main.semantic;

import main.nodes.Mutable;
import main.nodes.expression.ExpressionListNode;
import main.nodes.expression.ExpressionNode;
import main.nodes.expression.ExpressionType;
import main.nodes.function.FunctionNode;
import main.nodes.function.FunctionType;
import main.nodes.letstmt.LetStatementNode;
import main.nodes.stmt.StatementNode;
import main.nodes.stmt.StatementType;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.concurrent.atomic.AtomicBoolean;

public class MethodTable {

    public HashMap<String, MethodTableItem> items = new HashMap<>();

    private String currentMethod = "";

    private ArrayList<VariableTable> variableTables = new ArrayList<>();

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
        variableTables.add(variableTable);
        if(funcNode.body!=null){
            bodyVariables(funcNode.body, variableTable, new ArrayList<VariableTable>());
        }

        variableTables.forEach(variableTable::merge);
        //-----------------Добавление метода в таблицу
        items.put(funcNode.name, new MethodTableItem(funcNode.returnType.getName(), variableTable, funcNode.body!=null, funcNode.paramList.type));
    }

    private void bodyVariables(ExpressionNode body, VariableTable variableTable, ArrayList<VariableTable> initialTables){
        initialTables.add(variableTable);
        VariableTable bodyTable = new VariableTable();
        body.stmtList.list.forEach((n)->stmtVariables(n, bodyTable, initialTables));
        initialTables.remove(initialTables.size()-1);
        variableTables.add(bodyTable);
    }

    private void stmtVariables(StatementNode stmt, VariableTable variableTable, ArrayList<VariableTable> initialTables){
        if(stmt.type == StatementType.LET){
            letVariables(stmt.letStmt, variableTable, initialTables);
        }
        else if (stmt.type == StatementType.EXPRESSION){
            exprVariables(stmt.expr, variableTable, initialTables);
        }
    }

    private void exprVariables(ExpressionNode expression, VariableTable variableTable, ArrayList<VariableTable> initialTables){
        if(expression==null){
            return;
        }
        switch (expression.type) {
            case IF -> ifVariables(expression, variableTable, initialTables);
            case LOOP -> loopVariables(expression, variableTable, initialTables);
            case LOOP_FOR -> loopForVariables(expression, variableTable, initialTables);
            case LOOP_WHILE -> loopWhileVariables(expression, variableTable, initialTables);
            case ID -> idVariables(expression, variableTable, initialTables);
            case PLUS, MINUS, DIV, MUL, EQUAL, NOT_EQUAL, GREATER, LESS, GREATER_EQUAL, LESS_EQUAL, OR, AND, ASGN, RANGE, RANGE_IN, INDEX, ARRAY_AUTO_FILL -> {
                exprVariables(expression.exprLeft, variableTable, initialTables);
                exprVariables(expression.exprRight, variableTable, initialTables);
            }
            case RANGE_LEFT, RANGE_RIGHT, RANGE_IN_RIGHT, QT, U_MINUS, NEG, STRUCT_FIELD, FIELD_ACCESS, BREAK, RETURN ->
                    exprVariables(expression.exprLeft, variableTable, initialTables);
            case ARRAY, CALL, METHOD, STATIC_METHOD, STRUCT -> exprListVariables(expression.exprList, variableTable, initialTables);
        }
    }

    private void exprListVariables(ExpressionListNode exprList, VariableTable variableTable, ArrayList<VariableTable> initialTables){
        if (exprList == null) {
            return;
        }
        exprList.list.forEach((expr)->{
            exprVariables(expr, variableTable, initialTables);
        });
    }

    private void idVariables(ExpressionNode ident, VariableTable variableTable, ArrayList<VariableTable> initialTables){
        boolean contains = false;
        for (VariableTable item : initialTables) {
            if(item.contains(ident.name)){
                contains = true;
                break;
            }
        }
        if(!variableTable.contains(ident.name) && !contains){
            throw new IllegalArgumentException("Необъявленная переменная " + ident.name);
        }
    }

    private void ifVariables(ExpressionNode ifNode, VariableTable variableTable, ArrayList<VariableTable> initialTables){
        bodyVariables(ifNode.body, variableTable, initialTables);
        if(ifNode.elseBody!=null){
            bodyVariables(ifNode.elseBody, variableTable, initialTables);
        }
    }

    private void loopVariables(ExpressionNode loop, VariableTable variableTable, ArrayList<VariableTable> initialTables){
        bodyVariables(loop.body, variableTable, initialTables);
    }

    private void loopForVariables(ExpressionNode loopFor, VariableTable variableTable, ArrayList<VariableTable> initialTables){
        ExpressionType type = loopFor.exprLeft.type;
        if(type!= ExpressionType.RANGE && type!=ExpressionType.RANGE_IN && type!=ExpressionType.RANGE_RIGHT
                && type!=ExpressionType.RANGE_IN_RIGHT && type!=ExpressionType.RANGE_LEFT && type!=ExpressionType.ID){
            throw new IllegalArgumentException("Неверное RANGE выражение в цикле for. ID узла: " + loopFor.id);
        }
        variableTable.add(loopFor.name, Mutable.MUT, "i32");
        bodyVariables(loopFor.body, variableTable, initialTables);
    }

    private void loopWhileVariables(ExpressionNode loopWhile, VariableTable variableTable, ArrayList<VariableTable> initialTables){
        exprVariables(loopWhile.exprLeft, variableTable, initialTables);
        bodyVariables(loopWhile.body, variableTable, initialTables);
    }

    private void letVariables(LetStatementNode let, VariableTable variableTable, ArrayList<VariableTable> initialTables){

        if(variableTable.contains(let.name)){
            //throw new IllegalArgumentException("Переопределение переменной " + let.name + " для функции " + currentMethod);
            variableTable.overwrite(let.name, let.mut, let.type.getName());
        }
        variableTable.add(let.name, let.mut, let.type.getName());
    }

    public record MethodTableItem(String returnType, VariableTable variableTable, boolean hasBody, FunctionType functionType) {//todo мб поменять string на TypeNode
    }
}
