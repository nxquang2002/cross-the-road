#include "SingleRow.h"
#include <time.h>
#define ROW_NUM 5

class ROWS {
private:
    vector<SINGLEROW*> rows;
public:
    ROWS();
    ~ROWS();
    void newState(int t, int v);
};