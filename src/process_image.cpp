#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <glm/glm.hpp>

#include "image.h"

using namespace std;

#define GAMMA 2.2
#define EPLISON 0.001

glm::mat3 M = glm::mat3(
    0.4887180, 0.1762044, 0.0000000,     // column 1
    0.3106803, 0.8129847, 0.0102048,     // column 2
    0.2006017, 0.0108109, 0.9897952      // column 3
);
glm::mat3 Minv = glm::mat3(
     2.3706743, -0.5138850,  0.0052982,     // column 1
    -0.9000405,  1.4253036, -0.0146949,     // column 2
    -0.4706338,  0.0885814,  1.0093968      // column 3
);

// HW0 #3
// const Image& im: input image
// return the corresponding grayscale image
Image rgb_to_grayscale(const Image& im)
{
    assert(im.c == 3); // only accept RGB images
    Image gray(im.w,im.h,1); // create a new grayscale image (note: 1 channel)
  
    // TODO: calculate the pixels of 'gray'
    //NOT_IMPLEMENTED();

    const float red_weight = 0.299f, green_weight = 0.587f, blue_weight = 0.114;
    for (size_t y = 0; y < gray.h; y++)
    {
        for (size_t x = 0; x < gray.w; x++)
        {
            gray(x, y, 0) = red_weight * im(x, y, 0) + green_weight * im(x, y, 1) + blue_weight * im(x, y, 2);
        }
    }
    return gray;
}



// Example function that changes the color of a grayscale image
Image grayscale_to_rgb(const Image& im, float r, float g, float b)
  {
  assert(im.c == 1);
  Image rgb(im.w,im.h,3);
  
  for(int q2=0;q2<im.h;q2++)for(int q1=0;q1<im.w;q1++)
    {
    rgb(q1,q2,0)=r*im(q1,q2);
    rgb(q1,q2,1)=g*im(q1,q2);
    rgb(q1,q2,2)=b*im(q1,q2);
    }
  
  return rgb;
  }




// HW0 #4
// Image& im: input image to be modified in-place
// int c: which channel to shift
// float v: how much to shift
void shift_image(Image& im, int c, float v)
{
    assert(c>=0 && c<im.c); // needs to be a valid channel
  
    // TODO: shift all the pixels at the specified channe
    //NOT_IMPLEMENTED();

    for (size_t y = 0; y < im.h; y++)
    {
        for (size_t x = 0; x < im.w; x++)
        {
            im(x, y, c) = im(x, y, c) + v;
        }
    }
}

// HW0 #8
// Image& im: input image to be modified in-place
// int c: which channel to scale
// float v: how much to scale
void scale_image(Image& im, int c, float v)
{
    assert(c>=0 && c<im.c); // needs to be a valid channel
  
    // TODO: scale all the pixels at the specified channel
    //NOT_IMPLEMENTED();

    for (size_t y = 0; y < im.h; y++)
    {
        for (size_t x = 0; x < im.w; x++)
        {
            im(x, y, c) = im(x, y, c) * v;
        }
    }
}


// HW0 #5
// Image& im: input image to be modified in-place
void clamp_image(Image& im)
{
    // TODO: clamp all the pixels in all channel to be between 0 and 1
    //NOT_IMPLEMENTED();
    
    for (size_t ch = 0; ch < im.c; ch++)
    {
        for (size_t y = 0; y < im.h; y++)
        {
            for (size_t x = 0; x < im.w; x++)
            {
                if(isnan(im(x, y, ch))) { im(x, y, ch) = 0.0; }

                im(x, y, ch) = std::min(im(x, y, ch), 1.0f);
                im(x, y, ch) = std::max(im(x, y, ch), 0.0f);
            }
        }
    }
}

// These might be handy
float max(float a, float b, float c)
  {
  return max({a,b,c});
  }

float min(float a, float b, float c)
  {
  return min({a,b,c});
  }

inline bool is_float_equal(float a, float b) { return a - EPLISON < b && b < a + EPLISON; }
inline bool is_float_less_than_equal_zero(float a) { return a < EPLISON; }
// HW0 #6
// Image& im: input image to be modified in-place
void rgb_to_hsv(Image& im)
{
    assert(im.c==3 && "only works for 3-channels images");
  
    // TODO: Convert all pixels from RGB format to HSV format
    //NOT_IMPLEMENTED();
    for (int q2 = 0; q2 < im.h; q2++) 
    {
        for (int q1 = 0; q1 < im.w; q1++)
        {
            float &R = im(q1, q2, 0), &G = im(q1, q2, 1), &B = im(q1, q2, 2);

            // Value: the max intensity of the individual R, G, B channels
            float V = max(R, G, B);
            float m = min(R, G, B);
            float C = V - m;

            // Saturation: equal to the difference between the max and min and value
            float S;
            if (is_float_less_than_equal_zero(V))
            {
                S = 0.0f;
            }
            else {
                S = C / V;
            }

            // Hue:
            float H_prim = 0.0f;
            if (is_float_equal(R, V)) {
                H_prim = (G - B) / C;
            }
            else if (is_float_equal(G, V)) {
                H_prim = ((B - R) / C) + 2.0f;
            }
            else if (is_float_equal(B, V)) {
                H_prim = ((R - G) / C) + 4.0f;
            }

            float H = H_prim / 6.0f;
            if (is_float_less_than_equal_zero(C)) {
                H = 0.0f;
            }
            else if (H_prim < -TEST_EPS) {
                H = H + 1.0f;
            }

            R = H;
            G = S;
            B = V;
        }
    }
}

// HW0 #7
// Image& im: input image to be modified in-place
void hsv_to_rgb(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from HSV format to RGB format
  //NOT_IMPLEMENTED();

  for (int q2 = 0; q2 < im.h; q2++)
  {
      for (int q1 = 0; q1 < im.w; q1++)
      {
          float H = im(q1, q2, 0), S = im(q1, q2, 1), V = im(q1, q2, 2);

          float C = V * S;
          float X = C * (1.0f - std::abs(std::fmod(6.0f * H, 2.0f) - 1.0f));
          float m = V - C;

          float Rprim = 0.0f, Gprim = 0.0f, Bprim = 0.0f;
          if (H < (1.0f / 6.0f)) {
              Rprim = C; Gprim = X; Bprim = 0.0f;
          } else if ((1.0f / 6.0f) <= H && H < (2.0f / 6.0f)) {
              Rprim = X; Gprim = C; Bprim = 0.0f;
          } else if ((2.0f / 6.0f) <= H && H < (3.0f / 6.0f)) {
              Rprim = 0.0f; Gprim = C; Bprim = X;
          } else if ((3.0f / 6.0f) <= H && H < (4.0f / 6.0f)) {
              Rprim = 0.0f; Gprim = X; Bprim = C;
          } else if ((4.0f / 6.0f) <= H && H < (5.0f / 6.0f)) {
              Rprim = X; Gprim = 0.0f; Bprim = C;
          } else {
              Rprim = C; Gprim = 0.0f; Bprim = X;
          }

          float &R = im(q1, q2, 0), &G = im(q1, q2, 1), &B = im(q1, q2, 2);
          R = Rprim + m;
          G = Gprim + m;
          B = Bprim + m;
      }
  }
  }

void srgb_to_rgb(Image& im)
{
    for (int q2 = 0; q2 < im.h; q2++)
    {
        for (int q1 = 0; q1 < im.w; q1++)
        {
            glm::vec3 sRGB(
                im(q1, q2, 0),
                im(q1, q2, 1),
                im(q1, q2, 2)
            );

            glm::vec3 RGB = glm::pow(sRGB, glm::vec3(GAMMA));

            //RGB.r = isnan(RGB.r) ? 0.0 : RGB.r;
            //RGB.g = isnan(RGB.g) ? 0.0 : RGB.g;
            //RGB.b = isnan(RGB.b) ? 0.0 : RGB.b;

            bool is_valid = !glm::any(glm::isnan(RGB) || glm::isinf(RGB));
            PASSERT(is_valid, "sRGB->RGB: pixel coord (%d, %d) value (%.2f,%.2f,%.2f) INVALID", q1, q2, RGB.r, RGB.g, RGB.b);

            im(q1, q2, 0) = RGB.r;
            im(q1, q2, 1) = RGB.g;
            im(q1, q2, 2) = RGB.b;
        }
    }
}

void rgb_to_srgb(Image& im)
{
    for (int q2 = 0; q2 < im.h; q2++)
    {
        for (int q1 = 0; q1 < im.w; q1++)
        {
            glm::vec3 RGB(
                im(q1, q2, 0),
                im(q1, q2, 1),
                im(q1, q2, 2)
            );

            glm::vec3 sRGB = glm::pow(RGB, glm::vec3(1.0/GAMMA));

            sRGB.r = isnan(sRGB.r) ? 0.0 : sRGB.r;
            sRGB.g = isnan(sRGB.g) ? 0.0 : sRGB.g;
            sRGB.b = isnan(sRGB.b) ? 0.0 : sRGB.b;

            bool is_valid = !glm::any(glm::isnan(sRGB) || glm::isinf(sRGB));
            PASSERT(is_valid, "sRGB->RGB: pixel coord (%d, %d) value (%.2f,%.2f,%.2f) INVALID", q1, q2, sRGB.r, sRGB.g, sRGB.b);

            im(q1, q2, 0) = sRGB.r;
            im(q1, q2, 1) = sRGB.g;
            im(q1, q2, 2) = sRGB.b;
        }
    }

}

void rgb_to_xyz(Image& im)
{
    for (int q2 = 0; q2 < im.h; q2++)
    {
        for (int q1 = 0; q1 < im.w; q1++)
        {

            glm::vec3 RGB(
                im(q1, q2, 0),
                im(q1, q2, 1),
                im(q1, q2, 2)
            );

            glm::vec3 XYZ = M * RGB;

            bool is_valid = !glm::any(glm::isnan(XYZ) || glm::isinf(XYZ));
            PASSERT(is_valid, "RGB->XYZ: pixel coord (%d, %d) value (%.2f,%.2f,%.2f) INVALID", q1, q2, XYZ.x, XYZ.y, XYZ.z);

            im(q1, q2, 0) = XYZ.x;
            im(q1, q2, 1) = XYZ.y;
            im(q1, q2, 2) = XYZ.z;
        }
    }
}

void xyz_to_rgb(Image& im)
{
    for (int q2 = 0; q2 < im.h; q2++)
    {
        for (int q1 = 0; q1 < im.w; q1++)
        {
            glm::vec3 XYZ(
                im(q1, q2, 0),
                im(q1, q2, 1),
                im(q1, q2, 2)
            );

            glm::vec3 RGB = Minv * XYZ;

            bool is_valid = !glm::any(glm::isnan(RGB) || glm::isinf(RGB));
            PASSERT(is_valid, "XYZ->RGB: pixel coord (%d, %d) value (%.2f,%.2f,%.2f) INVALID", q1, q2, RGB.r, RGB.g, RGB.b);

            im(q1, q2, 0) = RGB.r;
            im(q1, q2, 1) = RGB.g;
            im(q1, q2, 2) = RGB.b;
        }
    }
}

void xyz_to_lch(Image& im)
{
    // Reference White E
    const float unprim = 4.0f / 19.0f;  // ≈ 0.2105
    const float vnprim = 9.0f / 19.0f;  // ≈ 0.4737 
    const float Yn = 1.0;

    for (int q2 = 0; q2 < im.h; q2++)
    {
        for (int q1 = 0; q1 < im.w; q1++)
        {
            float X = im(q1, q2, 0);
            float Y = im(q1, q2, 1);
            float Z = im(q1, q2, 2);

            // XYZ -> LAB/LUV
            const float uprim = (4.0 * X) / (X + (15.0 * Y) + (3.0 * Z));
            const float vprim = (9.0 * Y) / (X + (15.0 * Y) + (3.0 * Z));

            float Lstar = 0.0;
            if (Y / Yn <= 0.008856) {
                Lstar = 903.292 * (Y / Yn);
            }
            else {
                Lstar = (116.0 * std::powf((Y / Yn), (1.0 / 3.0))) - 16;
            }
            float ustar = (13.0 * Lstar) * (uprim - unprim);
            float vstar = (13.0 * Lstar) * (vprim - vnprim);

            // LUV -> LCH
            float C = std::sqrtf((ustar * ustar) + (vstar * vstar));
            float h = std::atan2(vstar, ustar);

            // output
            Lstar = isnan(Lstar) ? 0.0 : Lstar;
            C = isnan(C) ? 0.0 : C;
            h = isnan(h) ? 0.0 : h;
            
            bool is_valid = !(isnan(Lstar) || isnan(C) || isnan(h) ||
                isinf(Lstar) || isinf(C) || isinf(h));
            PASSERT(is_valid, "XYZ->LCH: pixel coord (%d, %d) value (%.2f,%.2f,%.2f) INVALID", q1, q2, Lstar, C, h);

            im(q1, q2, 0) = Lstar;
            im(q1, q2, 1) = C;
            im(q1, q2, 2) = h;
        }
    }
}

void lch_to_xyz(Image& im)
{
    const float e = 0.008856; // Intent of the CIE standard: 216/24389
    const float k = 903.3;    // Intent of the CIE standard: 24389/27
    const glm::vec3 r = glm::vec3(1.0, 1.0, 1.0);  // Illuminant E
    const float unot = (4.0 * r.x) / (r.x + (15.0 * r.y) + (3.0 * r.z));
    const float vnot = (9.0 * r.y) / (r.x + (15.0 * r.y) + (3.0 * r.z));

    for (int q2 = 0; q2 < im.h; q2++)
    {
        for (int q1 = 0; q1 < im.w; q1++)
        {
            float& L = im(q1, q2, 0), & C = im(q1, q2, 1), & H = im(q1, q2, 2);

            // LCH -> LUV  
            float u = C * glm::cos(H);
            float v = C * glm::sin(H);

            // LUV -> XYZ

            float Y = 0;
            if (L > (k*e))
            {
                Y = r.y * std::powf(((L + 16) / 116), 3);
            }
            else {
                Y = r.y * (L / k);
            }

            float a = (1.0 / 3.0) * (((52.0 * L) / (u + 13.0 * L * unot)) - 1.0);
            float b = (-5.0 * Y);
            float c = -(1.0 / 3.0);
            float d = Y * (((39.0 * L) / (v + 13 * L * vnot)) - 5.0);

            float X = (d - b) / (a - c);
            float Z = (X * a) + b;

            // output
            X = isnan(X) ? 0.0 : X;
            Y = isnan(Y) ? 0.0 : Y;
            Z = isnan(Z) ? 0.0 : Z;

            bool is_valid = !(isnan(X) || isnan(Y) || isnan(Z) ||
                isinf(X) || isinf(Y) || isinf(Z));
            PASSERT(is_valid, "XYZ->LCH: pixel coord (%d, %d) value (%.2f,%.2f,%.2f) INVALID", q1, q2, X, Y, Z);
            
            im(q1, q2, 0) = X;
            im(q1, q2, 1) = Y;
            im(q1, q2, 2) = Z;
        }
    }
}

// HW0 #9
// Image& im: input image to be modified in-place
void rgb_to_lch(Image& im)
{
    assert(im.c==3 && "only works for 3-channels images");
  
    // TODO: Convert all pixels from RGB format to LCH format
    //NOT_IMPLEMENTED();

    srgb_to_rgb(im);    // sRGB -> linear RGB
    rgb_to_xyz(im);     // RGB -> XYZ
    xyz_to_lch(im);     // XYZ -> LCH
}

// HW0 #9
// Image& im: input image to be modified in-place
void lch_to_rgb(Image& im)
{
    assert(im.c==3 && "only works for 3-channels images");
  
    // TODO: Convert all pixels from LCH format to RGB format
    //NOT_IMPLEMENTED();

    lch_to_xyz(im);     // LCH -> XYZ
    xyz_to_rgb(im);     // XYZ -> linear RGB
    rgb_to_srgb(im);    // linear RGB -> sRGB
}

// Implementation of member functions
void Image::clamp(void) { clamp_image(*this); }
void Image::shift(int c, float v) { shift_image(*this,c,v); }
void Image::scale(int c, float v) { scale_image(*this,c,v); }

void Image::HSVtoRGB(void) { hsv_to_rgb(*this); }
void Image::RGBtoHSV(void) { rgb_to_hsv(*this); }
void Image::LCHtoRGB(void) { lch_to_rgb(*this); }
void Image::RGBtoLCH(void) { rgb_to_lch(*this); }
