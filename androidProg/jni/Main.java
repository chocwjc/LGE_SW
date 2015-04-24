public class Main
{

	static { System.loadLibrary("main");  }  // ---> libmain.so
	public static native void printHelloWorld();

	public static void main(String[] args)
	{
		System.out.println("Hello world [Java mainclass]");

		printHelloWorld();  // ---> call c-lang function
	}
}
