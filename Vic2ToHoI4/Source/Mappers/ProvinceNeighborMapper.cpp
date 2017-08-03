/*Copyright (c) 2017 The Paradox Game Converters Project

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



#include "ProvinceNeighborMapper.h"
#include "ProvinceDefinitions.h"
#include "../Color.h"
#include "../Configuration.h"
#include "Log.h"

extern "C"
{
	#define ANSI_DECLARATORS
	#define REAL double
	#define VOID int
	#include "../triangle.h"
}



provinceNeighborMapper* provinceNeighborMapper::instance = nullptr;



provinceNeighborMapper::provinceNeighborMapper()
{
	processProvincesFile();
	createDelaunayTriangulations();
}


void provinceNeighborMapper::processProvincesFile()
{
	bitmap_image provinces(Configuration::getHoI4Path() + "/map/provinces.bmp");
	if (!provinces)
	{
		LOG(LogLevel::Error) << "Could not open " << Configuration::getHoI4Path() << "/map/provinces.bmp";
	}

	unsigned int height = provinces.height();
	unsigned int width = provinces.width();

	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			point position = { x, y };

			Color centerColor = getCenterColor(provinces, position);
			Color aboveColor = getAboveColor(provinces, position, height);
			Color belowColor = getBelowColor(provinces, position, height);
			Color leftColor = getLeftColor(provinces, position, width);
			Color rightColor = getRightColor(provinces, position, width);

			position.second = height - position.second - 1;
			if (centerColor != aboveColor)
			{
				handleNeighbor(centerColor, aboveColor, position);
			}
			if (centerColor != rightColor)
			{
				handleNeighbor(centerColor, rightColor, position);
			}
			if (centerColor != belowColor)
			{
				handleNeighbor(centerColor, belowColor, position);
			}
			if (centerColor != leftColor)
			{
				handleNeighbor(centerColor, leftColor, position);
			}

			if ((y == 0) || (y == (height - 1)))
			{
				int province = provinceDefinitions::getProvinceFromColor(centerColor);
				addToBoundary(province, position);
			}
		}
	}
}


Color provinceNeighborMapper::getCenterColor(bitmap_image& provinces, point position)
{
	rgb_t color;
	provinces.get_pixel(position.first, position.second, color);

	Color theColor(color.red, color.green, color.blue);
	return theColor;
}


Color provinceNeighborMapper::getAboveColor(bitmap_image& provinces, point position, int height)
{
	if (position.second > 0)
	{
		position.second--;
	}

	rgb_t color;
	provinces.get_pixel(position.first, position.second, color);

	Color theColor(color.red, color.green, color.blue);
	return theColor;
}


Color provinceNeighborMapper::getBelowColor(bitmap_image& provinces, point position, int height)
{
	if (position.second < height - 1)
	{
		position.second++;
	}

	rgb_t color;
	provinces.get_pixel(position.first, position.second, color);

	Color theColor(color.red, color.green, color.blue);
	return theColor;
}


Color provinceNeighborMapper::getLeftColor(bitmap_image& provinces, point position, int width)
{
	if (position.first > 0)
	{
		position.first--;
	}
	else
	{
		position.first = width - 1;
	}

	rgb_t color;
	provinces.get_pixel(position.first, position.second, color);

	Color theColor(color.red, color.green, color.blue);
	return theColor;
}


Color provinceNeighborMapper::getRightColor(bitmap_image& provinces, point position, int width)
{
	if (position.first < width - 1)
	{
		position.first++;
	}
	else
	{
		position.first = 0;
	}

	rgb_t color;
	provinces.get_pixel(position.first, position.second, color);

	Color theColor(color.red, color.green, color.blue);
	return theColor;
}


void provinceNeighborMapper::handleNeighbor(Color centerColor, Color otherColor, point position)
{
	int centerProvince = provinceDefinitions::getProvinceFromColor(centerColor);
	int otherProvince = provinceDefinitions::getProvinceFromColor(otherColor);

	addToBoundary(centerProvince, position);
	addNeighbor(centerProvince, otherProvince);
	addPointToBorder(centerProvince, otherProvince, position);
}


void provinceNeighborMapper::addToBoundary(int mainProvince, point position)
{
	auto boundary = provinceBoundaries.find(mainProvince);
	if (boundary != provinceBoundaries.end())
	{
		boundary->second.insert(position);
	}
	else
	{
		borderPoints newBorder;
		newBorder.insert(position);
		provinceBoundaries[mainProvince] = newBorder;
	}
}


void provinceNeighborMapper::addNeighbor(int mainProvince, int neighborProvince)
{
	auto centerMapping = provinceNeighbors.find(mainProvince);
	if (centerMapping != provinceNeighbors.end())
	{
		centerMapping->second.insert(neighborProvince);
	}
	else
	{
		set<int> neighbors = { neighborProvince };
		provinceNeighbors[mainProvince] = neighbors;
	}
}


void provinceNeighborMapper::addPointToBorder(int mainProvince, int neighborProvince, point position)
{
	auto bordersWithNeighbors = borders.find(mainProvince);
	if (bordersWithNeighbors == borders.end())
	{
		bordersWith newBordersWithNeighbors;
		borders.insert(make_pair(mainProvince, newBordersWithNeighbors));
		bordersWithNeighbors = borders.find(mainProvince);
	}

	auto border = bordersWithNeighbors->second.find(neighborProvince);
	if (border == bordersWithNeighbors->second.end())
	{
		orderedBorderPoints newBorder;
		bordersWithNeighbors->second.insert(make_pair(neighborProvince, newBorder));
		border = bordersWithNeighbors->second.find(neighborProvince);
	}

	if (border->second.size() == 0)
	{
		border->second.push_back(position);
	}
	else
	{
		auto lastPoint = border->second.back();
		if ((lastPoint.first != position.first) || (lastPoint.second != position.second))
		{
			border->second.push_back(position);
		}
	}
}


void provinceNeighborMapper::createDelaunayTriangulations()
{
	for (auto provinceBoundary: provinceBoundaries)
	{
		auto edges = createDelaunayTriangulation(provinceBoundary.second);
		proviceEdges.insert(make_pair(provinceBoundary.first, edges));
	}
}


set<edge> provinceNeighborMapper::createDelaunayTriangulation(const borderPoints& border)
{
	triangulateio in;
	in.numberofpointattributes = 0;
	in.pointmarkerlist = NULL;

	in.numberofpoints = border.size();
	in.pointlist = new REAL[border.size() * 2];

	int i = 0;
	for (auto borderPoint: border)
	{
		in.pointlist[i * 2 + 0] = borderPoint.first;
		in.pointlist[i * 2 + 1] = borderPoint.second;
		i++;
	}

	triangulateio out;
	out.pointlist = NULL;
	out.pointmarkerlist = NULL;
	out.neighborlist = NULL;
	out.edgelist = NULL;
	out.edgemarkerlist = NULL;
	out.trianglelist = NULL;
	triangulate("-z -Q -e", &in, &out, NULL);

	set<edge> edges;
	for (int i = 0; i < out.numberofedges / 2; i++)
	{
		int pointOneIndex = out.edgelist[i * 2 + 0];
		point pointOne;
		pointOne.first = in.pointlist[pointOneIndex * 2 + 0];
		pointOne.second = in.pointlist[pointOneIndex * 2 + 1];

		int pointTwoIndex = out.edgelist[i * 2 + 1];
		point pointTwo;
		pointTwo.first = in.pointlist[pointTwoIndex * 2 + 0];
		pointTwo.second = in.pointlist[pointTwoIndex * 2 + 1];

		edge newEdge;
		newEdge.first = pointOne;
		newEdge.second = pointTwo;
		edges.insert(newEdge);
	}

	delete[] in.pointlist;
	trifree(reinterpret_cast<VOID*>(out.pointlist));
	trifree(out.pointmarkerlist);
	trifree(out.neighborlist);
	trifree(out.edgelist);
	trifree(out.edgemarkerlist);
	trifree(out.trianglelist);

	return edges;
}


const set<int> provinceNeighborMapper::GetNeighbors(int province)
{
	auto neighbors = provinceNeighbors.find(province);
	if (neighbors != provinceNeighbors.end())
	{
		return neighbors->second;
	}
	else
	{
		set<int> empty;
		return empty;
	}
}


const point provinceNeighborMapper::GetBorderCenter(int mainProvince, int neighbor)
{
	auto bordersWithNeighbors = borders.find(mainProvince);
	if (bordersWithNeighbors == borders.end())
	{
		LOG(LogLevel::Warning) << "Province " << mainProvince << " has no borders.";
		return make_pair(-1, -1);
	}
	auto border = bordersWithNeighbors->second.find(neighbor);
	if (border == bordersWithNeighbors->second.end())
	{
		LOG(LogLevel::Warning) << "Province " << mainProvince << " does not border " << neighbor << ".";
		return make_pair(-1, -1);
	}

	return border->second[(border->second.size() / 2)];
}