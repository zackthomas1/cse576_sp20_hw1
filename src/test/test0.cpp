#include "../image.h"
#include "../utils.h"

#include <string>
using namespace std;

void test_get_pixel()
  {
  Image im = load_image("data/dots.png");
  // Test within image
  TEST(within_eps(0, im.clamped_pixel(0,0,0)));
  TEST(within_eps(1, im.clamped_pixel(1,0,1)));
  TEST(within_eps(0, im.clamped_pixel(2,0,1)));

  // Test padding
  TEST(within_eps(1, im.clamped_pixel(0,3,1)));
  TEST(within_eps(1, im.clamped_pixel(7,8,0)));
  TEST(within_eps(0, im.clamped_pixel(7,8,1)));
  TEST(within_eps(1, im.clamped_pixel(7,8,2)));
  }

void test_set_pixel()
  {
  Image im = load_image("data/dots.png");
  Image d(4,2,3);
  
  d.set_pixel(0,0,0,0); d.set_pixel(0,0,1,0); d.set_pixel(0,0,2,0);
  d.set_pixel(1,0,0,1); d.set_pixel(1,0,1,1); d.set_pixel(1,0,2,1);
  d.set_pixel(2,0,0,1); d.set_pixel(2,0,1,0); d.set_pixel(2,0,2,0);
  d.set_pixel(3,0,0,1); d.set_pixel(3,0,1,1); d.set_pixel(3,0,2,0);
  
  d.set_pixel(0,1,0,0); d.set_pixel(0,1,1,1); d.set_pixel(0,1,2,0);
  d.set_pixel(1,1,0,0); d.set_pixel(1,1,1,1); d.set_pixel(1,1,2,1);
  d.set_pixel(2,1,0,0); d.set_pixel(2,1,1,0); d.set_pixel(2,1,2,1);
  d.set_pixel(3,1,0,1); d.set_pixel(3,1,1,0); d.set_pixel(3,1,2,1);
  
  // Test images are same
  TEST(same_image(im, d));
  }

void test_grayscale()
  {
  Image im = load_image("data/colorbar.png");
  Image gray = rgb_to_grayscale(im);
  Image g = load_image("data/gray.png");
  g.save_image("output/gray_test");
  TEST(same_image(gray, g));
  }

void test_copy()
  {
  Image im = load_image("data/dog.jpg");
  Image c = im;
  TEST(same_image(im, c));
  }

void test_shift()
  {
  Image im = load_image("data/dog.jpg");
  Image c = im;
  shift_image(c, 1, .1);
  TEST(within_eps(im.data[0], c.data[0]));
  TEST(within_eps(im.data[im.w*im.h+13] + .1,  c.data[im.w*im.h + 13]));
  TEST(within_eps(im.data[2*im.w*im.h+72],  c.data[2*im.w*im.h + 72]));
  TEST(within_eps(im.data[im.w*im.h+47] + .1,  c.data[im.w*im.h + 47]));
  }

void test_rgb_to_hsv()
  {
  Image im = load_image("data/dog.jpg");
  rgb_to_hsv(im);
  Image hsv = load_image("data/dog.hsv.png");
  TEST(same_image(im, hsv));
  }

void test_hsv_to_rgb()
  {
  Image im = load_image("data/dog.jpg");
  Image c = im;
  rgb_to_hsv(im);
  hsv_to_rgb(im);
  TEST(same_image(im, c));
  }

void test_rgb2lch2rgb()
  {
  Image im = load_image("data/dog.jpg");
  Image c = im;
  
  rgb_to_lch(im);
  lch_to_rgb(im);
  TEST(same_image(im, c));

  im.save_image("output/rgb2lch2rgb_result");
  }


// Custom test case functions
// --------------------------
void test_getting_setting_pixel()
{
    Image im2 = load_image("data/dog.jpg");

    for (int i = 0; i < im2.w; i++)
    {
        for (int j = 0; j < im2.h; j++)
        {
            im2(i, j, 2) = 0.0f;
        }
    }
    im2.save_image("output/set_pixel_result");
}

void test_copy_image()
{
    Image im1 = load_image("data/dog.jpg");
    Image im2 = im1;

    im2.save_image("output/copy_image_result");
}

void test_shift_image()
{
    Image im1 = load_image("data/dog.jpg");

    shift_image(im1, 0, 0.4);
    shift_image(im1, 1, 0.4);
    shift_image(im1, 2, 0.4);
    clamp_image(im1);

    im1.save_image("output/shift_image_result");
}

void test_hsv_scale()
{
    Image im1 = load_image("data/dog.jpg");

    rgb_to_hsv(im1);
    //shift_image(im1, 1, 0.2f);
    scale_image(im1, 1, 4);
    clamp_image(im1);
    hsv_to_rgb(im1);

    im1.save_image("output/hsv_scale_result");
}

void test_rgb2xyz2rgb()
{
    Image im1 = load_image("data/dog.jpg");
    Image c = im1;

    srgb_to_rgb(im1);
    rgb_to_xyz(im1);
    xyz_to_rgb(im1);
    rgb_to_srgb(im1);

    TEST(same_image(im1, c));

    im1.save_image("output/rgb2xyz2rgb_result");
}

void test_lch_scale()
{
    Image im1 = load_image("data/dog.jpg");
    rgb_to_lch(im1);
    shift_image(im1, 1, 10.0f);
    //scale_image(im1, 1, 1.2);
    lch_to_rgb(im1);

    im1.save_image("output/lch_scale_result");
}

void test_rgb_to_lch()
{
    Image im1 = load_image("data/dog.jpg");
    rgb_to_lch(im1);
    im1.save_image("output/rgb_lch_result");
}


// Call test functions
// -------------------
void run_tests()
  {
  test_get_pixel();
  test_set_pixel();
  test_copy();
  test_shift();
  test_grayscale();
  test_rgb_to_hsv();
  test_hsv_to_rgb();
  test_rgb2lch2rgb();
  }

void run_custom_tests()
{
    test_getting_setting_pixel();
    test_copy_image();
    test_shift_image();
    test_hsv_scale();
    test_rgb2xyz2rgb();
    test_lch_scale();
    test_rgb_to_lch();
}

// Main
// ----
int main(int argc, char **argv)
  {
  // Image manipulation for fun testing.
  
  Image im2 = load_image("data/dog.jpg");
  for (int i=0; i<im2.w; i++)
      for (int j=0; j<im2.h; j++)
          im2(i, j, 0) = 0;
  im2.save_image("output/pixel_modifying_output");
  
  // Running example tests
  run_tests();
  run_custom_tests();
  printf("%d tests, %d passed, %d failed\n", tests_total, tests_total - tests_fail, tests_fail);

  return 0;
  }
