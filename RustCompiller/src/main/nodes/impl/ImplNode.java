package main.nodes.impl;

import main.nodes.conststmt.ConstStatementNode;
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

        if(associatedItemList==null){
            return null;
        }
        for (AssociatedItemNode item : associatedItemList.list){
            if(item.fun!=null && Objects.equals(item.fun.name, name) && item.fun.body!=null){
                return item.fun;
            }
        }
        return null;
    }

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

    public ConstStatementNode hasInitialization(String name, TypeNode type){

        if(associatedItemList==null){
            return null;
        }
        for (AssociatedItemNode item : associatedItemList.list){
            if(item.constStmt!=null && Objects.equals(item.constStmt.name, name) && item.constStmt.type.equals(type) && item.constStmt.expr!=null){
                return item.constStmt;
            }
        }
        return null;
    }

    public ConstStatementNode getConstVariable(String name){
        if(associatedItemList==null){
            return null;
        }
        for (AssociatedItemNode item : associatedItemList.list){
            if(item.constStmt!=null && Objects.equals(item.constStmt.name, name)){
                return item.constStmt;
            }
        }
        return null;
    }
}
