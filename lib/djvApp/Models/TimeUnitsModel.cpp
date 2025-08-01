// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2025 Darby Johnston
// All rights reserved.

#include <djvApp/Models/TimeUnitsModel.h>

#include <feather-tk/ui/Settings.h>

namespace djv
{
    namespace app
    {
        struct TimeUnitsModel::Private
        {
            std::shared_ptr<feather_tk::Settings> settings;
        };

        void TimeUnitsModel::_init(
            const std::shared_ptr<feather_tk::Context>& context,
            const std::shared_ptr<feather_tk::Settings>& settings)
        {
            tl::timeline::TimeUnitsModel::_init(context);
            FEATHER_TK_P();

            p.settings = settings;

            tl::timeline::TimeUnits units = tl::timeline::TimeUnits::Timecode;
            std::string s = tl::timeline::to_string(units);
            p.settings->get("/TimeUnits", s);
            tl::timeline::from_string(s, units);
            setTimeUnits(units);
        }

        TimeUnitsModel::TimeUnitsModel() :
            _p(new Private)
        {}

        TimeUnitsModel::~TimeUnitsModel()
        {
            FEATHER_TK_P();
            p.settings->set("/TimeUnits", tl::timeline::to_string(getTimeUnits()));
        }

        std::shared_ptr<TimeUnitsModel> TimeUnitsModel::create(
            const std::shared_ptr<feather_tk::Context>& context,
            const std::shared_ptr<feather_tk::Settings>& settings)
        {
            auto out = std::shared_ptr<TimeUnitsModel>(new TimeUnitsModel);
            out->_init(context, settings);
            return out;
        }
    }
}
