package com.example.test1;

import android.app.Activity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    static {

        System.loadLibrary("test-lib");
    }

    TextView tv_text;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tv_text = findViewById(R.id.tv_text);
        tv_text.setText(testNdk2("123456"));
        tv_text.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String str = stringFromJNI2(MainActivity.this, "ubuntu");
                Log.e("chris", str);
                tv_text.setText(testNdk2(str));
            }
        });
    }

    public int getIndex() {
        return index;
    }


    public native String getHello();

    public native int meaningOfTheUniverse() ;


    public void setIndex(int index) {
        this.index = index;
    }

    int index = 100;


    public static void showText(String jniStr) {

        Log.e("chris", jniStr);

    }


    native String testNdk();

    native String testNdk1(String str);

    native String testNdk2(String str);


    native String stringFromJNI();

    native String stringFromJNI1(int[] iArr, String[] strArr);

    native String stringFromJNI2(MainActivity iArr, String strArr);
}
