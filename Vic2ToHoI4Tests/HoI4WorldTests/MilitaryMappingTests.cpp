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
#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings.h"



TEST(HoI4World_militaryMappingsTests, defaultUnitMapCategoryIsBlank)
{
	HoI4::UnitMap theMap;
	ASSERT_EQ(std::string(""), theMap.getCategory());
}
TEST(HoI4World_militaryMappingsTests, defaultUnitMapTypeIsBlank)
{
	HoI4::UnitMap theMap;
	ASSERT_EQ(std::string(""), theMap.getType());
}
TEST(HoI4World_militaryMappingsTests, defaultUnitMapEquipmentIsBlank)
{
	HoI4::UnitMap theMap;
	ASSERT_EQ(std::string(""), theMap.getEquipment());
}
TEST(HoI4World_militaryMappingsTests, defaultUnitMapSizeIsZero)
{
	HoI4::UnitMap theMap;
	ASSERT_EQ(0, theMap.getSize());
}
TEST(HoI4World_militaryMappingsTests, blankUnitMapCategoryRemainsBlank)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t}"
	);
	HoI4::UnitMap theMap(input);
	ASSERT_EQ(std::string(""), theMap.getCategory());
}
TEST(HoI4World_militaryMappingsTests, blankUnitMapTypeRemainsBlank)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t}"
	);
	HoI4::UnitMap theMap(input);
	ASSERT_EQ(std::string(""), theMap.getType());
}
TEST(HoI4World_militaryMappingsTests, blankUnitMapEquipmentRemainsBlank)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t}"
	);
	HoI4::UnitMap theMap(input);
	ASSERT_EQ(std::string(""), theMap.getEquipment());
}
TEST(HoI4World_militaryMappingsTests, blankUnitMapSizeRemainsZero)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t}"
	);
	HoI4::UnitMap theMap(input);
	ASSERT_EQ(0, theMap.getSize());
}
TEST(HoI4World_militaryMappingsTests, UnitMapCategoryCanBeSet)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t\tcategory = land\n"\
		"\t\t\t}"
	);
	HoI4::UnitMap theMap(input);
	ASSERT_EQ(std::string("land"), theMap.getCategory());
}
TEST(HoI4World_militaryMappingsTests, UnitMapTypeCanBeSet)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t\ttype = infantry\n"\
		"\t\t\t}"
	);
	HoI4::UnitMap theMap(input);
	ASSERT_EQ(std::string("infantry"), theMap.getType());
}
TEST(HoI4World_militaryMappingsTests, UnitMapEquipmentCanBeSet)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t\tequipment = infantry_equipment_0\n"\
		"\t\t\t}"
	);
	HoI4::UnitMap theMap(input);
	ASSERT_EQ(std::string("infantry_equipment_0"), theMap.getEquipment());
}
TEST(HoI4World_militaryMappingsTests, UnitMapSizeCanBeSet)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t\tsize = 3\n"\
		"\t\t\t}"
	);
	HoI4::UnitMap theMap(input);
	ASSERT_EQ(3, theMap.getSize());
}
TEST(HoI4World_militaryMappingsTests, emptyUnitMappingStaysEmpty)
{
	std::stringstream input(
		"= {\n"\
		"\tmap = {\n"\
		"\t}"\
		"}"
	);
	HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(size_t(0), theMappings.getUnitMap().size());
}
TEST(HoI4World_militaryMappingsTests, Vic2UnitAddedToUnitMapping)
{
	std::stringstream input(
		"= {\n"\
		"\tmap = {\n"\
		"\t\tlink = {\n"\
		"\t\t\tvic = irregular\n"\
		"\t\t}\n"\
		"\t}"\
		"}"
	);
	HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(size_t(1), theMappings.getUnitMap().count("irregular"));
}
TEST(HoI4World_militaryMappingsTests, UnitMappingHandlesBlankHoI4UnitTypeCorrectly)
{
	std::stringstream input(
		"= {\n"\
		"\tmap = {\n"\
		"\t\tlink = {\n"\
		"\t\t\tvic = irregular\n"\
		"\t\t}\n"\
		"\t}"\
		"}"
	);
	HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(std::string(""), theMappings.getUnitMap().at("irregular").getType());
}
TEST(HoI4World_militaryMappingsTests, UnitMappingHandlesFilledHoI4UnitTypeCorrectly)
{
	std::stringstream input(
		"= {\n"\
		"\tmap = {\n"\
		"\t\tlink = {\n"\
		"\t\t\tvic = infantry\n"\
		"\t\t\thoi = {\n"\
		"\t\t\t\ttype = land\n"\
		"\t\t\t}\n"\
		"\t\t}\n"\
		"\t}"\
		"}"
	);
	HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(std::string("land"), theMappings.getUnitMap().at("infantry").getType());
}
TEST(HoI4World_militaryMappingsTests, emptyDivisionTemplatesStaysEmpty)
{
	std::stringstream input(
		"= {\n"\
		"\tdivision_templates = {\n"\
		"\t}"\
		"}"
	);
	HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(size_t(0), theMappings.getDivisionTemplates().size());
}
TEST(HoI4World_militaryMappingsTests, TemplateAddedToDivisionTemplateMapping)
{
	std::stringstream input(
		"= {\n"\
		"\tdivision_templates = {\n"\
		"\t\tdivision_template = {\n"\
		"\t\t\tname = \"Light Infantry Brigade\"\n"\
		"\t\t}\n"\
		"\t}"\
		"}"
	);
	HoI4::militaryMappings theMappings("", input);
	auto templates = theMappings.getDivisionTemplates();
	ASSERT_FALSE(std::find(templates.begin(), templates.end(), "Light Infantry Brigade") == templates.end());
}
TEST(HoI4World_militaryMappingsTests, emptySubstitutesStaysEmpty)
{
	std::stringstream input(
		"= {\n"\
		"\tsubstitutes = {\n"\
		"\t}"\
		"}"
	);
	HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(size_t(0), theMappings.getSubstitutes().size());
}
TEST(HoI4World_militaryMappingsTests, substituteAddedToSubstitutes)
{
	std::stringstream input(
		"= {\n"\
		"\tsubstitutes = {\n"\
		"\t\tartillery = artillery_brigade\n"\
		"\t}"\
		"}"
	);
	HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(size_t(1), theMappings.getSubstitutes().size());
}
TEST(HoI4World_militaryMappingsTests, substituteNameInList)
{
	std::stringstream input(
		"= {\n"\
		"\tsubstitutes = {\n"\
		"\t\tartillery = artillery_brigade\n"\
		"\t}"\
		"}"
	);
	HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(size_t(1), theMappings.getSubstitutes().count("artillery"));
}
TEST(HoI4World_militaryMappingsTests, substituteAlternateInMapping)
{
	std::stringstream input(
		"= {\n"\
		"\tsubstitutes = {\n"\
		"\t\tartillery = artillery_brigade\n"\
		"\t}"\
		"}"
	);
	HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(std::string("artillery_brigade"), theMappings.getSubstitutes().at("artillery"));
}