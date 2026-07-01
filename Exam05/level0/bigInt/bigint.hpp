#ifndef BIGINT_HPP
# define BIGINT_HPP

#include <string>
#include <iostream>

using std::string;
using std::ostream;

class	bigint {

public:
	bigint();
	bigint(size_t nbr);
	bigint(const string& str);
	bigint(const bigint& other);

	~bigint();

	bigint&	operator=(const bigint& other);

	/* -- Bigint Methods -- */
	bigint	operator+(const bigint& other) const;
	bigint&	operator+=(const bigint& other);

	bigint& operator++(void);
	bigint operator++(int);

	bigint	operator<<(const bigint& other) const;
	bigint&	operator<<=(const bigint& other);

	bigint	operator>>(const bigint& other) const;
	bigint&	operator>>=(const bigint& other);

	bool	operator>(const bigint& other) const;
	bool	operator>=(const bigint& other) const;
	bool	operator<(const bigint& other) const;
	bool	operator<=(const bigint& other) const;
	bool	operator==(const bigint& other) const;
	bool	operator!=(const bigint& other) const;

	/* -- Size_t Methods -- */
	bigint	operator+(size_t other) const;
	bigint&	operator+=(size_t other);

	bigint	operator<<(size_t shift) const;
	bigint&	operator<<=(size_t shift);

	bigint	operator>>(size_t shift) const;
	bigint&	operator>>=(size_t shift);

	bool	operator>(const bigint& other) const;
	bool	operator>=(const bigint& other) const;
	bool	operator<(const bigint& other) const;
	bool	operator<=(const bigint& other) const;
	bool	operator==(const bigint& other) const;
	bool	operator!=(const bigint& other) const;

	friend ostream& operator<<(ostream& os, const bigint& n);

private:
	string	_digits;
};

ostream& operator<<(ostream& os, const bigint& n);

string	tostring(size_t n);
void	normalize(string& s);
int		compare(const string& a, const string& b);
string	addAbs(const string& s1, const string& s2);

#endif