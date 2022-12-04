package treeCreate;

import main.nodes.Mutable;
import main.nodes.ProgramNode;
import main.nodes.Visibility;
import main.nodes.declstmt.DeclarationStatementNode;
import main.nodes.expression.ExpressionListNode;
import main.nodes.expression.ExpressionNode;
import main.nodes.expression.ExpressionType;
import main.nodes.function.FunctionType;
import main.nodes.impl.ImplType;
import main.nodes.letstmt.LetStatementNode;
import main.nodes.stmt.StatementListNode;
import main.nodes.stmt.StatementNode;
import main.nodes.stmt.StatementType;
import main.treeprint.Tree;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;

public class TreeFromXml {
    public static final String path = "treeXML.xml";

    public static Tree buildTree(){
        try {
            // Создается построитель документа
            DocumentBuilder documentBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
            // Создается дерево DOM документа из файла
            Document document = documentBuilder.parse(path);

            //program
            Node program = document.getDocumentElement();

            Tree tree = new Tree(programBuild(program));

            //stmt_list
            Node stmt_list = program.getFirstChild();

            //stmt_list children




            //System.out.println(stmt_list.getLength());



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
        programNode.stmtList = statementListBuild(programXML.getFirstChild());
        return programNode;
    }

    public static StatementListNode statementListBuild(Node stmtListXML){

        StatementListNode statementListNode = new StatementListNode();

        NodeList stmts = stmtListXML.getChildNodes();
        for (int i = 0; i < stmts.getLength(); i++) {
            statementListNode.list.add(statementBuild(stmts.item(i)));
        }

        return statementListNode;
    }

    public static StatementNode statementBuild(Node stmt){
        StatementNode statementNode = new StatementNode();
        statementNode.type = StatementType.valueOf(((Element)stmt).getAttribute("type"));

        switch (statementNode.type) {
            case DECLARATION -> statementNode.declarationStmt = declStmtBuild(stmt.getFirstChild());
            case LET -> statementNode.letStmt = letStmtBuild(stmt.getFirstChild());
            case EXPRESSION -> statementNode.expr = exprBuild(stmt.getFirstChild());
        }

        return statementNode;
    }

    public static DeclarationStatementNode declStmtBuild(Node declStmt){
        DeclarationStatementNode declarationStatementNode = new DeclarationStatementNode();
        //System.out.println(declStmt.getTextContent());
        return declarationStatementNode;
    }

    public static LetStatementNode letStmtBuild(Node letStmt){
        LetStatementNode letStatementNode = new LetStatementNode();

        return letStatementNode;
    }

    public static ExpressionNode exprBuild(Node expr){
        ExpressionNode exprNode = new ExpressionNode();
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
                exprNode.name = ((Element)expr).getAttribute("ident");
                break;
            case CALL:
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
            case FIELD_ACCESS:
                exprNode.name = ((Element)expr).getAttribute("ident");
                exprNode.exprList = exprListBuild(expr.getFirstChild());
                break;
            case IF:

                break;
        }


        return exprNode;
    }

    public static ExpressionListNode exprListBuild(Node exprList){
        ExpressionListNode expressionListNode = new ExpressionListNode();

        Node current = exprList.getFirstChild();
        while(current!=null){
            expressionListNode.list.add(exprBuild(current));
            current = current.getNextSibling();
        }

        return expressionListNode;
    }
}
