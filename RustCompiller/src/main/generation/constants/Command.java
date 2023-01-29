package main.generation.constants;

public enum Command {
    iconst_m1(0x2),
    iconst_0(0x3),
    iconst_1(0x4),
    iconst_2(0x5),
    iconst_3(0x6),
    iconst_4(0x7),
    iconst_5(0x8),

    bipush(0x10),
    sipush(0x11),

    ldc(0x12),
    ldc_w(0x13),

    iload(0x15),
    fload(0x17),
    aload(0x19),

    istore(0x36),
    fstore(0x38),
    astore(0x3A),

    pop(0x57),

    dup(0x59),
    dup2(0x5C),

    iadd(0x60),
    fadd(0x62),
    imul(0x68),
    fmul(0x6A),
    isub(0x64),
    fsub(0x66),
    idiv(0x6C),
    fdiv(0x6E),
    iinc(0x84),

    if_icmpeq(0x9F),
    if_icmpne(0xA0),
    if_icmplt(0xA1),
    if_icmple(0xA4),
    if_icmpgt(0xA3),
    if_icmpge(0xA2),

    fcmpg(0x96),
    fcmpl(0x95),

    ifeq(0x99),
    ifne(0x9A),
    iflt(0x9B),
    ifle(0x9E),
    ifgt(0x9D),
    ifge(0x9C),

    if_acmpeq(0xA5),
    if_acmpne(0xA6),

    goto_(0xA7),

    tableswitch(0xAA),
    lookupswitch(0xAB),

    newarray(0xBC),
    anewarray(0xBD),
    arraylength(0xBE),
    iaload(0x2E),
    aaload(0x32),
    iastore(0x4F),
    aastore(0x53),

    new_(0xBB),
    getfield(0xB4),
    putfield(0xB5),
    instanceof_(0xC1),
    checkcast(0xC0),

    invokevirtual(0xB6),
    invokespecial(0xB7),
    invokestatic(0xB8),

    ireturn(0xAC),
    freturn(0xAE),
    areturn(0xB0),
    return_(0xB1)
    ;

    public final int commandCode;

    Command(int commandCode) {
        this.commandCode = commandCode;
    }
}
