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
#include "../Vic2ToHoI4/Source/Configuration.h"



void setOutputName(const std::string& V2SaveFileName);



/*TEST_CLASS_INITIALIZE(ConverterMainTestsClassInitialization)
{
	ConfigurationFile("configuration.txt");
}
TEST_INITIALIZE(ConverterMainTestsMethodInitialization)
{
	theConfiguration.setOutputName("");
}*/

TEST(setOutputNameTests, filenameEmptyWhenGivenNoInput)
{
	std::string inputName = "";
	setOutputName(inputName);
	ASSERT_EQ(std::string(""), theConfiguration.getOutputName());
}

TEST(setOutputNameTests, filenameCorrectWhenSimplyAName)
{
	std::string inputName = "hoi4.v2";
	setOutputName(inputName);
	ASSERT_EQ(std::string("hoi4"), theConfiguration.getOutputName());
}

TEST(setOutputNameTests, filenameExtractedWithWindowsPath)
{
	std::string inputName = "C:\\Users\\Cosmostarr\\Documents\\Paradox Interactive\\Victoria II\\save games\\hoi4.v2";
	setOutputName(inputName);
	ASSERT_EQ(std::string("hoi4"), theConfiguration.getOutputName());
}

TEST(setOutputNameTests, filenameExtractedWithLinuxPath)
{
	std::string inputName = "/Users/Cosmostarr/Documents/Paradox Interactive/Victoria II/save games/hoi4.v2";
	setOutputName(inputName);
	ASSERT_EQ(std::string("hoi4"), theConfiguration.getOutputName());
}

TEST(setOutputNameTests, filenameExtractedWithMixedPathEndingLinuxStyle)
{
	std::string inputName = "C:\\Users\\Cosmostarr\\Documents\\Paradox Interactive\\Victoria II\\save games/hoi4.v2";
	setOutputName(inputName);
	ASSERT_EQ(std::string("hoi4"), theConfiguration.getOutputName());
}

TEST(setOutputNameTests, filenameExtractedWithMixedPathEndingWindowsStyle)
{
	std::string inputName = "/Users/Cosmostarr/Documents/Paradox Interactive/Victoria II/save games\\hoi4.v2";
	setOutputName(inputName);
	ASSERT_EQ(std::string("hoi4"), theConfiguration.getOutputName());
}

TEST(setOutputNameTests, filenameHasDashesReplaced)
{
	std::string inputName = "hoi4-something.v2";
	setOutputName(inputName);
	ASSERT_EQ(std::string("hoi4_something"), theConfiguration.getOutputName());
}

TEST(setOutputNameTests, filenameHasSpacesReplaced)
{
	std::string inputName = "hoi4 something.v2";
	setOutputName(inputName);
	ASSERT_EQ(std::string("hoi4_something"), theConfiguration.getOutputName());
}

TEST(setOutputNameTests, filenameHasNoExtension)
{
	std::string inputName = "hoi4";
	EXPECT_THROW(setOutputName(inputName), std::invalid_argument);
}

TEST(setOutputNameTests, filenameHasAnInvalidExtension)
{
	std::string inputName = "hoi4.eu4";
	EXPECT_THROW(setOutputName(inputName), std::invalid_argument);
}