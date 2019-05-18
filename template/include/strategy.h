#ifndef STRATEGY_H
#define STRATEGY_H
#include <iostream>
#include <type_traits>
class TestOM;
template<typename T>
struct is_prod : std::true_type
{

};
template<>
struct is_prod<TestOM> : std::false_type
{

};
class TestOM
{
public:
    void print(){
        std::cout << "this is a test om" << std::endl;
    }

};

class ProdOM
{
public:
    void print(){
        std::cout << "this is a prod om" << std::endl;
    }

    void print2(){
        std::cout << "this is another prod om" << std::endl;
    }
};

template<typename OM>
class strategy
{
    public:
        template<typename D>
        void print2(D d)
        {
            d.print2();
        }
        void print2(TestOM om)
        {
            om.print();
        }
        void print();

        OM om_;
};
template class strategy<TestOM>;
template class strategy<ProdOM>;
#endif // STRATEGY_H
