package main.generation;

import main.generation.constants.Command;
import main.generation.utils.Utils;
import main.nodes.VarType;
import main.nodes.expression.ExpressionNode;
import main.nodes.function.FunctionType;
import main.nodes.letstmt.LetStatementNode;
import main.nodes.stmt.StatementNode;
import main.semantic.ClassTable;
import main.semantic.Constant;
import main.semantic.FieldTable;
import main.semantic.MethodTable;
import main.treeprint.Tree;

import java.io.*;
import java.util.ArrayList;
import java.util.Map;
import java.util.Objects;

public class Generate {

    public Tree tree = null;

    public void generate(Tree tree) throws IOException {

        this.tree = tree;

        for (ClassTable item : this.tree.tables.tables.values()) {

            ByteArrayOutputStream out = new ByteArrayOutputStream();
            DataOutputStream dout = new DataOutputStream(out);
            dout.writeInt(0xCAFEBABE); //"magic"
            dout.writeShort(0); // минорная версия
            dout.writeShort(60); // мажорная версия

            // Generate class
            byte[] codGen = generateClass(item);

            // Constants count
            dout.writeShort(item.constantTable.items.size() + 1);

            // Constants
            dout.write(item.constantTable.constantTableToByteArray());

            // Code generation write to file
            dout.write(codGen);

            try (OutputStream outputStream = new FileOutputStream(item.name + ".class")) {
                out.writeTo(outputStream);
            }
        }
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
        dout.writeShort(classTable.fields().items.size());


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
            String a = fieldTableItem.type().getDescriptorForTable();
            dout.writeShort(classTable.constantTable.add(Constant.UTF8, fieldTableItem.type().getDescriptorForTable()) + 1);

            // Field attributes count
            dout.writeShort(0);
        }

        if (classTable.name != "Main") {
            // добавляем конструктор

            // Methods count
            dout.writeShort(classTable.methods().items.size() + 1);

            // Flag (Public)
            dout.writeShort(1);

            // Name
            dout.writeShort(classTable.constantAdd(Constant.UTF8, "<init>") + 1);

            // Descriptor
            dout.writeShort(classTable.constantAdd(Constant.UTF8, classTable.getConstructorDescriptor()) + 1);

            // Codegen
            ByteArrayOutputStream outConstructor = new ByteArrayOutputStream();
            DataOutputStream doutConstructor = new DataOutputStream(outConstructor);

            doutConstructor.write(Command.aload.commandCode);
            doutConstructor.write(0);
            doutConstructor.write(Command.invokespecial.commandCode);
            doutConstructor.writeShort(classTable.constantAddMethodRef("java/lang/Object", "<init>", "()V") + 1);
            int c = 1;
            for (Map.Entry<String, FieldTable.FieldTableItem> item : classTable.fields().items.entrySet()) {
                doutConstructor.write(Command.aload.commandCode);
                doutConstructor.write(0);
                switch (item.getValue().type().varType) {
                    case INT, BOOL -> doutConstructor.write(Command.iload.commandCode);
                    case FLOAT -> doutConstructor.write(Command.fload.commandCode);
                    case STRING, CHAR, ARRAY, ID -> doutConstructor.write(Command.aload.commandCode);
                }
                doutConstructor.write(c);
                doutConstructor.write(Command.putfield.commandCode);
                doutConstructor.writeShort(classTable.addFieldRef(classTable.name, item.getKey(), item.getValue().type().getDescriptorForTable()) + 1);
                c++;
            }
            doutConstructor.write(Command.return_.commandCode);

            // Method attrs count (always 1)
            dout.writeShort(1);

            // Code attr
            // Name
            dout.writeShort(classTable.constantTable.add(Constant.UTF8, "Code") + 1);

            // Length
            dout.writeInt(outConstructor.toByteArray().length + 12);

            // Stack size (max)
            dout.writeShort(0xFF);

            // Locals count (this)
            dout.writeShort(c);

            // Bytecode length
            dout.writeInt(outConstructor.toByteArray().length);

            // Тут добавлять код к результату
            dout.write(outConstructor.toByteArray());

            // Exceptions table length (always 0)
            dout.writeShort(0);

            // Code attrs count (always 0)
            dout.writeShort(0);
        }
        else {
            // Methods count
            dout.writeShort(classTable.methods().items.size());
        }

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
                        case "print" ->{
                            codeGen.write(generateExpr(expr.exprList.list.get(0), classTable));
                            codeGen.write(Command.invokestatic.commandCode);
                            codeGen.writeShort(classTable.constantTable.addMethodRef("RTL", "print", "(Ljava/lang/Object;)V") + 1);
                        }
                        case "print_i32" -> {
                            if (expr.exprList.list.get(0).string == null) {
                                throw new IllegalArgumentException("Ожидался string literal");
                            }
                            codeGen.write(Command.ldc_w.commandCode);
                            codeGen.writeShort(classTable.constantAddString(expr.exprList.list.get(0).string) + 1);
                            codeGen.write(generateExpr(expr.exprList.list.get(1), classTable));
                            codeGen.write(Command.invokestatic.commandCode);
                            codeGen.writeShort(classTable.constantTable.addMethodRef("RTL", "print_i32", "(Ljava/lang/String;I)V") + 1);
                        }
                        case "print_f64" -> {
                            if (expr.exprList.list.get(0).string == null) {
                                throw new IllegalArgumentException("Ожидался string literal");
                            }
                            codeGen.write(Command.ldc_w.commandCode);
                            codeGen.writeShort(classTable.constantAddString(expr.exprList.list.get(0).string) + 1);
                            codeGen.write(generateExpr(expr.exprList.list.get(1), classTable));
                            codeGen.write(Command.invokestatic.commandCode);
                            codeGen.writeShort(classTable.constantTable.addMethodRef("RTL", "print_f64", "(Ljava/lang/String;F)V") + 1);
                        }
                        case "print_char" -> {
                            if (expr.exprList.list.get(0).string == null) {
                                throw new IllegalArgumentException("Ожидался string literal");
                            }
                            codeGen.write(Command.ldc_w.commandCode);
                            codeGen.writeShort(classTable.constantAddString(expr.exprList.list.get(0).string) + 1);
                            codeGen.write(generateExpr(expr.exprList.list.get(1), classTable));
                            codeGen.write(Command.invokestatic.commandCode);
                            codeGen.writeShort(classTable.constantTable.addMethodRef("RTL", "print_char", "(Ljava/lang/String;Ljava/lang/String;)V") + 1);
                        }
                        case "print_bool" -> {
                            if (expr.exprList.list.get(0).string == null) {
                                throw new IllegalArgumentException("Ожидался string literal");
                            }
                            codeGen.write(Command.ldc_w.commandCode);
                            codeGen.writeShort(classTable.constantAddString(expr.exprList.list.get(0).string) + 1);
                            codeGen.write(generateExpr(expr.exprList.list.get(1), classTable));
                            codeGen.write(Command.invokestatic.commandCode);
                            codeGen.writeShort(classTable.constantTable.addMethodRef("RTL", "print_bool", "(Ljava/lang/String;I)V") + 1);
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
                    if(expr.exprList!=null){
                        for (ExpressionNode item : expr.exprList.list) {
                            codeGen.write(generateExpr(item, classTable));
                        }
                    }
                    codeGen.write(Command.invokestatic.commandCode);
                    codeGen.writeShort(classTable.constantAddMethodRef(classTable.name, expr.methodName, expr.methodTableItem().funcTypeForTable()) + 1);
                }
            }
            case STATIC_METHOD -> {
                if(expr.exprList!=null){
                    for(ExpressionNode param : expr.exprList.list){
                        codeGen.write(generateExpr(param, classTable));
                    }
                }
                codeGen.write(Command.invokestatic.commandCode);
                codeGen.writeShort(classTable.constantAddMethodRef(expr.parentId, expr.name, expr.methodTableItem().funcTypeForTable()) + 1);
            }
            case STRUCT -> {
                codeGen.write(Command.new_.commandCode);
                codeGen.writeShort(classTable.constantAddClass(expr.name) + 1);
                codeGen.write(Command.dup.commandCode);
                for (String item : tree.tables.tableByName(expr.name).getParamsForConstructor()) {
                    codeGen.write(generateExpr(expr.exprList.getStructFieldExprByName(item), classTable));
                }
                codeGen.write(Command.invokespecial.commandCode);
                codeGen.writeShort(classTable.constantAddMethodRef(expr.name, "<init>", tree.tables.tableByName(expr.name).getConstructorDescriptor()) + 1);
            }
            case FIELD_ACCESS -> {
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(Command.getfield.commandCode);
                codeGen.writeShort(classTable.addFieldRef(expr.className(), expr.name, expr.countedType.getDescriptorForTable()) + 1);
            }
            case FIELD_ASGN -> {
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(generateExpr(expr.exprRight, classTable));
                codeGen.write(Command.putfield.commandCode);
                codeGen.writeShort(classTable.addFieldRef(expr.body.className(), expr.body.name, expr.body.fieldTableItem().type().getDescriptorForTable()) + 1);
            }
            case METHOD -> {
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                if(expr.exprList!=null){
                    for(ExpressionNode param : expr.exprList.list){
                        codeGen.write(generateExpr(param, classTable));
                    }
                }
                codeGen.write(Command.invokevirtual.commandCode);
                codeGen.writeShort(classTable.constantAddMethodRef(expr.methodTable.className, expr.name, expr.methodTableItem().funcTypeForTable()) + 1);
            }
            case SELF -> {
                switch (expr.countedType.varType) {
                    case VOID -> {
                    }
                    case INT, BOOL -> {
                        codeGen.write(Command.iload.commandCode);
                        codeGen.write(0);
                    }
                    case CHAR, STRING, ARRAY, ID -> {
                        codeGen.write(Command.aload.commandCode);
                        codeGen.write(0);
                    }
                    case FLOAT -> {
                        codeGen.write(Command.fload.commandCode);
                        codeGen.write(0);
                    }
                    case UNDEFINED -> throw new IllegalArgumentException("UNDEFINED тип у узла (ID: " + expr.id + ")");
                }
            }
            case STRUCT_FIELD -> codeGen.write(generateExpr(expr.exprLeft, classTable));
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
            case OR -> {
                byte[] right = generateExpr(expr.exprRight, classTable);
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(Command.ifne.commandCode);
                codeGen.writeShort(right.length + 6);
                codeGen.write(right);
                codeGen.write(Command.ifeq.commandCode);
                codeGen.writeShort(7);
                codeGen.write(Command.iconst_1.commandCode);
                codeGen.write(Command.goto_.commandCode);
                codeGen.writeShort(4);
                codeGen.write(Command.iconst_0.commandCode);
            }
            case AND -> {
                byte[] right = generateExpr(expr.exprRight, classTable);
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(Command.ifeq.commandCode);
                codeGen.writeShort(right.length + 6);
                codeGen.write(right);
                codeGen.write(Command.ifne.commandCode);
                codeGen.writeShort(7);
                codeGen.write(Command.iconst_0.commandCode);
                codeGen.write(Command.goto_.commandCode);
                codeGen.writeShort(4);
                codeGen.write(Command.iconst_1.commandCode);
            }
            case NEG -> {
                codeGen.write(generateExpr(expr.exprLeft, classTable));
                codeGen.write(Command.iconst_1.commandCode);
                codeGen.write(Command.ixor.commandCode);
            }
            case U_MINUS -> {
                if (expr.exprLeft.countedType.varType == VarType.INT) {
                    codeGen.write(generateExpr(expr.exprLeft, classTable));
                    codeGen.write(Command.ineg.commandCode);
                } else if (expr.exprLeft.countedType.varType == VarType.FLOAT) {
                    codeGen.write(generateExpr(expr.exprLeft, classTable));
                    codeGen.write(Command.fneg.commandCode);
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
                if (expr.exprList != null) {
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
            }
            case ARRAY_AUTO_FILL -> {
                codeGen.write(Command.new_.commandCode);
                codeGen.writeShort(classTable.constantAddClass("RTLArray") + 1);
                codeGen.write(Command.dup.commandCode);
                codeGen.write(Command.invokespecial.commandCode);
                codeGen.writeShort(classTable.constantAddMethodRef("RTLArray", "<init>", "()V") + 1);
                switch (expr.countedType.typeArr.varType) {
                    case INT -> {
                        codeGen.write(generateExpr(expr.exprLeft, classTable));
                        codeGen.write(generateExpr(expr.exprRight, classTable));
                        codeGen.write(Command.invokevirtual.commandCode);
                        codeGen.writeShort(classTable.constantAddMethodRef("RTLArray", "intAutoFill", "(II)LRTLArray;") + 1);
                    }
                    case FLOAT -> {
                        codeGen.write(generateExpr(expr.exprLeft, classTable));
                        codeGen.write(generateExpr(expr.exprRight, classTable));
                        codeGen.write(Command.invokevirtual.commandCode);
                        codeGen.writeShort(classTable.constantAddMethodRef("RTLArray", "floatAutoFill", "(FI)LRTLArray;") + 1);
                    }
                    case STRING, ARRAY, CHAR -> {
                        codeGen.write(generateExpr(expr.exprLeft, classTable));
                        codeGen.write(generateExpr(expr.exprRight, classTable));
                        codeGen.write(Command.invokevirtual.commandCode);
                        codeGen.writeShort(classTable.constantAddMethodRef("RTLArray", "objectAutoFill", "(Ljava/lang/Object;I)LRTLArray;") + 1);
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
                        case CHAR, STRING, ARRAY, ID -> {
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
            case IF -> {
                if (expr.exprLeft != null) {
                    codeGen.write(generateExpr(expr.exprLeft, classTable));
                    codeGen.write(Command.ifeq.commandCode);
                    byte[] body = generateExpr(expr.body, classTable);
                    if (expr.elseBody != null) {
                        codeGen.writeShort(body.length + 6);
                    } else {
                        codeGen.writeShort(body.length + 3);
                    }
                    codeGen.write(body);
                }
                if (expr.elseBody != null) {
                    byte[] elseBody = generateExpr(expr.elseBody, classTable);
                    codeGen.write(Command.goto_.commandCode);
                    codeGen.writeShort(elseBody.length + 3);
                    codeGen.write(elseBody);
                }

            }
            case BLOCK -> {
                if (expr.stmtList != null) {
                    for (StatementNode item : expr.stmtList.list) {
                        codeGen.write(generateStmt(item, classTable));
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
            case RETURN -> {
                if (expr.exprLeft == null) {
                    codeGen.write(Command.return_.commandCode);
                } else {
                    codeGen.write(generateExpr(expr.exprLeft, classTable));
                    switch (expr.exprLeft.countedType.varType) {
                        case INT, BOOL -> codeGen.write(Command.ireturn.commandCode);
                        case FLOAT -> codeGen.write(Command.freturn.commandCode);
                        case STRING, CHAR, ARRAY, ID -> codeGen.write(Command.areturn.commandCode);
                    }
                }
            }
            case LOOP_FOR -> {
                ByteArrayOutputStream beforeIfOut = new ByteArrayOutputStream();
                DataOutputStream beforeIf = new DataOutputStream(beforeIfOut);

                ByteArrayOutputStream afterIfOut = new ByteArrayOutputStream();
                DataOutputStream afterIf = new DataOutputStream(afterIfOut);

                ByteArrayOutputStream finalOut = new ByteArrayOutputStream();
                DataOutputStream final_ = new DataOutputStream(finalOut);

                codeGen.write(generateExpr(expr.exprLeft.exprLeft, classTable));
                codeGen.write(Command.istore.commandCode);
                codeGen.write(expr.variableTableItem().ID());

                beforeIf.write(Command.iload.commandCode);
                beforeIf.write(expr.variableTableItem().ID());
                beforeIf.write(generateExpr(expr.exprLeft.exprRight, classTable));

                switch (expr.exprLeft.type){
                    case RANGE -> beforeIf.write(Command.if_icmpge.commandCode);
                    case RANGE_IN -> beforeIf.write(Command.if_icmpgt.commandCode);
                }

                byte[] cycleBody = generateExpr(expr.body, classTable);

                afterIf.write(Command.iinc.commandCode);
                afterIf.write(expr.variableTableItem().ID());
                afterIf.write(1);

                afterIf.write(Command.goto_.commandCode);
                int offerGoto = cycleBody.length + 9;
                int offerIf = cycleBody.length + 11;

                final_.write(beforeIfOut.toByteArray());
                final_.writeShort(offerGoto);
                final_.write(cycleBody);
                final_.write(afterIfOut.toByteArray());
                final_.writeShort(-offerIf);

                byte[] final__ = finalOut.toByteArray();

                for (int i = 1; i < final__.length - 1; i++) {
                    if(Utils.intFromByteArray(new byte[]{final__[i-1]}) == Command.goto_.commandCode){
                        int byte_ = Utils.intFromByteArray(new byte[]{final__[i], final__[i+1]});
                        if(byte_ == 0){//break
                            int toEnd = final__.length - i + 1;
                            byte[] toWrite = Utils.intTo2ByteArray(toEnd);
                            final__[i] = toWrite[0];
                            final__[i+1] = toWrite[1];
                        }
                        else if (byte_ == 1){//continue
                            int toInc = final__.length - i - 5;
                            byte[] toWrite = Utils.intTo2ByteArray(toInc);
                            final__[i] = toWrite[0];
                            final__[i+1] = toWrite[1];
                        }
                    }
                }

                codeGen.write(final__);
            }

            case LOOP_WHILE -> {
                ByteArrayOutputStream beforeBodyOut = new ByteArrayOutputStream();
                DataOutputStream beforeBody = new DataOutputStream(beforeBodyOut);

                ByteArrayOutputStream finalOut = new ByteArrayOutputStream();
                DataOutputStream final_ = new DataOutputStream(finalOut);

                beforeBody.write(generateExpr(expr.exprLeft, classTable));
                beforeBody.write(Command.ifeq.commandCode);

                byte[] body = generateExpr(expr.body, classTable);

                byte goto_ = (byte)(Command.goto_.commandCode);

                int toExpr = (beforeBodyOut.toByteArray().length + body.length + 2);
                int toEnd = (6 + body.length);

                final_.write(beforeBodyOut.toByteArray());
                final_.writeShort(toEnd);
                final_.write(body);
                final_.write(goto_);
                final_.writeShort(-toExpr);

                byte[] final__ = finalOut.toByteArray();

                for (int i = 1; i < final__.length - 1; i++) {
                    if(Utils.intFromByteArray(new byte[]{final__[i-1]}) == Command.goto_.commandCode){
                        int byte_ = Utils.intFromByteArray(new byte[]{final__[i], final__[i+1]});
                        if(byte_ == 0){//break
                            int toEndBreak = final__.length - i + 1;
                            byte[] toWrite = Utils.intTo2ByteArray(toEndBreak);
                            final__[i] = toWrite[0];
                            final__[i+1] = toWrite[1];
                        }
                        else if (byte_ == 1){//continue
                            int toInc = final__.length - i - 2;
                            byte[] toWrite = Utils.intTo2ByteArray(toInc);
                            final__[i] = toWrite[0];
                            final__[i+1] = toWrite[1];
                        }
                    }
                }

                codeGen.write(final__);
            }

            case LOOP -> {
                ByteArrayOutputStream bodyOut = new ByteArrayOutputStream();
                DataOutputStream body = new DataOutputStream(bodyOut);

                body.write(generateExpr(expr.body, classTable));

                byte[] body_ = bodyOut.toByteArray();

                for (int i = 1; i < body_.length - 1; i++) {
                    if(Utils.intFromByteArray(new byte[]{body_[i-1]}) == Command.goto_.commandCode){
                        int byte_ = Utils.intFromByteArray(new byte[]{body_[i], body_[i+1]});
                        if(byte_ == 0){//break
                            int toEnd = body_.length - i + 4;
                            byte[] toWrite = Utils.intTo2ByteArray(toEnd);
                            body_[i] = toWrite[0];
                            body_[i+1] = toWrite[1];
                        }
                        else if (byte_ == 1){//continue
                            int toStart = 1 - i;
                            byte[] toWrite = Utils.intTo2ByteArray(toStart);
                            body_[i] = toWrite[0];
                            body_[i+1] = toWrite[1];
                        }
                    }
                }

                codeGen.write(body_);
                codeGen.write(Command.goto_.commandCode);
                codeGen.writeShort(-body_.length);
            }

            case BREAK -> {
                if(expr.exprLeft!=null){
                    codeGen.write(generateExpr(expr.exprLeft, classTable));
                }
                codeGen.write(Command.goto_.commandCode);
                codeGen.writeShort(0);
            }
            case CONTINUE -> {
                codeGen.write(Command.goto_.commandCode);
                codeGen.writeShort(1);
            }
        }

        if(expr.isReturn){
            switch (expr.countedType.varType){
                case INT, BOOL -> codeGen.write(Command.ireturn.commandCode);
                case FLOAT -> codeGen.write(Command.freturn.commandCode);
                case STRING, CHAR, ARRAY, ID -> codeGen.write(Command.areturn.commandCode);
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
                case CHAR, STRING, ARRAY, ID -> codeGen.write(Command.astore.commandCode);
                case FLOAT -> codeGen.write(Command.fstore.commandCode);
                //case UNDEFINED -> throw new IllegalArgumentException("UNDEFINED тип у узла (ID: " + let.expr.exprRight.id + ")");
            }
            codeGen.write(let.variableTableItem().ID());
        }

        return codeGenOut.toByteArray();
    }
}
