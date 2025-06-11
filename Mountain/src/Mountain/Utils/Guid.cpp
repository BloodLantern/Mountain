#include "Mountain/Utils/Guid.hpp"

#include "Mountain/Utils/Logger.hpp"
#include "Mountain/Utils/Windows.hpp"

using namespace Mountain;

Guid Guid::New()
{
	Guid guid;

	const HRESULT result = CoCreateGuid(reinterpret_cast<UUID*>(&guid));

	if (result != S_OK)
		Logger::LogError("Couldn't create GUID");

	return guid;
}

Guid Guid::FromString(const char_t* str)
{
	Guid g;
	(void) sscanf_s(
		str,
		"%x-%hx-%hx-%hhx-%hhx-%hhx-%hhx-%hhx-%hhx-%hhx-%hhx",
		&g.m_Data1,
		&g.m_Data2,
		&g.m_Data3,
		&g.m_Data4[0],
		&g.m_Data4[1],
		&g.m_Data4[2],
		&g.m_Data4[3],
		&g.m_Data4[4],
		&g.m_Data4[5],
		&g.m_Data4[6],
		&g.m_Data4[7]
	);

	return g;
}

uint32_t Guid::GetData1() const { return m_Data1; }

uint16_t Guid::GetData2() const { return m_Data2; }

uint16_t Guid::GetData3() const { return m_Data3; }

const std::array<uint8_t, Guid::Data4Size>& Guid::GetData4() const { return m_Data4; }

bool_t Guid::operator==(const Guid& other) const
{
	return reinterpret_cast<const uint64_t*>(this)[0] == reinterpret_cast<const uint64_t*>(&other)[0] &&
		   reinterpret_cast<const uint64_t*>(this)[1] == reinterpret_cast<const uint64_t*>(&other)[1];
}

bool_t Guid::operator!=(const Guid& other) const { return !(*this == other); }


std::string Guid::ToString() const
{
	return std::format(
		"{:X}-{:X}-{:X}-{:X}-{:X}-{:X}-{:X}-{:X}-{:X}-{:X}-{:X}",
		m_Data1,
		m_Data2,
		m_Data3,
		m_Data4[0],
		m_Data4[1],
		m_Data4[2],
		m_Data4[3],
		m_Data4[4],
		m_Data4[5],
		m_Data4[6],
		m_Data4[7]
	);
}

size_t Guid::GetHashCode() const
{
    static constexpr size_t RandomValue = 0x9E3779B9;

	size_t result = 0;
	result ^= std::hash<uint32_t>()(m_Data1) + RandomValue;
	result ^= std::hash<uint16_t>()(m_Data2) + RandomValue + (result << 6) + (result >> 2);
	result ^= std::hash<uint16_t>()(m_Data3) + RandomValue + (result << 6) + (result >> 2);

	for (size_t i = 0; i < Data4Size; i++)
		result ^= std::hash<uint8_t>()(m_Data4[i]) + RandomValue + (result << 6) + (result >> 2);

	return result;
}
