package com.lge;

public class Main
{
	static { System.loadLibrary("hello"); } // libhello.so

	public static native void printHello();
	public        native void printWorld();

	public static void main(String[] args)
	{
		printHello();

		Main m =  new Main();
		m.printWorld();
	}
}
