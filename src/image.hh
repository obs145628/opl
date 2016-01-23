/** @file Imge class definition
 */

#ifndef DEF_IMAGE_HH_
#define DEF_IMAGE_HH_

# include <cstdint>
# include <cstddef>
# include <vector>



namespace opl
{

	/// Handle basic image modifications
	class Image
	{

	public:
		using pixel_type = uint32_t;
		using channel_type = uint8_t;

		static const uint32_t color_red;
		static const uint32_t culor_green;
		static const uint32_t color_blue;
		static const uint32_t color_black;
		static const uint32_t color_white;

		static uint32_t
		pixel_inverse (uint32_t color);

		static uint32_t
		pixel_value (uint8_t r, uint8_t g, uint8_t b, uint8_t a);

		static uint32_t
		alpha_composition (uint32_t src, uint32_t dst);

		Image (size_t w, size_t h);
		Image (size_t w, size_t h, uint32_t color);

		size_t
		width_get () const;

		size_t
		height_get () const;

		void
		fill (uint32_t color);

		Image
		crop_get (size_t x, size_t y, size_t w, size_t h) const;

		Image
		rotation_left_get () const;

		Image
		rotation_right_get () const;

		Image
		rotation_180_get () const;

		//Inverse the color of all the pixels
		void
		inverse ();


		//Inverse the color of the pixels in the region
		void
		inverse_region (size_t x, size_t y, size_t w, size_t h);


		void
		fill_region (size_t x, size_t y, size_t w, size_t h, uint32_t color);

		void
		copy_region (Image& dst, size_t x_dst, size_t y_dst,
					 size_t x_src, size_t y_src, size_t w, size_t h) const;

		uint32_t
		pixel_get (size_t x, size_t y) const;

		void
		pixel_set (size_t x, size_t y, uint32_t color);

		uint8_t
		pixel_r_get (size_t x, size_t y) const;

		uint8_t
		pixel_g_get (size_t x, size_t y) const;

		uint8_t
		pixel_b_get (size_t x, size_t y) const;

		uint8_t
		pixel_a_get (size_t x, size_t y) const;

		void
		pixel_r_set (size_t x, size_t y, uint8_t r);

		void
		pixel_g_set (size_t x, size_t y, uint8_t g);

		void
		pixel_b_set (size_t x, size_t y, uint8_t b);

		void
		pixel_a_set (size_t x, size_t y, uint8_t a);

		void
		pixel_rgba_set (size_t x, size_t y,
						uint8_t r, uint8_t g, uint8_t b, uint8_t a);


		///Draw a pixel on top of the current one
		void
		draw_pixel (size_t x, size_t y, uint32_t color);

		///Draw a region of top of another image
		void
		draw_region (Image& dst, size_t dst_x, size_t dst_y,
					 size_t src_x, size_t src_y, size_t w, size_t h);

		///Draw a line of top of the image
		void
		draw_line (size_t x0, size_t x1, size_t y0, size_t y1,
				   uint32_t color);

	private:
		size_t w_;
		size_t h_;
		std::vector<uint32_t> data_;
	};


}

# if 0

ImageRGBA *ImageRGBANewPNG(const char *path);
int ImageRGBASaveToPNG(ImageRGBA *img, const char *path);

# endif

#endif