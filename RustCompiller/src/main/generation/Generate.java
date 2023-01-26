package main.generation;

import main.generation.utils.Utils;
import main.nodes.expression.ExpressionNode;
import main.nodes.function.FunctionNode;
import main.nodes.function.FunctionType;
import main.nodes.stmt.StatementNode;
import main.semantic.ClassTable;
import main.semantic.Constant;
import main.semantic.ConstantTable;
import main.semantic.Tables;
import main.treeprint.Tree;

import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class Generate {

    public void generate(Tree tree) throws IOException {
        Tables tables = tree.tables;
        ClassTable classTable = tables.tableByName("Main");

        String mainName = "Main.class";


        File mainClass = new File(mainName);
        FileWriter myWriter = new FileWriter(mainClass);
        myWriter.write("");
        FileOutputStream fos = new FileOutputStream(mainName);


        // CAFEBABE
        fos.write(new byte[] { (byte)0xCA, (byte)0xFE, (byte)0xBA, (byte)0xBE });

        // Version
        fos.write(new byte[] { 0x00, 0x00, 0x00, 0x32 });

        // Generate class
        ArrayList<byte[]> codGen = generateClass(classTable);

        // Constants count
        fos.write(Utils.intTo2ByteArray(classTable.constantTable.items.size() + 1));

        // Constants
        classTable.constantTable.constantTableToByteArray().forEach( (item) -> {
            try {
                fos.write(item);
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        // Code generation write to file
        codGen.forEach( (item) -> {
            try {
                fos.write(item);
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        fos.close();
    }

    private void generateFunction(FunctionNode function){

    }

    private byte[] generate(StatementNode stmt, ClassTable classTable){

        return null;
    }

    private ArrayList<byte[]> generateClass(ClassTable classTable) {
        ArrayList<byte[]> result = new ArrayList<>();

        // Flags (PUBLIC + SUPER)
        result.add(new byte[] { 0x00, 0x21 });

        // Current class
        result.add(Utils.intTo2ByteArray(classTable.constantTable.addClass(classTable.name)+ 1));

        // Parent class
        result.add(Utils.intTo2ByteArray(classTable.constantTable.addClass("java/lang/Object") + 1));

        // Interfaces
        result.add(new byte[] { 0x00, 0x00 });

        // Fields count
        result.add(Utils.intTo2ByteArray(classTable.fields().items.size()));

        // Fields table
        classTable.fields().items.forEach((key, item) -> {
            // Flags access fields
            if (item.isConst()) {
                result.add(new byte[] { 0x00, 0x09});
            }
            else {
                result.add(new byte[] { 0x00, 0x00 });
            }

            // Name
            result.add(Utils.intTo2ByteArray(classTable.constantTable.getConstNumber(Constant.UTF8, key) + 1));

            // Descriptor
            result.add(Utils.intTo2ByteArray(classTable.constantTable.getConstNumber(Constant.UTF8, item.type().getConstNameForTable()) + 1));

            // Field attributes count
            result.add(new byte[] { 0x00, 0x00 });

        });

        // Methods count
        result.add(Utils.intTo2ByteArray(classTable.methods().items.size()));

        // Methods table
        // ------------------ Program constructor --------------

        // Flags (PUBLIC)
        result.add(new byte[] { 0x00, 0x01 });

        // Name
        result.add(Utils.intTo2ByteArray(classTable.constantTable.add(Constant.UTF8, "<init>") + 1));

        // Descriptor
        result.add(Utils.intTo2ByteArray(classTable.constantTable.add(Constant.UTF8, "()V") + 1));

        // Method attrs count (always 1)
        result.add(new byte[] { 0x00, 0x01 });

        // Code attr
        // Name
        result.add(Utils.intTo2ByteArray(classTable.constantTable.add(Constant.UTF8, "Code") + 1));

        // Length
        result.add(new byte[] { 0x00, 0x00, 0x00, 0x11 });

        // Stack size (max)
        result.add(new byte[] { (byte)0xFF, (byte)0xFF });

        // Locals count (this)
        result.add(new byte[] { 0x00, 0x01 });

        // Bytecode length
        result.add(new byte[] { 0x00, 0x00, 0x00, 0x05 });

        // Bytecode (Object constructor call)
        result.add(Utils.intTo1ByteArray(0x2A)); // aload_0
        result.add(Utils.intTo1ByteArray(0xB7)); // invokespecial
        result.add(Utils.intTo2ByteArray(classTable.constantTable.addMethodRef(classTable.name, "<init>", "()V"))); // MethodRef Obj Init
        result.add(Utils.intTo1ByteArray(0xB1)); // return
        // Exceptions table length (always 0)
        result.add(new byte[] { 0x00, 0x00 });

        // Code attrs count (always 0)
        result.add(new byte[] { 0x00, 0x00 });

        // Class attrs count
        result.add(new byte[] { 0x00, 0x00 });

        //------------------------------------Methods-----------------------------------
        classTable.methods().items.forEach((key, value) -> {
            // Flags
            if (value.functionType() == FunctionType.ASSOCIATED) {
                result.add(new byte[] { 0x00, 0x09 });
            }
            else {
                result.add(new byte[] { 0x00, 0x01 });
            }

            // Name
            result.add(Utils.intTo2ByteArray(classTable.constantTable.add(Constant.UTF8, key) + 1));

            // Descriptor
            result.add(Utils.intTo2ByteArray(classTable.constantTable.add(Constant.UTF8, ConstantTable.funcTypeForTable(value.returnType(), value.params())) + 1));

            // Codegen
            ArrayList<byte[]> code = new ArrayList<>();
            code.add(Utils.intTo1ByteArray(0xB1));

            // Method attrs count (always 1)
            result.add(new byte[] { 0x00, 0x01 });

            // Code attr
            // Name
            result.add(Utils.intTo2ByteArray(classTable.constantTable.add(Constant.UTF8, "Code") + 1));

            // Length
            result.add(new byte[] { 0x00, 0x00, 0x00, 0x0D });

            // Stack size (max)
            result.add(new byte[] { (byte)0xFF, (byte)0xFF });

            // Locals count (this)
            result.add(new byte[] { 0x00, 0x01 });

            // Bytecode length
            result.add(new byte[] { 0x00, 0x00, 0x00, 0x01 });

            // Тут добавлять код к результату
            result.addAll(code);

            // Exceptions table length (always 0)
            result.add(new byte[] { 0x00, 0x00 });

            // Code attrs count (always 0)
            result.add(new byte[] { 0x00, 0x00 });

            // Class attrs count
            result.add(new byte[] { 0x00, 0x00 });

        });

        return result;
    }

    private ArrayList<byte[]> generate(ExpressionNode expr, ClassTable classTable){
        ArrayList<byte[]> bytes = new ArrayList<>();
        switch (expr.type){

        }

        return null;
    }


}
