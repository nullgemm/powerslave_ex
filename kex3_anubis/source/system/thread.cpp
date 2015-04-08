//
// Copyright(C) 2014-2015 Samuel Villarreal
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//      Thread Class
//

#include "kexlib.h"

//
// kexThread::CreateThread
//

kexThread::kThread_t kexThread::CreateThread(const char *name, void *data, threadFunction_t function)
{
    return NULL;
}

//
// kexThread::GetThreadName
//

const char *kexThread::GetThreadName(kThread_t thread)
{
    return NULL;
}

//
// kexThread::SetThreadPriority
//

int kexThread::SetThreadPriority(kThread_t thread, const threadPriority_t priority)
{
    return -1;
}

//
// kexThread::WaitThread
//

void kexThread::WaitThread(kThread_t thread, int *status)
{
}

//
// kexThread::CreateMutex
//

kexThread::kMutex_t kexThread::CreateMutex(void)
{
    return NULL;
}

//
// kexThread::LockMutex
//

int kexThread::LockMutex(kMutex_t mutex, const bool bTimeOut)
{
    return -1;
}

//
// kexThread::UnlockMutex
//

int kexThread::UnlockMutex(kMutex_t mutex)
{
    return -1;
}

//
// kexThread::DestroyMutex
//

void kexThread::DestroyMutex(kMutex_t mutex)
{
}