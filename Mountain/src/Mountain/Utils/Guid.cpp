

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

Guid Guid::FromString(const c8* str)
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

u32 Guid::GetData1() const { return m_Data1; }

u16 Guid::GetData2() const { return m_Data2; }

u16 Guid::GetData3() const { return m_Data3; }

const Array<u8, Guid::Data4Size>& Guid::GetData4() const { return m_Data4; }

bool Guid::operator==(const Guid& other) const
{
	return reinterpret_cast<const u64*>(this)[0] == reinterpret_cast<const u64*>(&other)[0] &&
		   reinterpret_cast<const u64*>(this)[1] == reinterpret_cast<const u64*>(&other)[1];
}

bool Guid::operator!=(const Guid& other) const { return !(*this == other); }

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

usize Guid::GetHashCode() const
{
	static constexpr usize RandomValue = 0x9E3779B9;

	usize result = 0;
	result ^= std::hash<u32>{}(m_Data1) + RandomValue;
	result ^= std::hash<u16>{}(m_Data2) + RandomValue + (result << 6) + (result >> 2);
	result ^= std::hash<u16>{}(m_Data3) + RandomValue + (result << 6) + (result >> 2);

	for (usize i = 0; i < Data4Size; i++)
		result ^= std::hash<u8>{}(m_Data4[i]) + RandomValue + (result << 6) + (result >> 2);

	return result;
}
