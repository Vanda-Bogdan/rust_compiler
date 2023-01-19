package treeCreate;

import main.nodes.*;
import main.nodes.conststmt.ConstStatementNode;
import main.nodes.declstmt.DeclarationStatementNode;
import main.nodes.declstmt.DeclarationStatementType;
import main.nodes.enumm.EnumItemNode;
import main.nodes.enumm.EnumListNode;
import main.nodes.enumm.EnumNode;
import main.nodes.expression.ExpressionListNode;
import main.nodes.expression.ExpressionNode;
import main.nodes.expression.ExpressionType;
import main.nodes.function.FunctionNode;
import main.nodes.function.FunctionParamListNode;
import main.nodes.function.FunctionParamNode;
import main.nodes.function.FunctionType;
import main.nodes.impl.ImplNode;
import main.nodes.impl.ImplType;
import main.nodes.letstmt.LetStatementNode;
import main.nodes.stmt.StatementListNode;
import main.nodes.stmt.StatementNode;
import main.nodes.stmt.StatementType;
import main.nodes.struct.StructItemNode;
import main.nodes.struct.StructListNode;
import main.nodes.struct.StructNode;
import main.nodes.trait.AssociatedItemListNode;
import main.nodes.trait.AssociatedItemNode;
import main.nodes.trait.TraitNode;
import main.treeprint.Tree;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.io.StringReader;

public class TreeFromXml {
    public static final String path = "treeXML.xml";

    public static Tree buildTree(){
        try {

            DocumentBuilder documentBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
            Document document = documentBuilder.parse(path);

            Node program = document.getDocumentElement();

            Tree tree = new Tree(programBuild(program));
            return tree;

        } catch (ParserConfigurationException ex) {
            ex.printStackTrace(System.out);
        } catch (SAXException ex) {
            ex.printStackTrace(System.out);
        } catch (IOException ex) {
            ex.printStackTrace(System.out);
        }

        return null;
    }

    public static ProgramNode programBuild(Node programXML){

        ProgramNode programNode = new ProgramNode();
        programNode.id = Integer.parseInt(((Element)programXML).getAttribute("ID"));
        programNode.stmtList = statementListBuild(programXML.getFirstChild());
        return programNode;
    }

    public static StatementListNode statementListBuild(Node stmtListXML){

        StatementListNode statementListNode = new StatementListNode();
        statementListNode.id = Integer.parseInt(((Element)stmtListXML).getAttribute("ID"));
        NodeList stmts = stmtListXML.getChildNodes();
        for (int i = 0; i < stmts.getLength(); i++) {
            statementListNode.list.add(statementBuild(stmts.item(i)));
        }

        return statementListNode;
    }

    public static StatementNode statementBuild(Node stmt){
        StatementNode statementNode = new StatementNode();
        statementNode.type = StatementType.valueOf(((Element)stmt).getAttribute("type"));
        statementNode.id = Integer.parseInt(((Element)stmt).getAttribute("ID"));

        switch (statementNode.type) {
            case DECLARATION -> statementNode.declarationStmt = declStmtBuild(stmt.getFirstChild());
            case LET -> statementNode.letStmt = letStmtBuild(stmt.getFirstChild());
            case EXPRESSION -> statementNode.expr = exprBuild(stmt.getFirstChild());
        }

        return statementNode;
    }

    public static DeclarationStatementNode declStmtBuild(Node declStmt){
        DeclarationStatementNode declarationStatementNode = new DeclarationStatementNode();
        declarationStatementNode.id = Integer.parseInt(((Element)declStmt).getAttribute("ID"));
        declarationStatementNode.type = DeclarationStatementType.valueOf(((Element)declStmt).getAttribute("type"));

        switch (declarationStatementNode.type){
            case ENUM -> declarationStatementNode.enumItem = enumBuild(declStmt.getFirstChild());
            case FUNCTION -> declarationStatementNode.functionItem = functionBuild(declStmt.getFirstChild());
            case CONST_STMT -> declarationStatementNode.constStmtItem = constStmtBuild(declStmt.getFirstChild());
            case STRUCT -> declarationStatementNode.structItem = structBuild(declStmt.getFirstChild());
            case TRAIT -> declarationStatementNode.traitItem = traitBuild(declStmt.getFirstChild());
            case IMPL -> declarationStatementNode.implItem = implBuild(declStmt.getFirstChild());
        }
        return declarationStatementNode;
    }

    public static EnumNode enumBuild(Node enum_){
        EnumNode enumNode = new EnumNode();
        enumNode.name = ((Element)enum_).getAttribute("ident");
        enumNode.id = Integer.parseInt(((Element)enum_).getAttribute("ID"));
        if(enum_.hasChildNodes()){
            enumNode.enumList = enumListBuild(enum_.getFirstChild());
        }
        return enumNode;
    }

    public static EnumListNode enumListBuild(Node enumList){
        EnumListNode enumListNode = new EnumListNode();
        enumListNode.id = Integer.parseInt(((Element)enumList).getAttribute("ID"));

        Node current = enumList.getFirstChild();
        while(current!=null){
            enumListNode.list.add(enumItemBuild(current));
            current = current.getNextSibling();
        }

        return enumListNode;
    }

    public static EnumItemNode enumItemBuild(Node enumItem){
        EnumItemNode enumItemNode = new EnumItemNode();
        enumItemNode.id = Integer.parseInt(((Element)enumItem).getAttribute("ID"));
        enumItemNode.name = ((Element)enumItem).getAttribute("ident");

        if(((Element)enumItem).getElementsByTagName("struct_items").getLength()>0){
            enumItemNode.structList = structListBuild(((Element)enumItem).getElementsByTagName("struct_items").item(0));
        }
        if(((Element)enumItem).getElementsByTagName("expr").getLength()>0){
            enumItemNode.expr = exprBuild(((Element)enumItem).getElementsByTagName("expr").item(0));
        }

        return enumItemNode;
    }

    public static FunctionNode functionBuild(Node function_){
        FunctionNode functionNode = new FunctionNode();
        functionNode.id = Integer.parseInt(((Element)function_).getAttribute("ID"));
        functionNode.name = ((Element)function_).getAttribute("ident");
        functionNode.returnType = typeBuild(((Element)function_).getElementsByTagName("type_node").item(0));

        if(((Element)function_).getElementsByTagName("func_params").getLength()>0){
            functionNode.paramList = functionParamsBuild(((Element)function_).getElementsByTagName("func_params").item(0));
        }
        if(((Element)function_).getElementsByTagName("expr").getLength()>0){
            functionNode.body = exprBuild(((Element)function_).getElementsByTagName("expr").item(0));
        }

        return functionNode;
    }

    public static FunctionParamListNode functionParamsBuild(Node params){
        FunctionParamListNode functionParamListNode = new FunctionParamListNode();
        functionParamListNode.id = Integer.parseInt(((Element)params).getAttribute("ID"));
        functionParamListNode.type = FunctionType.valueOf(((Element)params).getAttribute("type"));
        Node current = params.getFirstChild();
        while(current!=null){
            functionParamListNode.list.add(functionParamBuild(current));
            current = current.getNextSibling();
        }

        return functionParamListNode;
    }

    public static FunctionParamNode functionParamBuild(Node param){
        FunctionParamNode paramNode = new FunctionParamNode();
        paramNode.id = Integer.parseInt(((Element)param).getAttribute("ID"));
        paramNode.mut = Mutable.valueOf(((Element)param).getAttribute("mutability"));
        paramNode.name = ((Element)param).getAttribute("ident");
        paramNode.type = typeBuild(param.getFirstChild());

        return paramNode;
    }

    public static ConstStatementNode constStmtBuild(Node constStmt_){
        ConstStatementNode constStatementNode = new ConstStatementNode();
        constStatementNode.id = Integer.parseInt(((Element)constStmt_).getAttribute("ID"));
        constStatementNode.name = ((Element)constStmt_).getAttribute("ident");
        constStatementNode.type = typeBuild(((Element)constStmt_).getElementsByTagName("type_node").item(0));

        if(((Element)constStmt_).getElementsByTagName("expr").getLength()>0){
            constStatementNode.expr = exprBuild(((Element)constStmt_).getElementsByTagName("expr").item(0));
        }

        return constStatementNode;
    }

    public static StructNode structBuild(Node struct_){
        StructNode structNode = new StructNode();
        structNode.id = Integer.parseInt(((Element)struct_).getAttribute("ID"));
        structNode.name = ((Element)struct_).getAttribute("ident");

        if(struct_.hasChildNodes()){
            structNode.structList = structListBuild(struct_.getFirstChild());
        }

        return structNode;
    }

    public static StructListNode structListBuild(Node structList){
        StructListNode structListNode = new StructListNode();
        structListNode.id = Integer.parseInt(((Element)structList).getAttribute("ID"));
        Node current = structList.getFirstChild();
        while(current!=null){
            structListNode.list.add(structItemBuild(current));
            current = current.getNextSibling();
        }

        return structListNode;
    }

    public static StructItemNode structItemBuild(Node structItem){
        StructItemNode structItemNode = new StructItemNode();
        structItemNode.id = Integer.parseInt(((Element)structItem).getAttribute("ID"));
        structItemNode.name = ((Element)structItem).getAttribute("ident");
        structItemNode.type = typeBuild(structItem.getFirstChild());


        return structItemNode;
    }

    public static TypeNode typeBuild(Node type){
        TypeNode typeNode = new TypeNode(VarType.EMPTY_TYPE);
        typeNode.id = Integer.parseInt(((Element)type).getAttribute("ID"));
        String name = ((Element)type).getAttribute("ident");
        typeNode.varType = VarType.valueOf(((Element)type).getAttribute("type"));

        if(name!=null){
            typeNode.name = name;
        }
        if(typeNode.varType==VarType.ARRAY){
            typeNode.typeArr = typeBuild(type.getFirstChild());
        }

        return typeNode;
    }

    public static AssociatedItemListNode associatedListBuild(Node assList){
        AssociatedItemListNode assListNode = new AssociatedItemListNode();
        assListNode.id = Integer.parseInt(((Element)assList).getAttribute("ID"));
        Node current = assList.getFirstChild();
        while(current!=null){
            assListNode.list.add(associatedItemBuild(current));
            current = current.getNextSibling();
        }

        return assListNode;
    }

    public static AssociatedItemNode associatedItemBuild(Node assItem){
        AssociatedItemNode associatedItemNode = new AssociatedItemNode();
        associatedItemNode.id = Integer.parseInt(((Element)assItem).getAttribute("ID"));
        String type = ((Element)assItem).getAttribute("type");
        switch (type) {
            case "FUNCTION" -> associatedItemNode.fun = functionBuild(assItem.getFirstChild());
            case "CONST_ITEM" -> associatedItemNode.constStmt = constStmtBuild(assItem.getFirstChild());
        }

        return associatedItemNode;
    }

    public static TraitNode traitBuild(Node trait_){
        TraitNode traitNode = new TraitNode();
        traitNode.id = Integer.parseInt(((Element)trait_).getAttribute("ID"));
        traitNode.name = ((Element)trait_).getAttribute("ident");
        if(trait_.hasChildNodes()){
            traitNode.associatedItemList = associatedListBuild(trait_.getFirstChild());
        }

        return traitNode;
    }

    public static ImplNode implBuild(Node impl_){
        ImplNode implNode = new ImplNode();
        implNode.id = Integer.parseInt(((Element)impl_).getAttribute("ID"));
        implNode.implType = ImplType.valueOf(((Element)impl_).getAttribute("type"));
        String name = ((Element)impl_).getAttribute("ident");
        if(!name.equals("")){
            implNode.name = name;
        }
        implNode.typeNode = typeBuild(((Element)impl_).getElementsByTagName("type_node").item(0));

        if(((Element)impl_).getElementsByTagName("associated_items").getLength()>0){
            implNode.associatedItemList = associatedListBuild(((Element)impl_).getElementsByTagName("associated_items").item(0));
        }

        return implNode;
    }

    public static LetStatementNode letStmtBuild(Node letStmt){
        LetStatementNode letStatementNode = new LetStatementNode();
        letStatementNode.id = Integer.parseInt(((Element)letStmt).getAttribute("ID"));
        letStatementNode.name = ((Element)letStmt).getAttribute("ident");
        letStatementNode.mut = Mutable.valueOf(((Element)letStmt).getAttribute("mutability"));

        letStatementNode.type = typeBuild(((Element)letStmt).getElementsByTagName("type_node").item(0));
        if(((Element)letStmt).getElementsByTagName("expr").getLength()>0){
            letStatementNode.expr = exprBuild(((Element)letStmt).getElementsByTagName("expr").item(0));
        }

        return letStatementNode;
    }

    public static ExpressionNode exprBuild(Node expr){
        ExpressionNode exprNode = new ExpressionNode();
        exprNode.id = Integer.parseInt(((Element)expr).getAttribute("ID"));
        exprNode.type = ExpressionType.valueOf(((Element)expr).getAttribute("type"));

        switch (exprNode.type){
            case PLUS:
            case MINUS:
            case DIV:
            case MUL:
            case EQUAL:
            case NOT_EQUAL:
            case GREATER:
            case LESS:
            case GREATER_EQUAL:
            case LESS_EQUAL:
            case OR:
            case AND:
            case ASGN:
            case RANGE:
            case RANGE_IN:
            case INDEX:
            case ARRAY_AUTO_FILL:
                exprNode.exprLeft = exprBuild(expr.getFirstChild());
                exprNode.exprRight = exprBuild(expr.getFirstChild().getNextSibling());
                break;
            case RANGE_LEFT:
            case RANGE_RIGHT:
            case RANGE_IN_RIGHT:
            case QT:
            case U_MINUS:
            case NEG:
            case STRUCT_FIELD:
            case FIELD_ACCESS:
                exprNode.name = ((Element)expr).getAttribute("ident");
                exprNode.exprLeft = exprBuild(expr.getFirstChild());
                break;
            case BREAK:
            case RETURN:
                if(expr.hasChildNodes()){
                    exprNode.exprLeft = exprBuild(expr.getFirstChild());
                }
                break;
            case ARRAY:
                exprNode.exprList = exprListBuild(expr.getFirstChild());
                break;
            case ID:
            case SELF:
                exprNode.name = ((Element)expr).getAttribute("ident");
                break;
            case CALL:
                exprNode.name = ((Element)expr).getAttribute("ident");
                if(expr.hasChildNodes()){
                    exprNode.exprList = exprListBuild(expr.getFirstChild());
                }
                break;
            case METHOD:
                exprNode.exprLeft = exprBuild(((Element)expr).getElementsByTagName("expr").item(0));
                exprNode.name = ((Element)expr).getAttribute("ident");
                if(((Element)expr).getElementsByTagName("expr_list").getLength()>0){
                    exprNode.exprList = exprListBuild(((Element)expr).getElementsByTagName("expr_list").item(0));
                }
                break;
            case STATIC_METHOD:
                exprNode.name = ((Element)expr).getAttribute("ident");
                exprNode.parentId = ((Element)expr).getAttribute("parent_ident");
                if(((Element)expr).getElementsByTagName("expr_list").getLength()>0){
                    exprNode.exprList = exprListBuild(((Element)expr).getElementsByTagName("expr_list").item(0));
                }
                break;
            case IF:
                Node condition = expr.getFirstChild();
                Node body = condition.getNextSibling();
                Node else_body = body.getNextSibling();

                exprNode.exprLeft = exprBuild(condition);
                exprNode.body = exprBuild(expr.getFirstChild().getNextSibling());
                if(else_body!=null){
                    exprNode.elseBody = exprBuild(else_body);
                }
                break;
            case LOOP:
                exprNode.body = exprBuild(((Element)expr).getElementsByTagName("expr").item(0));
                break;
            case LOOP_FOR:
                exprNode.name = ((Element)expr).getAttribute("ident");
                exprNode.exprLeft = exprBuild(expr.getFirstChild());
                exprNode.body = exprBuild(expr.getFirstChild().getNextSibling());//todo чекнуть пустой цикл
                break;
            case LOOP_WHILE:
                Node left = expr.getFirstChild();
                exprNode.exprLeft = exprBuild(left);
                if(left.getNextSibling()!=null){
                    exprNode.body = exprBuild(left.getNextSibling());
                }
                break;
            case BLOCK:
                if(expr.hasChildNodes()){
                    exprNode.stmtList = statementListBuild(expr.getFirstChild());
                }
                break;
            case INT_LIT:
                exprNode.anInt = Integer.parseInt(((Element)expr).getAttribute("value"));
                break;
            case FLOAT_LIT:
                exprNode.aFloat = Float.parseFloat(((Element)expr).getAttribute("value"));
                break;
            case BOOL_LIT:
                String bool = ((Element)expr).getAttribute("value");
                if(bool == "true"){
                    exprNode.aBoolean = true;
                }
                else {
                    exprNode.aBoolean = false;
                }
                break;
            case CHAR_LIT:
                exprNode.aChar = ((Element)expr).getAttribute("value").charAt(0); //todo проверить
                break;
            case STRING_LIT:
                exprNode.string = expr.getTextContent();
                break;
            case STRUCT:
                exprNode.name = ((Element)expr).getAttribute("ident");
                if(((Element)expr).getElementsByTagName("expr_list").getLength()>0){
                    exprNode.exprList = exprListBuild(((Element)expr).getElementsByTagName("expr_list").item(0));
                }
                break;
        }
        return exprNode;
    }

    public static ExpressionListNode exprListBuild(Node exprList){
        ExpressionListNode expressionListNode = new ExpressionListNode();
        expressionListNode.id = Integer.parseInt(((Element)exprList).getAttribute("ID"));
        Node current = exprList.getFirstChild();
        while(current!=null){
            expressionListNode.list.add(exprBuild(current));
            current = current.getNextSibling();
        }

        return expressionListNode;
    }
}
