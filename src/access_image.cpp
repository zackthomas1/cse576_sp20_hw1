#include "image.h"

// HW0 #1
// const Image& im: input image
// int x,y: pixel coordinates
// int ch: channel of interest
// returns the 0-based location of the pixel value in the data array
int pixel_address(const Image& im, int x, int y, int ch)
{
    // TODO: calculate and return the index
    //NOT_IMPLEMENTED();

    // return index: channel * (image_height * image_width) + (y * image_width) + x
    return (ch * (im.h * im.w)) + (y * (im.w)) + x;
}

// HW0 #1
// const Image& im: input image
// int x,y,ch: pixel coordinates and channel of interest
// returns the value of the clamped pixel at channel ch
float get_clamped_pixel(const Image& im, int x, int y, int ch)
{
    // TODO: clamp the coordinates and return the correct pixel value
    //NOT_IMPLEMENTED();

    // clamp coordinates to valid range
    x = std::min(x, im.w - 1);
    x = std::max(x, 0);

    y = std::min(y, im.h - 1);
    y = std::max(y, 0);

    ch = std::min(ch, im.c - 1);
    ch = std::max(ch, 0);

    return im(x,y,ch);
}


// HW0 #1
// Image& im: input image
// int x,y,ch: pixel coordinates and channel of interest
void set_pixel(Image& im, int x, int y, int c, float value)
{
    // TODO: Only set the pixel to the value if it's inside the image
    //NOT_IMPLEMENTED();

    if ((0 <= x && x < im.w) && (0 <= y && y < im.h) && (0 <= c && c < im.c))
    {
        im(x, y, c) = value;
    }
}



// HW0 #2
// Copies an image
// Image& to: destination image
// const Image& from: source image
void copy_image(Image& to, const Image& from)
{
    // allocating data for the new image
    to.data = (float*)calloc(from.w*from.h*from.c,sizeof(float));
    to.c = from.c;
    to.h = from.h;
    to.w = from.w;

    // TODO: populate the remaining fields in 'to' and copy the data
    // You might want to check how 'memcpy' function works
    //NOT_IMPLEMENTED();

    size_t bytes_to_copy = to.w * to.h* to.c * sizeof(float);
    if (to.data != nullptr && from.data != nullptr && bytes_to_copy > 0)
    {
        memcpy(to.data, from.data, bytes_to_copy);
    }
    else {
        to.data = nullptr;
    }
}
