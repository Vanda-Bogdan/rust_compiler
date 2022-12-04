package main.semantic;

import java.util.ArrayList;

public class Table {

    public final String name;
    public ArrayList<TableItem> items = new ArrayList<>();

    public Table(String name) {
        this.name = name;
    }

    public int add(TableItem item) {
        items.add(item);
        return items.size();
    }

    public int searchByUtf8(String utf8) {
        for (TableItem element : items) {
            if (element.type().code == Constant.UTF8.code && element.utf8() == utf8) {
                return element.type().code;
            }
        }
        return -1;
    }

}
