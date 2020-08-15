
//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "catch.hpp"
#include "georithm/Line.hpp"
#include "georithm/Vector.hpp"
#include "georithm/Intersection.hpp"
#include "georithm/Intersects.hpp"
#include "georithm/Rect.hpp"
#include "georithm/Bounding.hpp"
#include "georithm/Contains.hpp"
#include "georithm/Utility.hpp"

#include "georithm/transform/Scale.hpp"
#include "georithm/transform/Translate.hpp"
#include "georithm/transform/Rotate.hpp"
#include "georithm/transform/Shear.hpp"

//TEST_CASE("Line constexpr compile test", "[Line]")
//{
//	using namespace georithm;
//}

TEST_CASE("Rect compile and basic test", "[Rect]")
{
	using namespace georithm;

	using Vector2f = Vector<float, 2>;
	AABB_t<float> rect;
	REQUIRE(rect.isNull());

	rect.span() = { 1.f, 1.f };

	std::array segs
	{
		Segment<Vector2f>{ { 0.f, 0.f }, { 1.f, 0.f } },
		Segment<Vector2f>{ { 1.f, 0.f }, { 0.f, 1.f } },
		Segment<Vector2f>{ { 1.f, 1.f }, { -1.f, 0.f } },
		Segment<Vector2f>{ { 0.f, 1.f }, { 0.f, -1.f } }
	};

	for (std::size_t i = 0; i < edgeCount(rect); ++i)
	{
		REQUIRE(segs[i] == edge(rect, i));
	}

	//Vector2f vec{ 1.f, 1.f };
	//line.location() = vec;
	//REQUIRE(line.location() == vec);
	//vec = { 1.f, 2.f };
	//line.direction() = vec;
	//REQUIRE(line.direction() == vec);

	//REQUIRE(line[0] == line.location());
	//REQUIRE(line[1] == (line.direction() + line.location()));
	//REQUIRE(!line.isNull());

	//REQUIRE(line.vertexCount() == 2u);

	//auto lineSec = line;
	//REQUIRE(lineSec == line);
	//lineSec.location() += 2;
	//line = lineSec;
	//REQUIRE(lineSec == line);
}

TEST_CASE("Rect intersection test", "[Rect]")
{
	using namespace georithm;

	using Vector2f = Vector<float, 2>;
	AABB_t<float> rect{ {1.f, 1.f} };

	REQUIRE(intersects(rect.edge(0), rect));
	REQUIRE(intersects(rect, rect.edge(0)));
	REQUIRE(intersects(rect, rect));

	//auto result = intersection(rect, rect.edge(1));

	//forEachIntersection(rect, rect.edge(0), [](const auto& line, auto dist) {});

	REQUIRE(contains(rect, rect.span() / 2));
	REQUIRE(contains(rect, Vector2f{ 0.f, 0.5f }));
	REQUIRE(contains(rect, rect.span()));
	REQUIRE_FALSE(contains(rect, rect.span() + Vector2f{ 0.00001f, 0.f }));

	//lengthSq(rect.span());
	//std::array<int, 10> arr;
	//zip_elements(std::begin(arr), std::end(arr), std::begin(arr), [](auto lhs, auto rhs) { return lhs + rhs; });

	//Line<Vector<float, 2>> line{ Vector{ 1.f, 2.f }, Vector{ 1.f, 1.f} };
	//auto line2 = line;
	//auto interResult = intersection(line, line);
	//REQUIRE(std::get<0>(interResult) == LineIntersectionResult::collinear);
	//REQUIRE(std::get<1>(interResult) == std::nullopt);

	//line2.direction() = line2.direction() * (-1);
	//interResult = intersection(line, line2);
	//REQUIRE(std::get<0>(interResult) == LineIntersectionResult::collinear);
	//REQUIRE(std::get<1>(interResult) == std::nullopt);

	//line2.location() = { -1.f, 5.f };
	//interResult = intersection(line, line2);
	//REQUIRE(std::get<0>(interResult) == LineIntersectionResult::parallel);
	//REQUIRE(std::get<1>(interResult) == std::nullopt);
	//REQUIRE(!intersects(line, line2));

	//line2.direction().x() += 0.1f;
	//REQUIRE(intersects(line, line2));
}

TEST_CASE("Rect contains test - float", "[Rect]")
{
	using namespace georithm;

	using Vector2f = Vector<float, 2>;
	AABB_t<float> rect{ {1.f, 1.f} };

	REQUIRE(contains(rect, rect.span() / 2));
	REQUIRE(contains(rect, Vector2f{ 0.f, 0.5f }));
	REQUIRE(contains(rect, rect.span()));
	REQUIRE_FALSE(contains(rect, Vector2f{ -0.00001f, 0.f }));
	REQUIRE_FALSE(contains(rect, Vector2f{ 0.f, -0.00001f }));
	REQUIRE_FALSE(contains(rect, Vector2f{ -0.00001f, -0.00001f }));
	REQUIRE_FALSE(contains(rect, Vector2f{ -0.00001f, 0.00001f }));
	REQUIRE_FALSE(contains(rect, Vector2f{ 0.00001f, -0.00001f }));
	REQUIRE_FALSE(contains(rect, rect.span() + Vector2f{ 0.00001f, 0.f }));
	REQUIRE_FALSE(contains(rect, rect.span() + Vector2f{ 0.f, 0.00001f }));
	REQUIRE_FALSE(contains(rect, rect.span() + Vector2f{ 0.00001f, 0.00001f }));
	REQUIRE_FALSE(contains(rect, rect.span() + Vector2f{ 0.00001f, -0.00001f }));
	REQUIRE_FALSE(contains(rect, rect.span() + Vector2f{ -0.00001f, 0.00001f }));
}

TEST_CASE("Rect contains test - int", "[Rect]")
{
	using namespace georithm;

	using Vector2 = Vector<int, 2>;
	AABB_t<int> rect{ { 7, 5 } };

	REQUIRE(contains(rect, rect.span() / 2));
	REQUIRE(contains(rect, Vector2{ 0, 2 }));
	REQUIRE(contains(rect, rect.span()));
	REQUIRE_FALSE(contains(rect, Vector2{ -1, 0 }));
	REQUIRE_FALSE(contains(rect, Vector2{ 0, -1 }));
	REQUIRE_FALSE(contains(rect, Vector2{ -1, -1 }));
	REQUIRE_FALSE(contains(rect, Vector2{ -1, 1 }));
	REQUIRE_FALSE(contains(rect, Vector2{ 1, -1 }));
	REQUIRE_FALSE(contains(rect, rect.span() + Vector2{ 0, 1 }));
	REQUIRE_FALSE(contains(rect, rect.span() + Vector2{ 1, 0 }));
	REQUIRE_FALSE(contains(rect, rect.span() + Vector2{ 1, 1 }));
	REQUIRE_FALSE(contains(rect, rect.span() + Vector2{ -1, 1 }));
	REQUIRE_FALSE(contains(rect, rect.span() + Vector2{ 1, -1 }));
}

TEST_CASE("Rect make bounding rect test", "[Rect]")
{
	using namespace georithm;

	using Vector2 = Vector<int, 2>;
	AABB_t<int> rect{ {1, 1} };

	auto bb = makeBoundingRect(rect);

	REQUIRE(!(rect != bb));

	AABB_t<int> transRect{ { 10, 10 }, { -5, -5 } };
	bb = makeBoundingRect(transRect);
	REQUIRE(transRect != bb);
	REQUIRE(bb.position() == transRect.position() + transRect.span());
	REQUIRE(bb.position() == abs(transRect.span()));
}

TEST_CASE("Rect transform tests", "[Rect]")
{
	using namespace georithm;

	using Vector2F_t = Vector<float, 2>;

	SECTION("translate")
	{
		Rect<float, transform::Translate<Vector2F_t>> rect{ {1.f, 1.f} };

		SECTION("zero")
		{
			auto bb = makeBoundingRect(rect);
			REQUIRE(bb.position() == Vector2F_t::zero());
			REQUIRE(bb.span() == Vector2F_t{ 1.f, 1.f });
		}

		SECTION("not zero")
		{
			Vector2F_t position;
			Vector2F_t translation{ -3.f, 5.f };
			
			SECTION("position 0/0 move bottom right")
			{
			}

			SECTION("position 5/3 move bottom right")
			{
				position = { 5.f, 3.f };
			}

			SECTION("position 0/0 move top left")
			{
				translation *= -1.f;
			}

			SECTION("position 5/3 move top left")
			{
				translation *= -1.f;
				position = { 5.f, 3.f };
			}

			rect.translation() = position;
			rect.position() = position;
			auto bb = makeBoundingRect(rect);
			REQUIRE(bb.position() == position + position);
			REQUIRE(bb.span() == Vector2F_t{ 1.f, 1.f });
		}
	}

	SECTION("scale")
	{
		Rect<float, transform::Scale<Vector2F_t>> rect{ {1.f, 1.f} };

		SECTION("1:1")
		{
			auto bb = makeBoundingRect(rect);
			REQUIRE(bb.position() == Vector2F_t::zero());
			REQUIRE(bb.span() == Vector2F_t{ 1.f, 1.f });
		}

		SECTION("mirror")
		{
			rect.scale() = { -1.f, -1.f };
			auto bb = makeBoundingRect(rect);
			REQUIRE(bb.position() == Vector2F_t{ -1.f, -1.f });
			REQUIRE(bb.span() == Vector2F_t{ 1.f, 1.f });
		}

		SECTION("downscale")
		{
			rect.scale() = { 0.5f, 0.3f };
			auto bb = makeBoundingRect(rect);
			REQUIRE(bb.position() == Vector2F_t::zero());
			REQUIRE(bb.span() == Vector2F_t{ 0.5f, 0.3f });
		}

		SECTION("upscale")
		{
			rect.scale() = { 3.f, 2.f };
			auto bb = makeBoundingRect(rect);
			REQUIRE(bb.position() == Vector2F_t::zero());
			REQUIRE(bb.span() == Vector2F_t{ 3.f, 2.f });
		}
	}

	SECTION("rotate")
	{
		Rect<float, transform::Rotate<Vector2F_t>> rect{ {1.f, 1.f} };
		Rect<int, transform::Rotate<Vector<int, 2>>> iRect{ {1, 1 } };

		auto rotation = iRect.rotation();

		SECTION("1:1")
		{
			auto bb = makeBoundingRect(rect);
			REQUIRE(bb.position() == Vector2F_t::zero());
			REQUIRE(bb.span() == Vector2F_t{ 1.f, 1.f });
		}

		//SECTION("mirror")
		//{
		//	rect.scale() = { -1.f, -1.f };
		//	auto bb = makeBoundingRect(rect);
		//	REQUIRE(bb.position() == Vector2F_t{ -1.f, -1.f });
		//	REQUIRE(bb.span() == Vector2F_t{ 1.f, 1.f });
		//}

		//SECTION("downscale")
		//{
		//	rect.scale() = { 0.5f, 0.3f };
		//	auto bb = makeBoundingRect(rect);
		//	REQUIRE(bb.position() == Vector2F_t::zero());
		//	REQUIRE(bb.span() == Vector2F_t{ 0.5f, 0.3f });
		//}

		//SECTION("upscale")
		//{
		//	rect.scale() = { 3.f, 2.f };
		//	auto bb = makeBoundingRect(rect);
		//	REQUIRE(bb.position() == Vector2F_t::zero());
		//	REQUIRE(bb.span() == Vector2F_t{ 3.f, 2.f });
		//}
	}

	SECTION("shear")
	{
		Rect<float, transform::Shear<Vector2F_t>> rect{ {1.f, 1.f} };
		//Rect<int, transform::Rotate<Vector<int, 2>>> iRect{ {1, 1 } };

		SECTION("zero")
		{
			auto bb = makeBoundingRect(rect);
			REQUIRE(bb.position() == Vector2F_t::zero());
			REQUIRE(bb.span() == Vector2F_t{ 1.f, 1.f });
		}

		SECTION("x20")
		{
			rect.shear() = { 20.f, 0.f };
			
			auto bb = makeBoundingRect(rect);
			REQUIRE(bb.position() == Vector2F_t::zero());
			REQUIRE(bb.span() == Vector2F_t{ 21.f, 1.f });
			REQUIRE(vertex(rect, 3) == Vector2F_t{ 20.f, 1.f });
		}

		//SECTION("mirror")
		//{
		//	rect.scale() = { -1.f, -1.f };
		//	auto bb = makeBoundingRect(rect);
		//	REQUIRE(bb.position() == Vector2F_t{ -1.f, -1.f });
		//	REQUIRE(bb.span() == Vector2F_t{ 1.f, 1.f });
		//}

		//SECTION("downscale")
		//{
		//	rect.scale() = { 0.5f, 0.3f };
		//	auto bb = makeBoundingRect(rect);
		//	REQUIRE(bb.position() == Vector2F_t::zero());
		//	REQUIRE(bb.span() == Vector2F_t{ 0.5f, 0.3f });
		//}

		//SECTION("upscale")
		//{
		//	rect.scale() = { 3.f, 2.f };
		//	auto bb = makeBoundingRect(rect);
		//	REQUIRE(bb.position() == Vector2F_t::zero());
		//	REQUIRE(bb.span() == Vector2F_t{ 3.f, 2.f });
		//}
	}

	//AABB_t<int> transRect{ { 10, 10 }, { -5, -5 } };
	//bb = makeBoundingRect(transRect);
	//REQUIRE(transRect != bb);
	//REQUIRE(bb.position() == transRect.position() + transRect.span());
	//REQUIRE(bb.position() == abs(transRect.span()));
}
