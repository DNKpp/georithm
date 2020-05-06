
//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "catch.hpp"
#include "../include/georithm/Line.hpp"
#include "../include/georithm/Vector.hpp"
#include "../include/georithm/Intersection.hpp"
#include "../include/georithm/Intersects.hpp"

//TEST_CASE("Line constexpr compile test", "[Line]")
//{
//	using namespace georithm;
//}

TEST_CASE("Line compile and basic test", "[Line]")
{
	using namespace georithm;

	using Vector2f = Vector<float, 2>;
	Line<Vector2f> line;
	REQUIRE(line.isNull());
	REQUIRE(line.direction() == Vector2f::zero());
	REQUIRE(line.location() == Vector2f::zero());

	line = Line<Vector2f>{ { 1.f, 1.f }, { 2.f, 2.f } };
	REQUIRE(!line.isNull());
	REQUIRE(line.direction() == Vector2f{ 1.f, 1.f });
	REQUIRE(line.location() == Vector2f{ 2.f, 2.f });

	Vector2f vec{ 1.f, 1.f };
	line.location() = vec;
	REQUIRE(line.location() == vec);
	vec = { 1.f, 2.f };
	line.direction() = vec;
	REQUIRE(line.direction() == vec);

	REQUIRE(line.firstVertex() == line.location());
	REQUIRE(line.secondVertex() == (line.direction() + line.location()));
	REQUIRE(!line.isNull());

	auto lineSec = line;
	REQUIRE(lineSec == line);
	lineSec.location() += 2;
	line = lineSec;
	REQUIRE(lineSec == line);
}

TEST_CASE("Line intersection test", "[Line]")
{
	using namespace georithm;

	Line<Vector<float, 2>> line{ Vector{ 1.f, 2.f }, Vector{ 1.f, 1.f} };
	auto line2 = line;
	auto interResult = intersection(line, line);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::collinear);

	line2.direction() = line2.direction() * (-1);
	interResult = intersection(line, line2);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::collinear);

	line2.location() = { -1.f, 5.f };
	interResult = intersection(line, line2);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::parallel);
	REQUIRE(!intersects(line, line2));

	line2.direction().x() += 0.1f;
	REQUIRE(intersects(line, line2));
}
