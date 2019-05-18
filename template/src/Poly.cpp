
#include "Poly.h"

void Dog::move_forward()
{
    std::cout << "dog moving forward" << std::endl;
}

void Cat::introduce() const
{
    std::cout << "this is a cat" << std::endl;
}

void RusianBlue::introduce() const
{
    std::cout << "this is a cat and russian blue" << std::endl;
}

void RusianBlue::move_forward()
{
    std::cout << "russian blue moving forward" << std::endl;
}
