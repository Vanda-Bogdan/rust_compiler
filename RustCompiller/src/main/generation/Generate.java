package main.generation;

import com.sun.tools.jconsole.JConsoleContext;
import main.generation.constants.Command;
import main.generation.utils.Utils;
import main.nodes.expression.ExpressionNode;
import main.nodes.function.FunctionNode;
import main.nodes.function.FunctionType;
import main.nodes.stmt.StatementNode;
import main.semantic.*;
import main.treeprint.Tree;

import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Generate {

    public void generate(Tree tree) throws IOException {
        Tables tables = tree.tables;
        ClassTable mainTable = tables.tableByName("Main");

        String mainName = "Main.class";

        ByteArrayOutputStream out = new ByteArrayOutputStream();
        DataOutputStream dout = new DataOutputStream(out);
        dout.writeInt(0xCAFEBABE); //"magic"
        dout.writeShort(0); // минорная версия
        dout.writeShort(50); // мажорная версия

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
            dout.writeShort(classTable.constantTable.add(Constant.UTF8, ConstantTable.funcTypeForTable(methodTableItem.returnType(), methodTableItem.params())) + 1);

            // Codegen
            ByteArrayOutputStream out2 = new ByteArrayOutputStream();
            DataOutputStream dout2 = new DataOutputStream(out2);
            dout2.write(Command.ldc_w.commandCode);
            dout2.writeShort(classTable.constantAdd(Constant.STRING, classTable.constantAdd(Constant.UTF8, "Hello world!!!")) + 1);
            dout2.write(Command.invokestatic.commandCode);
            dout2.writeShort(classTable.constantTable.addMethodRef("RTL", "println", "(Ljava/lang/Object;)V") + 1);
            dout2.write(Command.return_.commandCode);

            // Method attrs count (always 1)
            dout.writeShort(1);

            // Code attr
            // Name
            dout.writeShort(classTable.constantTable.add(Constant.UTF8, "Code") + 1);

            // Length
            dout.writeInt(out2.size() + 12);

            // Stack size (max)
            dout.writeShort(0xFF);

            // Locals count (this)
            dout.writeShort(methodTableItem.variableTable().size());

            // Bytecode length
            dout.writeInt(out2.size());

            // Тут добавлять код к результату
            dout.write(out2.toByteArray());

            // Exceptions table length (always 0)
            dout.writeShort(0);

            // Code attrs count (always 0)
            dout.writeShort(0);

        }

        // Class attrs count
        dout.writeShort(0);

        return out.toByteArray();
    }

    private ArrayList<byte[]> generate(ExpressionNode expr, ClassTable classTable){
        ArrayList<byte[]> bytes = new ArrayList<>();
        switch (expr.type){

        }

        return null;
    }


}
