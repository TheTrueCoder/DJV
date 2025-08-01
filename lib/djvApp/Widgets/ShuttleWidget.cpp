// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2025 Darby Johnston
// All rights reserved.

#include <djvApp/Widgets/ShuttleWidget.h>

#include <feather-tk/core/Format.h>

#include <optional>

namespace djv
{
    namespace app
    {
        struct ShuttleWidget::Private
        {
            std::string iconPrefix;
            std::vector<std::shared_ptr<feather_tk::Image> > iconImages;
            int iconIndex = 0;
            float iconScale = 1.F;
            std::function<void(bool)> activeCallback;
            std::function<void(int)> callback;
        };

        void ShuttleWidget::_init(
            const std::shared_ptr<feather_tk::Context>& context,
            const std::string& iconPrefix,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(
                context,
                "djv::app::ShuttleWidget",
                parent);
            FEATHER_TK_P();

            _setMouseHoverEnabled(true);
            _setMousePressEnabled(true);

            p.iconPrefix = iconPrefix;
        }

        ShuttleWidget::ShuttleWidget() :
            _p(new Private)
        {}

        ShuttleWidget::~ShuttleWidget()
        {}

        std::shared_ptr<ShuttleWidget> ShuttleWidget::create(
            const std::shared_ptr<feather_tk::Context>& context,
            const std::string& iconPrefix,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ShuttleWidget>(new ShuttleWidget);
            out->_init(context, iconPrefix, parent);
            return out;
        }

        void ShuttleWidget::setActiveCallback(const std::function<void(bool)>& value)
        {
            _p->activeCallback = value;
        }

        void ShuttleWidget::setCallback(const std::function<void(int)>& value)
        {
            _p->callback = value;
        }

        void ShuttleWidget::sizeHintEvent(const feather_tk::SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            FEATHER_TK_P();

            if (event.displayScale != p.iconScale)
            {
                p.iconScale = event.displayScale;
                p.iconImages.clear();
            }
            if (p.iconImages.empty())
            {
                for (int i = 0; i < 8; ++i)
                {
                    p.iconImages.push_back(event.iconSystem->get(
                        feather_tk::Format("{0}{1}").
                        arg(p.iconPrefix).
                        arg(i),
                        event.displayScale));
                }
            }

            feather_tk::Size2I sizeHint;
            if (!p.iconImages.empty())
            {
                sizeHint = p.iconImages.front()->getSize();
            }
            _setSizeHint(sizeHint);
        }

        void ShuttleWidget::drawEvent(const feather_tk::Box2I& drawRect, const feather_tk::DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            FEATHER_TK_P();
            const feather_tk::Box2I& g = getGeometry();
            if (p.iconIndex >= 0 && p.iconIndex < p.iconImages.size())
            {
                const feather_tk::Size2I& iconSize = p.iconImages.front()->getSize();
                const feather_tk::Box2I g2(
                    g.min.x + g.w() / 2 - iconSize.w / 2,
                    g.min.y + g.h() / 2 - iconSize.h / 2,
                    iconSize.w,
                    iconSize.h);
                event.render->drawImage(
                    p.iconImages[p.iconIndex],
                    g2,
                    event.style->getColorRole(isEnabled() ?
                        feather_tk::ColorRole::Text :
                        feather_tk::ColorRole::TextDisabled));
            }
            if (_isMousePressed())
            {
                event.render->drawRect(
                    g,
                    event.style->getColorRole(feather_tk::ColorRole::Pressed));
            }
            else if (_isMouseInside())
            {
                event.render->drawRect(
                    g,
                    event.style->getColorRole(feather_tk::ColorRole::Hover));
            }
        }

        void ShuttleWidget::mouseEnterEvent(feather_tk::MouseEnterEvent& event)
        {
            IWidget::mouseEnterEvent(event);
            _setDrawUpdate();
        }

        void ShuttleWidget::mouseLeaveEvent()
        {
            IWidget::mouseLeaveEvent();
            _setDrawUpdate();
        }

        void ShuttleWidget::mouseMoveEvent(feather_tk::MouseMoveEvent& event)
        {
            IWidget::mouseMoveEvent(event);
            FEATHER_TK_P();
            const feather_tk::Box2I& g = getGeometry();
            if (_isMousePressed() && g.isValid())
            {
                const int d = event.pos.x - _getMousePressPos().x;
                const int i = d / (g.w() / 4);
                if (i != p.iconIndex)
                {
                    p.iconIndex = i % p.iconImages.size();
                    _setDrawUpdate();
                    if (p.callback)
                    {
                        p.callback(i);
                    }
                }
            }
        }

        void ShuttleWidget::mousePressEvent(feather_tk::MouseClickEvent& event)
        {
            IWidget::mousePressEvent(event);
            FEATHER_TK_P();
            _setDrawUpdate();
            if (p.activeCallback)
            {
                p.activeCallback(true);
            }
        }

        void ShuttleWidget::mouseReleaseEvent(feather_tk::MouseClickEvent& event)
        {
            IWidget::mouseReleaseEvent(event);
            FEATHER_TK_P();
            p.iconIndex = 0;
            _setDrawUpdate();
            if (p.activeCallback)
            {
                p.activeCallback(false);
            }
        }
    }
}
