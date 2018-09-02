all:
	g++ main.cc `pkg-config --cflags --libs opencv`