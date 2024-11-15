/*
 * Copyright (c) 2012-2020 Maarten Baert <maarten-baert@hotmail.com>

 * This file is part of Lingmo-Screenshot.
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef X264PRESETS_H
#define X264PRESETS_H
#include "Global.h"
#include "my_av.h"

// This file was generated by 'x264-preset-translator.php', don't edit it.

#if !SSR_USE_AVCODEC_PRIVATE_PRESET

void X264Preset(AVCodecContext* cc, const char* preset);

void X264Preset_ultrafast(AVCodecContext* cc);
void X264Preset_superfast(AVCodecContext* cc);
void X264Preset_veryfast(AVCodecContext* cc);
void X264Preset_faster(AVCodecContext* cc);
void X264Preset_fast(AVCodecContext* cc);
void X264Preset_medium(AVCodecContext* cc);
void X264Preset_slow(AVCodecContext* cc);
void X264Preset_slower(AVCodecContext* cc);
void X264Preset_veryslow(AVCodecContext* cc);
void X264Preset_placebo(AVCodecContext* cc);

#endif


#endif // X264PRESETS_H
