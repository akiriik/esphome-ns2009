#include "ns2009.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ns2009 {

static const char *const TAG = "ns2009";

// Lisätään oma map funktio
int map_value(int value, int in_min, int in_max, int out_min, int out_max) {
  if (value < in_min) value = in_min;
  if (value > in_max) value = in_max;
  return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void NS2009Touchscreen::setup() {
  ESP_LOGCONFIG(TAG, "Setting up NS2009...");
}

void NS2009Touchscreen::loop() {
  do {
    this->raw_z_ = read_register_(NS2009_READ_Z);
  } while (this->raw_z_ == 0xFFF);  // Filter false readings

  this->touched = (this->raw_z_ > TOUCH_THRESHOLD);
  
  if (this->touched) {
    this->raw_x_ = read_register_(NS2009_READ_X);
    this->raw_y_ = read_register_(NS2009_READ_Y);
    
    // Käytetään omaa map_value funktiota
    this->x = map_value(this->raw_x_, 410, 3780, 0, 320);
    this->y = map_value(this->raw_y_, 360, 3770, 0, 240);
    
    ESP_LOGD(TAG, "Touch detected - X: %d, Y: %d, Z: %d", this->x, this->y, this->raw_z_);
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

void NS2009Touchscreen::dump_config() {
  ESP_LOGCONFIG(TAG, "NS2009:");
  LOG_I2C_DEVICE(this);
}

}  // namespace ns2009
}  // namespace esphome
