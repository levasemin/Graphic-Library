#include <vector>
#include <stdio.h>

int main()
{
    std::vector<double> vec = {1, 2, 3, 4, 5};
    vec.erase(vec.begin() + 3);
    for (int i = 0; i < vec.size(); i++)
    {
        printf("%f\n", vec[i]);
    }
}