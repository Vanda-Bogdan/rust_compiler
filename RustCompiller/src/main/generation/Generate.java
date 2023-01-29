package main.generation;

import com.sun.tools.jconsole.JConsoleContext;
import main.generation.constants.CodeOfDefaultsTypes;
import main.generation.constants.Command;
import main.generation.utils.Utils;
import main.nodes.VarType;
import main.nodes.expression.ExpressionNode;
import main.nodes.function.FunctionNode;
import main.nodes.function.FunctionType;
import main.nodes.letstmt.LetStatementNode;
import main.nodes.stmt.StatementNode;
import main.semantic.*;
import main.treeprint.Tree;

import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

public class Generate {

    public void generate(Tree tree) throws IOException {
        Tables tables = tree.tables;
        ClassTable mainTable = tables.tableByName("Main");

        String mainName = "Main.class";

        ByteArrayOutputStream out = new ByteArrayOutputStream();
        DataOutputStream dout = new DataOutputStream(out);
        dout.writeInt(0xCAFEBABE); //"magic"
        dout.writeShort(0); // минорная версия
        dout.writeShort(60); // мажорная версия

        // Generate class
        byte[] codGen = generateClass(mainTable);

        // Constants count
        dout.writeShort(mainTable.constantTable.items.size() + 1);

        // Constants
        dout.write(mainTable.constantTable.constantTableToByteArray());

        // Code generation write to file
        dout.write(codGen);

        try(OutputStream outputStream = new FileOutputStream(mainName)) {
            out.writeTo(outputStream);
        }
    }

    private void generateFunction(FunctionNode function){

    }

    private byte[] generate(StatementNode stmt, ClassTable classTable){

        return null;
    }

    private byte[] generateClass(ClassTable classTable) throws IOException {
        //ArrayList<byte[]> result = new ArrayList<>();
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        DataOutputStream dout = new DataOutputStream(out);

        // Flags (PUBLIC + SUPER)
        dout.writeShort(0x0001 | 0x0020);

        // Current class
        dout.writeShort(classTable.constantTable.addClass(classTable.name) + 1);

        // Parent class
        dout.writeShort(classTable.constantTable.addClass("java/lang/Object") + 1);

        // Interfaces
        dout.writeShort(0);

        // Fields count
        dout.writeShort(0);


        // Fields table
        for(Map.Entry<String, FieldTable.FieldTableItem> entry : classTable.fields().items.entrySet()) {
            String fieldName = entry.getKey();
            FieldTable.FieldTableItem fieldTableItem = entry.getValue();

            // Flags access fields
            if (fieldTableItem.isConst()) {
                dout.writeShort(9);
            }
            else {
                dout.writeShort(1);
            }

            // Name
            dout.writeShort(classTable.constantTable.add(Constant.UTF8, fieldName) + 1);

            // Descriptor
            dout.writeShort(classTable.constantTable.add(Constant.UTF8, fieldTableItem.type().getConstNameForTable()) + 1);

            // Field attributes count
            dout.writeShort(0);
        }

        // Methods count
        dout.writeShort(classTable.methods().items.size());

        //------------------------------------Methods-----------------------------------
        for(Map.Entry<String, MethodTable.MethodTableItem> entry : classTable.methods().items.entrySet()){
            String methodName = entry.getKey();
            MethodTable.MethodTableItem methodTableItem = entry.getValue();

            // Flags
            if (methodTableItem.functionType() == FunctionType.ASSOCIATED) {
                dout.writeShort(9);
            }
            else {
                dout.writeShort(1);
            }

            // Name
            dout.writeShort(classTable.constantTable.add(Constant.UTF8, methodName) + 1);

            // Descriptor
            if(Objects.equals(classTable.name, "Main") && Objects.equals(methodName, "main")){
                dout.writeShort(classTable.constantTable.add(Constant.UTF8, "([Ljava/lang/String;)V") + 1);
            }else {
                dout.writeShort(classTable.constantTable.add(Constant.UTF8, methodTableItem.funcTypeForTable()) + 1);
            }

            // Codegen
            byte[] codeGen = generateFunction(methodTableItem.body(), classTable);

            // Method attrs count (always 1)
            dout.writeShort(1);

            // Code attr
            // Name
            dout.writeShort(classTable.constantTable.add(Constant.UTF8, "Code") + 1);

            // Length
            dout.writeInt(codeGen.length + 12);

            // Stack size (max)
            dout.writeShort(0xFF);

            // Locals count (this)
            dout.writeShort(methodTableItem.variableTable().size()+1);

            // Bytecode length
            dout.writeInt(codeGen.length);

            // Тут добавлять код к результату
            dout.write(codeGen);

            // Exceptions table length (always 0)
            dout.writeShort(0);

            // Code attrs count (always 0)
            dout.writeShort(0);

        }

        // Class attrs count
        dout.writeShort(0);

        return out.toByteArray();
    }

    private byte[] generateFunction(ExpressionNode body, ClassTable classTable) throws IOException {
        ByteArrayOutputStream codeGenOut = new ByteArrayOutputStream();
        DataOutputStream codeGen = new DataOutputStream(codeGenOut);

        if(body.stmtList!=null){
            for (StatementNode stmt : body.stmtList.list){
                codeGen.write(generateStmt(stmt, classTable));
            }
        }

        codeGen.write(Command.return_.commandCode);
        return codeGenOut.toByteArray();
    }

    private byte[] generateExpr(ExpressionNode expr, ClassTable classTable) throws IOException {

        ByteArrayOutputStream codeGenOut = new ByteArrayOutputStream();
        DataOutputStream codeGen = new DataOutputStream(codeGenOut);

        switch (expr.type){
            case CALL -> {
                MethodTable.MethodTableItem methodTableItem = expr.methodTableItem();
                if(expr.isRTLMethod){
                    switch (expr.name){
                        case "println" ->{
                            codeGen.write(generateExpr(expr.exprList.list.get(0), classTable));
                            codeGen.write(Command.invokestatic.commandCode);
                            codeGen.writeShort(classTable.constantTable.addMethodRef("RTL", "println", "(Ljava/lang/Object;)V") + 1);
                        }
                        case "println_i32" -> {
                            if (expr.exprList.list.get(0).string == null) {
                                throw new IllegalArgumentException("Ожидался string literal");
                            }
                            codeGen.write(Command.ldc_w.commandCode);
                            codeGen.writeShort(classTable.constantAddString(expr.exprList.list.get(0).string) + 1);
                            codeGen.write(generateExpr(expr.exprList.list.get(1), classTable));
                            codeGen.write(Command.invokestatic.commandCode);
                            codeGen.writeShort(classTable.constantTable.addMethodRef("RTL", "println_i32", "(Ljava/lang/String;I)V") + 1);
                        }
                        case "println_f64" -> {
                            if (expr.exprList.list.get(0).string == null) {
                                throw new IllegalArgumentException("Ожидался string literal");
                            }
                            codeGen.write(Command.ldc_w.commandCode);
                            codeGen.writeShort(classTable.constantAddString(expr.exprList.list.get(0).string) + 1);
                            codeGen.write(generateExpr(expr.exprList.list.get(1), classTable));
                            codeGen.write(Command.invokestatic.commandCode);
                            codeGen.writeShort(classTable.constantTable.addMethodRef("RTL", "println_f64", "(Ljava/lang/String;F)V") + 1);
                        }
                        case "println_char" -> {
                            if (expr.exprList.list.get(0).string == null) {
                                throw new IllegalArgumentException("Ожидался string literal");
                            }
                            codeGen.write(Command.ldc_w.commandCode);
                            codeGen.writeShort(classTable.constantAddString(expr.exprList.list.get(0).string) + 1);
                            codeGen.write(generateExpr(expr.exprList.list.get(1), classTable));
                            codeGen.write(Command.invokestatic.commandCode);
                            codeGen.writeShort(classTable.constantTable.addMethodRef("RTL", "println_char", "(Ljava/lang/String;Ljava/lang/String;)V") + 1);
                        }
                        case "println_bool" -> {
                            if (expr.exprList.list.get(0).string == null) {
                                throw new IllegalArgumentException("Ожидался string literal");
                            }
                            codeGen.write(Command.ldc_w.commandCode);
                            codeGen.writeShort(classTable.constantAddString(expr.exprList.list.get(0).string) + 1);
                            codeGen.write(generateExpr(expr.exprList.list.get(1), classTable));
                            codeGen.write(Command.invokestatic.commandCode);
                            codeGen.writeShort(classTable.constantTable.addMethodRef("RTL", "println_bool", "(Ljava/lang/String;I)V") + 1);
                        }
                        case "readln" -> {
                            codeGen.write(Command.invokestatic.commandCode);
                            codeGen.writeShort(classTable.constantTable.addMethodRef("RTL", "readln", "()Ljava/lang/String;") + 1);
                        }
                        case "readln_i32" -> {
                            codeGen.write(Command.invokestatic.commandCode);
                            codeGen.writeShort(classTable.constantTable.addMethodRef("RTL", "readln_i32", "()I") + 1);
                        }
                        case "readln_f64" -> {
                            codeGen.write(Command.invokestatic.commandCode);
                            codeGen.writeShort(classTable.constantTable.addMethodRef("RTL", "readln_f64", "()F") + 1);
                        }
                    }
                }
                else {
                    for (ExpressionNode item : expr.exprList.list) {
                        codeGen.write(generateExpr(item, classTable));
                    }
                    codeGen.write(Command.invokestatic.commandCode);
                    codeGen.writeShort(classTable.constantAddMethodRef(classTable.name, expr.methodName, expr.methodTableItem().funcTypeForTable()) + 1);
                }
            }
            case STATIC_METHOD -> {

            }
            case PLUS -> {
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(generateExpr(expr.exprRight, classTable));
                if (expr.countedType.varType == VarType.INT) {
                    codeGen.write(Command.iadd.commandCode);
                } else if (expr.countedType.varType == VarType.FLOAT) {
                    codeGen.write(Command.fadd.commandCode);
                }
            }
            case MINUS -> {
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(generateExpr(expr.exprRight, classTable));
                if (expr.countedType.varType == VarType.INT) {
                    codeGen.write(Command.isub.commandCode);
                } else if (expr.countedType.varType == VarType.FLOAT) {
                    codeGen.write(Command.fsub.commandCode);
                }
            }
            case MUL -> {
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(generateExpr(expr.exprRight, classTable));
                if (expr.countedType.varType == VarType.INT) {
                    codeGen.write(Command.imul.commandCode);
                } else if (expr.countedType.varType == VarType.FLOAT) {
                    codeGen.write(Command.fmul.commandCode);
                }
            }
            case DIV -> {
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(generateExpr(expr.exprRight, classTable));
                if (expr.countedType.varType == VarType.INT) {
                    codeGen.write(Command.idiv.commandCode);
                } else if (expr.countedType.varType == VarType.FLOAT) {
                    codeGen.write(Command.fdiv.commandCode);
                }
            }
            case EQUAL -> {
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(generateExpr(expr.exprRight, classTable));
                switch (expr.exprLeft.countedType.varType) {
                    case INT, BOOL -> {
                        codeGen.write(Command.if_icmpne.commandCode);
                        codeGen.writeShort(7);
                        codeGen.write(Command.iconst_1.commandCode);
                        codeGen.write(Command.goto_.commandCode);
                        codeGen.writeShort(4);
                        codeGen.write(Command.iconst_0.commandCode);
                    }
                    case FLOAT -> {
                        codeGen.write(Command.fcmpg.commandCode);
                        codeGen.write(Command.ifne.commandCode);
                        codeGen.writeShort(7);
                        codeGen.write(Command.iconst_1.commandCode);
                        codeGen.write(Command.goto_.commandCode);
                        codeGen.writeShort(4);
                        codeGen.write(Command.iconst_0.commandCode);
                    }
                    case CHAR, STRING -> {
                        codeGen.write(Command.iconst_0.commandCode);
                        codeGen.write(Command.invokestatic.commandCode);
                        codeGen.writeShort(classTable.constantAddMethodRef("RTL", "stringEqual", "(Ljava/lang/String;Ljava/lang/String;I)I") + 1);
                    }
                }
            }
            case NOT_EQUAL -> {
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(generateExpr(expr.exprRight, classTable));
                switch (expr.exprLeft.countedType.varType) {
                    case INT, BOOL -> {
                        codeGen.write(Command.if_icmpeq.commandCode);
                        codeGen.writeShort(7);
                        codeGen.write(Command.iconst_1.commandCode);
                        codeGen.write(Command.goto_.commandCode);
                        codeGen.writeShort(4);
                        codeGen.write(Command.iconst_0.commandCode);
                    }
                    case FLOAT -> {
                        codeGen.write(Command.fcmpg.commandCode);
                        codeGen.write(Command.ifeq.commandCode);
                        codeGen.writeShort(7);
                        codeGen.write(Command.iconst_1.commandCode);
                        codeGen.write(Command.goto_.commandCode);
                        codeGen.writeShort(4);
                        codeGen.write(Command.iconst_0.commandCode);
                    }
                    case CHAR, STRING -> {
                        codeGen.write(Command.iconst_1.commandCode);
                        codeGen.write(Command.invokestatic.commandCode);
                        codeGen.writeShort(classTable.constantAddMethodRef("RTL", "stringEqual", "(Ljava/lang/String;Ljava/lang/String;I)I") + 1);
                    }
                }
            }
            case GREATER -> {
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(generateExpr(expr.exprRight, classTable));
                switch (expr.exprLeft.countedType.varType) {
                    case INT, BOOL -> {
                        codeGen.write(Command.if_icmple.commandCode);
                        codeGen.writeShort(7);
                        codeGen.write(Command.iconst_1.commandCode);
                        codeGen.write(Command.goto_.commandCode);
                        codeGen.writeShort(4);
                        codeGen.write(Command.iconst_0.commandCode);
                    }
                    case FLOAT -> {
                        codeGen.write(Command.fcmpg.commandCode);
                        codeGen.write(Command.ifle.commandCode);
                        codeGen.writeShort(7);
                        codeGen.write(Command.iconst_1.commandCode);
                        codeGen.write(Command.goto_.commandCode);
                        codeGen.writeShort(4);
                        codeGen.write(Command.iconst_0.commandCode);
                    }
                    case CHAR, STRING -> {
                        codeGen.write(Command.iconst_2.commandCode);
                        codeGen.write(Command.invokestatic.commandCode);
                        codeGen.writeShort(classTable.constantAddMethodRef("RTL", "stringEqual", "(Ljava/lang/String;Ljava/lang/String;I)I") + 1);
                    }
                }
            }
            case LESS -> {
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(generateExpr(expr.exprRight, classTable));
                switch (expr.exprLeft.countedType.varType) {
                    case INT, BOOL -> {
                        codeGen.write(Command.if_icmpge.commandCode);
                        codeGen.writeShort(7);
                        codeGen.write(Command.iconst_1.commandCode);
                        codeGen.write(Command.goto_.commandCode);
                        codeGen.writeShort(4);
                        codeGen.write(Command.iconst_0.commandCode);
                    }
                    case FLOAT -> {
                        codeGen.write(Command.fcmpg.commandCode);
                        codeGen.write(Command.ifge.commandCode);
                        codeGen.writeShort(7);
                        codeGen.write(Command.iconst_1.commandCode);
                        codeGen.write(Command.goto_.commandCode);
                        codeGen.writeShort(4);
                        codeGen.write(Command.iconst_0.commandCode);
                    }
                    case CHAR, STRING -> {
                        codeGen.write(Command.iconst_3.commandCode);
                        codeGen.write(Command.invokestatic.commandCode);
                        codeGen.writeShort(classTable.constantAddMethodRef("RTL", "stringEqual", "(Ljava/lang/String;Ljava/lang/String;I)I") + 1);
                    }
                }
            }
            case GREATER_EQUAL -> {
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(generateExpr(expr.exprRight, classTable));
                switch (expr.exprLeft.countedType.varType) {
                    case INT, BOOL -> {
                        codeGen.write(Command.if_icmplt.commandCode);
                        codeGen.writeShort(7);
                        codeGen.write(Command.iconst_1.commandCode);
                        codeGen.write(Command.goto_.commandCode);
                        codeGen.writeShort(4);
                        codeGen.write(Command.iconst_0.commandCode);
                    }
                    case FLOAT -> {
                        codeGen.write(Command.fcmpg.commandCode);
                        codeGen.write(Command.iflt.commandCode);
                        codeGen.writeShort(7);
                        codeGen.write(Command.iconst_1.commandCode);
                        codeGen.write(Command.goto_.commandCode);
                        codeGen.writeShort(4);
                        codeGen.write(Command.iconst_0.commandCode);
                    }
                    case CHAR, STRING -> {
                        codeGen.write(Command.iconst_4.commandCode);
                        codeGen.write(Command.invokestatic.commandCode);
                        codeGen.writeShort(classTable.constantAddMethodRef("RTL", "stringEqual", "(Ljava/lang/String;Ljava/lang/String;I)I") + 1);
                    }
                }
            }
            case LESS_EQUAL -> {
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(generateExpr(expr.exprRight, classTable));
                switch (expr.exprLeft.countedType.varType) {
                    case INT, BOOL -> {
                        codeGen.write(Command.if_icmpgt.commandCode);
                        codeGen.writeShort(7);
                        codeGen.write(Command.iconst_1.commandCode);
                        codeGen.write(Command.goto_.commandCode);
                        codeGen.writeShort(4);
                        codeGen.write(Command.iconst_0.commandCode);
                    }
                    case FLOAT -> {
                        codeGen.write(Command.fcmpg.commandCode);
                        codeGen.write(Command.ifgt.commandCode);
                        codeGen.writeShort(7);
                        codeGen.write(Command.iconst_1.commandCode);
                        codeGen.write(Command.goto_.commandCode);
                        codeGen.writeShort(4);
                        codeGen.write(Command.iconst_0.commandCode);
                    }
                    case CHAR, STRING -> {
                        codeGen.write(Command.iconst_5.commandCode);
                        codeGen.write(Command.invokestatic.commandCode);
                        codeGen.writeShort(classTable.constantAddMethodRef("RTL", "stringEqual", "(Ljava/lang/String;Ljava/lang/String;I)I") + 1);
                    }
                }
            }
            case INT_LIT -> {
                codeGen.write(Command.ldc_w.commandCode);
                codeGen.writeShort(classTable.constantAdd(Constant.INTEGER, expr.anInt) + 1);
            }
            case FLOAT_LIT -> {
                codeGen.write(Command.ldc_w.commandCode);
                codeGen.writeShort(classTable.constantAdd(expr.aFloat) + 1);
            }
            case CHAR_LIT -> {
                codeGen.write(Command.ldc.commandCode);
                codeGen.write(classTable.constantAddString(String.valueOf(expr.aChar)) + 1);
            }
            case STRING_LIT -> {
                codeGen.write(Command.ldc_w.commandCode);
                codeGen.writeShort(classTable.constantAddString(expr.string) + 1);
            }
            case BOOL_LIT -> {
                if(expr.aBoolean) {
                    codeGen.write(Command.iconst_1.commandCode);
                }
                else {
                    codeGen.write(Command.iconst_0.commandCode);
                }
            }
            case ARRAY -> {
                codeGen.write(Command.new_.commandCode);
                codeGen.writeShort(classTable.constantAddClass("RTLArray") + 1);
                codeGen.write(Command.dup.commandCode);
                codeGen.write(Command.invokespecial.commandCode);
                codeGen.writeShort(classTable.constantAddMethodRef("RTLArray", "<init>", "()V") + 1);
                switch (expr.countedType.typeArr.varType) {
                    case INT -> {
                        for (ExpressionNode item : expr.exprList.list) {
                            codeGen.write(generateExpr(item, classTable));
                            codeGen.write(Command.invokevirtual.commandCode);
                            codeGen.writeShort(classTable.constantAddMethodRef("RTLArray", "initInt", "(I)LRTLArray;") + 1);
                        }
                    }
                    case FLOAT -> {
                        for (ExpressionNode item : expr.exprList.list) {
                            codeGen.write(generateExpr(item, classTable));
                            codeGen.write(Command.invokevirtual.commandCode);
                            codeGen.writeShort(classTable.constantAddMethodRef("RTLArray", "initFloat", "(F)LRTLArray;") + 1);
                        }
                    }
                    case STRING, ARRAY, CHAR -> {
                        for (ExpressionNode item : expr.exprList.list) {
                            codeGen.write(generateExpr(item, classTable));
                            codeGen.write(Command.invokevirtual.commandCode);
                            codeGen.writeShort(classTable.constantAddMethodRef("RTLArray", "initObject", "(Ljava/lang/Object;)LRTLArray;") + 1);
                        }
                    }
                }
            }
            case ID -> {
                if (expr.idType == ExpressionNode.IdType.LOCAL) {
                    switch (expr.countedType.varType) {
                        case VOID -> {
                        }
                        case INT, BOOL -> {
                            codeGen.write(Command.iload.commandCode);
                            codeGen.write(expr.variableTableItem().ID());
                        }
                        case CHAR, STRING, ARRAY -> {
                            codeGen.write(Command.aload.commandCode);
                            codeGen.write(expr.variableTableItem().ID());
                        }
                        case FLOAT -> {
                            codeGen.write(Command.fload.commandCode);
                            codeGen.write(expr.variableTableItem().ID());
                        }
                        case UNDEFINED -> throw new IllegalArgumentException("UNDEFINED тип у узла (ID: " + expr.id + ")");
                    }
                }
                else {
                    codeGen.write(Command.aload.commandCode);
                    // TODO поля класса, что сними блять делать?
                }
            }
            case ASGN -> {
                codeGen.write(generateExpr(expr.exprRight, classTable));

                switch (expr.exprRight.countedType.varType) {
                    case VOID -> {
                    }
                    case INT, BOOL -> codeGen.write(Command.istore.commandCode);
                    case CHAR, STRING, ARRAY -> codeGen.write(Command.astore.commandCode);
                    case FLOAT -> codeGen.write(Command.fstore.commandCode);
                    case ID -> {
                        //todo присвоение классу
                    }
                    case UNDEFINED -> throw new IllegalArgumentException("UNDEFINED тип у узла (ID: " + expr.exprRight.id + ")");
                }

                switch (expr.exprLeft.idType){
                    case LOCAL -> codeGen.write(expr.exprLeft.variableTableItem().ID());
                    case FIELD -> {
                        //todo putfield
                    }
                }
            }
            case INDEX -> {
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(generateExpr(expr.exprRight, classTable));
                codeGen.write(Command.invokevirtual.commandCode);
                switch (expr.exprLeft.countedType.typeArr.varType){
                    case INT -> {
                        codeGen.writeShort(classTable.constantAddMethodRef("RTLArray", "getInt", "(I)I") + 1);
                    }
                    case FLOAT -> {
                        codeGen.writeShort(classTable.constantAddMethodRef("RTLArray", "getFloat", "(I)F") + 1);
                    }
                    case STRING, CHAR -> {
                        codeGen.writeShort(classTable.constantAddMethodRef("RTLArray", "getObject", "(I)Ljava/lang/Object;") + 1);
                        codeGen.write(Command.checkcast.commandCode);
                        codeGen.writeShort(classTable.constantAddClass("java/lang/String") + 1);
                    }
                    case ARRAY -> {
                        codeGen.writeShort(classTable.constantAddMethodRef("RTLArray", "getObject", "(I)Ljava/lang/Object;") + 1);
                        codeGen.write(Command.checkcast.commandCode);
                        codeGen.writeShort(classTable.constantAddClass("RTLArray") + 1);
                    }
                    case UNDEFINED -> throw new IllegalArgumentException("UNDEFINED тип у узла (ID: " + expr.exprRight.id + ")");
                }
            }
            case INDEX_ASGN -> {
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(generateExpr(expr.body, classTable));
                codeGen.write(generateExpr(expr.exprRight, classTable));
                codeGen.write(Command.invokevirtual.commandCode);
                switch (expr.exprLeft.countedType.typeArr.varType){
                    case VOID -> {
                    }
                    case INT, BOOL -> {
                        codeGen.writeShort(classTable.constantAddMethodRef("RTLArray", "setInt", "(II)V") + 1);
                    }
                    case FLOAT -> {
                        codeGen.writeShort(classTable.constantAddMethodRef("RTLArray", "setFloat", "(IF)V") + 1);
                    }
                    case CHAR, STRING, ARRAY -> {
                        codeGen.writeShort(classTable.constantAddMethodRef("RTLArray", "setObject", "(ILjava/lang/Object;)V") + 1);
                    }
                    case UNDEFINED -> throw new IllegalArgumentException("UNDEFINED тип у узла (ID: " + expr.exprRight.id + ")");
                }
            }
        }

        return codeGenOut.toByteArray();
    }

    private byte[] generateStmt(StatementNode stmt, ClassTable classTable) throws IOException {
        ByteArrayOutputStream codeGenOut = new ByteArrayOutputStream();
        DataOutputStream codeGen = new DataOutputStream(codeGenOut);

        switch (stmt.type){
            case LET -> codeGen.write(generateLet(stmt.letStmt,classTable));
            case EXPRESSION -> codeGen.write(generateExpr(stmt.expr,classTable));
        }

        return codeGenOut.toByteArray();
    }

    private byte[] generateLet(LetStatementNode let, ClassTable classTable) throws IOException {
        ByteArrayOutputStream codeGenOut = new ByteArrayOutputStream();
        DataOutputStream codeGen = new DataOutputStream(codeGenOut);

        if (let.expr != null) {
            codeGen.write(generateExpr(let.expr, classTable));
            switch (let.expr.countedType.varType) {
                case VOID -> {
                }
                case INT, BOOL -> codeGen.write(Command.istore.commandCode);
                case CHAR, STRING, ARRAY -> codeGen.write(Command.astore.commandCode);
                case FLOAT -> codeGen.write(Command.fstore.commandCode);
                case ID -> {
                }
                case UNDEFINED -> throw new IllegalArgumentException("UNDEFINED тип у узла (ID: " + let.expr.exprRight.id + ")");
            }
            codeGen.write(let.variableTableItem().ID());
        }

        return codeGenOut.toByteArray();
    }
}
