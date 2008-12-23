#ifndef _UTILITY_BUFFERCALLER_H__
#define _UTILITY_BUFFERCALLER_H__

// ����ĳЩ��ʱ�ĺ����� ���Ľ��Ҳ��һ��ʱ���ڲ���ı�
// ����ֻ��Ҫn�ε���һ�ξͿ����ˣ� ���������Ӧ��ʹ�ô���
// ע�⣺ ���ಢ�����𱣴���ý���� �û�Ӧ��ʵ��һ���Լ���
// �������󣬲�ʹ�ú������󱣴���Ӧ�����

// �Ƿ�Ӧ�õ��õļ���
// ���磺����û�ָ�����ε���һ�ΰ��� ��ô�û����òź���3�Σ�ʵ����
// �����������ʵ�ʵĺ����� ����6�λ����3�Σ���ÿ�ζ�Ϊ n%m+1
// ��Ϊ��һ�ε��õ��Ƿ���뱣֤������ʵ�ʵ�����

// ע��BUF_CNT > 2
template <class T, int BUF_CNT>
class BufferCaller {
public:
	BufferCaller() {
		call_cnt_ = 0;
	}
	~BufferCaller() {
	}

	// �����õ�������ã����򲻵���
	// ע�� �û����𱣴��һ�εĵ��ý��
	void Call(T &a) {
		if (CallDirectly()) {
			a();
		}
	}
private:
	// �����ж��Ƿ�Ӧ��ֱ�ӵ��ú����� �������ú������еĽ��
	// �˺������뱧���һ�α�����ʱ����true
	// ע�����뱣֤���������ڲ�Ӧ�����ڽ��
	bool CallDirectly() {
		if (call_cnt_ % BUF_CNT == 0) {
			call_cnt_ = 1;
			return true;
		} else {
			call_cnt_ ++;
			return false;
		}
	}

	// ��¼����
	int call_cnt_;

	// ������
	friend class BufferCallerTest;
};

#endif  // _UTILITY_BUFFERCALLER_H__