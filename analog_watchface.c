#include <pebble.h>
static Window *s_main_window;
static RotBitmapLayer *sec_rot;
static RotBitmapLayer *min_rot;
static RotBitmapLayer *hr_rot;
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;
static GBitmap *sec_hand_bitmap;
static GBitmap *min_hand_bitmap;
static GBitmap *hr_hand_bitmap;
int index = 0; 
static void anim_sec(struct tm *t);

static void update_time() {
  
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  anim_sec(tick_time);
  
}



static void anim_sec(struct tm *t){
gbitmap_destroy(s_background_bitmap);
bitmap_layer_destroy(s_background_layer);
gbitmap_destroy(sec_hand_bitmap);
rot_bitmap_layer_destroy(sec_rot);
rot_bitmap_layer_destroy(min_rot);
gbitmap_destroy(min_hand_bitmap);
rot_bitmap_layer_destroy(hr_rot);
gbitmap_destroy(hr_hand_bitmap);
  
s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_G_BACK);
s_background_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap); 
layer_add_child(window_get_root_layer(s_main_window), bitmap_layer_get_layer(s_background_layer));
  
sec_hand_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_G_SEC);
sec_rot =  rot_bitmap_layer_create(sec_hand_bitmap);
GPoint ic;
ic.x = 0; 
ic.y = 0; 
GRect r;
int32_t secAngle = t->tm_sec * TRIG_MAX_ANGLE / 60;
r = layer_get_frame((Layer *)sec_rot);
r.origin.x = 47 - r.size.w/2 + 57 * cos_lookup((secAngle + 3 * TRIG_MAX_ANGLE / 4)%TRIG_MAX_ANGLE) / TRIG_MAX_RATIO;
r.origin.y = 64 - r.size.h/2 + 57 * sin_lookup((secAngle + 3 * TRIG_MAX_ANGLE / 4)%TRIG_MAX_ANGLE) / TRIG_MAX_RATIO;
layer_set_frame((Layer *)sec_rot, r);
rot_bitmap_set_src_ic(sec_rot, ic);
rot_bitmap_layer_set_angle(sec_rot, secAngle);
layer_add_child(window_get_root_layer(s_main_window), (Layer*)sec_rot);

min_hand_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_G_MIN);
min_rot =  rot_bitmap_layer_create(min_hand_bitmap);
GRect rr;
int32_t minuteAngle = t->tm_min * TRIG_MAX_ANGLE / 60;
rr = layer_get_frame((Layer *)sec_rot);
rr.origin.x = 122 - rr.size.w/2 + 57 * cos_lookup((minuteAngle + 3 * TRIG_MAX_ANGLE / 4)%TRIG_MAX_ANGLE) / TRIG_MAX_RATIO;
rr.origin.y = 122 - rr.size.h/2 + 57 * sin_lookup((minuteAngle + 3 * TRIG_MAX_ANGLE / 4)%TRIG_MAX_ANGLE) / TRIG_MAX_RATIO;
layer_set_frame((Layer *)min_rot, rr);
rot_bitmap_layer_set_angle(min_rot, minuteAngle);
layer_add_child(window_get_root_layer(s_main_window), (Layer*)min_rot);  
  
hr_hand_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_G_HR);
hr_rot =  rot_bitmap_layer_create(hr_hand_bitmap);
GRect rrr;
int32_t hourAngle = ((t->tm_hour%12)*60 + t->tm_min) * TRIG_MAX_ANGLE / 720;
rrr = layer_get_frame((Layer *)hr_rot);
rrr.origin.x = 72 - rrr.size.w/2 + 58 * cos_lookup((hourAngle + 3 * TRIG_MAX_ANGLE / 4)%TRIG_MAX_ANGLE) / TRIG_MAX_RATIO;
rrr.origin.y = 84 - rrr.size.h/2 + 58 * sin_lookup((hourAngle + 3 * TRIG_MAX_ANGLE / 4)%TRIG_MAX_ANGLE) / TRIG_MAX_RATIO;
layer_set_frame((Layer *)hr_rot, rrr);
rot_bitmap_layer_set_angle(hr_rot, hourAngle);
layer_add_child(window_get_root_layer(s_main_window), (Layer*)hr_rot); 

}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {  
 
  update_time();
  
}

static void main_window_load(Window *window){
 
s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_G_BACK);
s_background_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap); 
layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_background_layer));


  
sec_hand_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_G_SEC);
sec_rot =  rot_bitmap_layer_create(sec_hand_bitmap);
GRect bounds = layer_get_bounds((Layer*)sec_rot);
const GPoint center = grect_center_point(&bounds);
GRect image_frame = (GRect) { .origin = center, .size = bounds.size };
image_frame.origin.x = 67; 
image_frame.origin.y = 64;
rot_bitmap_layer_set_angle(sec_rot, 0);
layer_set_frame((Layer*)sec_rot,image_frame);
rot_bitmap_set_compositing_mode(sec_rot, GCompOpAssignInverted);
layer_add_child(window_get_root_layer(window), (Layer*)sec_rot);

  
min_hand_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_G_MIN);
min_rot =  rot_bitmap_layer_create(min_hand_bitmap);
GRect boundss = layer_get_bounds((Layer*)min_rot);
const GPoint center2 = grect_center_point(&boundss);
GRect image_frame2 = (GRect) { .origin = center2, .size = boundss.size };
image_frame2.origin.x = 67; 
image_frame2.origin.y = 64;
rot_bitmap_layer_set_angle(min_rot, 0);
layer_set_frame((Layer*)min_rot,image_frame2);
rot_bitmap_set_compositing_mode(min_rot, GCompOpAssignInverted);
layer_add_child(window_get_root_layer(window), (Layer*)min_rot);  
  
hr_hand_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_G_HR);
hr_rot =  rot_bitmap_layer_create(hr_hand_bitmap);
GRect boundsss = layer_get_bounds((Layer*)hr_rot);
const GPoint center3 = grect_center_point(&boundsss);
GRect image_frame3 = (GRect) { .origin = center3, .size = boundsss.size };
image_frame3.origin.x = 67; 
image_frame3.origin.y = 64;
rot_bitmap_layer_set_angle(hr_rot, 0);
layer_set_frame((Layer*)hr_rot,image_frame3);
rot_bitmap_set_compositing_mode(hr_rot, GCompOpAssignInverted);
layer_add_child(window_get_root_layer(window), (Layer*)hr_rot);   
}


static void main_window_unload(Window *window){
 
gbitmap_destroy(s_background_bitmap);
bitmap_layer_destroy(s_background_layer);
gbitmap_destroy(sec_hand_bitmap);
rot_bitmap_layer_destroy(sec_rot);
rot_bitmap_layer_destroy(min_rot);
gbitmap_destroy(min_hand_bitmap);
rot_bitmap_layer_destroy(hr_rot);
gbitmap_destroy(hr_hand_bitmap);

}


static void init(){
  s_main_window = window_create();
  // Register with TickTimerService
tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  window_stack_push(s_main_window, true);
  update_time();
}

static void deinit(){  
  window_destroy(s_main_window);
}


int main(void){
  init();
  app_event_loop();
  deinit();
}
