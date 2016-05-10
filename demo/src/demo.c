#include <pebble.h>
#include <linked-list.h>

static void init(void);
static void deinit(void);
static void window_load(Window *window);
static void window_unload(Window *window);
static void click_config_provider(void *context);
static void select_click_handler(ClickRecognizerRef recognizer, void *context);
static void up_click_handler(ClickRecognizerRef recognizer, void *context);
static void down_click_handler(ClickRecognizerRef recognizer, void *context);

static Window* window;
static Layer* layer;

static LinkedRoot* root;

int main(void) {
  init();
  app_event_loop();
  deinit();
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(window, true);

  root = linked_list_create_root();
}

static void deinit(void) {
  window_destroy(window);
}

static void window_load(Window *window) {
  layer = layer_create(GRect(0, 0, 144, 152));
}

static void window_unload(Window *window) {
  layer_destroy(layer);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
}
