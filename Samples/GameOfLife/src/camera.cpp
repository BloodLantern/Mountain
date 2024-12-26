#include "camera.hpp"

#include "ImGui/imgui.h"
#include "Mountain/input/input.hpp"

Camera::Camera()
    : m_Size(Mountain::Window::GetSize())
{
}

void Camera::HandleInputs()
{
    if (Mountain::Input::GetMouseButton(Mountain::MouseButton::Middle, Mountain::MouseButtonStatus::Pressed))
    {
        m_DragStartMousePosition = Mountain::Input::GetMousePosition();
        m_DragStartCameraPosition = position;
    }

    if (Mountain::Input::GetMouseButton(Mountain::MouseButton::Middle))
        position = m_DragStartCameraPosition + (m_DragStartMousePosition - Mountain::Input::GetMousePosition()) / m_Zoom;

    const float_t scroll = Mountain::Input::GetMouseWheel().y;
    if (scroll != 0.f)
        Zoom(Mountain::Input::GetMousePosition(), scroll);
}

void Camera::UpdateMatrices()
{
    if (m_Zoom <= 0.f)
        return;

    m_Matrix = Matrix::Scaling(Vector3{ m_Zoom, m_Zoom, 1.f }) * Matrix::Translation(static_cast<Vector3>(-position));
    m_InverseMatrix = m_Matrix.Inverted();
}

void Camera::Zoom(const Vector2 targetWindowPosition, const float_t times)
{
    const Vector2 oldWorldPosition = ToWorld(targetWindowPosition);
    SetZoom(m_Zoom * std::pow(CameraZoomFactor, times));
    UpdateMatrices(); // Very bad but the goal of this sample isn't a good camera anyway
    position += oldWorldPosition - ToWorld(targetWindowPosition);
}

void Camera::ZoomIn(const Vector2 targetWindowPosition)
{
    Zoom(targetWindowPosition, 1.f);
}

void Camera::ZoomOut(const Vector2 targetWindowPosition)
{
    Zoom(targetWindowPosition, -1.f);
}

void Camera::SetZoom(const float_t newZoom)
{
    const Vector2 oldSize = m_Size;
    m_Size *= m_Zoom / newZoom;
    position -= (m_Size - oldSize) * 0.5f;
    m_Zoom = newZoom;
}

float_t Camera::GetZoom() const
{
    return m_Zoom;
}

Vector2 Camera::ToWorld(const Vector2 screenPoint) const
{
    return m_InverseMatrix * screenPoint;
}

Vector2 Camera::ToScreen(const Vector2 worldPoint) const
{
    return m_Matrix * worldPoint;
}

const Matrix& Camera::GetMatrix() const
{
    return m_Matrix;
}

const Matrix& Camera::GetInverseMatrix() const
{
    return m_InverseMatrix;
}
