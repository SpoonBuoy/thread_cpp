build:
	@g++ -w -o temp.exe sol.cpp
gen:
	@g++ -w -o temp.exe gen.cpp
	@./temp.exe
	rm -rf ./temp.exe
run: build
	@./temp.exe
	@rm -rf ./temp.exe
clean:
	@rm -rf ./temp.exe
	@rm -rf ./*.txt