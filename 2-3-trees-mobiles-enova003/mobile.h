#ifndef MOBILE_H
#define MOBILE_H

#include <iostream>
#include <utility>
#include <string>


class MobileElement;

typedef MobileElement* Mobile;

/** Mobile elements come in two varieties:
      bars and weights
    A "bar" is a straight length of light plastic (negligible weight)
    with two other mobile elements hanging from it, one at each
    end of the bar. A bar will itself be hanging from a string, which
    may be tied anywhere along its length.

    Decorative objects are much heavier than any bar, but
    have negligible size and have no other elements hanging from them.

    A bar of length L with elements of weight X and Y hanging from 
    its left and right ends respectively, and hanging from a string tied 
    at a fraction P (0 <= P <= 1) from its left end, is said to be "balanced"
    if P*X == (1.0-P)*Y. To allow for round-off error, we will actually say
    that the bar is balanced if P*X and (1.0-P)*Y are approximately equal.
    P is then called the "balance point" for that bar.

**/

class MobileElement {

  bool isABar;

  // For decorative objects only, ignored for bars:
  double weight;

  // For bars only, ignored for decorative objects
  std::string id;
  Mobile left;
  Mobile right;
  double balancePoint;

public:
  // Create a weight element
  MobileElement (double weight);

  // Create a bar element
  MobileElement (std::string idstr, Mobile left, Mobile right);

  ~MobileElement();

  /**
   * When invoked on a bar, compute and set the balancePoint
   * for that bar and for all bars that hang from it, directly
   * or indirectly.
   *
   * @return the total weight of all elements hanging from this bar
   *           (directly or indirectly)
   */
  double balance ();

  /**
   * @brief Following a balance() call, get the position where the string must be tied.
   * 
   * @return double the fraction of the bar's length, from the left, where the string must
   *         be tied in order for the bar to hang horizontally.
   */
  double getBalancePoint() const {return balancePoint;}

private:

  static Mobile readTree (std::istream& in);

  void printTree (std::ostream& out, int level) const;
  void listBars (std::ostream& out) const;



  friend std::istream& operator>> (std::istream& in, Mobile& m);
  friend std::ostream& operator<< (std::ostream& out, Mobile m);

};


// Read and write mobiles
std::istream& operator>> (std::istream& in, Mobile& m);

std::ostream& operator<< (std::ostream& out, Mobile m);

#endif
