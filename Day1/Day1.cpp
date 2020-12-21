#include "Day1.h"

//Part I: assumptions
//1) All numbers in inputs are in range <0, 2020>
//2) Number of inputs number is greater than 2.
//3) There is exactly one pair of numbers which sum is equal to 2020.
//4) Input numbers are located into file Input.txt

//Part II: assumptions
//1) All numbers in inputs are in range <0, 2020>
//2) Number of inputs number is greater than 3.
//3) There is exactly one triplet of numbers which sum is equal to 2020.
//4) Input numbers are located into file Input.txt

int main()
{
    //Part I
    const auto inputs = ReadInputsFromFile("Input.txt");
    const auto pair = FindTheTwoEntriesThatSumTo2020(inputs);
    std::cout << "Part I: " << std::apply(MultiplyAllElements, pair) << std::endl;

    //Part II
    const auto triplet = FindTheTripletThatSumTo2020(inputs);
    std::cout << "Part II: " << std::apply(MultiplyAllElements, triplet) << std::endl;
}
