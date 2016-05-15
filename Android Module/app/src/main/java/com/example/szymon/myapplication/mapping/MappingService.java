package com.example.szymon.myapplication.mapping;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Szymon on 2016-05-13.
 */
public class MappingService {
    private List<MoveData> moveHistory = new ArrayList<>();

    public void addData(MoveData data) {
        moveHistory.add(data);
    }

    public void addData(String key) {
        this.addData(new MoveData(key, System.currentTimeMillis()));
    }

    public void clearData() {
        moveHistory.clear();
    }

    public List<MoveData> getMoveHistory() {
        return moveHistory;
    }
}
