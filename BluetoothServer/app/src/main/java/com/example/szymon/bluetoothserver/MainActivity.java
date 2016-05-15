package com.example.szymon.bluetoothserver;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import java.io.IOException;
import java.io.InputStream;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    private BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
    private BluetoothServerSocket bluetoothServerSocket = null;
    private BluetoothSocket bluetoothSocket = null;
    private InputStream inputStream;
    private TextView textView;

    public final UUID MY_UUID = UUID.fromString("00000000-0000-1000-8000-00805F9B34FB");
    public final String BLUETOOTH_NAME = "ALE-L21"; //HC-06, "HUAWEI U8815"


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        textView = (TextView) findViewById(R.id.textView);
        textView.setText("test");
        setContentView(R.layout.activity_main);
        bluetoothInit();
    }

    private void bluetoothInit() {
        try {
            bluetoothServerSocket = bluetoothAdapter.listenUsingInsecureRfcommWithServiceRecord("HUAWEI U8815", MY_UUID);
            bluetoothSocket = bluetoothServerSocket.accept();
            inputStream = bluetoothSocket.getInputStream();
            while (true) {
                textView.setText(inputStream.read());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
