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

    public static void println_bool(String str, int b) {
        if (!str.contains("{}")) {
            throw new IllegalArgumentException("Форматная строка вывода не содержит {}");
        }
        System.out.println(str.replace("{}", String.valueOf(b == 1)));
    }

    public static String readln(){
        java.util.Scanner in = new java.util.Scanner(System.in);
        return in.nextLine();
    }

    public static int readln_i32(){
        java.util.Scanner in = new java.util.Scanner(System.in);
        return in.nextInt();
    }

    public static float readln_f64(){
        java.util.Scanner in = new java.util.Scanner(System.in);
        return in.nextFloat();
    }

    public static int stringEqual(String left, String right, int code) {
        int result = 0;
        switch (code) {
            case 0 -> { // ==
                if (left == right) {
                    result = 1;
                } else {
                    result = 0;
                }
            }
            case 1 -> { // !=
                if (left != right) {
                    result = 1;
                } else {
                    result = 0;
                }
            }
            case 2 -> { // >
                if (left.compareTo(right) > 0) {
                    result = 1;
                } else {
                    result = 0;
                }
            }
            case 3 -> { // <
                if (left.compareTo(right) < 0) {
                    result = 1;
                } else {
                    result = 0;
                }
            }
            case 4 -> { // >=
                if (left.compareTo(right) >= 0) {
                    result = 1;
                } else {
                    result = 0;
                }
            }
            case 5 -> { // <=
                if (left.compareTo(right) <= 0) {
                    result = 1;
                } else {
                    result = 0;
                }
            }
        }
        return result;
    }
}
