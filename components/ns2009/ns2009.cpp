#include "ns2009.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ns2009 {

static const char *const TAG = "ns2009";

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
    
    // Map raw values to screen coordinates
    this->x = map(this->raw_x_, 410, 3780, 0, 320);
    this->y = map(this->raw_y_, 360, 3770, 0, 240);
    
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
