#include "mobile.h"

#include <cassert>
#include <cmath>
#include <iomanip>

using namespace std;


// Create a weight element
MobileElement::MobileElement (double w)
  : isABar(false), weight(w), id(), left(nullptr), right(nullptr), balancePoint(-1.0)
{}

// Create a bar element
MobileElement::MobileElement (string idstr, Mobile lft, Mobile rght)
  : isABar(true), weight(-1.0),
	id(idstr), left(lft), right(rght), balancePoint(-1.0)
{}

 
MobileElement::~MobileElement()
{
	delete left;
	delete right;
}


// Read and write mobiles


Mobile MobileElement::readTree (istream& in)
{
  char c;
  in >> c;
  if (c == '(')
    {
      // This is the start of a new bar description
      string id;
      in >> id;
      Mobile left = readTree(in);
      Mobile right = readTree(in);
      Mobile newBar = new MobileElement (id, left, right);
      in >> c;
      assert (c == ')'); // Check for syntax error
      return newBar;
    }
  else
    {
      // A decorative weight
      double w;
      in.putback(c);
      in >> w;
      return new MobileElement(w);
    }
}


std::istream& operator>> (std::istream& in, Mobile& m)
{
  m = MobileElement::readTree (in);
  return in;
}



void MobileElement::printTree (ostream& out, int level) const
{
  out << string(3*level, ' ');
  if (isABar)
    {
      out << "(" << id << "\n";
      left->printTree(out, level+1);
      out << "\n";
      right->printTree(out, level+1);
      out << ")";
    }
  else
    out << fixed << setprecision(2) << weight;
}

void MobileElement::listBars (ostream& out) const
{
	if (isABar)
	{
		out << id << ": " << fixed << setprecision(2) << balancePoint << endl;;
		left->listBars(out);
		right->listBars(out);
	}
	else
	{
		// Do nothing for decorative elements
	}
}

std::ostream& operator<< (std::ostream& out, Mobile m)
{
  if (m != 0)
  {
    m->printTree (out, 0);
    out << "\n";
    m->listBars(out);
  }
  return out;
}


double MobileElement::balance()
{
    if(isABar) {
    double leftWeight = left->balance();
    double rightWeight = right->balance();

    if(left->weight <= 0){
         balancePoint = 1 - (leftWeight / (leftWeight + rightWeight)); 
    } 
    else if(right->weight <= 0){ 
         balancePoint = (rightWeight / (rightWeight + leftWeight)); 
    }
    else {
        balancePoint = 1 - (left->weight / (left->weight + right->weight));
    }

     return leftWeight + rightWeight;
  } 
  
  else{
    balancePoint = 0.5;
    return weight;
  }
}
