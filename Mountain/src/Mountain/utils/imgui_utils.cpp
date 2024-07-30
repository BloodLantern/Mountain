#include "Mountain/utils/imgui_utils.hpp"

#include <magic_enum/magic_enum.hpp>

#include "Mountain/input/input.hpp"

using namespace Mountain;

void ImGuiUtils::GridPlotting(const std::string_view label, Vector2* const value, const float_t min, const float_t max)
{
    ImGui::Text("%s", label.data());
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
    ImGui::Text("%s", label.data());
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
    ImGui::Text("%s", label.data());
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

void ImGuiUtils::ShowInputsWindow()
{
        ImGui::Begin("Inputs");
        if (ImGui::TreeNode("Mouse"))
        {
            const Vector2i mousePos = static_cast<Vector2i>(Input::GetMousePosition());
            ImGui::Text("Position: %d, %d", mousePos.x, mousePos.y);
            ImGui::Text("Button down right: %d", Input::GetMouseButton(MouseButton::Right));
            ImGui::Text("Button release right: %d", Input::GetMouseButton(MouseButton::Right, MouseButtonStatus::Release));
            for (uint32_t i = 0; i < MouseButtonCount; i++)
            {
                ImGui::Text("Button down %d: %d", i + 1, Input::GetMouseButton(static_cast<MouseButton>(i)));
                ImGui::Text("Button release %d: %d", i + 1, Input::GetMouseButton(static_cast<MouseButton>(i), MouseButtonStatus::Release));
            }
            //ImGui::Text("Wheel: %f, %f", Mountain::Input::mouseWheel.x, Mountain::Input::mouseWheel.y);
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
                    ImGui::Text("Button %d - %s: %d", j, magic_enum::enum_name(button).data(), gamepad.GetButton(button));
                }

                Vector2 dpad = static_cast<Vector2>(gamepad.GetDirectionalPad());
                DirectionVector("Directional pad", &dpad);
                
                ImGui::TreePop();
            }
        }
        ImGui::End();
}

bool ImGui::DragAngle(
    const char* label,
    float* v,
    float v_speed,
    float v_min,
    float v_max,
    const char* format,
    ImGuiSliderFlags flags
)
{
    float_t degreeAngle = *v * Calc::Rad2Deg;
    const bool_t result = DragFloat(label, &degreeAngle, v_speed, v_min, v_max, format, flags);
    *v = degreeAngle * Calc::Deg2Rad;
    return result;
}
