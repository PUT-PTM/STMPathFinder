package com.example.szymon.myapplication;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.example.szymon.myapplication.mapping.MappingService;
import com.example.szymon.myapplication.mapping.MoveData;

import java.io.IOException;
import java.io.OutputStream;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class MainActivity extends AppCompatActivity {

    private static final String ADAPTER_NAME = "ADAPTER";
    private final int[] movingButton = {
            R.id.buttonUp,
            R.id.buttonDown,
            R.id.buttonLeft,
            R.id.buttonRight
    };

    private BluetoothManager bluetoothManager;
    private TextView textView = null;
    private OutputStream bluetoothOutputStream = null;
    private Map<Button, String> moveButtons = new HashMap<>();
    private Switch registerSwitch;
    private MappingService mappingService = new MappingService();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        init();
    }


    private void init() {
        textView = (TextView) findViewById(R.id.textView);
        registerSwitch = (Switch) findViewById(R.id.registering);

        activateBluetooth();

        initMovingButtons();
        initExploringButton();
        initClearButton();
    }

    private void initMovingButtons() {
        for (int buttonId : movingButton) {
            Button tmpButton = (Button) findViewById(buttonId);
            if (tmpButton != null) {
                tmpButton.setOnTouchListener(new View.OnTouchListener() {
                    @Override
                    public boolean onTouch(View v, MotionEvent event) {
                        if (event.getAction() == MotionEvent.ACTION_DOWN || event.getAction() == MotionEvent.ACTION_UP) {
                            Button button = (Button) v;
                            String key = button.getText().toString();
                            sendDataViaBluetooth(key);
                            registerIfEnabled(key);
                        }
                        return true;
                    }
                });
            }
            moveButtons.put(tmpButton, tmpButton.getText().toString());
        }
    }

    private void initExploringButton() {
        Button tmpButton = (Button) findViewById(R.id.buttonExploring);
        if (tmpButton != null) {
            tmpButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    Button button = (Button) v;
                    button.setEnabled(false);
                    runFromHistory();
                    button.setEnabled(true);
                }
            });
        }
    }

    private void initClearButton() {
        Button tmpButton = (Button) findViewById(R.id.buttonClear);
        if (tmpButton != null) {
            tmpButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    mappingService.clearData();
                }
            });
        }
    }

    private void activateBluetooth() {
        bluetoothManager = new BluetoothManager(this);
        bluetoothOutputStream = bluetoothManager.getOutputStream();
    }

    private void registerIfEnabled(String key) {
        if (registerSwitch.isChecked()) {
            mappingService.addData(key);
        }
    }

    private void runFromHistory() {
        if (mappingService.getMoveHistory().size() != 0) {
            enableUi(false);
            Iterator<MoveData> iterator = mappingService.getMoveHistory().iterator();
            MoveData firstMeasure = iterator.next();
            long lastTimestamp = firstMeasure.getTimestamp();
            sendDataViaBluetooth(firstMeasure.getKey());
            while (iterator.hasNext()) {
                MoveData measure = iterator.next();
                try {
                    long sleepTime = measure.getTimestamp() - lastTimestamp;
                    Thread.sleep(sleepTime);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                sendDataViaBluetooth(measure.getKey());
                lastTimestamp = measure.getTimestamp();
            }
            mappingService.clearData();
            enableUi(true);
        }
    }

    private void enableUi(Boolean enabled) {
        Button button;
        for (int buttonId : movingButton) {
            button = (Button) findViewById(buttonId);
            button.setEnabled(enabled);
        }
        ((Button) findViewById(R.id.buttonExploring)).setEnabled(enabled);
        ((Button) findViewById(R.id.buttonClear)).setEnabled(enabled);
        ((Switch) findViewById(R.id.registering)).setEnabled(enabled);
    }

    private void sendDataViaBluetooth(String message) {
        try {
            bluetoothOutputStream.write(message.getBytes());
            bluetoothOutputStream.write("\n".getBytes());
        } catch (IOException e) {
            errorExit("Fatal Error", "Error occurred while sending Data");
        }
    }

    private void errorExit(String title, String message) {
        Toast.makeText(getBaseContext(), title + " - " + message, Toast.LENGTH_LONG).show();
        finish();
    }
}
