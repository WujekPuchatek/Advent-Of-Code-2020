#include "Helpers.h"

#include <fstream>
#include <execution>
#include <algorithm>

Numbers ReadInputsFromFile(std::string_view filepath)
{
    auto numbers{ Numbers() };

    auto file{ std::ifstream(filepath.data()) };

    Number number{};
    while (file >> number)
        numbers.insert(number);

    return numbers;
}

Number CalculateRestToDesiredNumber(const Number expectedNumber, const Number val)
{
    return expectedNumber - val;
}

Number CalculateRestTo2020(const Number val)
{
    return CalculateRestToDesiredNumber(2020u, val);
};

DoubletOpt FindTheTwoEntriesThatSumToDesiredNumber(const Number expectedNumber, const Numbers& numbers)
{
    auto predicate = [&](const auto val) { return numbers.contains(CalculateRestToDesiredNumber(expectedNumber, val)); };
    auto numberIt = std::find_if(numbers.cbegin(), numbers.cend(), predicate);

    if (numberIt != numbers.cend())
        return Doublet(*numberIt, CalculateRestToDesiredNumber(expectedNumber, *numberIt));
    else
        return std::nullopt;
}

Doublet FindTheTwoEntriesThatSumTo2020(const Numbers& numbers)
{
    return FindTheTwoEntriesThatSumToDesiredNumber(2020u, numbers).value();
}

Triplet FindTheTripletThatSumTo2020(const Numbers& numbers)
{
    Triplet triplet{};

    std::for_each(
        std::execution::par_unseq,
        numbers.cbegin(), numbers.cend(),
        [&numbers, &triplet](const auto number)
        {
            auto restTo2020 = CalculateRestTo2020(number);
            const auto twoNumbersOpt = FindTheTwoEntriesThatSumToDesiredNumber(restTo2020, numbers);

            if (twoNumbersOpt.has_value())
            {
                const auto& twoNumbers = twoNumbersOpt.value();
                triplet = { number, std::get<0>(twoNumbers), std::get<1>(twoNumbers) };
            }
        });

    return triplet;
}