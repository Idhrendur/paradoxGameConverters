#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;



namespace HoI4WorldTests
{

TEST_CLASS(MilitaryMappingsTests)
{
	public:
		TEST_METHOD(defaultUnitMapCategoryIsBlank)
		{
			HoI4::UnitMap theMap;
			Assert::AreEqual(std::string(""), theMap.getCategory());
		}
		TEST_METHOD(defaultUnitMapTypeIsBlank)
		{
			HoI4::UnitMap theMap;
			Assert::AreEqual(std::string(""), theMap.getType());
		}
		TEST_METHOD(defaultUnitMapEquipmentIsBlank)
		{
			HoI4::UnitMap theMap;
			Assert::AreEqual(std::string(""), theMap.getEquipment());
		}
		TEST_METHOD(defaultUnitMapSizeIsZero)
		{
			HoI4::UnitMap theMap;
			Assert::AreEqual(0, theMap.getSize());
		}
		TEST_METHOD(blankUnitMapCategoryRemainsBlank)
		{
			std::stringstream input(
				"= {\n"\
				"\t\t\t}"
			);
			HoI4::UnitMap theMap(input);
			Assert::AreEqual(std::string(""), theMap.getCategory());
		}
		TEST_METHOD(blankUnitMapTypeRemainsBlank)
		{
			std::stringstream input(
				"= {\n"\
				"\t\t\t}"
			);
			HoI4::UnitMap theMap(input);
			Assert::AreEqual(std::string(""), theMap.getType());
		}
		TEST_METHOD(blankUnitMapEquipmentRemainsBlank)
		{
			std::stringstream input(
				"= {\n"\
				"\t\t\t}"
			);
			HoI4::UnitMap theMap(input);
			Assert::AreEqual(std::string(""), theMap.getEquipment());
		}
		TEST_METHOD(blankUnitMapSizeRemainsZero)
		{
			std::stringstream input(
				"= {\n"\
				"\t\t\t}"
			);
			HoI4::UnitMap theMap(input);
			Assert::AreEqual(0, theMap.getSize());
		}
		TEST_METHOD(UnitMapCategoryCanBeSet)
		{
			std::stringstream input(
				"= {\n"\
				"\t\t\t\tcategory = land\n"\
				"\t\t\t\ttype = infantry\n"\
				"\t\t\t\tequipment = infantry_equipment_0\n"\
				"\t\t\t\tsize = 3\n"\
				"\t\t\t}"
			);
			HoI4::UnitMap theMap(input);
			Assert::AreEqual(std::string("land"), theMap.getCategory());
		}
		TEST_METHOD(UnitMapTypeCanBeSet)
		{
			std::stringstream input(
				"= {\n"\
				"\t\t\t\tcategory = land\n"\
				"\t\t\t\ttype = infantry\n"\
				"\t\t\t\tequipment = infantry_equipment_0\n"\
				"\t\t\t\tsize = 3\n"\
				"\t\t\t}"
			);
			HoI4::UnitMap theMap(input);
			Assert::AreEqual(std::string("infantry"), theMap.getType());
		}
		TEST_METHOD(UnitMapEquipmentCanBeSet)
		{
			std::stringstream input(
				"= {\n"\
				"\t\t\t\tcategory = land\n"\
				"\t\t\t\ttype = infantry\n"\
				"\t\t\t\tequipment = infantry_equipment_0\n"\
				"\t\t\t\tsize = 3\n"\
				"\t\t\t}"
			);
			HoI4::UnitMap theMap(input);
			Assert::AreEqual(std::string("infantry_equipment_0"), theMap.getEquipment());
		}
		TEST_METHOD(UnitMapSizeCanBeSet)
		{
			std::stringstream input(
				"= {\n"\
				"\t\t\t\tcategory = land\n"\
				"\t\t\t\ttype = infantry\n"\
				"\t\t\t\tequipment = infantry_equipment_0\n"\
				"\t\t\t\tsize = 3\n"\
				"\t\t\t}"
			);
			HoI4::UnitMap theMap(input);
			Assert::AreEqual(3, theMap.getSize());
		}
		TEST_METHOD(emptyUnitMappingStaysEmpty)
		{
			std::stringstream input(
				"= {\n"\
				"\tmap = {\n"\
				"\t}"\
				"}"
			);
			HoI4::militaryMappings theMappings(input);
			Assert::AreEqual(size_t(0), theMappings.getUnitMap().size());
		}
		TEST_METHOD(Vic2UnitAddedToUnitMapping)
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
			HoI4::militaryMappings theMappings(input);
			Assert::AreEqual(size_t(1), theMappings.getUnitMap().count("irregular"));
		}
		TEST_METHOD(UnitMappingHandlesBlankHoI4UnitTypeCorrectly)
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
			HoI4::militaryMappings theMappings(input);
			Assert::AreEqual(std::string(""), theMappings.getUnitMap().at("irregular").getType());
		}
		TEST_METHOD(UnitMappingHandlesFilledHoI4UnitTypeCorrectly)
		{
			std::stringstream input(
				"= {\n"\
				"\tmap = {\n"\
				"\t\tlink = {\n"\
				"\t\t\tvic = infantry\n"\
				"\t\t\thoi = {\n"\
				"\t\t\t\ttype = land\n"\
				"\t\t\t\tunit = infantry\n"\
				"\t\t\tequipment = infantry_equipment_0\n"\
				"\t\t\tsize = 3\n"\
				"\t\t\t}\n"\
				"\t\t}\n"\
				"\t}"\
				"}"
			);
			HoI4::militaryMappings theMappings(input);
			Assert::AreEqual(std::string("land"), theMappings.getUnitMap().at("infantry").getType());
		}
		TEST_METHOD(allDivisionTemplatesInMapping)
		{
			std::stringstream input(
				"= {"\
				"\tdivision_templates = {"\
				"\t}"\
				"}"
			);
			HoI4::militaryMappings theMappings(input);
			Assert::AreEqual(size_t(11), theMappings.getDivisionTemplates().size());
		}
		TEST_METHOD(getDefaultMappingsWithNoMods)
		{
			HoI4::allMilitaryMappings allTheMappings;
			std::vector<std::string> mods;
			auto specificMappings = allTheMappings.getMilitaryMappings(mods);
			Assert::AreEqual(size_t(21), specificMappings.getUnitMap().size());
		}
		TEST_METHOD(getDefaultMappingsWithInvalidMod)
		{
			HoI4::allMilitaryMappings allTheMappings;
			std::vector<std::string> mods = { "NotAMod" };
			auto specificMappings = allTheMappings.getMilitaryMappings(mods);
			Assert::AreEqual(size_t(21), specificMappings.getUnitMap().size());
		}
		TEST_METHOD(getPDMMappingsWithPDM)
		{
			HoI4::allMilitaryMappings allTheMappings;
			std::vector<std::string> mods = { "PDM" };
			auto specificMappings = allTheMappings.getMilitaryMappings(mods);
			Assert::AreEqual(size_t(24), specificMappings.getUnitMap().size());
		}
};

}