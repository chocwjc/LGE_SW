public class Main
{
	static { System.loadLibrary("arr"); } // libarr.so
	public static native void  printIntArr(int[] arr);
	public static native int[] makeIntArr(int len);

	public static void main(String[] args)
	{
		int[] arr1 = new int[]{ 1,2,3,4,5 };
		
		printIntArr(arr1); // [C] 1 2 3 4 5

		int[] arr2 = makeIntArr(5);

		System.out.print("[Java] ");
		for (int i = 0; i < arr2.length; i++)
			System.out.print(arr2[i] + " ");    // [Java] 0 0 0 0 0
		System.out.println();
	}
}
