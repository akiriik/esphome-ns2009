import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, touchscreen
from esphome.const import CONF_ID

DEPENDENCIES = ['i2c']
AUTO_LOAD = ['touchscreen']

ns2009_ns = cg.esphome_ns.namespace('ns2009')
NS2009Touchscreen = ns2009_ns.class_('NS2009Touchscreen', touchscreen.Touchscreen, i2c.I2CDevice)

CONFIG_SCHEMA = touchscreen.TOUCHSCREEN_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(NS2009Touchscreen),
}).extend(i2c.i2c_device_schema(0x48))

async def to_code(config):
    var = await touchscreen.new_touchscreen(config)
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
