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
        double hue;
        double saturation;
        double lightness;

        [[nodiscard]] HSLuv withLightness (double amount) const
        {
            jassert (amount <= 100);
            return { hue, saturation, lightness + amount };
        }
        static juce::Colour toColour();
    };

    // Hue. Between 0.0 and 360.0.
    // Saturation. Between 0.0 and 100.0.
    // Lightness. Between 0.0 and 100.0.
    static juce::Colour colourFromHSLuv (HSLuv hsl)
    {
        double r, g, b;
        hsluv2rgb (hsl.hue, hsl.saturation, hsl.lightness, &r, &g, &b);
        return juce::Colour::fromRGB (static_cast<uint8_t> (std::floor (r * 255.999)),
            static_cast<uint8_t> (std::floor (g * 255.999)),
            static_cast<uint8_t> (std::floor (b * 255.999)));
    }

    static HSLuv colourToHSLuv (const juce::Colour& color)
    {
        HSLuv hsl {};
        rgb2hsluv (color.getRed() / 255.0, color.getGreen() / 255.0, color.getBlue() / 255.0, &hsl.hue, &hsl.saturation, &hsl.lightness);
        return hsl;
    }

    juce::Colour HSLuv::toColour()
    {
        return colourFromHSLuv (*this);
    }

}
