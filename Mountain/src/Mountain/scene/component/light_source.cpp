﻿#include "Mountain/scene/component/light_source.hpp"

#include "Mountain/scene/entity.hpp"

using namespace Mountain;

void LightSource::Update() { m_Position = m_Entity->position + offset; }

Vector2 LightSource::GetPosition() const { return m_Position; }
