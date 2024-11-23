#include "ns2009.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace ns2009 {

static const char *const TAG = "ns2009";

void NS2009Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up NS2009...");
}

void NS2009Component::loop() {
  scan_();
}

bool NS2009Component::check_touched_() {
  do {
    this->raw_z = read_register_(NS2009_READ_Z);
  } while (this->raw_z == 0xFFF);  // Filter false positive readings
  
  this->touched = (this->raw_z > THRESHOLD_Z);
  return this->touched;
}

void NS2009Component::scan_() {
  check_touched_();
  if (!this->touched)
    return;

  this->raw_x = read_register_(NS2009_READ_X);
  this->x = map_data_(this->raw_x, this->min_x_, this->max_x_, 0, SCREEN_SIZE_X);
  
  this->raw_y = read_register_(NS2009_READ_Y);
  this->y = map_data_(this->raw_y, this->min_y_, this->max_y_, 0, SCREEN_SIZE_Y);
  
  if (this->flip_x)
    this->x = SCREEN_SIZE_X - this->x;
  if (this->flip_y)
    this->y = SCREEN_SIZE_Y - this->y;

  ESP_LOGD(TAG, "Touch: X=%d(%d) Y=%d(%d) Z=%d", this->x, this->raw_x, this->y, this->raw_y, this->raw_z);
}

unsigned int NS2009Component::read_register_(unsigned char command) {
  uint8_t data[2];
  if (!this->write(&command, 1))  // Send command
    return 0;
  if (!this->read(data, 2))  // Read response
    return 0;
  return (data[0] << 4) | (data[1] >> 4);
}

int NS2009Component::map_data_(int data, int in_min, int in_max, int out_min, int out_max) {
  if (data < in_min)
    data = in_min;
  if (data > in_max)
    data = in_max;
  return ((data-in_min)*(out_max-out_min))/(in_max-in_min)+out_min;
}

void NS2009Component::calibrate(int min_x, int max_x, int min_y, int max_y) {
  this->min_x_ = min_x;
  this->max_x_ = max_x;
  this->min_y_ = min_y;
  this->max_y_ = max_y;
}

void NS2009Component::dump_config() {
  ESP_LOGCONFIG(TAG, "NS2009:");
  ESP_LOGCONFIG(TAG, "  Calibration: X=%d-%d Y=%d-%d", this->min_x_, this->max_x_, this->min_y_, this->max_y_);
  ESP_LOGCONFIG(TAG, "  Flip X: %s", ONOFF(this->flip_x));
  ESP_LOGCONFIG(TAG, "  Flip Y: %s", ONOFF(this->flip_y));
  LOG_I2C_DEVICE(this);
}

}  // namespace ns2009
}  // namespace esphome
