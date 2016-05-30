package com.example.szymon.myapplication;

import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MovingEvent implements View.OnTouchListener {

    public static final String STOP = "s";

    private String message;

    private Button button;

    private MainActivity mainActivity;

    public MovingEvent(Button button, String message, MainActivity mainActivity) {
        this.button = button;
        this.message = message;
        this.mainActivity = mainActivity;
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_DOWN) {
            mainActivity.sendDataViaBluetooth(message);
            mainActivity.registerIfEnabled(message);
            Toast.makeText(mainActivity.getBaseContext(), message, Toast.LENGTH_SHORT).show();
        }
        if (event.getAction() == MotionEvent.ACTION_UP) {
            mainActivity.sendDataViaBluetooth(STOP);
            mainActivity.registerIfEnabled(STOP);
        }
        return true;
    }
}
