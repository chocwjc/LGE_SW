public class Main
{
	static { System.loadLibrary("string"); } // libstring.so
	public static native void   printString(String s);
	public static native String getHelloWorld();

	public static void main(String args[])
	{
		printString("Hello, world"); // [C] Hello,  world
		System.out.println("[Java]" + getHelloWorld());
	}
}

