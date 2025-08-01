// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/Menu.h>

namespace djv
{
    namespace app
    {
        class HelpActions;

        //! Help menu.
        class HelpMenu : public feather_tk::Menu
        {
            FEATHER_TK_NON_COPYABLE(HelpMenu);

        protected:
            void _init(
                const std::shared_ptr<feather_tk::Context>&,
                const std::shared_ptr<HelpActions>&,
                const std::shared_ptr<IWidget>& parent);

            HelpMenu() = default;

        public:
            ~HelpMenu();

            static std::shared_ptr<HelpMenu> create(
                const std::shared_ptr<feather_tk::Context>&,
                const std::shared_ptr<HelpActions>&,
                const std::shared_ptr<IWidget>& parent = nullptr);
        };
    }
}
