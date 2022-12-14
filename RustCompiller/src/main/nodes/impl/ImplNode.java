package main.nodes.impl;

import main.nodes.function.FunctionNode;
import main.nodes.trait.AssociatedItemListNode;
import main.nodes.TypeNode;
import main.nodes.trait.AssociatedItemNode;

import java.util.Objects;

public class ImplNode {
    public int id;
    public String name;
    public ImplType implType;
    public TypeNode typeNode;
    public AssociatedItemListNode associatedItemList;

    public FunctionNode hasBody(String name){

        for (AssociatedItemNode item : associatedItemList.list){
            if(item.fun!=null && Objects.equals(item.fun.name, name) && item.fun.body!=null){
                return item.fun;
            }
        }
        return null;
    }

    public FunctionNode getFunction(String name){
        for (AssociatedItemNode item : associatedItemList.list){
            if(item.fun!=null && Objects.equals(item.fun.name, name)){
                return item.fun;
            }
        }
        return null;
    }
}
