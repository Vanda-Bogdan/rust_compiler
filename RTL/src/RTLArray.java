import java.util.ArrayList;

public class RTLArray {

    private ArrayList<Object> arrayList = new ArrayList<>();

    public int getInt(int index) {
        return (int) arrayList.get(index);
    }

    public void setInt(int index, int value) {
        arrayList.set(index, value);
    }

    public RTLArray initInt(int value) {
        arrayList.add(value);
        return this;
    }

    public float getFloat(int index) {
        return (float) arrayList.get(index);
    }

    public void setFloat(int index, float value) {
        arrayList.set(index, value);
    }

    public RTLArray initFloat(float value) {
        arrayList.add(value);
        return this;
    }

    public Object getObject(int index) {
        return arrayList.get(index);
    }

    public void setObject(int index, Object value) {
        arrayList.set(index, value);
    }

    public RTLArray initObject(Object value) {
        arrayList.add(value);
        return this;
    }

    public int len() {
        return arrayList.size();
    }

    public RTLArray intAutoFill(int value, int count) {
        for (int i = 0; i < count; i++) {
            arrayList.add(value);
        }
        return this;
    }

    public RTLArray floatAutoFill(float value, int count) {
        for (int i = 0; i < count; i++) {
            arrayList.add(value);
        }
        return this;
    }

    public RTLArray objectAutoFill(Object value, int count) {
        for (int i = 0; i < count; i++) {
            arrayList.add(value);
        }
        return this;
    }
}
