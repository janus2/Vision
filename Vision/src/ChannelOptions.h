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
 *                 Rene Gollent
 */

#ifndef _CHANNELOPTIONS_H_
#define _CHANNELOPTIONS_H_

#ifdef GNOME_BUILD
#  include "gnome/CString.h"
#  include "gnome/Window.h"
#elif BEOS_BUILD
#  include <String.h>
#  include <Window.h>
#endif

class ChannelAgent;
class BView;

class ChannelOptions : public BWindow
{
  public:
                              ChannelOptions (const char *, ChannelAgent *);
    virtual                   ~ChannelOptions (void);
    virtual bool              QuitRequested (void);
      
  private:  
    void                      Init (void);
    ChannelAgent              *parent;
    const char                *chan_name;
    
    BView                     *bgView;
    BView                     *privilegesView;
    
    
};


#endif
