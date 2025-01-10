#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace ns2009 {

// Rekisterit
static const uint8_t REG_X = 0xC0;  
static const uint8_t REG_Y = 0xD0;
// Poistetaan Z-rekisterit koska emme tarvitse niitä

class NS2009Component : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  void loop() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  // Uusi optio nopeille luvuille
  void set_fast_reads(bool fast_reads) { fast_reads_ = fast_reads; }

  float x{0};
  float y{0};
  // Poistetaan z koska emme tarvitse sitä

 protected:
  uint8_t read_byte_(uint8_t a_register);
  bool fast_reads_{false};  // Uusi muuttuja nopeille luvuille
};

}  // namespace ns2009
}  // namespace esphome
