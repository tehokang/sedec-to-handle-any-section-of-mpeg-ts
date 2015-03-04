/*************************************************************************************************************
	File 		: scxthread.h
	author 		: STC Component tstbcomp@humaxdigital.com
	comment		:
	date    	: 2013/11/25
	attention 	:

	(c) 2011-2014 Humax Co., Ltd.
	This program is produced by Humax Co., Ltd. (¡°Humax¡±) and
	the proprietary Software of Humax and its licensors. Humax provides you, as an Authorized Licensee,
	non-assignable, non-transferable and non-exclusive license to use this Software.
	You acknowledge that this Software contains valuable trade secrets of Humax and by using this Software
	you agree to the responsibility to take all reasonable efforts to protect the any information
	you receive from Humax. You are not permitted to duplicate, modify, distribute, sell or lease and
	reverse engineer or extract the source code of this Software unless you have Humax's written permission
	to do so.
	If you have no authorized license, discontinue using this Software immediately.

	THE SOFTWARE IS PROVIDED ¡°AS IS¡± AND HUMAX MAKES NO PROMISES, REPRESENTATIONS OR WARRANTIES,
	EITHER EXPRESS, IMPLIED OR STATUTORY, OR OTHERWISE, WITH RESPECT TO THE SOFTWARE.
	IN NO EVENT SHALL HUMAX BE LIABLE FOR LOST PROFITS, REVENUES, OR DATA, FINANCIAL LOSSES OR
	INDIRECT, SPECIAL, CONSEQUENTIAL, EXEMPLARTY OR PUNITIVE DAMAGES WHATSOEVER RELATING TO YOUR USE OR
	INABILITY TO USE THE SOFTWARE.

	This License is effective until terminated. You may terminate this License at any time
	by destroying all copies of the Software including all documentation. This License will terminate
	immediately without notice from Humax to you if you fail to comply with any provision of this License.
	Upon termination, you must destroy all copies of the Software and all documentation.

	The laws of the Republic of Korea will apply to any disputes arising out of or relating to
	this Copyright Notice. All claims arising out of or relating to this Copyright Notice will be litigated
	in the Seoul Central District Court, in the Republic of Korea.
*************************************************************************************************************/

#ifndef __SCX_THREAD_H__
#define __SCX_THREAD_H__

#include <pthread.h>

/*---------------------------------------------------------------
 * SCXRunnable
 *--------------------------------------------------------------*/
class SCXRunnable {
public:
	SCXRunnable() {}
	virtual ~SCXRunnable() {}

	virtual void *run() = 0;
};


/*---------------------------------------------------------------
 * SCXThread
 *--------------------------------------------------------------*/
#define SCXTHREAD_NAME_LEN	(32)

class SCXThread : public SCXRunnable {
public:
	SCXThread();
	SCXThread(const char *name);
	SCXThread(SCXThread &thread);
	virtual ~SCXThread();

	SCXThread& operator=(SCXThread& th);

	bool start();
	bool stop();
	bool join();
	bool isAlive();

	const char *getName() const;
	void setName(const char *name);

	static void sleep(unsigned int msec);

private:
	bool start(SCXRunnable *runnable);
	static void *wrapper_thread(void *args);

protected:
	char			m_name[SCXTHREAD_NAME_LEN];
	pthread_t		m_thread;
	bool			m_is_alive;
	pthread_mutex_t		m_mutex;
};

#endif /* __SCX_THREAD_H__ */
