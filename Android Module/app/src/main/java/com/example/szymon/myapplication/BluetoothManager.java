package com.example.szymon.myapplication;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.os.ParcelUuid;
import android.support.v7.app.AppCompatActivity;
import android.widget.Toast;

import java.io.IOException;
import java.io.OutputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Set;
import java.util.UUID;

/**
 * Created by Szymon on 2016-04-24.
 */
public class BluetoothManager {

    private AppCompatActivity appCompatActivity;
    private BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
    private BluetoothDevice bluetoothDevice = null;
    private OutputStream outputStream;

    public final UUID MY_UUID = UUID.fromString("00000000-0000-1000-8000-00805F9B34FB");
    public final String ROBOT_BLUETOOTH_NAME = "HUAWEI U8815"; //HC-06, "HUAWEI U8815"

    public BluetoothManager(AppCompatActivity appCompatActivity) {
        this.appCompatActivity = appCompatActivity;
        init();
    }

    public OutputStream getOutputStream() {
        return outputStream;
    }

    private void init() {
        String name;
        Set<BluetoothDevice> devices = bluetoothAdapter.getBondedDevices();
        for (BluetoothDevice device : devices) {
            name = device.getName();
            if (name.equals(ROBOT_BLUETOOTH_NAME)) { //device.getAddress().equals(ROBOT_BLUETOOTH_ADDRESS)
                bluetoothDevice = device;
            }
        }
        try {
            checkConnection();
            outputStream = bluetoothDevice.createInsecureRfcommSocketToServiceRecord(MY_UUID).getOutputStream();
        } catch (Exception e) {
            Toast.makeText(appCompatActivity.getBaseContext(), "Devices are not bounded!", Toast.LENGTH_LONG).show();
            appCompatActivity.finish();
        }
    }

    private void checkConnection() throws Exception {
        if (bluetoothDevice == null) {
            throw new Exception();
        }
    }
}
