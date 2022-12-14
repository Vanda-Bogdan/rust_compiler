package main.semantic;

import main.nodes.function.FunctionNode;
import main.nodes.trait.TraitNode;

import java.util.HashMap;

public class TraitTable {

    public HashMap<String, TraitItem> items = new HashMap<>();

    public void add(TraitNode traitNode) {
        MethodTable methods = new MethodTable();
        FieldTable fields = new FieldTable();
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
        items.put(traitNode.name, new TraitItem(methods, fields));
    }

    public record TraitItem(MethodTable methods, FieldTable fields) {
    }

}
