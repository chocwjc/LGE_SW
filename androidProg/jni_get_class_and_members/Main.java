public class Main
{
	static { System.loadLibrary("circle"); } // libcircle.so
	public  static native float getCircleArea(int r);

	public static void main(String[] args)
	{
		System.out.println(getCircleArea(2));
	}
}
