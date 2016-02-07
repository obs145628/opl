#include <cstddef>
#include <climits>
#include "random-generator.hh"
#include "date.hh"

namespace opl
{

	RandomGenerator::RandomGenerator ()
		: RandomGenerator (static_cast <unsigned long> (Date::timestamp_ms ()))
	{

	}

	RandomGenerator::RandomGenerator (unsigned long s)
		: mt_ (), mti_ (1), mag01_ {0x0UL, OPL_RG_MATRIX_A}
	{
		mt_[0] = s & 0xffffffffUL;
		for (; mti_< OPL_RG_N; ++mti_)
		{
			mt_[mti_] = (1812433253UL * (mt_[mti_ - 1]
										 ^ (mt_[mti_ - 1] >> 30)) + mti_);
			mt_[mti_] &= 0xffffffffUL;
		}
	}

	unsigned long
	RandomGenerator::int32_get ()
	{
		unsigned long y;

		if (mti_ == OPL_RG_N)
		{
			int kk;

			for (kk = 0; kk < OPL_RG_N - OPL_RG_M; ++kk)
			{
				y = (mt_[kk] & OPL_RG_UPPER_MASK)
					| (mt_[kk + 1] & OPL_RG_LOWER_MASK);
				mt_[kk] = mt_[kk + OPL_RG_M] ^ (y >> 1) ^ mag01_[y & 0x1UL];
			}
			for (; kk < OPL_RG_N - 1; ++kk)
			{
				y = (mt_[kk ] & OPL_RG_UPPER_MASK)
					| (mt_[kk + 1 ] & OPL_RG_LOWER_MASK);
				mt_[kk] = mt_[kk + ( OPL_RG_M - OPL_RG_N)] ^ (y >> 1)
					^ mag01_ [y & 0x1UL];
			}
			y = (mt_[OPL_RG_N - 1] & OPL_RG_UPPER_MASK)
				| (mt_[0 ] & OPL_RG_LOWER_MASK);
			mt_[OPL_RG_N - 1] = mt_ [OPL_RG_M - 1] ^ (y >> 1)
				^ mag01_[y & 0x1UL];

			mti_ = 0;
		}

		y = mt_[mti_++];
		y ^= (y >> 11);
		y ^= (y << 7) & 0x9d2c5680UL;
		y ^= (y << 15) & 0xefc60000UL;
		y ^= (y >> 18);
		return y;
	}

	long
	RandomGenerator::int31_get ()
	{
		return static_cast <long> (int32_get ()) >> 1;
	}

	int
	RandomGenerator::getInt ()
	{
		int n = static_cast <int> (int31_get ());
		size_t blocks = sizeof (int) / 4;
		int shift = 32;

		for (size_t i = 1; i < blocks; ++i)
			n = (n << shift) | static_cast<int> (int32_get ());
		return n;
	}

	unsigned int
	RandomGenerator::getUInt ()
	{
		unsigned int n = 0;
		size_t blocks = sizeof (unsigned int) / 4;
		unsigned int shift = 32;

		for (size_t i = 0; i < blocks; ++i)
			n = (n << shift) | static_cast<unsigned int> (int32_get ());
		return n;
	}

	long
	RandomGenerator::getLong ()
	{
		long n = static_cast <long> (int31_get ());
		size_t blocks = sizeof (long) / 4;
		long shift = 32;

		for (size_t i = 1; i < blocks; ++i)
			n = (n << shift) | static_cast<long> (int32_get ());
		return n;
	}


	unsigned long
	RandomGenerator::getULong ()
	{
		unsigned long n = 0;
		size_t blocks = sizeof (unsigned long) / 4;
		unsigned long shift = 32;

		for (size_t i = 0; i < blocks; ++i)
			n = (n << shift) | static_cast<unsigned long> (int32_get ());
		return n;
	}


	long long
	RandomGenerator::getLLong ()
	{
		long long n = static_cast <long long> (int31_get ());
		size_t blocks = sizeof (long long) / 4;
		long long shift = 32;

		for (size_t i = 1; i < blocks; ++i)
			n = (n << shift) | static_cast<long long> (int32_get ());
		return n;
	}

	unsigned long long
	RandomGenerator::getULLong ()
	{
		unsigned long long n = 0;
		size_t blocks = sizeof (unsigned long long) / 4;
		unsigned long long shift = 32;

		for (size_t i = 0; i < blocks; ++i)
			n = (n << shift) | static_cast<unsigned long long> (int32_get ());
		return n;
	}



	int
	RandomGenerator::getInt (int max)
	{
		return getInt () % max;
	}

	unsigned int
	RandomGenerator::getUInt (unsigned int max)
	{
		return getUInt () % max;
	}

	long
	RandomGenerator::getLong (long max)
	{
		return getLong () % max;
	}

	unsigned long
	RandomGenerator::getULong (unsigned long max)
	{
		return getULong () % max;
	}

	long long
	RandomGenerator::getLLong (long long max)
	{
		return getLLong () % max;
	}

	unsigned long long
	RandomGenerator::getULLong (unsigned long long max)
	{
		return getULLong () % max;
	}

	int
	RandomGenerator::getInt (int min, int max)
	{
		return getInt () % (max - min) + min;
	}

	unsigned int
	RandomGenerator::getUInt (unsigned int min, unsigned int max)
	{
		return getUInt () % (max - min) + min;
	}

	long
	RandomGenerator::getLong (long min, long max)
	{
		return getLong () % (max - min) + min;
	}

	unsigned long
	RandomGenerator::getULong (unsigned long min, unsigned long max)
	{
		return getULong () % (max - min) + min;
	}

	long long
	RandomGenerator::getLLong (long long min, long long max)
	{
		return getLLong () % (max - min) + min;
	}

	unsigned long long
	RandomGenerator::getULLong (unsigned long long min,
								unsigned long long max)
	{
		return getLLong () % (max - min) + min;
	}


	bool
	RandomGenerator::getBool ()
	{
		return static_cast<bool> (int32_get () % 2);
	}

	char
	RandomGenerator::getChar ()
	{
		return static_cast<char> (int32_get () % (CHAR_MAX + 1));
	}

	unsigned char
	RandomGenerator::getUChar ()
	{
		return static_cast<unsigned char> (int32_get () % (UCHAR_MAX + 1));
	}

	short
	RandomGenerator::getShort ()
	{
		return static_cast<short> (int32_get () % (SHRT_MAX + 1));
	}

	unsigned short
	RandomGenerator::getUShort ()
	{
		return static_cast<unsigned short> (int32_get () % (USHRT_MAX + 1));
	}


	char
	RandomGenerator::getChar (char max)
	{
		return static_cast <char> (int31_get () % max);
	}

	unsigned char
	RandomGenerator::getUChar (unsigned char max)
	{
		return static_cast <unsigned char> (int32_get () % max);
	}

	short
	RandomGenerator::getShort (short max)
	{
		return static_cast <short> (int32_get () % max);
	}

	unsigned short
	RandomGenerator::getUShort (unsigned short max)
	{
		return static_cast <unsigned short> (int32_get () % max);
	}

	char
	RandomGenerator::getChar (char min, char max)
	{
	    return static_cast <char> (int32_get () % (max - min) + min);
	}

	unsigned char
	RandomGenerator::getUChar (unsigned char min, unsigned char max)
	{
		return static_cast <unsigned char> (int32_get () % (max - min) + min);
	}

	short
	RandomGenerator::getShort (short min, short max)
	{
		return static_cast <short> (int32_get () % (max - min) + min);
	}

	unsigned short
	RandomGenerator::getUShort (unsigned short min, unsigned short max)
	{
		return static_cast <unsigned short> (int32_get () % (max - min)
											 + min);
	}


	float
	RandomGenerator::getFloat ()
	{
	    return int32_get ()
			* (static_cast<float> (1) / static_cast<float> (4294967295));
	}

	double
	RandomGenerator::getDouble ()
	{
		return int32_get ()
			* (static_cast<double> (1) / static_cast<double> (4294967295));
	}

	long double
	RandomGenerator::getLDouble ()
	{
		return int32_get ()
			* (static_cast<long double> (1)
			   / static_cast<long double> (4294967295));
	}


	void
	RandomGenerator::write (void *dst, size_t n)
	{
		unsigned char* ptr = reinterpret_cast <unsigned char*> (dst);
		for (size_t i = 0; i < n; ++i)
			ptr[i] = getUChar();
	}

	float
	RandomGenerator::getFloat (float max)
	{
		return getFloat() * max;
	}

	double
	RandomGenerator::getDouble (double max)
	{
		return getDouble() * max;
	}

	long double
	RandomGenerator::getLDouble (long double max)
	{
		return getLDouble() * max;
	}

	float
	RandomGenerator::getFloat (float min, float max)
	{
		return getFloat() * (max - min) + min;
	}

	double
	RandomGenerator::getDouble (double min, double max)
	{
		return getDouble() * (max - min) + min;
	}

	long double
	RandomGenerator::getLDouble (long double min, long double max)
	{
		return getLDouble() * (max - min) + min;
	}


}