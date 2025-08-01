// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <djvApp/Models/SettingsModel.h>

#include <tlTimelineUI/Window.h>

#include <tlTimeline/Player.h>

namespace tl
{
    namespace timelineui
    {
        class TimelineWidget;
    }
}

namespace djv
{
    namespace app
    {
        class App;
        class Viewport;

        //! Main window.
        class MainWindow : public tl::timelineui::Window
        {
            FEATHER_TK_NON_COPYABLE(MainWindow);

        protected:
            void _init(
                const std::shared_ptr<feather_tk::Context>&,
                const std::shared_ptr<App>&);

            MainWindow();

        public:
            ~MainWindow();

            //! Create a new main window.
            static std::shared_ptr<MainWindow> create(
                const std::shared_ptr<feather_tk::Context>&,
                const std::shared_ptr<App>&);

            //! Get the viewport.
            const std::shared_ptr<Viewport>& getViewport() const;

            //! Get the timeline widget.
            const std::shared_ptr<tl::timelineui::TimelineWidget>& getTimelineWidget() const;

            //! Focus the current frame widget.
            void focusCurrentFrame();

            //! Show the about dialog.
            void showAboutDialog();

            void setGeometry(const feather_tk::Box2I&) override;
            void keyPressEvent(feather_tk::KeyEvent&) override;
            void keyReleaseEvent(feather_tk::KeyEvent&) override;

        protected:
            void _drop(const std::vector<std::string>&) override;

        private:
            void _settingsUpdate(const MouseSettings&);
            void _settingsUpdate(const TimelineSettings&);
            void _settingsUpdate(const WindowSettings&);

            FEATHER_TK_PRIVATE();
        };
    }
}
