typedef union {
  uint32_t raw;
  struct {
    bool     rgb_anim :1; //在EEPROM定义变量，记录RGB开关状态
  };
} user_config_t;

user_config_t user_config;

void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user(); //从EEPROM读取状态
}

void eeconfig_init_user(void) {  
  user_config.raw = 0;
  user_config.rgb_anim = 1;     //清除EEPROM，默认状态
  eeconfig_update_user(user_config.raw); 
}

enum my_keycodes {
  RGB_ANIM = SAFE_RANGE,  //自定义一个键码
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_ANIM:
      if (record->event.pressed) {  //如果按下
        user_config.rgb_anim ^= 1; //改变状态
        eeconfig_update_user(user_config.raw);  //更新状态
      } else { //如果松开
      }
      return true;
    default:
      return true;
    }   
}

void rgb_matrix_indicators_kb(void) {
    if(user_config.rgb_anim == 0) {  //RGB关闭了
        rgb_matrix_set_color_all(0, 0, 0);  //所有RGB灯都关闭
    }
    if (host_keyboard_led_state().caps_lock) { //如果大写锁定开启
        rgb_matrix_set_color(0, 255, 0, 0);  //设置某个灯某颜色
    }
}
