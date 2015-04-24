public class Main
{
	static { System.loadLibrary("circle"); }
	public static native float getArea(int r);

	public static void main(String[] args)
	{
		System.out.println(getArea(2));
		System.out.println(getArea(3));
	}
}
