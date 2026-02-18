all:
	g++ -fpermissive Sesion1.cpp linkLayer.a -o Sesion1 -lpcap -pthread
run:
	sudo ./Sesion1
clean:
	rm -f Sesion1