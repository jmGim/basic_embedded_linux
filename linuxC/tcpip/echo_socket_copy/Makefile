CC=gcc

TARGET_SRV=echo_server
TARGET_CLN=echo_client

OBJECT_SRV=$(TARGET_SRV).o
OBJECT_CLN=$(TARGET_CLN).o

all:$(TARGET_SRV) $(TARGET_CLN)

$(TARGET_SRV):$(OBJECT_SRV)
	$(CC) -o $@ $(OBJECT_SRV)

$(TARGET_CLN):$(OBJECT_CLN)
	$(CC) -o $@ $(OBJECT_CLN)

%.o:%.c
	$(CC) -c -o $@ $<

clean:
	rm -rf *.o $(TARGET_SRV) $(TARGET_CLN)
