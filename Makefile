build:
	mkdir build

app: build
	g++ -c src/app.cpp -o build/app.o

main: build
	g++ -c test/main.cpp -I src/ -o build/main.o

run: app main
	g++ -o build/run build/*.o -pthread

direct: build
	g++ -g -o build/run src/app.cpp test/main.cpp -I src/ -pthread

clean:
	rm -rf build