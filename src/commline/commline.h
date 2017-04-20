#ifndef	_COMMLINE_H_
#define	_COMMLINE_H_

#include <sys/time.h>

#define	CL_SUCCESS	0
#define	CL_FAILURE	-1

#define	COMMLINE_MAX_BUF	2048

#define	CL_CREATEQ	(1<<0)	//Used by airline
#define	CL_ATTACHQ	(1<<1)	//Used by stackline

int cl_init(const uint8_t flags);
void cl_cleanup(void);

typedef struct _msg_buf_
{
	long mtype;
	uint16_t src_id;
	uint16_t dst_id;
	uint16_t len; // length of the buf only
	uint8_t lqi;	//Link quality indicator .. sent from airline to stackline
	uint8_t buf[1];
}msg_buf_t;

int cl_recvfrom_q(const long mtype, msg_buf_t *mbuf, uint16_t len);
int cl_sendto_q(const long mtype, msg_buf_t *mbuf, uint16_t len);

enum {
	STACKLINE=1,
	AIRLINE,
	FORKER,
};

#define	MTYPE(LINE,ID)	(((LINE)<<16)|(ID))

#ifndef	ERROR
#define	PRN(...)	\
	{\
		struct timeval tv;\
		gettimeofday(&tv, NULL);\
		printf("[%s:%d] [%ld:%ld] ", __FUNCTION__, __LINE__, tv.tv_sec, tv.tv_usec);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
	}
#define	ERROR(...) PRN(__VA_ARGS__)
#define	INFO(...) PRN(__VA_ARGS__)
#define	WARN(...) PRN(__VA_ARGS__)
#endif //ERROR

#endif	//_COMMLINE_H_
