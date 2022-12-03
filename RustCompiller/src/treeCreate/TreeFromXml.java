package treeCreate;

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

            // Получаем корневой элемент
            Element root = document.getDocumentElement();
            Node stmt_list = root.getFirstChild();

            for (int i = 0; i < stmt_list.getLength(); i++) {
                Element stmt = stmt_list;
                stmt.getFirstChild().getNextSibling();

                System.out.println(stmt.getAttributes());
            }

        } catch (ParserConfigurationException ex) {
            ex.printStackTrace(System.out);
        } catch (SAXException ex) {
            ex.printStackTrace(System.out);
        } catch (IOException ex) {
            ex.printStackTrace(System.out);
        }

        return new Tree(null);
    }

}
