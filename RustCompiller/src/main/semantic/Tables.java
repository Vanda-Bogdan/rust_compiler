package main.semantic;

import main.nodes.conststmt.ConstStatementNode;
import main.nodes.declstmt.DeclarationStatementNode;
import main.nodes.declstmt.DeclarationStatementType;
import main.nodes.enumm.EnumNode;
import main.nodes.function.FunctionNode;
import main.nodes.impl.ImplNode;
import main.nodes.stmt.StatementListNode;
import main.nodes.stmt.StatementNode;
import main.nodes.stmt.StatementType;
import main.nodes.struct.StructNode;
import main.nodes.trait.AssociatedItemNode;
import main.treeprint.Tree;

import java.io.IOException;
import java.util.HashMap;
import java.util.concurrent.atomic.AtomicInteger;

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
                enumClasses(declStmt.enumItem);
            }

            case CONST_STMT -> {
                constStmtClasses(declStmt.constStmtItem);
            }

            case FUNCTION -> {
                functionClasses(declStmt.functionItem);
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
                currentTable.addToFieldTable(structItem);
            }else {
                throw new IllegalArgumentException("Поле" + structItem.name + " структуры " + structNode.name + " уже определено");
            }
        });
    }

    private void implClasses(ImplNode impl){

        ClassTable struct = tableByName(impl.typeNode.name);

        if(struct==null){
            throw new IllegalArgumentException("Не существует структуры " + impl.typeNode.name);
        }

        switch (impl.implType){
            case TRAIT -> {
                //----------------------Методы--------------------------
                TraitTable.TraitItem trait = traitTable.traitByName(impl.name);
                if(trait==null){
                    throw new IllegalArgumentException("Не существует trait " + impl.name);
                }

                AtomicInteger traitPrototypes = new AtomicInteger();
                int implRealizations = 0;
                if(impl.associatedItemList!=null){
                    implRealizations = (int) impl.associatedItemList.list.stream().filter(item -> item.fun.body != null).count();
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
                            traitPrototypes.getAndIncrement();

                            //Добавить метод в таблицу констант данной структуры
                            int name = struct.constantAdd(Constant.UTF8, func.name);
                            int type = struct.constantAdd(Constant.UTF8, func.returnType.getNameForTable());
                            int N_T = struct.constantAdd(Constant.NAME_AND_TYPE, name, type);
                            int class_ = struct.getConstNumber(Constant.CLASS, struct.name);
                            struct.constantAdd(Constant.METHOD_REF, class_, N_T);

                            //Добавить метод в таблицу методов данной структуры
                            struct.addToMethodTable(trait.trait().getFunction(func.name));
                        } else {
                            throw new IllegalArgumentException("Отсутствует реализация в impl " + impl.name + " for " + impl.implType + "для функции " + funcName);
                        }
                    }
                    //если есть реализация, проверить что ее нет в impl и классе
                    else {
                        FunctionNode func = impl.hasBody(funcName);
                        if(func==null){
                            //func = impl.getFunction(funcName);
                            //Добавить метод в таблицу констант данной структуры
                            int name = struct.constantAdd(Constant.UTF8, funcName);
                            int type = struct.constantAdd(Constant.UTF8, value.returnType());
                            int N_T = struct.constantAdd(Constant.NAME_AND_TYPE, name, type);
                            int class_ = struct.getConstNumber(Constant.CLASS, struct.name);
                            struct.constantAdd(Constant.METHOD_REF, class_, N_T);

                            //Добавить метод в таблицу методов данной структуры
                            struct.addToMethodTable(trait.trait().getFunction(funcName));
                        }else {
                            throw new IllegalArgumentException("Метод " + funcName + " реализованный в trait переопределяется в impl");
                        }
                    }
                });
                if(traitPrototypes.get()!=implRealizations){
                    throw new IllegalArgumentException("Impl " + impl.name + " for " + impl.typeNode.getName() + " реализует лишние методы");
                }

                //----------------------Константы--------------------------
                AtomicInteger traitVarPrototypes = new AtomicInteger();
                int implVarRealizations = 0;
                if(impl.associatedItemList!=null){
                    implVarRealizations = (int) impl.associatedItemList.list.stream().filter(item -> item.constStmt != null).count();
                }

                trait.fields().items.forEach((fieldName, value) -> {
                    //Если константа не инициализирована, то найти в impl
                    if(value.expr()==null){
                        traitVarPrototypes.getAndIncrement();
                        ConstStatementNode const_ = impl.hasInitialization(fieldName, value.type());
                        if(const_!=null){
                            //Перезаписать константу
                            FieldTable.FieldTableItem field = trait.fields().items.get(const_.name);
                            trait.fields().items.put(const_.name, new FieldTable.FieldTableItem(field.type(), field.isConst(), const_.expr));

                        }else {
                            throw new IllegalArgumentException("Отсутствует реализация в impl " + impl.name + " for " + impl.implType + "для поля " + fieldName);
                        }
                    }
                });

                if(traitVarPrototypes.get()!=implVarRealizations){
                    throw new IllegalArgumentException("Impl " + impl.name + " for " + impl.implType + " реализует лишние константы");
                }
            }
            case INHERENT -> {
                for (AssociatedItemNode item : impl.associatedItemList.list) {
                    //Добавление методов
                    if (item.fun != null) {
                        if (struct.containsMethod(item.fun.name)) {
                            throw new IllegalArgumentException("Метод " + item.fun.name + " уже имеется в " + struct.name);
                        }
                        //Добавить метод в таблицу констант данной структуры
                        int name = struct.constantAdd(Constant.UTF8, item.fun.name);
                        int type = struct.constantAdd(Constant.UTF8, item.fun.returnType.getNameForTable());
                        int N_T = struct.constantAdd(Constant.NAME_AND_TYPE, name, type);
                        int class_ = struct.getConstNumber(Constant.CLASS, struct.name);
                        struct.constantAdd(Constant.METHOD_REF, class_, N_T);

                        //Добавить метод в таблицу методов данной структуры
                        struct.addToMethodTable(item.fun);
                    }
                    //Добавление констант
                    if(item.constStmt!=null){
                        if (struct.containsField(item.constStmt.name)) {
                            throw new IllegalArgumentException("Поле " + item.constStmt.name + " уже имеется в " + struct.name);
                        }
                        //Добавить поле в таблицу констант данной структуры
                        int name = struct.constantAdd(Constant.UTF8, item.constStmt.name);
                        int type = struct.constantAdd(Constant.UTF8, item.constStmt.type.getNameForTable());
                        int N_T = struct.constantAdd(Constant.NAME_AND_TYPE, name, type);
                        int class_ = struct.getConstNumber(Constant.CLASS, struct.name);
                        struct.constantAdd(Constant.FIELD_REF, class_, N_T);

                        //Добавить метод в таблицу методов данной структуры
                        struct.addToFieldTable(item.constStmt);
                    }
                }
            }
        }   
    }

    private void constStmtClasses(ConstStatementNode node) {
        // Проверка, что нет поля с таким же именем
        ClassTable main = tables.get("Main");
        if (main.containsField(node.name)) {
            throw new IllegalArgumentException("Поле с именем " + node.name + " уже существует в классе Main");
        }

        // Добавление поля в класс
        int name = main.constantAdd(Constant.UTF8, node.name);
        int type = main.constantAdd(Constant.UTF8, node.type.getNameForTable());
        int nameAndType = main.constantAdd(Constant.NAME_AND_TYPE, name, type);
        int class_ = main.getConstNumber(Constant.CLASS, main.name);
        main.constantAdd(Constant.FIELD_REF, class_, nameAndType);

        // Добавить поле в таблицу полей класса
        main.addToFieldTable(node);
    }

    private void functionClasses(FunctionNode function){
        // Проверка, что нет функции с таким же именем
        ClassTable main = tables.get("Main");
        if (main.containsMethod(function.name)) {
            throw new IllegalArgumentException("Метод с именем " + function.name + " уже существует в классе Main");
        }

        //Добавить метод в таблицу констант данной структуры
        int name = main.constantAdd(Constant.UTF8, function.name);
        int type = main.constantAdd(Constant.UTF8, function.returnType.getNameForTable());
        int N_T = main.constantAdd(Constant.NAME_AND_TYPE, name, type);
        int class_ = main.getConstNumber(Constant.CLASS, main.name);
        main.constantAdd(Constant.METHOD_REF, class_, N_T);

        //Добавить метод в таблицу методов данной структуры
        main.addToMethodTable(function);
    }

    private void enumClasses(EnumNode node) {
        // Создание таблицы класса и занесение имени enum
        createTable(node.name);
        int className = currentTable.constantAdd(Constant.UTF8, currentTable.name);
        currentTable.constantAdd(Constant.CLASS, className);

        // Обход элементов enum
        node.enumList.list.forEach(
                (item) -> {
                    // Добавление поля в класс
                    int name = currentTable.constantAdd(Constant.UTF8, item.name);
                    int type = currentTable.constantAdd(Constant.UTF8, node.name);
                    int nameAndType = currentTable.constantAdd(Constant.NAME_AND_TYPE, name, type);
                    int class_ = currentTable.getConstNumber(Constant.CLASS, currentTable.name);
                    currentTable.constantAdd(Constant.FIELD_REF, class_, nameAndType);

                    // Добавить поле в таблицу полей класса
                    currentTable.addToFieldTable(item, node.name);
                }
        );
    }

    public void outputTablesToFiles() {
        tables.values().forEach(
                (item) -> {
                    try {
                        item.outputToFile();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
        );
    }
}
