package main.semantic;

import main.nodes.Mutable;
import main.nodes.TypeNode;
import main.nodes.VarType;
import main.nodes.expression.ExpressionListNode;
import main.nodes.expression.ExpressionNode;
import main.nodes.expression.ExpressionType;
import main.nodes.function.FunctionNode;
import main.nodes.function.FunctionParamListNode;
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

    public MethodTableItem getMethod(String name){
        return items.get(name);
    }

    public void add(String name, MethodTableItem item){
        items.put(name, item);
    }

    private Tables tables;

    public void add(FunctionNode funcNode, FieldTable fields, Tables tables){
        this.tables = tables;
        variableTables.clear();
        VariableTable variableTable = new VariableTable();
        VariableTable variableTableFinal = new VariableTable();
        currentMethod = funcNode.name;
        //--------Заполнение таблицы локальных переменных
        //self
        if(funcNode.paramList.type != FunctionType.ASSOCIATED){
            variableTable.add("self", Mutable.NOT_MUT);
        }

        //параметры
        funcNode.paramList.list.forEach((item)-> variableTable.add(item.name, item.mut, item.type));

        //переменные в теле
        variableTables.add(variableTable);
        if(funcNode.body!=null){
            bodyVariables(funcNode.body, variableTable, new ArrayList<>(), fields);
        }

        variableTables.forEach(variableTableFinal::merge);
        //-----------------Добавление метода в таблицу
        items.put(funcNode.name, new MethodTableItem(funcNode.returnType, variableTableFinal, funcNode.body!=null, funcNode.paramList.type, funcNode.paramList));
    }

    private void bodyVariables(ExpressionNode body, VariableTable variableTable, ArrayList<VariableTable> initialTables, FieldTable fields){
        initialTables.add(variableTable);
        VariableTable bodyTable = new VariableTable();
        body.stmtList.list.forEach((n)->stmtVariables(n, bodyTable, initialTables, fields));
        initialTables.remove(initialTables.size()-1);
        if(bodyTable.size()>0){
            variableTables.add(bodyTable);
        }
    }

    /*private void bodyVariablesOldTable(ExpressionNode body, VariableTable variableTable, ArrayList<VariableTable> initialTables, FieldTable fields, VariableTable bodyTable){
        initialTables.add(variableTable);
        body.stmtList.list.forEach((n)->stmtVariables(n, bodyTable, initialTables, fields));
        initialTables.remove(initialTables.size()-1);
        if(bodyTable.size()>0){
            variableTables.add(bodyTable);
        }
    }*/

    private void stmtVariables(StatementNode stmt, VariableTable variableTable, ArrayList<VariableTable> initialTables, FieldTable fields){
        if(stmt.type == StatementType.LET){
            letVariables(stmt.letStmt, variableTable, initialTables, fields);
        }
        else if (stmt.type == StatementType.EXPRESSION){
            exprVariables(stmt.expr, variableTable, initialTables, fields);
        }
    }

    private void exprVariables(ExpressionNode expression, VariableTable variableTable, ArrayList<VariableTable> initialTables, FieldTable fields){
        if(expression==null){
            return;
        }
        switch (expression.type) {
            case IF -> ifVariables(expression, variableTable, initialTables, fields);
            case LOOP -> loopVariables(expression, variableTable, initialTables, fields);
            case LOOP_FOR -> loopForVariables(expression, variableTable, initialTables, fields);
            case LOOP_WHILE -> loopWhileVariables(expression, variableTable, initialTables, fields);
            case ID -> idVariables(expression, variableTable, initialTables, fields);
            case PLUS, MINUS, DIV, MUL, EQUAL, NOT_EQUAL, GREATER, LESS, GREATER_EQUAL, LESS_EQUAL, OR, AND, ASGN, RANGE, RANGE_IN, INDEX, ARRAY_AUTO_FILL -> {
                exprVariables(expression.exprLeft, variableTable, initialTables, fields);
                exprVariables(expression.exprRight, variableTable, initialTables, fields);
            }
            case RANGE_LEFT, RANGE_RIGHT, RANGE_IN_RIGHT, QT, U_MINUS, NEG, STRUCT_FIELD, BREAK, RETURN ->
                    exprVariables(expression.exprLeft, variableTable, initialTables, fields);
            case ARRAY, STRUCT -> exprListVariables(expression.exprList, variableTable, initialTables, fields);
            case CALL -> methodVariables(expression, variableTable, initialTables, fields);
            case METHOD -> classMethodVariables(expression, variableTable, initialTables, fields);
            case STATIC_METHOD -> classStaticMethodVariables(expression, variableTable, initialTables, fields);
            case FIELD_ACCESS -> fieldAccessVariables(expression, variableTable, initialTables, fields);
        }
    }

    private void classMethodVariables(ExpressionNode expression, VariableTable variableTable, ArrayList<VariableTable> initialTables, FieldTable fields){

        exprVariables(expression.exprLeft, variableTable, initialTables, fields);
        expression.exprLeft.defineTypeOfExpr();
        ClassTable classTable = tables.tableByName(expression.exprLeft.countedType.name);
        if(classTable!=null){
            expression.setVar(classTable.getMethod(expression.name));
        }
        exprListVariables(expression.exprList, variableTable, initialTables, fields);
    }

    private void classStaticMethodVariables(ExpressionNode expression, VariableTable variableTable, ArrayList<VariableTable> initialTables, FieldTable fields){

        ClassTable classTable = tables.tableByName(expression.parentId);
        if(classTable==null){
            throw new IllegalArgumentException("Не существует класса " + expression.parentId + ". ID: " + expression.id);
        }
        expression.setVar(classTable.getMethod(expression.name));

        exprListVariables(expression.exprList, variableTable, initialTables, fields);
    }

    private void methodVariables(ExpressionNode expression, VariableTable variableTable, ArrayList<VariableTable> initialTables, FieldTable fields){
        expression.setVar(getMethod(expression.name));
        exprListVariables(expression.exprList, variableTable, initialTables, fields);
    }

    private void fieldAccessVariables(ExpressionNode expression, VariableTable variableTable, ArrayList<VariableTable> initialTables, FieldTable fields){

        exprVariables(expression.exprLeft, variableTable, initialTables, fields);
        expression.exprLeft.defineTypeOfExpr();
        if(expression.exprLeft.countedType.varType!=VarType.ID){
            throw new IllegalArgumentException("Доступ к полю возможен только у идентификатора. ID: " + expression.exprLeft.id);
        }
        ClassTable classTable = tables.tableByName(expression.exprLeft.countedType.name);
        expression.setVar(classTable.getField(expression.name));
    }

    private void exprListVariables(ExpressionListNode exprList, VariableTable variableTable, ArrayList<VariableTable> initialTables, FieldTable fields){
        if (exprList == null) {
            return;
        }
        exprList.list.forEach((expr)->{
            exprVariables(expr, variableTable, initialTables, fields);
        });
    }

    private void idVariables(ExpressionNode ident, VariableTable variableTable, ArrayList<VariableTable> initialTables, FieldTable fields){

        //проверить переменную в локальной таблице
        VariableTable.VariableTableItem varItem = variableTable.getLast(ident.name);
        if(varItem!=null){
            ident.setVar(varItem);
            return;
        }

        //проверить переменную в таблицах верхнего уровня
        for (VariableTable item : initialTables) {
            varItem = item.getLast(ident.name);
            if(varItem!=null){
                ident.setVar(varItem);
                return;
            }
        }

        //проверить переменную в таблице полей
        if(fields!=null && fields.contains(ident.name)){
            ident.setVar(fields.get(ident.name));
            return;
        }

        throw new IllegalArgumentException("Необъявленная переменная " + ident.name);
    }

    private void ifVariables(ExpressionNode ifNode, VariableTable variableTable, ArrayList<VariableTable> initialTables, FieldTable fields){
        bodyVariables(ifNode.body, variableTable, initialTables, fields);
        if(ifNode.elseBody!=null){
            bodyVariables(ifNode.elseBody, variableTable, initialTables, fields);
        }
    }

    private void loopVariables(ExpressionNode loop, VariableTable variableTable, ArrayList<VariableTable> initialTables, FieldTable fields){
        bodyVariables(loop.body, variableTable, initialTables, fields);
    }

    private void loopForVariables(ExpressionNode loopFor, VariableTable variableTable, ArrayList<VariableTable> initialTables, FieldTable fields){
        ExpressionType type = loopFor.exprLeft.type;
        if(type!= ExpressionType.RANGE && type!=ExpressionType.RANGE_IN && type!=ExpressionType.RANGE_RIGHT
                && type!=ExpressionType.RANGE_IN_RIGHT && type!=ExpressionType.RANGE_LEFT && type!=ExpressionType.ID){
            throw new IllegalArgumentException("Неверное RANGE выражение в цикле for. ID узла: " + loopFor.id);
        }
        variableTable.add(loopFor.name, Mutable.MUT, new TypeNode(VarType.INT));
        bodyVariables(loopFor.body, variableTable, initialTables, fields);
    }

    private void loopWhileVariables(ExpressionNode loopWhile, VariableTable variableTable, ArrayList<VariableTable> initialTables, FieldTable fields){
        exprVariables(loopWhile.exprLeft, variableTable, initialTables, fields);
        bodyVariables(loopWhile.body, variableTable, initialTables, fields);
    }

    private void letVariables(LetStatementNode let, VariableTable variableTable, ArrayList<VariableTable> initialTables, FieldTable fields){
        int num = variableTable.add(let.name, let.mut, let.type);
        let.setVar(variableTable.getByID(num));

        exprVariables(let.expr, variableTable, initialTables, fields);
    }

    public record MethodTableItem(TypeNode returnType, VariableTable variableTable, boolean hasBody, FunctionType functionType, FunctionParamListNode params) {
    }
}
