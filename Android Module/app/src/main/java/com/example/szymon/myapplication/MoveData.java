package com.example.szymon.myapplication;

/**
 * Created by Szymon on 2016-05-13.
 */
public class MoveData {

    private String key;
    private long timestamp;

    public MoveData(String key, long timestamp) {
        this.key = key;
        this.timestamp = timestamp;
    }

    public MoveData(String key) {
        this.key = key;
        this.timestamp = System.currentTimeMillis();
    }

    public String getKey() {
        return key;
    }

    public void setKey(String key) {
        this.key = key;
    }

    public long getTimestamp() {
        return timestamp;
    }

    public void setTimestamp(long timestamp) {
        this.timestamp = timestamp;
    }


}
