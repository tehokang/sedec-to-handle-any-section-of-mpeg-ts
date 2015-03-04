/*************************************************************************************************************
	File 		: hdkappmgr.h
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

#ifndef __HDK_APPLICATION_MANAGER_H__
#define __HDK_APPLICATION_MANAGER_H__

#include "cpp/scxthread.h"
#include "scxlock.h"

#include <queue>

class HdkApplication;
class HdkApplicationContainer;

typedef enum {
	HDKAPPMGR_STATE_IDLE				= 0,
	HDKAPPMGR_STATE_NEW,
	HDKAPPMGR_STATE_PREV_CHECK,
	HDKAPPMGR_STATE_PREV_CHECK_AUTH,
	HDKAPPMGR_STATE_DISCARD,
	HDKAPPMGR_STATE_KILL,
	HDKAPPMGR_STATE_LOAD,
	HDKAPPMGR_STATE_FINISH
} eHdkAppMgrState;

/*------------------------------------------------------------------------
 * class HdkApplicationManager
 *-----------------------------------------------------------------------*/
class HdkApplicationManager : public SCXThread {
public:
	HdkApplicationManager();
	virtual ~HdkApplicationManager();

	bool push(HdkApplicationContainer *container);
	void pop();
	void popAll();

	bool runApplication(HdkApplication *app);
	bool stopCurrentApplication();
	HdkApplicationContainer *getCurrentContainer();

	virtual void *run();

public:
	static HdkApplicationManager	*s_the_appmgr;

private:
	void runLifeCycle();
	void stateIdle();
	void stateNew();
	void statePrevCheck();
	void statePrevCheckAuth();
	void stateDiscard();
	void stateKill();
	void stateLoad();
	void stateFinish();
	void goIdle();

private:
	eHdkAppMgrState	m_state;
	SCXLock			m_lock;
	std::queue<HdkApplicationContainer *>	m_app_container_queue;
	HdkApplicationContainer *m_prev_app_container;
	HdkApplication *m_target_app;
};

static inline HdkApplicationManager *getApplicationManager() { return HdkApplicationManager::s_the_appmgr; }

#endif	/* __HDK_APPLICATION_MANAGER_H__ */
