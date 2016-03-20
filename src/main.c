#include <pebble.h>

#define DOT 60
#define DASH 140
#define PAD 80
#define SPACE 190

static int mood=2;

// context words
static const uint32_t segments_space[] =   { 0, SPACE}; // no time on, SPACE time off
static const uint32_t segments_affirm[] =  { 35, 15, 35, 15, 35, 15, 35, 15, 35, 15 }; // purr
static const uint32_t segments_negate[] =  { 200, 10 };                          // long dash
// category words
static const uint32_t segments_what[] =    { DOT, PAD, DOT, PAD };               // ..
static const uint32_t segments_who[] =     { DOT, PAD, DASH, PAD };              // .-
static const uint32_t segments_where[] =   { DASH, PAD, DOT, PAD };              // -.
// uncoupled nouns
static const uint32_t segments_apple[] =   { DOT, PAD, DOT, PAD, 0, SPACE, DOT, PAD };                         // .
static const uint32_t segments_flute[] =   { DOT, PAD, DASH, PAD, 0, SPACE, DASH, PAD };                        // -
static const uint32_t segments_school[] =  { DASH, PAD, DOT, PAD, 0, SPACE, DOT, PAD, DOT, PAD, DOT, PAD };     // ...

// 2-coupled what nouns
static const uint32_t segments_kibble[] =  { DOT, PAD, DOT, PAD, 0, SPACE,
                                             DOT, PAD, DOT, PAD, DASH, PAD };    // ..-
static const uint32_t segments_pizza[] =   { DOT, PAD, DOT, PAD, 0, SPACE,
                                             DOT, PAD, DASH, PAD, DOT, PAD };    // .-.
static const uint32_t segments_beer[] =    { DOT, PAD, DOT, PAD, 0, SPACE,
                                             DASH, PAD, DASH, PAD, DOT, PAD };   // --.
static const uint32_t segments_salad[] =   { DOT, PAD, DOT, PAD, 0, SPACE,
                                             DASH, PAD, DOT, PAD, DASH, PAD };   // -.-
// 2-coupled who nouns
static const uint32_t segments_box[] =     { DOT, PAD, DASH, PAD, 0, SPACE,
                                             DOT, PAD, DOT, PAD, DASH, PAD };    // ..-
static const uint32_t segments_car[] =     { DOT, PAD, DASH, PAD, 0, SPACE,
                                             DOT, PAD, DASH, PAD, DOT, PAD };    // .-.
static const uint32_t segments_frisbee[] = { DOT, PAD, DASH, PAD, 0, SPACE,
                                             DASH, PAD, DOT, PAD, DOT, PAD };    // -..
static const uint32_t segments_doll[] =    { DOT, PAD, DASH, PAD, 0, SPACE,
                                             DOT, PAD, DASH, PAD, DASH, PAD };   // .--
// 2-coupled where nouns
static const uint32_t segments_park[] =    { DASH, PAD, DOT, PAD, 0, SPACE,
                                             DASH, PAD, DOT, PAD, DOT, PAD };    // -..
static const uint32_t segments_bed[] =     { DASH, PAD, DOT, PAD, 0, SPACE,
                                             DOT, PAD, DASH, PAD, DASH, PAD };   // .--
static const uint32_t segments_bar[] =     { DASH, PAD, DOT, PAD, 0, SPACE,
                                             DASH, PAD, DASH, PAD, DOT, PAD };   // --.
static const uint32_t segments_gym[] =     { DASH, PAD, DOT, PAD, 0, SPACE,
                                             DASH, PAD, DOT, PAD, DASH, PAD };   // -.-

static Window *window;
static TextLayer *text_layer;

static void my_vibrate(const uint32_t segments[], int length){
  VibePattern pat = {
    .durations = segments,
    .num_segments = length,
  };
  vibes_enqueue_custom_pattern(pat);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "a context word");
  my_vibrate(segments_affirm, ARRAY_LENGTH(segments_affirm));
  
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "a category word");
  VibePattern pat = {
    .durations = segments_what,
    .num_segments = ARRAY_LENGTH(segments_what),
  };
  vibes_enqueue_custom_pattern(pat);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "a noun");
  VibePattern pat = {
    .durations = segments_salad,
    .num_segments = ARRAY_LENGTH(segments_salad),
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
  
  static GBitmap *s_bitmap_mood_zero;
  s_bitmap_mood_zero = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MOOD_FIVE_ID);
  static BitmapLayer *s_bitmap_layer;
  s_bitmap_layer = bitmap_layer_create(GRect(42, 5, 60, 30));
  bitmap_layer_set_compositing_mode(s_bitmap_layer, GCompOpSet);
  bitmap_layer_set_bitmap(s_bitmap_layer, s_bitmap_mood_zero);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_bitmap_layer));
  
  
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