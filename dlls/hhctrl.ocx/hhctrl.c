/*
 * hhctrl implementation
 *
 * Copyright 2004 Krzysztof Foltman
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdarg.h>
#include <string.h>
#include "windef.h"
#include "winbase.h"
#include "wingdi.h"
#include "winnls.h"
#include "winuser.h"
#include "wine/debug.h"
#include "htmlhelp.h"

WINE_DEFAULT_DEBUG_CHANNEL(htmlhelp);

static const char *command_to_string(UINT command)
{
#define X(x) case x: return #x
    switch (command)
    {
        X( HH_DISPLAY_TOPIC );
        X( HH_DISPLAY_TOC );
        X( HH_DISPLAY_INDEX );
        X( HH_DISPLAY_SEARCH );
        X( HH_SET_WIN_TYPE );
        X( HH_GET_WIN_TYPE );
        X( HH_GET_WIN_HANDLE );
        X( HH_ENUM_INFO_TYPE );
        X( HH_SET_INFO_TYPE );
        X( HH_SYNC );
        X( HH_RESERVED1 );
        X( HH_RESERVED2 );
        X( HH_RESERVED3 );
        X( HH_KEYWORD_LOOKUP );
        X( HH_DISPLAY_TEXT_POPUP );
        X( HH_HELP_CONTEXT );
        X( HH_TP_HELP_CONTEXTMENU );
        X( HH_TP_HELP_WM_HELP );
        X( HH_CLOSE_ALL );
        X( HH_ALINK_LOOKUP );
        X( HH_GET_LAST_ERROR );
        X( HH_ENUM_CATEGORY );
        X( HH_ENUM_CATEGORY_IT );
        X( HH_RESET_IT_FILTER );
        X( HH_SET_INCLUSIVE_FILTER );
        X( HH_SET_EXCLUSIVE_FILTER );
        X( HH_INITIALIZE );
        X( HH_UNINITIALIZE );
        X( HH_PRETRANSLATEMESSAGE );
        X( HH_SET_GLOBAL_PROPERTY );
    default: return "???";
    }
#undef X
}

HWND WINAPI HtmlHelpW(HWND caller, LPCWSTR filename, UINT command, DWORD data)
{
    FIXME("(%p, %s, command=%s, data=%ld): stub\n",
          caller, debugstr_w( filename ),
          command_to_string( command ), data);

    switch (command)
    {
        case HH_DISPLAY_TOPIC:
        case HH_DISPLAY_TOC:
        case HH_DISPLAY_SEARCH:
        case HH_HELP_CONTEXT:
            MessageBoxA( NULL, "HTML Help functionality is currently unimplemented.\n\n"
                         "Try installing Internet Explorer, or using a native hhctrl.ocx with the Mozilla ActiveX control.",
                         "Wine", MB_OK | MB_ICONEXCLAMATION );
        default:
            return 0;
    }
}

HWND WINAPI HtmlHelpA(HWND caller, LPCSTR filename, UINT command, DWORD data)
{
    WCHAR *wfile = NULL;
    HWND result;

    if (filename)
    {
        DWORD len = MultiByteToWideChar( CP_ACP, 0, filename, -1, NULL, 0 );

        wfile = HeapAlloc( GetProcessHeap(), 0, (len+1) * sizeof(WCHAR));
        MultiByteToWideChar( CP_ACP, 0, filename, -1, wfile, len );
    }

    result = HtmlHelpW( caller, wfile, command, data );

    HeapFree( GetProcessHeap(), 0, wfile );
    return result;
}

int WINAPI doWinMain(HMODULE hMod, LPSTR cmdline)
{
    FIXME("(0x%x %s) stub!\n", (unsigned)hMod, debugstr_a(cmdline));
    return -1;
}
