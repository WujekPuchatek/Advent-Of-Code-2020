#pragma once

#include <set>
#include <cassert>
#include <fstream>
#include <optional>
#include <iostream>
#include <execution>
#include <algorithm>
#include <string_view>

using Numbers = std::set<unsigned>;

Numbers ReadInputsFromFile(std::string_view filepath)
{
    auto numbers{ Numbers() };

    auto file{ std::ifstream(filepath.data()) };

    unsigned number{};
    while (file >> number)
        numbers.insert(number);

    return numbers;
}

auto CalculateRestToDesiredNumber(const unsigned expectedNumber, const unsigned val)
{
    return expectedNumber - val;
}

auto CalculateRestTo2020 (const unsigned val)
{ 
    return CalculateRestToDesiredNumber(2020u, val);
};

std::optional<std::tuple<unsigned, unsigned>> FindTheTwoEntriesThatSumToDesiredNumber(const unsigned expectedNumber, const Numbers& numbers)
{
    auto predicate = [&](const auto val) { return numbers.contains(CalculateRestToDesiredNumber(expectedNumber, val)); };
    auto numberIt = std::find_if(numbers.cbegin(), numbers.cend(), predicate);

    if (numberIt != numbers.cend())
        return std::tuple(*numberIt, CalculateRestToDesiredNumber(expectedNumber, *numberIt));
    else
        return std::nullopt;
}

auto FindTheTwoEntriesThatSumTo2020(const Numbers& numbers)
{
    return FindTheTwoEntriesThatSumToDesiredNumber(2020u, numbers).value();
}

constexpr const static auto MultiplyAllElements = [](auto&&... numbers)
{
    return (numbers * ...);
};

auto FindTheTripletThatSumTo2020(const Numbers& numbers)
{
    std::tuple<unsigned, unsigned, unsigned> triplet{};

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
