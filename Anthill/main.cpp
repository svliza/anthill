#include <thread>
#include <chrono>
#include "field.h"

int main() {
	Field field(9, 15);
	for (int i = 0; i < 5; i++) {
		field.generation_resources();
		field.print_field();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}