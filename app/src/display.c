#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <lvgl.h>
#include "images/my_image.c"  // Your image file

static void display_custom_image(void) {
    const struct device *display_dev = DEVICE_DT_GET(DT_CHOSEN(zmk_display));
    if (!device_is_ready(display_dev)) {
        return;  // Display not ready
    }

    lv_obj_clean(lv_scr_act());  // Clear screen

    lv_obj_t *img = lv_img_create(lv_scr_act());
    lv_img_set_src(img, &my_image);  // Set your image
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);  // Center it

    lv_task_handler();  // Update LVGL
    display_blanking_off(display_dev);  // Keep display on
}

// Call this on init or in a behavior
void zmk_display_init(void) {
    display_custom_image();
}
