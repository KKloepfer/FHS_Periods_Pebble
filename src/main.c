//Include files from SDK
#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "PDutils.h"

//Define Universally Unique Identifier 
//	88a97cfd-2377-463a-84bd-b85eb4964063
#define UUID { 0x88, 0xa9, 0x7c, 0xfd, 0x23, 0x77, 0x46, 0x3a, 0x84, 0xbd, 0xb8, 0x5e, 0xb4, 0x96, 0x40, 0x63 }

//Declare structures for watch face elements
Window window;
TextLayer periodLayer;
TextLayer timeLayer;
 
//Declare variable for storing time string
static char hourText[] = "00:00";
static char wkDay[] = "Sat";
char* dayType;
char* period;
char* textUntil;
int timeuntilend;
	
	

//Set app info
PBL_APP_INFO(UUID, "FHS Periods", "Kai Kloepfer", 0, 1, DEFAULT_MENU_ICON, APP_INFO_WATCH_FACE);
							 
//UUID, app name, author, minor version, major version,
//use default icon, tell compiler this is a face
bool comp_time(int h1, int m1, int h2, int m2, int h3, int m3) {
	
	if((h1<=h2)  && (h2<=h3)) //Is start hour <= now hour <= end hour?
	{
		if((h1==h2) && (m2>=m1)) //If start hour = now hour, is now min >= start min ?
		{
			return true; 
		}
		if((h2==h3) && (m2<=m3)) //If end hour = now hour, if now min <= end min?
		{
			return true;
		}
		if((h1>h2) && (h2<h3)) //If start hour < now hour < end hour?
		{
			return true;
		}
	}
	else
	{
		return false;
	}
	return false;

}


void getPeriod(PblTm *tm) {
	
	time_t secconds_now;
	time_t secconds_end;
	PblTm time_end;
	PblTm difference;
	static char secconds[] = "";
	static char minutes[] = "";
	static char hours[] = "";
	dayType = "E";
	string_format_time(wkDay, sizeof(wkDay), "%a", tm);
	
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
	
	
	get_time(tm);
	//secconds_now=pmktime(tm);
	
	PblTm now;
	get_time(&now);
	period="E1";
	
	if(strcmp(dayType,"n")==0)
	{
		
		PblTm first_start;
		PblTm first_end;
		PblTm seccond_start;
		PblTm seccond_end;
		PblTm third_start;
		PblTm third_end;
		PblTm fourth_start;
		PblTm fourth_end;
		PblTm fifth_start;
		PblTm fifth_end;
		PblTm sixth_start;
		PblTm sixth_end;
		PblTm seventh_start;
		PblTm seventh_end;
		PblTm eighth_start;
		PblTm eighth_end;
		
		get_time(&first_start);
			first_start.tm_hour = 8;
			first_start.tm_min = 5;
		get_time(&first_end);
			first_end.tm_hour = 8;
			first_end.tm_min = 55;
		get_time(&seccond_start);
			seccond_start.tm_hour = 9;
			seccond_start.tm_min = 0;
		get_time(&seccond_end);
			seccond_end.tm_hour = 9;
			seccond_end.tm_min = 50;
		get_time(&third_start);
			third_start.tm_hour = 9;
			third_start.tm_min = 55;
		get_time(&third_end);
			third_end.tm_hour = 10;
			third_end.tm_min = 45;
		get_time(&fourth_start);
			fourth_start.tm_hour = 10;
			fourth_start.tm_min = 50;
		get_time(&fourth_end);
			fourth_end.tm_hour = 11;
			fourth_end.tm_min = 40;
		get_time(&fifth_start);
			fifth_start.tm_hour = 11;
			fifth_start.tm_min = 45;
		get_time(&fifth_end);
			first_end.tm_hour = 12;
			first_end.tm_min = 35;
		get_time(&sixth_start);
			sixth_start.tm_hour = 12;
			sixth_start.tm_min = 40;
		get_time(&sixth_end);
			sixth_end.tm_hour = 13;
			sixth_end.tm_min = 30;
		get_time(&seventh_start);
			first_end.tm_hour = 13;
			first_end.tm_min = 35;
		get_time(&seventh_end);
			seventh_start.tm_hour = 14;
			seventh_start.tm_min = 25;
		get_time(&eighth_start);
			eighth_start.tm_hour = 14;
			eighth_start.tm_min = 30;
		get_time(&eighth_end);
			eighth_end.tm_hour = 15;
			eighth_end.tm_min = 20;
		
		
		if (comp_time(first_start.tm_hour,first_start.tm_min,now.tm_hour,now.tm_min,first_end.tm_hour,first_end.tm_min))
		{
			period="1st";
			time_end=first_end;
			textUntil="Until End";
		}
		if (comp_time(first_end.tm_hour,first_end.tm_min,now.tm_hour,now.tm_min,seccond_start.tm_hour,seccond_start.tm_min))
		{
			period="Pass 1";
			time_end=seccond_start;
			textUntil="Until 2nd";
		}
		if (comp_time(seccond_start.tm_hour,seccond_start.tm_min,now.tm_hour,now.tm_min,seccond_end.tm_hour,seccond_end.tm_min))
		{
			period="2nd";
			time_end=seccond_end;
			textUntil="Until End";
		}
		if (comp_time(seccond_end.tm_hour,seccond_end.tm_min,now.tm_hour,now.tm_min,third_start.tm_hour,third_start.tm_hour))
		{
			period="Pass 2";
			time_end=third_start;
			textUntil="Until 3rd";
		}
		if (comp_time(third_start.tm_hour,third_start.tm_min,now.tm_hour,now.tm_min,third_end.tm_hour,third_end.tm_hour))
		{
			period="3rd";
			time_end=third_end;
			textUntil="Until End";
		}
		
		if (comp_time(third_end.tm_hour, third_end.tm_min,now.tm_hour,now.tm_min,fourth_start.tm_hour,fourth_start.tm_min))
		{
			period="Pass 3";
			time_end=fourth_start;
			textUntil="Until 4th";
		}
		if (comp_time(fourth_start.tm_hour,fourth_start.tm_min,now.tm_hour,now.tm_min,fourth_end.tm_hour,fourth_end.tm_min))
		{
			period="4th";
			time_end=fourth_end;
			textUntil="Until End";
		}
		if (comp_time(fourth_end.tm_hour,fourth_end.tm_min,now.tm_hour,now.tm_min,fifth_start.tm_hour,fifth_start.tm_min))
		{
			period="Pass 4";
			time_end=fifth_start;
			textUntil="Until 5th";
		}
		if (comp_time(fifth_start.tm_hour,fifth_start.tm_min,now.tm_hour,now.tm_min,fifth_end.tm_hour,fifth_end.tm_min))
		{
			period="5th";
			time_end=fifth_end;
			textUntil="Until End";
		}
		if (comp_time(fifth_end.tm_hour,fifth_end.tm_min,now.tm_hour,now.tm_min,sixth_start.tm_hour,sixth_start.tm_min))
		{
			period="Pass 5";
			time_end=sixth_start;
			textUntil="Until 6th";
		}
		if (comp_time(sixth_start.tm_hour,sixth_start.tm_min,now.tm_hour,now.tm_min,sixth_end.tm_hour,sixth_end.tm_min))
		{
			period="6th";
			time_end=sixth_end;
			textUntil="Until End";
		}
		if (comp_time(sixth_end.tm_hour,sixth_end.tm_min,now.tm_hour,now.tm_min,seventh_start.tm_hour,seventh_start.tm_min))
		{
			period="Pass 6";
			time_end=seventh_start;
			textUntil="Until 7th";
		}
		if (comp_time(seventh_start.tm_hour,seventh_start.tm_min,now.tm_hour,now.tm_min,seventh_end.tm_hour,seventh_start.tm_min))
		{
			period="7th";
			time_end=seventh_end;
			textUntil="Until End";
		}
		if (comp_time(seventh_end.tm_hour,seventh_end.tm_min,now.tm_hour,now.tm_min,eighth_start.tm_hour,eighth_start.tm_min))
		{
			period="Pass 7";
			time_end=eighth_start;
			textUntil="Until 8th";
		}
		if (comp_time(eighth_start.tm_hour,eighth_start.tm_min,now.tm_hour,now.tm_min,eighth_end.tm_hour,eighth_end.tm_min))
		{
			period="8th";
			time_end=eighth_end;
			textUntil="Until End";
		}	
		
		if (comp_time(eighth_end.tm_hour,eighth_end.tm_min,now.tm_hour,now.tm_min,23,59) || comp_time(00,01,now.tm_hour,now.tm_min,first_start.tm_hour,first_start.tm_min))
		{
			period="Out";
			time_end=eighth_end;
			textUntil="To School";
		}
		
		
		text_layer_set_text(&timeLayer, dayType);

	}
	
	if(strcmp(dayType,"w")==0)
	{
		period="Weekend";
	}
	
	time_end=time_end;
	
/* 
take time end and convert to secconds: secconds_end=((time_end.tm_min * 60)+(((time_end.tm_hour)*60)*60))
take time now and convert to secconds: secconds_now= ((now.tm_sec)+(now.tm_min * 60) + (((now.tm_hour)*60)*60)) 


*/
	//secconds_end = pmktime(&time_end);
		
	//difference.tm_hour = (((secconds_end-secconds_now)/60)/60);
	//snprintf(secconds, 100, "%d", difference.tm_hour);
	text_layer_set_text(&periodLayer, period);
}

/**
		* Function to set the time and date features on the TextLayers
		*/
void setTime(PblTm *t) {
	//PblTm *now;
	//get_time(&now);
	//const char *c;
	//sprintf(c, "%d", &now.tm_wday);
	
	
	
	//If user selects '24hr' in Settings on the watch
	if(clock_is_24h_style())
		string_format_time(hourText, sizeof(hourText), "%H:%M", t);
	else
		string_format_time(hourText, sizeof(hourText), "%I:%M", t);
	
	//Set the TextLayer text
	text_layer_set_text(&periodLayer, dayType);
}



/**
		* Handle function called every minute
		*/
void handle_minute_tick(AppContextRef ctx, PebbleTickEvent *t) {
	(void)ctx;
	
	PblTm time;	//Structure to store time info
	get_time(&time);	//Fill the structure with current time	
	//setTime(t->tick_time);	//Change time on 'zero seconds' mark
	getPeriod(t->tick_time);
}

/**
		* Handle function called every second
		*/
void handle_second_tick(AppContextRef ctx, PebbleTickEvent *t) {
	(void)ctx;
	
	PblTm time;	//Structure to store time info
	get_time(&time);	//Fill the structure with current time
	
	int seconds = time.tm_sec;	//Get the current number of seconds
	
	getPeriod(&time);
	
	if(seconds == 0)
		setTime(t->tick_time);	//Change the time on the 'zero seconds' mark
}

/**
		* Watch face initialisation handle function
		*/
void handle_init(AppContextRef ctx) {
	(void)ctx;	//This is not needed. Convert to void (nothing)
	
	//Initialise window
	window_init(&window, "Window Name");
	window_stack_push(&window, true);
	window_set_background_color(&window, GColorWhite);
	
	//Initialise TextLayers
	text_layer_init(&periodLayer, GRect(0, 5, 150, 45));
	text_layer_set_background_color(&periodLayer, GColorBlack);
	text_layer_set_text_color(&periodLayer, GColorWhite);
	text_layer_set_font(&periodLayer, 
						fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
	text_layer_set_text_alignment(&periodLayer, GTextAlignmentCenter);
	
	text_layer_init(&timeLayer, GRect(0, 60, 150, 100));
	text_layer_set_background_color(&timeLayer, GColorBlack);
	text_layer_set_text_color(&timeLayer, GColorWhite);
	text_layer_set_font(&timeLayer, 
						fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
	text_layer_set_text_alignment(&timeLayer, GTextAlignmentLeft);
	
	//Add to window
	layer_add_child(&window.layer, &periodLayer.layer);
	layer_add_child(&window.layer, &timeLayer.layer);
	
	//Set initial time so display isn't blank
	PblTm time;
	get_time(&time);
	getPeriod(&time);
	//setTime(&time); 
}

/**
		* Main Pebble app loop
		*/
void pbl_main(void *params) {
	PebbleAppHandlers handlers = {
		.init_handler = &handle_init,	//Register initialisation function
		
		.tick_info = {
			.tick_handler = &handle_second_tick,	//Register tick function
			.tick_units = SECOND_UNIT	//Specify to call every minute
		}
	};
	app_event_loop(params, &handlers);	//Continue from there!
}
