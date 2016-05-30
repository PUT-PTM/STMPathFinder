package com.example.szymon.myapplication;

import android.graphics.Color;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.example.szymon.myapplication.mapping.MappingService;
import com.example.szymon.myapplication.mapping.MoveData;

import java.io.IOException;
import java.io.OutputStream;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

public class MainActivity extends AppCompatActivity {

    private final List<Integer> movingButton = Arrays.asList(
            R.id.buttonUp,
            R.id.buttonDown,
            R.id.buttonLeft,
            R.id.buttonRight
    );

    private List<String> messages = Arrays.asList(
            "w",
            "r",
            "a",
            "d"
    );

    private BluetoothManager bluetoothManager;
    private TextView textView = null;
    private OutputStream bluetoothOutputStream = null;
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

        initMovingButtons();
        initExploringButton();
        initClearButton();

        activateBluetooth();
    }

    private void initMovingButtons() {
        for (int i = 0; i < messages.size(); i++) {
            Button tmpButton = (Button) findViewById(movingButton.get(i));
            if (tmpButton != null) {
                tmpButton.setOnTouchListener(new MovingEvent(tmpButton, messages.get(i), this));
                tmpButton.setText(messages.get(i));
            }
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

    void registerIfEnabled(String key) {
        if (registerSwitch.isChecked()) {
            mappingService.addData(key);
        }
    }

    private void runFromHistory() {
        if (mappingService.getMoveHistory().size() != 0) {
            disableUi();
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
            enableUi();
        }
    }

    private void enableUi() {
        for (int buttonId : movingButton) {
            enableButton((Button) findViewById(buttonId));
        }
        enableButton((Button) findViewById(R.id.buttonExploring));
        enableButton((Button) findViewById(R.id.buttonClear));
        enableButton((Switch) findViewById(R.id.registering));
    }

    private void disableUi() {
        for (int buttonId : movingButton) {
            enableButton((Button) findViewById(buttonId));
        }
        disableButton((Button) findViewById(R.id.buttonExploring));
        disableButton((Button) findViewById(R.id.buttonClear));
        disableButton((Switch) findViewById(R.id.registering));
    }

    private void enableButton(Button button) {
        button.setEnabled(true);
        button.setBackgroundColor(Color.WHITE);
    }

    private void disableButton(Button button) {
        button.setEnabled(false);
        button.setBackgroundColor(Color.GRAY);
    }

    void sendDataViaBluetooth(String message) {
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
