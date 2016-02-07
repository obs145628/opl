#include "color.hh"

namespace opl
{

	const Color Color::RED (static_cast<uint8_t> (255), 0, 0);
	const Color Color::GREEN (static_cast<uint8_t> (0), 255, 0);
	const Color Color::BLUE (static_cast <uint8_t> (0), 0, 255);
	const Color Color::BLACK (static_cast <uint8_t> (0), 0, 0);
	const Color Color::WHITE (static_cast <uint8_t> (255), 255, 255);

	Color::Color (uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		: r_ (r), g_ (g), b_ (b), a_ (a)
	{

	}

	Color::Color (r_type r, r_type g, r_type b, r_type a)
		: r_ (decimal_to_byte_ (r)), g_ (decimal_to_byte_ (g)),
		  b_ (decimal_to_byte_ (b)), a_ (decimal_to_byte_ (a))
	{

	}

	Color::Color(uint32_t value)
		: r_ ((value >> 16) & 0xFF), g_ ((value >> 8) & 0xFF),
		  b_ (value & 0xFF), a_ (value >> 24)
	{

	}

	Color
	Color::inverse () const
	{
		return Color (a_ - r_, a_ - g_, a_ - b_, a_);
	}

	Color
	Color::compose (const Color& dst) const
	{
		r_type src_a = dalpha ();
		r_type src_r = dred ();
		r_type src_g = dgreen ();
		r_type src_b = dblue ();
		r_type dst_a = dst.dalpha ();
		r_type dst_r = dst.dred ();
		r_type dst_g = dst.dgreen ();
		r_type dst_b = dst.dblue ();

		r_type res_a = dst_a * src_a + src_a
			* (static_cast<r_type> (1) - src_a);
		r_type res_r = dst_r * src_a + src_r
			* (static_cast<r_type> (1) - src_a);
		r_type res_g = dst_g * src_a + src_g
			* (static_cast<r_type> (1) - src_a);
		r_type res_b = dst_b * src_a + src_b
			* (static_cast<r_type> (1) - src_a);

		return Color (res_r, res_g, res_b, res_a);
	}

	uint8_t
	Color::red () const
	{
		return r_;
	}

	uint8_t
	Color::green () const
	{
		return g_;
	}

	uint8_t
	Color::blue () const
	{
		return b_;
	}

	uint8_t
	Color::alpha () const
	{
		return a_;
	}

	r_type
	Color::dred () const
	{
		return byte_to_decimal_ (r_);
	}

	r_type
	Color::dgreen () const
	{
		return byte_to_decimal_ (g_);
	}

	r_type
	Color::dblue () const
	{
		return byte_to_decimal_ (b_);
	}

	r_type
	Color::dalpha () const
	{
		return byte_to_decimal_ (a_);
	}

	r_type
	Color::byte_to_decimal_ (uint8_t byte)
	{
		return static_cast<r_type> (byte) / static_cast<r_type> (255);
	}

	uint8_t
	Color::decimal_to_byte_ (r_type byte)
	{
		return static_cast<uint8_t> (byte * static_cast<r_type> (255));
	}

	uint32_t
	Color::value () const
	{
		return (a_ << 24) | (r_ << 16) | (g_ << 8) | b_;
	}
}