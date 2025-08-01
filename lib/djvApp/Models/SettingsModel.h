// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <djvApp/Shortcuts.h>

#include <tlTimelineUI/IItem.h>

#include <tlTimeline/Player.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/FileBrowser.h>
#include <feather-tk/core/ObservableValue.h>

#include <tlIO/SequenceIO.h>
#if defined(TLRENDER_FFMPEG)
#include <tlIO/FFmpeg.h>
#endif // TLRENDER_FFMPEG
#if defined(TLRENDER_USD)
#include <tlIO/USD.h>
#endif // TLRENDER_USD

#include <nlohmann/json.hpp>

namespace feather_tk
{
    class Context;
    class Settings;
}

namespace djv
{
    namespace app
    {
        //! Advanced settings.
        struct AdvancedSettings
        {
            bool compat = true;
            size_t audioBufferFrameCount = tl::timeline::PlayerOptions().audioBufferFrameCount;
            size_t videoRequestMax = 16;
            size_t audioRequestMax = 16;

            bool operator == (const AdvancedSettings&) const;
            bool operator != (const AdvancedSettings&) const;
        };

        //! Export render size.
        enum class ExportRenderSize
        {
            Default,
            _1920_1080,
            _3840_2160,
            _4096_2160,
            Custom,

            Count,
            First = Default
        };
        FEATHER_TK_ENUM(ExportRenderSize);

        //! Get an export render size.
        feather_tk::Size2I getSize(ExportRenderSize);

        //! Export file type.
        enum class ExportFileType
        {
            Image,
            Sequence,
            Movie,

            Count,
            First = Image
        };
        FEATHER_TK_ENUM(ExportFileType);

        //! Export settings.
        struct ExportSettings
        {
            std::string directory;
            ExportRenderSize renderSize = ExportRenderSize::Default;
            feather_tk::Size2I customSize = feather_tk::Size2I(1920, 1080);
            ExportFileType fileType = ExportFileType::Image;

            std::string imageBaseName = "render.";
            size_t imageZeroPad = 0;
            std::string imageExtension = ".tif";

            std::string movieBaseName = "render";
            std::string movieExtension = ".mov";
            std::string movieCodec = "mjpeg";

            bool operator == (const ExportSettings&) const;
            bool operator != (const ExportSettings&) const;
        };

        //! File browser settings.
        struct FileBrowserSettings
        {
            bool nativeFileDialog = true;
            std::string path;
            feather_tk::FileBrowserOptions options;
            std::string extension;

            bool operator == (const FileBrowserSettings&) const;
            bool operator != (const FileBrowserSettings&) const;
        };

        //! Image sequence settings.
        struct ImageSequenceSettings
        {
            tl::timeline::ImageSequenceAudio audio = tl::timeline::Options().imageSequenceAudio;
            std::vector<std::string> audioExtensions = tl::timeline::Options().imageSequenceAudioExtensions;
            std::string audioFileName = tl::timeline::Options().imageSequenceAudioFileName;
            size_t maxDigits = 9;
            tl::io::SequenceOptions io;

            bool operator == (const ImageSequenceSettings&) const;
            bool operator != (const ImageSequenceSettings&) const;
        };

        //! Miscellaneous settings.
        struct MiscSettings
        {
            bool tooltipsEnabled = true;
            bool showSetup = true;

            bool operator == (const MiscSettings&) const;
            bool operator != (const MiscSettings&) const;
        };

        //! Mouse actions.
        enum class MouseAction
        {
            PanView,
            CompareWipe,
            ColorPicker,
            FrameShuttle,

            Count,
            First = ColorPicker
        };
        FEATHER_TK_ENUM(MouseAction);

        //! Mouse action binding.
        struct MouseActionBinding
        {
            MouseActionBinding() = default;
            MouseActionBinding(
                int button,
                feather_tk::KeyModifier modifier = feather_tk::KeyModifier::None);

            int button = 0;
            feather_tk::KeyModifier modifier = feather_tk::KeyModifier::None;

            bool operator == (const MouseActionBinding&) const;
            bool operator != (const MouseActionBinding&) const;
        };

        //! Mouse settings.
        struct MouseSettings
        {
            std::map<MouseAction, MouseActionBinding> bindings =
            {
                { MouseAction::ColorPicker, MouseActionBinding(0) },
                { MouseAction::PanView, MouseActionBinding(0, feather_tk::KeyModifier::Control) },
                { MouseAction::FrameShuttle, MouseActionBinding(0, feather_tk::KeyModifier::Shift) },
                { MouseAction::CompareWipe, MouseActionBinding(0, feather_tk::KeyModifier::Alt) }
            };

            float wheelScale = 1.1F;

            bool operator == (const MouseSettings&) const;
            bool operator != (const MouseSettings&) const;
        };

        //! Keyboard shortcuts settings.
        struct ShortcutsSettings
        {
            ShortcutsSettings();

            std::vector<Shortcut> shortcuts;

            bool operator == (const ShortcutsSettings&) const;
            bool operator != (const ShortcutsSettings&) const;
        };

        //! Style settings.
        struct StyleSettings
        {
            float displayScale = 0.F;
            feather_tk::ColorControls colorControls;
            feather_tk::ColorStyle colorStyle = feather_tk::ColorStyle::Dark;
            std::map<feather_tk::ColorRole, feather_tk::Color4F> customColorRoles = feather_tk::getCustomColorRoles();

            bool operator == (const StyleSettings&) const;
            bool operator != (const StyleSettings&) const;
        };

        //! Timeline thumbnails.
        enum class TimelineThumbnails
        {
            None,
            Small,
            Medium,
            Large,

            Count,
            First = None
        };
        FEATHER_TK_ENUM(TimelineThumbnails);

        //! Get the timeline thumbnails size.
        int getTimelineThumbnailsSize(TimelineThumbnails);

        //! Get the timeline waveform size.
        int getTimelineWaveformSize(TimelineThumbnails);

        //! Timeline settings.
        struct TimelineSettings
        {
            bool minimize = false;
            bool editable = false;
            bool frameView = true;
            bool scrollBars = true;
            bool autoScroll = true;
            bool stopOnScrub = false;
            TimelineThumbnails thumbnails = TimelineThumbnails::Small;

            bool operator == (const TimelineSettings&) const;
            bool operator != (const TimelineSettings&) const;
        };

        //! Window settings.
        struct WindowSettings
        {
            feather_tk::Size2I size = feather_tk::Size2I(1920, 1080);
            bool fileToolBar = true;
            bool compareToolBar = true;
            bool windowToolBar = true;
            bool viewToolBar = true;
            bool toolsToolBar = true;
            bool tabBar = true;
            bool timeline = true;
            bool bottomToolBar = true;
            bool statusToolBar = true;
            float splitter = .7F;
            float splitter2 = .7F;

            bool operator == (const WindowSettings&) const;
            bool operator != (const WindowSettings&) const;
        };

        //! Settings model.
        class SettingsModel : public std::enable_shared_from_this<SettingsModel>
        {
            FEATHER_TK_NON_COPYABLE(SettingsModel);

        protected:
            void _init(
                const std::shared_ptr<feather_tk::Context>&,
                const std::shared_ptr<feather_tk::Settings>&);

            SettingsModel();

        public:
            ~SettingsModel();

            //! Create a new model.
            static std::shared_ptr<SettingsModel> create(
                const std::shared_ptr<feather_tk::Context>&,
                const std::shared_ptr<feather_tk::Settings>&);

            //! Save the settings. Settings are also saved on exit.
            void save();

            //! Reset to default values.
            void reset();

            //! \name Advanced
            ///@{

            const AdvancedSettings& getAdvanced() const;
            std::shared_ptr<feather_tk::IObservableValue<AdvancedSettings> > observeAdvanced() const;
            void setAdvanced(const AdvancedSettings&);

            ///@}

            //! \name Cache
            ///@{

            const tl::timeline::PlayerCacheOptions& getCache() const;
            std::shared_ptr<feather_tk::IObservableValue<tl::timeline::PlayerCacheOptions> > observeCache() const;
            void setCache(const tl::timeline::PlayerCacheOptions&);

            ///@}

            //! \name Export
            ///@{

            const ExportSettings& getExport() const;
            std::shared_ptr<feather_tk::IObservableValue<ExportSettings> > observeExport() const;
            void setExport(const ExportSettings&);

            ///@}

            //! \name File Browser
            ///@{

            const FileBrowserSettings& getFileBrowser() const;
            std::shared_ptr<feather_tk::IObservableValue<FileBrowserSettings> > observeFileBrowser() const;
            void setFileBrowser(const FileBrowserSettings&);

            ///@}

            //! \name Image Sequences
            ///@{

            const ImageSequenceSettings& getImageSequence() const;
            std::shared_ptr<feather_tk::IObservableValue<ImageSequenceSettings> > observeImageSequence() const;
            void setImageSequence(const ImageSequenceSettings&);

            ///@}

            //! \name Miscellaneous
            ///@{

            const MiscSettings& getMisc() const;
            std::shared_ptr<feather_tk::IObservableValue<MiscSettings> > observeMisc() const;
            void setMisc(const MiscSettings&);

            ///@}

            //! \name Mouse
            ///@{

            const MouseSettings& getMouse() const;
            std::shared_ptr<feather_tk::IObservableValue<MouseSettings> > observeMouse() const;
            void setMouse(const MouseSettings&);

            ///@}

            //! \name Keyboard Shortcuts
            ///@{

            const ShortcutsSettings& getShortcuts() const;
            std::shared_ptr<feather_tk::IObservableValue<ShortcutsSettings> > observeShortcuts() const;
            void setShortcuts(const ShortcutsSettings&);

            ///@}

            //! \name Style
            ///@{

            const StyleSettings& getStyle() const;
            std::shared_ptr<feather_tk::IObservableValue<StyleSettings> > observeStyle() const;
            void setStyle(const StyleSettings&);

            ///@}

            //! \name Timeline
            ///@{

            const TimelineSettings& getTimeline() const;
            std::shared_ptr<feather_tk::IObservableValue<TimelineSettings> > observeTimeline() const;
            void setTimeline(const TimelineSettings&);

            ///@}

            //! \name Window
            ///@{

            const WindowSettings& getWindow() const;
            std::shared_ptr<feather_tk::IObservableValue<WindowSettings> > observeWindow() const;
            void setWindow(const WindowSettings&);

            ///@}

#if defined(TLRENDER_FFMPEG)
            //! \name FFmpeg
            ///@{

            const tl::ffmpeg::Options& getFFmpeg() const;
            std::shared_ptr<feather_tk::IObservableValue<tl::ffmpeg::Options> > observeFFmpeg() const;
            void setFFmpeg(const tl::ffmpeg::Options&);

            ///@}
#endif // TLRENDER_FFMPEG

#if defined(TLRENDER_USD)
            //! \name USD
            ///@{

            const tl::usd::Options& getUSD() const;
            std::shared_ptr<feather_tk::IObservableValue<tl::usd::Options> > observeUSD() const;
            void setUSD(const tl::usd::Options&);

            ///@}
#endif // TLRENDER_USD

        private:
            FEATHER_TK_PRIVATE();
        };

        //! \name Serialize
        ///@{

        void to_json(nlohmann::json&, const AdvancedSettings&);
        void to_json(nlohmann::json&, const ExportSettings&);
        void to_json(nlohmann::json&, const FileBrowserSettings&);
        void to_json(nlohmann::json&, const ImageSequenceSettings&);
        void to_json(nlohmann::json&, const MiscSettings&);
        void to_json(nlohmann::json&, const MouseActionBinding&);
        void to_json(nlohmann::json&, const MouseSettings&);
        void to_json(nlohmann::json&, const ShortcutsSettings&);
        void to_json(nlohmann::json&, const StyleSettings&);
        void to_json(nlohmann::json&, const TimelineSettings&);
        void to_json(nlohmann::json&, const WindowSettings&);

        void from_json(const nlohmann::json&, AdvancedSettings&);
        void from_json(const nlohmann::json&, ExportSettings&);
        void from_json(const nlohmann::json&, FileBrowserSettings&);
        void from_json(const nlohmann::json&, ImageSequenceSettings&);
        void from_json(const nlohmann::json&, MiscSettings&);
        void from_json(const nlohmann::json&, MouseActionBinding&);
        void from_json(const nlohmann::json&, MouseSettings&);
        void from_json(const nlohmann::json&, ShortcutsSettings&);
        void from_json(const nlohmann::json&, StyleSettings&);
        void from_json(const nlohmann::json&, TimelineSettings&);
        void from_json(const nlohmann::json&, WindowSettings&);

        ///@}
    }
}
