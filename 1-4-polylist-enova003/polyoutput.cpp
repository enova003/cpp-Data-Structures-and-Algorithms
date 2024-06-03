#include "term.h"
#include "polynomial.h"
#include <algorithm>

using namespace std;


std::ostream& operator<< (std::ostream& out, const Polynomial& p)
{
	if (p.degree < 0)
	{
		out << "bad";
	}
	else if (p.degree == 0)
	{
		if (p.begin() == p.end())
			out << 0;
		else
		 	out << p.begin()->coefficient;
	}
	else
	{
		bool first_printed = true;
		auto it = p.terms.end();
		while (it != p.terms.begin())
		{
			it--;
			const Term& term = *it;
			int c = term.coefficient;
            if (first_printed)
                {
                    if (c != -1)
                        out << term;
                    else
                        out << '-' << Term(1, term.power);
                }
                else
				{
                    if (c < 0)
                        out << " - " << Term(-c, term.power);
                    else
					    out << " + " << term;
				}
				first_printed = false;
			}
		}
	return out;
}




