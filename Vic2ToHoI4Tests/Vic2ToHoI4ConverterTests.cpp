#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Vic2ToHoI4/Source/Configuration.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


void getOutputName(const std::string& V2SaveFileName);



namespace ConverterMainTests
{

TEST_CLASS(getOutputNameTests)
{
	public:
		TEST_METHOD(TypeNotSetWhenNotGivenInput)
		{
			std::string inputName = "C:\\Users\\Cosmostarr\\Documents\\Paradox Interactive\\Victoria II\\save games/hoi4.v2";
			getOutputName(inputName);
			Assert::AreEqual(std::string("hoi4.v2"), theConfiguration.getOutputName());
		}
};

}