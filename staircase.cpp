#include <iostream>
int main();

int main() {

    double x{};
    std::cout << "Enter value of x: ";
    std::cin >> x;

    // This local variable should hold the result of stair( x )
    int stair{};

    // TASK: write code that calculates an integer value
    // corresponding to the value of the function stair( x ) here
    double temp = x / 0.1; //-20
    //std::cout << temp << std::endl;

    if (x > 0) {

        for (; stair <= (temp - 10); stair += 10) {
        }

    } else if (x < 0) {

        for (; stair > temp; stair -= 10) {
        }

    }

    stair = stair / 10;


    std::cout << "The value of stair(x) is: ";
    std::cout << stair;
    std::cout << std::endl;
    std::cout << std::endl;

    return 0;

}