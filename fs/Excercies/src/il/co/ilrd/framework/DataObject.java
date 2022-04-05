package il.co.ilrd.framework;

public class DataObject {
    private String code;
    private int value;


    private DataObject(String s, int val){
        code = s;
        value = val;
    }

    public String getCode(){
        return code;
    }

    public int getValue(){
        return value;
    }

    public static DataObject setObject(String s, int val){
        return new DataObject(s,val);

    }

}
