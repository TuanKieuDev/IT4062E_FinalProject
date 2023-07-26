#ifndef __ERROR_H__
#define __ERROR_H__

//* Common error
#define ERR_SOCKET_INIT -1 /* Can't create socket */
#define ERR_CREATE_THREAD -2 /* Can't open new thread */

//* Error from server
#define ERR_CONN_ACCEPT -101 /* Can't connect */
#define ERR_OPEN_FILE -102 /* Can't open file */

//* Error from client
#define ERR_CONNECT_TO_SERVER -201 /* Can't connect to server */
#define ERR_INCORRECT_ACC -202 /* Error from password */
#define ERR_SIGNED_IN_ACC -203 /* Sign in account that logined */
#define ERR_INVALID_RECEIVER -204 /* Can't find receiver */
#define ERR_GROUP_NOT_FOUND  -205 /* Can't find group */
#define ERR_IVITE_MYSELF -206 /* Error when invite myself */
#define ERR_USER_NOT_FOUND -207 /* User not found */
#define ERR_FULL_MEM  -208 /* Full member */
#define ERR_IS_MEM  -209 /* Already in group */
/**
 * Display error
 * @param err_code mã lỗi
*/
void report_err(int err_code);

#endif
