#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;



namespace HoI4WorldTests
{

TEST_CLASS(UnitMapTests)
{
	public:
		TEST_METHOD(defaultCategoryIsBlank)
		{
			HoI4::UnitMap theMap;
			Assert::AreEqual(std::string(""), theMap.getCategory());
		}
		TEST_METHOD(defaultTypeIsBlank)
		{
			HoI4::UnitMap theMap;
			Assert::AreEqual(std::string(""), theMap.getType());
		}
		TEST_METHOD(defaultEquipmentIsBlank)
		{
			HoI4::UnitMap theMap;
			Assert::AreEqual(std::string(""), theMap.getEquipment());
		}
		TEST_METHOD(defaultSizeIsZero)
		{
			HoI4::UnitMap theMap;
			Assert::AreEqual(0, theMap.getSize());
		}
		TEST_METHOD(categoryCanBeSet)
		{
			HoI4::UnitMap theMap("category", "type", "equipment", 42);
			Assert::AreEqual(std::string("category"), theMap.getCategory());
		}
		TEST_METHOD(typeCanBeSet)
		{
			HoI4::UnitMap theMap("category", "type", "equipment", 42);
			Assert::AreEqual(std::string("type"), theMap.getType());
		}
		TEST_METHOD(equipmentCanBeSet)
		{
			HoI4::UnitMap theMap("category", "type", "equipment", 42);
			Assert::AreEqual(std::string("equipment"), theMap.getEquipment());
		}
		TEST_METHOD(sizeCanBeSet)
		{
			HoI4::UnitMap theMap("category", "type", "equipment", 42);
			Assert::AreEqual(42, theMap.getSize());
		}
};


TEST_CLASS(MilitaryMappingsTests)
{
	public:
		TEST_METHOD(allUnitsInMapping)
		{
			std::stringstream input(
				"= {"\
				"\tmap = {"\
				"\t}"\
				"}"
			);
			HoI4::militaryMappings theMappings(input);
			Assert::AreEqual(size_t(28), theMappings.getUnitMap().size());
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
};


TEST_CLASS(AllMilitaryMappingsTests)
{
	public:
		TEST_METHOD(getDefaultMappingsWithNoMods)
		{
			HoI4::allMilitaryMappings allTheMappings;
			std::vector<std::string> mods;
			auto specificMappings = allTheMappings.getMilitaryMappings(mods);
			Assert::AreEqual(size_t(28), specificMappings.getUnitMap().size());
		}
		TEST_METHOD(getDefaultMappingsWithInvalidMod)
		{
			HoI4::allMilitaryMappings allTheMappings;
			std::vector<std::string> mods = { "NotAMod" };
			auto specificMappings = allTheMappings.getMilitaryMappings(mods);
			Assert::AreEqual(size_t(28), specificMappings.getUnitMap().size());
		}
		TEST_METHOD(getPDMMappingsWithPDM)
		{
			HoI4::allMilitaryMappings allTheMappings;
			std::vector<std::string> mods = { "PDM" };
			auto specificMappings = allTheMappings.getMilitaryMappings(mods);
			Assert::AreEqual(size_t(28), specificMappings.getUnitMap().size());
		}
};

}