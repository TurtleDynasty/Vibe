#include <pebble.h>
#include "default_window.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_mood_two_id;
static TextLayer *s_textlayer_question;
static BitmapLayer *s_bitmaplayer_mood;
static MenuLayer *s_menulayer_options;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_image_mood_two_id = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MOOD_TWO_ID);
  // s_textlayer_question
  s_textlayer_question = text_layer_create(GRect(5, 40, 132, 20));
  text_layer_set_text(s_textlayer_question, "What does Lucky want?");
  text_layer_set_text_alignment(s_textlayer_question, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_question);
  
  // s_bitmaplayer_mood
  s_bitmaplayer_mood = bitmap_layer_create(GRect(42, 5, 60, 30));
  bitmap_layer_set_bitmap(s_bitmaplayer_mood, s_res_image_mood_two_id);
  bitmap_layer_set_background_color(s_bitmaplayer_mood, GColorWhite);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_mood);
  
  // s_menulayer_options
  s_menulayer_options = menu_layer_create(GRect(0, 72, 144, 96));
  menu_layer_set_click_config_onto_window(s_menulayer_options, s_window);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_menulayer_options);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_question);
  bitmap_layer_destroy(s_bitmaplayer_mood);
  menu_layer_destroy(s_menulayer_options);
  gbitmap_destroy(s_res_image_mood_two_id);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_default_window(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_default_window(void) {
  window_stack_remove(s_window, true);
}
