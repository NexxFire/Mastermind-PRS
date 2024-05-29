# Compiler options
CC = gcc
CFLAGS = -Wall -Wextra -Iclient/include -Iserver/include -IlibSocket -IlibUtils -pthread
LDFLAGS = -pthread

# Directories
BUILD_DIR = build
INTER_DIR = $(BUILD_DIR)/intermediate
CLIENT_DIR = client
SERVER_DIR = server
LIBSOCKET_DIR = libSocket
LIBUTILS_DIR = libUtils

# Files
CLIENT_SRCS = $(wildcard $(CLIENT_DIR)/src/*.c)
CLIENT_OBJS = $(patsubst $(CLIENT_DIR)/src/%.c,$(INTER_DIR)/%.o,$(CLIENT_SRCS))
SERVER_SRCS = $(wildcard $(SERVER_DIR)/src/*.c)
SERVER_OBJS = $(patsubst $(SERVER_DIR)/src/%.c,$(INTER_DIR)/%.o,$(SERVER_SRCS))
LIBSOCKET_SRCS = $(wildcard $(LIBSOCKET_DIR)/*.c)
LIBSOCKET_OBJS = $(patsubst $(LIBSOCKET_DIR)/%.c,$(INTER_DIR)/%.o,$(LIBSOCKET_SRCS))
LIBUTILS_SRCS = $(wildcard $(LIBUTILS_DIR)/*.c)
LIBUTILS_OBJS = $(patsubst $(LIBUTILS_DIR)/%.c,$(INTER_DIR)/%.o,$(LIBUTILS_SRCS))

# Executables
CLIENT_EXECUTABLE = $(BUILD_DIR)/client
SERVER_EXECUTABLE = $(BUILD_DIR)/server

.PHONY: all clean client server

all: $(BUILD_DIR) client server

$(BUILD_DIR):
	mkdir -p $(INTER_DIR)

client: $(BUILD_DIR) $(CLIENT_EXECUTABLE)
	
server: $(BUILD_DIR) $(SERVER_EXECUTABLE)
	

$(CLIENT_EXECUTABLE): $(CLIENT_OBJS) $(LIBSOCKET_OBJS) $(LIBUTILS_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(SERVER_EXECUTABLE): $(SERVER_OBJS) $(LIBSOCKET_OBJS) $(LIBUTILS_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(INTER_DIR)/%.o: $(CLIENT_DIR)/src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(INTER_DIR)/%.o: $(SERVER_DIR)/src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(INTER_DIR)/%.o: $(LIBSOCKET_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(INTER_DIR)/%.o: $(LIBUTILS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
