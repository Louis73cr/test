##
## EPITECH PROJECT, 2022
## makefile
## File description:
## makefile
##

SRC_SRV 	=	src/server/main.c								\
				src/server/srv/server.c							\
				src/server/srv/server_accept_connections.c		\
				src/server/srv/server_check_client.c			\
				src/server/srv/server_socket_creations.c		\
				src/server/utils/uuid_generator.c				\
				src/server/utils/current_time.c					\
				src/server/utils/nb_line_in_conf_file.c			\
				src/server/data_save/data_gestion.c				\
				src/server/data_save/user_save.c				\
				src/server/data_save/team_save.c				\
				src/server/data_save/team_save2.c				\
				src/server/data_save/channel_save.c				\
				src/server/data_save/channel_save2.c			\
				src/server/data_save/channel_save3.c			\
				src/server/data_save/message_save.c				\
				src/server/data_save/message_save2.c			\
				src/server/data_save/load_message.c				\
				src/server/data_save/load_message2.c			\
				src/server/data_save/save_personnal_msg.c		\
				src/server/data_save/save_thread.c				\
				src/server/data_save/load_thread.c				\
				src/server/data_save/load_thread2.c				\
				src/server/data_save/load_personnal_msg.c		\
				src/server/data_save/load_personnal_msg2.c		\
				src/server/commande/handle_message.c 			\
				src/server/commande/channel/handle_channel.c 	\
				src/server/commande/channel/get_msg_channel.c	\
				src/server/commande/channel/get_msg_channel_bis.c	\
				src/server/commande/channel/send_msg_channel.c	\
				src/server/commande/channel/send_msg_channel2.c	\
				src/server/commande/channel/move_channel.c		\
				src/server/commande/channel/get_channel.c		\
				src/server/commande/channel/delete_channel.c	\
				src/server/commande/channel/create_channel.c	\
				src/server/commande/channel/update_channel.c	\
				src/server/commande/channel/find_pos.c			\
				src/server/commande/other/handle_other.c 		\
				src/server/commande/team/handle_team.c			\
				src/server/commande/team/get_user_in_team.c		\
				src/server/commande/team/create_team.c			\
				src/server/commande/team/delete_team.c			\
				src/server/commande/team/get_team.c				\
				src/server/commande/team/info_team.c			\
				src/server/commande/team/join_team.c			\
				src/server/commande/team/leave_team.c			\
				src/server/commande/team/move_team.c			\
				src/server/commande/thread/handle_thread.c		\
				src/server/commande/thread/thread_get_msg.c		\
				src/server/commande/thread/thread_send_msg.c	\
				src/server/commande/thread/thread_create.c		\
				src/server/commande/thread/thread_info.c		\
				src/server/commande/thread/thread_move.c		\
				src/server/commande/user/handle_user.c			\
				src/server/commande/user/handle_connections.c 	\
				src/server/commande/user/handle_connections2.c 	\
				src/server/commande/personnal_message/get_msg_pm.c 		\
				src/server/commande/personnal_message/get_pm.c 			\
				src/server/commande/personnal_message/handle_pm.c 		\
				src/server/commande/personnal_message/pm_create.c 		\
				src/server/commande/personnal_message/pm_info.c 		\
				src/server/commande/personnal_message/pm_move.c 		\
				src/server/commande/personnal_message/send_msg_pm.c 	\

OBJ_SRV = $(SRC_SRV:.c=.o)

NAME_SRV = myteams_server

CFLAGS = -I libs/myteams/ -L libs/myteams/ -g3 -W -Wall -Wextra #-Werror

NAME_CLIENT = myteams_cli

SRC_CLI	=	src/client/client.c	\
			src/client/client_run.c	\
			src/client/commands/list/handle_list.c	\
			src/client/commands/list/list_channel.c	\
			src/client/commands/list/list_team.c	\
			src/client/commands/list/list_response.c	\
			src/client/commands/list/list_thread.c	\
			src/client/commands/login/handle_login.c	\
			src/client/commands/login/new_user.c	\
			src/client/commands/logout/handle_logout.c	\
			src/client/commands/use/handle_use.c	\
			src/client/commands/use/set_new_loc.c	\
			src/client/commands/create/handle_create.c	\
			src/client/commands/create/create_response.c	\
			src/client/commands/create/create_team.c	\
			src/client/commands/create/create_thread.c	\
			src/client/commands/create/create_channel.c	\
			src/client/commands/info/handle_info.c	\
			src/client/commands/messages/handle_message.c	\
			src/client/commands/send/handle_send.c	\
			src/client/commands/subscribe/handle_subscribe.c	\
			src/client/commands/subscribed/handle_subscribed.c	\
			src/client/commands/unsubscribe/handle_unsubscribe.c	\
			src/client/commands/help/help.c	\
			src/client/commands/users/handle_users.c	\
			src/client/commands/user/handle_user.c	\
			src/client/tools/util.c	\
			src/client/tools/util_bis.c	\
			src/client/tools/util_three.c	\
			src/client/tools/util_four.c

OBJ_CLI = $(SRC_CLI:.c=.o)

all: $(NAME_SRV) $(NAME_CLIENT) create_data_dir

$(NAME_SRV): $(OBJ_SRV)
	gcc -o $(NAME_SRV) $(OBJ_SRV) -luuid -L ./libs/myteams	\
-I ./libs/myteams -lmyteams

$(NAME_CLIENT): $(OBJ_CLI)
	gcc -o $(NAME_CLIENT) $(OBJ_CLI) -L ./libs/myteams	\
-I ./libs/myteams -lmyteams

create_data_dir:
	mkdir -p data

dev:
	all clean

clean:
	rm -f $(OBJ_SRV)
	rm -f $(OBJ_CLI)

fclean: clean
	rm -f $(NAME_SRV)
	rm -f $(NAME_CLIENT)

re: fclean all

dev: all clean

.PHONY: all clean fclean re dev
