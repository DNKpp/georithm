
//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "catch.hpp"
#include "../include/georithm/Vector.hpp"

TEST_CASE("Vector constexpr compile test", "[Vector]")
{
	using namespace georithm;

	constexpr Vector<float, 2> vec;
	constexpr auto makeVector = [vec]()
	{
		auto tmp = vec;
		tmp += tmp;
		return tmp;
	};

	constexpr auto vec2 = makeVector();
	if constexpr (vec2[0] == 5) {};
}

TEST_CASE("Vector operator test", "[Vector]")
{
	using namespace georithm;

	Vector<int, 2> vec;
	auto vec2 = vec;
	REQUIRE(vec == vec2);
	REQUIRE(!(vec2 != vec));

	vec2 = { 7, 2 };
	REQUIRE(vec2 == Vector{ 7, 2 });
	REQUIRE(vec2.x()== 7);
	REQUIRE(vec2.y() == 2);
	REQUIRE(vec + vec2 == Vector{ 7, 2 });

	Vector real{ 1., 5. };
	auto real2 = real;
	real += real2;
	REQUIRE(real == real2 * 2);
	real -= real2;
	REQUIRE(real == real2);

	real += 1;
	REQUIRE(real == real2 + 1);
	real -= 2;
	REQUIRE(real == real2 - 1);
	real *= 3;
	REQUIRE(real == (real2 - 1) * 3);
	real /= 4;
	REQUIRE(real == ((real2 - 1) * 3) / 4);
	//real %= 5;
	vec2 %= 5;
	REQUIRE(vec2 == Vector{ 2, 2 });
}

TEST_CASE("Vector algorithm test", "[Vector]")
{
	using namespace georithm;

	Vector<int, 2> vec{ 1, 2 };
	REQUIRE(lengthSq(vec) == (vec.x() * vec.x() + vec.y() * vec.y()));
	REQUIRE(scalarProduct(vec, vec) == lengthSq(vec));
	REQUIRE(length(vec) == 2);	// sqrt converted to int
	REQUIRE(length<double>(vec) == Approx(std::sqrt((vec.x() * vec.x() + vec.y() * vec.y()))));

	auto vecf = static_cast<Vector<float, 2>>(vec * (-1));
	REQUIRE(vecf.x() == Approx(-1));
	REQUIRE(vecf.y() == Approx(-2));
	REQUIRE(length(normalize(vecf)) == Approx(1));

	vecf = abs(vecf);
	REQUIRE(vecf.x() == Approx(1));
	REQUIRE(vecf.y() == Approx(2));
	REQUIRE(length(normalize(vecf)) == Approx(1));
}

