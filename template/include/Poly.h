#ifndef POLY_H
#define POLY_H

#include <iostream>
class Animal
{
public:
    virtual ~Animal(){
        std::cout << "destroying animal base" << std::endl;
    }

    virtual void introduce() const = 0 ;
    virtual void move_forward(){
        std::cout << "animal moving forward" << std::endl;
    }
};

class Dog final: public Animal
{
public:
    void introduce() const override
    {
        std::cout << "this is a dog" << std::endl;
    }

    void move_forward() override;
    ~Dog(){
        std::cout<< "dog destroyed" << std::endl;
    }
};

class Cat : public Animal{
public:
    void introduce() const override;
    virtual ~Cat()
    {
        std::cout<<"cat destroyed" << std::endl;
    }
};

class RusianBlue : public Cat{
public:
    void introduce() const override;
    void move_forward() override;
    ~RusianBlue()
    {

        std::cout << "blue cat gone" << std::endl;
    }
};

#endif // POLY_H
