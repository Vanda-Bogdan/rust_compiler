package main.generation;

import com.sun.tools.jconsole.JConsoleContext;
import main.generation.constants.Command;
import main.generation.utils.Utils;
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
                            codeGen.write(Command.ldc_w.commandCode);
                            codeGen.writeShort(classTable.constantAdd(Constant.STRING, classTable.constantAdd(Constant.UTF8, expr.exprList.list.get(0).string)) + 1);
                            codeGen.write(Command.invokestatic.commandCode);
                            codeGen.writeShort(classTable.constantTable.addMethodRef("RTL", "println", "(Ljava/lang/Object;)V") + 1);
                        }
                        case "println_i32" -> {
                            codeGen.write(Command.ldc_w.commandCode);
                            codeGen.writeShort(classTable.constantAdd(Constant.STRING, classTable.constantAdd(Constant.UTF8, expr.exprList.list.get(0).string)) + 1);
                            codeGen.write(generateExpr(expr.exprList.list.get(1), classTable));
                            codeGen.write(Command.invokestatic.commandCode);
                            codeGen.writeShort(classTable.constantTable.addMethodRef("RTL", "println_i32", "(Ljava/lang/String;I)V") + 1);
                        }
                        case "println_f64" -> {
                            codeGen.write(Command.ldc_w.commandCode);
                            codeGen.writeShort(classTable.constantAdd(Constant.STRING, classTable.constantAdd(Constant.UTF8, expr.exprList.list.get(0).string)) + 1);
                            codeGen.write(Command.ldc_w.commandCode);
                            codeGen.writeShort(classTable.constantAdd(expr.exprList.list.get(1).aFloat) + 1);
                            codeGen.write(Command.invokestatic.commandCode);
                            codeGen.writeShort(classTable.constantTable.addMethodRef("RTL", "println_f64", "(Ljava/lang/String;F)V") + 1);
                        }
                        case "readln" -> {
                        }
                        case "readln_i32" -> {
                        }
                        case "readln_f64" -> {
                        }
                    }
                }
                else {
                    codeGen.write(generateFunction(methodTableItem.body(), classTable));
                }
            }
            case INT_LIT -> {
                codeGen.write(Command.ldc_w.commandCode);
                codeGen.writeShort(classTable.constantAdd(Constant.INTEGER, expr.anInt) + 1);
            }
            case ID -> {
                if (expr.idType == ExpressionNode.IdType.LOCAL) {
                    codeGen.write(Command.iload.commandCode);
                    codeGen.write(expr.variableTableItem().ID());
                }
                else {
                    codeGen.write(Command.aload.commandCode);
                    // TODO поля класса, что сними блять делать
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
                case INT -> {
                    codeGen.write(Command.istore.commandCode);
                    codeGen.write(let.variableTableItem().ID());
                }
                case CHAR -> {
                }
                case STRING -> {
                }
                case FLOAT -> {
                }
                case BOOL -> {
                }
                case ID -> {
                }
                case ARRAY -> {
                }
                case UNDEFINED -> {
                }
            }
        }

        return codeGenOut.toByteArray();
    }


}
