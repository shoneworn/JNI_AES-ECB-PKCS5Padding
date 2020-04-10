package com.songwo.jnidemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.sh.sdk.shareinstall.business.jni.AESEncrypt;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView tv_encode = findViewById(R.id.tv_encode);
        tv_encode.setText(AESEncrypt.encode("123123123"));
    }
}
