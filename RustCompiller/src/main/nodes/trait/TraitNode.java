package main.nodes.trait;

import main.nodes.function.FunctionNode;

import java.util.Objects;

public class TraitNode {
    public int id;
    public String name;
    public AssociatedItemListNode associatedItemList;

    public FunctionNode getFunction(String name){
        if(associatedItemList==null){
            return null;
        }
        for (AssociatedItemNode item : associatedItemList.list){
            if(item.fun!=null && Objects.equals(item.fun.name, name)){
                return item.fun;
            }
        }
        return null;
    }
}
