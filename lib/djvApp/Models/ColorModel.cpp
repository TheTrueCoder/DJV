// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2025 Darby Johnston
// All rights reserved.

#include <djvApp/Models/ColorModel.h>

#include <feather-tk/ui/Settings.h>

namespace djv
{
    namespace app
    {
        struct ColorModel::Private
        {
            std::shared_ptr<feather_tk::Settings> settings;
            std::shared_ptr<feather_tk::ObservableValue<tl::timeline::OCIOOptions> > ocioOptions;
            std::shared_ptr<feather_tk::ObservableValue<tl::timeline::LUTOptions> > lutOptions;
        };

        void ColorModel::_init(
            const std::shared_ptr<feather_tk::Context>& context,
            const std::shared_ptr<feather_tk::Settings>& settings)
        {
            FEATHER_TK_P();

            p.settings = settings;

            tl::timeline::OCIOOptions ocioOptions;
            p.settings->getT("/Color/OCIO", ocioOptions);
            p.ocioOptions = feather_tk::ObservableValue<tl::timeline::OCIOOptions>::create(ocioOptions);

            tl::timeline::LUTOptions lutOptions;
            p.settings->getT("/Color/LUT", lutOptions);
            p.lutOptions = feather_tk::ObservableValue<tl::timeline::LUTOptions>::create(lutOptions);
        }

        ColorModel::ColorModel() :
            _p(new Private)
        {}

        ColorModel::~ColorModel()
        {
            FEATHER_TK_P();
            p.settings->setT("/Color/OCIO", p.ocioOptions->get());
            p.settings->setT("/Color/LUT", p.lutOptions->get());
        }

        std::shared_ptr<ColorModel> ColorModel::create(
            const std::shared_ptr<feather_tk::Context>& context,
            const std::shared_ptr<feather_tk::Settings>& settings)
        {
            auto out = std::shared_ptr<ColorModel>(new ColorModel);
            out->_init(context, settings);
            return out;
        }

        const tl::timeline::OCIOOptions& ColorModel::getOCIOOptions() const
        {
            return _p->ocioOptions->get();
        }

        std::shared_ptr<feather_tk::IObservableValue<tl::timeline::OCIOOptions> > ColorModel::observeOCIOOptions() const
        {
            return _p->ocioOptions;
        }

        void ColorModel::setOCIOOptions(const tl::timeline::OCIOOptions& value)
        {
            _p->ocioOptions->setIfChanged(value);
        }

        const tl::timeline::LUTOptions& ColorModel::getLUTOptions() const
        {
            return _p->lutOptions->get();
        }

        std::shared_ptr<feather_tk::IObservableValue<tl::timeline::LUTOptions> > ColorModel::observeLUTOptions() const
        {
            return _p->lutOptions;
        }

        void ColorModel::setLUTOptions(const tl::timeline::LUTOptions& value)
        {
            _p->lutOptions->setIfChanged(value);
        }
    }
}
