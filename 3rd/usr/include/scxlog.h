/*************************************************************************************************************
	File 		: scxlog.h
	author 		: STC Component tstbcomp@humaxdigital.com
	comment		:
	date    	: 2013/11/22
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

#ifndef __SCX_LOG_H__
#define __SCX_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <time.h>
#include <stdio.h>

#define MAX_LOG_NAME	64

typedef enum {
	SLOG_CRIT		= 0x00000001,
	SLOG_ERR		= 0x00000002,
	SLOG_WARN		= 0x00000004,
	SLOG_INFO		= 0x00000008,
	SLOG_DEBUG		= 0x00000010
} eScxLogLevel;

typedef struct {
	char	name[MAX_LOG_NAME];
	int		log_mask;
	FILE	*fp;
} scxlog_t;

/*-------------------------------------------------------------------------
 *	interfaces
 *------------------------------------------------------------------------*/
/**
 * Initialize the log object
 *
 * @param[in] slog log object
 *
 * @return NONE
 */
void scxlog_init(scxlog_t *slog);

/**
 * Clean up the log object
 *
 * @param[in] slog log object
 *
 * @return NONE
 */
void scxlog_cleanup(scxlog_t *slog);

/**
 * Get the pointer of default log object
 *
 * @return The default log object 
 */
scxlog_t *scxlog_get_default_log();

/**
 * Set default log object
 *
 * @return The default log object 
 */
void scxlog_set_default_log(scxlog_t *def_log);

/**
 * Set the log name.
 *
 * @param[in] slog log object
 * @param[in] name the log name
 *
 * @return NONE
 */
void scxlog_set_name(scxlog_t *slog, const char *name);

/**
 * Get the log mask which set in scxlog.
 *
 * @param[in] slog log object
 *
 * @return the log mask
 */
unsigned int scxlog_get_logmask(const scxlog_t *slog);

/**
 * Set the log mask.
 * You can set the log priorities what you want to print to console.
 * eg)
 * 	scxlog_set_log_mask(slog, SLOG_CRIT | SLOG_ERR | SLOG_WARN)
 *
 * @param[in] slog log object
 * @param[in] log_mask the log prority mask
 *
 * @return NONE
 */
void scxlog_set_logmask(scxlog_t *slog, unsigned int log_mask);

/**
 * Set the console
 * The scxlog supports both of console and file logging, and so if you want to save the log to file,
 * you can set the opened file pointer or standard in/out/error by yourself.
 * If the file pointer is NULL, it will set as stdout.
 *
 * @param[in] slog log object
 * @param[in] fp the opend file pointer
 *
 * @return NONE
 */
void scxlog_set_console(scxlog_t *slog, FILE *fp);

/**
 * Print the log message with the time and priority.
 *
 * @param[in] slog log object
 * @param[in] time the logging time
 * @param[in] pri the log priority level
 * @param[in] format the log format
 *
 * @return return the size of log message if successful. Or 0 on error.
 */
int scxlog_print(const scxlog_t *slog, const char *time, int pri, const char *format, ...);

/*-------------------------------------------------------------------------
 *	easy interfaces
 *	You can display the log message on console or file via scx easy interfaces.
 *------------------------------------------------------------------------*/
/**
 * Critical log
 *
 * @return return the size of log message if successful. Or -1 on error.
 */
int sl_crit(const char *format, ...);

/**
 * Error log
 *
 * @return return the size of log message if successful. Or -1 on error.
 */
int sl_err(const char *format, ...);

/**
 * Warning log
 *
 * @return return the size of log message if successful. Or -1 on error.
 */
int sl_warn(const char *format, ...);

/**
 * Information log
 *
 * @return return the size of log message if successful. Or -1 on error.
 */
int sl_info(const char *format, ...);

/**
 * Debug log
 *
 * @return return the size of log message if successful. Or -1 on error.
 */
int sl_dbg(const char *format, ...);

#ifdef __cplusplus
};
#endif

#endif	/* __SCX_LOG_H__ */
