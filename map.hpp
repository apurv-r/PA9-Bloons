#include <vector>
using std::vector;


class map {
    private:
        vector<vector<int>> checkPoints;
        
    public:
        map(){}
        map(vector<vector<int>> checkPoints){}
        ~map(){}
        vector<vector<int>> getAllCheckPoints();
        vector<int> getCheckPoint(int index);
};


