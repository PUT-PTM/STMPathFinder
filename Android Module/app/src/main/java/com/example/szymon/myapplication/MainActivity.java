package com.example.szymon.myapplication;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private int[] buttons = {R.id.buttonUp, R.id.buttonDown, R.id.buttonLeft, R.id.buttonRight, R.id.buttonExploring};
    private TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView = (TextView) findViewById(R.id.textView);
        initButtons();
    }

    private void initButtons() {
        View.OnClickListener clickListener = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Button button = (Button) v;
                textView.setText(button.getText());
                Log.i("button", button.getText().toString());
            }
        };

        for (int i : buttons) {
            ((Button) findViewById(i)).setOnClickListener(clickListener);
        }
    }
}
