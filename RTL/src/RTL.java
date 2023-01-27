public class RTL {

    public static void println(Object out) {
        System.out.println(out);
    }

    public static void println_i32(String str, int value) {
        System.out.println(str.replace("{}", String.valueOf(value)));
    }

    public static void println_f64(String str, float value) {
        System.out.println(str.replace("{}", String.valueOf(value)));
    }

}
