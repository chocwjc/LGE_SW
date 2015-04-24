public class Main
{
	static { System.loadLibrary("arr2d"); } // libarr2d.so
	public static native void    print2DIntArr(int[][] arr);
	public static native int[][]  make2DIntArr(int row, int col);

	public static void main(String[] args)
	{
		int[][] arr1 = {{1,2,3}, {4,5,6}};
		print2DIntArr(arr1);

		int[][] arr2 = make2DIntArr(2, 3);

		System.out.print("[Java] ");
		
		for (int i = 0; i < arr2.length; i++) {
			for (int j = 0; j < arr2[i].length; j++) {
				System.out.print(arr2[i][j] +  " ");
			}
		}
		System.out.println();
	}
}
