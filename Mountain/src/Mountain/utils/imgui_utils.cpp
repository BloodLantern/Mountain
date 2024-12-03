#include "Mountain/utils/imgui_utils.hpp"

#include <magic_enum/magic_enum.hpp>

#include <ImGui/imgui_stdlib.h>

#include "Mountain/file/file_manager.hpp"
#include "Mountain/input/input.hpp"
#include "Mountain/resource/audio_track.hpp"
#include "Mountain/resource/resource_manager.hpp"

using namespace Mountain;

void ImGuiUtils::GridPlotting(const std::string_view label, Vector2* const value, const float_t min, const float_t max)
{
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
}

void ImGuiUtils::DirectionVector(const std::string_view label, Vector2* const value)
{
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
    drawList->AddRectFilled(p0, p1, Color::SlateGray().GetPackedValue());
        
    drawList->AddCircle(p0 + size * 0.5f, (size.x + size.y) * 0.5f, Color::Red().GetPackedValue());

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
}

void ImGuiUtils::DirectionVector(const std::string_view label, Vector2* const value, const Vector2 expected)
{
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
    drawList->AddRectFilled(p0, p1, Color::SlateGray().GetPackedValue());
        
    drawList->AddCircle(p0 + size * 0.5f, (size.x + size.y) * 0.5f, Color::Red().GetPackedValue());

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
    drawList->AddTriangleFilled(expectedPosition + expectedNormal * size.x * 0.1f + expectedOffset, expectedPosition - expectedNormal * size.x * 0.1f + expectedOffset, expectedPosition, (Color::Red() * 0.5f).GetPackedValue());

    drawList->AddLine(p0 + size * 0.5f, valuePosition, Color::Red().GetPackedValue());
    const Vector2 valueNormal = value->Normal();
    const Vector2 valueOffset = -*value * size.y * 0.1f;
    drawList->AddTriangleFilled(valuePosition + valueNormal * size.x * 0.1f + valueOffset, valuePosition - valueNormal * size.x * 0.1f + valueOffset, valuePosition, Color::Red().GetPackedValue());
    ImGui::PopClipRect();
}

bool ImGuiUtils::ComboEaser(const std::string_view label, Easing::Easer* v, const ImGuiComboFlags flags)
{
    static constexpr std::array Functions{
        std::make_pair("Linear", Utils::Identity<float_t>),
        std::make_pair("SineIn", Easing::SineIn),
        std::make_pair("SineOut", Easing::SineOut),
        std::make_pair("SineInOut", Easing::SineInOut),
        std::make_pair("QuadIn", Easing::QuadIn),
        std::make_pair("QuadOut", Easing::QuadOut),
        std::make_pair("QuadInOut", Easing::QuadInOut),
        std::make_pair("CubicIn", Easing::CubicIn),
        std::make_pair("CubicOut", Easing::CubicOut),
        std::make_pair("CubicInOut", Easing::CubicInOut),
        std::make_pair("QuartIn", Easing::QuartIn),
        std::make_pair("QuartOut", Easing::QuartOut),
        std::make_pair("QuartInOut", Easing::QuartInOut),
        std::make_pair("QuintIn", Easing::QuintIn),
        std::make_pair("QuintOut", Easing::QuintOut),
        std::make_pair("QuintInOut", Easing::QuintInOut),
        std::make_pair("ExpoIn", Easing::ExpoIn),
        std::make_pair("ExpoOut", Easing::ExpoOut),
        std::make_pair("ExpoInOut", Easing::ExpoInOut),
        std::make_pair("CircIn", Easing::CircIn),
        std::make_pair("CircOut", Easing::CircOut),
        std::make_pair("CircInOut", Easing::CircInOut),
        std::make_pair("BackIn", Easing::BackIn),
        std::make_pair("BackOut", Easing::BackOut),
        std::make_pair("BackInOut", Easing::BackInOut),
        std::make_pair("ElasticIn", Easing::ElasticIn),
        std::make_pair("ElasticOut", Easing::ElasticOut),
        std::make_pair("ElasticInOut", Easing::ElasticInOut),
        std::make_pair("BounceIn", Easing::BounceIn),
        std::make_pair("BounceOut", Easing::BounceOut),
        std::make_pair("BounceInOut", Easing::BounceInOut),
    };

    const auto current = std::ranges::find_if(Functions, [&](auto element) { return element.second == *v; });
    const auto value = current == Functions.end() ? "Linear" : current->first;

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
        }
        ImGui::EndCombo();
    }
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
        for (uint32_t i = 0; i < MouseButtonCount; i++)
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
        
        if (ImGui::TreeNode(std::format("Gamepad {} - {}", i, gamepad.GetName()).c_str()))
        {
            ImGui::Text("Left stick axis: %f, %f", gamepad.GetAxis(GamepadAxis::LeftStickHorizontal), gamepad.GetAxis(GamepadAxis::LeftStickVertical));
            Vector2 leftStick = gamepad.GetStick(GamepadStick::Left);
            ImGuiUtils::DirectionVector("Left stick", &leftStick);
            ImGui::Text("Right stick axis: %f, %f", gamepad.GetAxis(GamepadAxis::RightStickHorizontal), gamepad.GetAxis(GamepadAxis::RightStickVertical));
            Vector2 rightStick = gamepad.GetStick(GamepadStick::Right);
            ImGuiUtils::DirectionVector("Left stick", &rightStick);
            
            ImGui::Text("Left trigger axis: %f", gamepad.GetAxis(GamepadAxis::LeftTrigger));
            ImGui::Text("Right trigger axis: %f", gamepad.GetAxis(GamepadAxis::RightTrigger));

            for (uint32_t j = 0; j < GamepadButtonCount; j++)
            {
                const GamepadButton button = static_cast<GamepadButton>(j);
                const std::string_view name = magic_enum::enum_name(button);
                ImGui::Text("Button %u - %.*s: %d", j, static_cast<int32_t>(name.length()), name.data(), gamepad.GetButton(button));
            }

            Vector2 dpad = static_cast<Vector2>(gamepad.GetDirectionalPad());
            DirectionVector("Directional pad", &dpad);
            
            ImGui::TreePop();
        }
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
        const auto byteSize = Utils::ByteSizeUnit(file->GetSize());
        ImGui::Text("Size: %d %.*s", byteSize.first, static_cast<int32_t>(byteSize.second.length()), byteSize.second.data());
        ImGui::EndDisabled();

        if (ImGui::Button("Reload from disk"))
            file->Reload();
        if (ImGui::Button("Open with default editor"))
            file->OpenFile();
        if (ImGui::Button("Open in file explorer"))
            file->OpenInExplorer();

        ImGui::TreePop();
    }

    ImGui::End();
}

template <Concepts::ResourceT T>
static void DisplayResourceType(
    const std::string_view typeName,
    const std::string_view resourceNameFilter,
    const std::function<void(Pointer<T> resource)>& additionalAction = std::identity{}
)
{
    const List<Pointer<T>> resources = ResourceManager::FindAll<T>([&] (Pointer<T> f) -> bool_t { return Utils::StringContainsIgnoreCase(f->GetName(), resourceNameFilter); });
    if (ImGui::TreeNode(std::format("{} ({})", typeName, resources.GetSize()).c_str()))
    {
        for (Pointer resource : resources)
        {
            if (!ImGui::TreeNode(resource->GetName().c_str()))
                continue;

            if (ImGui::Button("Reload from cached file"))
                resource->Reload();
            if (ImGui::Button("Reload from disk"))
            {
                resource->GetFile()->Reload();
                resource->Reload();
            }

            additionalAction(resource);

            ImGui::TreePop();
        }

        ImGui::TreePop();
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
        [](const auto& audioTrack)
        {
            const std::string_view format = magic_enum::enum_name(audioTrack->GetFormat());
            ImGui::Text("Format: %.*s", static_cast<int32_t>(format.length()), format.data());
        }
    );
    DisplayResourceType<Font>("Font", filter);

    const List<Pointer<Shader>> resources = ResourceManager::FindAll<Shader>([&] (Pointer<Shader> f) -> bool_t { return Utils::StringContainsIgnoreCase(f->GetName(), filter); });
    if (ImGui::TreeNode(std::format("Shader ({} precompiled)", resources.GetSize()).c_str()))
    {
        for (Pointer resource : resources)
            ImGui::Text("%s", resource->GetName().c_str());

        ImGui::TreePop();
    }

    DisplayResourceType<Texture>(
        "Texture",
        filter,
        [](const auto& texture)
        {
            const Vector2i size = texture->GetSize();
            ImGui::Text("Size: %dx%d", size.x, size.y);
            ImGui::Text("Preview:");
            ImGui::Image(Utils::IntToPointer<void>(texture->GetId()), static_cast<Vector2>(texture->GetSize()));
        }
    );

    ImGui::End();
}

// ReSharper disable CppInconsistentNaming
bool ImGui::DragAngle(
    const char* label,
    float* v,
    const float v_speed,
    const float v_min,
    const float v_max,
    const char* format,
    const ImGuiSliderFlags flags
)
{
    float_t degreeAngle = *v * Calc::Rad2Deg;
    const bool_t result = DragFloat(label, &degreeAngle, v_speed, v_min, v_max, format, flags);
    *v = degreeAngle * Calc::Deg2Rad;
    return result;
}
// ReSharper restore CppInconsistentNaming
