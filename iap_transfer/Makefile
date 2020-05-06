P=$(shell echo $(INSTALL_PATH))

iap_transfer:main.c iap2.c
	$(CC) main.c iap2.c  -o iap_transfer

install:
	cp iap_transfer $(P)/
clean:
	rm *.o iap_transfer *.out
