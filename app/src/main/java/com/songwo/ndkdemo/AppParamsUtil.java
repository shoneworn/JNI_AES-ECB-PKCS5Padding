package com.songwo.ndkdemo;

import android.util.Base64;
import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;


public class AppParamsUtil {

    private static final String TAB = "|"; // 原来采用制表符，但是IOS走不通，改为竖线
    private static final String AES_KEY = "1234567890abcdef"; // AES加密key
    private static String mObatchid = ""; // 本次启动唯一ID
    private static String mAppverint = ""; // App版本号 ，如：010101
    private static String mCustomChannel;

    /**
     * AES加密
     *
     * @param str
     * @param key
     * @return
     */
    public static String aesEncrypt(String str, String key) {
        if (str == null || key == null) {
            return null;
        }

        try {
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
            cipher.init(Cipher.ENCRYPT_MODE, new SecretKeySpec(key.getBytes("utf-8"), "AES"));
            byte[] bytes = cipher.doFinal(str.getBytes("utf-8"));
            return new String(Base64.encode(bytes, Base64.NO_WRAP));
        } catch (Exception e) {
            return null;
        }
    }

    /**
     * AES解密
     *
     * @param str
     * @param key
     * @return
     */
    public static String aesDecrypt(String str, String key) {
        if (str == null || key == null) {
            return null;
        }

        try {
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
            cipher.init(Cipher.DECRYPT_MODE, new SecretKeySpec(key.getBytes("utf-8"), "AES"));
            byte[] bytes = Base64.decode(str, Base64.NO_WRAP);
            bytes = cipher.doFinal(bytes);
            return new String(bytes, "utf-8");
        } catch (Exception e) {
            return null;
        }
    }

}
