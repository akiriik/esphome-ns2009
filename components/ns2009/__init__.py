import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID

DEPENDENCIES = ['i2c']

ns2009_ns = cg.esphome_ns.namespace('ns2009')
NS2009Component = ns2009_ns.class_('NS2009Touchscreen', cg.Component, i2c.I2CDevice)

CONF_NS2009_ID = 'ns2009_id'

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(NS2009Component),
}).extend(cv.COMPONENT_SCHEMA).extend(i2c.i2c_device_schema(0x48))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
