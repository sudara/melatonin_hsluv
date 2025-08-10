/*
BEGIN_JUCE_MODULE_DECLARATION

 ID:               melatonin_hsluv
 vendor:           Sudara
 version:          1.0
 name:             Melatonin HSLuv Color Space implementation
 description:      A JUCE wrapper around the HSLuv color space C implementation
 license:          MIT
 dependencies:     juce_gui_basics

END_JUCE_MODULE_DECLARATION
*/

#pragma once
#include "hsluv/hsluv.h"
#include "juce_graphics/juce_graphics.h"

namespace melatonin
{
    struct HSLuv
    {
        // Hue. Between 0.0 and 360.0.
        // Saturation. Between 0.0 and 100.0.
        // Lightness. Between 0.0 and 100.0.
        double hue;
        double saturation;
        double lightness;

        [[nodiscard]] HSLuv withLightness (double amount) const
        {
            jassert (amount <= 100);
            return { hue, saturation, amount };
        }

        [[nodiscard]] HSLuv withSaturation (double amount) const
        {
            jassert (amount <= 100);
            return { hue, amount, lightness };
        }

        [[nodiscard]] juce::Colour toColour() const
        {
            double r, g, b;
            hsluv2rgb (hue, saturation, lightness, &r, &g, &b);
            return juce::Colour::fromRGB (static_cast<uint8_t> (std::floor (r * 255.999)),
                static_cast<uint8_t> (std::floor (g * 255.999)),
                static_cast<uint8_t> (std::floor (b * 255.999)));
        }

        static HSLuv fromColour (juce::Colour color)
        {
            HSLuv hsl {};
            rgb2hsluv (color.getRed() / 255.0, color.getGreen() / 255.0, color.getBlue() / 255.0, &hsl.hue, &hsl.saturation, &hsl.lightness);
            return hsl;
        }
    };

    [[nodiscard]] [[maybe_unused]] static juce::Colour withLightnessAndSaturation (const juce::Colour& color, const double lightness, const double saturation)
    {
        jassert (lightness <= 100);
        jassert (saturation <= 100);
        return HSLuv::fromColour (color).withLightness (lightness).withSaturation (saturation).toColour();
    }

    [[nodiscard]] [[maybe_unused]] static juce::Colour withLightness (const juce::Colour& color, const double amount)
    {
        jassert (amount <= 100);
        return HSLuv::fromColour (color).withLightness (amount).toColour();
    }

    [[nodiscard]] [[maybe_unused]] static juce::Colour withDeltaLightness (const juce::Colour& color, const double delta)
    {
        jassert (delta <= 100);
        auto hsluv = HSLuv::fromColour (color);
        return hsluv.withLightness (hsluv.lightness + delta).toColour();
    }

    [[nodiscard]] [[maybe_unused]] static juce::Colour withSaturation (const juce::Colour& color, const double amount)
    {
        jassert (amount <= 100);
        return HSLuv::fromColour (color).withSaturation (amount).toColour();
    }

}
