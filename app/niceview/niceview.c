#include 
#include 
#include 

#define NICEVIEW_I2C_ADDR 0x3C

#define SDA_PIN DT_ALIAS_I2C_1_SDA_PIN
#define SCL_PIN DT_ALIAS_I2C_1_SCL_PIN

static const struct device i2c_dev;
static struct i2c_msg msgs[2];

const uint8_t lcd_init_cmds[] = {
    0xAE, //display off
    0xD5, //display divide ratio/osc. freq. mode
    0x50, //set divide ratio
    0xA8, //set multiplex ratio
    0x3F, //63
    0xD3, //display offset
    0x0,  //no offset
    0x40, //set display start line
    0x8D, //charge pump
    0x14, //enable
    0x20, //memory address mode
    0x00, //horizontal
    0xA1, //segment remap
    0xC8, //com scan direction
    0xDA, //set com pins
    0x12, //(disable left/right remap)
    0x81, //contrast control
    0xCF, //128
    0xD9, //precharge period
    0xF1, //15
    0xDB, //VCOMH Deselect Level
    0x40, //0.77Vcc
    0xA4, //display all on
    0xA6, //normal display
    0xAF  //display on
};

void niceview_init(void) {
  i2c_dev = device_get_binding(DT_LABEL(DT_ALIAS_I2C_1));

  msgs[0].flags = 0;
  msgs[0].len = sizeof(lcd_init_cmds);
  msgs[0].buf = (uint8_t *)lcd_init_cmds;

  msgs[1].flags = I2C_MSG_STOP;

  i2c_write(i2c_dev, &amp;msgs[0], 2, NICEVIEW_I2C_ADDR);
}