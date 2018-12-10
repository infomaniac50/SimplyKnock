#include "Hooks_Threads.h"
#include "skse64_common/SafeWrite.h"
#include "skse64_common/Utilities.h"
#include "skse64_common/BranchTrampoline.h"
#include "GameThreads.h"

#include "common/ICriticalSection.h"
#include <queue>

ICriticalSection			s_taskQueueLock;
std::queue<TaskDelegate*>	s_tasks;

typedef UInt32(*_ProcessTaskInterface)(void * unk1);
RelocAddr <_ProcessTaskInterface> ProcessTaskInterface_Hook_Original(0x00C03E60);

RelocAddr <uintptr_t> ProcessTaskInterface_Target(0x005B31E0 + 0x739);

static bool IsTaskQueueEmpty()
{
	IScopedCriticalSection scoped(&s_taskQueueLock);
	return s_tasks.empty();
}

UInt32 ProcessTaskInterface_Hook(void * unk1)
{	
	while (!IsTaskQueueEmpty())
	{
		s_taskQueueLock.Enter();
		TaskDelegate * cmd = s_tasks.front();
		s_tasks.pop();
		s_taskQueueLock.Leave();

		cmd->Run();
		cmd->Dispose();
	}

	return ProcessTaskInterface_Hook_Original(unk1);
}

void TaskInterface::AddTask(TaskDelegate * cmd)
{
	s_taskQueueLock.Enter();
	s_tasks.push(cmd);
	s_taskQueueLock.Leave();
}

void Hooks_Threads_Init(void)
{
	
}

void Hooks_Threads_Commit(void)
{
	g_branchTrampoline.Write5Call(ProcessTaskInterface_Target.GetUIntPtr(), (uintptr_t)ProcessTaskInterface_Hook);
}
