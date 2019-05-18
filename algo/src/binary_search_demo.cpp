#include "binary_search_demo.h"

binary_search_demo::binary_search_demo()
{
    //ctor
}

binary_search_demo::~binary_search_demo()
{
    //dtor
}

void binary_search_demo::run()
{
    std::cout << "binary demo start" << std::endl;

    std::vector<int> odds{1,2,3,4,5};
    std::for_each(odds.begin(), odds.end(), [](const int& i){std::cout << "vector element is " << i << std::endl;});

    for(int target=0; target<=6; ++target)
    {
        auto left = odds.begin();
        auto right = odds.end();
        bool found = false;
        while(left<right)
        {
            auto mid = left;
            std::advance(mid, (right-left)/2);
            if(*mid == target)
            {
                found = true;
                break;
            }
            else if(*mid < target)
            {
                left = mid+1;
            }
            else
            {
                right = mid;
            }
        }
        if(found)
            std::cout << target << " ok" << std::endl;
        else
            std::cout << target << " fail" << std::endl;
    }


}
