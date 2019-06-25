.PHONY: data clean test resultat

TARGET = tp1
OBJECTS = tp1.o
CC = gcc
CFLAGS = -Wall -pedantic -std=c11
SOURCE = https://www.github.com/guyfrancoeur/INF3135_E2019_TP/raw/master/crypto-data.zip
FILEIN = ./data/crypto-msg01.in
FILEOUT = ./data/crypto-msg01.out
FILEALPHA = ./data/crypto-msg01.alphabet

CLE=`cat ./data/crypto-msg01.cle`
ACTION=`cat ./data/crypto-msg01.action`
CP=`cat cp.txt`

default: tp1

tp1: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

tp1.o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c
data:
	rm -rf ./data
	mkdir data
	cd data
	wget $(SOURCE)
	unzip crypto-data.zip -d ./data
	rm -rf crypto-data.zip

clean:
	rm -rf $(TARGET) *.o
	rm -rf data

resultat:
	git add note-du-tp.txt
	git commit -m "le fichier note-du-tp.txt est pousse dans le depot distant"
	git push origin master

test:
	./$(TARGET) -i $(FILEIN) -o $(FILEOUT) -a $(FILEALPHA) -k ${CLE} ${ACTION} -c ${CP}
