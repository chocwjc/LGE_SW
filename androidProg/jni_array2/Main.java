public class Main
{
	static { System.loadLibrary("charArr"); } // libcharArr.so
	public static native void   printCharArr(char[] arr);
	public static native char[] makeCharArr(int len);

	public static void main(String[] args)
	{
		char[] arr1 = new char[]{ 'a', 'b', 'c', 'd', 'e' };
		
		printCharArr(arr1); // [C] 1 2 3 4 5

		char[] arr2 = makeCharArr(5);

		System.out.print("[Java] ");
		for (int i = 0; i < arr2.length; i++)
			System.out.print(arr2[i] + " ");    // [Java] 0 0 0 0 0
		System.out.println();
	}
}
