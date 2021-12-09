#ifndef _ROWS_H_
#define _ROWS_H_

#include "SingleRow.h"
#include <time.h>
#define ROW_NUM 5

class ROWS {
private:
    vector<SINGLEROW*> rows;
public:
    ROWS(int dist = 7);
    ~ROWS();
    void initializeState(int speed);
    void newState(int t, int v, int lightPhase, int epoch);
    vector<ENEMY*> listEnemies(int rowIndex) const;    //get the list of enemies in row i
};

#endif // !_ROWS_H_