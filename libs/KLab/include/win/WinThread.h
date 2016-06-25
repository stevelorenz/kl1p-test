// KLab - A portable C++ collection of classes for general purpose.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KLab C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#ifndef KLAB_WINTHREAD_H
#define KLAB_WINTHREAD_H

#include "../SystemUtil.h"
#include "../ScopedMutex.h"
#include "../Signal.h"
#include "../Log.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
class TThread<TClass, TRunFunc, MSWindowsSystem> : public IThreadStatus
{
public:

    TThread(TClass& obj);    
    virtual ~TThread();
    
    bool                        start();
    void                        suspend();
    void                        resume();
    void                        stop();
    bool                        isStarted() const;
    bool                        isSuspended() const;
    bool    		            isRunning() const;
	
    virtual bool                checkThreadState() const;

    void                        join();


protected:

    static DWORD WINAPI         RunThreadFunction(LPVOID param);


private:

    TThread();   
    TThread(const TThread<TClass, TRunFunc, MSWindowsSystem>& thread);
    TThread<TClass, TRunFunc, MSWindowsSystem>& operator=(const TThread<TClass, TRunFunc, MSWindowsSystem>& thread);


private:

    TClass&                     _obj;
    HANDLE                      _thread;
    DWORD                       _threadID;
    bool                        _isStarted;
    bool                        _isSuspended;

    TMutex<MSWindowsSystem>     _mutex;
    TSignal<MSWindowsSystem>    _resumeSignal;
};

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline TThread<TClass, TRunFunc, MSWindowsSystem>::TThread(TClass& obj) : IThreadStatus(),
_obj(obj), _thread(NULL), _threadID(0), _isStarted(false), _isSuspended(false),
_mutex(), _resumeSignal(_mutex)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline TThread<TClass, TRunFunc, MSWindowsSystem>::~TThread()
{
    this->stop();
    this->join();

    if(_thread != NULL)
    {
        ::TerminateThread(_thread, 0);
        ::CloseHandle(_thread);
        _thread   = NULL;
        _threadID = 0;
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline bool TThread<TClass, TRunFunc, MSWindowsSystem>::start()
{    
    bool ret = true;
    if(this->isStarted() == false)
    {        
        ret = false;

        _mutex.lock();
		if(_thread != NULL)
		{
			_mutex.unlock();
			this->join();
		}
		else
		{
			_mutex.unlock();
		}

        TScopedMutex<TMutex<MSWindowsSystem> > mutex(_mutex);
       
        _thread = ::CreateThread(NULL, 0, &TThread<TClass, TRunFunc, MSWindowsSystem>::RunThreadFunction, (LPVOID)this, 0, &_threadID);
        _isStarted   = (_thread != NULL);
        _isSuspended = false;

        ret = _isStarted;

    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline void TThread<TClass, TRunFunc, MSWindowsSystem>::suspend()
{
    if(this->isStarted())
    {
        if(this->isSuspended() == false)
        {
            TScopedMutex<TMutex<MSWindowsSystem> > mutex(_mutex);

            _isSuspended = true;
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline void TThread<TClass, TRunFunc, MSWindowsSystem>::resume()
{
    if(this->isStarted())
    {
        if(this->isSuspended())
        {            
            TScopedMutex<TMutex<MSWindowsSystem> > mutex(_mutex);

            _isSuspended = false;
            _resumeSignal.set();
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline void TThread<TClass, TRunFunc, MSWindowsSystem>::stop()
{
    TScopedMutex<TMutex<MSWindowsSystem> > mutex(_mutex); 

    if(_isSuspended)   
        this->resume();

    _isStarted   = false;
    _isSuspended = false;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline bool TThread<TClass, TRunFunc, MSWindowsSystem>::isStarted() const
{
    TScopedMutex<TMutex<MSWindowsSystem> > mutex(_mutex);

    return _isStarted;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline bool TThread<TClass, TRunFunc, MSWindowsSystem>::isSuspended() const
{
    TScopedMutex<TMutex<MSWindowsSystem> > mutex(_mutex);

    return _isSuspended;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline bool TThread<TClass, TRunFunc, MSWindowsSystem>::isRunning() const
{
    TScopedMutex<TMutex<MSWindowsSystem> > mutex(_mutex);

    return (_isStarted && _isSuspended==false);
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline bool TThread<TClass, TRunFunc, MSWindowsSystem>::checkThreadState() const
{
    const_cast<TMutex<MSWindowsSystem>&>(_mutex).lock();
    if(_isSuspended)
        const_cast<TSignal<MSWindowsSystem>&>(_resumeSignal).wait();
    const_cast<TMutex<MSWindowsSystem>&>(_mutex).unlock();

    return this->isStarted();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline void TThread<TClass, TRunFunc, MSWindowsSystem>::join()
{
    _mutex.lock();
    bool doJoin = (_threadID>0 && ::GetCurrentThreadId()!=_threadID && _thread!=NULL);
    _mutex.unlock();

	if(doJoin)
		::WaitForSingleObject(_thread, INFINITE);
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
DWORD WINAPI TThread<TClass, TRunFunc, MSWindowsSystem>::RunThreadFunction(LPVOID param)
{   
    TThread<TClass, TRunFunc, MSWindowsSystem>* thread = static_cast<TThread<TClass, TRunFunc, MSWindowsSystem>*>(param);
    if(thread != 0)
    {
        try
        {
			thread->_mutex.lock();
			thread->_mutex.unlock();
		
            ((thread->_obj).*TRunFunc)(const_cast<const IThreadStatus&>(*((IThreadStatus*)thread)));
        }
        catch(klab::KException& e)
        {
            LOG(klab::ERROR_LOG)<<"Error during thread execution !!! "<<e.what();
        }
        catch(std::exception& e)
        {
            LOG(klab::ERROR_LOG)<<"Error during thread execution !!! "<<e.what();
        }
        catch(...)
        {
            LOG(klab::ERROR_LOG)<<"Unknown error during thread execution !!!";
        }       

        // Clean thread handle.
        TScopedMutex<TMutex<MSWindowsSystem> > mutex(thread->_mutex);   
        thread->_isStarted   = false;
        thread->_isSuspended = false;

        if(thread->_thread != NULL)
        {
            ::CloseHandle(thread->_thread);
            thread->_thread   = NULL;
            thread->_threadID = 0;
        }
    }    

    return 0;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
