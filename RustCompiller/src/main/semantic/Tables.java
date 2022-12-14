package main.semantic;

import main.nodes.ProgramNode;
import main.nodes.TypeNode;
import main.nodes.declstmt.DeclarationStatementNode;
import main.nodes.declstmt.DeclarationStatementType;
import main.nodes.function.FunctionNode;
import main.nodes.impl.ImplNode;
import main.nodes.letstmt.LetStatementNode;
import main.nodes.stmt.StatementListNode;
import main.nodes.stmt.StatementNode;
import main.nodes.stmt.StatementType;
import main.nodes.struct.StructListNode;
import main.nodes.struct.StructNode;
import main.nodes.trait.TraitNode;
import main.treeprint.Tree;

import java.util.ArrayList;
import java.util.HashMap;

public class Tables {

    private ClassTable currentTable = null;

    private HashMap<String, ClassTable> tables = new HashMap<String, ClassTable>();

    private TraitTable traitTable = new TraitTable();

    public ClassTable tableByName(String name){
        return tables.get(name);
    }

    private ClassTable createTable(String name) {
        if(tables.containsKey(name)){
            throw new IllegalArgumentException("Класс" + name + " уже существует");
        }
        ClassTable table = new ClassTable(name);
        tables.put(name, table);
        currentTable = table;
        return table;
    }

    public void createTables(Tree tree) {

        createTable("Main");
        stmtListTrait(tree.prg.stmtList);
        stmtListClasses(tree.prg.stmtList);
    }

    //----------------------------------------Сбор всех трейтов-----------------------------------------
    private void stmtListTrait(StatementListNode stmtList){
        stmtList.list.forEach(this::stmtTrait);
    }

    private void stmtTrait(StatementNode stmt) {
        if (stmt.type == StatementType.DECLARATION) {
            declStmtTrait(stmt.declarationStmt);
        }
    }

    private void declStmtTrait(DeclarationStatementNode declStmt){
        if (declStmt.type == DeclarationStatementType.TRAIT) {
            traitTable.add(declStmt.traitItem);
        }
    }


    //-----------------------------------------Обход дерева---------------------------------------------
    private void stmtListClasses(StatementListNode stmtList) {
        stmtList.list.forEach(this::stmtClasses);
    }

    private void stmtClasses(StatementNode stmt) {
        if (stmt.type == StatementType.DECLARATION) {
            declStmtClasses(stmt.declarationStmt);
        }
    }

    private void declStmtClasses(DeclarationStatementNode declStmt){
        switch (declStmt.type) {
            case STRUCT -> {
                structClasses(declStmt.structItem);
            }

            case IMPL -> {
                implClasses(declStmt.implItem);
            }

            case ENUM -> {
                //todo enum
            }

            case CONST_STMT -> {
                //todo const
            }
        }
    }

    private void structClasses(StructNode structNode){

        createTable(structNode.name);

        currentTable.constantAdd(Constant.UTF8, "Code");
        int className = currentTable.constantAdd(Constant.UTF8, structNode.name);
        int classConst = currentTable.constantAdd(Constant.CLASS, className);
        structNode.structList.list.forEach((structItem)->{
            if(!currentTable.constantContains(Constant.UTF8, structItem.name)){
                //Заполнение таблицы констант
                int name = currentTable.constantAdd(Constant.UTF8, structItem.name);                  //имя
                int type = currentTable.constantAdd(Constant.UTF8, structItem.type.getNameForTable());//тип
                int N_T = currentTable.constantAdd(Constant.NAME_AND_TYPE, name, type);               //Name&Type
                currentTable.constantAdd(Constant.FIELD_REF, classConst, N_T);                        //FieldRef

                //Заполнение таблицы полей
                currentTable.fieldsAdd(structItem);
            }else {
                throw new IllegalArgumentException("Поле" + structItem.name + " структуры " + structNode.name + " уже определено");
            }
        });
    }

    private void implClasses(ImplNode impl){

        ClassTable struct = tableByName(impl.typeNode.name);
        if(struct==null){
            throw new IllegalArgumentException("Не существует структуры" + impl.typeNode.name);
        }

        switch (impl.implType){
            case TRAIT -> {
                TraitTable.TraitItem trait = traitTable.traitByName(impl.name);
                if(trait==null){
                    throw new IllegalArgumentException("Не существует трейта" + impl.name);
                }

                trait.methods().items.forEach((funcName, value) -> {
                    //заполнение методов в таблицу констант структуры

                    //Проверить что метода еще нет в структуре
                    if (struct.containsMethod(funcName)) {
                        throw new IllegalArgumentException("Метод " + funcName + " уже реализован для структуры " + struct.name);
                    }

                    //если нет реализации, найти ее в impl
                    if (!value.hasBody()) {
                        FunctionNode func = impl.hasBody(funcName);
                        if (func != null) {
                            //Добавить метод в таблицу констант данной структуры
                            int name = struct.constantAdd(Constant.UTF8, func.name);
                            int type = struct.constantAdd(Constant.UTF8, func.returnType.getNameForTable());
                            int N_T = struct.constantAdd(Constant.NAME_AND_TYPE, name, type);
                            int class_ = struct.getConstNumber(Constant.CLASS, struct.name);
                            struct.constantAdd(Constant.METHOD_REF, class_, N_T);

                            //Добавить метод в таблицу методов данной структуры
                            struct.addToMethodTable(func);
                        } else {
                            throw new IllegalArgumentException("Отсутствует реализация в impl для функции " + funcName);
                        }
                    }
                    //если есть реализация, проверить что ее нет в impl и классе
                    else {
                        FunctionNode func = impl.hasBody(funcName);
                        if(func==null){
                            func = impl.getFunction(funcName);
                            //Добавить метод в таблицу констант данной структуры
                            int name = struct.constantAdd(Constant.UTF8, func.name);
                            int type = struct.constantAdd(Constant.UTF8, func.returnType.getNameForTable());
                            int N_T = struct.constantAdd(Constant.NAME_AND_TYPE, name, type);
                            int class_ = struct.getConstNumber(Constant.CLASS, struct.name);
                            struct.constantAdd(Constant.METHOD_REF, class_, N_T);

                            //Добавить метод в таблицу методов данной структуры
                            struct.addToMethodTable(func);
                        }else {
                            throw new IllegalArgumentException("Метод " + funcName + " реализованный в трейте переопределяется в impl");
                        }
                    }
                });

            }

            case INHERENT -> {

            }
        }
    }


    private static String typeParse(TypeNode type) {
        switch (type.varType) {
            case INT -> {
                return "I";
            }
            case CHAR -> {
                return "C";
            }
            case STRING -> {
                return "S";
            }
            case FLOAT -> {
                return "F";
            }
            case BOOL -> {
                return "B";
            }
            case ID -> {
                return type.name;
            }
            case ARRAY -> {
                TypeNode tArr = type.typeArr;
                while (tArr.typeArr != null) {
                    tArr = tArr.typeArr;
                }
                return typeParse(tArr);
            }
            default -> {
                return null;
            }
        }
    }
}
