#include <iostream>
#include "../CPP API/API.h"

int main()
{
    set_dimensions(400, 600);
    plot_scatter(new double[3] {1, 5, 10}, new double[3] {2,3,2}, (char*)"C:/Users/benny/Desktop/b.png", 3);
}
