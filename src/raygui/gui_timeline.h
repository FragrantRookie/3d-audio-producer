/*******************************************************************************************
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2021 Pablo Camacho
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/



#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui/raygui.h"

#include <stdlib.h>
#include <string.h>

//3d Object Timeline

#ifndef GUI_3D_OBJECT_TIMELINE_H
#define GUI_3D_OBJECT_TIMELINE_H

typedef struct 
{
	bool editMode;
	
	bool valueChanged;
	bool addPoint;
	bool showPropertiesBox;
	
	//frame selection variables, 
	size_t current_timeline_frame;
	bool frameSelected;
	float frameDrawX;
	
} TimelineSettings;

typedef struct 
{	
	size_t max_num_frames;
	
	bool* array_points_ptr; //array of points to render
	
	bool showPropertiesBox;
	
	//where to draw points
	int draw_start_x;
	int draw_y;
	
} TimelineParameterSettings;



#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

TimelineSettings InitTimelineSettings();
TimelineParameterSettings InitTimelineParameterSettings(size_t max_num_frames, bool* points_ptr, int x, int y);

//Draws timeline 
//returns if timeline was clicked on
bool Gui_Timeline(TimelineSettings* settings);

bool Gui_Timeline_Parameter(TimelineParameterSettings* settings);

#ifdef __cplusplus
}
#endif

#endif

#if defined(GUI_3D_OBJECT_TIMELINE)

TimelineSettings InitTimelineSettings()
{
	TimelineSettings settings = {0};
	
	settings.editMode = true;
	settings.current_timeline_frame = 0;
	
	return settings;
}

TimelineParameterSettings InitTimelineParameterSettings(size_t max_num_frames, bool* points_ptr, int x, int y)
{
	TimelineParameterSettings settings = { 0 };
	
	settings.array_points_ptr = points_ptr;
	settings.max_num_frames = max_num_frames;
	
	settings.draw_start_x = x;
	settings.draw_y = y;
	
	return settings;
}

bool Gui_Timeline(TimelineSettings* settings)
{
	//draw timeline
	//horizontal axis is the time
	//vertical axis is nothing

	//draw box with background color
	float screen_height = GetScreenHeight();
	Rectangle drawAreaRect = {0, 400 , GetScreenWidth(), screen_height};

	DrawRectangleRec(drawAreaRect, Fade(GRAY, 0.8f));

	float leftBound = 200;
	Rectangle mouseArea = {leftBound, 400 , GetScreenWidth(), screen_height};

	//if in edit mode
	if(settings->editMode)
	{
		//draw cursor line where mouse pointer is
	
		Vector2 mousePoint = GetMousePosition();

		//select frame based on where mouse pointer is clicked on 
		if (CheckCollisionPointRec(mousePoint, mouseArea))
		{
			float cursor_x = mousePoint.x;
			if(cursor_x < leftBound){cursor_x = leftBound;}

			Color cursor_color = BLACK;
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				settings->frameSelected = !settings->frameSelected;
				
				if(settings->frameSelected)
				{
					settings->frameDrawX = cursor_x;
				}
			}
			
			if(settings->frameSelected)
			{
				cursor_x = settings->frameDrawX;
				cursor_color = YELLOW;
				
				if(settings->frameDrawX >= 200)
				{
					settings->current_timeline_frame = static_cast <size_t> ( (settings->frameDrawX - 200) / 2);
				}
			}
			
			DrawRectangle(cursor_x,400,2,screen_height,cursor_color);
		}
		else
		{
			if(settings->frameSelected)
			{
				Color cursor_color = YELLOW;
				DrawRectangle(settings->frameDrawX,400,2,screen_height,cursor_color);
				
				if(settings->frameDrawX >= 200)
				{
					settings->current_timeline_frame = static_cast <size_t> ( (settings->frameDrawX - 200) / 2);
				}
				
			}
			
			
		}
	}
	//else if not in edit mode, i.e. playback mode
	else
	{
		//draw cursor at current timeline frame
		float cursor_x = (settings->current_timeline_frame * 2) + 200;
		
		DrawRectangle(cursor_x,400,2,screen_height,BLACK);
	}
}

bool Gui_Timeline_Parameter(TimelineParameterSettings* settings)
{

	//draw points
	
	bool* element_ptr = settings->array_points_ptr;
	size_t i = 0;
	
	for(i = 0; i < settings->max_num_frames; i++)
	{
		if(*element_ptr)
		{
			DrawCircle(settings->draw_start_x + 2*i, settings->draw_y, 2, BLACK);
		}
		
		element_ptr++;
	}
	
	//if mouse click on point in timeline and add point is false
		//show properties box to true

		
	//if show properties box bool is true
		//draw properties box
		//show the contents of the point in timeline such as position and rotation.
	
}

#endif