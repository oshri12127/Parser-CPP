//
// Created by Oshri on 21/06/2021.
//

#ifndef EX5_COUNTER_H
#define EX5_COUNTER_H
#include <iostream>
#include <iterator>
#include <map>
#include <stdexcept>
template <class T>
class Counter {
public:
    Counter(const std::string &name) : name(name) {}
    ~Counter() {}
    Counter(const Counter &c):name(c.name),counter(c.counter){}//copy ctor
    Counter& operator=(const Counter &c);
    void clear(){counter.clear();}//clear the counter values.
    void add(const T& value);//add to counter
    const int operator[](const T& value);//return num the instances of the value
    const T most_common();//returns the most common value
    const std::string &getName() const {return name;}//get name of counter
    void add_from_stream(std::istream& in);
    void print_to_stream(std::ostream& out);
    void print_most_common(std::ostream& out);
private:
    std::string name;
    std::map<T, int> counter;


};

template<class T>
void Counter<T>::add(const T &value)
{
    typename std::map<T, int>::iterator it = counter.find(value);
    if (it != counter.end())
    {
        it->second++;
    }
    else
    {
        counter.insert(std::pair<T, int>(value, 1));
    }

}

template<class T>
const int Counter<T>::operator[](const T &value) {
    typename std::map<T, int>::iterator it = counter.find(value);
    if (it != counter.end())
    {
       return it->second;
    }
    else
    {
        return 0;
    }
}

template<class T>
const T Counter<T>::most_common() {
    if(counter.empty()==true)
    {
        std::string error = "Error: Counter is empty";
        throw std::invalid_argument(error);
    }
    typename std::map<T, int>::iterator it=counter.begin();
    typename std::map<T, int>::iterator end=counter.end();
    int max_value = it->second;
    T value = it->first;
    for( ; it != end; ++it) {
        if(it->second >= max_value)
        {
            if(it->second == max_value)
            {
                if(it->first<value)
                {
                    max_value = it->second;
                    value = it->first;
                }
            }
            else
            {
                max_value = it->second;
                value = it->first;
            }
        }
    }
    return value;
}

template<class T>
void Counter<T>::print_most_common(std::ostream& out)
{
    T val=most_common();
    out<<"most common element for counter "<<name<<" is "<<val<<":"<< operator[](val)<<std::endl;
}

template<class T>
void Counter<T>::add_from_stream(std::istream &in)
{
   T tempVal;
    while(in.eof()== false)
    {
        in >> tempVal;
        if (in.fail() == true) {
            std::string error = "Error: Read failed";
            throw std::invalid_argument(error);
        }
        add(tempVal);
    }

}

template<class T>
void Counter<T>::print_to_stream(std::ostream &out)
{
    typename std::map<T, int>::iterator it=counter.begin();
    typename std::map<T, int>::iterator end=counter.end();
    out<<"counter "<<name<<" = { ";
    for( ; it != end; ++it)
    {
    out<<it->first<<":"<<it->second<<" ";
    }
    out<<"}"<<std::endl;
}

template<class T>
Counter<T> &Counter<T>::operator=(const Counter &c) {
    if(this== &c)
        return (*this);
    this->name = c.name;
    this->counter = c.counter;
    return *this;
}


#endif //EX5_COUNTER_H
