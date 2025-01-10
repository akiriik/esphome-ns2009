#pragma once

#include "esphome/core/automation.h"
#include "esphome/core/component.h"

namespace esphome {
namespace ns2009 {

struct NS2009Config {
  bool fast_reads{false};
};

class NS2009Component;

}  // namespace ns2009
}  // namespace esphome
