/*Copyright (c) 2018 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/UnitMap.h"



TEST(HoI4World_UnitMapTests, defaultUnitMapCategoryIsBlank)
{
	HoI4::UnitMap theMap;
	ASSERT_EQ(std::string(""), theMap.getCategory());
}
TEST(HoI4World_UnitMapTests, defaultUnitMapTypeIsBlank)
{
	HoI4::UnitMap theMap;
	ASSERT_EQ(std::string(""), theMap.getType());
}
TEST(HoI4World_UnitMapTests, defaultUnitMapEquipmentIsBlank)
{
	HoI4::UnitMap theMap;
	ASSERT_EQ(std::string(""), theMap.getEquipment());
}
TEST(HoI4World_UnitMapTests, defaultUnitMapSizeIsZero)
{
	HoI4::UnitMap theMap;
	ASSERT_EQ(0, theMap.getSize());
}
TEST(HoI4World_UnitMapTests, blankUnitMapCategoryRemainsBlank)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t}"
	);
	HoI4::UnitMap theMap(input);
	ASSERT_EQ(std::string(""), theMap.getCategory());
}
TEST(HoI4World_UnitMapTests, blankUnitMapTypeRemainsBlank)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t}"
	);
	HoI4::UnitMap theMap(input);
	ASSERT_EQ(std::string(""), theMap.getType());
}
TEST(HoI4World_UnitMapTests, blankUnitMapEquipmentRemainsBlank)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t}"
	);
	HoI4::UnitMap theMap(input);
	ASSERT_EQ(std::string(""), theMap.getEquipment());
}
TEST(HoI4World_UnitMapTests, blankUnitMapSizeRemainsZero)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t}"
	);
	HoI4::UnitMap theMap(input);
	ASSERT_EQ(0, theMap.getSize());
}
TEST(HoI4World_UnitMapTests, UnitMapCategoryCanBeSet)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t\tcategory = land\n"\
		"\t\t\t}"
	);
	HoI4::UnitMap theMap(input);
	ASSERT_EQ(std::string("land"), theMap.getCategory());
}
TEST(HoI4World_UnitMapTests, UnitMapTypeCanBeSet)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t\ttype = infantry\n"\
		"\t\t\t}"
	);
	HoI4::UnitMap theMap(input);
	ASSERT_EQ(std::string("infantry"), theMap.getType());
}
TEST(HoI4World_UnitMapTests, UnitMapEquipmentCanBeSet)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t\tequipment = infantry_equipment_0\n"\
		"\t\t\t}"
	);
	HoI4::UnitMap theMap(input);
	ASSERT_EQ(std::string("infantry_equipment_0"), theMap.getEquipment());
}
TEST(HoI4World_UnitMapTests, UnitMapSizeCanBeSet)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t\tsize = 3\n"\
		"\t\t\t}"
	);
	HoI4::UnitMap theMap(input);
	ASSERT_EQ(3, theMap.getSize());
}