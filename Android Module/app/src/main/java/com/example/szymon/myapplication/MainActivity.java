package com.example.szymon.myapplication;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.io.OutputStream;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    private static final String ADAPTER_NAME = "ADAPTER";
    private final int[] movingButton = {
            R.id.buttonUp,
            R.id.buttonDown,
            R.id.buttonLeft,
            R.id.buttonRight,
            R.id.buttonExploring
    };

    private BluetoothManager bluetoothManager;
    private TextView textView = null;
    private OutputStream outputStream = null;
    private Map<Button, String> moveButtons = new HashMap<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        init();
    }


    private void init() {
        textView = (TextView) findViewById(R.id.textView);
        bluetoothManager = new BluetoothManager(this);
        outputStream = bluetoothManager.getOutputStream();
        //Initialize buttons, that handle on press events, and sending data
        initMovingButtons();
        initExploringButton();

    }

    private void initMovingButtons() {
        for (int buttonId : movingButton) {
            Button tmpButton = (Button) findViewById(buttonId);
            //ten if dlatego, że srodowisko bardzo balo sie o nulla 0_o
            if (tmpButton != null) {
                tmpButton.setOnTouchListener(new View.OnTouchListener() {
                    @Override
                    public boolean onTouch(View v, MotionEvent event) {
                        Button button = (Button) v;
                        while (event.getAction() == MotionEvent.ACTION_DOWN) {
                            sendData(moveButtons.get(button));
                        }
                        return true;
                    }
                });
            }
            moveButtons.put(tmpButton, tmpButton.getText().toString());
        }
    }

    private void sendData(String message) {
        byte[] msgBuffer = message.getBytes();

        try {
            outputStream.write(msgBuffer);
        } catch (IOException e) {
            errorExit("Fatal Error", "Error occurred while sending Data");
        }
    }

    private void initExploringButton() {
        textView.setText("This button is not yet implemented.");
    }

    private void errorExit(String title, String message) {
        Toast.makeText(getBaseContext(), title + " - " + message, Toast.LENGTH_LONG).show();
        finish();
    }
}
