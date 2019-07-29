.PHONY: data clean test resultat

TARGET = tp1
OBJECTS = tp1.o
CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -lm -O2
SOURCE = https://www.github.com/guyfrancoeur/INF3135_E2019_TP/raw/master/crypto-data.zip
FILEIN = ./data/crypto-msg01.in
FILEOUT = ./data/crypto-msg01.out
FILEALPHA = ./data

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
	mv ./data/crypto-msg01.alphabet ./data/alphabet.txt



clean:
	rm -rf *.o data tp1 tp2 *.h.gch

resultat:
	git add note-du-tp.txt
	git commit -m "le fichier note-du-tp.txt est pousse dans le depot distant"
	git push origin master

test: data tp1
	./$(TARGET) -i $(FILEIN) -o $(FILEOUT) -a $(FILEALPHA) -k ${CLE} ${ACTION} -c ${CP}

