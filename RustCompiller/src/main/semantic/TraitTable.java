package main.semantic;

import main.nodes.function.FunctionNode;
import main.nodes.trait.TraitNode;

import java.util.ArrayList;
import java.util.HashMap;

public class TraitTable {

    private HashMap<String, TraitItem> items = new HashMap<>();

    public TraitItem traitByName(String name){
        return items.get(name);
    }

    public void add(TraitNode traitNode) {
        ArrayList<FunctionNode> methods = new ArrayList<>();
        FieldTable fields = new FieldTable(null);
        traitNode.associatedItemList.list.forEach(
                (item) -> {
                    if (item.fun != null) {
                        methods.add(item.fun);
                    }
                    else if (item.constStmt != null) {
                        fields.add(item.constStmt);
                    }
                }
        );
        items.put(traitNode.name, new TraitItem(methods, fields, traitNode));
    }

    public record TraitItem(ArrayList<FunctionNode> methods, FieldTable fields, TraitNode trait) {
    }

}
