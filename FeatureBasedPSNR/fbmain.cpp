#include"../ConfigGenerator/ConfigGenerator.h"

int main(int argc, char* argv[]){
	ConfigGenerator generator(argv[1]);
	generator.nameReader(argv[2]);
	generator.generateFbBatch();
	//generator.runFbBatch();
	return 1;
}