#ifndef BINARY_SEARCH_DEMO_H
#define BINARY_SEARCH_DEMO_H
#include <iostream>
#include <vector>
#include <algorithm>
class demo
{
public:
    virtual ~demo(){}
    virtual void run()=0;
};

class binary_search_demo : public demo
{
    public:
        binary_search_demo();
        virtual ~binary_search_demo();
        void run() override;
    protected:

    private:
};

#endif // BINARY_SEARCH_DEMO_H
