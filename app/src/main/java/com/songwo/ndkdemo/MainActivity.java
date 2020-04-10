package com.songwo.ndkdemo;


import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

import com.sh.sdk.shareinstall.business.jni.AESEncrypt;

public class MainActivity extends Activity {

    private TextView tvEncode;
    private TextView tvEncodeJ;
    private TextView tvDecode;
    private TextView tvDecodeJ;
    private static final String CONTENT = "123123123";
    private static final String KEY = "1234567890abcdef";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        AESEncrypt aesEncrypt = new AESEncrypt();
        // Example of a call to a native method
        tvEncode = findViewById(R.id.tv_encode);
        tvEncodeJ = findViewById(R.id.tv_encode_j);
        tvDecode = findViewById(R.id.tv_decode);
        tvDecodeJ = findViewById(R.id.tv_decode_j);

        String encryptNative = encodeStr(aesEncrypt, CONTENT);
        String encryptJava = AppParamsUtil.aesEncrypt(CONTENT, KEY);

        tvEncode.setText("native Aes encode = " + encryptNative);
        tvEncodeJ.setText("java Aes encode = " + encryptJava);

        tvDecode.setText("native Aes decode = " + decodeStr(aesEncrypt, encryptNative));
        tvDecodeJ.setText("java Aes decode = " + AppParamsUtil.aesDecrypt(encryptJava, KEY));
    }

    private String decodeStr(AESEncrypt aesEncrypt, String encodeStr) {
        return aesEncrypt.decode(encodeStr);
    }

    private String encodeStr(AESEncrypt aesEncrypt, String s) {
        return aesEncrypt.encode(s);
    }


}
