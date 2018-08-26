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



#ifndef HOI4_ARMY_H_
#define HOI4_ARMY_H_



#include <string>
#include <vector>
#include <fstream>



namespace HoI4
{

class RegimentType
{
	public:
		explicit RegimentType(const std::string& type, int x, int y);
		RegimentType(const RegimentType&) = default;

		const std::string getType() const { return type; }

		friend std::ostream& operator << (std::ostream& out, const RegimentType& regiment);

	private:
		RegimentType& operator=(const RegimentType&) = delete;

		std::string	type;
		int x;
		int y;
};


std::ostream& operator << (std::ostream& out, const RegimentType& regiment);


class DivisionTemplateType
{
	public:
		explicit DivisionTemplateType(const std::string& name);
		DivisionTemplateType(const DivisionTemplateType&) = default;
		DivisionTemplateType& operator=(const DivisionTemplateType&) = default;

		friend std::ostream& operator << (std::ostream& out, const DivisionTemplateType& rhs);

		void addRegiment(const RegimentType& newRegiment)			{ regiments.push_back(newRegiment); }
		void addSupportRegiment(const RegimentType& newRegiment)	{ supportRegiments.push_back(newRegiment); }

		std::string getName() const { return name; }

		std::vector<RegimentType> getRegiments() const { return regiments; }
		std::vector<RegimentType> getSupportRegiments() const { return supportRegiments; }

	private:
		std::string name;
		std::vector<RegimentType>	regiments;
		std::vector<RegimentType>	supportRegiments;
};


std::ostream& operator << (std::ostream& out, const DivisionTemplateType& rhs);


class DivisionType
{
	public:
		DivisionType(const std::string& name, const std::string& type, int location);
		DivisionType(const DivisionType&) = default;

		friend std::ostream& operator << (std::ostream& out, const DivisionType&);

	private:
		DivisionType& operator=(const DivisionType&) = delete;

		std::string	name;
		std::string	type;
		int location = 0;
};


std::ostream& operator << (std::ostream& out, const DivisionType&);


class UnitMap
{
	public: 
		UnitMap(const std::string& category, const std::string& type, const std::string& equipment, int size);
		UnitMap() = default;
		UnitMap(const UnitMap&) = default;
		UnitMap& operator=(const UnitMap&) = default;

		std::string getCategory() const { return category; }
		std::string getType() const { return type; }
		std::string getEquipment() const { return equipment; }
		int getSize() const {return size; }

	private:
		std::string category;
		std::string type;
		std::string equipment;
		int size = 0;
};

}



#endif // HOI4_ARMY_H_