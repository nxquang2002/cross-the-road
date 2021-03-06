#ifndef _ROWS_H_
#define _ROWS_H_

#include "SingleRow.h"
#include "Level.h"
#include <time.h>
#define ROW_NUM 5

class ROWS {
private:
    vector<SINGLEROW*> rows;
public:
    ROWS();
    ROWS(int dist);
    ~ROWS();
    void initializeState(int speed);
    void nextState(int t, int v, int lightPhase, int epoch, bool denser);
    vector<ENEMY*> listEnemies(int rowIndex) const;    //get the list of enemies in row i
    void saveRows(ofstream& ofs);
    void loadRows(ifstream& ifs, LEVEL level);
};

#endif // !_ROWS_H_