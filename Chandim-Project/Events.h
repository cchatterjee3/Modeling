/**
*    @file Events.h
*     \brief declaration of different templated event bases
*/

#ifndef __EVENTS_H__
#define __EVENTS_H__

#include "CommonDefs.h"
#include <set>
#include <iostream>
#include "calender_queue.h"

using namespace std;

class EventBase
{
public:
       
	EventBase (Time_t t) : time(t) {}
	virtual void CallHandler() = 0; // All subclasses must implement this
	Time_t getTime()
	{
		return time;
	}
	//private:
	Time_t time; //TimeStamp for the event
};


template<typename T, typename OBJ>
class Event0 : public EventBase
{
	// Event class with no arguments
	// Type T is the object type for the event handler object
	// Type OBJ is the actual event handler object
public:
	void (T::*handler)(void);
	OBJ*      obj;
public:
/**
*    Empty constructor
*
*/
	Event0(double t, void (T::*f)(), OBJ* obj0)
		: EventBase(t), handler(f), obj(obj0) {}
	void CallHandler();
};

/**
*    Event call handler function in the case of no parameters
*
*/
template <typename T, typename OBJ>
void Event0<T, OBJ>::CallHandler()
{
	(obj->*handler)();
}

// Event with one parameter on the callback function
template<typename T, typename OBJ, typename U1, typename T1>
class Event1 : public EventBase
{
public:
/**
*    Empty constructor
*
*/
	Event1(double t, void (T::*f)(U1), OBJ* obj0, T1 t1_0)
		: EventBase(t), handler(f), obj(obj0), t1(t1_0) {}
	void (T::*handler)(U1);
	OBJ*      obj;
	T1        t1;
public:
	void CallHandler();
};

/**
*    Event call handler function in the case of one parameters
*
*/
template <typename T, typename OBJ, typename U1, typename T1>
void Event1<T, OBJ, U1, T1>::CallHandler()
{
	(obj->*handler)(t1);
}

template<typename T, typename OBJ,
         typename U1, typename T1,
         typename U2, typename T2>
class Event2 : public EventBase
{
public:
/**
*    Empty constructor
*
*/
	Event2(double t, void (T::*f)(U1, U2), OBJ* obj0, T1 t1_0, T2 t2_0)
		: EventBase(t), handler(f), obj(obj0), t1(t1_0), t2(t2_0) {}
	void (T::*handler)(U1, U2);
	OBJ*      obj;
	T1        t1;
	T2        t2;
public:
	void CallHandler();
};

/**
*    Event call handler function in the case of two parameters
*
*/
template <typename T, typename OBJ,
         typename U1, typename T1,
         typename U2, typename T2>
void Event2<T, OBJ, U1, T1, U2, T2>::CallHandler()
{
	(obj->*handler)(t1, t2);
}

template <typename T,  typename OBJ,
         typename U1, typename T1,
         typename U2, typename T2,
         typename U3, typename T3>
class Event3 : public EventBase
{
public:
/**
*    Empty constructor
*
*/
	Event3(double t, void (T::*f)(U1, U2, U3), OBJ *obj0, T1 t1_0, T2 t2_0, T3 t3_0)
		: EventBase(t), handler(f), obj(obj0), t1(t1_0), t2(t2_0), t3(t3_0) {}
	void (T::*handler)(U1, U2, U3);
	OBJ* obj;
	T1 t1;
	T2 t2;
	T3 t3;

public:
	void CallHandler();
};

/**
*    Event call handler function in the case of three parameters
*
*/
template <typename T,  typename OBJ,
         typename U1, typename T1,
         typename U2, typename T2,
         typename U3, typename T3>
void Event3<T,OBJ,U1,T1,U2,T2,U3,T3>::CallHandler()
{
	(obj->*handler)(t1,t2,t3);
}

//Event Comparator
class event_compare
{
public:
       /**
*    Comparator used for sorting in sets, maps and other STL if needed
*
*/
	inline bool operator()(EventBase* const& l, const EventBase* const& r) const
	{
		if (l->time < r->time) return true;
		return false;
	}
};



#endif
