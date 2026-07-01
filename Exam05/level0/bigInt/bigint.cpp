#include "bigint.hpp"

using std::string;
using std::ostream;

/***************/
/* -- UTILS -- */
/***************/

void	normalize(string& s)
{
	size_t k = 0;

	while (k < s.size() && s[k] == '0')
		++k;
	
	if (k == s.size())
		s = "0";
	else
		s.erase(0, k);
}

int		compare(const string& a, const string& b)
{
	if (a.size() != b.size())
		return ((a.size() > b.size()) ? 1 : -1);
	return ((a > b) ? 1 : (b > a) ? -1 : 0);
}

string	addAbs(const string& s1, const string& s2)
{
	string res;
	int retenue = 0;

	int i = static_cast<int>(s1.size()) - 1;
	int j = static_cast<int>(s2.size()) - 1;

	while (i >= 0 || j >= 0 || retenue)
	{
		int a = (i >= 0) ? s1[i] - '0' : 0;
		int b = (j >= 0) ? s2[j] - '0' : 0;

		int sum = a + b + retenue;
		retenue = sum / 10;

		res.insert(res.begin(), (sum % 10) + '0');
		i--;
		j--;
	}

	normalize(res);
	return (res);
}

string	tostring(size_t n)
{
	string res;

	if (n == 0)
		return ("0");

	while (n > 0)
	{
		res.insert(res.begin(), static_cast<char>(n % 10 + '0'));
		n /= 10;
	}

	normalize(res);
	return (res);
}

size_t	tonumber(const string& s)
{
	
}

/********************/
/* -- CANNONICAL -- */
/********************/

bigint::bigint() : _digits("0") {}

bigint::bigint(const string& str) : _digits(str) {
	normalize(_digits);
}
bigint::bigint(size_t nbr) : _digits(tostring(nbr)) {}

bigint::bigint(const bigint& other) : _digits(other._digits) {}

bigint::~bigint() {}

bigint&	bigint::operator=(const bigint& other)
{
	if (this != &other)
		_digits = other._digits;

	return (*this);
}

/************************/
/* -- BIGINT METHODS -- */
/************************/

/* -- Comparisons -- */
bool	bigint::operator!=(const bigint& other) const { return (_digits != other._digits); }
bool	bigint::operator==(const bigint& other) const { return (_digits == other._digits); }
bool	bigint::operator<=(const bigint& other) const { return (compare(_digits, other._digits) <= 0); }
bool	bigint::operator<(const bigint& other) const { return (compare(_digits, other._digits) < 0); }
bool	bigint::operator>=(const bigint& other) const { return (compare(_digits, other._digits) >= 0); }
bool	bigint::operator>(const bigint& other) const { return (compare(_digits, other._digits) > 0); }


/* -- Add Methods -- */
bigint&	bigint::operator++(void)
{
	_digits = addAbs(_digits, "1");

	return (*this);
}

bigint	bigint::operator++(int)
{
	bigint tmp(*this);
	_digits = addAbs(_digits, "1");

	return (tmp);
}

bigint	bigint::operator+(const bigint& other) const
{
	return (bigint(addAbs(_digits, other._digits)));
}

bigint&	bigint::operator+=(const bigint& other)
{
	_digits = addAbs(_digits, other._digits);

	return (*this);
}


/* -- DigitShift Methods -- */


/************************/
/* -- SIZE_T METHODS -- */
/************************/

bigint	bigint::operator>>(size_t shift) const
{
	bigint res(*this);

	if (shift >= res._digits.size())
		res._digits = "0";
	else
		res._digits.erase(res._digits.size() - shift);

	return (res);
}

bigint&	bigint::operator>>=(size_t shift)
{
	if (shift >= _digits.size())
		_digits = "0";
	else
		_digits.erase(_digits.size() - shift);

	return (*this);
}

bigint	bigint::operator<<(size_t shift) const
{
	bigint res(*this);

	if (res._digits != "0")
		res._digits.append(shift, '0');

	return (res);
}

bigint&	bigint::operator<<=(size_t shift)
{
	if (_digits != "0")
		_digits.append(shift, '0');

	return (*this);
}



/* -- OSTREAM -- */

ostream& operator<<(ostream& os, const bigint& n)
{
	os << n._digits;

	return (os);
}
