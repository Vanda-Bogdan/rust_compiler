package main;

import main.semantic.Tables;
import main.treeprint.Tree;
import treeCreate.TreeFromXml;

import java.io.IOException;

public class Main{

    public static void main (String args[]) throws IOException {

        Tree tree = TreeFromXml.buildTree();
        tree.print();
        Tables tables = new Tables();
        tables.createTables(tree);
        tables.outputTablesToFiles();
        int a =  5;


    }



}
