package main.semantic;

public enum Constant {
    UTF8(1),
    INTEGER(3),
    FLOAT(4),
    STRING(8),
    NAME_AND_TYPE(12),
    CLASS(7),
    FIELD_REF(9),
    METHOD_REF(10),
    INTERFACE_METHOD_REF(11),
    LONG(5),
    DOUBLE(6),
    METHOD_HANDLE(15),
    METHOD_TYPE(16),
    INVOKE_DYNAMIC(18)
    ;

    public final int code;
    Constant(int code) {
        this.code = code;
    }
}
