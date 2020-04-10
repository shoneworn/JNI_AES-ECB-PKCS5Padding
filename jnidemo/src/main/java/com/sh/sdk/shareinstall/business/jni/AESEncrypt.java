package com.sh.sdk.shareinstall.business.jni;


/**
 * Created by chenxiangxiang on 2020/4/9.
 */
public class AESEncrypt {
     static {
          System.loadLibrary("JNIEncrypt");
     }
     public static native String decode(String content);

     public static native String encode(String content);


}
