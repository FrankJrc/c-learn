#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

#include <future>
using namespace std;

int i = 0;
mutex mtx;
condition_variable cv;

void waiting_function()
{
    unique_lock l(mtx);
    cout << "start to wait" << endl;
    cv.wait(l, []()->bool{return i!=0;});
    cout << "wake up now" << endl;
}

void waiting_function_no_condition()
{
    unique_lock l(mtx);
    cout << "start to wait with no condition" << endl;
    cv.wait(l);
    cout << "no condition wait wake up now" << endl;
}

void notify_function()
{
    this_thread::sleep_for(2s);
    {
        //this will wait up the no condition wait since it does not check value of i.
        std::lock_guard<std::mutex> lg(mtx);
        cout << "first notification" << endl;
        cv.notify_all();
    }

    this_thread::sleep_for(2s);
    {
        std::lock_guard<std::mutex> lg(mtx);
        cout << "second notification" << endl;
        i=1;
        //this wait up the other wait which requires i to not be zero
        cv.notify_all();
    }
}

void promise_thread(promise<int> i, promise<float> f)
{
    this_thread::sleep_for(1s);
    i.set_value(10);

    this_thread::sleep_for(2s);
    f.set_value(1.5f);
}
int main()
{
    thread t(waiting_function);
    this_thread::sleep_for(0.1s);
    thread t2(waiting_function_no_condition);
    this_thread::sleep_for(0.1s);
    thread t1(notify_function);

    if(t.joinable())
        t.join();

    if(t1.joinable())
        t1.join();

    if(t2.joinable())
        t2.join();

    promise<int> p;
    promise<float>f;
    auto future_int = p.get_future();
    auto future_float = f.get_future();
    thread fut_thread(promise_thread, std::move(p), std::move(f));
    future_int.wait();
    cout << "get future integer returned " << future_int.get() << endl;

    future_float.wait();
    cout << "get future float returned " << future_float.get() << endl;
    fut_thread.join();
    cout << "Hello world!" << endl;
    return 0;
}
