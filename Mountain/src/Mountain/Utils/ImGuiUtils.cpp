#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Utils/ImGuiUtils.hpp"

#include <mimalloc.h>

#include <ImGui/imgui_stdlib.h>

#include <magic_enum/magic_enum.hpp>

#include "Mountain/Screen.hpp"
#include "Mountain/FileSystem/FileManager.hpp"
#include "Mountain/Input/Input.hpp"
#include "Mountain/Input/Time.hpp"
#include "Mountain/Resource/AudioTrack.hpp"
#include "Mountain/Resource/Font.hpp"
#include "Mountain/Resource/ResourceManager.hpp"
#include "Mountain/Utils/FileSystemWatcher.hpp"

using namespace Mountain;

namespace
{
    void EasingTooltip(const Easing::Easer function)
    {
        if (!ImGui::BeginItemTooltip())
            return;

        ImGuiUtils::DrawEasingFunction("##", function);

        ImGui::EndTooltip();
    };
}

void ImGuiUtils::GridPlotting(const std::string_view label, Vector2* const value, const float_t min, const float_t max)
{
    ImGui::PushID(value);

    ImGui::Text("%.*s", static_cast<int32_t>(label.length()), label.data());
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    constexpr Vector2 size(100.f, 100.f);
    ImGui::InvisibleButton("##canvas", size);

    const Vector2 p0 = ImGui::GetItemRectMin();
    const Vector2 p1 = ImGui::GetItemRectMax();

    const Vector2 plottingRange(min, max);
    constexpr Vector2 uniformRange(0.f, 1.f);

    // Handle clicking
    if (ImGui::IsItemActive() && ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
        const ImGuiIO& io = ImGui::GetIO();

        // Compute new value, ranged between 0 and 1
        const Vector2 newValue = (io.MousePos - p0) / size;

        // Remap the value from [0; 1] to [min; max]
        value->x = Utils::RemapValue(newValue.x, uniformRange, plottingRange);
        value->y = Utils::RemapValue(newValue.y, uniformRange, plottingRange);

        // Clamp the value between min and max
        value->x = std::clamp(value->x, min, max);
        value->y = std::clamp(value->y, min, max);
    }

    // Create rectangle
    ImGui::PushClipRect(p0, p1, true);
    drawList->AddRectFilled(p0, p1, Color::SlateGray().GetPackedValue());

    // Remap from [min; max] to [0, 1]
    const Vector2 clamped(
        Utils::RemapValue(value->x, plottingRange, uniformRange),
        Utils::RemapValue(value->y, plottingRange, uniformRange)
    );

    // Compute cursor position
    Vector2 position = p0 + clamped * size;
    position.y *= -1; // In 2D, the Y axis goes downwards

    drawList->AddCircle(position, 5, Color::Red().GetPackedValue());
    ImGui::PopClipRect();

    // Draw slider float version
    ImGui::SameLine();
    ImGui::VSliderFloat("##v2y", { 18.f, 100.f }, &value->y, min, max, "%.3f", ImGuiSliderFlags_AlwaysClamp);
    ImGui::SliderFloat("##v2x", &value->x, min, max, "%.3f", ImGuiSliderFlags_AlwaysClamp);

    ImGui::PopID();
}

void ImGuiUtils::DirectionVector(const std::string_view label, Vector2* const value)
{
    ImGui::PushID(value);

    ImGui::Text("%.*s", static_cast<int32_t>(label.length()), label.data());
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    constexpr Vector2 size(100.f, 100.f);
    ImGui::InvisibleButton("##canvas", size);

    const Vector2 p0 = ImGui::GetItemRectMin();
    const Vector2 p1 = ImGui::GetItemRectMax();

    constexpr Vector2 plottingRange(-1.f, 1.f);
    constexpr Vector2 uniformRange(0.f, 1.f);

    // Handle clicking
    if (ImGui::IsItemActive() && ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
        const ImGuiIO& io = ImGui::GetIO();

        // Compute new value, ranged between 0 and 1
        const Vector2 newValue = (io.MousePos - p0) / size;

        // Remap the value from [0; 1] to [min; max]
        value->x = Utils::RemapValue(newValue.x, uniformRange, plottingRange);
        value->y = Utils::RemapValue(newValue.y, uniformRange, plottingRange);

        // Clamp the value between min and max
        value->x = std::clamp(value->x, -1.f, 1.f);
        value->y = std::clamp(value->y, -1.f, 1.f);

        *value = value->Normalized();
    }

    // Create rectangle
    ImGui::PushClipRect(p0, p1, true);
    drawList->AddCircleFilled(p0 + size * 0.5f, size.x * 0.5f, Color::SlateGray().GetPackedValue());

    // Remap from [min; max] to [0, 1]
    const Vector2 clamped(
        Utils::RemapValue(value->x, plottingRange, uniformRange),
        Utils::RemapValue(value->y, plottingRange, uniformRange)
    );

    // Compute cursor position
    const Vector2 position = p0 + clamped * size;

    drawList->AddLine(p0 + size * 0.5f, position, Color::Red().GetPackedValue());
    const Vector2 normal = value->Normal();
    const Vector2 offset = -*value * size.y * 0.1f;
    drawList->AddTriangleFilled(position + normal * size.x * 0.1f + offset, position - normal * size.x * 0.1f + offset, position, Color::Red().GetPackedValue());
    ImGui::PopClipRect();

    ImGui::PopID();
}

void ImGuiUtils::DirectionVector(const std::string_view label, Vector2* const value, const Vector2 expected)
{
    ImGui::PushID(value);

    ImGui::Text("%.*s", static_cast<int32_t>(label.length()), label.data());
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    constexpr Vector2 size = Vector2::One() * 100.f;
    ImGui::InvisibleButton("##canvas", size);

    const Vector2 p0 = ImGui::GetItemRectMin();
    const Vector2 p1 = ImGui::GetItemRectMax();

    constexpr Vector2 plottingRange(-1.f, 1.f);
    constexpr Vector2 uniformRange(0.f, 1.f);

    // Handle clicking
    if (ImGui::IsItemActive() && ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
        const ImGuiIO& io = ImGui::GetIO();

        // Compute new value, ranged between 0 and 1
        const Vector2 newValue = (io.MousePos - p0) / size;

        // Remap the value from [0; 1] to [min; max]
        value->x = Utils::RemapValue(newValue.x, uniformRange, plottingRange);
        value->y = Utils::RemapValue(newValue.y, uniformRange, plottingRange);

        // Clamp the value between min and max
        value->x = std::clamp(value->x, -1.f, 1.f);
        value->y = std::clamp(value->y, -1.f, 1.f);

        *value = value->Normalized();
    }

    // Create rectangle
    ImGui::PushClipRect(p0, p1, true);
    drawList->AddCircleFilled(p0 + size * 0.5f, size.x * 0.5f, Color::SlateGray().GetPackedValue());

    // Remap from [min; max] to [0, 1]
    const Vector2 valueClamped(
        Utils::RemapValue(value->x, plottingRange, uniformRange),
        Utils::RemapValue(value->y, plottingRange, uniformRange)
    );
    const Vector2 expectedClamped(
        Utils::RemapValue(expected.x, plottingRange, uniformRange),
        Utils::RemapValue(expected.y, plottingRange, uniformRange)
    );

    // Compute cursor position
    const Vector2 valuePosition = p0 + valueClamped * size;
    const Vector2 expectedPosition = p0 + expectedClamped * size;

    drawList->AddLine(p0 + size * 0.5f, expectedPosition, (Color::Red() * 0.5f).GetPackedValue());
    const Vector2 expectedNormal = expected.Normal();
    const Vector2 expectedOffset = -expected * size.y * 0.1f;
    drawList->AddTriangleFilled(
        expectedPosition + expectedNormal * size.x * 0.1f + expectedOffset,
        expectedPosition - expectedNormal * size.x * 0.1f + expectedOffset,
        expectedPosition,
        (Color::Red() * 0.5f).GetPackedValue()
    );

    drawList->AddLine(p0 + size * 0.5f, valuePosition, Color::Red().GetPackedValue());
    const Vector2 valueNormal = value->Normal();
    const Vector2 valueOffset = -*value * size.y * 0.1f;
    drawList->AddTriangleFilled(
        valuePosition + valueNormal * size.x * 0.1f + valueOffset,
        valuePosition - valueNormal * size.x * 0.1f + valueOffset,
        valuePosition,
        Color::Red().GetPackedValue()
    );
    ImGui::PopClipRect();

    ImGui::PopID();
}

bool ImGuiUtils::ComboEaser(const std::string& label, Easing::Easer* v, const ImGuiComboFlags flags)
{
    static constexpr Array Functions{
        std::make_pair("Linear", Easing::Linear),
        std::make_pair("Sine In", Easing::SineIn),
        std::make_pair("Sine Out", Easing::SineOut),
        std::make_pair("Sine In/Out", Easing::SineInOut),
        std::make_pair("Quad In", Easing::QuadIn),
        std::make_pair("Quad Out", Easing::QuadOut),
        std::make_pair("Quad In/Out", Easing::QuadInOut),
        std::make_pair("Cubic In", Easing::CubicIn),
        std::make_pair("Cubic Out", Easing::CubicOut),
        std::make_pair("Cubic In/Out", Easing::CubicInOut),
        std::make_pair("Quart In", Easing::QuartIn),
        std::make_pair("Quart Out", Easing::QuartOut),
        std::make_pair("Quart In/Out", Easing::QuartInOut),
        std::make_pair("Quint In", Easing::QuintIn),
        std::make_pair("Quint Out", Easing::QuintOut),
        std::make_pair("Quint In/Out", Easing::QuintInOut),
        std::make_pair("Expo In", Easing::ExpoIn),
        std::make_pair("Expo Out", Easing::ExpoOut),
        std::make_pair("Expo In/Out", Easing::ExpoInOut),
        std::make_pair("Circ In", Easing::CircIn),
        std::make_pair("Circ Out", Easing::CircOut),
        std::make_pair("Circ In/Out", Easing::CircInOut),
        std::make_pair("Back In", Easing::BackIn),
        std::make_pair("Back Out", Easing::BackOut),
        std::make_pair("Back In/Out", Easing::BackInOut),
        std::make_pair("Elastic In", Easing::ElasticIn),
        std::make_pair("Elastic Out", Easing::ElasticOut),
        std::make_pair("Elastic In/Out", Easing::ElasticInOut),
        std::make_pair("Bounce In", Easing::BounceIn),
        std::make_pair("Bounce Out", Easing::BounceOut),
        std::make_pair("Bounce In/Out", Easing::BounceInOut),
    };

    const auto current = std::ranges::find_if(Functions, [&](auto element) { return element.second == *v; });
    const char_t* const value = current == Functions.end() ? "Linear" : current->first;

    bool_t result = false;
    if (ImGui::BeginCombo(label.data(), value, flags))
    {
        for (const auto& pair : Functions)
        {
            if (ImGui::Selectable(pair.first))
            {
                *v = pair.second;
                result = true;
            }

            EasingTooltip(pair.second);
        }
        ImGui::EndCombo();
    }

    EasingTooltip(*v);

    return result;
}

void ImGuiUtils::ShowInputsWindow()
{
    ImGui::Begin("Mountain Inputs");
    if (ImGui::TreeNode("Mouse"))
    {
        const Vector2i mousePos = static_cast<Vector2i>(Input::GetMousePosition());
        ImGui::Text("Position: %d, %d", mousePos.x, mousePos.y);
        ImGui::Text("Button down right: %d", Input::GetMouseButton(MouseButton::Right));
        ImGui::Text("Button release right: %d", Input::GetMouseButton(MouseButton::Right, MouseButtonStatus::Release));
        for (uint32_t i = 0; i < magic_enum::enum_count<MouseButton>(); i++)
        {
            ImGui::Text("Button down %u: %d", i + 1, Input::GetMouseButton(static_cast<MouseButton>(i)));
            ImGui::Text("Button release %u: %d", i + 1, Input::GetMouseButton(static_cast<MouseButton>(i), MouseButtonStatus::Release));
        }
        ImGui::Text("Wheel: %f, %f", Input::GetMouseWheel().x, Input::GetMouseWheel().y);
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Keyboard"))
    {
        ImGui::Text("Key down B: %d", Input::GetKey(Key::B));
        ImGui::Text("Key release B: %d", Input::GetKey(Key::B, KeyStatus::Release));
        ImGui::TreePop();
    }

    ImGui::Text("Gamepads connected: %u", Input::GetGamepadsConnected());
    for (uint32_t i = 0; i < Input::GamepadMax; i++)
    {
        const GamepadInput& gamepad = Input::GetGamepad(i);

        if (!gamepad.GetConnected())
            continue;

        ImGui::PushID(&i + i);

        if (ImGui::TreeNode(std::format("Gamepad {} - {}", i, gamepad.GetName()).c_str()))
        {
            ImGui::Text("Left stick axis: %f, %f", gamepad.GetAxis(GamepadAxis::LeftStickHorizontal), gamepad.GetAxis(GamepadAxis::LeftStickVertical));
            Vector2 leftStick = gamepad.GetStick(GamepadStick::Left);
            DirectionVector("Left stick", &leftStick);
            ImGui::Text("Right stick axis: %f, %f", gamepad.GetAxis(GamepadAxis::RightStickHorizontal), gamepad.GetAxis(GamepadAxis::RightStickVertical));
            Vector2 rightStick = gamepad.GetStick(GamepadStick::Right);
            DirectionVector("Right stick", &rightStick);

            ImGui::BeginDisabled();
            ImGui::Text("Left trigger axis: %f", gamepad.GetAxis(GamepadAxis::LeftTrigger));
            ImGui::Text("Right trigger axis: %f", gamepad.GetAxis(GamepadAxis::RightTrigger));
            ImGui::EndDisabled();

            for (uint32_t j = 0; j < magic_enum::enum_count<GamepadButton>(); j++)
            {
                const GamepadButton button = static_cast<GamepadButton>(j);
                const std::string_view name = magic_enum::enum_name(button);
                ImGui::Text("Button %u - %.*s: %d", j, static_cast<int32_t>(name.length()), name.data(), gamepad.GetButton(button));
            }

            ImGui::BeginDisabled();
            Vector2 dpad = static_cast<Vector2>(gamepad.GetDirectionalPad()).Normalized();
            DirectionVector("Directional pad", &dpad);
            ImGui::EndDisabled();

            if (gamepad.HasCapability(GamepadCapabilities::Gyroscope))
            {
                const Vector3& gyro = gamepad.GetGyroscope();
                ImGui::Text("Gyroscope: %f, %f, %f", gyro.x, gyro.y, gyro.z);
            }

            if (gamepad.HasCapability(GamepadCapabilities::Accelerometer))
            {
                const Vector3& accel = gamepad.GetAccelerometer();
                ImGui::Text("Accelerometer: %f, %f, %f", accel.x, accel.y, accel.z);
            }

            if (gamepad.HasCapability(GamepadCapabilities::Touchpad))
            {
                for (size_t j = 0; j < gamepad.GetTouchpadAmount(); j++)
                {
                    const GamepadInput::TouchpadInfo& touchpad = gamepad.GetTouchpad(j);

                    ImGui::Text("Touchpad %ud: ", i);
                    ImGui::Text("\tMax fingers: %d", touchpad.nbrOfFingersMax);
                    for (size_t k = 0; k < touchpad.fingerLocations.GetSize(); k++)
                    {
                        const Vector2& finger = touchpad.fingerLocations[k];
                        ImGui::Text("\tFinger %zu: %f, %f", k, finger.x, finger.y);
                    }
                }
            }

            ImGui::Text("Battery level: %d%%", gamepad.GetBattery());
            const std::string_view batteryState = magic_enum::enum_name(gamepad.GetBatteryState());
            ImGui::Text("Battery status: %*s", static_cast<int32_t>(batteryState.length()), batteryState.data());

            if (gamepad.HasCapability(GamepadCapabilities::Rumble))
            {
                if (ImGui::Button("Test weak rumble"))
                    gamepad.Rumble(1.f, 0.f, 1.f);

                if (ImGui::Button("Test strong rumble"))
                    gamepad.Rumble(0.f, 1.f, 1.f);
            }

            if (gamepad.HasCapability(GamepadCapabilities::Led))
            {
                Color color = gamepad.GetLight();

                if (ImGui::ColorEdit3("Light", &color.r))
                    gamepad.SetLight(color);
            }

            ImGui::TreePop();
        }

        ImGui::PopID();
    }
    ImGui::End();
}

void ImGuiUtils::ShowFileManager()
{
    ImGui::Begin("File Manager");

    static std::string filter;
    ImGui::InputText("Filter", &filter);

    ImGui::Separator();

    for (Pointer file : FileManager::FindAll<File>([&] (Pointer<File> f) -> bool_t { return f->GetPathString().contains(filter); }))
    {
        if (!ImGui::TreeNode(file->GetPathString().c_str()))
            continue;

        const std::string_view format = magic_enum::enum_name(file->GetType());
        ImGui::Text("Format: %.*s", static_cast<int32_t>(format.length()), format.data());
        ImGui::BeginDisabled();
        if (file->GetSize() < 1000)
        {
            ImGui::Text("Size: %lld B", file->GetSize());
        }
        else
        {
            const auto byteSize = Utils::ByteSizeUnit(file->GetSize());
            ImGui::Text("Size: %.2f %.*s", byteSize.first, static_cast<int32_t>(byteSize.second.length()), byteSize.second.data());
        }
        ImGui::EndDisabled();

        if (file->Exists())
        {
            if (ImGui::Button("Reload from disk"))
                file->Reload();
            if (ImGui::Button("Open with default editor"))
                file->OpenFile();
            if (ImGui::Button("Open in file explorer"))
                file->OpenInExplorer();
        }

        ImGui::TreePop();
    }

    ImGui::End();
}

namespace
{
    void DisplayReloadOptions(Resource& resource, File& file)
    {
        if (ImGui::Button("Reload from cached file"))
            resource.Reload();
        if (file.Exists() && ImGui::Button("Reload from disk"))
        {
            file.Reload();
            resource.Reload();
        }
    }

    template <Concepts::Resource T>
    void DisplayResourceType(
        const std::string_view typeName,
        const std::string_view resourceNameFilter,
        const std::function<void(Pointer<T> resource)>& additionalAction = std::identity{}
    )
    {
        const List<Pointer<T>> resources = ResourceManager::FindAll<T>([&] (Pointer<T> r) -> bool_t { return Utils::StringContainsIgnoreCase(r->GetName(), resourceNameFilter); });
        const List<Pointer<T>> packagedResources = FindAll(resources, [] (const Pointer<T>& r) -> bool_t { return ResourceManager::IsBinary(r->GetName()); });
        if (ImGui::TreeNode(std::format("{} ({}, {} packaged in binary)", typeName, resources.GetSize(), packagedResources.GetSize()).c_str()))
        {
            for (Pointer resource : resources)
            {
                if (!ImGui::TreeNode(resource->GetName().c_str()))
                    continue;

                Pointer file = resource->GetFile();
                if (file != nullptr)
                    DisplayReloadOptions(*resource, *file);

                additionalAction(resource);

                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
    }

    template <>
    void DisplayResourceType(
        const std::string_view typeName,
        const std::string_view resourceNameFilter,
        const std::function<void(Pointer<Shader> resource)>& additionalAction
    )
    {
        const List<Pointer<Shader>> shaders = ResourceManager::FindAll<Shader>([&] (Pointer<Shader> r) -> bool_t { return Utils::StringContainsIgnoreCase(r->GetName(), resourceNameFilter); });
        const List<Pointer<Shader>> packagedShaders = FindAll(shaders,
            [](const Pointer<Shader>& r) -> bool_t
            {
                return ResourceManager::IsBinary(First(r->GetFiles())->GetPathString());
            }
        );

        if (ImGui::TreeNode(std::format("{} ({}, {} packaged in binary)", typeName, shaders.GetSize(), packagedShaders.GetSize()).c_str()))
        {
            for (Pointer shader : shaders)
            {
                if (!ImGui::TreeNode(shader->GetName().c_str()))
                    continue;

                for (size_t i = 0; i < shader->GetFiles().GetSize(); i++)
                {
                    Pointer<File>& shaderFile = shader->GetFiles()[i];

                    if (shaderFile == nullptr)
                        continue;

                    if (!ImGui::TreeNode(std::string{magic_enum::enum_name(static_cast<Graphics::ShaderType>(i))}.c_str()))
                        continue;

                    DisplayReloadOptions(*shader, *shaderFile);

                    ImGui::TreePop();
                }

                additionalAction(shader);

                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
    }
}

void ImGuiUtils::ShowResourceManager()
{
    ImGui::Begin("Resource Manager");

    static std::string filter;
    ImGui::InputText("Filter", &filter);

    ImGui::Separator();

    DisplayResourceType<AudioTrack>(
        "AudioTrack",
        filter,
        [](const Pointer<AudioTrack>& audioTrack)
        {
            const std::string_view format = magic_enum::enum_name(audioTrack->GetFormat());
            ImGui::Text("Format: %.*s", static_cast<int32_t>(format.length()), format.data());
        }
    );

    DisplayResourceType<Font>("Font", filter);

    DisplayResourceType<Shader>("Shader", filter);

    DisplayResourceType<ComputeShader>("ComputeShader", filter);

    DisplayResourceType<Texture>(
        "Texture",
        filter,
        [](const Pointer<Texture>& texture)
        {
            const Vector2i size = texture->GetSize();
            ImGui::Text("Size: %dx%d", size.x, size.y);
            ImGui::Text("Preview:");
            ImGui::Image(Utils::IntToPointer<void>(texture->GetId()), static_cast<Vector2>(texture->GetSize()));
        }
    );

    ImGui::End();
}

bool_t ImGuiUtils::PushSeparatorText(const char_t* label)
{
    ImGui::SeparatorText(label);
    ImGui::PushID(label);
    return true;
}

void ImGuiUtils::PopSeparatorText()
{
    ImGui::PopID();
}

bool_t ImGuiUtils::PushCollapsingHeader(const char_t* label, const ImGuiTreeNodeFlags flags)
{
    if (ImGui::CollapsingHeader(label, flags))
    {
        ImGui::PushID(label);
        return true;
    }
    return false;
}

void ImGuiUtils::PopCollapsingHeader()
{
    ImGui::PopID();
}

void ImGuiUtils::SetNextItemWidthAvail()
{
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
}

void ImGuiUtils::ShowPerformanceMonitoring()
{
    ImGui::Begin("Performance Monitoring");

    static float_t updateInterval = 0.25f;

    ImGui::SeparatorText("Settings");

    ImGui::DragFloat("Update interval", &updateInterval, 0.01f, 0.f, 1.f);

    auto targetFps = Time::targetFps;
    const double_t refreshRate = Screen::GetRefreshRate();
    constexpr double_t zero = 0;
    if (Optional(
        &targetFps,
        refreshRate,
        refreshRate,
        [&](double_t& value) -> bool_t
        {
            return ImGui::DragScalar("Target FPS", ImGuiDataType_Double, &value, 1.f, &zero, nullptr, "%.0f");
        }
    ))
    {
        Time::targetFps = targetFps;
    }
    bool_t vsync = Window::GetVSync();
    ImGui::Checkbox("Vertical Synchronization", &vsync);
    Window::SetVSync(vsync);

    ImGui::SeparatorText("Statistics");

    static float_t fps = 0.f;
    static double_t memoryCpuOnly = 0.f;
    static double_t memoryTotal = 0.f;
    static float_t deltaTime = 0.f;
    static float_t frameDuration = 0.f;
    static float_t frameDurationLeft = 0.f;
    static Vector2i framebufferSize;

    static float_t lastUpdateTime = 0.f;
    static uint64_t lastUpdateTotalFrames = 0;

    if (Time::OnIntervalUnscaled(updateInterval))
    {
        const float_t updateTime = Time::GetTotalTimeUnscaled();
        const uint64_t totalFrames = Time::GetTotalFrameCount();

        deltaTime = Time::GetDeltaTimeUnscaled();
        fps = Calc::Round(static_cast<float_t>(totalFrames - lastUpdateTotalFrames) / (updateTime - lastUpdateTime));
        frameDuration = Time::GetLastFrameDuration();
        frameDurationLeft = Time::GetTargetDeltaTime() == 0.f ? 0.f : (Time::GetTargetDeltaTime() - frameDuration);
        framebufferSize = Window::GetSize();

        size_t cpuMemory, totalMemory;
        mi_process_info(nullptr, nullptr, nullptr, &cpuMemory, nullptr, &totalMemory, nullptr, nullptr);

        memoryCpuOnly = static_cast<double_t>(cpuMemory) * 1e-6; // Convert to MB
        memoryTotal = static_cast<double_t>(totalMemory) * 1e-6; // Convert to MB

        lastUpdateTime = updateTime;
        lastUpdateTotalFrames = totalFrames;
    }

    ImGui::Text("Frame #%llu", lastUpdateTotalFrames);
    Color fpsColor = Color::LightGreen();
    if (fps < 60.f)
        fpsColor = Color::Orange();
    if (fps < 20.f)
        fpsColor = Color::Red();
    ImGui::TextColored(static_cast<ImVec4>(fpsColor), "%.0f FPS (%.1fms)", fps, deltaTime * 1000.f);
    ImGui::Text("CPU: %.1fms (%.1fms left)", frameDuration * 1000.f, frameDurationLeft * 1000.f);
    ImGui::Text("Memory: %.2fMB (%.2fMB including GPU)", memoryCpuOnly, memoryTotal);
    ImGui::Text("Framebuffer: %dx%d", framebufferSize.x, framebufferSize.y);

    ImGui::End();
}

void ImGuiUtils::DrawEasingFunction(const char_t* label, const Easing::Easer function, const int32_t pointCount)
{
    float_t* data = static_cast<float_t*>(_malloca(pointCount * sizeof(float_t)));

    float_t min = std::numeric_limits<float_t>::max();
    float_t max = std::numeric_limits<float_t>::min();

    for (int32_t i = 0; i < pointCount; i++)
    {
        const float_t value = function(static_cast<float_t>(i) / static_cast<float_t>(pointCount));
        data[i] = value;

        if (value < min)
            min = value;
        else if (value > max)
            max = value;
    }

    ImGui::PlotLines(label, data, pointCount, 0, nullptr, min, max, {100, 100});

    _freea(data);
}

// ReSharper disable CppInconsistentNaming
bool ImGui::DragAngle(
    const char* label,
    float* v_rad,
    const float v_speed,
    const float v_degrees_min,
    const float v_degrees_max,
    const char* format,
    const ImGuiSliderFlags flags
)
{
    float_t degreeAngle = *v_rad * Calc::Rad2Deg;
    const bool_t result = DragFloat(label, &degreeAngle, v_speed, v_degrees_min, v_degrees_max, format, flags);
    *v_rad = degreeAngle * Calc::Deg2Rad;
    return result;
}

template <>
bool ImGui::ComboEnum<Easing::Type>(const char* label, Easing::Type* v, const ImGuiComboFlags flags)
{
    bool_t result = false;
    if (BeginCombo(label, STRING_VIEW_TO_C_STR(magic_enum::enum_name(*v)), flags))
    {
        for (const Easing::Type value : magic_enum::enum_values<Easing::Type>())
        {
            if (Selectable(STRING_VIEW_TO_C_STR(magic_enum::enum_name(value))))
            {
                *v = value;
                result = true;
            }

            EasingTooltip(Easing::FromType(value));
        }
        EndCombo();
    }

    EasingTooltip(Easing::FromType(*v));

    return result;
}

// ReSharper restore CppInconsistentNaming
