#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "account_manager.h"
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sqlite3.h>
#include <string.h>


#define MSG_SIZE 2048
#define MAX_SQL_SIZE 3072
//* Control signal

// server
#define LOGIN_SUCC 101 /* Login successful */
#define INCORRECT_ACC 102 /* Wrong username or password */
#define SIGNED_IN_ACC 103 /* Account was logined */
#define RECV_SUCC 104 /* Receive successful */

// client
#define LOGIN_REQ 201 /* Request login */
#define QUIT_REQ 202 /* Request logout */

#define MSG_SENT_SUCC 301
#define END_CHAT 302

#define SHOW_USER 401
#define CHAT_ALL 403
#define LOG_OUT 404

#define GROUP_CHAT_INIT 405
#define SHOW_GROUP 406
#define NEW_GROUP  407
#define MSG_MAKE_GROUP_SUCC 408
#define MSG_MAKE_GROUP_ERR 409
#define JOIN_GROUP 410
#define JOIN_GROUP_SUCC 411
#define HANDEL_GROUP_MESS 412
#define INVITE_FRIEND 413
#define INVITE_FRIEND_SUCC 414
#define GROUP_CHAT 415
#define GROUP_INFO 416
#define SHOW_GROUP_INFO_START 417
#define SHOW_GROUP_NAME 418
#define SHOW_GROUP_MEM_NUMBER 419
#define SHOW_GROUP_MEM_USERNAME 420
#define SHOW_GROUP_INFO_END 421
#define LEAVE_GROUP 422
#define LEAVE_GROUP_SUCC 423


#define PRIVATE_CHAT 501
#define SEND_PUBLIC_KEY 502
#define SEND_PUBLIC_KEY_REQ 503
#define RECV_PUB_KEY_SUCCESS 504
#define NO_PUBLIC_KEY -504

#define TESTING_MSG "#sys_testing#"



//* Message format
typedef struct Package_ {
    char msg[MSG_SIZE]; /* message content */
    long long encrypted_msg[MSG_SIZE]; /* encode message content */
    char sender[USERNAME_SIZE]; /* sender's username */
    char receiver[USERNAME_SIZE]; /* receiver's username */
    int group_id; /*group id*/
    int ctrl_signal; /* control signal */
} Package;


#endif
