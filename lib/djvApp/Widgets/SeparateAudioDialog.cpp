// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2025 Darby Johnston
// All rights reserved.

#include <djvApp/Widgets/SeparateAudioDialog.h>

namespace djv
{
    namespace app
    {
        struct SeparateAudioDialog::Private
        {
            std::shared_ptr<SeparateAudioWidget> widget;
        };

        void SeparateAudioDialog::_init(
            const std::shared_ptr<feather_tk::Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IDialog::_init(
                context,
                "djv::app::SeparateAudioDialog",
                parent);
            FEATHER_TK_P();

            p.widget = SeparateAudioWidget::create(
                context,
                shared_from_this());

            p.widget->setCancelCallback(
                [this]
                {
                    close();
                });
        }

        SeparateAudioDialog::SeparateAudioDialog() :
            _p(new Private)
        {}

        SeparateAudioDialog::~SeparateAudioDialog()
        {}

        std::shared_ptr<SeparateAudioDialog> SeparateAudioDialog::create(
            const std::shared_ptr<feather_tk::Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<SeparateAudioDialog>(new SeparateAudioDialog);
            out->_init(context, parent);
            return out;
        }

        void SeparateAudioDialog::setCallback(const std::function<void(
            const tl::file::Path&,
            const tl::file::Path&)>& value)
        {
            _p->widget->setCallback(value);
        }
    }
}
