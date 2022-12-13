package main;

import main.semantic.Tables;
import main.treeprint.Tree;
import treeCreate.TreeFromXml;

import java.io.IOException;

public class Main{

    private static int cd = 13;

    public static void main (String args[]) throws IOException {

        //Tree tree = TreeFromXml.buildTree();
        //Tables tables = new Tables();
        //tables.createTables(tree);

        //tree.print();
        jopa();
        NoMain na = new NoMain();
        na.function();
    }

    public static int jopa(){
        return -9;
    }

    public static class NoMain{
        public int pole = -1;
        public int function(){
            return 18;
        }
    }

}
