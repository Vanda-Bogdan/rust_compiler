public class RTL {

    public static void println(Object out) {
        System.out.println(out);
    }

    public static void println_i32(String str, int value) {
        if (!str.contains("{}")) {
            throw new IllegalArgumentException("Форматная строка вывода не содержит {}");
        }
        System.out.println(str.replace("{}", String.valueOf(value)));
    }

    public static void println_f64(String str, float value) {
        if (!str.contains("{}")) {
            throw new IllegalArgumentException("Форматная строка вывода не содержит {}");
        }
        System.out.println(str.replace("{}", String.valueOf(value)));
    }

    public static void println_char(String str, String ch) {
        if (!str.contains("{}")) {
            throw new IllegalArgumentException("Форматная строка вывода не содержит {}");
        }
        System.out.println(str.replace("{}", String.valueOf(ch)));
    }

}
