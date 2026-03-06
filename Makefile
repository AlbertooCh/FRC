all:
	g++ -fpermissive Sesion2.cpp linkLayer.a -o Sesion2 -lpcap -pthread
run:
	sudo ./Sesion2
clean:
	rm -f Sesion2