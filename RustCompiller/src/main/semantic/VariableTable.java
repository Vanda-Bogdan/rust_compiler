package main.semantic;

import main.nodes.Mutable;

import java.util.ArrayList;
import java.util.Objects;

public class VariableTable {

    private final String UNDEFINED = "undefined";

    public ArrayList<VariableTableItem> items = new ArrayList<>();

    public void add(String name, Mutable isMut, String type) {
        if(contains(name)){
            return;
        }
        items.add(new VariableTableItem(name, isMut, type));
    }

    public void add(String name, Mutable isMut) {
        if(contains(name)){
            return;
        }
        items.add(new VariableTableItem(name, isMut, UNDEFINED));
    }

    public boolean contains(String name) {
        return items.contains(new VariableTableItem(name, Mutable.NOT_MUT, ""));
    }

    public int getVarNumber(String name) {
        return items.indexOf(new VariableTableItem(name, Mutable.NOT_MUT, ""));
    }

    public void overwrite(String name, Mutable isMut, String type) {
        items.set(getVarNumber(name), new VariableTableItem(name, isMut, type));
    }

    public void merge(VariableTable other){
        other.items.forEach((item)-> add(item.name(), item.isMut(), item.type()));
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
