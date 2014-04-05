#include <pebble.h>
#include <PDUtils.h>
#include "pebble.h"
//#include <xprintf.h>	
	
Window *window;
TextLayer *text_layer_time_left;
TextLayer *text_layer_text_until;
TextLayer *text_layer_period;
Layer *line_layer;
static char time_left_string[]="00:00";
static char *date_text;
static char wkDay[] = "Err";
char* dayType;
char* period;
char* textUntil;


void handle_second_tick(struct tm *tick_time, TimeUnits units_changed);
bool comp_time (int time_start, int time_now, int time_end);

void line_layer_update_callback(Layer *layer, GContext* ctx) {
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
}

int time_seconds (){
	struct tm time_today;
	
	time_t seconds_today;
	time_t seconds_now;
	
	time(&seconds_now);
	time_today=*localtime(&seconds_now);
	time_today.tm_hour = 0;
	time_today.tm_min = 0;
	time_today.tm_sec = 0; 
	seconds_today= p_mktime(&time_today);
	//seconds_today=1396591200;
	return seconds_now - seconds_today;
}

bool comp_time (int time_start, int time_now, int time_end){
	if ((time_start<time_now) && (time_now<time_end)){
		return true;
	}
	else
	{
		return false;
	}
}

void day_type(){
	time_t now;
	struct tm * now_brokenout;
	
	time(&now);
	now_brokenout=localtime(&now);
	
	strftime(wkDay, sizeof(wkDay), "%a", now_brokenout);
	
	if (strcmp(wkDay,"Sun") == 0)
	{
		dayType = "w";
	}
	
	if (strcmp(wkDay,"Mon") == 0)
	{
		dayType = "n";
	}
	
	if (strcmp(wkDay,"Tue") == 0)
	{
		dayType = "n";
	}
	
	if (strcmp(wkDay,"Wed") == 0)
	{
		dayType = "1";
	}
	
	if (strcmp(wkDay,"Thu") == 0)
	{
		dayType = "2";
	}
	
	if (strcmp(wkDay,"Fri") == 0)
	{
		dayType = "n";
	}
	
	if (strcmp(wkDay,"Sat") == 0)
	{
		dayType = "w";
	}
}

void get_period(){
		
	int now;
	time_t time_left;
	now = time_seconds();
	time_t time_end = 0;
	day_type();
	struct tm *time_end_formatted;
	char *time_format="%R";
	if(strcmp(dayType,"w")==0){
		
		period="None!";
		time_end=0;
		textUntil=" ";
	}
	
	if(strcmp(dayType,"n")==0){	//Is dayType a normal day?
		//Start and End times of each period for normal day converted to seconds since 12:00AM
		int first_start = 29100;
		int first_end = 32100;
		int second_start = 32400;
		int second_end = 35400;
		int thrid_start = 35700;
		int third_end = 38700;
		int fourth_start = 39000;
		int fourth_end = 42000;
		int fifth_start = 42300;
		int fifth_end = 45300;
		int sixth_start = 45600;
		int sixth_end = 48600;
		int seventh_start = 48900;
		int seventh_end = 51900;
		int eighth_start = 52200;
		int eighth_end = 55200;
		
		if (comp_time(first_start,now,first_end))
		{
			period="1st";
			time_end=first_end;
			textUntil="Until End:";
		}
		if (comp_time(first_end,now,second_start))
		{
			period="Pass 1";
			time_end=second_start;
			textUntil="Until 2nd:";
		}
		if (comp_time(second_start,now,second_end))
		{
			period="2nd";
			time_end=second_end;
			textUntil="Until End:";
		}
		if (comp_time(second_end,now,thrid_start))
		{
			period="Pass 2";
			time_end=thrid_start;
			textUntil="Until 3rd:";
		}
		if (comp_time(thrid_start,now,third_end))
		{
			period="3rd";
			time_end=third_end;
			textUntil="Until End:";
		}
		
		if (comp_time(third_end,now,fourth_start))
		{
			period="Pass 3";
			time_end=fourth_start;
			textUntil="Until 4th:";
		}
		if (comp_time(fourth_start,now,fourth_end))
		{
			period="4th";
			time_end=fourth_end;
			textUntil="Until End:";
		}
		if (comp_time(fourth_end,now,fifth_start))
		{
			period="Pass 4";
			time_end=fifth_start;
			textUntil="Until 5th:";
		}
		if (comp_time(fifth_start,now,fifth_end))
		{
			period="5th";
			time_end=fifth_end;
			textUntil="Until End:";
		}
		if (comp_time(fifth_end,now,sixth_start))
		{
			period="Pass 5";
			time_end=sixth_start;
			textUntil="Until 6th:";
		}
		if (comp_time(sixth_start,now,sixth_end))
		{
			period="6th";
			time_end=sixth_end;
			textUntil="Until End:";
		}
		if (comp_time(sixth_end,now,seventh_start))
		{
			period="Pass 6";
			time_end=seventh_start;
			textUntil="Until 7th:";
		}
		if (comp_time(seventh_start,now,seventh_end))
		{
			period="7th";
			time_end=seventh_end;
			textUntil="Until End:";
		}
		if (comp_time(seventh_end,now,eighth_start))
		{
			period="Pass 7";
			time_end=eighth_start;
			textUntil="Until 8th:";
		}
		if (comp_time(eighth_start,now,eighth_end))
		{
			period="8th";
			time_end=eighth_end;
			textUntil="Until End:";
		}	
		
		if (comp_time(eighth_end,now,86340))
		{
			period="Out";
			time_end=now;
			textUntil="Sleep";
		}
		if (comp_time(00000,now,first_start))
		{
			period="Out";
			time_end=first_start;
			textUntil="To School2";
		}
		
	}
	if (time_end == 0)
	{
		time_left=0;
	}
	else
	{
		if (time_left>=3600)
		{
			time_format = "%R";
		}
		if(time_left<3600)
		{
			time_format = "%M:%S";
		}
		time_left=time_end-now;
	}
	
	time_end_formatted = localtime(&time_left);
	strftime(time_left_string, sizeof(time_left_string), time_format , time_end_formatted);

	text_layer_set_text(text_layer_period, period);
	text_layer_set_text(text_layer_time_left, time_left_string);
	text_layer_set_text(text_layer_text_until, textUntil);
}

void handle_init(void) {
	// Create a window
	window = window_create();
	
	window_set_background_color(window, GColorBlack);
	Layer *window_layer = window_get_root_layer(window);
	//////////////////////////	
	//Create Text Layer
	text_layer_period = text_layer_create(GRect(0, 0, 144, 154));
	
	// Set the text, font, and text alignment
	text_layer_set_text(text_layer_period, "period");
	text_layer_set_text_color(text_layer_period, GColorWhite);
	text_layer_set_background_color(text_layer_period, GColorBlack);
	text_layer_set_font(text_layer_period, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
	text_layer_set_text_alignment(text_layer_period, GTextAlignmentCenter);
	
	// Add the text layer to the window
	layer_add_child(window_layer, text_layer_get_layer(text_layer_period));
	////////////////////////////
	GRect line_frame = GRect(8, 53, 128, 2);
  	line_layer = layer_create(line_frame);
	layer_set_update_proc(line_layer, line_layer_update_callback);
  	layer_add_child(window_layer, line_layer);
	
	////////////////////////////
	//Create Text Layer
	text_layer_text_until = text_layer_create(GRect(0, 70, 144, 154));
	
	// Set the text, font, and text alignment
	text_layer_set_text(text_layer_text_until, "text_until");
	text_layer_set_text_color(text_layer_text_until, GColorWhite);
	text_layer_set_background_color(text_layer_text_until, GColorBlack);
	text_layer_set_font(text_layer_text_until, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer_text_until, GTextAlignmentCenter);
	
	// Add the text layer to the window
	layer_add_child(window_layer, text_layer_get_layer(text_layer_text_until));
	////////////////
	
	//////////////////////////	
	//Create Text Layer
	text_layer_time_left = text_layer_create(GRect(0, 100, 144, 154));
	
	// Set the text, font, and text alignment
	text_layer_set_text(text_layer_time_left, "time_left_string");
	text_layer_set_text_color(text_layer_time_left, GColorWhite);
	text_layer_set_background_color(text_layer_time_left, GColorBlack);
	text_layer_set_font(text_layer_time_left, fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS));
	text_layer_set_text_alignment(text_layer_time_left, GTextAlignmentCenter);
	
	// Add the text layer to the window
	layer_add_child(window_layer, text_layer_get_layer(text_layer_time_left));
	
	
	
	// Push the window
	window_stack_push(window, true);
	
	//Suscribe to second tick service
	tick_timer_service_subscribe(SECOND_UNIT, handle_second_tick);
	handle_second_tick(NULL, SECOND_UNIT);
	
	//DEBUG
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Finished Init");
}

void handle_second_tick(struct tm *tick_time, TimeUnits units_changed) {
  	get_period();
}

void handle_deinit(void) {
  text_layer_destroy(text_layer_time_left);
  window_destroy(window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
