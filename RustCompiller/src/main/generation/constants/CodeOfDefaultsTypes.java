package main.generation.constants;

public enum CodeOfDefaultsTypes {
    T_BOOLEAN(4),
    T_CHAR(5),
    T_FLOAT(6),
    T_DOUBLE(7),
    T_BYTE(8),
    T_SHORT(9),
    T_INT(10),
    T_LONG(11)
    ;

    private int codeOfDefaultsTypes;

    CodeOfDefaultsTypes(int codeOfDefaultsTypes) {
        this.codeOfDefaultsTypes = codeOfDefaultsTypes;
    }
}
