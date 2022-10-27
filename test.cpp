#include <iostream>
class A
{
    public:
        virtual void a() {};
};

class B : public A
{
    public:
        A el;
        void a() override {};
};

template <class type>
void my_function(A* my_a)
{
	B* my_b = dynamic_cast<type*>(my_a);

	if (my_b == nullptr)
	    std::cout << "Этот объект не является объектом типа B" << std::endl;    
}

int main()
{
    B object_b;

    my_function<B>((A *)&object_b);
}