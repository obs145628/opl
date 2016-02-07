/** @file Color class definition
 */

#ifndef COLOR_HH_
# define COLOR_HH_

# include <cstdint>
# include "types.hh"

namespace opl
{

	/**
	 * Handle RGBA color using 0-255 / 0-1 representations
	 */
	class Color
	{

	public:

		static const Color RED;
		static const Color GREEN;
		static const Color BLUE;
		static const Color BLACK;
		static const Color WHITE;


		Color (uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		Color (r_type r, r_type g, r_type b, r_type a = 1.0);
		Color (uint32_t value);

		Color
		inverse () const;

		Color
		compose (const Color& dst) const;

		uint8_t
		red () const;

		uint8_t
		green () const;

		uint8_t
		blue () const;

		uint8_t
		alpha () const;

		r_type
		dred () const;

		r_type
		dgreen () const;

		r_type
		dblue () const;

		r_type
		dalpha () const;

		uint32_t
		value () const;




	private:
		uint8_t r_;
		uint8_t g_;
		uint8_t b_;
		uint8_t a_;

		static r_type
		byte_to_decimal_ (uint8_t byte);

		static uint8_t
		decimal_to_byte_ (r_type byte);




	};

}

#endif //!COLOR_HH_