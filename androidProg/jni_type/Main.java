public class Main
{
	static { System.loadLibrary("type"); }  // libtype.so
	public static native void printInt(int i);
	public static native void printByte(byte i);
	public static native void printChar(char i);
	public static native void printShort(short i);
	public static native void printLong(long i);
	public static native void printFloat(float i);
	public static native void printDouble(double i);
	public static native void printBoolean(boolean i);

	public static void main(String[] args)
	{
		printInt(1);
		printByte((byte)2);
		printChar('A');
		printShort((short)3);
		printLong((long)4);
		printFloat((float)1.1);
		printDouble(1.2);
		printBoolean(true);
	}
}


