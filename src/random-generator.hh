/** @file Random Generator class definition, with Mersenne twister algortihm
 */

#ifndef RANDOM_GENERATOR_HH_
# define RANDOM_GENERATOR_HH_

# include <cstddef>
# include <array>

# define OPL_RG_N 624
# define OPL_RG_M 397
# define OPL_RG_MATRIX_A 0x9908b0dfUL
# define OPL_RG_UPPER_MASK 0x80000000UL
# define OPL_RG_LOWER_MASK 0x7fffffffUL

namespace opl
{

	/** Pseudo random generator
	 * Implementend with Hersenne Twister Algorithm
	 */
	class RandomGenerator
	{

	public:
		RandomGenerator ();
		RandomGenerator (unsigned long s);

		///Returns n \in [0, 4,294,967,295]
		unsigned long
		int32_get ();

		///Returns n \in [0, 2,147,483,648]
		long
		int31_get ();


		///Returns n \in [0, INT_MAX]
		int
		getInt ();

		///Returns n \in [0, UINT_MAX]
		unsigned int
		getUInt ();

		///Returns n \in [0, LONG_MAX]
		long
		getLong ();

		///Returns n \in [0, ULONG_MAX]
		unsigned long
		getULong ();

		///Returns n \in [0, LLONG_MAX]
		long long
		getLLong ();

		///Returns n \in [0, ULLONG_MAX]
		unsigned long long
		getULLong ();


		int
		getInt (int max);

		unsigned int
		getUInt (unsigned int max);

		long
		getLong (long max);

		unsigned long
		getULong (unsigned long max);

		long long
		getLLong (long long max);

		unsigned long long
		getULLong (unsigned long long max);

		int
		getInt (int min, int max);

		unsigned int
		getUInt (unsigned int min, unsigned int max);

		long
		getLong (long min, long max);

		unsigned long
		getULong (unsigned long min, unsigned long max);

		long long
		getLLong (long long min, long long max);

		unsigned long long
		getULLong (unsigned long long min, unsigned long long max);


		bool
		getBool ();

		char
		getChar ();

		unsigned char
		getUChar ();

		short
		getShort ();

		unsigned short
		getUShort ();


		char
		getChar (char max);

		unsigned char
		getUChar (unsigned char max);

		short
		getShort (short max);

		unsigned short
		getUShort (unsigned short max);

		char
		getChar (char min, char max);

		unsigned char
		getUChar (unsigned char min, unsigned char max);

		short
		getShort (short min, short max);

		unsigned short
		getUShort (unsigned short min, unsigned short max);

		///Returns n \in [0, 1[
		float
		getFloat ();

		///Returns n \in [0, 1[
		double
		getDouble ();

		///Returns n \in [0, 1[
		long double
		getLDouble ();



		float
		getFloat (float max);

		double
		getDouble (double max);

		long double
		getLDouble (long double max);


		float
		getFloat (float min, float max);

		double
		getDouble (double min, double max);

		long double
		getLDouble (long double min, long double max);


		///write n random bytes at dst
		void
		write (void *dst, size_t n);






	private:
		std::array<unsigned long, OPL_RG_N> mt_;
		int mti_;
		std::array<unsigned long, 2> mag01_;

	};

}


#endif //!RANDOM_GENERATOR_HH_