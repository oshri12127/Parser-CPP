//
// Created by Oshri on 21/06/2021.
//

#include "ParserSim.h"

void ParserSim::run()//run the parser
{
    try
    {
        inputHandling();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
        exit(-1);
    }

}

void ParserSim::inputHandling()//input and errors
{
    int type;
    int count;
    std::string line;
    std::string word;
    std::stringstream ss;
    std::string inputArr[256];
    while (std::cin.eof()== false)
    {
        type=0;
        ss.clear();
        count = 0;
        getline(std::cin, line);
        ss<<line;
        if(line==""||line==" ")
            continue;
        while (getline(ss, word, ' ') && count < 256) {
            if(word!="")
                inputArr[count++] = word;
        }
        if(inputArr[0]=="string_counter"||inputArr[0]=="int_counter")
        {
            if(count!=2)
            {
                std::string error = "Error: Missing counter name";
                throw std::invalid_argument(error);
            }
            if(counterIsExist(inputArr[1],type)!=-1)
            {
                std::string error = "Error: Counter name already exists";
                throw std::invalid_argument(error);
            }
            if(inputArr[0]=="string_counter")
            {
                Counter<std::string>tempC(inputArr[1]);
                string_counter.push_back(tempC);
            }
            else//int_counter
            {
                Counter<int>tempC(inputArr[1]);
                int_counter.push_back(tempC);
            }
        }
        else if(inputArr[0]=="add_from_file")
        {
            if(count!=3)
            {
                if(count==1)
                {
                    std::string error = "Error: Missing counter name";
                    throw std::invalid_argument(error);
                }
                if(count==2)
                {
                    std::string error = "Error: Missing file name";
                    throw std::invalid_argument(error);
                }
            }
            int counterIndex=counterIsExist(inputArr[1],type);
            if(counterIndex==-1)//not found
            {
                std::string error = "Error: No counter named "+inputArr[1];
                throw std::invalid_argument(error);
            }

            std::fstream file(inputArr[2].c_str());
            if (file.is_open()==false)
            {
                std::string error = "Error: Failed to open file";
                throw std::invalid_argument(error);
            }
            std::stringstream isInput;
            std::string  line;
            while (std::getline( file, line ))
            {
                isInput << line;
                if(type==1)//string_counter vec
                    string_counter[counterIndex].add_from_stream(isInput);
                if(type==2)//int_counter vec
                    int_counter[counterIndex].add_from_stream(isInput);
                isInput.clear();
            }
            file.close();
        }
        else if(inputArr[0]=="add_from_string")
        {
            if(count<2)
            {
                std::string error = "Error: Missing counter name";
                throw std::invalid_argument(error);
            }
            int counterIndex=counterIsExist(inputArr[1],type);
            if(counterIndex==-1)//not found
            {
                std::string error = "Error: No counter named "+inputArr[1];
                throw std::invalid_argument(error);
            }
            std::stringstream isInput;
            for (int i = 2; i <count ; ++i)
            {
                if(i==2)
                    isInput<<inputArr[i];
                else
                    isInput<<" "<<inputArr[i];
            }
            if(type==1)//string_counter vec
                string_counter[counterIndex].add_from_stream(isInput);
            if(type==2)//int_counter vec
                int_counter[counterIndex].add_from_stream(isInput);
        }
        else if(inputArr[0]=="stats")
        {
            if(count!=2)
            {
                std::string error = "Error: Missing counter name";
                throw std::invalid_argument(error);
            }
            int counterIndex=counterIsExist(inputArr[1],type);
            if(counterIndex==-1)
            {
                std::string error = "Error: No counter named "+inputArr[1];
                throw std::invalid_argument(error);
            }
            if(type==1)//string_counter vec
                string_counter[counterIndex].print_to_stream(std::cout);
            if(type==2)//int_counter vec
                int_counter[counterIndex].print_to_stream(std::cout);

        }
        else if(inputArr[0]=="most_common")
        {
            if(count!=2)
            {
                std::string error = "Error: Missing counter name";
                throw std::invalid_argument(error);
            }
            int counterIndex=counterIsExist(inputArr[1],type);
            if(counterIndex==-1)
            {
                std::string error = "Error: No counter named "+inputArr[1];
                throw std::invalid_argument(error);
            }
            if(type==1)//string_counter vec
                string_counter[counterIndex].print_most_common(std::cout);
            if(type==2)//int_counter vec
                int_counter[counterIndex].print_most_common(std::cout);
        }
        else
        {
            std::string error = "Error: Unknown command "+inputArr[0];
            throw std::invalid_argument(error);
        }

    }
}

int ParserSim::counterIsExist(std::string &name,int &type)//check if counter is exist by name and return there index and type.
{
    for (unsigned int i = 0; i < string_counter.size(); ++i)
    {
        if(name==string_counter[i].getName())
        {
            type=1;//string
            return i;
        }
    }
    for (unsigned int j = 0; j < int_counter.size(); ++j)
    {
        if(name==int_counter[j].getName())
        {
            type=2;//int
            return j;
        }
    }
    return -1;//not found
}


