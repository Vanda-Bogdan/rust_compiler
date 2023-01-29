package main;

import main.generation.Generate;
import main.treeprint.Tree;
import treeCreate.TreeFromXml;

import java.io.IOException;
import java.util.Scanner;

public class Main{

    public static void main (String args[]) throws IOException {

        Tree tree = TreeFromXml.buildTree();
        tree.transform();
        tree.print();
        tree.createTables();
        tree.typesCheck();
        Generate generation = new Generate();
        generation.generate(tree);


    }

}
