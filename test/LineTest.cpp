
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
	REQUIRE(line.direction() == Vector2f{ 2.f, 2.f });
	REQUIRE(line.location() == Vector2f{ 1.f, 1.f });

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

TEST_CASE("Ray intersection test", "[Line]")
{
	using namespace georithm;

	Ray<Vector<float, 2>> ray{ Vector{ 1.f, 2.f }, Vector{ 1.f, 1.f} };

	auto interResult = intersection(ray, ray);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::collinear);

	Ray<Vector<float, 2>> ray2{ Vector{ 1.f, 2.f }, Vector{ -1.f, -1.f} };
	interResult = intersection(ray, ray2);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::collinear);

	ray2.location() += ray2.direction() * 0.001;
	interResult = intersection(ray, ray2);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::parallel);

	ray2.direction().x() -= 0.1f;
	interResult = intersection(ray, ray2);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::none);

	ray2.location() = { 1.f, 2.f };
	ray2.direction() = { -1.f, -1.f };
	ray2.direction().x() -= 0.1f;
	interResult = intersection(ray, ray2);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::intersecting);
	REQUIRE(std::get<1>(interResult) == Approx(0));

	ray2.direction() = { -1.f, -1.f };
	ray2.location().x() += 1;
	interResult = intersection(ray, ray2);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::parallel);
}

TEST_CASE("Segment intersection test", "[Line]")
{
	using namespace georithm;

	Segment<Vector<float, 2>> segment{ Vector{ 1.f, 2.f }, Vector{ 1.f, 1.f} };

	auto interResult = intersection(segment, segment);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::collinear);

	Segment<Vector<float, 2>> segment2{ Vector{ 1.f, 2.f }, Vector{ -1.f, -1.f} };
	interResult = intersection(segment, segment2);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::collinear);

	segment2.location() += segment2.direction() * 0.001;
	interResult = intersection(segment, segment2);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::parallel);

	segment2.direction().x() -= 0.1f;
	interResult = intersection(segment, segment2);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::none);

	segment2.location() = { 1.f, 2.f };
	segment2.direction() = { -1.f, -1.f };
	segment2.direction().x() -= 0.1f;
	interResult = intersection(segment, segment2);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::intersecting);
	REQUIRE(std::get<1>(interResult) == Approx(0));

	segment2.direction() = { -1.f, -1.f };
	segment2.location().x() += 1;
	interResult = intersection(segment, segment2);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::parallel);

	segment2.location() = segment.secondVertex();
	segment2.direction() = segment.direction();
	segment2.direction().x() -= 0.1f;
	interResult = intersection(segment, segment2);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::intersecting);
	REQUIRE(std::get<1>(interResult) == Approx(1));

	segment2.location() += segment.direction() * 0.001;
	interResult = intersection(segment, segment2);
	REQUIRE(std::get<0>(interResult) == LineIntersectionResult::none);
}
