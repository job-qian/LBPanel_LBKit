/* --------------------------------------------------------------------------
 *
 * Panel application for little board
 * Copyright (C) 2018, Anthony Lee, All Rights Reserved
 *
 * This software is a freeware; it may be used and distributed according to
 * the terms of The MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * File: TApplication.cpp
 * Description:
 *
 * --------------------------------------------------------------------------*/

#include "TApplication.h"
#include "TMainPageView.h"
#include "TMenuPageView.h"
#include "TCommandsPageView.h"


TApplication::TApplication(const LBAppSettings *settings)
	: LBApplication(settings),
	  fScreenOffTimeout(0)
{
	bool use24Hours = false;
	bool showSeconds = false;
	int32 thermalZone = 0;
	bool useLCDStyle = false;

	for(int32 k = 0; k < settings->CountItems(); k++)
	{
		BString name, value, options;

		if(settings->GetItemAt(k, &name, &value, &options) != B_OK) continue;
		if(name.FindFirst("LBPanel::") != 0) continue;
		name.Remove(0, 9);

		if(name == "MenuItem" && options.Length() > 0) do
		{
			BString args;

			int32 found = options.FindFirst(",");
			if(found == 0) break;
			if(found > 0)
			{
				if(found < options.Length() - 1)
					args.SetTo(options.String() + found + 1);
				options.Truncate(found);
			}

			t_menu_item *item = (t_menu_item*)malloc(sizeof(t_menu_item));
			if(item == NULL || fCustomMenu.AddItem(item) == false)
			{
				if(item != NULL) free(item);
				break;
			}

			item->title = strdup(value.String());
			item->command = strdup(options.String());
			item->args = (args.Length() > 0) ? strdup(args.String()) : NULL;
		} while(false);

		if(name == "ScreenOffTimeout")
		{
			fScreenOffTimeout = (int32)atoi(value.String());
		}
		else if(name == "24Hours")
		{
			use24Hours = (value == "1" || value.ICompare("true") == 0);
		}
		else if(name == "ShowSeconds")
		{
			showSeconds = (value == "1" || value.ICompare("true") == 0);
		}
		else if(name == "ThermalZone")
		{
			thermalZone = (int32)atoi(value.String());
		}
		else if(name == "LCDStyle")
		{
			useLCDStyle = (value == "1" || value.ICompare("true") == 0);
		}
	}

	TMainPageView *mainPageView = new TMainPageView();
	if(use24Hours) mainPageView->Set24Hours();
	if(showSeconds) mainPageView->ShowSeconds();
	if(useLCDStyle) mainPageView->SetLCDStyle();
	mainPageView->SetThermalZone(thermalZone);

	AddPageView(new TCommandsPageView(), true);
	AddPageView(mainPageView, false);
	AddPageView(new TMenuPageView(), false);
}


TApplication::~TApplication()
{
	EmptyCustomMenu();
}


void
TApplication::EmptyCustomMenu()
{
	for(int32 k = 0; k < fCustomMenu.CountItems(); k++)
	{
		t_menu_item *item = (t_menu_item*)fCustomMenu.ItemAt(k);

		if(item->title) free(item->title);
		if(item->command) free(item->command);
		if(item->args) free(item->args);
		free(item);
	}
	fCustomMenu.MakeEmpty();
}


int32
TApplication::CountCustomMenuItems() const
{
	return fCustomMenu.CountItems();
}


const t_menu_item*
TApplication::CustomMenuItemAt(int32 index) const
{
	t_menu_item *item = (t_menu_item*)fCustomMenu.ItemAt(index);
	return item;
}


void
TApplication::Pulse()
{
	// TODO
}


void
TApplication::MessageReceived(BMessage *msg)
{
	switch(msg->what)
	{
		case LBK_APP_SETTINGS_UPDATED:
			// TODO: update custom menu, screen off timeout, etc.
			break;

		default:
			LBApplication::MessageReceived(msg);
	}
};

