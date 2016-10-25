#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>
#include "SimpleTextOverlay.hpp"

using namespace rendering;

namespace {

  class SimpleTextOverlay : public DrawableTextOverlay {
    std::string text;
  public:
    explicit SimpleTextOverlay();
    virtual ~SimpleTextOverlay() override {}

    virtual void update(const std::string& newText) override {
      text = newText;
    }

    virtual void draw() const override;
  };

  const char* font_file = ASTEROIDS_FONT_FILE;

  unsigned char ttf_buffer[1<<20];
  unsigned char temp_bitmap[512*512];

  stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs

  STBTT_DEF int stbtt_BakeFontBitmap(const unsigned char *data, int offset,  // font location (use offset=0 for plain .ttf)
                                     float pixel_height,                     // height of font in pixels
                                     unsigned char *pixels, int pw, int ph,  // bitmap to be filled in
                                     int first_char, int num_chars,          // characters to bake
                                     stbtt_bakedchar *chardata);             // you allocate this, it's num_chars long
// if return is positive, the first unused row of the bitmap
// if return is negative, returns the negative of the number of characters that fit
// if return is 0, no characters fit and no rows were used
// This uses a very crappy packing.

  SimpleTextOverlay::SimpleTextOverlay() {

  }

  void SimpleTextOverlay::draw() const {

  }
}

std::shared_ptr<DrawableTextOverlay> rendering::create_text_overlay() {
  return std::make_shared<SimpleTextOverlay>();
}
