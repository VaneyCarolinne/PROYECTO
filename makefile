#Makefile Proyecto

#Variables
CC = g++ #Compilador
CFLAGS = -g #Depurador
PRINCIPAL = main.cpp #Archivo en que se ejecutara el programa
OBJETOS = main.o #Objetos 

#EJECUTABLE
EXE: $(OBJETOS)
	$(CC) -o $@ $^

#Para Compilar las Clases
	#Archivo Ejecutable
Main: $(PRINCIPAL) $(OBJETOS) 
	$(CC) $(CFLAGS) $(PRINCIPAL) $(OBJETOS) -o $@
	#Lista de Objetos
main.o: main.cpp Element.h Node.h DOM_Tree.h
	$(CC) $(CFLAGS) -c $<

#Eliminación de los archivos temporales
clean:
	rm -rf EXE *.o

