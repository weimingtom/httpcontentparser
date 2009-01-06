#ifndef _SELECTIO_BUFFERRESULT_H__
#define _SELECTIO_BUFFERRESULT_H__

#include <map>
#include <string>
#include <utility\replacepacket.h>
#include <utility\HTTPPacket.h>
#include <utility\fd_set_utility.h>

class HTTPPacket;

// ��������Ľ��
// ���һ��������ɽ���֮�󣬿��ܻ�Ҫ�ֳɶ�������ϲ������
// ��ʱ������һ������: ����������ݻᱻ����Σ� ����ͬʱ��
// �ᱻ�����Ρ� Ϊ���޸�����������ǻ���һ��������Ľ����
// ���ֵӦ����handlePacket��ӻ��ѯ
// ��removePacketʱ�Ƴ�
class BufferResult {
public:
	bool getResult(int code, int * result); 
	void addResultPair(int code, int result);
	void removeBufferResult(HTTPPacket *packet);
	void removeAllBufferResult() {content_check_result_.clear();}

private:
	typedef std::map<int, int> BUFFER_RESULT;
	BUFFER_RESULT content_check_result_;

	// �ٽ���
	yanglei_utility::CAutoCreateCS cs_;
};

#endif  // _SELECTIO_BUFFERRESULT_H__