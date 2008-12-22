#ifndef _UTILITY_BUFFERCALLER_H__
#define _UTILITY_BUFFERCALLER_H__

// 对于某些耗时的函数， 他的结果也许一段时间内不会改变
// 我们只需要n次调用一次就可以了， 这种情况下应该使用此类
// 注意： 此类并不负责保存调用结果， 用户应该实现一个自己的
// 函数对象，并使用函数对象保存相应结果。

// 是否应该调用的计算
// 例如：如果用户指定三次调用一次啊， 那么用户调用才函数3次，实际上
// 将会调用两次实际的函数， 调用6次会调用3次，即每次都为 n%m+1
// 因为第一次调用的是否必须保证函数被实际调用了

// 注意BUF_CNT > 2
template <class T, int BUF_CNT>
class BufferCaller {
public:
	BufferCaller() {
		call_cnt_ = 0;
	}
	~BufferCaller() {
	}

	// 如果因该调用则调用，否则不调用
	// 注， 用户负责保存第一次的调用结果
	void Call(T &a) {
		if (CallDirectly()) {
			a();
		}
	}
private:
	// 用于判断是否应该直接调用函数， 或者利用函数旧有的结果
	// 此函数必须抱枕第一次被调用时返回true
	// 注：必须保证函数对象内部应经存在结果
	bool CallDirectly() {
		if (call_cnt_ % BUF_CNT == 0) {
			call_cnt_ = 1;
			return true;
		} else {
			call_cnt_ ++;
			return false;
		}
	}

	// 记录次数
	int call_cnt_;

	// 测试类
	friend class BufferCallerTest;
};

#endif  // _UTILITY_BUFFERCALLER_H__