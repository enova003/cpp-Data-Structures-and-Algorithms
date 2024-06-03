#include "polynomial.h"
#include <algorithm>

using namespace std;

void Polynomial::normalize () 
{
	if (degree < 0)
	{
		terms.clear();
		return;
	}

	std::list<Term>::iterator it = terms.begin();
	while (it != terms.end())
	{
		if (it->coefficient == 0)
			it = terms.erase(it);
		else
			++it;
	}
	if (terms.begin() != terms.end()) 
		degree = terms.back().power;
	else
		degree = 0;
}

Polynomial::Polynomial () 
: degree(-1), terms()
{
}

Polynomial::Polynomial (int b, int a) 
: degree(1)
{
    terms.emplace_back(b, 0);
    terms.emplace_back(a, 1);
    normalize();
}

Polynomial::Polynomial (std::initializer_list<Term> term2) 
: degree(0), terms()
{  
    int maxPower = 0;
    for(auto& t : term2)
    {
        if(t.power > maxPower)
        {
            maxPower = t.power;
        }
    }
    degree = maxPower;

    while (terms.size() < degree + 1) {
        terms.emplace_back(0, terms.size());
    }

    for(auto& t : terms)
    {
        for(auto& t2 : term2)
        {
            if(t.power == t2.power)
            {
                t.coefficient = t2.coefficient;
            }
        }
    }

    normalize();

}


Polynomial::Polynomial (int nC, int coeff[])
: degree(nC-1)
{
	for (int i = 0; i < nC; ++i) {
		if (coeff[i] != 0) {
			terms.push_back(Term(coeff[i], i));
		}
	}
	normalize();
}

int Polynomial::getDegree() const 
{
	return degree;
}

int Polynomial::getCoeff(int power) const
{
	for(const auto& term : terms)
    {
        if(term.power == power)
        {
            return term.coefficient;
        }
    }

    return 0;
}

Polynomial Polynomial::operator+ (const Polynomial& p) const 
{
    Polynomial result;

    if (degree == -1 && p.degree == -1) {
           return result;
     } 
    else if (degree == -1) {
           return p;
    } 
    else if (p.degree == -1) {
           return *this;
    }

    auto it1 = terms.begin();
    auto it2 = p.terms.begin();
    while (it1 != terms.end() && it2 != p.terms.end()) {
        if (it1->power == it2->power) {
            int coeff = it1->coefficient + it2->coefficient;
            if (coeff != 0) {
                result.terms.push_back(Term(coeff, it1->power));
            }
            it1++;
            it2++;
        } else if (it1->power < it2->power) {
            result.terms.push_back(*it1);
            it1++;
        } else {
            result.terms.push_back(*it2);
            it2++;
        }
    }

    result.terms.insert(result.terms.end(), it1, terms.end());
    result.terms.insert(result.terms.end(), it2, p.terms.end());

    result.degree = result.terms.empty() ? 0 : result.terms.back().power;
    result.normalize();

    return result;

}


Polynomial Polynomial::operator* (int scale) const 
{
    if (degree == -1) {
        return Polynomial(); 
    }

    Polynomial result(*this);
    for (auto& term : result.terms) {
        term.coefficient *= scale;
    }
    result.normalize();
    return result;
}

Polynomial Polynomial::operator* (Term term) const 
{
    if(degree == -1)
    {
        return Polynomial();
    }

    Polynomial result(*this);
    for (auto& t : result.terms) {
        t.coefficient *= term.coefficient;
        t.power += term.power;
    }
    result.normalize();
    return result;
}


void Polynomial::operator*= (int scale) 
{
	if (degree == -1)
		return;
	for (auto& term : terms)
    {
        term.coefficient *= scale;
    }
    normalize();
}

Polynomial Polynomial::operator/ (const Polynomial& p) const
{  
    if (degree == 0)
    {
        return Polynomial(0);
    }

    else if (degree < p.degree)
    {
        return Polynomial();
    }
    Polynomial returnTerms;
    returnTerms.degree = 0;
    Polynomial remainder(*this);
    Polynomial remainder2(*this);
    Polynomial subtractor;

    int resultSize = degree - p.degree + 1;

    for(int i = resultSize - 1; i >= 0; --i)
    {
        int coeffRemainder = remainder.getCoeff(i+p.degree);
        int coeffDenominator = p.getCoeff(p.degree);

        if(coeffRemainder % coeffDenominator == 0)
        {
            int coeff = coeffRemainder / coeffDenominator;

            remainder2.terms.emplace_back(coeff, i);
            remainder2.normalize();    

            returnTerms.terms.emplace_front(coeff, i);
            
            subtractor = p * Term(-coeff, i);
            remainder = remainder + subtractor;
        }
        else
        {
            break;
        }
    }

    if(remainder == Polynomial(0))
    {
        returnTerms.normalize();
        return returnTerms;
    }
    else
    {
        return Polynomial();
    } 
}

bool Polynomial::operator==(const Polynomial& p) const 
{
    return (degree == p.degree && terms == p.terms);
}

Polynomial::iterator Polynomial::begin() 
{
    return terms.begin();
}

Polynomial::iterator Polynomial::end() 
{
    return terms.end();
}

Polynomial::const_iterator Polynomial::begin() const 
{
    return terms.begin();
}

Polynomial::const_iterator Polynomial::end() const 
{
    return terms.end();
}