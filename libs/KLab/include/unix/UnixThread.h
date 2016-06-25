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

#ifndef KLAB_UNIXTHREAD_H
#define KLAB_UNIXTHREAD_H

#include "../SystemUtil.h"
#include "../ScopedMutex.h"
#include "../Signal.h"
#include <pthread.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
class TThread<TClass, TRunFunc, UnixSystem> : public IThreadStatus
{
public:

    TThread(TClass& obj);    
    virtual ~TThread();
    
    bool            start();
	void            suspend();
	void            resume();
    void            stop();
    bool            isStarted() const;
	bool            isSuspended() const;
    bool    		isRunning() const;
	
    virtual bool    checkThreadState() const;

    void            join();


protected:

    static void*	RunThreadFunction(void* param);


private:

    TThread();   
    TThread(const TThread<TClass, TRunFunc, UnixSystem>& thread);
    TThread<TClass, TRunFunc, UnixSystem>&	operator=(const TThread<TClass, TRunFunc, UnixSystem>& thread);


private:

    TClass&         	_obj;
	pthread_attr_t 		_attr;
    pthread_t			_thread;	
	bool				_isCreated;
    bool            	_isStarted;
	bool				_isSuspended;

    TMutex<UnixSystem>	_mutex;
	TSignal<UnixSystem>	_resumeSignal;
};

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline TThread<TClass, TRunFunc, UnixSystem>::TThread(TClass& obj) : IThreadStatus(),
_obj(obj), _attr(), _thread(), _isCreated(false), _isStarted(false), _isSuspended(false),
_mutex(), _resumeSignal(_mutex)
{
	pthread_attr_init(&_attr);
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline TThread<TClass, TRunFunc, UnixSystem>::~TThread()
{
    this->stop();
    this->join(); 
	
	pthread_attr_destroy(&_attr);
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline bool TThread<TClass, TRunFunc, UnixSystem>::start()
{	
    bool ret = true;
    if(this->isStarted() == false)
    {
        ret = false;
		
		_mutex.lock();
		if(_isCreated)
		{
			_mutex.unlock();
			this->join();
		}
		else
		{
			_mutex.unlock();
		}
		
		TScopedMutex<TMutex<UnixSystem> > mutex(_mutex);
				
		pthread_attr_setdetachstate(&_attr, PTHREAD_CREATE_JOINABLE);
		int result = pthread_create(&_thread, &_attr, &TThread<TClass, TRunFunc, UnixSystem>::RunThreadFunction, (void*)this);
		_isCreated = (result == 0);
		_isStarted = _isCreated;
		_isSuspended = false;

		ret = _isStarted;
    }
	
    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline void TThread<TClass, TRunFunc, UnixSystem>::suspend()
{
    if(this->isStarted())
    {
        if(this->isSuspended() == false)
        {
			TScopedMutex<TMutex<UnixSystem> > mutex(_mutex);

			_isSuspended = true;
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline void TThread<TClass, TRunFunc, UnixSystem>::resume()
{
    if(this->isStarted())
    {
        if(this->isSuspended())
        {
            TScopedMutex<TMutex<UnixSystem> > mutex(_mutex);

            _isSuspended = false;
            _resumeSignal.set();
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline void TThread<TClass, TRunFunc, UnixSystem>::stop()
{
    TScopedMutex<TMutex<UnixSystem> > mutex(_mutex); 

    if(_isSuspended)   
        this->resume();

    _isStarted   = false;
    _isSuspended = false;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline bool TThread<TClass, TRunFunc, UnixSystem>::isStarted() const
{
    TScopedMutex<TMutex<UnixSystem> > mutex(_mutex);

    return _isStarted;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline bool TThread<TClass, TRunFunc, UnixSystem>::isSuspended() const
{
    TScopedMutex<TMutex<UnixSystem> > mutex(_mutex);

    return _isSuspended;
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline bool TThread<TClass, TRunFunc, UnixSystem>::isRunning() const
{
    TScopedMutex<TMutex<UnixSystem> > mutex(_mutex);

    return (_isStarted && _isSuspended==false);
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline bool TThread<TClass, TRunFunc, UnixSystem>::checkThreadState() const
{
	const_cast<TMutex<UnixSystem>&>(_mutex).lock();
	if(_isSuspended)
        const_cast<TSignal<UnixSystem>&>(_resumeSignal).wait();
    const_cast<TMutex<UnixSystem>&>(_mutex).unlock();
	
    return this->isStarted();
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
inline void TThread<TClass, TRunFunc, UnixSystem>::join()
{
	_mutex.lock();
    bool doJoin = (pthread_equal(pthread_self(), _thread)==0 && _isCreated);
    _mutex.unlock();
	
	if(doJoin)
		pthread_join(_thread, NULL);				
}

// ---------------------------------------------------------------------------------------------------- //

template<class TClass, void (TClass::*TRunFunc)(const IThreadStatus&)>
void* TThread<TClass, TRunFunc, UnixSystem>::RunThreadFunction(void* param)
{   
    TThread<TClass, TRunFunc, UnixSystem>* thread = static_cast<TThread<TClass, TRunFunc, UnixSystem>*>(param);
    if(thread != 0)
    {				
        try
        {
			thread->_mutex.lock();
			thread->_mutex.unlock();
		
            ((thread->_obj).*TRunFunc)(const_cast<const IThreadStatus&>(*((IThreadStatus*)thread)));
        }
        catch(...)
        {}        

        // Clean thread handle.
        thread->_mutex.lock();  
        thread->_isStarted   = false;
		thread->_isSuspended = false;
		thread->_isCreated   = false;
		thread->_mutex.unlock();       		
    }   

	pthread_exit(NULL);	
    return 0;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
