/*
 * HSLuv-C: Human-friendly HSL
 * <https://github.com/hsluv/hsluv-c>
 * <https://www.hsluv.org/>
 *
 * Copyright (c) 2015 Alexei Boronine (original idea, JavaScript implementation)
 * Copyright (c) 2015 Roger Tallada (Obj-C implementation)
 * Copyright (c) 2017 Martin Mitáš (C implementation, based on Obj-C implementation)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef HSLUV_H
#define HSLUV_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Convert HSLuv to RGB.
 *
 * @param h Hue. Between 0.0 and 360.0.
 * @param s Saturation. Between 0.0 and 100.0.
 * @param l Lightness. Between 0.0 and 100.0.
 * @param[out] pr Red component. Between 0.0 and 1.0.
 * @param[out] pg Green component. Between 0.0 and 1.0.
 * @param[out] pb Blue component. Between 0.0 and 1.0.
 */
void hsluv2rgb (double h, double s, double l, double* pr, double* pg, double* pb);

/**
 * Convert RGB to HSLuv.
 *
 * @param r Red component. Between 0.0 and 1.0.
 * @param g Green component. Between 0.0 and 1.0.
 * @param b Blue component. Between 0.0 and 1.0.
 * @param[out] ph Hue. Between 0.0 and 360.0.
 * @param[out] ps Saturation. Between 0.0 and 100.0.
 * @param[out] pl Lightness. Between 0.0 and 100.0.
 */
void rgb2hsluv (double r, double g, double b, double* ph, double* ps, double* pl);

/**
 * Convert HPLuv to RGB.
 *
 * @param h Hue. Between 0.0 and 360.0.
 * @param s Saturation. Between 0.0 and 100.0.
 * @param l Lightness. Between 0.0 and 100.0.
 * @param[out] pr Red component. Between 0.0 and 1.0.
 * @param[out] pg Green component. Between 0.0 and 1.0.
 * @param[out] pb Blue component. Between 0.0 and 1.0.
 */
void hpluv2rgb (double h, double s, double l, double* pr, double* pg, double* pb);

/**
 * Convert RGB to HPLuv.
 *
 * Note that HPLuv color space does not cover all the colors of RGB color
 * space. More specifically, some valid RGB triplets may correspond to colors
 * whose saturation is not representable in the HPLuv color space and falls
 * outside the valid range between 0.0 and 100.0.
 *
 * Application can still get closest color correctly representable in the HPLuv
 * color space by clamping the saturation into the valid range:
 *
 * @code C
 * ...
 * if(rgb2hpluv(r, g, b, &h, &s, &v) != 0) {
 *     if(s < 0.0)
 *         s = 0.0;
 *     if(s > 100.0)
 *         s = 100.0;
 * }
 * ...
 * @endcode
 *
 * @param r Red component. Between 0.0 and 1.0.
 * @param g Green component. Between 0.0 and 1.0.
 * @param b Blue component. Between 0.0 and 1.0.
 * @param[out] ph Hue. Between 0.0 and 360.0.
 * @param[out] ps Saturation. Between 0.0 and 100.0 if the input is
 * representable in HPLuv color space; and outside the range if it's not.
 * @param[out] pl Lightness. Between 0.0 and 100.0.
 *
 * @return Returns 0 if the RGB triplet is representable in the HPLuv color
 * space, -1 otherwise.
 */
int rgb2hpluv (double r, double g, double b, double* ph, double* ps, double* pl);

#ifdef __cplusplus
}
#endif

#endif /* HSLUV_H */
