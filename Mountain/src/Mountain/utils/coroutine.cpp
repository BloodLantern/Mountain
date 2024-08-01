// ReSharper disable CppMemberFunctionMayBeStatic
#include "Mountain/utils/coroutine.hpp"

#include <ranges>

#include "Mountain/input/time.hpp"
// ReSharper disable once CppUnusedIncludeDirective
#include "Mountain/utils/formatter.hpp"
#include "Mountain/utils/logger.hpp"

using namespace Mountain;

bool_t Coroutine::Awaitable::await_ready() { return false; }

void Coroutine::Awaitable::await_suspend(std::coroutine_handle<promise_type>) {}

void Coroutine::Awaitable::await_resume() {}

Guid Coroutine::Start(Coroutine&& coroutine)
{
    Guid id = Guid::New();
    
    coroutine.m_Id = id;
    m_RunningRoutines.emplace(id, std::move(coroutine));
    
    return id;
}

void Coroutine::Start(Coroutine&& coroutine, Guid* const coroutineId)
{
    Guid& id = *coroutineId;
    if (id != Guid::Empty() && IsRunning(id))
        Stop(id);
    
    coroutine.m_Id = id;
    id = Start(std::move(coroutine));
}

void Coroutine::UpdateAll()
{
    std::vector<const Coroutine*> finishedRoutines;
    
    for (const auto& routine : m_RunningRoutines | std::views::values)
    {
        if (!routine.Valid())
            continue;
        
        auto& awaitValue = routine.m_Handle.promise().awaitValue;
        
        awaitValue -= AwaitType(Time::GetDeltaTime());
        if (awaitValue > AwaitType::zero())
            continue;
        
        routine.Resume();

        if (routine.Finished())
            finishedRoutines.push_back(&routine);
    }

    for (const auto& routine : finishedRoutines)
        Stop(routine->GetId());
}

void Coroutine::Stop(const Guid& coroutineId)
{
    if (!m_RunningRoutines.contains(coroutineId))
        return;

    m_RunningRoutines.at(coroutineId).Destroy();
    m_RunningRoutines.erase(coroutineId);
}

void Coroutine::StopAll()
{
    for (auto& coroutine : m_RunningRoutines | std::views::values)
        coroutine.Destroy();

    m_RunningRoutines.clear();
}

bool_t Coroutine::IsRunning(const Guid& coroutineId) { return m_RunningRoutines.contains(coroutineId); }

bool_t Coroutine::IsRunningAndNotEmpty(const Guid& coroutineId) { return coroutineId != Guid::Empty() && IsRunning(coroutineId); }

size_t Coroutine::GetRunningCount() { return m_RunningRoutines.size(); }

Coroutine Coroutine::promise_type::get_return_object() { return Coroutine(HandleType::from_promise(*this)); }

std::suspend_always Coroutine::promise_type::initial_suspend() { return {}; }

std::suspend_always Coroutine::promise_type::final_suspend() noexcept { return {}; }

void Coroutine::promise_type::unhandled_exception()
{
    try
    {
        std::rethrow_exception(std::current_exception());
    }
    catch (const std::exception& e)
    {
        Logger::LogError("Uncaught exception in coroutine body: {}", e);
        throw;
    }
}

void Coroutine::promise_type::return_void() {}

Coroutine::Awaitable Coroutine::promise_type::await_transform(const AwaitType& duration)
{
    awaitValue = duration;
    return {};
}

Coroutine::Awaitable Coroutine::promise_type::await_transform(const float_t duration) { return await_transform(AwaitType(duration)); }

std::suspend_always Coroutine::promise_type::yield_value(nullptr_t) { return {}; }

Coroutine::Coroutine(const HandleType handle) : m_Handle(handle) {}

Coroutine::~Coroutine() { DestroySafe(); }

Coroutine::Coroutine(Coroutine&& other) noexcept
    : m_Handle(other.m_Handle)
    , m_Id(other.m_Id)
{
    other.Reset();
}

Coroutine& Coroutine::operator=(Coroutine&& other) noexcept
{
    m_Handle = other.m_Handle;
    m_Id = other.m_Id;

    other.Reset();

    return *this;
}

Coroutine& Coroutine::operator=(const HandleType handle) noexcept
{
    m_Handle = handle;
    m_Id = {};

    return *this;
}

void Coroutine::Resume() const { m_Handle.resume(); }

void Coroutine::ResumeSafe() const
{
    if (Valid())
        Resume();
}

bool_t Coroutine::Finished() const { return m_Handle.done(); }

bool_t Coroutine::FinishedSafe() const
{
    if (Valid())
        return Finished();
    
    return false;
}

void Coroutine::Destroy()
{
    m_Handle.destroy();
    m_Handle = {};
}

void Coroutine::DestroySafe()
{
    if (Valid())
        Destroy();
}

bool_t Coroutine::Valid() const { return static_cast<bool_t>(m_Handle); }

void Coroutine::Reset()
{
    m_Handle = {};
    m_Id = {};
}

Guid Coroutine::GetId() const { return m_Id; }

Coroutine::Coroutine(const Guid& guid, const HandleType handle) : Coroutine(handle) { m_Id = guid; }
