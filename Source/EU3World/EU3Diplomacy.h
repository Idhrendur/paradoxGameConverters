#ifndef EU3DIPLOMACY_H_
#define EU3DIPLOMACY_H_


#include "..\Date.h"
#include <vector>
using namespace std;



class Object;
class EU3Country;



struct EU3Agreement
{
	EU3Agreement();
	void output(FILE*);

	string		type;
	EU3Country*	country1;
	EU3Country*	country2;
	date			startDate;
};


class EU3Diplomacy
{
	public:
		EU3Diplomacy();
		void output(FILE*);
	private:
		vector<EU3Agreement>	agreements;
};

// Types of agreements:
//open_market - eventually care
//casus_belli - care
//royal_marriage - care
//guarantee - don't know
//alliance - don't know
//union - care
//sphere - don't know
//vassal - care

#endif