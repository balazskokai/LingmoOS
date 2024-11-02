/*
 * Copyright 2024 KylinSoft Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef VISIONSESSION_H
#define VISIONSESSION_H

#include "vision.h"
#include "services/visionprocessorproxy.h"
#include <jsoncpp/json/value.h>
#include <string>
#include <any>
#include <vector>

namespace vision {
    
class VisionSession {
public:
    VisionSession();
    VisionResult init(const std::string &engineName, const Json::Value &config);

    void setPromptImageCallback(ImageResultCallback callback, std::any userData);

    void setPromptImageSize(int width, int height);

    void setPromptImageNumber(int number);

    void setPromptImageStyle(VisionImageStyle style);

    std::string getPrompt2imageSupportedParams() const;

    VisionResult promptImage(const char* prompt);

private:
    VisionProcessorProxy visionProcessorProxy_;
};

}


#endif // SPEECHSESSION_H