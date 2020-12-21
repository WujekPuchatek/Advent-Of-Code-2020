#pragma once

#include <set>
#include <tuple>
#include <optional>
#include <string_view>

using Number = unsigned;
using Numbers = std::set<Number>;

using Doublet = std::tuple<Number, Number>;
using DoubletOpt = std::optional<Doublet>;

using Triplet = std::tuple<Number, Number, Number>;

Numbers ReadInputsFromFile(std::string_view filepath);

Number CalculateRestToDesiredNumber(const Number expectedNumber, const Number val);
Number CalculateRestTo2020(const Number val);

DoubletOpt FindTheTwoEntriesThatSumToDesiredNumber(const Number expectedNumber, const Numbers& numbers);
Doublet FindTheTwoEntriesThatSumTo2020(const Numbers& numbers);

Triplet FindTheTripletThatSumTo2020(const Numbers& numbers);

template<typename Tuple>
Number MultiplyAllElements(const Tuple& tuple)
{
	constexpr auto multiplyAllElems = [](auto&&... numbers)
	{
		return (numbers * ...);
	};
	return std::apply(multiplyAllElems, tuple);
}


