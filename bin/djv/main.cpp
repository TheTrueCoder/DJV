// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2024 Darby Johnston
// All rights reserved.

#include <djvApp/App.h>

#include <tlTimelineUI/Init.h>
#include <tlDevice/Init.h>

#include <feather-tk/core/Context.h>
#include <feather-tk/core/Error.h>

#include <iostream>

#if defined(_WINDOWS)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>
#endif // _WINDOWS

FEATHER_TK_MAIN()
{
    int r = 1;
    try
    {
        auto context = feather_tk::Context::create();
        tl::timelineui::init(context);
        tl::device::init(context);
        auto args = feather_tk::convert(argc, argv);
        auto app = djv::app::App::create(context, args);
        r = app->getExit();
        if (0 == r)
        {
            app->run();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    return r;
}

#if defined(_WINDOWS)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int)
{
    return wmain(__argc, __wargv);
}
#endif // _WINDOWS
