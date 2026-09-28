#include"all.hpp"

class ReadMap{
public:
    ReadMap(string filename);
    vector <Platform>  get_platforms();
private:
    vector<Platform > platforms;
};
