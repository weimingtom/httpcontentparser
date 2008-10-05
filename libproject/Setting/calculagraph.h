#ifndef _SETTING_CALULA_GRAPH_H__
#define _SETTING_CALULA_GRAPH_H__

#include <assert.h>

template<int STATE_NUM>
class MultiCalculagraph;

// 单个状态的定时切换
// 可以确定一个时间是否应该发生
class Calculagraph {
public:
	Calculagraph(void);
	~Calculagraph(void);
public:
	void initialize() {Reset();}

	// 尝试切换状态，如果成功， 则返回true
	// 如果失败则返回false
	bool trySwitch();

	// 设置
	void setTimespan(const DWORD seconds);
	DWORD getTimespan() const;
private:
	friend  class MultiCalculagraph;

	// 充值当前计时器
	void Reset();
	DWORD getTimeEscape() const;
	DWORD state_begin_;
	DWORD time_span_;
};


// class MultiCalculagraph
// 多个状态的定时切换
template<int STATE_NUM>
class MultiCalculagraph {
public:
	MultiCalculagraph() {}
	~MultiCalculagraph() {}

public:
	void initialize(int type) { setCurrentState(type);}

	// 尝试切换状态，如果成功， 则返回true
	// 如果失败则返回false
	bool trySwitch();
	
	// 获取当前状态
	int  getCurrentState() const { return state_; }

	// 获取切换状态的剩余时间
	int  getRemainTime() const { return (getCurrentTimespan() - getCurrentTimeEscape());}

	// 设置和获取时间间隔
	void setTimespan(const DWORD seconds, const int type);
	DWORD getTimespan(const int type) const;

	void Reset() { return Reset(getCurrentState());}
	// 强制改变状态
	int  forceSwitch(int type);
private:
	// 充值及时器，但需要指明及时器的种类
	void  Reset(const int type);

	// 设置当前状态
	void setCurrentState(const int type);
	int getNextState();
	DWORD getCurrentTimeEscape() const;
	DWORD getCurrentTimespan() const;
	int state_;	// 当前状态
	Calculagraph calculagraph_[STATE_NUM];
};

template<int STATE_NUM>
int MultiCalculagraph<STATE_NUM>::getNextState() {
	return (state_ + 1) % STATE_NUM;
}

// 强制改变状态
template<int STATE_NUM>
int  MultiCalculagraph<STATE_NUM>::forceSwitch(int type) {
	setCurrentState(type);
	Reset(type);
	return 0;
}
// 设置当前状态
template<int STATE_NUM>
void MultiCalculagraph<STATE_NUM>::setCurrentState(const int type) {
	assert (type < STATE_NUM && type >= 0);
	state_ = type;
	Reset(type);
}	

// 尝试切换状态
template<int STATE_NUM>
bool MultiCalculagraph<STATE_NUM>::trySwitch() {
	if (getCurrentTimeEscape() > getCurrentTimespan()) {
		state_ = getNextState();
		Reset(state_);
		return true;
	} else {
		return false;
	}
}


template<int STATE_NUM>
void  MultiCalculagraph<STATE_NUM>::Reset(const int type) {
	assert (type < STATE_NUM && type >= 0);
	calculagraph_[type].Reset();
}


template<int STATE_NUM>
DWORD MultiCalculagraph<STATE_NUM>::getCurrentTimeEscape() const {
	return calculagraph_[state_].getTimeEscape();
}

// 获取当前的Timespan
template<int STATE_NUM>
DWORD MultiCalculagraph<STATE_NUM>::getCurrentTimespan() const {
	return getTimespan(state_);
}

// 设置状态的TIMESPAN
template<int STATE_NUM>
void MultiCalculagraph<STATE_NUM>::setTimespan(const DWORD seconds, const int type) {
	assert (type < STATE_NUM && type >= 0);
	calculagraph_[type].setTimespan(seconds);
}

template<int STATE_NUM>
DWORD MultiCalculagraph<STATE_NUM>::getTimespan(const int type) const {
	assert (type < STATE_NUM && type >= 0);
	return calculagraph_[type].getTimespan();
}

#endif  // _SETTING_CALULA_GRAPH_H__
