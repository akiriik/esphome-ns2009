# NS2009 Touchscreen Component for ESPHome

This is an external component for ESPHome that adds support for NS2009 touchscreen controllers.

## Installation

Add this to your ESPHome configuration:

```yaml
external_components:
  - source: github://yourusername/esphome-ns2009
    components: [ns2009]

i2c:
  sda: GPIO21
  scl: GPIO22

touchscreen:
  - platform: ns2009
    i2c_id: bus_a
    id: touch
