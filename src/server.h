#ifndef __SERVER_H__
#define __SERVER_H__

#include "network.h"
#include "db.h"
#include "error.h"
#include "account_manager.h"

#include "rsa.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define MAX_USER 1024
#define MAX_GROUP 10
#define NULL_STRING "#NULL_STRING#"
#define SERVER_SYSTEM_USERNAME "#server_system#"
#define GROUP_NAME_SIZE 30

//* Active user
typedef struct Active_user_ {
    char username[USERNAME_SIZE]; 
    int socket; 
    int group_id[MAX_GROUP];
} Active_user;

//* Group
typedef struct Member_{
    char username[USERNAME_SIZE]; 
    int socket; 
} Member;

typedef struct Group_ {
    Member group_member[MAX_USER]; 
    int curr_num; 
    char group_name[GROUP_NAME_SIZE]; 
} Group;



typedef struct public_key_users_ {
    char username[USERNAME_SIZE];
    struct public_key_class public_key[1];
}Public_key_users;

void send_public_key(int client_socket, char* receiver);
void save_public_key(char* sender, char* msg);

//* Create server
/**
 * Create socket 
 * @return file descriptor của socket
*/
int create_listen_socket();

/**
 * Accpet client
 * @param listen_socket socket listen connect
 * @return file descriptor of connected socket
*/
int accept_conn(int listen_socket);

/**
 * Read account list
 * Create listen socket and accept connect
 * Distribute thread for each user
*/
void make_server();

//* Before user login
/**
 * Receive request
 * @param param socket connect to client
*/
void *pre_login_srv(void *param);

/**
 * Check username and password
 * @param conn_socket socket kết nối đến client
 * @param acc_list danh sách tài khoản
*/
void handle_login(int conn_socket, Account *acc_list);

/**
 * Search user by conn_socket
 * @param conn_socket socket connect to client
 * @param acc_list account list
*/
int search_user(int conn_socket);


//* After login
void sv_user_use(int conn_socket);

/**
 * Display online user
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
void sv_active_user(int conn_socket, Package *pkg);

/**
 * Resolve 1-1 chat
 * @param conn_socket socket Connect to client
 * @param pkg pointer to message from client
*/
void sv_private_chat(int conn_socket, Package *pkg);

/**
 * Resolve chat all
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
void sv_chat_all(int conn_socket, Package *pkg);

/**
 * Resolve group chat
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
void sv_group_chat_init(int conn_socket, Package *pkg);

/**
 * Send to member of current group
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
void sv_show_group(int conn_socket, Package *pkg);

/**
 * Create new group
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
void sv_new_group(int conn_socket, Package *pkg);

/**
 * Invite user to group
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
int sv_add_group_user(Active_user *user, int group_id);

/**
 * Leave group
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
int sv_leave_group_user(Active_user *user, int group_id);

/**
 * Add user to group
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
int sv_add_user(Active_user user, Group *group);

/**
 * user join group
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
void sv_join_group(int conn_socket, Package *pkg);

/**
 * Find group id by name
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
int  sv_search_id_group(Group group[],Active_user user, char *group_name);

/**
 * Find user id by name
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
int  sv_search_id_user(Active_user user[], char *user_name);

/**
 * Find user id by name
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
int  sv_search_id_user_group(Group group, char *user_name);

/**
 * Invite friend
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
void sv_invite_friend(int conn_socket, Package *pkg);

/**
 * Chat in group
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
void sv_group_chat(int conn_socket, Package *pkg);

/**
 * Display group info
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
void sv_show_group_info(int conn_socket, Package *pkg);

/**
 * Leave group
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
void sv_leave_group(int conn_socket, Package *pkg);

/**
 * Update group
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
void sv_update_port_group(Active_user *user, Group *group);




/**
 * Display members in group
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
void print_members(Group group);
/**
 * Check user in group or not
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
int check_user_in_group(Active_user user, int group_id);
/**
 * Logout
 * @param conn_socket socket connect to client
 * @param pkg pointer to message from client
*/
void sv_logout(int conn_socket, Package *pkg);

#endif
