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
 * Contributor(s): Wade Majors <wade@ezri.org>
 *                 Rene Gollent
 *                 Todd Lair
 *                 Andrew Bazan
 */

#ifndef _VISION_H_
#define _VISION_H_

#include <Application.h>
#include <String.h>
#include <Locker.h>

#include "VisionBase.h"

class BFont;
class Theme;
class AboutWindow;
class SetupWindow;
class PrefsWindow;
class ClientWindow;
class NetworkWindow;
class DCCFileWindow;
class SettingsFile;
class BLocker;
class BNetEndpoint;

extern class VisionApp * vision_app;

class VisionApp : public BApplication
{
  public:
                            VisionApp (void);

    virtual void            MessageReceived (BMessage *);
    virtual void            AboutRequested (void);
    virtual bool            QuitRequested (void);
    virtual void            ArgvReceived (int32, char **);
    virtual void            ReadyToRun (void);
    
    void                    LoadURL (const char *);

    BString                 VisionVersion (int);
    
    void                    InitDefaults (void);
    
    void                    LoadDefaults (int32);

    void                    ClientFontFamilyAndStyle (int32, const char *,
                              const char *);
    void                    ClientFontSize (int32, float);
    const BFont             *GetClientFont (int32) const;
    
    const BRect             GetRect (const char *);
    status_t                SetRect (const char *, BRect);
    
    const char              *GetString (const char *) const; 
    status_t                SetString (const char *, int32 index, const char *); 
    
    rgb_color               GetColor (int32) const;
    void                    SetColor (int32, const rgb_color);

    BString                 GetEvent (int32) const;
    void                    SetEvent (int32, const char *);

    BString                 GetCommand (int32);
    void                    SetCommand (int32, const char *);

    bool                    GetBool (const char *);
    status_t                SetBool (const char *, bool);
    
    BMessage                GetNetwork (const char *);
    BMessage				GetNetwork (int32);
    status_t                SetNetwork (const char *, BMessage *);
    status_t                RemoveNetwork (const char *);
    bool                    CheckNetworkValid (const char *);

    Theme *                 ActiveTheme(void);
    
    void                    GetThreadName (int, BString &);
    
    void                    BenchOut (const char *);

    void                    Broadcast (BMessage *);
    void                    Broadcast (BMessage *, const char *, bool = false);
    
    void                    AddIdent (const char *, const char *);
    void                    RemoveIdent (const char *);
    const char *            GetIdent (const char *);
    static int32            Identity (void *);
    
    void                    AcquireDCCLock (void);
    void                    ReleaseDCCLock (void);
    
    BString                 fEvents[MAX_EVENTS];

    bool                    fDebugSettings;
    bool                    fDebugSend;
    bool                    fDebugRecv;
    bool                    fSettingsLoaded;
    bool                    fNumBench;

    // used for benchmarking
    int32                   fBench1;
    int32                   fBench2;
    
    ClientWindow            *pClientWin (void) const;

  private:
	void					InitSettings (void);
	bool                    SaveSettings (void);
    void                    ThreadStates (void);
    bool                    CheckStartupNetworks (void);
    
    volatile bool           fShuttingDown;

    AboutWindow             *fAboutWin;
    SetupWindow             *fSetupWin;
    ClientWindow            *fClientWin;
    PrefsWindow             *fPrefsWin;
    NetworkWindow           *fNetWin;
    DCCFileWindow           *fDccFileWin;
    
    SettingsFile			*fVisionSettings;
    
    rgb_color               fColors[MAX_COLORS];
    BFont                   *fClientFont[MAX_FONTS];
	BString					fCommands[MAX_COMMANDS];
	BMessage                fIdents;
	BLocker                 fIdentLock,
	                          fSettingsLock,
	                        fDccLock;
	thread_id               fIdentThread;
	int32                   fIdentSocket;
	Theme                   *fActiveTheme;
};

const uint32 VIS_NETWORK_DATA        = 'vndc';
const uint32 VIS_NETWORK_DEFAULTS    = 'vndd';

const int SET_SERVER    = 1;
const int SET_GENERAL   = 2;
const int SET_WINDOW    = 3;
const int SET_NOTIFY    = 4;
const int SET_FONT      = 5;
const int SET_COLOR     = 6;
const int SET_STRINGS   = 7;
const int SET_DCC       = 8;

const int VERSION_VERSION = 1;
const int VERSION_DATE    = 2;

const int THREAD_S = 1;  // socket
const int THREAD_L = 2;  // thread

#endif
