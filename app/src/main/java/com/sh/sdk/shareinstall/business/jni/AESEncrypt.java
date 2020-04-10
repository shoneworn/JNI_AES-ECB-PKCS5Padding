package com.sh.sdk.shareinstall.business.jni;


/**
 * Created by chenxiangxiang on 2020/4/9.
 */
public class AESEncrypt {
     static {
          System.loadLibrary("JNIEncrypt");
     }
     public native String decode(String content);

     public native String encode(String content);


}
