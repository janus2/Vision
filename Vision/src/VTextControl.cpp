/* 
 * The contents of this file are subject to the Mozilla Public 
 * License Version 1.1 (the "License"); you may not use this file 
 * except in compliance with the License. You may obtain a copy of 
 * the License at http://www.mozilla.org/MPL/ 
 * 
 * Software distributed under the License is distributed on an "AS 
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or 
 * implied. See the License for the specific language governing 
 * rights and limitations under the License. 
 * 
 * The Original Code is Vision. 
 * 
 * The Initial Developer of the Original Code is The Vision Team.
 * Portions created by The Vision Team are
 * Copyright (C) 1999, 2000, 2001 The Vision Team.  All Rights
 * Reserved.
 * 
 * Contributor(s): Wade Majors <guru@startrek.com>
 */

// Class description:
// VTextControl is a derivative of BTextControl which adds context menus

// it's intention is to be fully compliant and portable, so it can easily
// be dropped into other applications as well.

#include <PopUpMenu.h>
#include <MenuItem.h>
#include <View.h>

#include <Window.h>

#include <stdio.h>

#include "VTextControl.h"

VTextControl::VTextControl (BRect frame, const char *name, const char *label,
                            const char *text, BMessage *vtcmessage,
                            uint32 resizingMode, uint32 flags)
  : BTextControl(
    frame,
    name,
    label,
    text,
    vtcmessage,
    resizingMode,
    flags)
{
}

VTextControl::VTextControl (BMessage *data)
  : BTextControl(
    data)
{

}

void
VTextControl::AllAttached (void)
{

  myPopUp = new BPopUpMenu("Context Menu", false, false);

  //BMenuItem *item;
  myPopUp->AddItem (new BMenuItem("Cut", new BMessage (B_CUT)));
  myPopUp->AddItem (new BMenuItem("Copy", new BMessage (B_COPY)));
  myPopUp->AddItem (new BMenuItem("Paste", new BMessage (B_PASTE)));
  myPopUp->AddSeparatorItem();
  myPopUp->AddItem (new BMenuItem("Select All", new BMessage (B_SELECT_ALL)));
  
  myPopUp->SetFont (be_plain_font);
  myPopUp->SetTargetForItems (TextView());

  TextView()->AddFilter (new VTextControlFilter (this));

}

VTextControl::~VTextControl (void)
{
  delete myPopUp;
}

///////////////////////////
// Filter //

VTextControlFilter::VTextControlFilter (VTextControl *parentcontrol)
 : BMessageFilter (B_ANY_DELIVERY, B_ANY_SOURCE),

  parent (parentcontrol)
{
  //
}

filter_result
VTextControlFilter::Filter (BMessage *msg, BHandler **handler)
{
  filter_result result (B_DISPATCH_MESSAGE);
  switch (msg->what)
  {
    case B_MOUSE_DOWN:
    {
      BPoint myPoint;
      uint32 mousebuttons;
      int32  keymodifiers (0);
      parent->Parent()->GetMouse (&myPoint, &mousebuttons);
      
      bool handled (false);

      msg->FindInt32 ("modifiers", &keymodifiers);  

      if (mousebuttons == B_SECONDARY_MOUSE_BUTTON
      && (keymodifiers & B_SHIFT_KEY)   == 0
      && (keymodifiers & B_OPTION_KEY)  == 0
      && (keymodifiers & B_COMMAND_KEY) == 0
      && (keymodifiers & B_CONTROL_KEY) == 0)
      {
        parent->myPopUp->Go (
          parent->Parent()->ConvertToScreen (myPoint),
          true,
          false);
        handled = true;
      }
      
      if (handled)
        result = B_SKIP_MESSAGE;
      
      break;   
    }
  }

  return result;

}

VTextControlFilter::~VTextControlFilter (void)
{
 //
}