package com.johnnie.pcapanalyzer.utils;

public class TextUtils {
	
	private TextUtils () {}
	
	/**
	 * 判断字符串是否为空
	 * @param str
	 * @return
	 */
	public static boolean isEmpty (String str) {
		if (str == null || str.length() < 0) {
			return true;
		} else {
			return false;
		}
	}
	
}
