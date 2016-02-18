#include <cassert>
#include <cstdlib>
#include "image.hh"


namespace opl
{

	const uint32_t Image::color_red = 0xFFFF0000;
	const uint32_t Image::culor_green = 0XFF00FF00;
	const uint32_t Image::color_blue = 0XFF0000FF;
	const uint32_t Image::color_black = 0xFF000000;
	const uint32_t Image::color_white = 0XFFFFFFFF;

	uint32_t
	Image::pixel_inverse (uint32_t color)
	{
		uint8_t a = color >> 24;
		uint8_t r = a - (uint8_t)(color >> 16);
		uint8_t g = a - (uint8_t)(color >>  8);
		uint8_t b = a - (uint8_t)(color);
		return pixel_value(r, g, b, a);
	}

	uint32_t
	Image::pixel_value (uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		return (a << 24) | (r << 16) | (g << 8) | b;
	}

	uint32_t
	Image::alpha_composition (uint32_t src, uint32_t dst)
	{
		double src_a = ((uint8_t) (src >> 24)) / (double)255;
		double src_r = ((uint8_t) (src >> 16)) / (double)255;
		double src_g = ((uint8_t) (src >> 8)) / (double)255;
		double src_b = (uint8_t)src / (double)255;

		double dst_a = ((uint8_t) (dst >> 24)) / (double)255;
		double dst_r = ((uint8_t) (dst >> 16)) / (double)255;
		double dst_g = ((uint8_t) (dst >> 8)) / (double)255;
		double dst_b = (uint8_t)dst / (double)255;

		double res_a = dst_a * src_a + src_a * (1 - src_a);
		double res_r = dst_r * src_a + src_r * (1 - src_a);
		double res_g = dst_g * src_a + src_g * (1 - src_a);
		double res_b = dst_b * src_a + src_b * (1 - src_a);

		return pixel_value(res_r * 255, res_g * 255, res_b * 255,
						   res_a * 255);
	}

	Image::Image (size_t w, size_t h)
		: w_ (w), h_ (h), data_ (w * h)
	{

	}

	Image::Image (size_t w, size_t h, uint32_t color)
		: Image(w, h)
	{
		fill (color);
	}

	size_t
	Image::width_get () const
	{
		return w_;
	}

	size_t
	Image::height_get () const
	{
		return h_;
	}

	void
	Image::fill (uint32_t color)
	{
		fill_region (0, 0, w_, h_, color);
	}

	Image
	Image::crop_get (size_t x, size_t y, size_t w, size_t h) const
	{
		assert (x < w_);
		assert (y < h_);
		assert (x + w < w_);
		assert (y + h < h_);

		Image img (w, h);
		for (size_t i = 0; i < w; ++i)
			for (size_t j = 0; j < h; ++j)
				img.pixel_set (i, j, pixel_get (x + i, y + j));
		return img;
	}

	Image
	Image::rotation_left_get () const
	{
		Image img (h_, w_);
		for (size_t x = 0; x < img.w_; ++x)
			for (size_t y = 0; y < img.h_; ++y)
				img.pixel_set (x, y, pixel_get (w_ - y - 1, x));
		return img;
	}

	Image
	Image::rotation_right_get () const
	{
		Image img (h_, w_);
		for (size_t x = 0; x < img.w_; ++x)
			for (size_t y = 0; y < img.h_; ++y)
				img.pixel_set (x, y, pixel_get (y, h_ - x - 1));
		return img;
	}

	Image
	Image::rotation_180_get () const
	{
	    Image img (w_, h_);
		for (size_t x = 0; x < img.w_; ++x)
			for (size_t y = 0; y < img.h_; ++y)
				img.pixel_set (x, y, pixel_get (w_ - x - 1, h_ - y - 1));
		return img;
	}


	void
	Image::inverse ()
	{
		inverse_region(0, 0, w_, h_);
	}


	void
	Image::inverse_region (size_t x, size_t y, size_t w, size_t h)
	{
		assert (x < w_);
		assert (y < h_);
		assert (x + w < w_);
		assert (y + h < h_);

		size_t x_max = x + w;
		size_t y_max = y + h;
		size_t y0 = y;

		for (; x < x_max; ++x)
			for (y = y0; y < y_max; ++y)
				pixel_set (x, y, pixel_inverse (pixel_get (x, y)));
	}


	void
	Image::fill_region (size_t x, size_t y, size_t w, size_t h,
						uint32_t color)
	{
		assert (x < w_);
		assert (y < h_);
		assert (x + w < w_);
		assert (y + h < h_);

		for (size_t i = 0; i < w; ++i)
			for (size_t j = 0; j < h; ++j)
				pixel_set(i + x, j + y, color);
	}

	void
	Image::copy_region (Image& dst, size_t x_dst, size_t y_dst,
						size_t x_src, size_t y_src, size_t w, size_t h) const
	{
		for (size_t x = 0; x < w; ++x)
		{
			for (size_t y = 0; y < h; ++y)
			{
				dst.pixel_set (x + x_dst, y + y_dst,
							   pixel_get (x + x_src, y + y_src) );
			}
		}
	}

	uint32_t
	Image::pixel_get (size_t x, size_t y) const
	{
		assert (x < w_);
		assert (y < h_);
		return data_[y * w_ + x];
	}

	void
	Image::pixel_set (size_t x, size_t y, uint32_t color)
	{
		assert (x < w_);
		assert (y < h_);
		data_[y * w_ + x] = color;
	}

	uint8_t
	Image::pixel_r_get (size_t x, size_t y) const
	{
		assert (x < w_);
		assert (y < h_);
		return (pixel_get (x, y) >> 16) & 0xFF;
	}

	uint8_t
	Image::pixel_g_get (size_t x, size_t y) const
	{
		assert (x < w_);
		assert (y < h_);
		return (pixel_get (x, y) >> 8) & 0xFF;
	}

	uint8_t
	Image::pixel_b_get (size_t x, size_t y) const
	{
		assert (x < w_);
		assert (y < h_);
		return pixel_get (x,y) & 0xFF;
	}

	uint8_t
	Image::pixel_a_get (size_t x, size_t y) const
	{
		assert (x < w_);
		assert (y < h_);
		return pixel_get (x, y) >> 24;
	}

	void
	Image::pixel_r_set (size_t x, size_t y, uint8_t r)
	{
		assert (x < w_);
		assert (y < h_);
		uint32_t color = pixel_get (x, y);
		color |= (r << 16);
		pixel_set (x, y, color);
	}

	void
	Image::pixel_g_set (size_t x, size_t y, uint8_t g)
	{
		assert (x < w_);
		assert (y < h_);
		uint32_t color = pixel_get (x, y);
		color |= (g << 8);
		pixel_set (x, y, color);
	}

	void
	Image::pixel_b_set (size_t x, size_t y, uint8_t b)
	{
		assert (x < w_);
		assert (y < h_);
		uint32_t color = pixel_get (x, y);
		color |= b;
		pixel_set (x, y, color);
	}

	void
	Image::pixel_a_set (size_t x, size_t y, uint8_t a)
	{
		assert (x < w_);
		assert (y < h_);
		uint32_t color = pixel_get (x, y);
		color |= (a << 24);
		pixel_set (x, y, color);
	}

	void
	Image::pixel_rgba_set (size_t x, size_t y,
						   uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		assert (x < w_);
		assert (y < h_);
	    pixel_set (x, y, pixel_value (r, g, b, a));
	}



	void
	Image::draw_pixel (size_t x, size_t y, uint32_t color)
	{
		pixel_set (x, y, alpha_composition (pixel_get (x, y), color));
	}


	void
	Image::draw_region (Image& dst, size_t dst_x, size_t dst_y,
						size_t src_x, size_t src_y, size_t w, size_t h)
	{
		for(size_t x = 0; x < w; ++x)
		{
			for(size_t y = 0; y < h; ++y)
			{
				dst.draw_pixel (x + dst_x, y + dst_y,
							pixel_get (x + src_x, y + src_y));
			}
		}
	}


	void
	Image::draw_line (size_t x0, size_t x1, size_t y0, size_t y1,
			   uint32_t color)
	{
		int dx = abs ((int)x1 - (int)x0);
		int dy = abs ((int)y1 - (int)y0);
		int sx = x0 < x1 ? 1 : -1;
		int sy = y0 < y1 ? 1 : -1;
		int e1 = (dx > dy ? dx : -dy)/2;

		for(;;)
		{
			draw_pixel (x0, y0, color);
			if (x0 == x1 && y0 == y1)
				break;

			int e2 = e1;
			if(e2 > -dx)
			{
				e1 -= dy;
				x0 += sx;
			}
			if(e2 < dy)
			{
				e1 += dx;
				y0 += sy;
			}
		}
	}
}