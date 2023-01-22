package main.semantic;

import main.nodes.Mutable;
import main.nodes.TypeNode;
import main.nodes.VarType;

import java.util.*;

public class VariableTable {

    private int ID = 0;
    private ArrayList <VariableTableItem> items = new ArrayList<>();

    public int size(){
        return items.size();
    }

    public int add(String name, Mutable isMut, TypeNode type) {
        items.add(new VariableTableItem(ID, name, isMut, type));
        return ID++;
    }

    public int add(String name, Mutable isMut) {
        items.add(new VariableTableItem(ID, name, isMut, new TypeNode(VarType.UNDEFINED)));
        return ID++;
    }

    public void resetType(int ID, TypeNode newType){
        int num = 0;
        for (VariableTableItem item :items) {
            if(item.ID() == ID){
                items.set(num, new VariableTableItem(item.ID(), item.name(), item.isMut(), newType));
                //item = new VariableTableItem(item.ID(), item.name(), item.isMut(), newType);
                return;
            }
            num++;
        }
    }

    public VariableTableItem getLast(String name){
        for (int i = items.size()-1; i>=0; i--){
            VariableTableItem item = items.get(i);
            if(Objects.equals(item.name(), name)){
                return item;
            }
        }
        return null;
    }

    public VariableTableItem getByID(int ID){
        for (int i = items.size()-1; i>=0; i--){
            VariableTableItem item = items.get(i);
            if(item.ID == ID){
                return item;
            }
        }
        return null;
    }

    public void merge(VariableTable other){
        for (VariableTableItem item: other.items) {
            add(item.name(), item.isMut(), item.type());
        }
    }

    public record VariableTableItem(int ID, String name, Mutable isMut, TypeNode type) {
        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            VariableTableItem that = (VariableTableItem) o;
            return name.equals(that.name);
        }

        @Override
        public int hashCode() {
            return Objects.hash(name);
        }
    }
}
