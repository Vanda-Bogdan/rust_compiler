package main.generation;

import main.generation.utils.Utils;
import main.nodes.expression.ExpressionNode;
import main.nodes.function.FunctionNode;
import main.nodes.stmt.StatementNode;
import main.semantic.ClassTable;
import main.semantic.Tables;
import main.treeprint.Tree;

import java.io.*;
import java.util.ArrayList;

public class Generate {

    public void generate(Tree tree) throws IOException {
        Tables tables = tree.tables;
        ClassTable classTable = tables.tableByName("main");

        String mainName = "main.class";


        File mainClass = new File(mainName);
        FileOutputStream fos = new FileOutputStream(mainName);

        fos.write(Utils.intTo2ByteArray(101));
        fos.write(Utils.intTo2ByteArray(102));
        fos.write(Utils.intTo2ByteArray(103));
    }

    private void generateFunction(FunctionNode function){

    }

    private byte[] generate(StatementNode stmt, ClassTable classTable){

        return null;
    }

    private ArrayList<byte[]> generate(ExpressionNode expr, ClassTable classTable){
        ArrayList<byte[]> bytes = new ArrayList<>();
        switch (expr.type){

        }

        return null;
    }
}
