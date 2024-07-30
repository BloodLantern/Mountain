// ReSharper disable CppMemberFunctionMayBeStatic
#include "Mountain/utils/coroutine.hpp"

#include <ranges>

#include "Mountain/input/time.hpp"
#include "Mountain/utils/formatter.hpp"
#include "Mountain/utils/logger.hpp"

using namespace Mountain;

bool_t Coroutine::Awaitable::await_ready() { return false; }

void Coroutine::Awaitable::await_suspend(std::coroutine_handle<promise_type>) {}

void Coroutine::Awaitable::await_resume() {}

Guid Coroutine::Start(const Coroutine& coroutine)
{
    Guid id = Guid::New();
    m_RunningRoutines.emplace(id, Coroutine(id, coroutine.m_Handle));
    return id;
}

void Coroutine::Start(const Coroutine& coroutine, Guid* const coroutineId)
{
    Guid& ref = *coroutineId;
    if (ref != Guid::Empty() && IsRunning(ref))
        Stop(ref);
    ref = Start(coroutine);
}

void Coroutine::UpdateAll()
{
    std::vector<Coroutine*> finishedRoutines;
    
    for (auto&& entry : std::views::values(m_RunningRoutines))
    {
        auto& awaitValue = entry.m_Handle.promise().awaitValue;
        
        awaitValue -= AwaitType(Time::GetDeltaTime());
        if (awaitValue > AwaitType::zero())
            continue;
        
        entry.Resume();

        if (entry.Finished())
            finishedRoutines.push_back(&entry);
    }

    for (auto&& routine : finishedRoutines)
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
    for (const auto& coroutine : m_RunningRoutines | std::views::values)
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

void Coroutine::promise_type::return_void() { finished = true; }

Coroutine::Awaitable Coroutine::promise_type::await_transform(const AwaitType& duration)
{
    awaitValue = duration;
    return {};
}

Coroutine::Awaitable Coroutine::promise_type::await_transform(float_t duration) { return await_transform(AwaitType(duration)); }

std::suspend_always Coroutine::promise_type::yield_value(nullptr_t) { return {}; }

Coroutine::Coroutine(const HandleType handle) : m_Handle(handle) {}

void Coroutine::Resume() const { m_Handle.resume(); }

bool_t Coroutine::Finished() const { return m_Handle.promise().finished; }

void Coroutine::Destroy() const { m_Handle.destroy(); }

Guid Coroutine::GetId() const { return m_Id; }

Coroutine::Coroutine(const Guid& guid, const HandleType handle) : Coroutine(handle) { m_Id = guid; }
