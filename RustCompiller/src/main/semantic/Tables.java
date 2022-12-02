package main.semantic;

import main.nodes.ProgramNode;

import java.util.ArrayList;

public class Tables {

    public ArrayList<Table> tables = new ArrayList<>();

    public void create(ProgramNode root) {
        int idTable = 0;
        int idTableItem = 0;

        Table mainClass = new Table("Main");



    }



    private boolean searchByName(String name) {
        for (Table element : tables) {
            if (element.name == name) {
                return true;
            }
        }
        return false;
    }
}
