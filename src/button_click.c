#include <pebble.h>

static Window *window;
static TextLayer *text_layer;

static const uint32_t up_segments[] = { 100, 50, 200, 50, 50, 100, 200, 50, 100 }; //U-=. P=-
static const uint32_t select_segments[] = { 200, 50, 50, 100, 200, 50, 200 }; //O=. K==
static const uint32_t down_segments[] = { 100, 50, 50, 50, 100, 100, 200, 50, 50, 100, 100, 50, 200, 50, 200, 100, 50, 50, 100, 50, 200 }; //D-.- O=. W-== N.-=

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "OK");
  VibePattern pat = {
    .durations = select_segments,
    .num_segments = ARRAY_LENGTH(select_segments),
  };
  vibes_enqueue_custom_pattern(pat);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "UP");
  VibePattern pat = {
    .durations = up_segments,
    .num_segments = ARRAY_LENGTH(up_segments),
  };
  vibes_enqueue_custom_pattern(pat);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "DOWN");
  VibePattern pat = {
    .durations = down_segments,
    .num_segments = ARRAY_LENGTH(down_segments),
  };
  vibes_enqueue_custom_pattern(pat);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(text_layer, "Press a button");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
	.load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}