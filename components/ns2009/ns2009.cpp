#include "ns2009.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ns2009 {

static const char *const TAG = "ns2009";

void NS2009Touchscreen::setup() {
  ESP_LOGCONFIG(TAG, "Setting up NS2009...");
}

void NS2009Touchscreen::loop() {
  if (read_touch_point_()) {
    if (this->raw_z_ > TOUCH_THRESHOLD) {
      // Map coordinates to screen space
      float x = (float)(this->raw_x_ - min_x_) / (max_x_ - min_x_) * screen_width_;
      float y = (float)(this->raw_y_ - min_y_) / (max_y_ - min_y_) * screen_height_;
      
      this->send_touch(x, y);
      ESP_LOGV(TAG, "Touch: x=%f y=%f", x, y);
    } else {
      this->send_release();
    }
  }
}

uint16_t NS2009Touchscreen::read_register_(uint8_t reg) {
  uint8_t data[2];
  if (!this->read_bytes(reg, data, 2)) {
    ESP_LOGW(TAG, "Reading register %02x failed!", reg);
    return 0;
  }
  return (data[0] << 4) | (data[1] >> 4);
}

bool NS2009Touchscreen::read_touch_point_() {
  do {
    this->raw_z_ = read_register_(NS2009_READ_Z);
  } while (this->raw_z_ == 0xFFF);  // Filter false readings
  
  if (this->raw_z_ > TOUCH_THRESHOLD) {
    this->raw_x_ = read_register_(NS2009_READ_X);
    this->raw_y_ = read_register_(NS2009_READ_Y);
    return true;
  }
  return false;
}

void NS2009Touchscreen::dump_config() {
  ESP_LOGCONFIG(TAG, "NS2009:");
  LOG_I2C_DEVICE(this);
  ESP_LOGCONFIG(TAG, "  Screen Size: %dx%d", screen_width_, screen_height_);
}

}  // namespace ns2009
}  // namespace esphome
