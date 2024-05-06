/*
 * Copyright (C) 2017 The Android Open Source Project
 * Copyright (C) 2024 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <aidl/android/hardware/light/BnLights.h>

#include <fstream>
#include <mutex>
#include <unordered_map>

namespace aidl {
namespace android {
namespace hardware {
namespace light {
namespace impl {
namespace nvidia {

struct Light : public BnLights {
public:
    Light();

    ndk::ScopedAStatus setLightState(int32_t in_id, const HwLightState& in_state)  override;
    ndk::ScopedAStatus getLights(std::vector<HwLight>* _aidl_return)  override;

private:
    void setBacklight(const HwLightState& state);
    void setButtonsLight(const HwLightState& state);

    std::ofstream mBacklight;
    std::fstream mPowerLed;
    std::ofstream mPowerLedState;
    std::ofstream mButtonLeds;
    std::ofstream mButtonLedsState;
    int8_t mLedBrightness;

    struct LightData {
        HwLight data;
        std::function<void(const HwLightState&)> callback;
    };

    std::unordered_map<int32_t, struct LightData> mLights;
    std::mutex mLock;
};
}  // namespace nvidia
}  // namespace impl
}  // namespace light
}  // namespace hardware
}  // namespace android
}  // namespace aidl
