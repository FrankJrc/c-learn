#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include "strategy.h"
#include "Poly.h"
using namespace std;
mutex mtx;
template<typename T>
auto print(const T&) -> typename enable_if<is_prod<T>::value, bool>::type
{
    cout << "prod ";
    return true;
}

template<typename T>
auto print(const T&) -> typename enable_if<!is_prod<T>::value, bool>::type
{
    cout << "non prod ";
    return false;
}

class Dummy{
private:
    int _id{0};

public:
    Dummy(int id) : _id(id){}

    void print(int x)
    {
        //lock_guard implements RAII
        //in its destructor, it automatically release the lock.
        //so this is exception safe as well
        std::lock_guard<std::mutex> lock(mtx);
        cout << "my id is " << _id << ", now setting new id to " << x << endl;
        _id = x;
    }

    int id(){
        return _id;
    }
};

int main()
{
    atomic_bool execute{true};
    atomic_llong c{0};
    vector<thread> threads;

    Dummy d{1};
    auto func = [&](){
            int local = 0;
            while(execute)
            {
                ++c;
                ++local;
            }
            mtx.lock();
            cout << "thread executed " << local << "times" << endl;
            mtx.unlock();
        };
    //we have to capture by reference. otherwise, set bool execute to false has no effect to the catured by value execute in thread
    //thread support only move assignment, not copy assignment

    threads.emplace_back(func);
    threads.push_back(thread(func));

    //we have to use &d or std::ref(d), other wise a copy of d is passed in and invoked on the temp object
    threads.emplace_back(&Dummy::print, ref(d), 10);

    Animal* dog = new Dog();
    Animal* cat = new Cat();
    Animal* blue_cat = new RusianBlue();
    mtx.lock();
    dog->introduce();
    cat->introduce();
    blue_cat->introduce();

    dog->move_forward();
    cat->move_forward();
    blue_cat->move_forward();
    mtx.unlock();
    //because animal's destructor is virtual, we can actually polymoph and destroy concrete types.
    delete dog;
    delete cat;
    delete blue_cat;


    cout << is_prod<TestOM>::value << endl;
    cout << is_prod<ProdOM>::value << endl;

    TestOM test;
    ProdOM prod;

    cout << print(test) << endl;
    cout << print(prod) << endl;

    execute = false;

    for(auto& t:threads)
    {
        mtx.lock();
        cout << "created thread's id is " << t.get_id() << ", main thread id is " << std::this_thread::get_id() << endl;
        mtx.unlock();
        if(t.joinable())
            t.join();
    }

    mtx.lock();
    cout << "thread executed " << c << " times" << endl;
    cout << "d's id is " << d.id() << endl;
    mtx.unlock();
    return 0;
}
