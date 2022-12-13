package main;

import main.semantic.Tables;
import main.treeprint.Tree;
import treeCreate.TreeFromXml;

import java.io.IOException;

public class Main{

    private static int cd = 13;

    public static void main (String args[]) throws IOException {

        Tree tree = TreeFromXml.buildTree();
        Tables tables = new Tables();
        tables.createTables(tree);

        //tree.print();

    }


}
