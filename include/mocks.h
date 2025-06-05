#pragma once

#include <main.h>
#include <yukti.h>

YT_DECLARE_FUNC_VOID (mode_advance);
YT_DECLARE_FUNC (TestModes, mode_get);
YT_DECLARE_FUNC (bool, mode_is_dirty);

YT_DECLARE_FUNC_VOID (status_led_off);
YT_DECLARE_FUNC_VOID (status_led_on);
YT_DECLARE_FUNC_VOID (loop_delay, uint16_t);
YT_DECLARE_FUNC_VOID (holdoff_test_init);
YT_DECLARE_FUNC_VOID (runt_pulse_init);
YT_DECLARE_FUNC_VOID (runt_pulse_exit);
YT_DECLARE_FUNC (bool, is_switch_pressed);

YT_DECLARE_FUNC_VOID (hw_init);
YT_DECLARE_FUNC_VOID (usart_off);
YT_DECLARE_FUNC_VOID (usart_on);
YT_DECLARE_FUNC_VOID (usart_send_char, char);
YT_DECLARE_FUNC_VOID (usart_send_string, const char*);
YT_DECLARE_FUNC_VOID (holdoff_test_body, uint16_t);
YT_DECLARE_FUNC_VOID (runt_pulse_body, uint16_t, uint8_t, uint8_t);

YT_DEFINE_FUNC_VOID (mode_advance);
YT_DEFINE_FUNC (TestModes, mode_get);
YT_DEFINE_FUNC (bool, mode_is_dirty);

YT_DEFINE_FUNC_VOID (status_led_off);
YT_DEFINE_FUNC_VOID (status_led_on);
YT_DEFINE_FUNC_VOID (loop_delay, uint16_t);
YT_DEFINE_FUNC_VOID (holdoff_test_init);
YT_DEFINE_FUNC_VOID (runt_pulse_init);
YT_DEFINE_FUNC_VOID (runt_pulse_exit);
YT_DEFINE_FUNC (bool, is_switch_pressed);

YT_DEFINE_FUNC_VOID (hw_init);
YT_DEFINE_FUNC_VOID (usart_off);
YT_DEFINE_FUNC_VOID (usart_on);
YT_DEFINE_FUNC_VOID (usart_send_char, char);
YT_DEFINE_FUNC_VOID (usart_send_string, const char*);
YT_DEFINE_FUNC_VOID (holdoff_test_body, uint16_t);
YT_DEFINE_FUNC_VOID (runt_pulse_body, uint16_t, uint8_t, uint8_t);
