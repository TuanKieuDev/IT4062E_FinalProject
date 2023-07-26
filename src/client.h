#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "server.h"
#include "network.h"
#include "db.h"
#include "error.h"
#include "util.h"

#include "rsa.h"

// #define TESTING_MSG "#sys_testing#"

extern struct public_key_class my_pub[1];
extern struct private_key_class my_priv[1];

extern Public_key_users pub[512];
extern int pubkey_count;

void send_my_public_key(int client_socket);
void receive_public_key(int client_socket, Package* pkg);
int check_public_key(int client_socket, char* username);

char* group_msg_encrypt(char* msg, char* key);
char* group_msg_decrypt(char* msg, char* key);


extern char my_username[USERNAME_SIZE];
extern char curr_group_name[GROUP_NAME_SIZE];
extern int curr_group_id;
extern int join_succ;

//* Connect
/**
 * Create socket and connect to server
 * @return socket connected to server
*/
int connect_to_server();

void login_menu();

void user_menu();

void group_chat_menu();

void sub_group_chat_menu(char *group_name);

void ask_server(int client_socket);

int login(int client_socket, char *username, char *password);

void user_use(int client_socket);

void *read_msg(void *param);

void see_active_user(int client_socket);

int private_chat(int client_socket, char *receiver, char *msg);

void make_done(); 

int check_receiver(int client_socket, char* receiver);

void chat_all(int client_socket);

void group_chat_init(int client_socket);

void show_group(int client_socket);

void new_group(int client_socket);

void join_group(int client_socket, char *group_name);

void handel_group_mess(int client_socket);

void invite_friend(int client_socket, char *friend_username);

void group_chat(int client_socket, char *msg);

void show_group_info(int client_socket);

void leave_group(int client_socket);

void logout(int client_socket);

#endif
