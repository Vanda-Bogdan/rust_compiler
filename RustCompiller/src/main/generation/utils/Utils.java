package main.generation.utils;

import main.semantic.*;

import java.nio.ByteBuffer;
import java.util.ArrayList;

public class Utils {

    // ---------------------------Перевод численных значений в массив байт и обратно---------------------- //
    public static byte[] intTo2ByteArray(int value) {
        return new byte[]{
                (byte) (value >> 8),
                (byte) value
        };
    }

    public static byte[] intTo4ByteArray(int value) {
        return ByteBuffer.allocate(4).putInt(value).array();
    }

    public static byte[] floatTo4ByteArray(float value) {
        return ByteBuffer.allocate(4).putFloat(value).array();
    }

    public static int intFromByteArray(byte[] arr) {
        int value = 0;
        for (byte b : arr) {
            value = (value << 8) + (b & 0xFF);
        }
        return value;
    }

    public static float floatFromByteArray(byte[] arr) {
        return ByteBuffer.wrap(arr).getFloat();
    }

    public static byte[] intTo1ByteArray(int value) {
        return new byte[] {
                (byte)value
        };
    }

    // -----------------------------------Запись в файл массива массивов байт---------------------------------------- //
    public static void write() {

    }

}
