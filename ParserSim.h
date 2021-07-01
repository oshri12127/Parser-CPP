//
// Created by Oshri on 21/06/2021.
//

#ifndef EX5_PARSERSIM_H
#define EX5_PARSERSIM_H

#include "Counter.h"
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>

class ParserSim {
public:
    ParserSim() {}
    ~ParserSim() {}
    void run();
private:
    std::vector<Counter<std::string> >string_counter;
    std::vector<Counter<int> >int_counter;
    void inputHandling();
    int counterIsExist(std::string &name,int &type);
    ParserSim(const ParserSim &s):string_counter(s.string_counter),int_counter(s.int_counter){}
    ParserSim& operator=(const ParserSim &s);//dont need

};


#endif //EX5_PARSERSIM_H
