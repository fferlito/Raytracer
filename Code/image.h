#ifndef IMAGE_H_
#define IMAGE_H_

#include "triple.h"

#include <string>
#include <vector>

class Image
{
    std::vector<Color> d_pixels;
    unsigned d_width;
    unsigned d_height;

    public:
        Image(unsigned width = 0, unsigned height = 0);
        Image(std::string const &filename);

        // normal accessors
        void put_pixel(unsigned x, unsigned y, Color const &c);
        Color get_pixel(unsigned x, unsigned y) const;

        // Handier accessors
        // Usage: color = img(x,y);
        //        img(x,y) = color;
        Color const &operator()(unsigned x, unsigned y) const;
        Color &operator()(unsigned x, unsigned y);

        unsigned width() const;
        unsigned height() const;
        unsigned size() const;

        // Normalized accessors, unsignederval is (0...1, 0...1)
        // usefull for texture access
        Color const &colorAt(float x, float y) const;

        void write_png(std::string const &filename) const;
        void read_png(std::string const &filename);

    private:
        inline unsigned index(unsigned x, unsigned y) const
        {
            return y * d_width + x;
        }

        inline unsigned findex(float x, float y) const
        {
            return index(
                static_cast<unsigned>(x * (d_width - 1)),
                static_cast<unsigned>(y * (d_height - 1)));
        }

};

#endif
