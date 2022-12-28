package main.semantic;

import main.nodes.Mutable;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

public class VariableTable {

    private int ID = 0;
    private HashMap<Integer, VariableTableItem> items = new HashMap<>();

    public VariableTableItem get(int num){
        return items.get(num);
    }

    public int getNum(String name){
        for (Map.Entry<Integer, VariableTableItem> entry : items.entrySet()){
            if(Objects.equals(entry.getValue().name, name)){
                return entry.getKey();
            }
        }
        return -1;
    }

    public int size(){
        return items.size();
    }

    public int add(String name, Mutable isMut, String type) {
        items.put(ID, new VariableTableItem(name, isMut, type));
        return ID++;
    }

    public int add(String name, Mutable isMut) {
        items.put(ID, new VariableTableItem(name, isMut, "undefined"));
        return ID++;
    }

    public boolean contains(String name) {
        return items.containsValue(new VariableTableItem(name, Mutable.NOT_MUT, ""));
    }

    /*public void overwrite(String name, Mutable isMut, String type) {
        items.set(getVarNumber(name), new VariableTableItem(name, isMut, type));
    }*/

    public void merge(VariableTable other){
        for(Map.Entry<Integer, VariableTableItem> entry : items.entrySet()){
            add(entry.getValue().name(), entry.getValue().isMut(), entry.getValue().type());
        }
    }

    public record VariableTableItem(String name, Mutable isMut, String type) {
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
