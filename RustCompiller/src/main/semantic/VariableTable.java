package main.semantic;

import main.nodes.Mutable;

import java.util.*;

public class VariableTable {

    private int ID = 0;
    private ArrayList <VariableTableItem> items = new ArrayList<>();

    public int size(){
        return items.size();
    }

    public int add(String name, Mutable isMut, String type) {
        items.add(new VariableTableItem(ID, name, isMut, type));
        return ID++;
    }

    public int add(String name, Mutable isMut) {
        items.add(new VariableTableItem(ID, name, isMut, "undefined"));
        return ID++;
    }

    public VariableTableItem getLast(String name, Mutable isMut, String type){
        for (int i = items.size()-1; i>=0; i--){
            VariableTableItem item = items.get(i);
            if(Objects.equals(item.name(), name) && item.isMut()==isMut && Objects.equals(item.type, type)){
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

    public record VariableTableItem(int ID, String name, Mutable isMut, String type) {
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
