#include "pebmain.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_14;
static TextLayer *text_layer;
static DictionaryIterator *iter;

static AppSync sync;

enum {
  SPY_KEY_START,
  SPY_KEY_STOP,
  IMG_START,
  IMG_DATA,
  IMG_STOP,
  IMG_MSG,
};





static uint8_t sync_buffer[1024];  
enum WeatherKey {
  WEATHER_ICON_KEY = 0x1  // TUPLE_CSTRING
};




static void my_select_click_handler(ClickRecognizerRef recognizer, void *context) {
 
  
int symbol = 0;


Tuplet symbol_tuple = TupletInteger(SPY_KEY_START, symbol);
  
  
 app_message_outbox_begin(&iter);

  
  dict_write_tuplet(iter, &symbol_tuple);
  dict_write_end(iter);

  app_message_outbox_send();



}








void click_config_provider(void *context) {
      window_single_click_subscribe(BUTTON_ID_SELECT, (ClickHandler) my_select_click_handler);

}




static void sync_error_callback(DictionaryResult dict_error, AppMessageResult app_message_error, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Sync Error: %d", app_message_error);
}

static void sync_tuple_changed_callback(const uint32_t key, const Tuple* new_tuple, const Tuple* old_tuple, void* context) {
    
  text_layer_set_text(text_layer, new_tuple->value->cstring);

    
  
}




   
void window_load(Window *window) {

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  
  
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  // text_layer
  text_layer = text_layer_create(GRect(25, 69, 100, 11));
  text_layer_set_text(text_layer, "Press Select");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_font(text_layer, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)text_layer);


  // Create the menu layer
  window_set_click_config_provider(s_window, click_config_provider);
  // Bind the menu layer's click config provider to the window for interactivity

  // Add it to the window for display
  
  
}

 void out_sent_handler(DictionaryIterator *sent, void *context) {
 APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message worked!");
 }


 void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
 APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Failed to Send!");
 }



      

    
  

     void in_received_handler(DictionaryIterator *received, void *context) { 
 
         
      


     }


 void in_dropped_handler(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Dropped!");
 }




static void init_msg(){
  
   app_message_register_inbox_dropped(in_dropped_handler);
   app_message_register_outbox_sent(out_sent_handler);
   app_message_register_outbox_failed(out_failed_handler);
   app_message_register_inbox_received(in_received_handler);
  
/* Tuplet initial_values[] = {
    TupletInteger(WEATHER_ICON_KEY, (uint8_t) 1)};
  app_sync_init(&sync, sync_buffer, sizeof(sync_buffer), initial_values, ARRAY_LENGTH(initial_values),
      sync_tuple_changed_callback, sync_error_callback, NULL);
      */

}




static void handle_window_unload(Window* window) {
    app_message_deregister_callbacks();
  app_sync_deinit(&sync); 
  text_layer_destroy(text_layer);
}

int main(void) {
 s_window = window_create();
  window_set_fullscreen(s_window, true);
    app_comm_set_sniff_interval(SNIFF_INTERVAL_REDUCED);
       app_message_open(256, 256);
  init_msg();
  
  
  window_set_window_handlers(s_window, (WindowHandlers) {
     .load = window_load,
    .unload = handle_window_unload,
  });
  
  
  window_stack_push(s_window, true);
  
      app_event_loop();

  
  window_destroy(s_window);
}


